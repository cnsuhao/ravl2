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
//! docentry="Ravl.Core.Arrays.3D"
//! rcsid="$Id$"
//! file="Ravl/Core/Container/SArray/SArray3d.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="10/09/1998"

#include "Ravl/SBfAcc3d.hh"
#include "Ravl/Buffer3d.hh"
#include "Ravl/Index3d.hh"
#include "Ravl/BfAcc3Iter.hh"
#include "Ravl/BfAcc3Iter2.hh"
#include "Ravl/BfAcc3Iter3.hh"

namespace RavlN {
  
  template<class DataT> class SArray1dC;
  template<class DataT> class SArray3dIterC;
  template<class DataT> class Slice1dC;
  template<class DataT> class Slice1dIterC;

  //! userlevel=Advanced  
  //: Simple 3 dimentional array.
  
  template<class DataT>
  class SArray3dC 
    : public SizeBufferAccess3dC<DataT>
  {
  public:
    typedef DataT ElementT;
    //: Allow function templates to find type of array.
    
    typedef SArray3dIterC<DataT> IteratorT;
    //: Type of iterator.
    
    inline SArray3dC()
      {}
    //: Default constructor.
    
    SArray3dC(SizeT dim1,SizeT dim2,SizeT dim3);
    //: Constructor.
    
#if 0
    SArray3dC(const BufferC<DataT> & bf, SizeT size1,SizeT size2,SizeT startOffset = 0,SizeT stride = 0);
    //: Constructor using the buffer 'bf'. 
    // This can be used, for example to view a 1d array, as a 3d array.
    // startOffset is the location in the buffer to use as 0,0.
    // If stride is set to zero, size2 is used.
    // <p> NOT IMPLEMENTED, Will be on request.
#endif
    
    SArray3dC<DataT> Copy() const;
    //: Copy array.
    
    //:------------------
    // Special operations
    
    Buffer3dC<DataT> &Buffer() 
      { return data; }
    //: Access base data buffer.
    // Experts only!
    
    const Buffer3dC<DataT> &Buffer() const
      { return data; }
    //: Constant access base data buffer.
    // Experts only!

    SArray3dC<DataT> operator+(const SArray3dC<DataT> & arr) const;
    // Sums 2 numerical arrays. The operator returns the result as a new array.
    
    SArray3dC<DataT> operator-(const SArray3dC<DataT> & arr) const;
    // Subtracts 2 numerical arrays. The operator returns
    // the result as a new array.
    
    SArray3dC<DataT> operator*(const SArray3dC<DataT> & arr) const;
    // Mutliplies 2 numerical arrays. The operator returns the result as a new array.
    
    SArray3dC<DataT> operator/(const SArray3dC<DataT> & arr) const;
    // Devides 2 numerical arrays. The operator returns
    // the result as a new array.
    
    SArray3dC<DataT> operator*(const DataT &number) const;
    // Multiplys the array by the 'number'. The operator
    // returns the result as a new array.
    
    SArray3dC<DataT> operator/(const DataT &number) const;
    // Divides all array items by the 'number'. The operator 
    // returns the result as a new array.
    
    SArray3dC<DataT> operator+(const DataT &number) const;
    // Adds 'number' to the array. The operator
    // returns the result as a new array.
    
    SArray3dC<DataT> operator-(const DataT &number) const;
    // Subtracts 'number' from all array items. The operator 
    // returns the result as a new array.
    
    const SArray3dC<DataT> & operator+=(const SArray3dC<DataT> & arr);
    // Adds the 2nd array to this array.
    
    const SArray3dC<DataT> & operator-=(const SArray3dC<DataT> & arr);
    // Subtracts the 2nd array from this array.
    
    const SArray3dC<DataT> & operator*=(const SArray3dC<DataT> & arr);
    // Multiplies the 2nd array to this array.
    
    const SArray3dC<DataT> & operator/=(const SArray3dC<DataT> & arr);
    // Divides the 2nd array from this array.
    
    const SArray3dC<DataT> & operator+=(const DataT &number);
    // Adds 'number' to all array items.
    
    const SArray3dC<DataT> & operator-=(const DataT &number);
    // Subtracts 'number' from all array items.
    
    const SArray3dC<DataT> & operator*=(const DataT &number);
    // Multiplies the array by the 'number'.
    
    const SArray3dC<DataT> & operator/=(const DataT &number);
    // Divides the array elements by the 'number'.

#if 0
    Slice1dC<DataT> Diagonal() {
      return Slice1dC<DataT>(data.Data(),
			     &((*this)[0][0]),
			     Min(Size1(),Size2(),Size3()),
			     Stride()+1);
    }
    //: Take a slice along the diagonal of the array.
    // <p> NOT IMPLEMENTED, Will be on request.
    
    SArray1dC<DataT> SliceRow(IndexC i)
      { return SArray1dC<DataT>(data.Data(),SArray1d()[i]); }
    //: Access row as 1d array.
    // NB. Changes made to the slice will also affect this array!
    // <p> NOT IMPLEMENTED, Will be on request.
    
    Slice1dC<DataT> SliceColumn(IndexC i) { 
      return Slice1dC<DataT>(data.Data(),
			     &((*this)[0][i]),
			     Min(Size1(),Size2(),Size3()),
			     Stride());
    }
    //: Access columb as 1d slice.
    // NB. Changes made to the slice will also affect this array!
    // <p> NOT IMPLEMENTED, Will be on request.
    
    void SetColumn(IndexC i,const SArray1dC<DataT> &val);
    //: Set the values in the column i to those in 'val'.
    // 'val' must have a size equal to the number of rows.
    // <p> NOT IMPLEMENTED, Will be on request.
    
    void SetRow(IndexC i,const SArray1dC<DataT> &val);
    //: Set the values in the row i to those in 'val'.
    // 'val' must have a size equal to the number of columns
    // <p> NOT IMPLEMENTED, Will be on request.
#endif    
  protected:
    void BuildAccess(SizeT size1);
    
    Buffer3dC<DataT> data; // Handle to data.
  };
  
  template <class DataT>
  ostream & operator<<(ostream & s, const SArray3dC<DataT> & arr) {
    s << "0 " <<  arr.Size1() << " 0 " << arr.Size2() << " 0 " << arr.Size3() << "\n";
    return s << ((SizeBufferAccess3dC<DataT> &) arr);
  }
  // Prints into the stream 's'
  
  template <class DataT>
  istream & operator>>(istream & s, SArray3dC<DataT> & arr) {
    SizeT size1,size2,size3,x1,x2,x4;
    s >> x1 >> size1 >> x2 >> size2 >> x3 >> size3;
    RavlAssert(x1 == 0 && x2 == 0 && x3 == 0);  // Only accept arrays starting at origin.
    return s >> ((SizeBufferAccess3dC<DataT> &) arr);
  }
  // Reads the array from the stream 's'
  
  template<class DataT>
  BinOStreamC &operator<<(BinOStreamC & s, const SArray3dC<DataT> & arr) {
    SizeT x = 0;
    s << x << arr.Size1() << x << arr.Size2() << x << arr.Size3();
    return s << ((SizeBufferAccess3dC<DataT> &) arr);
  }

  template<class DataT>
  BinIStreamC &operator>>(BinIStreamC & s, SArray3dC<DataT> & arr) {
    SizeT size1,size2,size3,x1,x2,x3;
    s >> x1 >> size1 >> x2 >> size2 >> x3 >> size3;
    RavlAssert(x1 == 0 && x2 == 0  && x3 == 0); // Only accept arrays starting at origin.
    arr = SArray3dC<DataT>(size1,size2);
    return s >> ((SizeBufferAccess3dC<DataT> &) arr);
  }
  
  /////////////////////////////////////////////////////

  template<class DataT>
  void SArray3dC<DataT>::BuildAccess(SizeT size1) {
    Attach(data,size1);
    const SizeT d3Size = Size3();
    const SizeT d2Size = Size2();
    BufferAccessC<DataT>  *acc2 = data.DataIndex().ReferenceElm();
    DataT *atData = data.Data().ReferenceElm();
    for(BufferAccessIterC<BufferAccessC<BufferAccessC<DataT> > > it(*this,size1);it;it++,acc2 += d2Size) {
      *it = acc2;
      for(BufferAccessIterC<BufferAccessC<DataT> > it2(*it,size2);it2;it2++,atData += d3Size)
	*it2 = atData;
    }
  }
  
  template<class DataT>
  SArray3dC<DataT>::SArray3dC(SizeT nsize1,SizeT nsize2,SizeT nsize3)
    : SizeBufferAccess3dC<DataT>(nsize2,nsize3),
      data(nsize1,nsize2,nsize3)
  { BuildAccess(nsize1); }
  
#if 0
  template<class DataT>
  SArray3dC<DataT>::SArray3dC(const BufferC<DataT> & bf, SizeT size1,SizeT nsize2,SizeT startOffset,SizeT stride)
    : SizeBufferAccess3dC<DataT>(size2),
      data(bf,bsize1)
  { BuildAccess(startOffset,stride); }
#endif
  
  template<class DataT>
  SArray3dC<DataT> 
  SArray3dC<DataT>::Copy() const {
    SArray3dC<DataT> newun(Size1(),size2,size3); // Allocate new array.
    for(BufferAccess3dIter2C<DataT,DataT > it(*this,size2,size3,
					      newun,size2,size3);
	it;it++)
      it.Data2() = it.Data1();
    return newun;
  }
  
  
  template<class DataT>
  SArray3dC<DataT> SArray3dC<DataT>::operator+(const SArray3dC<DataT> & arr) const {
    SArray3dC<DataT> ret(Size1(),Size2(),Size3());
    for(BufferAccess3dIter3C<DataT,DataT,DataT> it(ret,size2,size3,
						   *this,size2,size3,
						   arr,arr.Size2(),arr.Size3());
	it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray3dC<DataT> SArray3dC<DataT>::operator-(const SArray3dC<DataT> & arr) const {
    SArray3dC<DataT> ret(Size1(),Size2(),Size3());
    for(BufferAccess3dIter3C<DataT,DataT,DataT> it(ret,size2,size3,*this,size2,size3,arr,arr.Size2(),arr.Size3());it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray3dC<DataT> SArray3dC<DataT>::operator*(const SArray3dC<DataT> & arr) const {
    SArray3dC<DataT> ret(Size1(),Size2(),Size3());
    for(BufferAccess3dIter3C<DataT,DataT,DataT> it(ret,size2,size3,*this,size2,size3,arr,arr.Size2(),arr.Size3());it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray3dC<DataT> SArray3dC<DataT>::operator/(const SArray3dC<DataT> & arr) const {
    SArray3dC<DataT> ret(Size1(),Size2(),Size3());
    for(BufferAccess3dIter3C<DataT,DataT,DataT> it(ret,size2,size3,*this,size2,size3,arr,arr.Size2(),arr.Size3());it;it++)
      it.Data1() = it.Data2() / it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray3dC<DataT> SArray3dC<DataT>::operator+(const DataT &number) const {
    SArray3dC<DataT> ret(Size1(),Size2(),Size3());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,size2,size3,*this,Size2(),Size3());it;it++)
      it.Data1() = it.Data2() + number;
    return ret;
  }
  
  template<class DataT>
  SArray3dC<DataT> SArray3dC<DataT>::operator-(const DataT &number) const {
    SArray3dC<DataT> ret(Size1(),Size2(),Size3());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,size2,size3,*this,Size2(),Size3());it;it++)
      it.Data1() = it.Data2() - number;
    return ret;
  }
  
  template<class DataT>
  SArray3dC<DataT> SArray3dC<DataT>::operator*(const DataT &number) const {
    SArray3dC<DataT> ret(Size1(),Size2(),Size3());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,size2,size3,*this,Size2(),Size3());it;it++)
      it.Data1() = it.Data2() * number;
    return ret;
  }
  
  template<class DataT>
  SArray3dC<DataT> SArray3dC<DataT>::operator/(const DataT &number) const {
    SArray3dC<DataT> ret(Size1(),Size2(),Size3());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,size2,size3,*this,Size2(),Size3());it;it++)
      it.Data1() = it.Data2() / number;
    return ret;
  }
    
  template<class DataT>
  const SArray3dC<DataT> & SArray3dC<DataT>::operator+=(const SArray3dC<DataT> & arr) {
    for(BufferAccess3dIter2C<DataT,DataT> it(*this,size2,size3,arr,arr.Size2(),arr.Size3());it;it++)
      it.Data1() += it.Data2();
    return *this;
  }
  
  template<class DataT>
  const SArray3dC<DataT> & SArray3dC<DataT>::operator-=(const SArray3dC<DataT> & arr) {
    for(BufferAccess3dIter2C<DataT,DataT> it(*this,size2,size3,arr,arr.Size2(),arr.Size3());it;it++)
      it.Data1() -= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const SArray3dC<DataT> & SArray3dC<DataT>::operator*=(const SArray3dC<DataT> & arr) {
    for(BufferAccess3dIter2C<DataT,DataT> it(*this,size2,size3,arr,arr.Size2(),arr.Size3());it;it++)
      it.Data1() *= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const SArray3dC<DataT> & SArray3dC<DataT>::operator/=(const SArray3dC<DataT> & arr) {
    for(BufferAccess3dIter2C<DataT,DataT> it(*this,size2,size3,arr,arr.Size2(),arr.Size3());it;it++)
      it.Data1() /= it.Data2();
    return *this;
  }
  
  template<class DataT>
  const SArray3dC<DataT> & SArray3dC<DataT>::operator+=(const DataT &number) {
    for(BufferAccess3dIterC<DataT> it(*this,size2,size3);it;it++)
      it.Data1() += number;
    return *this;
  }
    
  template<class DataT>
  const SArray3dC<DataT> & SArray3dC<DataT>::operator-=(const DataT &number) {
    for(BufferAccess3dIterC<DataT> it(*this,size2,size3);it;it++)
      it.Data1() -= number;
    return *this;
  }
  
  template<class DataT>
  const SArray3dC<DataT> & SArray3dC<DataT>::operator*=(const DataT &number) {
    for(BufferAccess3dIterC<DataT> it(*this,size2,size3);it;it++)
      it.Data1() *= number;
    return *this;
  }
  
  template<class DataT>
  const SArray3dC<DataT> & SArray3dC<DataT>::operator/=(const DataT &number) {
    for(BufferAccess3dIterC<DataT> it(*this,size2,size3);it;it++)
      it.Data() /= number;
    return *this;
  }
  
#if 0
  template<class DataT>
  void SArray3dC<DataT>::SetColumn(IndexC i,const SArray1dC<DataT> &val) {
    RavlAssert(val.Size() == size2);
    // Avoid including to many headers just use a ptr, not a slice.
    DataT *d1 = &((*this)[0][i]); 
    for(BufferAccessIterC<DataT> it(val);it;it++,d1 += Stride())
      *it = *d1;
  }
  
  template<class DataT>
  void SArray3dC<DataT>::SetRow(IndexC i,const SArray1dC<DataT> &val) {
    RavlAssert(val.Size() == size1);
    for(BufferAccessIter2C<DataT,DataT> it(SArray1d()[i],val);it;it++)
      it.Data1() = it.Data2();
  }
#endif
  
}

#endif
