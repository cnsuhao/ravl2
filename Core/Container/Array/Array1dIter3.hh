// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLARR1ITER3_HEADER
#define RAVLARR1ITER3_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Arrays.1D"
//! file="Ravl/Core/Container/Array/Array1dIter3.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="24/08/99"
//! userlevel=Default

#include "Ravl/Array1d.hh"
#include "Ravl/BfAccIter3.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: triple Array1dC iterator.
  
  template<class Data1T,class Data2T,class Data3T>
  class Array1dIter3C 
    : public BufferAccessIter3C<Data1T,Data2T,Data3T>
  {
  public:
    Array1dIter3C()
      {}
    //: Default constructor.
    
    Array1dIter3C(const Array1dC<Data1T> &arr1,const Array1dC<Data2T> &arr2,const Array1dC<Data3T> &arr3,bool matching = true)
      : BufferAccessIter3C<Data1T,Data2T,Data3T>(arr1,arr2,arr3),
      dat1(arr1),
      dat2(arr2),
      dat3(arr3)
      {
	if(matching) {
	  RavlAssert(arr1.Range() == arr2.Range());
	  RavlAssert(arr1.Range() == arr3.Range());
	}
      }
    //: Constructor.

    Array1dIter3C(const Array1dC<Data1T> &arr1,const Array1dC<Data2T> &arr2,const Array1dC<Data3T> &arr3,const IndexRangeC &rng)
      : BufferAccessIter3C<Data1T,Data2T,Data3T>(arr1,arr2,arr3),
      dat1(arr1,rng),
      dat2(arr2,rng),
      dat3(arr3,rng)
      {}
    //: Constructor.
    
    
    inline void First() 
      { BufferAccessIter3C<Data1T,Data2T,Data3T>::First(dat1,rng1,dat2,rng2,dat3,rng3); }
    //: Goto first element in the array.
    
  protected:
    Array1dC<Data1T> dat1;
    Array1dC<Data2T> dat2;
    Array1dC<Data3T> dat3;
  };
  
}
#endif
