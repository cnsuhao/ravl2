// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_RANGEBUFFFERACCESS2D_HEADER
#define RAVL_RANGEBUFFFERACCESS2D_HEADER 1
///////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Buffer/RangeBufferAccess2d.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.API.Core.Arrays.Buffer"

#include "Ravl/RangeBufferAccess.hh"
#include "Ravl/BufferAccess2dIter.hh"
#include "Ravl/BufferAccess2dIter2.hh"
#include "Ravl/BufferAccess2dIter3.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/IndexRange2d.hh"
#include "Ravl/Assert.hh"
#include "Ravl/Buffer2d.hh"

namespace RavlN {
  
  class BinOStreamC;
  class BinIStreamC;
  
  //! userlevel=Develop
  //: Basic access to buffer with limited size
  // The class RangeBufferAccessC enables to random indexed access to
  // a sequentially organised continous part of memory called buffer.
  // The access functions check if an accessed element is valid only in
  // debug mode.
  
  template <class DataT>
  class RangeBufferAccess2dC 
    : protected BufferAccessC<DataT>
  {
  public:
    RangeBufferAccess2dC(const IndexRangeC &nrng2)
      : m_stride(0),
        m_range2(nrng2)
    {}
    //: Constructor.
    
    RangeBufferAccess2dC(const RangeBufferAccess2dC<DataT> &buffer,
                         const IndexRangeC &r1,
                         const IndexRangeC &r2)
      : BufferAccessC<DataT>(buffer),
        m_stride(buffer.ByteStride()),
        m_range1(r1),
	m_range2(r2)
    {}
    //: Construct a access to a rectangle within 'ab' with ranges r1 and r2.
    
    RangeBufferAccess2dC(const RangeBufferAccess2dC<DataT> &buffer,const IndexRange2dC &frame)
      : BufferAccessC<DataT>(buffer),
        m_stride(buffer.ByteStride()),
        m_range1(frame.Range1()),
	m_range2(frame.Range2())
    {
      RavlAssert(buffer.Range1().Contains(frame.Range1()));
      RavlAssert(buffer.Range2().Contains(frame.Range2()));
    }
    //: Construct a access to a rectangle within 'ab' with ranges r1 and r2.

    RangeBufferAccess2dC(const BufferAccessC<DataT> &buffer,
                         const IndexRangeC &r1,const IndexRangeC &r2,
                         IntT byteStride)
      : BufferAccessC<DataT>(buffer),
        m_stride(byteStride),
        m_range1(r1),
	m_range2(r2)
    {}
    //: Construct a access to a rectangle within 'ab' with ranges r1 and r2.
    // Assumes all the offsets for the buffers should already be setup.
    
    RangeBufferAccess2dC()
      : m_stride(0),
        m_range2(0,-1)
    {}
    //: Default constructor.

    BufferAccessC<DataT> &BufferAccess()
    { return *this; }
    //: Access buffer;

    const BufferAccessC<DataT> &BufferAccess() const
    { return *this; }
    //: Access buffer;

    inline void Attach(const RangeBufferAccess2dC<DataT> & buffer) 
    { *this = buffer; }
    // Changes this buffer access to have the same access rights as 'buffer'.
    
    inline void Attach(const BufferAccessC<DataT> & buffer,
		       const IndexRangeC          & range1,
		       const IndexRangeC          & range2,
                             IntT                   byteStride
                       ) {
      this->m_buff = reinterpret_cast<DataT *>(reinterpret_cast<char *>(buffer.ReferenceElm()) - byteStride * range1.Min().V()) - range2.Min().V();
      m_range1 = range1;
      m_range2 = range2;
      m_stride = byteStride;
    }
    // Changes this buffer access to have the access rights as 'buffer' limited
    // by range 'range1' and 'range2', so the first element in 'buffer' is accessed at
    // 'range1.Min()','range2.Min()'.

    inline void Attach(const BufferAccessC<DataT> & buffer,
		       const IndexRange2dC        & frame,
                             IntT                   byteStride
                       )
    { Attach(buffer,frame.Range1(),frame.Range2(),byteStride); }
    // Changes this buffer access to have the access rights as 'buffer' limited
    // by frame so the first element in 'buffer' is accessed at
    // 'frame.TRow()','frame.LCol()'.

    inline void Attach(const Buffer2dC<DataT> & buffer,
		       const IndexRangeC      & range1,
		       const IndexRangeC      & range2)
    {
      m_stride = buffer.ByteStride();
      this->m_buff = ShiftPointerInBytes(buffer.ReferenceElm(),-m_stride * range1.Min().V()) - range2.Min().V();
      m_range1 = range1;
      m_range2 = range2;
      RavlAssert((SizeT) range1.Size() <= buffer.Size1());
      RavlAssert((SizeT) range2.Size() <= buffer.Size2());
    }
    // Changes this buffer access to have the access rights as 'buffer' limited
    // by range 'range1' and 'range2', so the first element in 'buffer' is accessed at
    // 'range1.Min()','range2.Min()'.

    inline void Attach(const Buffer2dC<DataT> & buffer,
		       const IndexRange2dC    & frame)
    { Attach(buffer,frame.Range1(),frame.Range2()); }
    // Changes this buffer access to have the access rights as 'buffer' limited
    // by 'frame' so the first element in 'buffer' is accessed at
    // 'frame.TRow()','frame.LCol()'.
    
    inline DataT *PointerTo(IndexC row,IndexC col)
    { return reinterpret_cast<DataT *>(reinterpret_cast<char *>(this->ReferenceVoid()) + row.V() * m_stride) + col.V(); }
    //: Compute an elements position.
    // NOTE: This does not range check, the returned element
    // may not be valid.
    
    inline const DataT *PointerTo(IndexC row,IndexC col) const
    { return reinterpret_cast<DataT *>(reinterpret_cast<char *>(this->ReferenceVoid()) + row.V() * m_stride) + col.V(); }
    //: Compute an elements position.
    // NOTE: This does not range check, the returned element
    // may not be valid.

    inline DataT *RowPtr(IndexC i) {
#if RAVL_CHECK
      if (!m_range1.Contains(i))
	IssueError(__FILE__,__LINE__,"Row index %d out of index range %d to %d  ",i.V(),m_range1.Min().V(),m_range1.Max().V());
#endif
      return reinterpret_cast<DataT *>(reinterpret_cast<char *>(this->ReferenceVoid()) + i.V() * m_stride);
    }
    //: Access element 0 of row i.
    // Note: The element may not actually exist. <p>
    // Advanced users only!

    inline const DataT *RowPtr(IndexC i) const {
#if RAVL_CHECK
      if (!m_range1.Contains(i))
	IssueError(__FILE__,__LINE__,"Row index %d out of index range %d to %d  ",i.V(),m_range1.Min().V(),m_range1.Max().V());
#endif
      return reinterpret_cast<DataT *>(reinterpret_cast<char *>(this->ReferenceVoid()) + i.V() * m_stride);
    }
    //: Access element 0 of row i.
    // Note: The element may not actually exist. <p>
    // Advanced users only!
    
    inline RangeBufferAccessC<DataT> operator[](IndexC i)
    { return RangeBufferAccessC<DataT>(m_range2,RowPtr(i)); }
    //: access to the item array[(i)]

    inline const RangeBufferAccessC<const DataT> operator[](IndexC i) const
    { return RangeBufferAccessC<const DataT>(m_range2,RowPtr(i)); }
    //: return the item array[(i)]

    inline DataT &operator[](const Index2dC & i) { 
#if RAVL_CHECK
      if (!m_range2.Contains(i.Col()))
	IssueError(__FILE__,__LINE__,"Column index %d out of index range %d to %d  ",i.Col().V(),m_range2.Min().V(),m_range2.Max().V());
#endif
      return RowPtr(i.Row())[i.Col().V()];
    }
    //: access to the item array[(i)]
    
    inline const DataT & operator[](const Index2dC & i) const { 
#if RAVL_CHECK
      if (!m_range2.Contains(i.Col()))
	IssueError(__FILE__,__LINE__,"Column index %d out of index range %d to %d  ",i.Col().V(),m_range2.Min().V(),m_range2.Max().V());
#endif
      return RowPtr(i.Row())[i.Col().V()];
    }
    //: return the item array[(i)]
    
    inline const IndexRangeC &Range1() const
    { return m_range1; }
    //: Range of first index.
    
    inline const IndexRangeC &Range2() const
    { return m_range2; }
    //: Range of second index.

    SizeT Size() const 
    { return Range1().Size() * Range2().Size(); }
    //: Get the total number of elements in the array.
    
    void Fill(const DataT &d);
    //: Fill array with value.
    
    void ShiftRows(IndexC offset) {
      this->m_buff = ShiftPointerInBytes(this->m_buff,offset.V() * m_stride);
      m_range2 += offset;
    }
    //: The array is shifted "vertically" by <code>offset</code> w.r.t. the coordinate origin.
    // In other words the row index of a given pixel will be <i>incremented</i> by <code>offset</code>.

    void ShiftCols(IndexC offset) {
      this->m_buff -= offset.V();
      m_range1 += offset;
    }
    //: The array is shifted "horizontally" by <code>offset</code> w.r.t. the coordinate origin.
    // In other words the column index of a given pixel will be <i>incremented</i> by <code>offset</code>.

    IndexRange2dC Rectangle() const
    { return IndexRange2dC(Range1(),Range2()); }
    //: Return ranges of indexes
    
    IndexRange2dC Frame() const
    { return IndexRange2dC(Range1(),Range2()); }
    //: Return ranges of indexes
    
    IndexRange2dC Range() const
    { return IndexRange2dC(Range1(),Range2()); }
    //: Return ranges of indexes

    inline bool Contains(const Index2dC & i) const
    { return Range1().Contains(i.Row()) && Range2().Contains(i.Col()); }
    //: Returns TRUE if there is an item of the 2D array
    
    bool IsContinuous() const
    { return m_stride == static_cast<IntT>((Range2().Size() * sizeof(DataT))); }
    //: Test if all the elements are continuous in memory.
    
    IntT ByteStride() const
    { return m_stride; }
    //: Get the stride between rows.
    // NOTE: This is in bytes.
    
    bool IsEmpty() const
    { return (Range1().Size() <= 0) || (Range2().Size() <= 0); }
    //: Is rectangle empty ?

    IndexC RowIndexOf(const DataT &element) const {
      RavlAssert(IsValid());
      IndexC ret = (IndexC(reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm())) - (Range2().Min()*IndexC((IntT)sizeof(DataT))))/m_stride;
      RavlAssertMsg(Range1().Contains(ret),"Requested element not from this array.");
      return ret;
    }
    //: Compute the row from address of an element in the array.
    // 'element' must be a direct reference to an element in the array.
    
    IndexC ColIndexOf(const DataT &element) const {
      RavlAssert(IsValid());
      IntT diff = (reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm()));
      diff -= Range2().Min() * IndexC((int) sizeof(DataT));
      IndexC ret = ((diff % m_stride)/IndexC((IntT) sizeof(DataT))) + Range2().Min();
      RavlAssertMsg(Range2().Contains(ret),"Requested element not from this array.");
      return ret;
    }
    //: Compute the column from address of an element in the array.
    // 'element' must be a direct reference to an element in the array.
    
    Index2dC IndexOf(const DataT &element) const {
      RavlAssert(IsValid());
      IndexC diff = (reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm()));
      diff -= Range2().Min() * IndexC((IntT) sizeof(DataT));
      Index2dC ret((diff / m_stride),
                   ((diff % m_stride)/IndexC((IntT) sizeof(DataT))) + Range2().Min());
      RavlAssertMsg(Frame().Contains(ret),"Requested element not from this array.");
      return ret;
    }
    //: Gompute the index of 'element' in the array.
    // 'element' must be a direct reference to an element in the array.

    using BufferAccessC<DataT>::IsValid;
    using BufferAccessC<DataT>::ReferenceElm;
    
  protected:
    IntT m_stride; // Stride of array in bytes.
    IndexRangeC m_range1;
    IndexRangeC m_range2;
  };

  // Constructor for the iterator.
  template<typename DataT>
  inline BufferAccess2dIterC<DataT>::BufferAccess2dIterC(const RangeBufferAccess2dC<DataT> &array)
  { First(array.BufferAccess(),array.ByteStride(),array.Range1(),array.Range2()); }

  template<typename DataT>
  inline bool BufferAccess2dIterC<DataT>::First(const SizeBufferAccess2dC<DataT> &array)
  { return First(array.BufferAccess(),array.ByteStride(),array.Range1(),array.Range2()); }
    //: Construct on size array.

  template<typename Data1T,typename Data2T>
  BufferAccess2dIter2C<Data1T,Data2T>::BufferAccess2dIter2C(const RangeBufferAccess2dC<Data1T> &pbuf1,
			                                    const RangeBufferAccess2dC<Data2T> &pbuf2,
                                                            const IndexRangeC &range1,const IndexRangeC &range2) {
    First(pbuf1.BufferAccess(),pbuf1.ByteStride(),
          pbuf2.BufferAccess(),pbuf2.ByteStride(),
          range1,range2);
  }
  //: Constructor.

  template<typename Data1T,typename Data2T,typename Data3T>
  BufferAccess2dIter3C<Data1T,Data2T,Data3T>::BufferAccess2dIter3C(const RangeBufferAccess2dC<Data1T> &pbuf1,
			                                           const RangeBufferAccess2dC<Data2T> &pbuf2,
			                                           const RangeBufferAccess2dC<Data3T> &pbuf3,
                                                                   const IndexRangeC &range1,const IndexRangeC &range2) {
    First(pbuf1.BufferAccess(),pbuf1.ByteStride(),
          pbuf2.BufferAccess(),pbuf2.ByteStride(),
          pbuf3.BufferAccess(),pbuf3.ByteStride(),
          range1,range2);
  }
  //: Constructor.


  template<class DataT>
  void RangeBufferAccess2dC<DataT>::Fill(const DataT &d) {
    for(BufferAccess2dIterC<DataT> it(*this);it;it++)
      *it = d;
  }
  
  template <class DataT>
  ostream & operator<<(ostream & s, const RangeBufferAccess2dC<DataT> & arr) {
    for(BufferAccess2dIterC<DataT> it(arr);it;) {
      s << *it;
      for(;it.Next();) 
	s << ' ' << *it;
      s << '\n';
    }    
    return s;
  }
  
  template <class DataT>
  istream & operator>>(istream & s, RangeBufferAccess2dC<DataT> & arr) {
    for(BufferAccess2dIterC<DataT> it(arr);it;it++) 
      s >> *it;
    return s;
  }

  template<class DataT>
  BinOStreamC &operator<<(BinOStreamC & s, const RangeBufferAccess2dC<DataT> & arr) {
    for(BufferAccess2dIterC<DataT> it(arr);it;it++)
      s << *it;
    return s;
  }
  
  template<class DataT>
  BinIStreamC &operator>>(BinIStreamC & s, RangeBufferAccess2dC<DataT> & arr) {
    for(BufferAccess2dIterC<DataT> it(arr);it;it++)
      s >> *it;
    return s;
  }
  
  //: Save real array to binary stream 
  BinOStreamC &operator<<(BinOStreamC &out,const RangeBufferAccess2dC<RealT> &img);
  
  //: Load real array image from binary stream 
  BinIStreamC &operator>>(BinIStreamC &in,RangeBufferAccess2dC<RealT> &img);  
  
  //: Save float array image to binary stream 
  BinOStreamC &operator<<(BinOStreamC &out,const RangeBufferAccess2dC<FloatT> &img);
  
  //: Load float array image from binary stream 
  BinIStreamC &operator>>(BinIStreamC &in,RangeBufferAccess2dC<FloatT> &img);  
  
  //: Save byte array to binary stream 
  BinOStreamC &operator<<(BinOStreamC &out,const RangeBufferAccess2dC<ByteT> &img);
  
  //: Load byte array from binary stream 
  BinIStreamC &operator>>(BinIStreamC &in,RangeBufferAccess2dC<ByteT> &img);  
  
  
}

#endif
