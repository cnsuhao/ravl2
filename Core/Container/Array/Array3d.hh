// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLARRAY3D_HH
#define RAVLARRAY3D_HH
///////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Array/Array3d.hh"
//! lib=RavlCore
//! author="Radek Marik"
//! date="2/5/1993"
//! docentry="Ravl.Core.Arrays.3D"
//! rcsid="$Id$"
//! example=exArray3d.cc
//! userlevel=Normal

#include "Ravl/RBfAcc3d.hh"
#include "Ravl/Buffer3d.hh"
#include "Ravl/Index3d.hh"
#include "Ravl/IndexRange3d.hh"
#include "Ravl/BfAcc3Iter.hh"
#include "Ravl/BfAcc3Iter2.hh"
#include "Ravl/BfAcc3Iter3.hh"

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
  
  template <class DataT>
  class Array3dC
    : public RangeBufferAccess3dC<DataT>
  {
  public:
    Array3dC()
      {}
    //: Creates an empty 3D array.
    
    Array3dC(SizeT dim1, SizeT dim2, SizeT dim3);
    //: Creates 3D array with the range < <0,dim1-1>, <0,dim2-1> >
    
    Array3dC(IntT minI,IntT maxI,IntT minJ,IntT maxJ,IntT minK,IntT maxK);
    //: Creates 3D array with the range minRow to maxRow by minCol to maxCol.
    
    Array3dC(IndexC minI,IndexC maxI,IndexC minJ,IndexC maxJ,IndexC minK,IndexC maxK);
    //: Creates 3D array with the range minRow to maxRow by minCol to maxCol.
    
    Array3dC(const Index3dC & min, const Index3dC & max);
    //: Creates 3D array with the range < <min[0], max[0]>, <min[1], max[1]> >.
    
    Array3dC(const IndexRangeC & rng1, const IndexRangeC & rng2, const IndexRangeC & rng3);
    //: Creates 3D array with the range <rng1, rng2>
    
    Array3dC(const IndexRange3dC & rect);
    //: Create 3D array with the range covering indexes in 'rect'
    
    Array3dC(const IndexRange3dC & rect,const BufferC<DataT> &data);
    //: Create 3D array with the range covering indexes in 'rect' from data.
    // NB. It is the users responsability to ensure that 'data' is
    // large enought to contain 'rect'.
    
    Array3dC(const Array3dC<DataT> &arr,const IndexRange3dC & rect);
    //: Create a sub array of 'arr' covering indexes 'rect'.
    
    Array3dC<DataT> Copy() const;
    //: Make a copy of the array.
    
#if 0
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
#endif
    
    inline const Array3dC<DataT> & Array3d() const
      { return(*this); }
    //: access to the constant object
    
    inline Array3dC<DataT> & Array3d()
      { return(*this); }
    //: access to the object

#if 0    
    inline void ShiftIndexes1(IndexC offset);
    //: All indexes of Range1() will be changed by 'offset'.
    // The range will be shifted by -offset.
    
    void ShiftIndexes2(IndexC offset);
    //: All indexes of Range2() will be changed by 'offset'.
    // The range will be shifted by -offset.
#endif
    
    Array3dC<DataT> operator+(const Array3dC<DataT> & arr) const;
    //: Sums 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array3dC<DataT> operator-(const Array3dC<DataT> & arr) const;
    //: Subtracts 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array3dC<DataT> operator*(const Array3dC<DataT> & arr) const;
    //: Mutliplies 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array3dC<DataT> operator/(const Array3dC<DataT> & arr) const;
    //: Divides 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array3dC<DataT> operator*(const DataT &number) const;
    //: Multiplys the array by the 'number'. 
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
    
  protected:
    void ConstructAccess(const IndexRangeC &rng1);
    //: Construct access for buffer.
    // This assumes a suitable amount of space has been allocated
    // in 'data'
    
    Buffer3dC<DataT> data; // Raw data stored in array.
  };
  
  
  template <class DataT>
  ostream & operator<<(ostream & s, const Array3dC<DataT> & arr);
  // Prints into the stream 's'
  
  template <class DataT>
  istream & operator>>(istream & s, Array3dC<DataT> & arr);
  // Reads the array from the stream 's'
  
  ////////////////////////////////////////////////////////////////////////////////
  
#if 0
  template <class DataT>
  inline 
  void Array3dC<DataT>::ShiftIndexes1(IndexC offset)
  { ShiftIndexes(offset); }
  
  template <class DataT>
  void Array3dC<DataT>::ShiftIndexes2(IndexC offset) {
    for(BufferAccessIterC<BufferAccessC<DataT> > it(*this);it.IsElm();it.Next()) 
      it.Data().ShiftIndexes(offset);
    size2 -= offset.V(); // Keep dim2 uptodate.
  }
#endif
  
  template <class DataT>
  void Array3dC<DataT>::ConstructAccess(const IndexRangeC &rng1) {
    Attach(data,rng1);
    const SizeT d3Size = Range3().Size();
    const SizeT d2Size = Range2().Size();
    BufferAccessC<DataT>  *acc2 = data.DataIndex().ReferenceElm() - Range2().Min().V();
    DataT *atData = data.Data().ReferenceElm() - Range3().Min().V();
    for(BufferAccessIterC<BufferAccessC<BufferAccessC<DataT> > > it(*this,rng1);it;it++,acc2 += d2Size) {
      *it = acc2;
      for(BufferAccessIterC<BufferAccessC<DataT> > it2(*it,Range2());it2;it2++,atData += d3Size)
	*it2 = atData;
    }
  }
  
  template <class DataT>
  Array3dC<DataT>::Array3dC(SizeT nsize1, SizeT nsize2, SizeT nsize3)
    : RangeBufferAccess3dC<DataT>(IndexRangeC(0,nsize2-1),IndexRangeC(0,nsize3-1)),
      data(nsize1,nsize2,nsize3)
  { ConstructAccess(IndexRangeC(0,nsize1-1)); }
  
  template <class DataT>
  Array3dC<DataT>::Array3dC(IndexC minI,IndexC maxI,
			    IndexC minJ,IndexC maxJ,
			    IndexC minK,IndexC maxK)
    : RangeBufferAccess3dC<DataT>(IndexRangeC(minJ,maxI),IndexRangeC(minK,maxK)),
      data(IndexRangeC(minI,maxI).Size(),IndexRangeC(minJ,maxJ).Size(),IndexRangeC(minK,maxK).Size())
  {
    RavlAssert(minI <= maxI);
    RavlAssert(minJ <= maxJ);
    RavlAssert(minK <= maxK);
    ConstructAccess(IndexRangeC(minI,maxI)); 
  }
  
  template <class DataT>
  Array3dC<DataT>::Array3dC(IntT minI,IntT maxI,IntT minJ,IntT maxJ,IntT minK,IntT maxK) 
    : RangeBufferAccess3dC<DataT>(IndexRangeC(minJ,maxJ),IndexRangeC(minK,maxK)),
      data(IndexRangeC(minI,maxI).Size(),IndexRangeC(minJ,maxJ).Size(),IndexRangeC(minK,maxK).Size())
  {
    RavlAssert(minI <= maxI);
    RavlAssert(minJ <= maxJ);
    RavlAssert(minK <= maxK);
    ConstructAccess(IndexRangeC(minI,maxI)); 
  }

  template <class DataT>
  Array3dC<DataT>::Array3dC(const IndexRangeC & rng1,
			    const IndexRangeC & rng2,
			    const IndexRangeC & rng3)
    : RangeBufferAccess3dC<DataT>(rng2,rng3),
      data(rng1.Size(),rng2.Size(),rng3.Size())
  { ConstructAccess(rng1); }
  
  template <class DataT>
  Array3dC<DataT>::Array3dC(const Index3dC & min, const Index3dC & max)
    : RangeBufferAccess3dC<DataT>(IndexRangeC(min[1],max[1])),
      data(IndexRangeC(min[0],max[0]).Size(),Range2().Size())
  { ConstructAccess(IndexRangeC(min[0],max[0])); }
  
  template <class DataT>
  Array3dC<DataT>::Array3dC(const IndexRange3dC & frame)
    : RangeBufferAccess3dC<DataT>(frame.Range2(),frame.Range3()),
      data(frame.Range1().Size(),frame.Range2().Size(),frame.Range3().Size())
  { ConstructAccess(frame.Range1()); }
  
  template <class DataT>
  Array3dC<DataT>::Array3dC(const IndexRange3dC & frame,const BufferC<DataT> &ndata)
    : RangeBufferAccess3dC<DataT>(frame.Range2(),frame.Range3()),
      data(ndata,frame.Range1().Size())
  { ConstructAccess(frame.Range1()); }

  template <class DataT>
  Array3dC<DataT>::Array3dC(const Array3dC<DataT> &arr,const IndexRange3dC & frame) 
    : RangeBufferAccess3dC<DataT> (arr,frame),
    data(arr.data)
  {}
  
  template <class DataT>
  Array3dC<DataT> 
  Array3dC<DataT>::Copy() const {
    Array3dC<DataT> ret(Frame());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,ret.Range2(),*this,Range2());it;it++)
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
    s << arr.Range1().Min() << arr.Range1().Max() << arr.Range2().Min() << arr.Range2().Max();
    return s << ((const RangeBufferAccess3dC<DataT> &)arr);
  }
  
  template<class DataT>
  BinIStreamC &operator>>(BinIStreamC & s, Array3dC<DataT> & arr) {
    IndexRangeC rng1,rng2;
    s >> rng1.Min() >> rng1.Max() >> rng2.Min() >> rng2.Max();
    arr = Array3dC<DataT>(rng1,rng2);
    return s >> ((RangeBufferAccess3dC<DataT> &)arr);
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator+(const Array3dC<DataT> & arr) const {
    Array3dC<DataT> ret(Frame());
    for(BufferAccess3dIter3C<DataT,DataT,DataT> it(ret,Range2(),Range3(),
						   *this,Range2(),Range3(),
						   arr,arr.Range2(),arr.Range3());
	it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator-(const Array3dC<DataT> & arr) const {
    Array3dC<DataT> ret(Frame());
    for(BufferAccess3dIter3C<DataT,DataT,DataT> it(ret,Range2(),Range3(),
						   *this,Range2(),Range3(),
						   arr,arr.Range2(),arr.Range3());it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator*(const Array3dC<DataT> & arr) const {
    Array3dC<DataT> ret(Frame());
    for(BufferAccess3dIter3C<DataT,DataT,DataT> it(ret,Range2(),Range3(),
						   *this,Range2(),Range3(),
						   arr,arr.Range2(),arr.Range3());it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator/(const Array3dC<DataT> & arr) const {
    Array3dC<DataT> ret(Frame());
    for(BufferAccess3dIter3C<DataT,DataT,DataT> it(ret,Range2(),Range3(),
						   *this,Range2(),Range3(),
						   arr,arr.Range2(),arr.Range3());it;it++)
      it.Data1() = it.Data2() / it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator+(const DataT &number) const {
    Array3dC<DataT> ret(Frame());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,Range2(),Range3(),
					     arr,arr.Range2(),arr.Range3());it;it++)
      it.Data1() = it.Data2() + number;
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator-(const DataT &number) const {
    Array3dC<DataT> ret(Frame());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,Range2(),Range3(),
					     arr,arr.Range2(),arr,arr.Range3());it;it++)
      it.Data1() = it.Data2() - number;
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator*(const DataT &number) const {
    Array3dC<DataT> ret(Frame());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,Range2(),Range3(),
					     arr,arr.Range2(),arr.Range3());it;it++)
      it.Data1() = it.Data2() * number;
    return ret;
  }
  
  template<class DataT>
  Array3dC<DataT> Array3dC<DataT>::operator/(const DataT &number) const {
    Array3dC<DataT> ret(Frame());
    for(BufferAccess3dIter2C<DataT,DataT> it(ret,Range2(),Range3(),
					     arr,arr.Range2(),arr.Range3());it;it++)
      it.Data1() = it.Data2() / number;
    return ret;
  }
    
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator+=(const Array3dC<DataT> & arr) {
    for(BufferAccess3dIter2C<DataT,DataT> it(*this,Range2(),Range3(),
					     arr,arr.Range2(),arr.Range3());it;it++)
      it.Data1() += it.Data2();
    return *this;
  }
  
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator-=(const Array3dC<DataT> & arr) {
    for(BufferAccess3dIter2C<DataT,DataT> it(*this,Range2(),Range3(),
					     arr,arr.Range2(),arr.Range3());it;it++)
      it.Data1() -= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator*=(const Array3dC<DataT> & arr) {
    for(BufferAccess3dIter2C<DataT,DataT> it(*this,Range2(),Range3(),
					     arr,arr.Range2(),arr.Range3());it;it++)
      it.Data1() *= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator/=(const Array3dC<DataT> & arr) {
    for(BufferAccess3dIter2C<DataT,DataT> it(*this,Range2(),Range3(),
					     arr,arr.Range2(),arr.Range3());it;it++)
      it.Data1() /= it.Data2();
    return *this;
  }
  
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator+=(const DataT &number) {
    for(BufferAccess3dIterC<DataT> it(*this,Range2(),Range3());it;it++)
      it.Data1() += number;
    return *this;
  }
    
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator-=(const DataT &number) {
    for(BufferAccess3dIterC<DataT> it(*this,Range2(),Range3());it;it++)
      it.Data1() -= number;
    return *this;
  }
  
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator*=(const DataT &number) {
    for(BufferAccess3dIterC<DataT> it(*this,Range2(),Range3());it;it++)
      it.Data1() *= number;
    return *this;
  }
  
  template<class DataT>
  const Array3dC<DataT> & Array3dC<DataT>::operator/=(const DataT &number) {
    for(BufferAccess3dIterC<DataT> it(*this,Range2(),Range3());it;it++)
      it.Data() /= number;
    return *this;
  }
  
}
#endif

