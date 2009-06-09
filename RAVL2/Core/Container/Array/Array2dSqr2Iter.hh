// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ARRAY2DSQR2ITER_HEADER
#define RAVL_ARRAY2DSQR2ITER_HEADER 1
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.API.Core.Arrays.2D"
//! author="Charles Galambos"
//! lib=RavlCore
//! file="Ravl/Core/Container/Array/Array2dSqr2Iter.hh"

#include "Ravl/Array2d.hh"
#include "Ravl/BufferAccess2dIter.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Iterator which slides a 2x2 window over an array.
  // The square can be accessed with DataBL,DataBR,DataUL and DataUR
  // which access the following array elements. <p>
  //  TL TR <br>
  //  BL BR <br>
  
  template<class DataT>
  class Array2dSqr2IterC 
    : protected BufferAccess2dIterC<DataT>
  {
  public:
    Array2dSqr2IterC()
    {}
    //: Default constructor.
    
    Array2dSqr2IterC(const Array2dC<DataT> &narray) 
      : array(narray)
    { 
      First(); 
    }
    //: Constructor.
    
    bool First() {
      IndexRangeC nrng1a(array.Range1().Min()+1,array.Range1().Max());
      IndexRangeC nrng2a(array.Range2().Min()+1,array.Range2().Max());
      RavlAssert(nrng1a.Min() <= nrng1a.Max());
      RavlAssert(nrng2a.Min() <= nrng2a.Max());
      if(!BufferAccess2dIterC<DataT>::First(array.BufferAccess(),array.ByteStride(),nrng1a,nrng1a))
	return false;
      up = ShiftPointerInBytes(&(this->Data()),-array.ByteStride());
      return true;
    }
    //: Goto first element in the array.
    
    bool NextRow() {
      if(!BufferAccess2dIterC<DataT>::NextRow())
        return false;
      up = ShiftPointerInBytes(&this->Data(),-array.ByteStride());
      return true;
    }
    //: Goto next row.
    
    bool SkipRow(int n) {
      if(!BufferAccess2dIterC<DataT>::SkipRow(n))
        return false;
      up = ShiftPointerInBytes(&this->Data(),-array.ByteStride());
      return true;
    }
    //: Skip forward n rows.
    
    bool Next() {
      if(!BufferAccess2dIterC<DataT>::Next()) {
        up = ShiftPointerInBytes(&(this->Data()),-array.ByteStride());
        return false;
      }
      up++;
      return true;
   }
    //: Goto next element.
    // Returns true if its on the same row.

    bool Next(int n) { 
      up += n;
      this->m_cit += n;
      if(this->m_cit)
	return true;
      SkipRow(n);
      return false;
    }
    //: Goto next element.
    // Returns true if its on the same row.
    
    void NextCol(int n) { 
      up += n;
      this->m_cit += n;
    }
    //: Goto next column
    // This will NOT automaticly go to the next row.
    // Returns true if is a valid element.
    
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
    
    DataT &operator*() 
    { return *this->m_cit; }
    //: Access bottom right data element 
    
    const DataT &operator*() const
    { return *this->m_cit; }
    //: Access bottom right data element 
    
    DataT &DataBR() 
    { return *this->m_cit; }
    //: Access bottom right data element 

    const DataT &DataBR() const
    { return *this->m_cit; }
    //: Access bottom right data element 

    DataT &DataBL() 
    { return (&(*this->m_cit))[-1]; }
    //: Access bottom left data element 

    const DataT &DataBL() const
    { return (&(*this->m_cit))[-1]; }
    //: Access bottom left data element 
    
    DataT &DataTR() 
    { return *up; }
    //: Access upper right data element 
    
    const DataT &DataTR() const
    { return *up; }
    //: Access upper right data element
    
    DataT &DataTL() 
    { return up[-1]; }
    //: Access upper left data element.
    
    const DataT &DataTL() const
    { return up[-1]; }
    //: Access upper left data element
    
    Index2dC Index() const
    { return array.IndexOf(this->DataBR()); }
    //: Get index of current location of DataBR(),
    //: bottom right pixel in the array.
    // Has to be calculated, and so is slightly slow.

    Index2dC IndexBR() const
    { return array.IndexOf(this->DataBR()); }
    //: Get index of current location of DataBR(),
    //: bottom right pixel in the array.
    // Has to be calculated, and so is slightly slow.
    
  protected:
    Array2dC<DataT> array;
    DataT *up;
  };
}



#endif
