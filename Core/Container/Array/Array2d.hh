// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ARRAY2D_HH
#define RAVL_ARRAY2D_HH
///////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Array/Array2d.hh"
//! lib=RavlCore
//! author="Radek Marik"
//! date="2/5/1993"
//! docentry="Ravl.Core.Arrays.2D"
//! rcsid="$Id$"
//! example=exArray2d.cc
//! userlevel=Normal

#include "Ravl/RBfAcc2d.hh"
#include "Ravl/Buffer2d.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/IndexRange2d.hh"
#include "Ravl/BfAcc2Iter.hh"
#include "Ravl/BfAcc2Iter2.hh"
#include "Ravl/BfAcc2Iter3.hh"
#include "Ravl/SArray2d.hh"

class istream;
class ostream;

namespace RavlN {
  
  template<class DataT> class SArray2dC;
  template<class DataT> class Array1dC;
  template<class DataT> class Slice1dC;
  template<class DataT> class Slice1dIterC;
  
  //! userlevel=Basic
  //: 2 Dimensional array
  // The class Array2dC is a container of items which can be indexed
  // by 2-dimensional index.
  
  template <class DataT>
  class Array2dC
    : public RangeBufferAccess2dC<DataT>
  {
  public:
    Array2dC()
      {}
    //: Creates an empty 2D array.
    
    Array2dC(SizeT dim1, SizeT dim2);
    //: Creates 2D array with the range < <0,dim1-1>, <0,dim2-1> >
    
    Array2dC(IntT minRow,IntT maxRow,IntT minCol,IntT maxCol);
    //: Creates 2D array with the range minRow to maxRow by minCol to maxCol.
    
    Array2dC(IndexC minRow,IndexC maxRow,IndexC minCol,IndexC maxCol);
    //: Creates 2D array with the range minRow to maxRow by minCol to maxCol.
    
    Array2dC(const Index2dC & min, const Index2dC & max);
    //: Creates 2D array with the range < <min[0], max[0]>, <min[1], max[1]> >.
    
    Array2dC(const IndexRangeC & rng1, const IndexRangeC & rng2);
    //: Creates 2D array with the range <rng1, rng2>
    
    Array2dC(const IndexRange2dC & rect);
    //: Create 2D array with the range covering indexes in 'rect'
    
    Array2dC(const IndexRange2dC & rect,const BufferC<DataT> &data);
    //: Create 2D array with the range covering indexes in 'rect' from data.
    // NB. It is the users responsability to ensure that 'data' is
    // large enought to contain 'rect'.
    
    Array2dC(const Array2dC<DataT> &arr,const IndexRange2dC & rect);
    //: Create a sub array of 'arr' covering indexes 'rect'.
    
    Array2dC(const SArray2dC<DataT> &sarr);
    //: Construct 2d array from sarray.
    // Note: This does NOT make a copy, it just creates
    // another access to the buffer.
    
    Array2dC<DataT> Copy() const;
    //: Make a copy of the array.
    
    inline SArray2dC<DataT> SArray2d(bool doShift = false);
    //: Create an access as an SArray.
    // NB. This does NOT copy the data, it only make a new access to it.
    // If doShift is true element Range1().Min(),Range2().Min() will
    // become 0,0 of the sarray. Otherwise if the array does not 
    // contain element '0,0' an error will occure in check mode, 
    // when optimised is enabled an empty array  will be returned. 
    
    Array1dC<DataT> SliceRow(IndexC i)
      { return Array1dC<DataT>(data.Data(),(*this)[i]); }
    //: Access row as 1d array.
    // NB. Changes made to the slice will also affect this array!
    
    Slice1dC<DataT> SliceColumn(IndexC i) { 
      return Slice1dC<DataT>(data.Data(),
			     &((*this)[Range1().Min()][i]),
			     Min(Range1.Size(),Range2.Size()),
			     Stride());
    }
    //: Access columb as 1d slice.
    // NB. Changes made to the slice will also affect this array!
    
    Slice1dC<DataT> Diagonal() {
      return Slice1dC<DataT>(data.Data(),
			     &((*this)[Range1().Min()][Range2().Min()]),
			     Min(Range1.Size(),Range2.Size()),
			     Stride()+1);
    }
    //: Take a slice along the diagonal of the array.
    // NB. Changes made to the slice will also affect this array!
    
    inline const Array2dC<DataT> & Array2d() const
      { return(*this); }
    //: access to the constant object
    
    inline Array2dC<DataT> & Array2d()
      { return(*this); }
    //: access to the object
    
    inline void ShiftIndexes1(IndexC offset);
    //: All indexes of Range1() will be changed by 'offset'.
    // The range will be shifted by -offset.
    
    void ShiftIndexes2(IndexC offset);
    //: All indexes of Range2() will be changed by 'offset'.
    // The range will be shifted by -offset.
    
    Array2dC<DataT> operator+(const Array2dC<DataT> & arr) const;
    //: Sums 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array2dC<DataT> operator-(const Array2dC<DataT> & arr) const;
    //: Subtracts 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array2dC<DataT> operator*(const Array2dC<DataT> & arr) const;
    //: Mutliplies 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array2dC<DataT> operator/(const Array2dC<DataT> & arr) const;
    //: Divides 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array2dC<DataT> operator*(const DataT &number) const;
    //: Multiplys the array by the 'number'. 
    // The operator returns the result as a new array.
    
    Array2dC<DataT> operator/(const DataT &number) const;
    //: Divides all array items by the 'number'. 
    // The operator returns the result as a new array.
    
    Array2dC<DataT> operator+(const DataT &number) const;
    //: Adds 'number' to the array. 
    // The operator returns the result as a new array.
    
    Array2dC<DataT> operator-(const DataT &number) const;
    //: Subtracts 'number' from all array items. 
    // The operator  returns the result as a new array.
    
    const Array2dC<DataT> & operator+=(const Array2dC<DataT> & arr);
    //: Adds the 2nd array to this array.
    
    const Array2dC<DataT> & operator-=(const Array2dC<DataT> & arr);
    //: Subtracts the 2nd array from this array.
    
    const Array2dC<DataT> & operator*=(const Array2dC<DataT> & arr);
    //: Multiplies the 2nd array to this array.
    
    const Array2dC<DataT> & operator/=(const Array2dC<DataT> & arr);
    //: Divides the 2nd array from this array.
    
    const Array2dC<DataT> & operator+=(const DataT &number);
    //: Adds 'number' to all array items.
    
    const Array2dC<DataT> & operator-=(const DataT &number);
    //: Subtracts 'number' from all array items.
    
    const Array2dC<DataT> & operator*=(const DataT &number);
    //: Multiplies the array by the 'number'.
    
    const Array2dC<DataT> & operator/=(const DataT &number);
    //: Divides the array elements by the 'number'.
    
  protected:
    void ConstructAccess(const IndexRangeC &rng1);
    //: Construct access for buffer.
    // This assumes a suitable amount of space has been allocated
    // in 'data'
    
    Buffer2dC<DataT> data; // Raw data stored in array.
  };
  
  
  template <class DataT>
  ostream & operator<<(ostream & s, const Array2dC<DataT> & arr);
  // Prints into the stream 's'
  
  template <class DataT>
  istream & operator>>(istream & s, Array2dC<DataT> & arr);
  // Reads the array from the stream 's'
  
  ////////////////////////////////////////////////////////////////////////////////
  
  template <class DataT>
  inline 
  void Array2dC<DataT>::ShiftIndexes1(IndexC offset)
  { ShiftIndexes(offset); }
  
  template <class DataT>
  void Array2dC<DataT>::ShiftIndexes2(IndexC offset) {
    for(BufferAccessIterC<BufferAccessC<DataT> > it(*this);it.IsElm();it.Next()) 
      it.Data().ShiftIndexes(offset);
    size2 -= offset.V(); // Keep dim2 uptodate.
  }
  
  template <class DataT>
  void Array2dC<DataT>::ConstructAccess(const IndexRangeC &rng1) {
    Attach(data,rng1);
    const SizeT d2Size = Range2().Size();
    DataT *at = data.Data().ReferenceElm() - Range2().Min().V();
    for(BufferAccessIterC<BufferAccessC<DataT> > it(*this);it;it++,at += d2Size)
      *it = at;
  }
  
  template <class DataT>
  Array2dC<DataT>::Array2dC(SizeT nsize1, SizeT nsize2)
    : RangeBufferAccess2dC<DataT>(IndexRangeC(0,nsize2-1)),
      data(nsize1,nsize2)
  { ConstructAccess(IndexRangeC(0,nsize1-1)); }
  
  template <class DataT>
  Array2dC<DataT>::Array2dC(IndexC minRow,IndexC maxRow,
			    IndexC minCol,IndexC maxCol)
    : RangeBufferAccess2dC<DataT>(IndexRangeC(minCol,maxCol)),
      data(IndexRangeC(minRow,maxRow).Size(),IndexRangeC(minCol,maxCol).Size())
  { 
    RavlAssert(minRow <= maxRow);
    RavlAssert(minCol <= maxCol);
    ConstructAccess(IndexRangeC(minRow,maxRow)); 
  }
  
  template <class DataT>
  Array2dC<DataT>::Array2dC(IntT minRow,IntT maxRow,IntT minCol,IntT maxCol) 
    : RangeBufferAccess2dC<DataT>(IndexRangeC(minCol,maxCol)),
      data(IndexRangeC(minRow,maxRow).Size(),IndexRangeC(minCol,maxCol).Size())    
  {
    RavlAssert(minRow <= maxRow);
    RavlAssert(minCol <= maxCol);
    ConstructAccess(IndexRangeC(minRow,maxRow)); 
  }

  template <class DataT>
  Array2dC<DataT>::Array2dC(const IndexRangeC & rng1,
			    const IndexRangeC & rng2)
    : RangeBufferAccess2dC<DataT>(rng2),
      data(rng1.Size(),rng2.Size())
  { ConstructAccess(rng1); }
  
  template <class DataT>
  Array2dC<DataT>::Array2dC(const Index2dC & min, const Index2dC & max)
    : RangeBufferAccess2dC<DataT>(IndexRangeC(min[1],max[1])),
      data(IndexRangeC(min[0],max[0]).Size(),Range2().Size())
  { ConstructAccess(IndexRangeC(min[0],max[0])); }
  
  template <class DataT>
  Array2dC<DataT>::Array2dC(const IndexRange2dC & rect)
    : RangeBufferAccess2dC<DataT>(rect.Range2()),
      data(rect.Range1().Size(),rect.Range2().Size())
  { ConstructAccess(rect.Range1()); }
  
  template <class DataT>
  Array2dC<DataT>::Array2dC(const IndexRange2dC & rect,const BufferC<DataT> &ndata)
    : RangeBufferAccess2dC<DataT>(rect.Range2()),
      data(ndata,rect.Range1().Size())
  { ConstructAccess(rect.Range1()); }

  template <class DataT>
  Array2dC<DataT>::Array2dC(const Array2dC<DataT> &arr,const IndexRange2dC & rect) 
    : RangeBufferAccess2dC<DataT> (arr,rect),
    data(arr.data)
  {}

  template <class DataT>
  Array2dC<DataT>::Array2dC(const SArray2dC<DataT> &sarr)
    : RangeBufferAccess2dC<DataT>(sarr,IndexRangeC(0,sarr.Size1()-1),IndexRangeC(0,sarr.Size2()-1)),
      data(sarr.Buffer())
  {}

  template <class DataT>
  Array2dC<DataT> Array2dC<DataT>::Copy() const {
    Array2dC<DataT> ret(Rectangle());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,ret.Range2(),*this,Range2());it;it++)
      it.Data1() = it.Data2();
    return ret;
  }

  template <class DataT>
  inline SArray2dC<DataT> Array2dC<DataT>::SArray2d(bool doShift) {
    if(Range1().Size() == 0 || Range2().Size() == 0)
      return SArray2dC<DataT>(); // Empty array.
    if(doShift) {
      SizeT offset = &((*this)[Range1().Min()][Range2().Min()]) - data.Data().ReferenceElm();
      return SArray2dC<DataT>(data.Data(),Range1().Size(),Range2().Size(),offset,(SizeT) Stride());
    }
    if(!Contains(Index2dC(0,0))) {
      RavlAssertMsg(Contains(Index2dC(0,0)),"Array2dC must contain the element 0,0 to convert to an SArray without shifting. "); // Cause assertion failure in debug/check mode
      return SArray2dC<DataT>();
    }
    return SArray2dC<DataT>(data,*this,Range1().Max().V()+1,Range2().Max().V()+1);
  }
  
    
  template <class DataT>
  ostream & operator<<(ostream & s, const Array2dC<DataT> & arr) {
    s << arr.Rectangle() << "\n";
    return s << ((const RangeBufferAccess2dC<DataT> &)arr);
  }
  
  
  template <class DataT>
  istream &operator>>(istream & s, Array2dC<DataT> & arr) {
    IndexRange2dC rect;
    s >> rect;
    arr = Array2dC<DataT>(rect);
    return s >> ((RangeBufferAccess2dC<DataT> &)arr);
  }
  
  
  template<class DataT>
  BinOStreamC &operator<<(BinOStreamC & s, const Array2dC<DataT> & arr) {
    s << arr.Range1().Min() << arr.Range1().Max() << arr.Range2().Min() << arr.Range2().Max();
    return s << ((const RangeBufferAccess2dC<DataT> &)arr);
  }
  
  template<class DataT>
  BinIStreamC &operator>>(BinIStreamC & s, Array2dC<DataT> & arr) {
    IndexRangeC rng1,rng2;
    s >> rng1.Min() >> rng1.Max() >> rng2.Min() >> rng2.Max();
    arr = Array2dC<DataT>(rng1,rng2);
    return s >> ((RangeBufferAccess2dC<DataT> &)arr);
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator+(const Array2dC<DataT> & arr) const {
    Array2dC<DataT> ret(Rectangle());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,Range2(),
						   *this,Range2(),
						   arr,arr.Range2());
	it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator-(const Array2dC<DataT> & arr) const {
    Array2dC<DataT> ret(Rectangle());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,Range2(),*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator*(const Array2dC<DataT> & arr) const {
    Array2dC<DataT> ret(Rectangle());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,Range2(),*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator/(const Array2dC<DataT> & arr) const {
    Array2dC<DataT> ret(Rectangle());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,Range2(),*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() / it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator+(const DataT &number) const {
    Array2dC<DataT> ret(Rectangle());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,Range2(),Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() + number;
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator-(const DataT &number) const {
    Array2dC<DataT> ret(Rectangle());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() - number;
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator*(const DataT &number) const {
    Array2dC<DataT> ret(Rectangle());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() * number;
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator/(const DataT &number) const {
    Array2dC<DataT> ret(Rectangle());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() / number;
    return ret;
  }
    
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator+=(const Array2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() += it.Data2();
    return *this;
  }
  
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator-=(const Array2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() -= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator*=(const Array2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() *= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator/=(const Array2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() /= it.Data2();
    return *this;
  }
  
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator+=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this,Range2());it;it++)
      it.Data1() += number;
    return *this;
  }
    
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator-=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this,Range2());it;it++)
      it.Data1() -= number;
    return *this;
  }
  
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator*=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this,Range2());it;it++)
      it.Data1() *= number;
    return *this;
  }
  
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator/=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this,Range2());it;it++)
      it.Data() /= number;
    return *this;
  }
  
}
#endif

