// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SLICE1D_HEADER
#define RAVL_SLICE1D_HEADER 1
////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Advanced
//! file="Ravl/Core/Container/Buffer/Slice1d.hh"
//! lib=RavlCore
//! docentry="Ravl.API.Core.Arrays"
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/Buffer.hh"
#include "Ravl/Assert.hh"
#include "Ravl/IndexRange1d.hh"
#include "Ravl/RangeBufferAccess.hh"
#include "Ravl/SizeBufferAccess.hh"

//: Ravl namespace.

namespace RavlN {

  template<class DataT> class Slice1dIterC;
  template<class Data1T,class Data2T> class Slice1dIter2C;
  template<class Data1T,class Data2T,class Data3T> class Slice1dIter3C;
  
  //:  Slice through array
  // Slices are NOT simple arrays, they have an additional paramiter
  // 'stride' which allows them to access both rows and columns of
  // block matrixes equally.
  // This intended to support numerical types, operations
  // on the vector are implemented as would be expected
  
  template<class DataT>
  class Slice1dC {
  public:
    Slice1dC()
     : m_range(0,-1),
       m_stride(1),
       m_ref(0)
    {}
    //: Creates a zero length vector.
    
    Slice1dC(SizeT size)
      : m_range(0,size-1),
        m_stride(sizeof(DataT)),
        m_buffer(size)
    { m_ref = reinterpret_cast<char *>(m_buffer.ReferenceElm()); }
    //: Allocate a vector of size 'nsize'
    
    Slice1dC(const IndexRangeC &range)
      : m_range(range),
        m_stride(sizeof(DataT)),
        m_buffer(range.Size())
    { m_ref = reinterpret_cast<char *>(m_buffer.ReferenceElm() - range.Min().V()); }
    //: Allocate a Slice with a range of 'nrng'
    
    Slice1dC(BufferC<DataT> &buff,SizeT size,IntT byteOffset,IntT byteStride)
      : m_range(size),
        m_stride(byteStride),
        m_ref(reinterpret_cast<char *>(buff.ReferenceElm()) + byteOffset),
        m_buffer(buff)
    {
      RavlAssert((SizeT) Abs(byteStride) >= sizeof(DataT)); // Must be more than 1 element long.
      RavlAssert(((size-1) * m_stride + byteOffset) < (sizeof(DataT) * buff.Size())); // Check it fits.
    }
    //: Attach a vector to a buffer.
    // buff   - Buffer in which data is held.
    // size   - Number of elements in the slice.
    // off    - Offset in bytes into buffer of first element.
    // byteStride - distance in bytes between successive elements.
    // Element 0 is at 'off' in buffer, and use the given stride.

    Slice1dC(BufferC<DataT> &buff,DataT *refElm,SizeT size,IntT byteStride)
      : m_range(size),
        m_stride(byteStride),
        m_ref(reinterpret_cast<char *>(refElm)),
        m_buffer(buff)
    {
      RavlAssert((SizeT) Abs(byteStride) >= sizeof(DataT)); // Must be more than 1 element long.
      RavlAssert(((size-1) * m_stride + sizeof(DataT) * (refElm - m_buffer.ReferenceElm())) < (sizeof(DataT) * buff.Size())); // Check it fits.
    }
    //: Attach a vector to a buffer.
    // buff   - Buffer in which data is held.
    // size   - Number of elements in the slice.
    // refElm - Pointer to first element in the slice.
    // stride - distance between successive elements in slice.
    // Element 0 is at 'refElm' in buffer, and use the given stride.


    Slice1dC(BufferC<DataT> &buff,DataT *refElm,IndexRangeC range,IntT byteStride)
      : m_range(range),
        m_stride(byteStride),
        m_ref(reinterpret_cast<char *>(refElm)),
        m_buffer(buff)
    {
      RavlAssert(m_range.Min() <= m_range.Max());
      RavlAssert(((m_range.Min().V()) * m_stride + sizeof(DataT) * (refElm - m_buffer.ReferenceElm())) >= 0); // Check it fits.
      RavlAssert(((m_range.Max().V()) * m_stride + sizeof(DataT) * (refElm - m_buffer.ReferenceElm())) < (sizeof(DataT) * m_buffer.Size())); // Check it fits.
    }
    //: Attach a vector to a buffer.
    // buff   - Buffer in which data is held.
    // refElm - Pointer to element 0 in the slice. (even if its not in 'range')
    // range  - Range of indexes to map data to.
    // stride - distance between successive elements in slice.
    // Element '*refElm' is at index 0 in buffer, and use the given stride.
    
    SizeT Size() const
    { return m_range.Size(); }
    //: Size of vector.
    
    bool IsEmpty() const
    { return m_range.Size() <= 0; }
    //: Is slice empty ?
    
    Slice1dC Copy() const;
    //: Make copy of vector.
    
    void Fill(const DataT &val);
    //: Fill vector with value 'val'
    
    DataT &operator[](IndexC i) {
      RavlAssertMsg(m_range.Contains(i),"Slice1dC, Index out of range.");
      return *reinterpret_cast<DataT *>(m_ref + (i.V() * m_stride));
    }
    //: Access element i in vector.
    
    const DataT &operator[](IndexC i) const {
      RavlAssertMsg(m_range.Contains(i),"Slice1dC, Index out of range.");
      return *reinterpret_cast<const DataT *>(m_ref + (i.V() * m_stride));
    }
    //: Constant access to element i in vector.

    DataT &operator[](int i){
      RavlAssertMsg(m_range.Contains(i),"Slice1dC, Index out of range.");
      return *reinterpret_cast<DataT *>(m_ref + (i * m_stride));
    }
    //: Access element i in vector.
    
    const DataT &operator[](int i) const {
      RavlAssertMsg(m_range.Contains(i),"Slice1dC, Index out of range.");
      return *reinterpret_cast<const DataT *>(m_ref + (i * m_stride));
    }
    //: Constant access to element i in vector.
    
    DataT &First()
    { return *reinterpret_cast<DataT *>(m_ref + (m_range.Min().V() * m_stride)); }
    //: Access first element in the vector.
    // Not the results of this function is undefined if Size() is zero.
    
    const DataT &First() const
    { return *reinterpret_cast<const DataT *>(m_ref + (m_range.Min().V() * m_stride)); }
    //: Access first element in the vector.
    // Not the results of this function is undefined if Size() is zero.
    
    DataT &Last()
    { return *reinterpret_cast<DataT *>(m_ref + (m_range.Max().V() * m_stride)); }
    //: Access last element in vector.
    
    const DataT &Last() const
    { return *reinterpret_cast<const DataT *>(m_ref + (m_range.Max().V() * m_stride)); }
    //: Access last element in vector.

    IntT ByteStride() const
    { return m_stride; }
    //: Access stride of vector in bytes.
    
    bool IsContinuous() const
    { return m_stride == static_cast<IntT>(sizeof(DataT)); }
    //: Test if the elements in the slice are continuous in memory.

    Slice1dC<DataT> operator+(const Slice1dC<DataT>& b) const;
    //: Returns the sum of two vectors.
    
    Slice1dC<DataT> operator-(const Slice1dC<DataT>& b) const;
    //: Returns the diference between this vector and the vector 'b'.
    
    Slice1dC<DataT> operator*(const DataT &alfa) const;
    //: Returns the multiplication of this vector by the scalar 'alpha'.
  
    Slice1dC<DataT> operator*(const Slice1dC<DataT> & b) const;
    //: Returns the vector whose elements are the results of multiplication
    //: of this vector by the vector 'b' element by element.
    
    Slice1dC<DataT> & operator+=(const Slice1dC<DataT> & b);
    //: add the vector 'b' to the vector
    
    Slice1dC<DataT> & operator+=(const DataT &alpha);
    //: add the scalar to each element of the vector
    
    Slice1dC<DataT> & operator-=(const Slice1dC<DataT> & b);
    //: subtract the vector 'b' from the vector
    
    Slice1dC<DataT> & operator-=(const DataT &alpha);
    //: subtract the scalar from each element of the vector
    
    Slice1dC<DataT> & operator*=(const DataT &alpha);
    //: multiply the vector by the scalar 'alpha'
    
    Slice1dC<DataT> & operator/=(const DataT &alpha);
    //: divide the vector by the scalar 'alpha'
    
    Slice1dC<DataT> & operator/=(const Slice1dC<DataT> &vec);
    //: (*this)[index] = (*this)[index]/vec[index]
    
    DataT Sum() const;      
    //: Returns the sum all elements of the vector.
    
    DataT Product() const;      
    //: Returns the product of all elements of the vector.
    
    DataT SumOfSqr() const;
    //: Returns the sum of the squares of all the elements of the vector.
    
    Slice1dC<DataT> & Reciprocal();
    //: All elements of the vector are changed to their reciprocal values. 
    //: It is assumed that all elements of the vector differs from zero.
    
    RealT Modulus() const
    { return Sqrt(SumOfSqr()); } 
    //: Returns the modulus of the vector.
    // The Sqrt(SumOfSqr()).
    
    DataT Dot(const Slice1dC<DataT> & v) const;         
    //: scalar product of vectors    
    
    DataT TMul(const Slice1dC<DataT> & v) const
    { return Dot(v); }
    //: An alias for dot product.
    
    BufferC<DataT> &Buffer()
    { return m_buffer; }
    //: Access the raw buffer 
    
    const BufferC<DataT> &Buffer() const
    { return m_buffer; }
    //: Access the raw buffer.
    
    const IndexRangeC &Range() const
    { return m_range; }
    //: Access range of valid indexs.
    
    const IndexC &IMin() const
    { return m_range.Min(); }
    //: Get minimum index.
    
    const IndexC &IMax() const
    { return m_range.Max(); }
    //: Get maximum index.
    
    bool Contains(const IndexC &i) const
    { return m_range.Contains(i); }
    //: Test if slice contains index i.
    
    DataT &ReferenceElm()
    { return *reinterpret_cast<DataT *>(m_ref); }
    //: Access refrence element.
    // Advanced users only.
    
    const DataT &ReferenceElm() const
    { return *reinterpret_cast<DataT *>(m_ref); }
    //: Access refrence element.
    // Advanced users only.
    
    void CopyFrom(const Slice1dC<DataT> &data);
    //: Copy 'data' into this slice.
    // Both must be the same length.
    
    void CopyFrom(const RangeBufferAccessC<DataT> &data);
    //: Copy 'data' into this slice.
    // Both must be the same length.
    
  protected:
    IndexRangeC m_range;// Range of valid index's
    IntT m_stride;    // Stride of data.
    char *m_ref;     // Ptr to element 0
    BufferC<DataT> m_buffer;
  };

  template<class DataT>
  ostream &operator<<(ostream &out,const Slice1dC<DataT> &dat);
  //: Write to stream.
  
  template<class DataT>
  istream &operator>>(istream &out,Slice1dC<DataT> &dat);
  //: Read from stream.

}
//// Slice1dC Impl ////////////////////////////////////////////////////////////////////

#include "Ravl/Slice1dIter.hh"
#include "Ravl/Slice1dIter2.hh"
#include "Ravl/Slice1dIter3.hh"

//: Ravl namespace.

namespace RavlN {
  
  
  template<class DataT>
  Slice1dC<DataT> Slice1dC<DataT>::Copy() const {
    Slice1dC<DataT> ret(Size());
    for(Slice1dIter2C<DataT,DataT> it(ret,*this);it;it++)
      it.Data1() = it.Data2();
    return ret;
  }
  
  template<class DataT>
  void Slice1dC<DataT>::Fill(const DataT &val) {
    for(Slice1dIterC<DataT> it(*this);it;it++)
      *it = val;
  }
  
  template<class DataT>
  Slice1dC<DataT> Slice1dC<DataT>::operator+(const Slice1dC<DataT>& b) const {
    Slice1dC<DataT> ret(Size());
    for(Slice1dIter3C<DataT,DataT,DataT> it(ret,*this,b);it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }

  template<class DataT>
  Slice1dC<DataT> Slice1dC<DataT>::operator-(const Slice1dC<DataT>& b) const {
    Slice1dC<DataT> ret(Size());
    for(Slice1dIter3C<DataT,DataT,DataT> it(ret,*this,b);it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;  
  }
  
  template<class DataT>
  Slice1dC<DataT> Slice1dC<DataT>::operator*(const DataT &alpha) const {
    Slice1dC<DataT> ret(Size());
    for(Slice1dIter2C<DataT,DataT> it(ret,*this);it;it++)
      it.Data1() = it.Data2() * alpha;
    return ret;
  }
  
  template<class DataT>
  Slice1dC<DataT> Slice1dC<DataT>::operator*(const Slice1dC<DataT> & b) const {
    Slice1dC<DataT> ret(Size());
    for(Slice1dIter3C<DataT,DataT,DataT> it(ret,*this,b);it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataT>
  Slice1dC<DataT> &Slice1dC<DataT>::operator+=(const Slice1dC<DataT> & b) {
    for(Slice1dIter2C<DataT,DataT> it(*this,b);it;it++)
      it.Data1() += it.Data2();
    return (*this);
  }
  
  template<class DataT>
  Slice1dC<DataT> &Slice1dC<DataT>::operator+=(const DataT &alpha) {
    for(Slice1dIterC<DataT> it(*this);it;it++)
      *it += alpha;
    return (*this);
  }
  
  template<class DataT>
  Slice1dC<DataT> &Slice1dC<DataT>::operator-=(const Slice1dC<DataT> & b) {
    for(Slice1dIter2C<DataT,DataT> it(*this,b);it;it++)
      it.Data1() -= it.Data2();
    return (*this);
  }
  
  template<class DataT>
  Slice1dC<DataT> &Slice1dC<DataT>::operator-=(const DataT &alpha) {
    for(Slice1dIterC<DataT> it(*this);it;it++)
      *it -= alpha;
    return (*this);  
  }
  
  template<class DataT>
  Slice1dC<DataT> &Slice1dC<DataT>::operator*=(const DataT &alpha) {
    for(Slice1dIterC<DataT> it(*this);it;it++)
      *it *= alpha;
    return (*this);
  }
  
  template<class DataT>
  Slice1dC<DataT> &Slice1dC<DataT>::operator/=(const DataT &alpha) {
    for(Slice1dIterC<DataT> it(*this);it;it++)
      *it /= alpha;
    return (*this);  
  }
  
  template<class DataT>
  Slice1dC<DataT> &Slice1dC<DataT>::operator/=(const Slice1dC<DataT> &vec) {
    for(Slice1dIter2C<DataT,DataT> it(*this,vec);it;it++)
      it.Data1() /= it.Data2();
    return (*this);
  }
  
  template<class DataT>
  DataT Slice1dC<DataT>::Sum() const {
    Slice1dIterC<DataT> it(*this);
    if(!it) return 0;
    DataT sum = StdCopy(*it);
    for(it++;it;it++)
      sum += *it;
    return sum;
  }
  
  template<class DataT>
  DataT Slice1dC<DataT>::Product() const  {
    Slice1dIterC<DataT> it(*this);
    if(!it) return 1; // Or throw an exception ?
    DataT prod = StdCopy(*it);
    for(it++;it;it++)
      prod *= *it;
    return prod;
  }

  //: Returns the sum of the squares of all the elements of the vector.
  
  template<class DataT>  
  DataT Slice1dC<DataT>::SumOfSqr() const {
    DataT ret;
    Slice1dIterC<DataT> it(*this);
    if(!it) {
      SetZero(ret);
      return ret;
    }
    ret = Sqr(*it);
    for(it++;it;it++)
      ret += Sqr(*it);
    return ret;
  }
  
  template<class DataT>
  Slice1dC<DataT> & 
  Slice1dC<DataT>::Reciprocal() {
    for(Slice1dIterC<DataT> it(*this);it;it++)
      *it = 1/ *it;
    return *this;
  }
  
  template<class DataT>
  DataT Slice1dC<DataT>::Dot(const Slice1dC<DataT> & v) const {
    DataT sum;
    Slice1dIter2C<DataT,DataT> it(*this,v);
    if(!it) {
      SetZero(sum);
      return sum;
    }
    sum = it.Data1() * it.Data2();
    for(it++;it;it++)
      sum += it.Data1() * it.Data2();
    return sum;  
  }
  
  template<class DataT>
  void Slice1dC<DataT>::CopyFrom(const Slice1dC<DataT> &data) {
    RavlAssert(Size() == data.Size());
    for(Slice1dIter2C<DataT,DataT> it(*this,data);it;it++)
      it.Data1() = it.Data2();
  }
  
  template<class DataT>
  void Slice1dC<DataT>::CopyFrom(const RangeBufferAccessC<DataT> &data) {
    RavlAssert(Size() == data.Size());
    if(Size() == 0)
      return ;
    const DataT *at = &(data[data.IMin()]);
    for(Slice1dIterC<DataT> it(*this);it;it++,at++)
      *it = *at;
  }
  
  template<class DataT>
  void RangeBufferAccessC<DataT>::CopyFrom(const Slice1dC<DataT> &slice) {
    RavlAssert(Size() == slice.Size());
    if(Size() == 0)
      return ;
    DataT *at = &((*this)[IMin()]);
    for(Slice1dIterC<DataT> it(slice);it;it++,at++)
      *at = *it;
  }

  template<class DataT>
  void SizeBufferAccessC<DataT>::CopyFrom(const Slice1dC<DataT> &slice) {
    RavlAssert(Size() == slice.Size());
    if(Size() == 0)
      return ;
    DataT *at = &((*this)[0]);
    for(Slice1dIterC<DataT> it(slice);it;it++,at++)
      *at = *it;
  }
  
  template<class DataT>
  ostream &operator<<(ostream &strm,const Slice1dC<DataT> &dat) {
    strm << dat.Range() << "\n";
    for(Slice1dIterC<DataT> it(dat);it;it++)
      strm << *it << " ";
    return strm;
  }
  
  template<class DataT>
  istream &operator>>(istream &strm,Slice1dC<DataT> &dat) {
    IndexRangeC s;
    strm >> s;
    Slice1dC<DataT> tmp(s);
    for(Slice1dIterC<DataT> it(tmp);it;it++)
      strm >> *it;
    dat = tmp;
    return strm;
  }
  
  
}

#endif
