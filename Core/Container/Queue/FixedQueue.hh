// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FIXQUEUE_HEADER
#define RAVL_FIXQUEUE_HEADER 1
//////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Queue/FixedQueue.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"
//! date="6/6/1997"
//! docentry="Ravl.Core.Queues"
//! rcsid="$Id$"

#include "Ravl/SArray1d.hh"
#include "Ravl/Assert.hh"

namespace RavlN {
  template<class T> class FixedQueueIterC;
  template<class T> class FixedQueueRevIterC;
  
  //! userlevel=Normal
  //: Fixed size circular queue.
  // A SMALL object.
  // This is sometimes known as a ring buffer.
  // FIXME :- Make FixedQueueC big. <p>
  // Note, this does not destroy items removed from
  // the queue until the element is overwritten by another.
  
  template<class T>
  class FixedQueueC 
    : protected SArray1dC<T> 
  {
  public:
    explicit inline FixedQueueC(SizeT Size);
    //: Constructor.
    
    inline bool IsSpace();
    //: Is space to data into ring ?
    
    inline void InsLast(const T &Obj);
    //: Insert data at end of queue.
    // returns the place its index in the array.
    
    inline void ForceInsLast(const T &Obj);
    //: Insert data at end of queue, if no space discard oldest element.
    // returns the place its index in the array.
    
    inline bool IsEmpty() const 
    { return head == tail; }
    //: Is ring empty ?
    
    inline T GetFirst();
    //: Get first item from queue.

    inline const T &First() const { 
      RavlAssert(!IsEmpty());
      return *tail; 
    }
    //: Access first the first element in the queue.

    inline T &First() { 
      RavlAssert(!IsEmpty());
      return *tail; 
    }
    //: Access first the first element in the queue.
    
    inline T &Last() { 
      RavlAssert(!IsEmpty());
      T *l = head - 1;
      if(l < &(*this)[0])
	l = eoa-1;
      return *l; 
    }
    //: Look at the item most recently placed in the queue.

    inline const T &Last() const { 
      RavlAssert(!IsEmpty());
      T *l = head - 1;
      if(l < &(*this)[0])
	l = eoa-1;
      return *l; 
    }
    //: Look at the item most recently placed in the queue.
    
    inline void DelFirst();
    //: Delete first item in buffer 
    
    inline SizeT Size() const;
    //: No of items in the ring.

    inline SizeT MaxSize() const
    { return SArray1dC<T>::Size()-1; }
    //: Get maximum size of queue.
    
    inline bool IsInRing(UIntT P) const;
    //: Is P an index in the ring.
    
    inline void Empty();
    //: Empty the queue of all contents. 
    // Reset to head=0, tail=0
    
  protected:
    T *head; // Next free location.
    T *tail; // Last used location.
    T *eoa;  // Ptr to end of array.

    friend class FixedQueueIterC<T>;
    friend class FixedQueueRevIterC<T>;
  };
  
  //! userlevel=Normal
  //: Iterate through contents of the queue.
  // This goes from the oldest element in the list to the latest. <p>
  
  template<class T>
  class FixedQueueIterC
    : public SArray1dC<T>
  {
  public:
    FixedQueueIterC()
      : at(0),
	end(0)
    {}
    //: Default constructor.
    
    FixedQueueIterC(FixedQueueC<T> &queue)
      : SArray1dC<T>(queue)
    { First(queue); }
    //: Constructor from a queue.
    // Note: Chaning the queue after the iterator is contructed
    // will not affect the indexs iterated, though the data will
    // change.
    
    void First(FixedQueueC<T> &queue) {
      SArray1dC<T>::operator=(queue);
      at = queue.tail;
      end = queue.head;
      eoa = queue.eoa;
    }
    //: Goto first element in queue.
    
    const FixedQueueIterC<T> &operator=(FixedQueueC<T> &queue) {
      First(queue);
      return *this;
    }
    //: Assign to a queue.
    
    bool IsElm() const
    { return at != end; }
    //: At valid element ?
    
    operator bool() const
    { return at != end; }
    //: At a valid element ?
    
    void Next() {
      at++;
      if(at == eoa)
	at = &(*this)[0];
    }
    //: Goto next element.
    
    void operator++(int)
    { Next(); }
    //: Goto next element.
    
    void operator++()
    { Next(); }
    //: Goto next element.
    
    T &Data() 
    { return *at; }
    //: Access data.
    
    const T &Data() const
    { return *at; }
    //: Access data.
    
    T &operator*()
    { return *at; }
    //: Access data.

    const T &operator*() const
    { return *at; }
    //: Access data.
    
    T *operator->()
    { return at; }
    //: Access data.

    const T *operator->() const
    { return at; }
    //: Access data.
    
  protected:
    T *at;
    T *end;
    T *eoa;
  };

  //-----------------------------------------------------
  //! userlevel=Normal
  //: Iterate through contents of the queue.
  // This goes from the latest element in the list to the oldest.
  
  template<class T>
  class FixedQueueRevIterC
    : public SArray1dC<T>
  {
  public:
    FixedQueueRevIterC()
      : at(0),
	end(0)
    {}
    //: Default constructor.
    
    FixedQueueRevIterC(FixedQueueC<T> &queue)
      : SArray1dC<T>(queue)
    { First(queue); }
    //: Constructor from a queue.
    // Note: Chaning the queue after the iterator is contructed
    // will not affect the indexs iterated, though the data will
    // change.
    
    void First(FixedQueueC<T> &queue) {
      SArray1dC<T>::operator=(queue);
      at = queue.head;
      end = queue.tail -1;
      eoa = &((*this)[0]) - 1;
      if(end == eoa)
	end = &(*this)[this->Size()-1]; 
      Next();
    }
    //: Goto first element in queue.
    
    const FixedQueueIterC<T> &operator=(FixedQueueC<T> &queue) {
      First(queue);
      return *this;
    }
    //: Assign to a queue.
    
    bool IsElm() const
    { return at != end; }
    //: At valid element ?
    
    operator bool() const
    { return at != end; }
    //: At a valid element ?
    
    void Next() {
      at--;
      if(at == eoa)
	at = &(*this)[this->Size()-1];
    }
    //: Goto next element.
    
    void operator++(int)
    { Next(); }
    //: Goto next element.
    
    void operator++()
    { Next(); }
    //: Goto next element.
    
    T &Data() 
    { return *at; }
    //: Access data.
    
    const T &Data() const
    { return *at; }
    //: Access data.
    
    T &operator*()
    { return *at; }
    //: Access data.

    const T &operator*() const
    { return *at; }
    //: Access data.
    
    T *operator->()
    { return at; }
    //: Access data.

    const T *operator->() const
    { return at; }
    //: Access data.
    
  protected:
    T *at;
    T *end;
    T *eoa;
  };
  
  //-----------------------------------------------------
  
  template<class T>
  inline
  FixedQueueC<T>::FixedQueueC(SizeT Size) 
    : SArray1dC<T>(Size+1)  // Cause we always need space for 1 more item.
  { 
    head = &((*this)[0]);
    tail = head;
    eoa = &(head[SArray1dC<T>::Size()]);
  }
  
  template<class T>
  inline 
  bool FixedQueueC<T>::IsSpace()  {
    T *nhead = head + 1;
    if(nhead >= eoa)
      nhead = &(*this)[0];
    return (nhead != tail);
  }
  
  template<class T>
  inline 
  void FixedQueueC<T>::InsLast(const T &Obj)  {
    RavlAssert(IsSpace());
    *(head++) = Obj;
    if(head >= eoa)
      head = &(*this)[0];
  }
  
  template<class T>
  inline 
  void FixedQueueC<T>::ForceInsLast(const T &Obj) {
    *(head++) = Obj;
    if(head >= eoa)
      head = &((*this)[0]);
    if(head == tail) { // Need to push tail ?
      if(++tail >= eoa)
	tail = &((*this)[0]);
    }
  }
  
  
  template<class T>
  inline 
  T FixedQueueC<T>::GetFirst() {
    RavlAssert(!IsEmpty());
    T Ret = *(tail++);
    if(tail >= eoa)
      tail = &((*this)[0]);
    return Ret;
  }
  
  template<class T>
  inline 
  void  FixedQueueC<T>::DelFirst()  {
    RavlAssert(!IsEmpty());
    if(++tail >= eoa)
      tail = &((*this)[0]);
  }

  template<class T>
  inline 
  SizeT FixedQueueC<T>::Size() const {
    if(head >= tail)
      return (SizeT) (head - tail);
    return (SizeT) ((eoa - tail) + (head - &((*this)[0])));
  }
  
  template<class T>
  inline 
  bool FixedQueueC<T>::IsInRing(UIntT at) const  {
    if(IsEmpty())
      return false;
    const T *p = &((*this)[at]);
    if(head > tail)
      return (p >= tail && p < head);
    return (p >= tail || p < head);
  }
  
  template<class T>
  inline 
  void FixedQueueC<T>::Empty() {
    tail = &((*this)[0]);
    head = tail;
  }
}


#endif
