// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BLKQUEUE_HEADER
#define RAVL_BLKQUEUE_HEADER 1
///////////////////////////////////////////////////////////////////////////
//! date="15/11/1995"
//! file="Ravl/Core/Container/Queue/BlkQueue.hh"
//! lib=RavlCore
//! author="George (Jiri) Matas"
//! docentry="Ravl.API.Core.Queues"
//! example=exQueue.cc
//! rcsid="$Id: BlkQueue.hh 6479 2007-12-01 10:26:31Z craftit $"

#include "Ravl/Assert.hh"

#if RAVL_HAVE_TEMPLATEREQUIREALLDEFINITIONS 
#include "Ravl/Stream.hh"
#endif

#if RAVL_HAVE_ANSICPPHEADERS
#include <new>
#else
#include <new.h>
#endif

namespace RavlN {
  //: Basic Queue.
  //! userlevel=Normal
  
  template <class T>
  class BlkQueueC {
  public:
    
    inline BlkQueueC(int blkSize = 20);
    ~BlkQueueC();
    
    inline T GetFirst();
    //: Get the first element in the queue.
    
    inline void InsLast(const T& data);
    //: Put an item at the end of the queue.
    
    inline T& First()
    { return (first!=blkSize) ? firstBlk->d[first] : firstBlk->link->d[0]; }
    //: Access the first element in the queue.
    
    inline const T& First() const
    { return (first!=blkSize) ? firstBlk->d[first] : firstBlk->link->d[0]; }
    //: Access the first element in the queue.
    
    inline T& Last()
    { return lastBlk->d[last-1]; }
    //: Access the last element in the queue.
    
    inline const T& Last()  const
    { return lastBlk->d[last-1]; }
    //: Access the last element in the queue.
    
    inline bool IsEmpty() const
    { return last==first && lastBlk==firstBlk; }
    //: Is queue empty ?
    
    inline SizeT Size() const
    { return last-first + blkTotal; }
    //: Returns the number of items in the queue.
    
    inline void DelFirst(); 
    //: Delete the first element in the queue.
    
    inline void  Empty();
    //: Empty the queue of all items.

    inline void InsFirst(const T& data);
    //: Insert an item at the front of the queue.
    
    inline T& Top()
    { return First(); }
    //: Alias for First().
    
    inline void Push(const T& d)
    { InsFirst(d); }
    //: Push an item onto the front of the queue.
    
    inline T Pop()
    { return GetFirst();}
    //: Pop an item off the front on the queue.
    
    void DbPrint(){ cerr << "queue -> "<< last <<", "<< first <<", "<< Size() <<"\n"; }
    //: Debug print.
    
  protected:
    inline void Init();
    inline void FixFirst();
    //! userlevel=Develop
    struct q_Blk {q_Blk* link; T d[1];};
    q_Blk * AllocBlk()
    {return (q_Blk*) new char[sizeof(q_Blk) + sizeof(T)*(blkSize-1)];}
    void FirstBlk();
    void DelBlk();
    
    q_Blk* firstBlk;                   
    q_Blk* lastBlk;                   
    
    short first;
    short last;
    short blkSize;
    int blkTotal;
  };
  
  //--------------------------------------------------------------------------
  
  template<class T>
  inline void BlkQueueC<T>::Init() {
    RavlAssert(blkSize > 0);
    blkSize    =  -blkSize;
    first      =  last    = blkSize; 
    firstBlk   =  lastBlk = 0;
    blkTotal   =  0;
  }
  
  template<class T>
  inline 
  BlkQueueC<T>::BlkQueueC(int size)
    : blkSize(size) 
  { Init(); }
  
  template <class T>
  void BlkQueueC<T>::DelBlk() {
    q_Blk * next = firstBlk->link;
    delete [] ((char *) firstBlk);
    firstBlk = next;
    blkTotal -=   blkSize;
  }
  
  template<class T>
  inline void BlkQueueC<T>::FirstBlk() {
    blkSize  = -blkSize;
    first    = last   = 0;
    firstBlk = lastBlk= AllocBlk();
  }
  
  template<class T> 
  inline void    BlkQueueC<T>::Empty() {
    while(!IsEmpty())
      DelFirst();
  }
  
  template<class T>
  BlkQueueC<T>::~BlkQueueC()  { 
    Empty(); 
    if(firstBlk != 0)
      DelBlk(); 
  }
  
  template<class T>
  inline  void BlkQueueC<T>::FixFirst() {
    if (IsEmpty()) 
      IssueError(__FILE__,__LINE__,"attempting to read from and empty queue.");
    if (first == blkSize)  {
      DelBlk();
      first = 0;
    }
  }
  
  template<class T>
  inline  void BlkQueueC<T>::DelFirst() {
    FixFirst();
    (&firstBlk->d[first++])->~T();
  }
  
  template<class T>
  inline  T BlkQueueC<T>::GetFirst() {
    FixFirst();
    T tmp=firstBlk->d[first];
    (&firstBlk->d[first++])->~T();
    return tmp;
  }
    
  template<class T>
  inline void BlkQueueC<T>::InsLast(const T& data) {
    if (last == blkSize) {
      if(blkSize<0)
	FirstBlk();
      else {
	lastBlk->link = AllocBlk();
	lastBlk = lastBlk->link;
	blkTotal +=   blkSize;
	last = 0;
      }
      lastBlk->link = NULL;
    }
    new(&lastBlk->d[last++]) T(data);   // like a straightforward array impl.
  }
  
  template<class T>
  inline 
  void BlkQueueC<T>::InsFirst(const T& data) {
    --first;
    if(first<0) {
      if (blkSize<0) {
	FirstBlk();
	new(&(firstBlk->d[last++])) T(data);
	return;
      } else {
	q_Blk* f = AllocBlk();
	f->link  = firstBlk;
	firstBlk = f;
	first    = blkSize - 1;
	blkTotal += blkSize;
      }
    }
    new(&firstBlk->d[first]) T(data);
  }
}

#endif
