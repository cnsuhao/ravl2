// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ARRAY2ITER6_HEADER
#define RAVL_ARRAY2ITER6_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Arrays.2D"
//! file="Ravl/Core/Container/Array/Array2dIter6.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="7/12/2002"
//! userlevel=Default

#include "Ravl/Array2d.hh"
#include "Ravl/BfAcc2Iter6.hh"

namespace RavlN {
  //! userlevel=Normal
  //: Array2dC iterator for 6 arrays.
  // This will iterate through six rectangles of the same size.  The rectangles need not
  // have the same origin.  
  // The first array controls the number of elements visited.
  
  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class Data6T>
  class Array2dIter6C 
    : public BufferAccess2dIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T>
  {
  public:
    Array2dIter6C()
    {}
    //: Default constructor.
    
    Array2dIter6C(const Array2dC<Data1T> &arr1,
		  const Array2dC<Data2T> &arr2,
		  const Array2dC<Data3T> &arr3,
		  const Array2dC<Data4T> &arr4,
		  const Array2dC<Data5T> &arr5,
		  const Array2dC<Data6T> &arr6,
		  bool matching = true)
      : BufferAccess2dIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T>(arr1,arr1.Range2(),
									arr2,arr2.Range2(),
									arr3,arr3.Range2(),
									arr4,arr4.Range2(),
									arr5,arr5.Range2(),
									arr6,arr6.Range2()
									),
        dat1(arr1),
        dat2(arr2),
        dat3(arr3),
        dat4(arr4),
        dat5(arr5),
        dat6(arr6)
    { 
      if(matching) {
	RavlAssert(dat1.Range().Size() == dat2.Range().Size());
	RavlAssert(dat1.Range().Size() == dat3.Range().Size());
	RavlAssert(dat1.Range().Size() == dat4.Range().Size());
	RavlAssert(dat1.Range().Size() == dat5.Range().Size());
	RavlAssert(dat1.Range().Size() == dat6.Range().Size());
      } else {
	RavlAssertMsg(dat1.Range().Rows() <= dat2.Range().Rows(),"Array2dIter3C, Second array is has fewer rows than the first. ");
	RavlAssertMsg(dat1.Range().Cols() <= dat2.Range().Cols(),"Array2dIter3C, Second array is has fewer cols than the first. ");
	RavlAssertMsg(dat1.Range().Rows() <= dat3.Range().Rows(),"Array2dIter3C, Third array is has fewer rows than the first. ");
	RavlAssertMsg(dat1.Range().Cols() <= dat3.Range().Cols(),"Array2dIter3C, Third array is has fewer cols than the first. ");
	RavlAssertMsg(dat1.Range().Rows() <= dat4.Range().Rows(),"Array2dIter3C, Fourth array is has fewer rows than the first. ");
	RavlAssertMsg(dat1.Range().Cols() <= dat4.Range().Cols(),"Array2dIter3C, Fourth array is has fewer cols than the first. ");
	RavlAssertMsg(dat1.Range().Rows() <= dat5.Range().Rows(),"Array2dIter3C, Fifth array is has fewer rows than the first. ");
	RavlAssertMsg(dat1.Range().Cols() <= dat5.Range().Cols(),"Array2dIter3C, Fifth array is has fewer cols than the first. ");
	RavlAssertMsg(dat1.Range().Rows() <= dat6.Range().Rows(),"Array2dIter3C, Sixth array is has fewer rows than the first. ");
	RavlAssertMsg(dat1.Range().Cols() <= dat6.Range().Cols(),"Array2dIter3C, Sixth array is has fewer cols than the first. ");
      }
      First();
    }
    //: Constructor.
    // If 'matching' is true, the rectangles must be of the same size. <br>
    // If 'matching' is set to false the size of the rectangle is set to that of the first array, 'arr1'
    // arr1 MUST have a size equal to or smaller than arr2 and arr3 in both dimensions.
    
    Array2dIter6C(const Array2dC<Data1T> &arr1,
		  const Array2dC<Data2T> &arr2,
		  const Array2dC<Data3T> &arr3,
		  const Array2dC<Data4T> &arr4,
		  const Array2dC<Data5T> &arr5,
		  const Array2dC<Data6T> &arr6,
		  const IndexRange2dC &rect)
      : dat1(arr1,rect),
        dat2(arr2,rect),
        dat3(arr3,rect),
        dat4(arr4,rect),
        dat5(arr5,rect),
        dat6(arr6,rect)
    { BufferAccess2dIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T>::First(dat1,dat1.Range2(),
								      dat2,dat2.Range2(),
								      dat3,dat3.Range2(),
								      dat4,dat4.Range2(),
								      dat5,dat5.Range2(),
								      dat6,dat6.Range2()
								      );
    }
    //: Constructor.
    // Iterate through 'rect' in all arrays. 'rect' must be within both arr1, arr2 and arr3.

    Array2dIter6C(const Array2dC<Data1T> &arr1,const IndexRange2dC &irng1,
		  const Array2dC<Data2T> &arr2,const IndexRange2dC &irng2,
		  const Array2dC<Data3T> &arr3,const IndexRange2dC &irng3,
		  const Array2dC<Data4T> &arr4,const IndexRange2dC &irng4,
		  const Array2dC<Data5T> &arr5,const IndexRange2dC &irng5,
		  const Array2dC<Data6T> &arr6,const IndexRange2dC &irng6)
      : dat1(arr1,irng1),
        dat2(arr2,irng2),
        dat3(arr3,irng3),
        dat4(arr4,irng4),
        dat5(arr5,irng5),
        dat6(arr6,irng6)
    { BufferAccess2dIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T>::First(dat1,dat1.Range2(),
									     dat2,dat2.Range2(),
									     dat3,dat3.Range2(),
									     dat4,dat4.Range2(),
									     dat5,dat5.Range2(),
									     dat6,dat6.Range2());
    }
    //: Constructor.
    // Iterate through indicated sub range in all arrays. irng1 should have the same or smaller
    // overall size than the rest of the ranges
    
    
    inline bool First() {
      return BufferAccess2dIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T>::First(dat1,dat1.Range2(),
										    dat2,dat2.Range2(),
										    dat3,dat3.Range2(),
										    dat4,dat4.Range2(),
										    dat5,dat5.Range2(),
										    dat6,dat6.Range2()
										    );
    }
    //: Goto first element in the array.
    // Return TRUE if there actually is one.
    
    Index2dC Index() const { 
      RavlAssert(dat1.IsValid());
      return Index2dC((IntT) (&(rit.Data1()) - dat1.ReferenceElm()),
		      (IntT) (&(cit.Data1()) - rit.Data1().ReferenceElm())); 
    }
    //: Get index of current location.
    // Has to be calculate, and so is slightly slow.
        
  protected:
    Array2dC<Data1T> dat1;
    Array2dC<Data2T> dat2;
    Array2dC<Data3T> dat3;
    Array2dC<Data4T> dat4;
    Array2dC<Data5T> dat5;
    Array2dC<Data6T> dat6;
  };
}
#endif
