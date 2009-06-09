// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BUFFFERACCESS2ITER2_HEADER
#define RAVL_BUFFFERACCESS2ITER2_HEADER 1
///////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Buffer/BufferAccess2dIter2.hh"
//! lib=RavlCore
//! userlevel=Default
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/BufferAccessIter2.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/IndexRange2d.hh"
#include "Ravl/BufferAccess2dIterBase.hh"

namespace RavlN {

  template <class DataT> class RangeBufferAccess2dC;
  template <class DataT> class SizeBufferAccess2dC;
  

  //! userlevel=Advanced
  //: Iterate through a 2d buffer.
  
  template <class Data1T,class Data2T>
  class BufferAccess2dIter2C 
    : public BufferAccess2dIterBaseC
  {
  public:
    BufferAccess2dIter2C()
    {}
    //: Default constructor.
    
    BufferAccess2dIter2C(const BufferAccessC<Data1T> &pbuf1,IntT stride1,
			 const BufferAccessC<Data2T> &pbuf2,IntT stride2,
                         IntT size1,IntT size2)
    { First(pbuf1,stride1,pbuf2,stride2,size1,size2); }
    //: Constructor.

    BufferAccess2dIter2C(const SizeBufferAccess2dC<Data1T> &pbuf1,
			 const SizeBufferAccess2dC<Data2T> &pbuf2,
                         IntT size1,IntT size2);
    //: Constructor.
    
    BufferAccess2dIter2C(const SizeBufferAccess2dC<Data1T> &pbuf1,
			 const SizeBufferAccess2dC<Data2T> &pbuf2);
    //: Constructor.
    
    BufferAccess2dIter2C(const RangeBufferAccess2dC<Data1T> &pbuf1,
			 const RangeBufferAccess2dC<Data2T> &pbuf2,
                         const IndexRangeC &range1,const IndexRangeC &range2);
    //: Constructor.

    BufferAccess2dIter2C(const RangeBufferAccess2dC<Data1T> &pbuf1,const IndexRange2dC &frame1,
			 const RangeBufferAccess2dC<Data2T> &pbuf2,const IndexRange2dC &frame2);
    //: Constructor.

    BufferAccess2dIter2C(const RangeBufferAccess2dC<Data1T> &pbufA,
			 const RangeBufferAccess2dC<Data2T> &pbufB);
    //: Constructor.

    BufferAccess2dIter2C(const BufferAccessC<Data1T> &pbuf1,IntT byteStride1,
                         const BufferAccessC<Data2T> &pbuf2,IntT byteStride2,
                         SizeT size1,SizeT size2) {
      First(pbuf1,byteStride1,
            pbuf2,byteStride2,
            size1,size2);
    }
    //: Constructor
    
    BufferAccess2dIter2C(const BufferAccessC<Data1T> &pbuf1,IntT byteStride1,const IndexRange2dC &range1,
			 const BufferAccessC<Data2T> &pbuf2,IntT byteStride2,const IndexRange2dC &range2)
    { First(pbuf1,byteStride1,range1.Range1(),range1.Range2(),
            pbuf2,byteStride2,range2.Range1(),range2.Range2()); }
    //: Constructor.
    
    BufferAccess2dIter2C(const BufferAccessC<Data1T> &pbufA,IntT byteStrideA,const IndexRangeC &nrng1a,const IndexRangeC &nrng2a,
			 const BufferAccessC<Data2T> &pbufB,IntT byteStrideB,const IndexRangeC &nrng1b,const IndexRangeC &nrng2b)
    { First(pbufA,byteStrideA,nrng1a,nrng2a,
	    pbufB,byteStrideB,nrng1b,nrng2b);
    }
    //: Constructor.


    bool First(const BufferAccessC<Data1T> &pbuf1,IntT byteStride1,
               const BufferAccessC<Data2T> &pbuf2,IntT byteStride2,
               SizeT size1,SizeT size2) {
      m_size2 = size2;
      m_stride1 = byteStride1;
      m_stride2 = byteStride2;
      if(size1 == 0 || size2 == 0) {
        m_cit.Invalidate();
        m_rit1 = 0;
        m_rit2 = 0;
        m_endRow = 0;
        return false;
      }
      RavlAssert(byteStride1 != 0 && byteStride2 != 0);
      m_rit1 = reinterpret_cast<char *>(pbuf1.ReferenceElm());
      m_rit2 = reinterpret_cast<char *>(pbuf2.ReferenceElm());
      m_endRow = m_rit1+m_stride1 * static_cast<IntT>(size1);
      return m_cit.First(reinterpret_cast<Data1T*>(m_rit1),
                         reinterpret_cast<Data2T*>(m_rit2),
                         m_size2);
    }
    //: Goto first element.
    // returns true if there is one.
    
    bool First(const Data1T *pbuf1,const Data2T *pbuf2,SizeT size1) {
      RavlAssert(m_stride1 != 0 && m_stride2 != 0);
      m_rit1   = reinterpret_cast<char *>(const_cast<Data1T*>(pbuf1));
      m_rit2   = reinterpret_cast<char *>(const_cast<Data2T*>(pbuf2));
      m_endRow = m_rit1 + m_stride1 * static_cast<IntT>(size1);
      return m_cit.First(reinterpret_cast<Data1T*>(m_rit1),
                         reinterpret_cast<Data2T*>(m_rit2),
                         m_size2);
    }
    //: Goto first assuming stride and m_size2 are already setup correctly and size1 is not zero.
    
    bool First(const BufferAccessC<Data1T> &pbuf1,IntT byteStride1,
               const BufferAccessC<Data2T> &pbuf2,IntT byteStride2,
               const IndexRangeC &range1,const IndexRangeC &range2) {
      m_size2 = range2.Size();
      m_stride1 = byteStride1;
      m_stride2 = byteStride2;
      if(range1.IsEmpty() || m_size2 == 0) {
        m_cit.Invalidate();
        m_rit1 = 0;
        m_rit2 = 0;
        m_endRow = 0;
        return false;
      }
      m_rit1 = reinterpret_cast<char *>(pbuf1.ReferenceElm() + range2.Min().V()) + byteStride1 * range1.Min().V();
      m_rit2 = reinterpret_cast<char *>(pbuf2.ReferenceElm() + range2.Min().V()) + byteStride2 * range1.Min().V();
      m_endRow = m_rit1 + byteStride1 * (IntT) range1.Size();
      return m_cit.First(reinterpret_cast<Data1T*>(m_rit1),
                         reinterpret_cast<Data2T*>(m_rit2),
                         m_size2);
    }
    //: Goto first element in the array

    bool First(const BufferAccessC<Data1T> &pbufa,IntT byteStrideA,const IndexRangeC &range1a,const IndexRangeC &range2a,
	       const BufferAccessC<Data2T> &pbufb,IntT byteStrideB,const IndexRangeC &range1b,const IndexRangeC &range2b) {
      m_size2 = range2a.Size();
      m_stride1 = byteStrideA;
      m_stride2 = byteStrideB;
      RavlAssert((IntT) m_size2 <= range2b.Size());
      if(range1a.IsEmpty() || m_size2 == 0) {
        m_cit.Invalidate();
        m_rit1 = 0;
        m_rit2 = 0;
        m_endRow = 0;
        return false;
      }
      RavlAssert(range1a.Size() <= range1b.Size());
      m_rit1 = reinterpret_cast<char *>(pbufa.ReferenceElm() + range2a.Min().V()) + byteStrideA * range1a.Min().V();
      m_rit2 = reinterpret_cast<char *>(pbufb.ReferenceElm() + range2b.Min().V()) + byteStrideB * range1b.Min().V();
      m_endRow = m_rit1 + byteStrideA * range1a.Size();
      return m_cit.First(reinterpret_cast<Data1T*>(m_rit1),
                         reinterpret_cast<Data2T*>(m_rit2),
                         m_size2);
    }
    //: Goto first element.
    // returns true if there is one.

    bool First(const BufferAccessC<Data1T> &pbufa,IntT byteStrideA,const IndexRange2dC &rangea,
	       const BufferAccessC<Data2T> &pbufb,IntT byteStrideB,const IndexRange2dC &rangeb) {
      return First(pbufa,byteStrideA,rangea.Range1(),rangea.Range2(),
                   pbufb,byteStrideB,rangeb.Range1(),rangeb.Range2());
    }
    //: Goto first element.
    // returns true if there is one.
        
    bool Next() { 
      m_cit.Next();
      if(!m_cit.IsElm()) {
	CNextRow();
	return false;
      }
      return true;
    }
    //: Goto next element.
    // returns true if on the same row.
    
    bool NextRow() {
      m_rit1 += m_stride1;
      m_rit2 += m_stride2;
      if(m_rit1 == m_endRow) return false;
      m_cit.First(reinterpret_cast<Data1T*>(m_rit1),
                  reinterpret_cast<Data2T*>(m_rit2),
                  m_size2);
      return true;
    }
    //: Go to the begining of the next row.
    // Returns true if the iterator is begining of a valid row, and false
    // if it is at the end of the array.
    
    bool NextRow(IntT offset) {
      m_rit1 += m_stride1;
      m_rit2 += m_stride2;
      if(m_rit1 == m_endRow || offset >= (IntT) m_size2) return false;
      m_cit.First(reinterpret_cast<Data1T*>(m_rit1) + offset,
                  reinterpret_cast<Data2T*>(m_rit2) + offset,
                  m_size2 - offset);
      return true;
    }
    //: Go to the 'offset' from the first element in the next row.
    // Returns true if the iterator is in a valid row, and false
    // if it is at the end of the array. 
    
    bool SkipRow(IntT offset) {
      m_rit1 += m_stride1 * offset;
      m_rit2 += m_stride2 * offset;
      if(m_stride1 > 0) {
        if(m_rit1 >= m_endRow) return false;
      } else {
        if(m_rit1 <= m_endRow) return false;
      }
      m_cit.First(reinterpret_cast<Data1T*>(m_rit1),
                  reinterpret_cast<Data2T*>(m_rit2),
                  m_size2);
      return true;
    }
    //: Skip 'offset' rows. 
    // Leaves the iterator 'offset' rows further down the image, in the first column. <br>
    // Returns true if the iterator is left on a valid element.
    
    void NextCol(int skip)
    { m_cit.Next(skip); }
    //: Go forward 'skip' columns, without checking for row change.
    // Use with care.

    bool IsElm() const
    { return m_cit.IsElm(); }
    //: At a valid element ?

    operator bool() const
    { return m_cit.IsElm(); }
    //: At a valid element ?
    
    void operator++() {  
      m_cit++;
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
    
    Data1T &Data1() 
    { return m_cit.Data1(); }
    //: Access data.

    const Data1T &Data1() const
    { return m_cit.Data1(); }
    //: Access data.

    Data2T &Data2() 
    { return m_cit.Data2(); }
    //: Access data.
    
    const Data2T &Data2() const
    { return m_cit.Data2(); }
    //: Access data.
        
    void Invalidate()
    { m_cit.Invalidate(); }
    //: Invalidate this iterator.
    
  protected:
    void CNextRow();
    //: Alternate version of NextRow() to help compiler get inlining right.
    
    BufferAccessIter2C<Data1T,Data2T> m_cit;
    SizeT m_size2;
    char  *m_rit2; // Start of current row for array 2
    IntT m_stride2;
  };
  
  template <class Data1T,class Data2T>
  void BufferAccess2dIter2C<Data1T,Data2T>::CNextRow() {
    m_rit1 += m_stride1;
    m_rit2 += m_stride2;
    if(m_rit1 == m_endRow)
      return ;
    m_cit.First(reinterpret_cast<Data1T*>(m_rit1),
                reinterpret_cast<Data2T*>(m_rit2),
                m_size2);
  }
}

#endif

