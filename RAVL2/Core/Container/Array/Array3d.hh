// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ARRAY3D_HEADER
#define RAVL_ARRAY3D_HEADER 1
///////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Array/Array3d.hh"
//! lib=RavlCore
//! author="Radek Marik"
//! date="2/5/1993"
//! docentry="Ravl.API.Core.Arrays.3D"
//! example=exArray3d.cc
//! userlevel=Normal

#include "Ravl/RangeBufferAccess3d.hh"
#include "Ravl/Buffer3d.hh"
#include "Ravl/AttachedBuffer3d.hh"
#include "Ravl/Array2d.hh"
#include "Ravl/Index3d.hh"
#include "Ravl/IndexRange3d.hh"
#include "Ravl/BufferAccess3dIter.hh"
#include "Ravl/BufferAccess3dIter2.hh"
#include "Ravl/BufferAccess3dIter3.hh"
#include "Ravl/Types.hh"

namespace RavlN {
  
  template<class DataT> class Array1dC;
  template<class DataT> class Array2dC;
  template<class DataT> class Slice1dC;
  template<class DataT> class Slice1dIterC;

  //! userlevel=Basic
  //: 3 Dimensional array
  // The class Array3dC is a container of items which can be indexed
  // by 3-dimensional index.
  
  template <class DataT>
  class Array3dC
    : public RangeBufferAccess3dC<DataT>
  {
  public:
    Array3dC()
    {}
    //: Creates an empty 3D array.
    
    Array3dC(const SizeT &dim1,const SizeT &dim2, const SizeT &dim3)
      : m_data(dim1,dim2,dim3)
    { Attach(m_data,IndexRangeC(dim1),IndexRangeC(dim2),IndexRangeC(dim3)); }
    //: Creates 3D array with the range < <0,dim1-1>, <0,dim2-1>, <0,dim3-1> >
    
    Array3dC(IntT minI,IntT maxI,IntT minJ,IntT maxJ,IntT minK,IntT maxK);
    //: Creates 3D array with the range minRow to maxRow by minCol to maxCol.
    
    Array3dC(IndexC minI,IndexC maxI,IndexC minJ,IndexC maxJ,IndexC minK,IndexC maxK);
    //: Creates 3D array with the range minRow to maxRow by minCol to maxCol.
    
    Array3dC(const Index3dC & min, const Index3dC & max);
    //: Creates 3D array with the range < <min[0], max[0]>, <min[1], max[1]> , <min[3], max[3]> >.
    
    Array3dC(const IndexRangeC & range1, const IndexRangeC & range2, const IndexRangeC & range3)
      : m_data(range1.Size(),range2.Size(),range3.Size())
    { Attach(m_data,range1,range2,range3); }
    //: Creates 3D array with the range <rng1, rng2, rng3>
    
    Array3dC(const IndexRange3dC & frame)
      : m_data(frame)
    { Attach(m_data,frame);  }
    //: Create 3D array with the range covering indexes in 'frame'
    
    Array3dC(const BufferC<DataT> &data,const IndexRange3dC & frame)
      : m_data(AttachedBuffer3dC<DataT>(data,frame))
    { Attach(m_data,frame); }
    //: Create 3D array with the range covering indexes in 'rect' from data.
    // NB. It is the users responsibility to ensure that 'data' is
    // large enough to contain 'rect'.
    
    Array3dC(const Array3dC<DataT> &arr,const IndexRange3dC & frame)
      : RangeBufferAccess3dC<DataT> (arr,frame),
        m_data(arr.m_data)
    {}
    //: Create a sub array of 'arr' covering indexes 'rect'.
    
    Array3dC<DataT> Copy() const;
    //: Make a copy of the array.
    
    inline const Array3dC<DataT> & Array3d() const
    { return(*this); }
    //: access to the constant object
    
    inline Array3dC<DataT> & Array3d()
    { return(*this); }
    //: access to the object
    
    Array3dC<DataT> operator+(const Array3dC<DataT> & arr) const;
    //: Sums 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array3dC<DataT> operator-(const Array3dC<DataT> & arr) const;
    //: Subtracts 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array3dC<DataT> operator*(const Array3dC<DataT> & arr) const;
    //: Multiplies 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array3dC<DataT> operator/(const Array3dC<DataT> & arr) const;
    //: Divides 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array3dC<DataT> operator*(const DataT &number) const;
    //: Multiplies the array by the 'number'. 
    // The operator returns the result as a new array.
    
    Array3dC<DataT> operator/(const DataT &number) const;
    //: Divides all array items by the 'number'. 
    // The operator returns the result as a new array.
    
    Array3dC<DataT> operator+(const DataT &number) const;
    //: Adds 'number' to the array. 
    // The operator returns the result as a new array.
    
    Array3dC<DataT> operator-(const DataT &number) const;
    //: Subtracts 'number' from all array items. 
    // The operator  returns the result as a new array.
    
    const Array3dC<DataT> & operator+=(const Array3dC<DataT> & arr);
    //: Adds the 2nd array to this array.
    
    const Array3dC<DataT> & operator-=(const Array3dC<DataT> & arr);
    //: Subtracts the 2nd array from this array.
    
    const Array3dC<DataT> & operator*=(const Array3dC<DataT> & arr);
    //: Multiplies the 2nd array to this array.
    
    const Array3dC<DataT> & operator/=(const Array3dC<DataT> & arr);
    //: Divides the 2nd array from this array.
    
    const Array3dC<DataT> & operator+=(const DataT &number);
    //: Adds 'number' to all array items.
    
    const Array3dC<DataT> & operator-=(const DataT &number);
    //: Subtracts 'number' from all array items.
    
    const Array3dC<DataT> & operator*=(const DataT &number);
    //: Multiplies the array by the 'number'.
    
    const Array3dC<DataT> & operator/=(const DataT &number);
    //: Divides the array elements by the 'number'.
    
    Array2dC<DataT> Slice1(IndexC i);
    //: Take a slice across the first dimension of the 3d array.
    // Note this does NOT copy the data, any changes made to this slice
    // will be seen in the original 3d volume. 

    Array2dC<DataT> Slice2(IndexC j);
    //: Take a slice across the second dimension of the 3d array.
    // Note this does NOT copy the data, any changes made to this slice
    // will be seen in the original 3d volume. <p>
    // Note: This routine is slightly slower than Slice1 as it has to construct
    // a new access array.
    
    Buffer3dC<DataT> &Buffer()
    { return m_data; }
    //: Access the buffer holding underlying data.
    // Advanced users only.

    inline const IndexRangeC &Range1() const
    { return RangeBufferAccess3dC<DataT>::Range1(); }
    //: Range of first index.
    
    inline const IndexRangeC &Range2() const
    { return RangeBufferAccess3dC<DataT>::Range2(); }
    //: Range of second index.
    
    inline const IndexRangeC &Range3() const
    { return RangeBufferAccess3dC<DataT>::Range3(); }
    //: Range of third index.
    
  protected:    
    Buffer3dC<DataT> m_data; // Raw data stored in array.
  };
  
  
  template <class DataT>
  ostream & operator<<(ostream & s, const Array3dC<DataT> & arr);
  // Prints into the stream 's'
  
  template <class DataT>
  istream & operator>>(istream & s, Array3dC<DataT> & arr);
  // Reads the array from the stream 's'
  
  ////////////////////////////////////////////////////////////////////////////////
  
  
  template <class DataT>
  Array3dC<DataT>::Array3dC(IndexC minI,IndexC maxI,
			    IndexC minJ,IndexC maxJ,
			    IndexC minK,IndexC maxK)
    : m_data(IndexRangeC(minI,maxI).Size(),IndexRangeC(minJ,maxJ).Size(),IndexRangeC(minK,maxK).Size())
  {
    RavlAssert(minI <= maxI);
    RavlAssert(minJ <= maxJ);
    RavlAssert(minK <= maxK);
    Attach(m_data,IndexRangeC(minI,maxI),IndexRangeC(minJ,maxJ),IndexRangeC(minK,maxK));
  }
  
  template <class DataT>
  Array3dC<DataT>::Array3dC(IntT minI,IntT maxI,IntT minJ,IntT maxJ,IntT minK,IntT maxK) 
    : m_data(IndexRangeC(minI,maxI).Size(),IndexRangeC(minJ,maxJ).Size(),IndexRangeC(minK,maxK).Size())
  {
    RavlAssert(minI <= maxI);
    RavlAssert(minJ <= maxJ);
    RavlAssert(minK <= maxK);
    Attach(m_data,IndexRangeC(minI,maxI),IndexRangeC(minJ,maxJ),IndexRangeC(minK,maxK));
  }
  
  
  template <class DataT>
  Array3dC<DataT>::Array3dC(const Index3dC & min, const Index3dC & max)
    : m_data(IndexRangeC(min[0],max[0]).Size(),
	   IndexRangeC(min[1],max[1]).Size(),
	   IndexRangeC(min[2],max[2]).Size())
  { Attach(m_data,IndexRangeC(min[0],max[0]),IndexRangeC(min[1],max[1]),IndexRangeC(min[2],max[2])); }
  
  
  template <class DataT>
  Array3dC<DataT> 
  Array3dC<DataT>::Copy() const {
    Array3dC<DataT> ret(this->Frame());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,(*this),ret.Range1(),ret.Range2(),ret.Range3());it;it++)
      it.Data1() = it.Data2();
    return ret;
  }
    
  template <class DataT>
  ostream & operator<<(ostream & s, const Array3dC<DataT> & arr) {
    s << arr.Frame() << "\n";
    return s << ((const RangeBufferAccess3dC<DataT> &)arr);
  }
  
  
  template <class DataT>
  istream &operator>>(istream & s, Array3dC<DataT> & arr) {
    IndexRange3dC frame;
    s >> frame;
    arr = Array3dC<DataT>(frame);
    return s >> ((RangeBufferAccess3dC<DataT> &)arr);
  }
  
  
  template<class DataT>
  BinOStreamC &operator<<(BinOStreamC & s, const Array3dC<DataT> & arr) {
    s << arr.Range1() << arr.Range2() << arr.Range3();
    return s << ((const RangeBufferAccess3dC<DataT> &)arr);
  }
  
  template<class DataT>
  BinIStreamC &operator>>(BinIStreamC & s, Array3dC<DataT> & arr) {
    IndexRangeC rng1,rng2,rng3;
    s >> rng1 >> rng2 >> rng3;
    SizeT size = rng1.Size() * rng2.Size() * rng3.Size();
    if((size * sizeof(DataT)) > s.ArraySizeLimit() || size > s.ArraySizeLimit())
      throw ExceptionOutOfRangeC("Incoming array size exceeds limit for stream.");
    arr = Array3dC<DataT>(rng1,rng2,rng3);
    return s >> ((RangeBufferAccess3dC<DataT> &)arr);
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator+(const Array3dC<DataT> & arr) const {
    Array3dC<DataT> ret(this->Frame());
    for(BufferAccess3dIter3C<DataT,DataT,DataT> it(ret,*this,arr,ret.Range1(),ret.Range2(),ret.Range3());
	it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator-(const Array3dC<DataT> & arr) const {
    Array3dC<DataT> ret(this->Frame());
    for(BufferAccess3dIter3C<DataT,DataT,DataT> it(ret,*this,arr,ret.Range1(),ret.Range2(),ret.Range3());it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator*(const Array3dC<DataT> & arr) const {
    Array3dC<DataT> ret(this->Frame());
    for(BufferAccess3dIter3C<DataT,DataT,DataT> it(ret,*this,arr,ret.Range1(),ret.Range2(),ret.Range3());it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator/(const Array3dC<DataT> & arr) const {
    Array3dC<DataT> ret(this->Frame());
    for(BufferAccess3dIter3C<DataT,DataT,DataT> it(ret,*this,arr,ret.Range1(),ret.Range2(),ret.Range3());it;it++)
      it.Data1() = it.Data2() / it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator+(const DataT &number) const {
    Array3dC<DataT> ret(this->Frame());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,*this,ret.Range1(),ret.Range2(),ret.Range3());it;it++)
      it.Data1() = it.Data2() + number;
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator-(const DataT &number) const {
    Array3dC<DataT> ret(this->Frame());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,*this,ret.Range1(),ret.Range2(),ret.Range3());it;it++)
      it.Data1() = it.Data2() - number;
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator*(const DataT &number) const {
    Array3dC<DataT> ret(this->Frame());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,*this,ret.Range1(),ret.Range2(),ret.Range3());it;it++)
      it.Data1() = it.Data2() * number;
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator/(const DataT &number) const {
    Array3dC<DataT> ret(this->Frame());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,*this,ret.Range1(),ret.Range2(),ret.Range3());it;it++)
      it.Data1() = it.Data2() / number;
    return ret;
  }
    
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator+=(const Array3dC<DataT> & arr) {
    for(BufferAccess3dIter2C<DataT,DataT> it(*this,arr,this->Range1(),this->Range2(),this->Range3());it;it++)
      it.Data1() += it.Data2();
    return *this;
  }
  
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator-=(const Array3dC<DataT> & arr) {
    for(BufferAccess3dIter2C<DataT,DataT> it(*this,arr,
                                             this->Range1(),this->Range2(),this->Range3());it;it++)
      it.Data1() -= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator*=(const Array3dC<DataT> & arr) {
    for(BufferAccess3dIter2C<DataT,DataT> it(*this,arr,
                                             this->Range1(),this->Range2(),this->Range3());it;it++)
      it.Data1() *= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator/=(const Array3dC<DataT> & arr) {
    for(BufferAccess3dIter2C<DataT,DataT> it(*this,arr,
                                             this->Range1(),this->Range2(),this->Range3());it;it++)
      it.Data1() /= it.Data2();
    return *this;
  }
  
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator+=(const DataT &number) {
    for(BufferAccess3dIterC<DataT> it(*this);it;it++)
      it.Data1() += number;
    return *this;
  }
    
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator-=(const DataT &number) {
    for(BufferAccess3dIterC<DataT> it(*this);it;it++)
      it.Data1() -= number;
    return *this;
  }
  
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator*=(const DataT &number) {
    for(BufferAccess3dIterC<DataT> it(*this);it;it++)
      it.Data1() *= number;
    return *this;
  }
  
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator/=(const DataT &number) {
    for(BufferAccess3dIterC<DataT> it(*this);it;it++)
      it.Data() /= number;
    return *this;
  }
  
  template<class DataT>
  Array2dC<DataT> Array3dC<DataT>::Slice1(IndexC i)
  { return Array2dC<DataT>(m_data,(*this)[i]); }
  
  template<class DataT>
  Array2dC<DataT> Array3dC<DataT>::Slice2(IndexC j) {
    RavlAssert(Range2().Contains(j));
    DataT *start = ShiftPointerInBytes(this->ReferenceElm(),j.V() * this->ByteStride2());
    RangeBufferAccess2dC<DataT> rbf(start,Range1(),Range3(),this->ByteStride1());
    return Array2dC<DataT>(m_data,rbf);
  }
  
}
#endif

