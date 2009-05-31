// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SARR2ITER_HEADER
#define RAVL_SARR2ITER_HEADER 1
////////////////////////////////////////////////////////////
//! docentry="Ravl.API.Core.Arrays.2D"
//! rcsid="$Id$
//! file="Ravl/Core/Container/SArray/SArray2dIter.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="10/09/1998"
//! userlevel=Advanced

#include "Ravl/SArray2d.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/BufferAccess2dIter.hh"
#include "Ravl/Index2d.hh"

namespace RavlN {

  //! userlevel=Advanced
  //: SArray2dC iterator.
  // Simple 2d array iterator.
  
  template<class DataT>
  class SArray2dIterC 
  : public BufferAccess2dIterC<DataT>
  {
  public:
    SArray2dIterC()
    {}
    //: Default constructor.
    
    SArray2dIterC(const SArray2dC<DataT> &narr)
      : arr(narr)
    { First(); }
    //: Constructor.
    
    const SArray2dIterC<DataT> &operator=(SArray2dC<DataT> &narr) {
      arr = narr;
      First();
      return *this;
    }
    //: Assignment to an array.
    
    inline void First()
    { BufferAccess2dIterC<DataT>::First(arr.BufferAccess(),arr.ByteStride(),arr.Size1(),arr.Size2()); }
    //: Goto first element in array.
    
    IndexC RowIndex() const 
    { return arr.RowIndexOf(this->Data()); }
    //: Get index of current row.
    
    IndexC ColIndex() const 
    { return arr.ColIndexOf(this->Data()); }
    //: Compute curent column
    
    Index2dC Index() const 
    { return arr.IndexOf(this->Data()); }
    //: Compute index of current location.
    
  protected:
    SArray2dC<DataT> arr;
  };
  
  
}

#endif
