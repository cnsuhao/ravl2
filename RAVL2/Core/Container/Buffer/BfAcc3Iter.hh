// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BFACC3ITER_HEADER
#define RAVL_BFACC3ITER_HEADER 1
///////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Buffer/BfAcc3Iter.hh"
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! lib=RavlCore
//! userlevel=Advanced
//! author="Charles Galambos"

#include "Ravl/BufferAccessIter.hh"
#include "Ravl/BfAcc2Iter.hh"
#include "Ravl/IndexRange1d.hh"

namespace RavlN {
  template <class DataT> class RangeBufferAccess3dC;
  template <class DataT> class SizeBufferAccess3dC;
  
  //! userlevel=Advanced
  //: 3D buffer iterator.
  
  template <class DataT>
  class BufferAccess3dIterC {
  public:
    BufferAccess3dIterC()
    {}
    //: Default constructor.
    
    BufferAccess3dIterC(const RangeBufferAccess3dC<DataT> &data);
    //: Construct from a 3d buffer.

    BufferAccess3dIterC(const SizeBufferAccess3dC<DataT> &data);
    //: Construct from a 3d buffer.

    BufferAccess3dIterC(const BufferAccessC<DataT> &pbuf,
                        SizeT size1,SizeT size2,SizeT size3,
                        IntT byteStride1,IntT byteStride2)
    { First(pbuf,size1,size2,size3,byteStride1,byteStride2); }
    //: Constructor.
    
    BufferAccess3dIterC(const BufferAccessC<DataT> &pbuf,
                        const IndexRangeC &range1,const IndexRangeC &range2,const IndexRangeC &range3,
                        IntT byteStride1,IntT byteStride2)
    { First(pbuf,range1,range2,range3,byteStride1,byteStride2); }
    //: Constructor.
    
    bool First(const BufferAccessC<DataT> &pbuf,
               const IndexRangeC &range1,const IndexRangeC &range2,const IndexRangeC &range3,
               IntT byteStride1,IntT byteStride2)
    {
      m_slice = reinterpret_cast<char *>(pbuf.ReferenceElm() + range3.Min().V()) + range1.Min().V() * byteStride1 + range2.Min().V() * byteStride2;
      m_sliceEnd = m_slice + byteStride1 * range1.Max().V();
      m_size2 = range2.Size();
      if(m_slice == m_sliceEnd || m_size2 == 0) {
        m_sit.Invalidate();
        return false;
      }
      DataT *sliceStart=reinterpret_cast<DataT*>(m_slice);
      m_sit.First(sliceStart,m_size2,range3.Size(),byteStride2);
      m_stride1 = byteStride1;
      return true;
    }
    //: Goto first element in the array
        
    bool First(const BufferAccessC<DataT> &pbuf,
               SizeT size1,SizeT size2,SizeT size3,
               IntT byteStride1,IntT byteStride2)
    {
      m_slice = reinterpret_cast<char *>(pbuf.ReferenceElm());
      m_sliceEnd = m_slice + byteStride1 * size1;
      if(m_slice == m_sliceEnd || size2 == 0 || size3 == 0) {
        m_sit.Invalidate();
        return false;
      }
      m_size2 = size2;
      m_sit.First(reinterpret_cast<DataT*>(m_slice),size2,size3,byteStride2);
      m_stride1 = byteStride1;
      return true;
    }
    //: Goto first element in the array
    
    void SliceStart() 
    { m_sit.First(reinterpret_cast<DataT *>(m_slice),m_size2); }
    //: Go back to the begining of this row.
    
    bool NextSlice() {
      m_slice += m_stride1;
      if(m_slice == m_sliceEnd)
	return false;
      m_sit.First(reinterpret_cast<DataT *>(m_slice),m_size2);
      return true;      
    }
    //: Go to the begining of the next row.
    // returns true if iterator is left at the begining of a valid row or
    // false if the end of the array has been reached.
    
    bool Next() { 
      m_sit++;
      if(m_sit.IsElm())
	return true;
      this->DoNextSlice();
      return false;
    }
    //: Goto next element.
    // Goto next element in the array. Returns true if the element
    // is on the same row of the array. It returns false if the element is on
    // the next row or at the end of the array.
    
    bool IsElm() const
    { return m_sit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    operator bool() const
    { return m_sit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    void operator++() {  
      m_sit++;
      if(!m_sit.IsElm())
	this->NextSlice();
    }
    //: Goto next element.
    
    void operator++(int) {  
      m_sit++;
      if(!m_sit.IsElm())
	this->NextSlice();
    }
    //: Goto next element.
    
    DataT &operator*() 
    { return *m_sit; }
    //: Access data of current element
    
    const DataT &operator*() const
    { return *m_sit; }
    //: Access data of current element

    DataT *operator->() 
    { return &(*m_sit); }
    //: Access data of current element
    
    const DataT *operator->() const
    { return &(*m_sit); }
    //: Access data of current element
    
    DataT &Data() 
    { return *m_sit; }
    //: Access data of current element

    const DataT &Data() const
    { return *m_sit; }
    //: Access data of current element

    DataT &Data1() 
    { return *m_sit; }
    //: Access data of current element
    
    const DataT &Data1() const
    { return *m_sit; }
    //: Access data of current element
    
  protected:
    bool DoNextSlice();
    //: Goto next row.
    
    char *m_slice;
    const char *m_sliceEnd;
    BufferAccess2dIterC<DataT> m_sit;
    SizeT m_size1;
    SizeT m_size2;
    IntT m_stride1;
  };


  //: Goto next row.
  template <class DataT>
  bool BufferAccess3dIterC<DataT>::DoNextSlice() {
    m_slice += m_stride1;
    if(m_slice == m_sliceEnd)
      return false;
    m_sit.First(reinterpret_cast<DataT *>(m_slice),m_size2);
    return true;
  }

}


#endif
