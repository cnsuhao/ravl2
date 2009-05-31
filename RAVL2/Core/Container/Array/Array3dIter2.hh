// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ARRAY3ITER2_HEADER
#define RAVL_ARRAY3ITER2_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.API.Core.Arrays.3D"
//! file="Ravl/Core/Container/Array/Array3dIter2.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="24/08/99"
//! userlevel=Default

#include "Ravl/Array3d.hh"
#include "Ravl/BufferAccess3dIter2.hh"

namespace RavlN {
  //! userlevel=Normal
  //: dual Array3dC iterator.
  
  template<class Data1T,class Data2T>
  class Array3dIter2C 
    : public BufferAccess3dIter2C<Data1T,Data2T>
  {
  public:
    Array3dIter2C()
    {}
    //: Default constructor.
    
    Array3dIter2C(const Array3dC<Data1T> &arr1,const Array3dC<Data2T> &arr2,bool matching = true)
      : BufferAccess3dIter2C<Data1T,Data2T>(arr1,arr2,
                                            arr1.Range1(),arr1.Range2(),arr1.Range3()),
        dat1(arr1),
        dat2(arr2)
    { 
      if(matching) 
	RavlAssert(dat1.Range() == dat2.Range());
    }
    //: Constructor.
    
    Array3dIter2C(const Array3dC<Data1T> &arr1,const Array3dC<Data2T> &arr2,const IndexRange3dC &rect)
      : dat1(arr1,rect),
        dat2(arr2,rect)
    {
      First();
    }
    //: Constructor.
    
    inline bool First() 
    { return BufferAccess3dIter2C<Data1T,Data2T>::First(dat1.BufferAccess(),dat1.ByteStride1(),dat1.ByteStride2(),
                                                        dat2.BufferAccess(),dat2.ByteStride1(),dat2.ByteStride2(),
                                                        dat1.Range1(),dat1.Range2(),dat1.Range3()); }
    //: Goto first element in the array.
    // Return TRUE if there actually is one.
    
    Index3dC Index() const 
    { return dat1.IndexOf(this->Data1()); }
    //: Get index of current location in array 1.
    // Has to be calculate, and so is slightly slow.
    
  protected:
    Array3dC<Data1T> dat1;
    Array3dC<Data2T> dat2;
  };
}

#endif
