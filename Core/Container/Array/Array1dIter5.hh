// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ARRAY1ITER5_HEADER
#define RAVL_ARRAY1ITER5_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Arrays.1D"
//! file="Ravl/Core/Container/Array/Array1dIter5.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="07/12/2002"
//! userlevel=Default

#include "Ravl/Array1d.hh"
#include "Ravl/BfAccIter5.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: triple Array1dC iterator.
  // Note, the first array in the triple controls the number of elements visited.
  
  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T>
  class Array1dIter5C 
    : public BufferAccessIter5C<Data1T,Data2T,Data3T,Data4T,Data5T>
  {
  public:
    Array1dIter5C()
    {}
    //: Default constructor.
    
    Array1dIter5C(const Array1dC<Data1T> &arr1,const Array1dC<Data2T> &arr2,
		  const Array1dC<Data3T> &arr3,const Array1dC<Data4T> &arr4,
		  const Array1dC<Data5T> &arr5,bool matching = true)
      : BufferAccessIter5C<Data1T,Data2T,Data3T,Data4T,Data5T>(arr1,arr2,arr3,arr4,arr5),
	dat1(arr1),
	dat2(arr2),
	dat3(arr3),
	dat4(arr4),
	dat5(arr5)
    {
      if(matching) {
	RavlAssertMsg(arr1.Range() == arr2.Range(),"Array1dIter5C, First and second array ranges don't match.");
	RavlAssertMsg(arr1.Range() == arr3.Range(),"Array1dIter5C, First and third array ranges don't match.");
	RavlAssertMsg(arr1.Range() == arr4.Range(),"Array1dIter5C, First and fourth array ranges don't match.");
	RavlAssertMsg(arr1.Range() == arr5.Range(),"Array1dIter5C, First and fifth array ranges don't match.");
      }
    }
    //: Constructor.
    // If you don't intend to iterator over the same range for each array set the 'matching' paramiter to 
    // false.  This will disable the check.
    
    Array1dIter5C(const Array1dC<Data1T> &arr1,const Array1dC<Data2T> &arr2,
		  const Array1dC<Data3T> &arr3,const Array1dC<Data4T> &arr4,
		  const Array1dC<Data5T> &arr5,const IndexRangeC &rng)
      : BufferAccessIter5C<Data1T,Data2T,Data3T,Data4T,Data5T>(arr1,arr2,arr3,arr4,arr5),
	dat1(arr1,rng),
	dat2(arr2,rng),
	dat3(arr3,rng),
	dat4(arr4,rng),
	dat5(arr5,rng)
    {}
    //: Constructor.
    
    inline void First() 
    { BufferAccessIter5C<Data1T,Data2T,Data3T,Data4T,Data5T>::First(dat1,dat2,dat3,dat4,dat5); }
    //: Goto first element in the array.
    
    bool IsFirst() const
    { return at1 == &dat1[dat1.IMin()]; }
    //: Test if this is the first element in the range.
    // Note,this is slower than IsElm().
    
  protected:
    Array1dC<Data1T> dat1;
    Array1dC<Data2T> dat2;
    Array1dC<Data3T> dat3;
    Array1dC<Data4T> dat4;
    Array1dC<Data5T> dat5;
  };
  
}
#endif
