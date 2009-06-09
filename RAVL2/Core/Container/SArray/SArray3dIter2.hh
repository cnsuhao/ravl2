// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SARR3ITER2_HEADER
#define RAVL_SARR3ITER2_HEADER 1
////////////////////////////////////////////////////////////
//! docentry="Ravl.API.Core.Arrays.3D"
//! rcsid="$Id$
//! file="Ravl/Core/Container/SArray/SArray3dIter2.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="10/09/1998"
//! userlevel=Advanced

#include "Ravl/SArray3d.hh"
#include "Ravl/BufferAccess2dIter2.hh"

namespace RavlN {
  //! userlevel=Advanced
  //: Dual SArray3dC iterator.
  // Dual Simple 3d array iterator.
  
  template<class Data1T,class Data2T>
  class SArray3dIter2C 
    : public BufferAccess3dIter2C<Data1T,Data2T>
  {
  public:
    SArray3dIter2C()
    {}
    //: Default constructor.
    
    SArray3dIter2C(const SArray3dC<Data1T> &arr,const SArray3dC<Data2T> &narr2)
      : arr1(arr),
        arr2(narr2)
    { First(); }
    //: Constructor.
    
    inline bool First() 
    { return BufferAccess3dIter2C<Data1T,Data2T>::First(arr1.BufferAccess(),arr1.ByteStride1(),arr1.ByteStride2(),
                                                        arr2.BufferAccess(),arr2.ByteStride1(),arr2.ByteStride2(),
                                                        arr1.Size1(),arr1.Size2(),arr1.Size3()); }
    //: Goto first element in array.
    // returns true if there is one.
    
    Index3dC Index() const
    { return arr1.IndexOf(this->Data1()); }
    //: Get index of current location in array 1.
    // Has to be calculate, and so is slightly slow.
    
  private:
    SArray3dC<Data1T> arr1;
    SArray3dC<Data2T> arr2;
  };

  ////////////////////////////////////////////////////////////////
  
   
}
#endif
