// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSARR2ITER3_HEADER
#define RAVLSARR2ITER3_HEADER 1
////////////////////////////////////////////////////////////
//! docentry="Ravl.Core.Arrays.2D"
//! rcsid="$Id$
//! file="Ravl/Core/Container/SArray/SArr2Iter3.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="10/09/98"
//! userlevel=Advanced

#include "Ravl/SArray2d.hh"

namespace RavlN {
  //! userlevel=Advanced
  //: Triple SArray2dC iterator.
  // Triple Simple 2d array iterator.
  
  template<class Data1T,class Data2T,class Data3T>
  class SArray2dIter3C 
    : public BufferAccess2dIter3C<Data1T,Data2T,Data3T>
  {
  public:
    SArray2dIter3C()
      {}
    //: Default constructor.
    
    SArray2dIter3C(const SArray2dC<Data1T> &arr,
		   const SArray2dC<Data2T> &narr2,
		   const SArray2dC<Data3T> &narr3)
      : arr1(arr),
      arr2(narr2),
      arr3(narr3)
      { First(); }
    //: Constructor.
    
    inline bool First() {
      return BufferAccess2dIter3C<Data1T,Data2T,Data3T>::First(arr1,arr1.Size2(),
							       arr2,arr2.Size2(),
							       arr3,arr3.Size2());
    }
    //: Goto first element in array.
    // returns true if there is a first element.
    
    Index2dC Index() const { 
      IndexC row = it1.Index();
      IndexC col = IntT(&(it2.Data1()) - (it1.Data1().ReferenceElm()));
      return Index2dC(row, col);
    } 
    //: Get current index.
    // This is a little slow.

  protected:    
    SArray2dC<Data1T> arr1;
    SArray2dC<Data2T> arr2;
    SArray2dC<Data3T> arr3;
  };
  
  ////////////////////////////////////////////////////////////////  
  
}

#endif
