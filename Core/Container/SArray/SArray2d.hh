// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SARRAY2D_HEADER
#define RAVL_SARRAY2D_HEADER 1
/////////////////////////////////////////////////////
//! userlevel=Normal
//! docentry="Ravl.Core.Arrays.2D"
//! rcsid="$Id$"
//! file="Ravl/Core/Container/SArray/SArray2d.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="10/09/98"

#include "Ravl/SBfAcc2d.hh"
#include "Ravl/Buffer2d.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/BfAcc2Iter.hh"
#include "Ravl/BfAcc2Iter2.hh"
#include "Ravl/BfAcc2Iter3.hh"

namespace RavlN {
  
  template<class DataT> class SArray1dC;
  template<class DataT> class Array2dC;
  template<class DataT> class SArray2dIterC;
  template<class DataT> class Slice1dC;
  template<class DataT> class Slice1dIterC;

  //! userlevel=Advanced  
  //: Simple 2 dimentional array.
  
  template<class DataT>
  class SArray2dC 
    : public SizeBufferAccess2dC<DataT>
  {
  public:
    typedef DataT ElementT;
    //: Allow function templates to find type of array.
    
    typedef SArray2dIterC<DataT> IteratorT;
    //: Type of iterator.
    
    inline SArray2dC()
    {}
    //: Default constructor.
    
    SArray2dC(SizeT dim1,SizeT dim2);
    //: Constructor.
    
    SArray2dC(const BufferC<DataT> & bf, SizeT size1,SizeT size2,SizeT startOffset = 0,SizeT stride = 0);
    //: Constructor using the buffer 'bf'. 
    // This can be used, for example to view a 1d array, as a 2d array.
    // startOffset is the location in the buffer to use as 0,0.
    // If stride is set to zero, size2 is used.
    
    SArray2dC<DataT> Copy() const;
    //: Copy array.
    
    // Special operations
    // -----------------
    
    Buffer2dC<DataT> &Buffer() 
    { return data; }
    //: Access base data buffer.
    // Experts only!
    
    const Buffer2dC<DataT> &Buffer() const
    { return data; }
    //: Constant access base data buffer.
    // Experts only!

    SArray2dC<DataT> operator+(const SArray2dC<DataT> & arr) const;
    // Sums 2 numerical arrays. The operator returns the result as a new array.
    
    SArray2dC<DataT> operator-(const SArray2dC<DataT> & arr) const;
    // Subtracts 2 numerical arrays. The operator returns
    // the result as a new array.
    
    SArray2dC<DataT> operator*(const SArray2dC<DataT> & arr) const;
    // Mutliplies 2 numerical arrays. The operator returns the result as a new array.
    
    SArray2dC<DataT> operator/(const SArray2dC<DataT> & arr) const;
    // Devides 2 numerical arrays. The operator returns
    // the result as a new array.
    
    SArray2dC<DataT> operator*(const DataT &number) const;
    // Multiplys the array by the 'number'. The operator
    // returns the result as a new array.
    
    SArray2dC<DataT> operator/(const DataT &number) const;
    // Divides all array items by the 'number'. The operator 
    // returns the result as a new array.
    
    SArray2dC<DataT> operator+(const DataT &number) const;
    // Adds 'number' to the array. The operator
    // returns the result as a new array.
    
    SArray2dC<DataT> operator-(const DataT &number) const;
    // Subtracts 'number' from all array items. The operator 
    // returns the result as a new array.
    
    const SArray2dC<DataT> & operator+=(const SArray2dC<DataT> & arr);
    // Adds the 2nd array to this array.
    
    const SArray2dC<DataT> & operator-=(const SArray2dC<DataT> & arr);
    // Subtracts the 2nd array from this array.
    
    const SArray2dC<DataT> & operator*=(const SArray2dC<DataT> & arr);
    // Multiplies the 2nd array to this array.
    
    const SArray2dC<DataT> & operator/=(const SArray2dC<DataT> & arr);
    // Divides the 2nd array from this array.
    
    const SArray2dC<DataT> & operator+=(const DataT &number);
    // Adds 'number' to all array items.
    
    const SArray2dC<DataT> & operator-=(const DataT &number);
    // Subtracts 'number' from all array items.
    
    const SArray2dC<DataT> & operator*=(const DataT &number);
    // Multiplies the array by the 'number'.
    
    const SArray2dC<DataT> & operator/=(const DataT &number);
    // Divides the array elements by the 'number'.
    
    DataT SumSqr() const;
    //: Calculate the sum of the squares of all the elements in the array
    
    Slice1dC<DataT> Diagonal() {
      return Slice1dC<DataT>(data.Data(),
			     &((*this)[0][0]),
			     Min(Size1(),Size2()),
			     Stride()+1);
    }
    //: Take a slice along the diagonal of the array.
    
    SArray1dC<DataT> SliceRow(IndexC i)
    { return SArray1dC<DataT>(data.Data(),(*this)[i]); }
    //: Access row as 1d array.
    // NB. Changes made to the slice will also affect this array!
    
    Slice1dC<DataT> SliceColumn(IndexC i) { 
      return Slice1dC<DataT>(data.Data(),
			     &((*this)[0][i]),
			     Size1(),
			     Stride());
    }
    //: Access columb as 1d slice.
    // NB. Changes made to the slice will also affect this array!
    
    void SetColumn(IndexC i,const SArray1dC<DataT> &val);
    //: Set the values in the column i to those in 'val'.
    // 'val' must have a size equal to the number of rows.
    
    void SetRow(IndexC i,const SArray1dC<DataT> &val);
    //: Set the values in the row i to those in 'val'.
    // 'val' must have a size equal to the number of columns
    
  protected:
    SArray2dC(Buffer2dC<DataT> & bf, 
	      const BufferAccessC<BufferAccessC<DataT> > &ab,
	      SizeT dim1,SizeT dim2)
      : SizeBufferAccess2dC<DataT>(ab,dim1,dim2),
	data(bf)
    {}
    //: Construct from a buffer, and an existing buffer access.
    
    void BuildAccess(UIntT offset = 0,UIntT stride = 0);
    
    Buffer2dC<DataT> data; // Handle to data.
    
    friend class Array2dC<DataT>;
  };
  
  template <class DataT>
  ostream & operator<<(ostream & s, const SArray2dC<DataT> & arr) {
    s << "0 " <<  (arr.Size1()-1) << " 0 " << (arr.Size2()-1) << "\n";
    s << ((SizeBufferAccess2dC<DataT> &) arr);
    return s;
  }
  // Prints into the stream 's'
  
  template <class DataT>
  istream & operator>>(istream & s, SArray2dC<DataT> & arr) {
    SizeT size1,size2,x1,x2;
    s >> x1 >> size1 >> x2 >> size2;
    RavlAssert(x1 == 0 && x2 == 0);  // Only accept arrays starting at origin.
    arr = SArray2dC<DataT>(size1+1,size2+1);
    s >> ((SizeBufferAccess2dC<DataT> &) arr);
    return s;
  }
  // Reads the array from the stream 's'
  
  template<class DataT>
  BinOStreamC &operator<<(BinOStreamC & s, const SArray2dC<DataT> & arr) {
    SizeT x = 0;
    s << x << (arr.Size1()-1) << x << (arr.Size2()-1);
    s << ((SizeBufferAccess2dC<DataT> &) arr);
    return s;
  }

  template<class DataT>
  BinIStreamC &operator>>(BinIStreamC & s, SArray2dC<DataT> & arr) {
    SizeT size1,size2,x1,x2;
    s >> size1 >> x1 >> size2 >> x2;
    RavlAssert(x1 == 0 && x2 == 0); // Only accept arrays starting at origin.
    arr = SArray2dC<DataT>(size1,size2);
    return s >> ((SizeBufferAccess2dC<DataT> &) arr);
  }
  
  /////////////////////////////////////////////////////

  template<class DataT>
  void SArray2dC<DataT>::BuildAccess(UIntT offset,UIntT stride) {
    Attach(data);
    if(stride == 0)
      stride = size2;
    DataT *at = data.Data().ReferenceElm() + offset;
    for(BufferAccessIterC<BufferAccessC<DataT> > it(*this);
	it;it++,at += stride)
      *it = BufferAccessC<DataT>(at);
  }
  
  template<class DataT>
  SArray2dC<DataT>::SArray2dC(SizeT nsize1,SizeT nsize2)
    : SizeBufferAccess2dC<DataT>(nsize2),
      data(nsize1,nsize2)
  { BuildAccess(); }
  
  template<class DataT>
  SArray2dC<DataT>::SArray2dC(const BufferC<DataT> & bf, SizeT size1,SizeT nsize2,SizeT startOffset,SizeT stride)
    : SizeBufferAccess2dC<DataT>(nsize2),
      data(bf,size1)
  { BuildAccess(startOffset,stride); }
  
  template<class DataT>
  SArray2dC<DataT> 
  SArray2dC<DataT>::Copy() const {
    SArray2dC<DataT> newun(Size1(),size2); // Allocate new array.
    for(BufferAccess2dIter2C<DataT,DataT > it(*this,size2,
					      newun,size2);
	it;it++)
      it.Data2() = it.Data1();
    return newun;
  }
  
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator+(const SArray2dC<DataT> & arr) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,size2,
						   *this,size2,
						   arr,arr.Size2());
	it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator-(const SArray2dC<DataT> & arr) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,size2,*this,size2,arr,arr.Size2());it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator*(const SArray2dC<DataT> & arr) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,size2,*this,size2,arr,arr.Size2());it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator/(const SArray2dC<DataT> & arr) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,size2,*this,size2,arr,arr.Size2());it;it++)
      it.Data1() = it.Data2() / it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator+(const DataT &number) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,size2,*this,Size2());it;it++)
      it.Data1() = it.Data2() + number;
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator-(const DataT &number) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,size2,*this,Size2());it;it++)
      it.Data1() = it.Data2() - number;
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator*(const DataT &number) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,size2,*this,Size2());it;it++)
      it.Data1() = it.Data2() * number;
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator/(const DataT &number) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,size2,*this,Size2());it;it++)
      it.Data1() = it.Data2() / number;
    return ret;
  }
    
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator+=(const SArray2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,size2,arr,arr.Size2());it;it++)
      it.Data1() += it.Data2();
    return *this;
  }
  
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator-=(const SArray2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,size2,arr,arr.Size2());it;it++)
      it.Data1() -= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator*=(const SArray2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,size2,arr,arr.Size2());it;it++)
      it.Data1() *= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator/=(const SArray2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,size2,arr,arr.Size2());it;it++)
      it.Data1() /= it.Data2();
    return *this;
  }
  
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator+=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this,size2);it;it++)
      it.Data1() += number;
    return *this;
  }
    
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator-=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this,size2);it;it++)
      it.Data1() -= number;
    return *this;
  }
  
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator*=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this,size2);it;it++)
      it.Data1() *= number;
    return *this;
  }
  
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator/=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this,size2);it;it++)
      it.Data() /= number;
    return *this;
  }

  template<class DataT>
  DataT SArray2dC<DataT>::SumSqr() const {
    BufferAccess2dIterC<DataT> it(*this,size2);
    if(!it) {
      DataT ret;
      SetZero(ret);
      return ret;
    }
    DataT ret = Sqr(*it);
    for(it++;it;it++)
      ret += Sqr(*it);
    return ret;
  }
  
  template<class DataT>
  void SArray2dC<DataT>::SetColumn(IndexC i,const SArray1dC<DataT> &val) {
    RavlAssert(val.Size() == Size1());
    // Avoid including to many headers by just using a ptr, not a slice.
    DataT *d1 = &((*this)[0][i]); 
    for(BufferAccessIterC<DataT> it(val);it;it++,d1 += Stride())
      *d1 = *it;
  }
  
  template<class DataT>
  void SArray2dC<DataT>::SetRow(IndexC i,const SArray1dC<DataT> &val) {
    RavlAssert(val.Size() == Size2());
    for(BufferAccessIter2C<DataT,DataT> it((*this)[i],val);it;it++)
      it.Data1() = it.Data2();
  }
  
}

#endif
