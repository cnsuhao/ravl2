// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SBFACC3D_HEADER
#define RAVL_SBFACC3D_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/SizeBufferAccess3d.hh"
//! lib=RavlCore
//! userlevel=Develop
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.API.Core.Arrays.Buffer"

#include "Ravl/SizeBufferAccess.hh"
#include "Ravl/SizeBufferAccess2d.hh"
#include "Ravl/Index3d.hh"
#include "Ravl/BufferAccess3dIter.hh"
#include "Ravl/BufferAccess3dIter2.hh"
#include "Ravl/BufferAccess3dIter3.hh"
#include "Ravl/Types.hh"
#include "Ravl/Buffer3d.hh"

namespace RavlN {
  
  class BinOStreamC;
  class BinIStreamC;
  
  //! userlevel=Develop
  //: Access for 3D array.
  
  template <class DataT>
  class SizeBufferAccess3dC 
    : protected BufferAccessC<DataT>
  {
  public:
    SizeBufferAccess3dC()
      : m_size1(0),
        m_size2(0),
	m_size3(0),
        m_stride1(0),
        m_stride2(0)
    {}
    //: Default constructor.
    
    SizeBufferAccess3dC(SizeT size1,SizeT size2,SizeT size3)
      : m_size1(size1),
        m_size2(size2),
	m_size3(size3),
        m_stride1(0),
        m_stride2(0)
    {}
    //: Constructor.

    SizeBufferAccess3dC(const BufferAccessC<DataT> &ab,
                        IntT byteStride1,IntT byteStride2,
                        SizeT size1,SizeT size2,SizeT size3
                        )
      : BufferAccessC<DataT>(ab),
        m_size1(size1),
	m_size2(size2),
	m_size3(size3),
        m_stride1(byteStride1),
        m_stride2(byteStride2)
    {}
    //: Constructor.

    SizeBufferAccess3dC(const Buffer3dC<DataT> &ab,
                        SizeT size1,SizeT size2,SizeT size3)
      : BufferAccessC<DataT>(ab),
        m_size1(size1),
	m_size2(size2),
	m_size3(size3),
        m_stride1(ab.ByteStride1()),
        m_stride2(ab.ByteStride2())
    {
      RavlAssert(m_size1 <= ab.Size1());
      RavlAssert(m_size2 <= ab.Size2());
      RavlAssert(m_size3 <= ab.Size3());
    }
    //: Constructor.
    
    using BufferAccessC<DataT>::IsValid;
    using BufferAccessC<DataT>::ReferenceElm;
    
    void Attach(const BufferAccessC<DataT> &ab,
                IntT byteStride1,IntT byteStride2,
                SizeT size1,SizeT size2,SizeT size3
                ) {
      BufferAccess() = ab;
      m_size1 = size1;
      m_size2 = size2;
      m_size3 = size3;
      m_stride1 = byteStride1;
      m_stride2 = byteStride2;
    }
    //: Attach to a buffer.

    void Attach(const Buffer3dC<DataT> &ab,
                SizeT size1,SizeT size2,SizeT size3
                ) {
      BufferAccess() = ab;
      m_size1 = size1;
      m_size2 = size2;
      m_size3 = size3;
      m_stride1 = ab.ByteStride1();
      m_stride2 = ab.ByteStride2();
    }
    //: Attach to a buffer.
    

    BufferAccessC<DataT> &BufferAccess()
    { return *this; }
    //: Access buffer;

    const BufferAccessC<DataT> &BufferAccess() const
    { return *this; }
    //: Access buffer;

    inline bool Contains(const Index3dC & i) const { 
      return (((UIntT) i.K().V()) < m_size3) &&
	(((UIntT) i.J().V()) < m_size2) &&
	(((UIntT) i.I().V()) < m_size1);
    }
    //: Returns true if there is an item of the 3D array

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
      if(((UIntT) i.V()) >= m_size1)
	IssueError(__FILE__,__LINE__,"I index %d out of index range 0 to %zu  ",i.V(),static_cast<size_t>(m_size1));
      if(((UIntT) j.V()) >= m_size2)
	IssueError(__FILE__,__LINE__,"J index %d out of index range 0 to %zu  ",j.V(),static_cast<size_t>(m_size2));
#endif
      return reinterpret_cast<DataT *>(reinterpret_cast<char *>(this->ReferenceVoid()) + i.V() * m_stride1 + j.V() * m_stride2);
    }

    const DataT *RowPtr(const IndexC &i,const IndexC &j) const {
#if RAVL_CHECK
      if(((UIntT) i.V()) >= m_size1)
	IssueError(__FILE__,__LINE__,"I index %d out of index range 0 to %zu  ",i.V(),static_cast<size_t>(m_size1));
      if(((UIntT) j.V()) >= m_size2)
	IssueError(__FILE__,__LINE__,"J index %d out of index range 0 to %zu  ",j.V(),static_cast<size_t>(m_size2));
#endif
      return reinterpret_cast<const DataT *>(reinterpret_cast<const char *>(this->ReferenceVoid()) + i.V() * m_stride1 + j.V() * m_stride2);
    }

    inline DataT & operator[](const Index3dC & i) { 
#if RAVL_CHECK
      if(((UIntT) i.K().V()) >= m_size3)
	IssueError(__FILE__,__LINE__,"K index %d out of index range 0 to %zu  ",i.K().V(),static_cast<size_t>(m_size3));
#endif
      return RowPtr(i.I(),i.J())[i.K().V()];
    }
    //: access to the item array[(i)]
    
    inline const DataT & operator[](const Index3dC & i) const { 
#if RAVL_CHECK
      if(((UIntT) i.K().V()) >= m_size3)
	IssueError(__FILE__,__LINE__,"K index %d out of index range 0 to %zu  ",i.K().V(),static_cast<size_t>(m_size3));
#endif
      return RowPtr(i.I(),i.J())[i.K().V()];
    }
    //: return the item array[(i)]
    
    inline SizeBufferAccess2dC<DataT> operator[](const IndexC &i) {
#if RAVL_CHECK
      if(((UIntT) i.V()) >= m_size1)
	IssueError(__FILE__,__LINE__,"I index %d out of index range 0 to %zu  ",i.V(),static_cast<size_t>(m_size1));
#endif
      DataT *start = reinterpret_cast<DataT *>(reinterpret_cast<char *>(this->ReferenceVoid()) + i.V() * m_stride1);
      return SizeBufferAccess2dC<DataT>(start,m_size2,m_size3,m_stride2);
    }
    //: access to the item array[(i)]
    
    inline const SizeBufferAccess2dC<const DataT> operator[](const IndexC &i) const {
#if RAVL_CHECK
      if(((UIntT) i.V()) >= m_size1)
	IssueError(__FILE__,__LINE__,"I index %d out of index range 0 to %zu  ",i.V(),static_cast<size_t>(m_size1));
#endif
      const DataT *start = reinterpret_cast<const DataT *>(reinterpret_cast<const char *>(this->ReferenceVoid()) + i.V() * m_stride1);
      return SizeBufferAccess2dC<const DataT>(start,m_size2,m_size3,m_stride2);
    }
    //: return the item array[(i)]

        inline SizeBufferAccess2dC<DataT> operator[](const SizeC &i) {
#if RAVL_CHECK
      if(((UIntT) i.V()) >= m_size1)
	IssueError(__FILE__,__LINE__,"I index %d out of index range 0 to %zu  ",i.V(),m_size1);
#endif
      DataT *start = reinterpret_cast<DataT *>(reinterpret_cast<char *>(this->ReferenceVoid()) + i.V() * m_stride1);
      return SizeBufferAccess2dC<DataT>(start,m_size2,m_size3,m_stride2);
    }
    //: access to the item array[(i)]

    inline const SizeBufferAccess2dC<const DataT> operator[](const SizeT &i) const {
#if RAVL_CHECK
      if(((UIntT) i.V()) >= m_size1)
	IssueError(__FILE__,__LINE__,"I index %d out of index range 0 to %zu  ",i.V(),static_cast<size_t>(m_size1));
#endif
      const DataT *start = reinterpret_cast<const DataT *>(reinterpret_cast<const char *>(this->ReferenceVoid()) + i.V() * m_stride1);
      return SizeBufferAccess2dC<const DataT>(start,m_size2,m_size3,m_stride2);
    }
    //: return the item array[(i)]

    inline SizeBufferAccess2dC<DataT> operator[](int i) {
#if RAVL_CHECK
      if(((UIntT) i) >= m_size1)
	IssueError(__FILE__,__LINE__,"I index %d out of index range 0 to %zu  ",i,static_cast<size_t>(m_size1));
#endif
      DataT *start = reinterpret_cast<DataT *>(reinterpret_cast<char *>(this->ReferenceVoid()) + i * m_stride1);
      return SizeBufferAccess2dC<DataT>(start,m_size2,m_size3,m_stride2);
    }
    //: access to the item array[(i)]
    
    inline SizeBufferAccess2dC<const DataT> operator[](int i) const {
#if RAVL_CHECK
      if(((UIntT) i) >= m_size1)
	IssueError(__FILE__,__LINE__,"I index %d out of index range 0 to %zu  ",i,static_cast<size_t>(m_size1));
#endif
      const DataT *start = reinterpret_cast<const DataT *>(reinterpret_cast<const char *>(this->ReferenceVoid()) + i * m_stride1);
      return SizeBufferAccess2dC<const DataT>(start,m_size2,m_size3,m_stride2);
    }
    //: return the item array[(i)]
    
    SizeT Size1() const
    { return m_size1; }
    //: Get size of dimension 1
    
    SizeT Size2() const
    { return m_size2; }
    //: Get size of dimension 2
    
    SizeT Size3() const
    { return m_size3; }
    //: Get size of dimension 3

    SizeT Size() const 
    { return Size1() * Size2() * Size3(); }
    //: Get the total number of elements in the array.

    IndexRangeC Range1() const
    { return IndexRangeC(0,(IntT) m_size1-1); }
    //: Range of first index.

    IndexRangeC Range2() const
    { return IndexRangeC(0,(IntT) m_size2-1); }
    //: Range of second index.

    IndexRangeC Range3() const
    { return IndexRangeC(0,(IntT) m_size3-1); }
    //: Range of third index.
    
    bool IsEmpty() const
    { return m_size1== 0 || m_size2 == 0 || m_size3 == 0;}
    //: Test if no elements are accessable by this interface.
    
    IntT ByteStride1() const
    { return m_stride1; }
    //: Access number of bytes between slices.
    
    IntT ByteStride2() const
    { return m_stride2; }
    //: Access number of bytes between rows.
    
    void Fill(const DataT &d);
    //: Fill array with value.

    IndexC Index1Of(const DataT &element) const {
      RavlAssert(IsValid());
      IndexC diff = reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm());
      IndexC ret = diff/m_stride1;
      RavlAssertMsg(Range1().Contains(ret),"Requested element not from this array.");
      return ret;
    }
    //: Compute the row from address of an element in the array.
    // 'element' must be a direct reference to an element in the array.

    IndexC Index2Of(const DataT &element) const {
      RavlAssert(IsValid());
      IndexC diff = (reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm()));
      IndexC ret = ((diff % m_stride1)/m_stride2);
      RavlAssertMsg(Range2().Contains(ret),"Requested element not from this array.");
      return ret;
    }
    //: Compute the column from address of an element in the array.
    // 'element' must be a direct reference to an element in the array.

    IndexC Index3Of(const DataT &element) const {
      RavlAssert(IsValid());
      IndexC diff = (reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm()));
      IndexC ret = ((diff % m_stride1)%m_stride2)/IndexC((IntT) sizeof(DataT)) ;
      RavlAssertMsg(Range3().Contains(ret),"Requested element not from this array.");
      return ret;
    }
    //: Compute the column from address of an element in the array.
    // 'element' must be a direct reference to an element in the array.

    Index3dC IndexOf(const DataT &element) const {
      RavlAssert(IsValid());
      IndexC diff = (reinterpret_cast<const char *>(&element) - reinterpret_cast<const char *>(ReferenceElm()));
      IndexC offset2 = (diff % m_stride1);
      Index3dC ret((diff / m_stride1),
                   (offset2/m_stride2),
                   (offset2%m_stride2)/IndexC((IntT) sizeof(DataT))) ;
      RavlAssertMsg(Range1().Contains(ret.I()) && Range2().Contains(ret.J()) && Range3().Contains(ret.K()),
                    "Requested element not from this array.");
      return ret;
    }
    //: Compute the index of 'element' in the array.
    // 'element' must be a direct reference to an element in the array.

  protected:
    SizeT m_size1;
    SizeT m_size2;
    SizeT m_size3;
    IntT m_stride1;
    IntT m_stride2;
  };


  template<class DataT>
  BufferAccess3dIterC<DataT>::BufferAccess3dIterC(const SizeBufferAccess3dC<DataT> &data)
  { First(data.BufferAccess(),data.ByteStride1(),data.ByteStride2(),data.Size1(),data.Size2(),data.Size3()); }
  //: Constructor for an iterator.

  template<class DataT>
  BufferAccess3dIterC<DataT>::BufferAccess3dIterC(const SizeBufferAccess3dC<DataT> &pbufA,
      SizeT size1, SizeT size2, SizeT size3)
  {
    First(pbufA.BufferAccess(), pbufA.ByteStride1(), pbufA.ByteStride2(),
        size1, size2, size3);
  }

  //: Constructor.


  template<typename Data1T,typename Data2T>
  BufferAccess3dIter2C<Data1T,Data2T>::BufferAccess3dIter2C(const SizeBufferAccess3dC<Data1T> &pbufA,
                                                            const SizeBufferAccess3dC<Data2T> &pbufB,
                                                            SizeT size1,SizeT size2,SizeT size3
                                                            ) {
    First(pbufA.BufferAccess(),pbufA.ByteStride1(),pbufA.ByteStride2(),
          pbufB.BufferAccess(),pbufB.ByteStride1(),pbufB.ByteStride2(),
          size1,size2,size3);
  }
  //: Constructor.
  
  template<typename Data1T,typename Data2T,typename Data3T>
  BufferAccess3dIter3C<Data1T,Data2T,Data3T>::BufferAccess3dIter3C(const SizeBufferAccess3dC<Data1T> &pbufA,
                                                                   const SizeBufferAccess3dC<Data2T> &pbufB,
                                                                   const SizeBufferAccess3dC<Data3T> &pbufC,
                                                                   SizeT size1,SizeT size2,SizeT size3
                                                                   ) {
    First(pbufA.BufferAccess(),pbufA.ByteStride1(),pbufA.ByteStride2(),
          pbufB.BufferAccess(),pbufB.ByteStride1(),pbufB.ByteStride2(),
          pbufC.BufferAccess(),pbufC.ByteStride1(),pbufC.ByteStride2(),
          size1,size2,size3);
  }
  //: Constructor.
  

  template<class DataT>
  void SizeBufferAccess3dC<DataT>::Fill(const DataT &d) {
    for(BufferAccess3dIterC<DataT> it(*this);it;it++)
      *it = d;
  }
  
  template <class DataT>
  ostream & operator<<(ostream & s, const SizeBufferAccess3dC<DataT> & arr) {
    for(BufferAccess3dIterC<DataT> it(arr);it;) {
      s << *it;
      for(;it.Next();) 
	s << ' ' << *it;
      s << '\n';
    }    
    return s;
  }
  
  template <class DataT>
  istream & operator>>(istream & s, SizeBufferAccess3dC<DataT> & arr) {
    for(BufferAccess3dIterC<DataT> it(arr);it;it++) 
      s >> *it;
    return s;
  }
  
  template<class DataT>
  BinOStreamC &operator<<(BinOStreamC & s, const SizeBufferAccess3dC<DataT> & arr) {
    for(BufferAccess3dIterC<DataT> it(arr);it;it++)
      s << *it;
    return s;
  }
  
  template<class DataT>
  BinIStreamC &operator>>(BinIStreamC & s, SizeBufferAccess3dC<DataT> & arr) {
    for(BufferAccess3dIterC<DataT> it(arr);it;it++)
      s >> *it;
    return s;
  }
  
}

#endif
