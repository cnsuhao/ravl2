// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ARRAY2DSQR51ITER2_HEADER
#define RAVL_ARRAY2DSQR51ITER2_HEADER 1
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.API.Core.Arrays.2D"
//! author="Charles Galambos"
//! lib=RavlCore
//! file="Ravl/Core/Container/Array/Array2dSqr51Iter2.hh"

#include "Ravl/Array2d.hh"
#include "Ravl/BufferAccess2dIter2.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Iterate through an array accessing 5x5 area, 1 pixel in a second array.
  
  template<class Data1T,class Data2T>
  class Array2dSqr51Iter2C 
    : protected BufferAccess2dIter2C<Data1T,Data2T>
  {
  public:
    Array2dSqr51Iter2C()
    {}
    //: Default constructor.
    
    Array2dSqr51Iter2C(const Array2dC<Data1T> &narray1,const Array2dC<Data2T> &narray2) 
      : array1(narray1),
	array2(narray2)
    { First(); }
    //: Constructor.
    
    bool First() {
      IndexRange2dC frame1 = array1.Frame().Expand(-2);
      RavlAssert(array2.Frame().Contains(frame1));
      if(!BufferAccess2dIter2C<Data1T,Data2T>::First(array1.BufferAccess(),array1.ByteStride(),frame1,
                                                     array2.BufferAccess(),array2.ByteStride(),frame1
                                                     ))
        return false;
      up2 = ShiftPointerInBytes(&(this->Data1()),-2 * array1.ByteStride());
      up1 = ShiftPointerInBytes(&(this->Data1()),-array1.ByteStride());
      dn1 = ShiftPointerInBytes(&(this->Data1()),array1.ByteStride());
      dn2 = ShiftPointerInBytes(&(this->Data1()),2 * array1.ByteStride());
      return true;
    }
    //: Goto first element in the array.
    
    bool Next() {
      if(!BufferAccess2dIter2C<Data1T,Data2T>::Next()) {
        up2 = ShiftPointerInBytes(&(this->Data1()),-2 * array1.ByteStride());
        up1 = ShiftPointerInBytes(&(this->Data1()),-array1.ByteStride());
        dn1 = ShiftPointerInBytes(&(this->Data1()),array1.ByteStride());
        dn2 = ShiftPointerInBytes(&(this->Data1()),2 * array1.ByteStride());
        return false;
      }
      up2++;
      up1++;
      dn1++;
      dn2++;
      return false;
    }
    //: Goto next element.
    
    bool IsElm() const
    { return this->m_cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    operator bool() const
    { return this->m_cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    void operator++() 
    { Next(); }
    //: Goto next element.
    
    void operator++(int) 
    { Next(); }
    //: Goto next element.
    
    Data1T *DataU2() 
    { return up2; }
    //: Access upper row
    // Use with [] operator. Only use index's from -2 to 2.

    const Data1T *DataU2() const
    { return up2; }
    //: Access upper row
    // Use with [] operator. Only use index's from -2 to 2.
    
    Data1T *DataU1() 
    { return up1; }
    //: Access upper row
    // Use with [] operator. Only use index's from -2 to 2.

    const Data1T *DataU1() const
    { return up1; }
    //: Access upper row
    // Use with [] operator. Only use index's from -2 to 2.

    Data1T *DataM0() 
    { return &this->Data1(); }
    //: Access middle row
    // Use with [] operator. Only use index's from -2 to 2.

    const Data1T *DataM0() const
    { return &this->Data1(); }
    //: Access middle row
    // Use with [] operator. Only use index's from -2 to 2.
    
    Data1T *DataD1() 
    { return dn1; }
    //: Access lower row
    // Use with [] operator. Only use index's from -2 to 2.

    const Data1T *DataD1() const
    { return dn1; }
    //: Access lower row
    // Use with [] operator. Only use index's from -2 to 2.
    
    Data1T *DataD2() 
    { return dn2; }
    //: Access lowest row
    // Use with [] operator. Only use index's from -2 to 2.

    const Data1T *DataD2() const
    { return dn2; }
    //: Access lowest row
    // Use with [] operator. Only use index's from -2 to 2.
    
    Data2T &Data2() 
    { return this->m_cit.Data2(); }
    //: Access data from second array.

    const Data2T &Data2() const
    { return this->m_cit.Data2(); }
    //: Access data from second array.
    
    Index2dC Index() const
    { return array1.IndexOf(this->DataM0()[0]); }
    //: Get index of current location of the middle pixel in the first array.
    // Has to be calculate, and so is slightly slow.

  protected:
    Array2dC<Data1T> array1;
    Array2dC<Data2T> array2;
    Data1T *up2;
    Data1T *up1;
    Data1T *dn1;
    Data1T *dn2;
  };
}



#endif
