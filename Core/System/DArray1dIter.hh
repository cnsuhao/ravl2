// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DARRAY1DITER_HEADER
#define RAVL_DARRAY1DITER_HEADER 1
//! docentry="Ravl.Core.Misc"
//! lib=RavlCore
//! author="Charles Galambos"
//! rcsid="$Id$"
//! file="Ravl/Core/System/DArray1dIter.hh"

#include "Ravl/DArray1d.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Dynamic array iterator.
  
  template<class DataT>
  class DArray1dIterC {
  public:
    DArray1dIterC()
    {}
    //: Default constructor.

    DArray1dIterC(const DArray1dC<DataT> &narr)
      : arr(narr)
    { First(); }
    //: Constructor.
    
    void First() {
      cit = arr.Body().chunks;
      if(!cit)
	return ;
      it.First(cit->Data()); 
    }
    //: Goto first element in the array.
    
    const DArray1dIterC<DataT> &operator=(const DArray1dC<DataT> &narr) {
      arr = narr;
      First();
      return *this;
    }
    //: Assign to array.
    // Leave iterator at first element in list.
    
    bool IsElm() const
    { return it.IsElm(); }
    //: At a valid element ?
    
    operator bool() const
    { return it.IsElm(); }
    //: At a valid element ?

    DataT &Data()
    { return it.Data(); }
    //: Access data.
    
    const DataT &Data() const
    { return it.Data(); }
    //: Access data.
    
    DataT &operator*() 
    { return it.Data(); }
    //: Access data.

    const DataT &operator*() const
    { return it.Data(); }
    //: Access data.

    DataT *operator->() 
    { return &it.Data(); }
    //: Access data.

    const DataT *operator->() const
    { return &it.Data(); }
    //: Access data.
    
    void Next() {
      it++;
      if(it) return ;
      cit++;
      if(!cit) return ;
      it.First(cit->Data()); 
    }
    //: Goto next element.
    
    void operator++(int)
    { Next(); }
    //: Goto next element.
    
    IndexC Index() 
    { return IndexC((IntT)( &(*it) - cit.Data().Data().ReferenceElm())); }
    //: Get index of current element.
    
    void Invalidate()
    { it.Invalidate(); }
    //: Invalidate iterator.
    
  protected:
    DArray1dC<DataT> arr;
    BufferAccessIterC<DataT> it;
    IntrDLIterC<DChunkC<DataT> > cit;
  };
    

}


#endif
