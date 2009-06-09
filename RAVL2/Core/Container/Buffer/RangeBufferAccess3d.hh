// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_RANGEBUFFERACCESS3D_HEADER
#define RAVL_RANGEBUFFERACCESS3D_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/RangeBufferAccess3d.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.API.Core.Arrays.Buffer"

#include "Ravl/RangeBufferAccess.hh"
#include "Ravl/RangeBufferAccess2d.hh"
#include "Ravl/Index3d.hh"
#include "Ravl/IndexRange3d.hh"
#include "Ravl/BufferAccess3dIter.hh"
#include "Ravl/BufferAccess3dIter2.hh"
#include "Ravl/BufferAccess3dIter3.hh"
#include "Ravl/Types.hh"
#include "Ravl/Buffer3d.hh"

namespace RavlN {

  //! userlevel=Advanced
  //: Access to 3d buffer.
  
  template <class DataT>
  class RangeBufferAccess3dC 
    : protected BufferAccessC<DataT>
  {
  public:
    RangeBufferAccess3dC()
      : m_stride1(0),
        m_stride2(0)
    {}
    //: Default constructor.
    
    RangeBufferAccess3dC(const IndexRangeC &range1,
                         const IndexRangeC &range2,
                         const IndexRangeC &range3,
                         IntT byteStride1,
                         IntT byteStride2)
      : m_range1(range1),
        m_range2(range2),
	m_range3(range3),
        m_stride1(byteStride1),
        m_stride2(byteStride2)
    {}
    //: Constructor.

    RangeBufferAccess3dC(const BufferAccessC<DataT> &buffer,
			 const IndexRange3dC &frame,
                         IntT byteStride1,
                         IntT byteStride2
                         )
      : BufferAccessC<DataT>(buffer),
        m_range1(frame.Range1()),
	m_range2(frame.Range2()),
	m_range3(frame.Range3()),
        m_stride1(byteStride1),
        m_stride2(byteStride2)
    {}
    //: Construct a access to a frame within 'ab' with indexs 'frame'.

    RangeBufferAccess3dC(const RangeBufferAccess3dC<DataT> &ab,
			 const IndexRange3dC &frame)
      : BufferAccessC<DataT>(ab),
        m_range1(frame.Range1()),
	m_range2(frame.Range2()),
	m_range3(frame.Range3()),
        m_stride1(ab.ByteStride1()),
        m_stride2(ab.ByteStride2())
    {
      RavlAssert(ab.Range1().Contains(frame.Range1()));
      RavlAssert(ab.Range2().Contains(frame.Range2()));
      RavlAssert(ab.Range3().Contains(frame.Range3()));
    }
    //: Construct a access to a frame within 'ab' with indexs 'frame'.

    inline void Attach(const Buffer3dC<DataT> & buffer,
		       const IndexRangeC          & range1,
		       const IndexRangeC          & range2,
		       const IndexRangeC          & range3
                       ) {
      m_stride1 = buffer.ByteStride1();
      m_stride2 = buffer.ByteStride2();
      this->m_buff = reinterpret_cast<DataT *>(reinterpret_cast<char *>(buffer.ReferenceElm()) - m_stride1 * range1.Min().V() - m_stride2 * range2.Min().V()) - range3.Min().V();
      m_range1 = range1;
      m_range2 = range2;
      m_range3 = range3;
    }
    // Changes this buffer access to have the access rights as 'buffer' limited
    // by range 'range1', 'range2' and 'range3', so the first element in 'buffer' is accessed at
    // 'range1.Min()','range2.Min()','range3.Min()'.

    inline void Attach(const Buffer3dC<DataT> & buffer,
		       const IndexRange3dC     & frame
                       )
    { Attach(buffer,frame.Range1(),frame.Range2(),frame.Range3()); }
    // Changes this buffer access to have the access rights as 'buffer' limited
    // by given range so the first element in 'buffer' is accessed at
    // 'range.MinI()','range2.MinJ()','range2.MinK()'.

    BufferAccessC<DataT> &BufferAccess()
    { return *this; }
    //: Access buffer;

    const BufferAccessC<DataT> &BufferAccess() const
    { return *this; }
    //: Access buffer;
    
    inline bool Contains(const Index3dC & i) const
    { return Range1().Contains(i.I()) && Range2().Contains(i.J()) && Range3().Contains(i.J()); }
    //: Returns true if there is an item of the �D array

    inline DataT *PointerTo(IndexC i,IndexC j,IndexC k)
    { return reinterpret_cast<DataT *>(reinterpret_cast<char *>(this->ReferenceVoid()) + i.V() * m_stride1 + j.V() * m_stride2) + k.V(); }
    //: Compute an elements position.
    // NOTE: This does not range check, the returned element
    // may not be valid.

    inline const DataT *PointerTo(IndexC i,IndexC j,IndexC k) const
    { return reinterpret_cast<const DataT *>(reinterpret_cast<const char *>(this->ReferenceVoid()) + i.V() * m_stride1 + j.V() * m_stride2) + k.V(); }
    //: Compute an elements position.
    // NOTE: This does not range check, the returned element
    // may not be valid.
    
    DataT *RowPtr(const IndexC &i,const IndexC &j) {
#if RAVL_CHECK
      if(!m_range1.Contains(i))
	IssueError(__FILE__,__LINE__,"I index %d out of index range %d to %d  ",i.V(),m_range1.Min().V(),m_range1.Max().V());
      if(!m_range2.Contains(j))
	IssueError(__FILE__,__LINE__,"J index %d out of index range %d to %d  ",j.V(),m_range2.Min().V(),m_range2.Max().V());
#endif
      return reinterpret_cast<DataT *>(reinterpret_cast<char *>(this->ReferenceVoid()) + i.V() * m_stride1 + j.V() * m_stride2);
    }
    
    const DataT *RowPtr(const IndexC &i,const IndexC &j) const {
#if RAVL_CHECK
      if(!m_range1.Contains(i))
	IssueError(__FILE__,__LINE__,"I index %d out of index range %d to %d  ",i.V(),m_range1.Min().V(),m_range1.Max().V());
      if(!m_range2.Contains(j))
	IssueError(__FILE__,__LINE__,"J index %d out of index range %d to %d  ",j.V(),m_range2.Min().V(),m_range2.Max().V());
#endif
      return reinterpret_cast<const DataT *>(reinterpret_cast<const char *>(this->ReferenceVoid()) + i.V() * m_stride1 + j.V() * m_stride2);
    }

    inline DataT & operator[](const Index3dC & i) {
#if RAVL_CHECK
      if(!m_range3.Contains(i.K()))
	IssueError(__FILE__,__LINE__,"K index %d out of index range %d to %d  ",i.K().V(),m_range3.Min().V(),m_range3.Max().V());
#endif
      return RowPtr(i.I(),i.J())[i.K().V()];
    }
    //: access to the item array[(i)]

    inline const DataT & operator[](const Index3dC & i) const {
#if RAVL_CHECK
      if(!m_range3.Contains(i.K()))
	IssueError(__FILE__,__LINE__,"K index %d out of index range %d to %d  ",i.K().V(),m_range3.Min().V(),m_range3.Max().V());
#endif
      return RowPtr(i.I(),i.J())[i.K().V()];
    }
    //: access to the item array[(i)]


    inline RangeBufferAccess2dC<DataT> operator[](IndexC i) {
#if RAVL_CHECK
      if(!m_range1.Contains(i))
	IssueError(__FILE__,__LINE__,"I index %d out of index range %d to %d  ",i.V(),m_range1.Min().V(),m_range1.Max().V());
#endif 
      DataT *start = reinterpret_cast<DataT *>(reinterpret_cast<char *>(this->ReferenceVoid()) + i.V() * m_stride1);      
      return RangeBufferAccess2dC<DataT>(start,m_range2,m_range3,m_stride2);
    }
    //: access to the item array[(i)]
    
    inline const RangeBufferAccess2dC<const DataT> operator[](IndexC i) const {
#if RAVL_CHECK
      if(!m_range1.Contains(i))
	IssueError(__FILE__,__LINE__,"I index %d out of index range %d to %d  ",i.V(),m_range1.Min().V(),m_range1.Max().V());
#endif
      const DataT *start = reinterpret_cast<const DataT *>(reinterpret_cast<const char *>(this->ReferenceVoid()) + i.V() * m_stride1);
      return RangeBufferAccess2dC<const DataT>(start,m_range2,m_range3,m_stride2);
    }
    //: return the item array[(i)]

    inline const IndexRangeC &Range1() const
    { return m_range1; }
    //: Range of first index.
    
    inline const IndexRangeC &Range2() const
    { return m_range2; }
    //: Range of second index.
    
    inline const IndexRangeC &Range3() const
    { return m_range3; }
    //: Range of second index.
    
    IndexRange3dC Frame() const
    { return IndexRange3dC(Range1(),Range2(),Range3()); }
    //: Return ranges of indexes
    
    IndexRange3dC Range() const
    { return IndexRange3dC(Range1(),Range2(),Range3()); }
    //: Return ranges of indexes
    
    void Fill(const DataT &d);
    //: Fill array with value.
    
    UIntT Size() const 
    { return Range1().Size() * Range2().Size() * Range3().Size(); }
    //: Get the total number of elements in the array.

    bool IsEmpty() const
    { return Range1().Size() == 0 || Range2().Size() == 0 || Range3().Size() == 0; }
    //: Test if there are no accessable elements.
    
    IntT ByteStride1() const
    { return m_stride1; }
    //: Return the distance between continuous stretches of index 2 blocks in bytes.

    IntT ByteStride2() const
    { return m_stride2; }
    //: Return the distance between continuous stretches of index 3 blocks in bytes.

    bool IsContinuous() const {
      return m_stride1 == static_cast<IntT>((Range2().Size() * Range3().Size() * sizeof(DataT)))&&
             m_stride2 == static_cast<IntT>((Range3().Size() * sizeof(DataT)));
    }
    //: Test if the elements are continuous in memory.

    IndexC Index1Of(const DataT &element) const {
      RavlAssert(IsValid());
      IndexC diff = reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm());
      IndexC ret = (diff - (Range3().Min()*((IntT)sizeof(DataT)) + Range2().Min() * m_stride2 + Range1().Min() * m_stride1) )/m_stride1 +  Range1().Min();
      RavlAssertMsg(Range1().Contains(ret),"Requested element not from this array.");
      return ret;
    }
    //: Compute the row from address of an element in the array.
    // 'element' must be a direct reference to an element in the array.

    IndexC Index2Of(const DataT &element) const {
      RavlAssert(IsValid());
      IndexC diff = (reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm()));
      diff -= (Range3().Min()*((IntT)sizeof(DataT)) + Range2().Min() * m_stride2 + Range1().Min() * m_stride1);
      IndexC ret = ((diff % m_stride1)/m_stride2) + Range2().Min();
      RavlAssertMsg(Range2().Contains(ret),"Requested element not from this array.");
      return ret;
    }
    //: Compute the column from address of an element in the array.
    // 'element' must be a direct reference to an element in the array.

    IndexC Index3Of(const DataT &element) const {
      RavlAssert(IsValid());
      IndexC diff = (reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm()));
      diff -= (Range3().Min()*((IntT)sizeof(DataT)) + Range2().Min() * m_stride2 + Range1().Min() * m_stride1);
      IndexC ret = ((diff % m_stride1)%m_stride2)/IndexC((IntT) sizeof(DataT)) + Range3().Min();
      RavlAssertMsg(Range3().Contains(ret),"Requested element not from this array.");
      return ret;
    }
    //: Compute the column from address of an element in the array.
    // 'element' must be a direct reference to an element in the array.

    Index3dC IndexOf(const DataT &element) const {
      RavlAssert(IsValid());
      IndexC diff = (reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm()));
      diff -= (Range3().Min()*((IntT)sizeof(DataT)) + Range2().Min() * m_stride2 + Range1().Min() * m_stride1);

      IndexC offset2 = (diff % m_stride1);
      Index3dC ret((diff / m_stride1) + Range1().Min(),
                   (offset2/m_stride2) + Range2().Min(),
                   (offset2%m_stride2)/IndexC((IntT) sizeof(DataT)) + Range3().Min()) ;
      RavlAssertMsg(Range1().Contains(ret.I()) && Range2().Contains(ret.J()) && Range3().Contains(ret.K()),
                    "Requested element not from this array.");
      return ret;
    }
    //: Gompute the index of 'element' in the array.
    // 'element' must be a direct reference to an element in the array.

    void ShiftIndex1(IndexC offset) {
      this->m_buff = ShiftPointerInBytes(this->m_buff,-offset.V() * m_stride2);
      m_range1 += offset;
    }
    //: The array is shifted "vertically" by <code>offset</code> w.r.t. the coordinate origin.
    // In other words the row index of a given pixel will be <i>incremented</i> by <code>offset</code>.

    void ShiftIndex2(IndexC offset) {
      this->m_buff = ShiftPointerInBytes(this->m_buff,-offset.V() * m_stride1);
      m_range2 += offset;
    }
    //: The array is shifted "horizontally" by <code>offset</code> w.r.t. the coordinate origin.
    // In other words the column index of a given pixel will be <i>incremented</i> by <code>offset</code>.

    void ShiftIndex3(IndexC offset) {
      this->m_buff -= offset.V();
      m_range3 += offset;
    }
    //: The array is shifted "horizontally" by <code>offset</code> w.r.t. the coordinate origin.
    // In other words the column index of a given pixel will be <i>incremented</i> by <code>offset</code>.

    using BufferAccessC<DataT>::IsValid;
    using BufferAccessC<DataT>::ReferenceElm;

  protected:
    IndexRangeC m_range1;
    IndexRangeC m_range2;
    IndexRangeC m_range3;
    IntT m_stride1;
    IntT m_stride2;
  };


  template<typename DataT>
  BufferAccess3dIterC<DataT>::BufferAccess3dIterC(const RangeBufferAccess3dC<DataT> &data)
  { First(data.BufferAccess(),data.ByteStride1(),data.ByteStride2(),
          data.Range1(),data.Range2(),data.Range3());
  }
  //: Construct from a 3d buffer.

  template<typename DataT>
  BufferAccess3dIterC<DataT>::BufferAccess3dIterC(const RangeBufferAccess3dC<DataT> &bufA,
                      const IndexRangeC &range1,
                      const IndexRangeC &range2,
                      const IndexRangeC &range3) {
    First(bufA.BufferAccess(),bufA.ByteStride1(),bufA.ByteStride2(),
          range1,range2,range3);
  }
  //: Construct from a 3d buffer.


  template<typename Data1T,typename Data2T>
  BufferAccess3dIter2C<Data1T,Data2T>::BufferAccess3dIter2C(const RangeBufferAccess3dC<Data1T> &bufA,
                                                            const RangeBufferAccess3dC<Data2T> &bufB,
                                                            const IndexRangeC &range1,const IndexRangeC &range2,const IndexRangeC &range3)
  {
    First(bufA.BufferAccess(),bufA.ByteStride1(),bufA.ByteStride2(),
          bufB.BufferAccess(),bufB.ByteStride1(),bufB.ByteStride2(),
          range1,range2,range3);
  }
  //: Construct from a 3d buffer.
  
  template<typename Data1T,typename Data2T>
  BufferAccess3dIter2C<Data1T,Data2T>::BufferAccess3dIter2C(const RangeBufferAccess3dC<Data1T> &bufA,
                                                            const RangeBufferAccess3dC<Data2T> &bufB,
                                                            const IndexRange3dC &range)
  {
    First(bufA.BufferAccess(),bufA.ByteStride1(),bufA.ByteStride2(),
          bufB.BufferAccess(),bufB.ByteStride1(),bufB.ByteStride2(),
          range.Range1(),range.Range2(),range.Range3());
  }
  //: Construct from a 3d buffer.

  template<typename Data1T,typename Data2T,typename Data3T>
  BufferAccess3dIter3C<Data1T,Data2T,Data3T>::BufferAccess3dIter3C(const RangeBufferAccess3dC<Data1T> &bufA,
                                                                   const RangeBufferAccess3dC<Data2T> &bufB,
                                                                   const RangeBufferAccess3dC<Data3T> &bufC,
                                                                   const IndexRangeC &range1,const IndexRangeC &range2,const IndexRangeC &range3)
  {
    First(bufA.BufferAccess(),bufA.ByteStride1(),bufA.ByteStride2(),
          bufB.BufferAccess(),bufB.ByteStride1(),bufB.ByteStride2(),
          bufC.BufferAccess(),bufC.ByteStride1(),bufC.ByteStride2(),
          range1,range2,range3);
  }
  //: Construct from a 3d buffer.

  template<typename Data1T,typename Data2T,typename Data3T>
  BufferAccess3dIter3C<Data1T,Data2T,Data3T>::BufferAccess3dIter3C(const RangeBufferAccess3dC<Data1T> &bufA,
                                                                   const RangeBufferAccess3dC<Data2T> &bufB,
                                                                   const RangeBufferAccess3dC<Data3T> &bufC,
                                                                   const IndexRange3dC &range)
  {
    First(bufA.BufferAccess(),bufA.ByteStride1(),bufA.ByteStride2(),
          bufB.BufferAccess(),bufB.ByteStride1(),bufB.ByteStride2(),
          bufC.BufferAccess(),bufC.ByteStride1(),bufC.ByteStride2(),
          range.Range1(),range.Range2(),range.Range3());
  }
  //: Construct from a 3d buffer.

  
  template<class DataT>
  void RangeBufferAccess3dC<DataT>::Fill(const DataT &d) {
    for(BufferAccess3dIterC<DataT> it(*this);it;it++)
      *it = d;
  }

  
  template <class DataT>
  ostream & operator<<(ostream & s, const RangeBufferAccess3dC<DataT> & arr) {
    for(BufferAccess3dIterC<DataT> it(arr);it;) {
      s << *it;
      for(;it.Next();) 
	s << ' ' << *it;
      s << '\n';
    }    
    return s;
  }
  
  template <class DataT>
  istream & operator>>(istream & s, RangeBufferAccess3dC<DataT> & arr) {
    for(BufferAccess3dIterC<DataT> it(arr);it;it++) 
      s >> *it;
    return s;
  }

  template<class DataT>
  BinOStreamC &operator<<(BinOStreamC & s, const RangeBufferAccess3dC<DataT> & arr) {
    for(BufferAccess3dIterC<DataT> it(arr);it;it++)
      s << *it;
    return s;
  }
  
  template<class DataT>
  BinIStreamC &operator>>(BinIStreamC & s, RangeBufferAccess3dC<DataT> & arr) {
    for(BufferAccess3dIterC<DataT> it(arr);it;it++)
      s >> *it;
    return s;
  }
  
}

#endif
