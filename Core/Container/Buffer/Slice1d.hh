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
//! docentry="Ravl.Core.Arrays"
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/Buffer.hh"
#include "Ravl/Assert.hh"
#include "Ravl/IndexRange1d.hh"

//: Ravl namespace.

namespace RavlN {

  template<class DataT> class Slice1dIterC;
  template<class Data1T,class Data2T> class Slice1dIter2C;
  template<class Data1T,class Data2T,class Data3T> class Slice1dIter3C;
  
  //:  Slice through array
  // Slices are NOT simple arrays, they have an additional paramiter
  // 'stride' which allows them to access both rows and columbs of
  // block matrixes equally.
  // This intended to support numerical types, operations
  // on the vector are implemented as would be expected
  
  template<class DataT>
  class Slice1dC {
  public:
    Slice1dC();
    //: Creates a zero length vector.
    
    Slice1dC(SizeT nsize);
    //: Allocate a vector of size 'nsize'
    
    Slice1dC(const IndexRangeC &nrng);
    //: Allocate a Slice with a range of 'nrng'
    
    Slice1dC(BufferC<DataT> &buff,SizeT size,UIntT off,IntT stride = 1);
    //: Attach a vector to a buffer.
    // size   - Number of elements in the slice.
    // buff   - Buffer in which data is held.
    // off    - Offset into buffer of first element.
    // stride - distance between successive elements in slice.
    // Element 0 is at 'off' in buffer, and use the given stride.

    Slice1dC(BufferC<DataT> &buff,DataT *refElm,SizeT size,IntT stride = 1);
    //: Attach a vector to a buffer.
    // size   - Number of elements in the slice.
    // buff   - Buffer in which data is held.
    // elm    - Refrence to first element in the slice.
    // stride - distance between successive elements in slice.
    // Element 0 is at 'off' in buffer, and use the given stride.
    
    SizeT Size() const
      { return rng.Size(); }
    //: Size of vector.
    
    Slice1dC Copy() const;
    //: Make copy of vector.
    
    void Fill(const DataT &val);
    //: Fill vector with value 'val'
    
    DataT &operator[](IndexC i);
    //: Access element i in vector.
    
    const DataT &operator[](IndexC i) const;
    //: Constant access to element i in vector.
    
    DataT &First()
      { return ref[0]; }
    //: Access first element in the vector.
    // Not the results of this function is undefined if Size() is zero.
    
    const DataT &First() const
      { return ref[0]; }
    //: Access first element in the vector.
    // Not the results of this function is undefined if Size() is zero.
    
    DataT &Last()
      { return ref[stride * (size-1)]; }
    //: Access last element in vector.
    
    const DataT &Last() const
      { return ref[stride * (size-1)]; }
    //: Access last element in vector.

    IntT Stride() const
      { return stride; }
    //: Access stride of vector.
    
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
    
    DataT Modulus() const
      { return Sqrt(SumOfSqr()); } 
    //: Returns the modulus of the vector.
    // The Sqrt(SumOfSqr()).

    DataT TMul(const Slice1dC<DataT> & b) const;
    //: multiplication 'DataT' = (*this).T() * b
    
    DataT Dot(const Slice1dC<DataT> & v) const;         
    //: scalar product of vectors    

    BufferC<DataT> &Buffer()
      { return buffer; }
    //: Access the raw buffer 
    
    const BufferC<DataT> &Buffer() const
      { return buffer; }
    //: Access the raw buffer.
    
  protected:
    IndexRangeC rng;// Range of valid index's
    IntT stride;    // Stride of data.
    DataT *ref;     // Ptr to element 0
    BufferC<DataT> buffer;
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
  Slice1dC<DataT>::Slice1dC()
    : rng(0,-1),
      stride(1),
      ref(0)
  {}
  
  template<class DataT>
  Slice1dC<DataT>::Slice1dC(BufferC<DataT> &buff,SizeT nsize,UIntT noff,IntT nstride) 
    : rng(nsize),
      stride(nstride),
      ref(&(buff.ReferenceElm()[noff])),
      buffer(buff)
  { 
    RavlAssert(((nsize-1) * stride + noff) < buff.Size()); // Check it fits.
  }

  template<class DataT>
  Slice1dC<DataT>::Slice1dC(BufferC<DataT> &buff,DataT *refElm,SizeT nsize,IntT nstride ) 
    : rng(nsize),
      stride(nstride),
      ref(refElm),
      buffer(buff)
  {
    UIntT noff = refElm - buffer.ReferenceElm();
    RavlAssert(((nsize-1) * stride + noff) < buff.Size()); // Check it fits.    
  }
								       
    //: Attach a vector to a buffer.
    // size   - Number of elements in the slice.
    // buff   - Buffer in which data is held.
    // elm    - Refrence to first element in the slice.
    // stride - distance between successive elements in slice.
    // Element 0 is at 'off' in buffer, and use the given stride.
  
  template<class DataT>
  Slice1dC<DataT>::Slice1dC(SizeT nsize) 
    : rng(nsize),
      stride(1),
      buffer(nsize)
  { ref = buffer.ReferenceElm(); }
  
  
  template<class DataT>
  Slice1dC<DataT>::Slice1dC(const IndexRangeC &nrng)
    : rng(nrng),
      stride(1),
      buffer(nrng.Size())
  { ref = buffer.ReferenceElm()[-nrng.Min()]; }
  
  template<class DataT>
  DataT &Slice1dC<DataT>::operator[](IndexC i) { 
    RavlAssertMsg(rng.Contains(i),"Slice1dC, Index out of range.");
    return ref[i.V() * stride]; 
  }
  
  template<class DataT>
  const DataT &Slice1dC<DataT>::operator[](IndexC i) const { 
    RavlAssertMsg(rng.Contains(i),"Slice1dC, Index out of range.");
    return ref[i.V() * stride]; 
  }

  template<class DataT>
  Slice1dC<DataT> Slice1dC<DataT>::Copy() const {
    Slice1dC<DataT> ret(Size());
    for(Slice1dIter2C<DataT,DataT> it(ret,*this);it;it++)
      it[0] = it[1];
    return ret;
  }
  
  template<class DataT>
  void Slice1dC<DataT>::Fill(const DataT &val) {
    for(Slice1dIterC<DataT> it(*this);it;it++)
      *it = val;
  }
  
  template<class DataT>
  Slice1dC<DataT>
  Slice1dC<DataT>::operator+(const Slice1dC<DataT>& b) const {
    Slice1dC<DataT> ret(Size());
    for(Slice1dIter3C<DataT,DataT,DataT> it(ret,*this,b);it;it++)
      it[0] = it[1] + it[2];
    return ret;
  }

  template<class DataT>
  Slice1dC<DataT> 
  Slice1dC<DataT>::operator-(const Slice1dC<DataT>& b) const {
    Slice1dC<DataT> ret(Size());
    for(Slice1dIter3C<DataT,DataT,DataT> it(ret,*this,b);it;it++)
      it[0] = it[1] - it[2];
    return ret;  
  }
  
  template<class DataT>
  Slice1dC<DataT> 
  Slice1dC<DataT>::operator*(const DataT &alpha) const {
    Slice1dC<DataT> ret(Size());
    for(Slice1dIter2C<DataT,DataT> it(ret,*this);it;it++)
      it[0] = it[1] * alpha;
    return ret;
  }
  
  template<class DataT>
  Slice1dC<DataT> 
  Slice1dC<DataT>::operator*(const Slice1dC<DataT> & b) const {
    Slice1dC<DataT> ret(Size());
    for(Slice1dIter3C<DataT,DataT,DataT> it(ret,*this,b);it;it++)
      it[0] = it[1] * it[2];
    return ret;
  }
  
  template<class DataT>
  Slice1dC<DataT> & 
  Slice1dC<DataT>::operator+=(const Slice1dC<DataT> & b) {
    for(Slice1dIter2C<DataT,DataT> it(*this,b);it;it++)
      it[0] += it[1];
    return (*this);
  }
  
  template<class DataT>
  Slice1dC<DataT> & 
  Slice1dC<DataT>::operator+=(const DataT &alpha) {
    for(Slice1dIterC<DataT> it(*this);it;it++)
      *it += alpha;
    return (*this);
  }
  
  template<class DataT>
  Slice1dC<DataT> & 
  Slice1dC<DataT>::operator-=(const Slice1dC<DataT> & b) {
    for(Slice1dIter2C<DataT,DataT> it(*this,b);it;it++)
      it[0] -= it[1];
    return (*this);
  }
  
  template<class DataT>
  Slice1dC<DataT> & 
  Slice1dC<DataT>::operator-=(const DataT &alpha) {
    for(Slice1dIterC<DataT> it(*this);it;it++)
      *it -= alpha;
    return (*this);  
  }
  
  template<class DataT>
  Slice1dC<DataT> & 
  Slice1dC<DataT>::operator*=(const DataT &alpha) {
    for(Slice1dIterC<DataT> it(*this);it;it++)
      *it *= alpha;
    return (*this);
  }
  
  template<class DataT>
  Slice1dC<DataT> & 
  Slice1dC<DataT>::operator/=(const DataT &alpha) {
    for(Slice1dIterC<DataT> it(*this);it;it++)
      *it /= alpha;
    return (*this);  
  }
  
  template<class DataT>
  Slice1dC<DataT> & 
  Slice1dC<DataT>::operator/=(const Slice1dC<DataT> &vec) {
    for(Slice1dIter2C<DataT,DataT> it(*this,b);it;it++)
      it[0] /= it[1];
    return (*this);
  }
  
  template<class DataT>
  DataT 
  Slice1dC<DataT>::Sum() const {
    Slice1dIterC<DataT> it(*this);
    if(!it)
      return 0;
    DataT sum = *it;
    it++;
    for(;it;it++)
      sum += *it;
    return sum;
  }
  
  template<class DataT>
  DataT Slice1dC<DataT>::Product() const  {
    Slice1dIterC<DataT> it(*this);
    if(!it)
      return 1; // Or throw an exception ?
    DataT prod = *it;
    it++;
    for(;it;it++)
      prod *= *it;
    return prod;
  }

  //: Returns the sum of the squares of all the elements of the vector.
  
  template<class DataT>  
  DataT Slice1dC<DataT>::SumOfSqr() const {
    DataT ret;
    SetToZero(ret);
    for(Slice1dIterC<DataT> it(*this);it;it++)
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
  DataT 
  Slice1dC<DataT>::TMul(const Slice1dC<DataT> & b) const {
    DataT sum = 0;
    for(Slice1dIter2C<DataT,DataT> it(*this,b);it;it++)
      sum += it[0] * it[1];
    return (*this);
  }
  
  template<class DataT>
  DataT 
  Slice1dC<DataT>::Dot(const Slice1dC<DataT> & v) const {
    DataT sum = 0;
    for(Slice1dIter2C<DataT,DataT> it(*this,v);it;it++)
      sum += it[0] * it[1];
    return (*this);  
  }

  template<class DataT>
  ostream &operator<<(ostream &strm,const Slice1dC<DataT> &dat) {
    strm << dat.Size() << "\n";
    for(Slice1dIterC<DataT> it(dat);it;it++)
      strm << *it << " ";
    return strm;
  }
  
  template<class DataT>
  istream &operator>>(istream &strm,Slice1dC<DataT> &dat) {
    UIntT s;
    strm >> s;
    Slice1dC<DataT> tmp(s);
    for(Slice1dIterC<DataT> it(tmp);it;it++)
      strm >> *it;
    dat = tmp;
    return strm;
  }
  
  
}

#endif
