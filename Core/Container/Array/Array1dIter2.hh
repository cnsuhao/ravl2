// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLARR1ITER2_HEADER
#define RAVLARR1ITER2_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Arrays.1D"
//! file="Ravl/Core/Container/Array/Array1dIter2.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="24/08/99"
//! userlevel=Default

#include "Ravl/Array1d.hh"
#include "Ravl/BfAccIter2.hh"

namespace RavlN {
  //! userlevel=Normal
  //: dual Array1dC iterator.
  
  template<class Data1T,class Data2T>
  class Array1dIter2C 
    : public BufferAccessIter2C<Data1T,Data2T>
  {
  public:
    Array1dIter2C()
      {}
    //: Default constructor.
    
    Array1dIter2C(const Array1dC<Data1T> &arr1,const Array1dC<Data2T> &arr2,bool matching = true)
      : BufferAccessIter2C<Data1T,Data2T>(arr1,arr2),
        dat1(arr1),
        dat2(arr2)
      {
	if(matching) 
	  RavlAssert(arr1.Range() == arr2.Range());
      }
    //: Constructor.
    // If you don't intend to iterator over the same range for each array set the 'matching' paramiter to 
    // false.  This will disable the check.
    
    Array1dIter2C(const Array1dC<Data1T> &arr1,const Array1dC<Data2T> &arr2,const IndexRangeC &rng)
      : dat1(arr1,rng),
        dat2(arr2,rng)
      { BufferAccessIter2C<Data1T,Data2T>::First(dat1,dat2); }
    //: Constructor.
    
    inline void First() 
      { BufferAccessIter2C<Data1T,Data2T>::First(dat1,dat2); }
    //: Goto first element in the array.
    
  protected:
    Array1dC<Data1T> dat1;
    Array1dC<Data2T> dat2;
  };
}

#endif
