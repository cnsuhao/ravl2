// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSARRAY2D_HEADER
#define RAVLSARRAY2D_HEADER 1
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
  template<class DataT> class SArray2dIterC;
  template<class DataT> class Slice1dC;
  template<class DataT> class Slice1dIterC;

  //! userlevel=Advanced  
  //: Simple 2 dimentional array.
  
  template<class DataC>
  class SArray2dC 
    : public SizeBufferAccess2dC<DataC>
  {
  public:
    typedef DataC ElementT;
    //: Allow function templates to find type of array.
    
    typedef SArray2dIterC<DataC> IteratorT;
    //: Type of iterator.
    
    inline SArray2dC()
      {}
    //: Default constructor.
    
    SArray2dC(SizeT dim1,SizeT dim2);
    //: Constructor.
    
    SArray2dC(const BufferC<DataC> & bf, SizeT size1,SizeT size2,SizeT startOffset = 0,SizeT stride = 0);
    //: Constructor using the buffer 'bf'. 
    // This can be used, for example to view a 1d array, as a 2d array.
    // startOffset is the location in the buffer to use as 0,0.
    // If stride is set to zero, size2 is used.
    
    SArray2dC<DataC> Copy() const;
    //: Copy array.
    
    // Special operations
    // -----------------
    
    Buffer2dC<DataC> &Buffer() 
      { return data; }
    //: Access base data buffer.
    // Experts only!
    
    const Buffer2dC<DataC> &Buffer() const
      { return data; }
    //: Constant access base data buffer.
    // Experts only!

    SArray2dC<DataC> operator+(const SArray2dC<DataC> & arr) const;
    // Sums 2 numerical arrays. The operator returns the result as a new array.
    
    SArray2dC<DataC> operator-(const SArray2dC<DataC> & arr) const;
    // Subtracts 2 numerical arrays. The operator returns
    // the result as a new array.
    
    SArray2dC<DataC> operator*(const SArray2dC<DataC> & arr) const;
    // Mutliplies 2 numerical arrays. The operator returns the result as a new array.
    
    SArray2dC<DataC> operator/(const SArray2dC<DataC> & arr) const;
    // Devides 2 numerical arrays. The operator returns
    // the result as a new array.
    
    SArray2dC<DataC> operator*(const DataC &number) const;
    // Multiplys the array by the 'number'. The operator
    // returns the result as a new array.
    
    SArray2dC<DataC> operator/(const DataC &number) const;
    // Divides all array items by the 'number'. The operator 
    // returns the result as a new array.
    
    SArray2dC<DataC> operator+(const DataC &number) const;
    // Adds 'number' to the array. The operator
    // returns the result as a new array.
    
    SArray2dC<DataC> operator-(const DataC &number) const;
    // Subtracts 'number' from all array items. The operator 
    // returns the result as a new array.
    
    const SArray2dC<DataC> & operator+=(const SArray2dC<DataC> & arr);
    // Adds the 2nd array to this array.
    
    const SArray2dC<DataC> & operator-=(const SArray2dC<DataC> & arr);
    // Subtracts the 2nd array from this array.
    
    const SArray2dC<DataC> & operator*=(const SArray2dC<DataC> & arr);
    // Multiplies the 2nd array to this array.
    
    const SArray2dC<DataC> & operator/=(const SArray2dC<DataC> & arr);
    // Divides the 2nd array from this array.
    
    const SArray2dC<DataC> & operator+=(const DataC &number);
    // Adds 'number' to all array items.
    
    const SArray2dC<DataC> & operator-=(const DataC &number);
    // Subtracts 'number' from all array items.
    
    const SArray2dC<DataC> & operator*=(const DataC &number);
    // Multiplies the array by the 'number'.
    
    const SArray2dC<DataC> & operator/=(const DataC &number);
    // Divides the array elements by the 'number'.

    Slice1dC<DataC> Diagonal() {
      return Slice1dC<DataC>(data.Data(),
			     &((*this)[0][0]),
			     Min(Size1(),Size2()),
			     Stride());
    }
    //: Take a slice along the diagonal of the array.
    
    SArray1dC<DataC> SliceRow(IndexC i)
      { return SArray1dC<DataC>(data,SArray1d()[i]); }
    //: Access row as 1d array.
    // NB. Changes made to the slice will also affect this array!
    
    Slice1dC<DataC> SliceColumn(IndexC i) { 
      return Slice1dC<DataC>(data.Data(),
			     &((*this)[0][i]),
			     Min(Size1(),Size2()),
			     Stride());
    }
    //: Access columb as 1d slice.
    // NB. Changes made to the slice will also affect this array!
    
  protected:
    void BuildAccess(UIntT offset = 0,UIntT stride = 0);
    
    Buffer2dC<DataC> data; // Handle to data.
  };
  
  template <class DataC>
  ostream & operator<<(ostream & s, const SArray2dC<DataC> & arr) {
    s << "0 " <<  arr.Size1() << " 0 " << arr.Size2() << "\n";
    return s << ((SizeBufferAccess2dC<DataC> &) arr);
  }
  // Prints into the stream 's'
  
  template <class DataC>
  istream & operator>>(istream & s, SArray2dC<DataC> & arr) {
    SizeT size1,size2,x1,x2;
    s >> x1 >> size1 >> x2 >> size2;
    RavlAssert(x1 == 0 && x2 == 0);  // Only accept arrays starting at origin.
    return s >> ((SizeBufferAccess2dC<DataC> &) arr);
  }
  // Reads the array from the stream 's'
  
  template<class DataC>
  BinOStreamC &operator<<(BinOStreamC & s, const SArray2dC<DataC> & arr) {
    SizeT x = 0;
    s << x << arr.Size1() << x << arr.Size2();
    return s << ((SizeBufferAccess2dC<DataC> &) arr);
  }

  template<class DataC>
  BinIStreamC &operator>>(BinIStreamC & s, SArray2dC<DataC> & arr) {
    SizeT size1,size2,x1,x2;
    s >> size1 >> size2;
    RavlAssert(x1 == 0 && x2 == 0); // Only accept arrays starting at origin.
    arr = SArray2dC<DataC>(size1,size2);
    return s >> ((SizeBufferAccess2dC<DataC> &) arr);
  }
  
  /////////////////////////////////////////////////////

  template<class DataC>
  void SArray2dC<DataC>::BuildAccess(UIntT offset,UIntT stride) {
    Attach(data);
    if(stride == 0)
      stride = size2;
    DataC *at = data.Data().ReferenceElm() + offset;
    for(BufferAccessIterC<BufferAccessC<DataC> > it(*this);
	it;it++,at += stride)
      *it = BufferAccessC<DataC>(at);
  }
  
  template<class DataC>
  SArray2dC<DataC>::SArray2dC(SizeT nsize1,SizeT nsize2)
    : SizeBufferAccess2dC<DataC>(nsize2),
      data(nsize1,nsize2)
  { BuildAccess(); }
  
  template<class DataC>
  SArray2dC<DataC>::SArray2dC(const BufferC<DataC> & bf, SizeT size1,SizeT nsize2,SizeT startOffset,SizeT stride)
    : SizeBufferAccess2dC<DataC>(size2),
      data(bf,bsize1)
  { BuildAccess(startOffset,stride); }
  
  template<class DataC>
  SArray2dC<DataC> 
  SArray2dC<DataC>::Copy() const {
    SArray2dC<DataC> newun(Size1(),size2); // Allocate new array.
    for(BufferAccess2dIter2C<DataC,DataC > it(*this,size2,
					      newun,size2);
	it;it++)
      it.Data2() = it.Data1();
    return newun;
  }
  
  
  template<class DataC>
  SArray2dC<DataC> SArray2dC<DataC>::operator+(const SArray2dC<DataC> & arr) const {
    SArray2dC<DataC> ret(Size1(),Size2());
    for(BufferAccess2dIter3C<DataC,DataC,DataC> it(ret,size2,
						   *this,size2,
						   arr,arr.Size2());
	it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }
  
  template<class DataC>
  SArray2dC<DataC> SArray2dC<DataC>::operator-(const SArray2dC<DataC> & arr) const {
    SArray2dC<DataC> ret(Size1(),Size2());
    for(BufferAccess2dIter3C<DataC,DataC,DataC> it(ret,size2,*this,size2,arr,arr.Size2());it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;
  }
  
  template<class DataC>
  SArray2dC<DataC> SArray2dC<DataC>::operator*(const SArray2dC<DataC> & arr) const {
    SArray2dC<DataC> ret(Size1(),Size2());
    for(BufferAccess2dIter3C<DataC,DataC,DataC> it(ret,size2,*this,size2,arr,arr.Size2());it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataC>
  SArray2dC<DataC> SArray2dC<DataC>::operator/(const SArray2dC<DataC> & arr) const {
    SArray2dC<DataC> ret(Size1(),Size2());
    for(BufferAccess2dIter3C<DataC,DataC,DataC> it(ret,size2,*this,size2,arr,arr.Size2());it;it++)
      it.Data1() = it.Data2() / it.Data3();
    return ret;
  }
  
  template<class DataC>
  SArray2dC<DataC> SArray2dC<DataC>::operator+(const DataC &number) const {
    SArray2dC<DataC> ret(Size1(),Size2());
    for(BufferAccess2dIter2C<DataC,DataC> it(ret,size2,size2,arr,arr.Size2());it;it++)
      it.Data1() = it.Data2() + number;
    return ret;
  }
  
  template<class DataC>
  SArray2dC<DataC> SArray2dC<DataC>::operator-(const DataC &number) const {
    SArray2dC<DataC> ret(Size1(),Size2());
    for(BufferAccess2dIter2C<DataC,DataC> it(ret,size2,arr,arr.Size2());it;it++)
      it.Data1() = it.Data2() - number;
    return ret;
  }
  
  template<class DataC>
  SArray2dC<DataC> SArray2dC<DataC>::operator*(const DataC &number) const {
    SArray2dC<DataC> ret(Size1(),Size2());
    for(BufferAccess2dIter2C<DataC,DataC> it(ret,size2,arr,arr.Size2());it;it++)
      it.Data1() = it.Data2() * number;
    return ret;
  }
  
  template<class DataC>
  SArray2dC<DataC> SArray2dC<DataC>::operator/(const DataC &number) const {
    SArray2dC<DataC> ret(Size1(),Size2());
    for(BufferAccess2dIter2C<DataC,DataC> it(ret,size2,arr,arr.Size2());it;it++)
      it.Data1() = it.Data2() / number;
    return ret;
  }
    
  template<class DataC>
  const SArray2dC<DataC> & SArray2dC<DataC>::operator+=(const SArray2dC<DataC> & arr) {
    for(BufferAccess2dIter2C<DataC,DataC> it(*this,size2,arr,arr.Size2());it;it++)
      it.Data1() += it.Data2();
    return *this;
  }
  
  template<class DataC>
  const SArray2dC<DataC> & SArray2dC<DataC>::operator-=(const SArray2dC<DataC> & arr) {
    for(BufferAccess2dIter2C<DataC,DataC> it(*this,size2,arr,arr.Size2());it;it++)
      it.Data1() -= it.Data2();
    return *this;
  }
    
  template<class DataC>
  const SArray2dC<DataC> & SArray2dC<DataC>::operator*=(const SArray2dC<DataC> & arr) {
    for(BufferAccess2dIter2C<DataC,DataC> it(*this,size2,arr,arr.Size2());it;it++)
      it.Data1() *= it.Data2();
    return *this;
  }
    
  template<class DataC>
  const SArray2dC<DataC> & SArray2dC<DataC>::operator/=(const SArray2dC<DataC> & arr) {
    for(BufferAccess2dIter2C<DataC,DataC> it(*this,size2,arr,arr.Size2());it;it++)
      it.Data1() /= it.Data2();
    return *this;
  }
  
  template<class DataC>
  const SArray2dC<DataC> & SArray2dC<DataC>::operator+=(const DataC &number) {
    for(BufferAccess2dIterC<DataC> it(*this,size2);it;it++)
      it.Data1() += number;
    return *this;
  }
    
  template<class DataC>
  const SArray2dC<DataC> & SArray2dC<DataC>::operator-=(const DataC &number) {
    for(BufferAccess2dIterC<DataC> it(*this,size2);it;it++)
      it.Data1() -= number;
    return *this;
  }
  
  template<class DataC>
  const SArray2dC<DataC> & SArray2dC<DataC>::operator*=(const DataC &number) {
    for(BufferAccess2dIterC<DataC> it(*this,size2);it;it++)
      it.Data1() *= number;
    return *this;
  }
  
  template<class DataC>
  const SArray2dC<DataC> & SArray2dC<DataC>::operator/=(const DataC &number) {
    for(BufferAccess2dIterC<DataC> it(*this,size2);it;it++)
      it.Data() /= number;
    return *this;
  }
}

#endif
