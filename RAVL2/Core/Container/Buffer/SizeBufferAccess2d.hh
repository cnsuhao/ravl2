// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SBFACC2D_HEADER
#define RAVL_SBFACC2D_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/SizeBufferAccess2d.hh"
//! lib=RavlCore
//! userlevel=Develop
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.API.Core.Arrays.Buffer"

#include "Ravl/SizeBufferAccess.hh"
#include "Ravl/BufferAccess2dIter.hh"
#include "Ravl/BufferAccess2dIter2.hh"
#include "Ravl/BufferAccess2dIter3.hh"
#include "Ravl/Buffer2d.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/Types.hh"
#include "Ravl/IndexRange2d.hh"

namespace RavlN {
  
  class BinOStreamC;
  class BinIStreamC;
  
  //: Basic access to buffer with limited size
  // The class SizeBufferAccessC enables to random indexed access to
  // a sequentially organised continous part of memory called buffer.
  // The access functions check if an accessed element is valid only in
  // debug mode.
  
  template <class DataT>
  class SizeBufferAccess2dC 
    : protected BufferAccessC<DataT>
  {
  public:
    SizeBufferAccess2dC(SizeT size1,SizeT size2,IntT byteStride)
      : m_size1(size1),
        m_size2(size2),
        m_stride(byteStride)
    {}
    //: Constructor.
    
    SizeBufferAccess2dC(const BufferAccessC<DataT> &ab,SizeT size1,SizeT size2,IntT byteStride)
      : BufferAccessC<DataT>(ab),
        m_size1(size1),
	m_size2(size2),
        m_stride(byteStride)
    {}
    //: Constructor.
    
    SizeBufferAccess2dC(const SizeBufferAccess2dC<DataT > &ab,SizeT size1,SizeT size2)
      : BufferAccessC<DataT >(ab),
        m_size1(size1),
	m_size2(size2),
        m_stride(ab.ByteStride())
    {
      RavlAssert(size1 <= ab.Size1());
      RavlAssert(size2 <= ab.Size2());
    }
    //: Constructor.
    
    SizeBufferAccess2dC()
      : m_size1(0),
        m_size2(0),
        m_stride(0)
    {}
    //: Default constructor.

    BufferAccessC<DataT> &BufferAccess()
    { return *this; }
    //: Access buffer;

    const BufferAccessC<DataT> &BufferAccess() const
    { return *this; }
    //: Access buffer;

    inline void Attach(const SizeBufferAccess2dC<DataT> & buffer) {
      *this = buffer;
    }
    // Changes this buffer access to have the same access rights as 'buffer'.

    inline void Attach(const BufferAccessC<DataT> & buffer,
		       const SizeT                  size1,
		       const SizeT                  size2,
                             IntT                   byteStride
                       ) {
      this->m_buff = buffer.ReferenceElm();
      m_size1 = size1;
      m_size2 = size2;
      m_stride = byteStride;
    }
    // Changes this buffer access to have the access rights as 'buffer' limited
    // by size1 and size2. 
    
    inline void Attach(const Buffer2dC<DataT> & buffer,
		       const SizeT              size1,
		       const SizeT              size2
                      )
    {
      m_stride = buffer.ByteStride();
      this->m_buff = buffer.ReferenceElm();
      m_size1 = size1;
      m_size2 = size2;
      RavlAssert((SizeT) size1 <= buffer.Size1());
      RavlAssert((SizeT) size2 <= buffer.Size2());
    }
    // Changes this buffer access to have the access rights as 'buffer' limited
    // by size1 and size2
    
    inline bool Contains(const Index2dC &i) const { 
      return (((UIntT) i.Col().V()) < m_size2) &&
	(((UIntT) i.Row().V()) < m_size1);
    }
    //: Does this buffer contain the index i ?
    // Returns true if yes.

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
    
    DataT *RowPtr(IndexC i) {
#if RAVL_CHECK
      if (((UIntT) i.V()) >= m_size1)
	IssueError(__FILE__,__LINE__,"Row index %u out of index range 0-%u  ",i.V(),m_size1-1);
#endif
      return reinterpret_cast<DataT *>(reinterpret_cast<char *>(this->m_buff) + m_stride * i.V());
    }
    //: Access element 0 of row i.
    // Note: The element may not actually exist. <p>
    // Advanced users only!

    const DataT *RowPtr(IndexC i) const {
#if RAVL_CHECK
      if (((UIntT) i.V()) >= m_size1)
	IssueError(__FILE__,__LINE__,"Row index  %u out of index range 0-%u  ",i.V(),m_size1-1);
#endif
      return reinterpret_cast<const DataT *>(reinterpret_cast<const char *>(this->m_buff) + m_stride * i.V());
    }
    //: Access element 0 of row i.
    // Note: The element may not actually exist. <p>
    // Advanced users only!


    inline DataT & operator[](const Index2dC & i) { 
#if RAVL_CHECK
      if (((UIntT) i.Col().V()) >= m_size2)
	IssueError(__FILE__,__LINE__,"Column index %u out of index range 0-%u  ",i.Col().V(),m_size2-1);
#endif
      return RowPtr(i.Row())[i.Col().V()];
    }
    //: access to the item array[(i)]
    
    inline const DataT & operator[](const Index2dC & i) const { 
#if RAVL_CHECK
      if (((UIntT) i.Col().V()) >= m_size2)
	IssueError(__FILE__,__LINE__,"Column index %u out of index range 0-%u  ",i.Col().V(),m_size2-1);
#endif
      return RowPtr(i.Row())[i.Col().V()];
    }
    //: return the item array[(i)]
    
    inline SizeBufferAccessC<DataT> operator[](IndexC i)
    { return SizeBufferAccessC<DataT>(RowPtr(i.V()),m_size2); }
    //: access to the item array[(i)]
    
    inline const SizeBufferAccessC<const DataT> operator[](IndexC i) const
    { return SizeBufferAccessC<const DataT>(RowPtr(i.V()),m_size2); }
    //: return the item array[(i)]
    
    inline SizeBufferAccessC<DataT> operator[](int i)
    { return SizeBufferAccessC<DataT>(RowPtr(i),m_size2); }
    //: access to the item array[(i)]
    
    inline const SizeBufferAccessC<const DataT> operator[](int i) const
    { return SizeBufferAccessC<const DataT>(RowPtr(i),m_size2); }
    //: return the item array[(i)]
    
    inline SizeT Size1() const
    { return m_size1; }
    //: Size.
    
    inline SizeT Size2() const
    { return m_size2; }
    //: Size.
    
    SizeT Size() const 
    { return Size1() * Size2(); }
    //: Get the total number of elements in the array.
    
    void Fill(const DataT &d);
    //: Fill array with value.
    
    IntT ByteStride() const
    { return m_stride; }
    //: Get the stride of the 2d array. 

    bool IsContinuous() const
    { return m_stride == (IntT) (m_size2 * sizeof(DataT)); }
    //: Test if the array is allocated in a continous area of memory.
    
    IndexRange2dC Frame() const
    { return IndexRange2dC(0,(IntT) m_size1-1,0,(IntT) m_size2-1); }
    //: Return ranges of indexes
    
    IndexRangeC Range1() const
    { return IndexRangeC(0,(IntT) m_size1-1); }
    //: Range of first index.
    
    IndexRangeC Range2() const
    { return IndexRangeC(0,(IntT) m_size2-1); }
    //: Range of second index.
    
    IndexC RowIndexOf(const DataT &element) const {
      RavlAssert(IsValid());
      IndexC ret = (IndexC(reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm())))/m_stride;
      RavlAssertMsg(Range1().Contains(ret),"Requested element not from this array.");
      return ret;
    }
    //: Compute the row from address of an element in the array.
    // 'element' must be a direct reference to an element in the array.

    IndexC ColIndexOf(const DataT &element) const {
      RavlAssert(IsValid());
      IndexC diff = (reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm()));
      IndexC ret = ((diff % m_stride)/IndexC((IntT) sizeof(DataT)));
      RavlAssertMsg(Range2().Contains(ret),"Requested element not from this array.");
      return ret;
    }
    //: Compute the column from address of an element in the array.
    // 'element' must be a direct reference to an element in the array.

    Index2dC IndexOf(const DataT &element) const {
      RavlAssert(IsValid());
      IndexC diff = (reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm()));
      Index2dC ret((diff / m_stride),
                   ((diff % m_stride)/IndexC((IntT) sizeof(DataT))));
      RavlAssertMsg(Frame().Contains(ret),"Requested element not from this array.");
      return ret;
    }
    //: Gompute the index of 'element' in the array.
    // 'element' must be a direct reference to an element in the array.
    

    using BufferAccessC<DataT>::IsValid;
    using BufferAccessC<DataT>::ReferenceElm;
  protected:
    SizeT m_size1;
    SizeT m_size2;
    IntT m_stride;
  };

  // Constructor for the iterator.
  template<typename DataT>
  inline BufferAccess2dIterC<DataT>::BufferAccess2dIterC(const SizeBufferAccess2dC<DataT> &array)
  { First(array.BufferAccess(),array.ByteStride(),
          array.Size1(),array.Size2());
  }

  template<typename Data1T,typename Data2T>
  inline BufferAccess2dIter2C<Data1T,Data2T>::BufferAccess2dIter2C(const SizeBufferAccess2dC<Data1T> &pbuf1,
                                                                   const SizeBufferAccess2dC<Data2T> &pbuf2,
                                                                   IntT size1,IntT size2) {
    First(pbuf1.BufferAccess(),pbuf1.ByteStride(),
          pbuf2.BufferAccess(),pbuf2.ByteStride(),
          size1,size2);
  }

  template<typename Data1T,typename Data2T,typename Data3T>
  inline BufferAccess2dIter3C<Data1T,Data2T,Data3T>::BufferAccess2dIter3C(const SizeBufferAccess2dC<Data1T> &pbuf1,
                                                                          const SizeBufferAccess2dC<Data2T> &pbuf2,
                                                                          const SizeBufferAccess2dC<Data3T> &pbuf3,
                                                                          IntT size1,IntT size2) {
    First(pbuf1.BufferAccess(),pbuf1.ByteStride(),
          pbuf2.BufferAccess(),pbuf2.ByteStride(),
          pbuf3.BufferAccess(),pbuf3.ByteStride(),
          size1,size2);
  }


  template<typename DataT>
  void SizeBufferAccess2dC<DataT>::Fill(const DataT &d) {
    for(BufferAccess2dIterC<DataT> it(*this);it;it++)
      *it = d;
  }
  
  template <class DataT>
  ostream & operator<<(ostream & s, const SizeBufferAccess2dC<DataT> & arr) {
    for(BufferAccess2dIterC<DataT> it(arr);it;) {
      s << *it;
      for(;it.Next();) 
	s << ' ' << *it;
      s << '\n';
    }    
    return s;
  }
  
  template <class DataT>
  istream & operator>>(istream & s, SizeBufferAccess2dC<DataT> & arr) {
    for(BufferAccess2dIterC<DataT> it(arr);it;it++) 
      s >> *it;
    return s;
  }
  
  template<class DataT>
  BinOStreamC &operator<<(BinOStreamC & s, const SizeBufferAccess2dC<DataT> & arr) {
    for(BufferAccess2dIterC<DataT> it(arr);it;it++)
      s << *it;
    return s;
  }
  
  template<class DataT>
  BinIStreamC &operator>>(BinIStreamC & s, SizeBufferAccess2dC<DataT> & arr) {
    for(BufferAccess2dIterC<DataT> it(arr);it;it++)
      s >> *it;
    return s;
  }
  
  //: Save real array to binary stream 
  BinOStreamC &operator<<(BinOStreamC &out,const SizeBufferAccess2dC<RealT> &img);
  
  //: Load real array image from binary stream 
  BinIStreamC &operator>>(BinIStreamC &in,SizeBufferAccess2dC<RealT> &img);  
  
  //: Save float array image to binary stream 
  BinOStreamC &operator<<(BinOStreamC &out,const SizeBufferAccess2dC<FloatT> &img);
  
  //: Load float array image from binary stream 
  BinIStreamC &operator>>(BinIStreamC &in,SizeBufferAccess2dC<FloatT> &img);  
  
  //: Save byte array to binary stream 
  BinOStreamC &operator<<(BinOStreamC &out,const SizeBufferAccess2dC<ByteT> &img);
  
  //: Load byte array from binary stream 
  BinIStreamC &operator>>(BinIStreamC &in,SizeBufferAccess2dC<ByteT> &img);  
  
  
}
#endif
