// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef PRIQUEUE_HEADER
#define PRIQUEUE_HEADER 1
////////////////////////////////////////////////
//! userlevel=Normal
//! example=TPriQH.cc
//! docentry="Ravl.Core.Queues"
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Queue/PriQueue.hh"
//! author="Charles Galambos"
//! date="24/08/98"
//! lib=RavlCore

#include "Ravl/SDArray1d.hh"
#include "Ravl/RCWrap.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/Assert.hh"

namespace RavlN {
  //: Array based priority queue.
  // BIG OBJECT <p>
  // Keys must have operation '<' defined.
  // This queue assumes: **** Small numbers == High priority. ****
  
  template <class K,class D>
  class PriQueueC {
  public:
    PriQueueC(UIntT initSize = 32);
    //: Default constructor.
    
    PriQueueC(const PriQueueC<K,D> &body);
    //: Copy constructor.
    
    bool IsElm(void) const
      { return Array().Size() > 0; }
    //: Does the queue contains any items ?
    
    bool IsEmpty(void) const
      { return Array().Size() == 0; }
    //: Is the queue empty ?
    
    D &Top(void);
    //: Look/Modify data on top of queue.
    // Refrence not garanteed to stay valid
    // after any insert/delete operation !
    
    const D &Top(void) const;
    //: Look at data on top of queue.
    // Refrence not garanteed to stay valid
    // after any insert/delete operation !
    
    const K &TopKey(void) const;
    //: Look at key on top of queue.
    // Refrence not garanteed to stay valid
    // after any insert/delete operation !
    
    void DelTop(void);
    //: Delete item on top of queue.
    // NB. IsElm(), must be true before calling this.
    
    Tuple2C<K,D> GetTopPair(void);
    //: Get Key/Data pair from queue.
    
    D GetTop(void);
    //: Get Data from top of queue.
    
    void Insert(const K &Key,const D &Data)
      { Insert(Tuple2C<K,D>(Key,Data)); }
    //: Insert Data/Key into queue.
    
    void Insert(const Tuple2C<K,D> &dat);
    //: Insert Data/Key into queue.
    
    bool Remove(const Tuple2C<K,D> &New)
      { return false; }
    //: Remove all instances of Key from queue.
    //!bug: NOT IMPLEMENTED
    // Returns True if found.
    
    bool Remove(const K &Key)
      { return false; }
    //: Remove all instances of Key from queue.
    //!bug: NOT IMPLEMENTED
    // Returns True if found.
    
    UIntT Size(void) const 
      { return Array().Size(); }
    //: Get number of items in queue.
    
    void Empty(void)
      { Array().Empty(); }
    //: Empty the queue of all its contents.
    
    bool Check();
    //: Check consistancy.
  protected:
    RCWrapC<SDArray1dC<Tuple2C<K,D> > > data;
    
    SDArray1dC<Tuple2C<K,D> > &Array() 
      { return data.Data(); }
    
    const SDArray1dC<Tuple2C<K,D> > &Array() const 
      { return data.Data(); }
  };
  
  //////////////////////////////////////////
  
  template <class K,class D>
  PriQueueC<K,D>::PriQueueC(UIntT initSize)
    : data(SDArray1dC<Tuple2C<K,D> >(initSize))
  {}
  
  template <class K,class D>
  PriQueueC<K,D>::PriQueueC(const PriQueueC<K,D> &body)
    : data(body.data)
  {}
    
  template <class K,class D>
  D &PriQueueC<K,D>::Top(void) {
    RavlAssert(IsElm());
    return Array()[0].Data2();
  }
  
  template <class K,class D>
  const D &
  PriQueueC<K,D>::Top(void) const {
    RavlAssert(IsElm());
    return Array()[0].Data2();
  }
  
  template <class K,class D>
  const K &
  PriQueueC<K,D>::TopKey(void) const {
    RavlAssert(IsElm());
    return Array()[0].Data1();
  }
  
  template <class K,class D>
  void PriQueueC<K,D>::DelTop(void) {
    SDArray1dC<Tuple2C<K,D> > &arr = Array();
    UIntT child;
    const UIntT tsize = arr.Size() - 1;
    if(tsize == 0) {
      arr.Chop();
      return ;
    }
    Tuple2C<K,D> lastelem = arr[tsize];
    UIntT i;
    for(i = 1;i * 2 <= tsize;i = child+1) {
      child = (i * 2) - 1;
      if((child != tsize) && arr[child+1].Data1() < arr[child].Data1())
	child++;
      if(arr[child].Data1() < lastelem.Data1())
	arr[i-1] = arr[child];
      else
	break;
    }
    arr[i-1] = lastelem;
    arr.Chop();
  }
  
  template <class K,class D>
  Tuple2C<K,D> PriQueueC<K,D>::GetTopPair(void) {
    Tuple2C<K,D> ret = Array()[0];
    DelTop();
    return ret;
  }
  
  template <class K,class D>
  D PriQueueC<K,D>::GetTop(void)  {
    D ret = Array()[0].Data2();
    DelTop();
    return ret;
  }
  
  template <class K,class D>
  void PriQueueC<K,D>::Insert(const Tuple2C<K,D> &dat) {
    SDArray1dC<Tuple2C<K,D> > &arr = Array();
    UIntT i;
    i = arr.Size() + 1;
    if(i == 1) { // First in queue ?
      arr.Add(dat);
      return ;
    }
    // Need do any shifting at all ?
    if(arr[i/2-1].Data1() < dat.Data1()) {
      arr.Add(dat); // No, just add on end.
      return ;
    }
    i /= 2;
    Tuple2C<K,D> tmp(arr[i-1]); 
    // Have to use tempory here as array may be resized and the
    // refrence returned from arr[] may be invalid.
    arr.Add(tmp); // Move up.
    for(;(i > 1) && dat.Data1() < arr[i/2-1].Data1();i /= 2)
      arr[i-1] = arr[i/2-1];
    arr[i-1] = dat;
  }
  
  template <class K,class D>
  bool PriQueueC<K,D>::Check() {
    SDArray1dC<Tuple2C<K,D> > &arr = Array();
    for(UIntT i = 1;i < Size();i++) {
      RavlAssert(arr[((i+1)/2)-1].Data1() < arr[i].Data1());
    }
    return true;
  }
}

#endif

