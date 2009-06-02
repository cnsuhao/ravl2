// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BUFFERACCES2DITER_HEADER
#define RAVL_BUFFERACCES2DITER_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/BufferAccess2dIter.hh"
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! lib=RavlCore
//! userlevel=Advanced
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/BufferAccessIter.hh"
#include "Ravl/IndexRange1d.hh"
#include "Ravl/IndexRange2d.hh"
#include "Ravl/Index2d.hh"

namespace RavlN {

  template <class DataT> class RangeBufferAccess2dC;
  template <class DataT> class SizeBufferAccess2dC;
  
  //! userlevel=Advanced
  //: 2d buffer iterator.
  
  template <class DataT>
  class BufferAccess2dIterC {
  public:
    BufferAccess2dIterC()
    {}
    //: Default constructor.

    BufferAccess2dIterC(const BufferAccessC<DataT> &pbuf,IntT byteStride,
                        SizeT size1,SizeT size2)
    { First(pbuf,byteStride,size1,size2); }
    //: Constructor.    
    
    BufferAccess2dIterC(const BufferAccessC<DataT> &pbuf,IntT byteStride,
                        const IndexRangeC &nrng1,const IndexRangeC &nrng2)
    { First(pbuf,byteStride,nrng1,nrng2); }
    //: Constructor.
    
    BufferAccess2dIterC(const RangeBufferAccess2dC<DataT> &array);
    //: Construct on ranged array.
    
    BufferAccess2dIterC(const SizeBufferAccess2dC<DataT> &array);
    //: Construct on size array.
    
    bool First(const BufferAccessC<DataT> &pbuf,IntT byteStride,
               SizeT size1,SizeT size2) {
      if(size1 == 0 || size2 == 0) {
        m_cit.Invalidate();
        return false;
      }
      m_size2 = size2;
      m_rit   = reinterpret_cast<char *>(pbuf.ReferenceElm());
      m_endRow = m_rit + byteStride * (IntT) size1;
      DataT *colStart=reinterpret_cast<DataT*>(m_rit);
      m_cit.First(colStart,m_size2);
      m_stride = byteStride;
      return true;
    }
    //: Goto first element in the array.
    
    bool First(const DataT *pbuf,SizeT size1) {
      RavlAssert(m_stride != 0);
      RavlAssert(m_size2 != 0)
      m_rit   = reinterpret_cast<char *>(const_cast<DataT*>(pbuf));
      m_endRow = m_rit + m_stride * (IntT) size1;
      DataT *colStart=reinterpret_cast<DataT*>(m_rit);
      m_cit.First(colStart,m_size2);
      return true;
    }
    //: Goto first assuming stride and m_size2 are already setup correctly and size1 is not zero.

    bool First(const BufferAccessC<DataT> &pbuf,IntT byteStride,
               const IndexRangeC &range1,const IndexRangeC &range2) {
      m_size2 = range2.Size();
      if(range1.IsEmpty() || m_size2 == 0) {
        m_cit.Invalidate();
        return false;
      }
      m_rit   = reinterpret_cast<char *>(pbuf.ReferenceElm() + range2.Min().V()) + byteStride * range1.Min().V();
      m_endRow = m_rit + byteStride * range1.Size();
      DataT *colStart=reinterpret_cast<DataT*>(m_rit);
      m_cit.First(colStart,m_size2);
      m_stride = byteStride;
      return true;
    }
    //: Goto first element in the array
    
    bool First(const BufferAccessC<DataT> &pbuf,IntT byteStride,const IndexRange2dC &range)
    { return First(pbuf,byteStride,range.Range1(),range.Range2()); }
    //: Goto first.

    bool First(const SizeBufferAccess2dC<DataT> &array);
    //: Construct on size array.

    inline void RowStart() {
      DataT *colStart=reinterpret_cast<DataT*>(m_rit);
      m_cit.First(colStart,m_size2);
    }
    //: Go back to the begining of this row.
    
    void SetColEnd(int n)
    { m_cit.SetEnd(n); }
    //: End the iteration of the current row n elements from current place.
    // 'n' must be less than or equal to the number of elements left. 
    
    bool NextRow() {
      m_rit += m_stride;
      if(m_rit == m_endRow)
	return false;
      DataT *colStart=reinterpret_cast<DataT*>(m_rit);
      m_cit.First(colStart,m_size2);
      return true;      
    }
    //: Go to the begining of the next row.
    // Returns true if the iterator is begining of a valid row, and false
    // if it is at the end of the array.
    
    bool NextRow(IndexC off) {
      m_rit += m_stride;
      if(m_rit == m_endRow)
	return false;
      if(off > m_size2)
	return false;
      RavlAssert(off >= 0);
      m_cit.First(reinterpret_cast<DataT *>(m_rit) + off.V(),
                  m_size2 - off.V());
      return true;
    }
    //: Goto 'offset' column's in on the next row.
    // Returns true if the iterator is in a valid row, and false
    // if it is at the end of the array.
    
    bool SkipRow(IntT offset) {
      m_rit += m_stride * offset;
      if(m_stride > 0) {
        if(m_rit >= m_endRow) return false;
      } else {
        if(m_rit <= m_endRow) return false;
      }
      DataT *colStart=reinterpret_cast<DataT*>(m_rit);
      m_cit.First(colStart,m_size2);
      return true;
    }
    //: Skip 'offset' rows. 
    // Leaves the iterator 'offset' rows further down the image, in the first column. <br>
    // Returns true if the iterator is left on a valid element.
    
    void NextCol()
    { m_cit.Next(); }
    //: Goto next column, without checking for row change.
    // Use with care.

    void NextCol(int skip)
    { m_cit.Next(skip); }
    //: Go forward 'skip' columns, without checking for row change.
    // Use with care.
    
    bool IsColElm() const
    { return m_cit.IsElm(); }
    //: Is column element ?
    
    bool Next() { 
      m_cit.Next();
      if(m_cit.IsElm())
	return true;
      CNextRow();
      return false;
    }
    //: Goto next element.
    // Goto next element in the array. Returns true if the element
    // is on the same row of the array. It returns false if the element is on
    // the next row or at the end of the array.
    
    bool IsElm() const
    { return m_cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    operator bool() const
    { return m_cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    void operator++() { 
      ++m_cit;
      if(!m_cit.IsElm())
	CNextRow();
    }
    //: Goto next element.
    
    void operator++(int) {
      m_cit++;
      if(!m_cit.IsElm())
	CNextRow();      
    }
    //: Goto next element.
    
    void operator+=(UIntT n) {
      m_cit.Next(n);
      if(!m_cit.IsElm())
	CNextRow(n);
    }
    //: Goto next element when subsampling by a factor of n.
    //  That is, when used to iterate through a 2D array, it will subsample rows and columns by a factor of n
    
    DataT &operator*() 
    { return *m_cit; }
    //: Access data of current element
    
    const DataT &operator*() const
    { return *m_cit; }
    //: Access data of current element
    
    DataT *operator->() 
    { return &(*m_cit); }
    //: Access data of current element
    
    const DataT *operator->() const
    { return &(*m_cit); }
    //: Access data of current element
    
    DataT &Data() 
    { return *m_cit; }
    //: Access data of current element

    const DataT &Data() const
    { return *m_cit; }
    //: Access data of current element

    DataT &Data1() 
    { return *m_cit; }
    //: Access data of current element
    
    const DataT &Data1() const
    { return *m_cit; }
    //: Access data of current element

//    RangeBufferAccessC<DataT> Row()
//    { return RangeBufferAccessC<DataT>(m_range2,reinterpret_cast<DataT *>(m_rit)); }
//    //: Access row we're currently iterating.
//
//    const RangeBufferAccessC<DataT> Row() const
//    { return RangeBufferAccessC<DataT>(m_range2,reinterpret_cast<DataT *>(m_rit)); }
//    //: Access row we're currently iterating.

		  
    void Invalidate()
    { m_cit.Invalidate(); }
    //: Invalidate this iterator.
    
  protected:
    void CNextRow();
    //: Non inlined next row method to encourage the compiler to get inlining of Next() right.
    
    void CNextRow(IntT n);
    //: Non inlined next row method to encourage the compiler to get inlining of Next() right.
    
    BufferAccessIterC<DataT> m_cit;
    SizeT m_size2;
    char  *m_rit; // Row iterator.
    const char *m_endRow;
    IntT m_stride;
  };

  
  template <class DataT>
  void BufferAccess2dIterC<DataT>::CNextRow() {
    m_rit += m_stride;
    if(m_rit != m_endRow)
      RowStart();
  }
  
  template <class DataT>
  void BufferAccess2dIterC<DataT>::CNextRow(IntT n) {
    m_rit += m_stride * n;
    if(m_stride > 0) {
      if(m_rit < m_endRow) RowStart();
    } else {
      if(m_rit > m_endRow) RowStart();
    }
  }
  
}


#endif
