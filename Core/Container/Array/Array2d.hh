// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef ARRAY2D_HH
#define ARRAY2D_HH
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

class istream;
class ostream;

namespace RavlN {
  
  template<class DataT> class Array1dC;
  template<class DataT> class Slice1dC;
  template<class DataT> class Slice1dIterC;
  
  //! userlevel=Basic
  //: 2 Dimensional array
  // The class Array2dC is a container of items which can be indexed
  // by 2-dimensional index.
  
  template <class DataC>
  class Array2dC
    : public RangeBufferAccess2dC<DataC>
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
    
    Array2dC(const IndexRange2dC & rect,const BufferC<DataC> &data);
    //: Create 2D array with the range covering indexes in 'rect' from data.
    // NB. It is the users responsability to ensure that 'data' is
    // large enought to contain 'rect'.
    
    Array2dC<DataC> Copy() const;
    //: Make a copy of the array.
    
    Array1dC<DataC> SliceRow(IndexC i)
      { return Array1dC<DataC>(data.Data(),(*this)[i]); }
    //: Access row as 1d array.
    // NB. Changes made to the slice will also affect this array!
    
    Slice1dC<DataC> SliceColumn(IndexC i) { 
      return Slice1dC<DataC>(data.Data(),
			     &((*this)[Range1().Min()][i]),
			     Min(Range1.Size(),Range2.Size()),
			     Stride());
    }
    //: Access columb as 1d slice.
    // NB. Changes made to the slice will also affect this array!
    
    Slice1dC<DataC> Diagonal() {
      return Slice1dC<DataC>(data.Data(),
			     &((*this)[Range1().Min()][Range2().Min()]),
			     Min(Range1.Size(),Range2.Size()),
			     Stride()+1);
    }
    //: Take a slice along the diagonal of the array.
    // NB. Changes made to the slice will also affect this array!
    
    inline const Array2dC<DataC> & Array2d() const
      { return(*this); }
    //: access to the constant object
    
    inline Array2dC<DataC> & Array2d()
      { return(*this); }
    //: access to the object
    
    inline void ShiftIndexes1(IndexC offset);
    //: All indexes of Range1() will be changed by 'offset'.
    // The range will be shifted by -offset.
    
    void ShiftIndexes2(IndexC offset);
    //: All indexes of Range2() will be changed by 'offset'.
    // The range will be shifted by -offset.
    
    // Logical conditions.
    // -------------------
    
    Array2dC<DataC> operator+(const Array2dC<DataC> & arr) const;
    //: Sums 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array2dC<DataC> operator-(const Array2dC<DataC> & arr) const;
    //: Subtracts 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array2dC<DataC> operator*(const Array2dC<DataC> & arr) const;
    //: Mutliplies 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array2dC<DataC> operator/(const Array2dC<DataC> & arr) const;
    //: Divides 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array2dC<DataC> operator*(const DataC &number) const;
    //: Multiplys the array by the 'number'. 
    // The operator returns the result as a new array.
    
    Array2dC<DataC> operator/(const DataC &number) const;
    //: Divides all array items by the 'number'. 
    // The operator returns the result as a new array.
    
    Array2dC<DataC> operator+(const DataC &number) const;
    //: Adds 'number' to the array. 
    // The operator returns the result as a new array.
    
    Array2dC<DataC> operator-(const DataC &number) const;
    //: Subtracts 'number' from all array items. 
    // The operator  returns the result as a new array.
    
    const Array2dC<DataC> & operator+=(const Array2dC<DataC> & arr);
    //: Adds the 2nd array to this array.
    
    const Array2dC<DataC> & operator-=(const Array2dC<DataC> & arr);
    //: Subtracts the 2nd array from this array.
    
    const Array2dC<DataC> & operator*=(const Array2dC<DataC> & arr);
    //: Multiplies the 2nd array to this array.
    
    const Array2dC<DataC> & operator/=(const Array2dC<DataC> & arr);
    //: Divides the 2nd array from this array.
    
    const Array2dC<DataC> & operator+=(const DataC &number);
    //: Adds 'number' to all array items.
    
    const Array2dC<DataC> & operator-=(const DataC &number);
    //: Subtracts 'number' from all array items.
    
    const Array2dC<DataC> & operator*=(const DataC &number);
    //: Multiplies the array by the 'number'.
    
    const Array2dC<DataC> & operator/=(const DataC &number);
    //: Divides the array elements by the 'number'.
    
  protected:
    void ConstructAccess(const IndexRangeC &rng1);
    //: Construct access for buffer.
    // This assumes a suitable amount of space has been allocated
    // in 'data'
    
    Buffer2dC<DataC> data; // Raw data stored in array.
  };
  
  
  template <class DataC>
  ostream & operator<<(ostream & s, const Array2dC<DataC> & arr);
  // Prints into the stream 's'
  
  template <class DataC>
  istream & operator>>(istream & s, Array2dC<DataC> & arr);
  // Reads the array from the stream 's'
  
  ////////////////////////////////////////////////////////////////////////////////
  
  template <class DataC>
  inline 
  void Array2dC<DataC>::ShiftIndexes1(IndexC offset)
  { ShiftIndexes(offset); }
  
  template <class DataC>
  void Array2dC<DataC>::ShiftIndexes2(IndexC offset) {
    for(BufferAccessIterC<BufferAccessC<DataC> > it(*this);it.IsElm();it.Next()) 
      it.Data().ShiftIndexes(offset);
    size2 -= offset.V(); // Keep dim2 uptodate.
  }
  
  template <class DataC>
  void Array2dC<DataC>::ConstructAccess(const IndexRangeC &rng1) {
    Attach(data,rng1);
    const SizeT d2Size = Range2().Size();
    DataC *at = data.Data().ReferenceElm() - Range2().Min().V();
    for(BufferAccessIterC<BufferAccessC<DataC> > it(*this);it;it++,at += d2Size)
      *it = at;
  }
  
  template <class DataC>
  Array2dC<DataC>::Array2dC(SizeT nsize1, SizeT nsize2)
    : RangeBufferAccess2dC<DataC>(IndexRangeC(0,nsize2-1)),
      data(nsize1,nsize2)
  { ConstructAccess(IndexRangeC(0,nsize1-1)); }
  
  template <class DataC>
  Array2dC<DataC>::Array2dC(IndexC minRow,IndexC maxRow,
			    IndexC minCol,IndexC maxCol)
    : RangeBufferAccess2dC<DataC>(IndexRangeC(minCol,maxCol)),
      data(IndexRangeC(minRow,maxRow).Size(),IndexRangeC(minCol,maxCol).Size())
  { 
    RavlAssert(minRow <= maxRow);
    RavlAssert(minCol <= maxCol);
    ConstructAccess(IndexRangeC(minRow,maxRow)); 
  }
  
  template <class DataC>
  Array2dC<DataC>::Array2dC(IntT minRow,IntT maxRow,IntT minCol,IntT maxCol) 
    : RangeBufferAccess2dC<DataC>(IndexRangeC(minCol,maxCol)),
      data(IndexRangeC(minRow,maxRow).Size(),IndexRangeC(minCol,maxCol).Size())    
  {
    RavlAssert(minRow <= maxRow);
    RavlAssert(minCol <= maxCol);
    ConstructAccess(IndexRangeC(minRow,maxRow)); 
  }

  template <class DataC>
  Array2dC<DataC>::Array2dC(const IndexRangeC & rng1,
			    const IndexRangeC & rng2)
    : RangeBufferAccess2dC<DataC>(rng2),
      data(rng1.Size(),rng2.Size())
  { ConstructAccess(rng1); }
  
  template <class DataC>
  Array2dC<DataC>::Array2dC(const Index2dC & min, const Index2dC & max)
    : RangeBufferAccess2dC<DataC>(IndexRangeC(min[1],max[1])),
      data(IndexRangeC(min[0],max[0]).Size(),Range2().Size())
  { ConstructAccess(IndexRangeC(min[0],max[0])); }
  
  template <class DataC>
  Array2dC<DataC>::Array2dC(const IndexRange2dC & rect)
    : RangeBufferAccess2dC<DataC>(rect.Range2()),
      data(rect.Range1().Size(),rect.Range2().Size())
  { ConstructAccess(rect.Range1()); }
  
  template <class DataC>
  Array2dC<DataC>::Array2dC(const IndexRange2dC & rect,const BufferC<DataC> &ndata)
    : RangeBufferAccess2dC<DataC>(rect.Range2()),
      data(ndata,rect.Range1().Size())
  { ConstructAccess(rect.Range1()); }
  
  template <class DataC>
  Array2dC<DataC> 
  Array2dC<DataC>::Copy() const {
    Array2dC<DataC> ret(Rectangle());
    for(BufferAccess2dIter2C<DataC,DataC> it(ret,ret.Range2(),*this,Range2());it;it++)
      it.Data1() = it.Data2();
    return ret;
  }
    
  template <class DataC>
  ostream & operator<<(ostream & s, const Array2dC<DataC> & arr) {
    s << arr.Rectangle() << "\n";
    return s << ((const RangeBufferAccess2dC<DataC> &)arr);
  }
  
  
  template <class DataC>
  istream &operator>>(istream & s, Array2dC<DataC> & arr) {
    IndexRange2dC rect;
    s >> rect;
    arr = Array2dC<DataC>(rect);
    return s >> ((RangeBufferAccess2dC<DataC> &)arr);
  }
  
  
  template<class DataC>
  BinOStreamC &operator<<(BinOStreamC & s, const Array2dC<DataC> & arr) {
    s << arr.Range1().Min() << arr.Range1().Max() << arr.Range2().Min() << arr.Range2().Max();
    return s << ((const RangeBufferAccess2dC<DataC> &)arr);
  }
  
  template<class DataC>
  BinIStreamC &operator>>(BinIStreamC & s, Array2dC<DataC> & arr) {
    IndexRangeC rng1,rng2;
    s >> rng1.Min() >> rng1.Max() >> rng2.Min() >> rng2.Max();
    arr = Array2dC<DataC>(rng1,rng2);
    return s >> ((RangeBufferAccess2dC<DataC> &)arr);
  }
  
  template<class DataC>
  Array2dC<DataC> Array2dC<DataC>::operator+(const Array2dC<DataC> & arr) const {
    Array2dC<DataC> ret(Rectangle());
    for(BufferAccess2dIter3C<DataC,DataC,DataC> it(ret,Range2(),
						   *this,Range2(),
						   arr,arr.Range2());
	it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }
  
  template<class DataC>
  Array2dC<DataC> Array2dC<DataC>::operator-(const Array2dC<DataC> & arr) const {
    Array2dC<DataC> ret(Rectangle());
    for(BufferAccess2dIter3C<DataC,DataC,DataC> it(ret,Range2(),*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;
  }
  
  template<class DataC>
  Array2dC<DataC> Array2dC<DataC>::operator*(const Array2dC<DataC> & arr) const {
    Array2dC<DataC> ret(Rectangle());
    for(BufferAccess2dIter3C<DataC,DataC,DataC> it(ret,Range2(),*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataC>
  Array2dC<DataC> Array2dC<DataC>::operator/(const Array2dC<DataC> & arr) const {
    Array2dC<DataC> ret(Rectangle());
    for(BufferAccess2dIter3C<DataC,DataC,DataC> it(ret,Range2(),*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() / it.Data3();
    return ret;
  }
  
  template<class DataC>
  Array2dC<DataC> Array2dC<DataC>::operator+(const DataC &number) const {
    Array2dC<DataC> ret(Rectangle());
    for(BufferAccess2dIter2C<DataC,DataC> it(ret,Range2(),Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() + number;
    return ret;
  }
  
  template<class DataC>
  Array2dC<DataC> Array2dC<DataC>::operator-(const DataC &number) const {
    Array2dC<DataC> ret(Rectangle());
    for(BufferAccess2dIter2C<DataC,DataC> it(ret,Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() - number;
    return ret;
  }
  
  template<class DataC>
  Array2dC<DataC> Array2dC<DataC>::operator*(const DataC &number) const {
    Array2dC<DataC> ret(Rectangle());
    for(BufferAccess2dIter2C<DataC,DataC> it(ret,Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() * number;
    return ret;
  }
  
  template<class DataC>
  Array2dC<DataC> Array2dC<DataC>::operator/(const DataC &number) const {
    Array2dC<DataC> ret(Rectangle());
    for(BufferAccess2dIter2C<DataC,DataC> it(ret,Range2(),arr,arr.Range2());it;it++)
      it.Data1() = it.Data2() / number;
    return ret;
  }
    
  template<class DataC>
  const Array2dC<DataC> & Array2dC<DataC>::operator+=(const Array2dC<DataC> & arr) {
    for(BufferAccess2dIter2C<DataC,DataC> it(*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() += it.Data2();
    return *this;
  }
  
  template<class DataC>
  const Array2dC<DataC> & Array2dC<DataC>::operator-=(const Array2dC<DataC> & arr) {
    for(BufferAccess2dIter2C<DataC,DataC> it(*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() -= it.Data2();
    return *this;
  }
    
  template<class DataC>
  const Array2dC<DataC> & Array2dC<DataC>::operator*=(const Array2dC<DataC> & arr) {
    for(BufferAccess2dIter2C<DataC,DataC> it(*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() *= it.Data2();
    return *this;
  }
    
  template<class DataC>
  const Array2dC<DataC> & Array2dC<DataC>::operator/=(const Array2dC<DataC> & arr) {
    for(BufferAccess2dIter2C<DataC,DataC> it(*this,Range2(),arr,arr.Range2());it;it++)
      it.Data1() /= it.Data2();
    return *this;
  }
  
  template<class DataC>
  const Array2dC<DataC> & Array2dC<DataC>::operator+=(const DataC &number) {
    for(BufferAccess2dIterC<DataC> it(*this,Range2());it;it++)
      it.Data1() += number;
    return *this;
  }
    
  template<class DataC>
  const Array2dC<DataC> & Array2dC<DataC>::operator-=(const DataC &number) {
    for(BufferAccess2dIterC<DataC> it(*this,Range2());it;it++)
      it.Data1() -= number;
    return *this;
  }
  
  template<class DataC>
  const Array2dC<DataC> & Array2dC<DataC>::operator*=(const DataC &number) {
    for(BufferAccess2dIterC<DataC> it(*this,Range2());it;it++)
      it.Data1() *= number;
    return *this;
  }
  
  template<class DataC>
  const Array2dC<DataC> & Array2dC<DataC>::operator/=(const DataC &number) {
    for(BufferAccess2dIterC<DataC> it(*this,Range2());it;it++)
      it.Data() /= number;
    return *this;
  }
  
}
#endif

