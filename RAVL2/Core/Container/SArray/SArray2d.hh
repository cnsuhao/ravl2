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
//! docentry="Ravl.API.Core.Arrays.2D"
//! rcsid="$Id$"
//! file="Ravl/Core/Container/SArray/SArray2d.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="10/09/1998"

#include "Ravl/SizeBufferAccess2d.hh"
#include "Ravl/Buffer2d.hh"
#include "Ravl/AttachedBuffer2d.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/BufferAccess2dIter.hh"
#include "Ravl/BufferAccess2dIter2.hh"
#include "Ravl/BufferAccess2dIter3.hh"

namespace RavlN {
  
  template<class DataT> class SArray1dC;
  template<class DataT> class Array2dC;
  template<class DataT> class SArray2dIterC;
  template<class DataT> class Slice1dC;
  template<class DataT> class Slice1dIterC;
  
  //! userlevel=Advanced  
  //: Simple 2 dimensional array.
  // For each dimension of the array, the lower index is 0.

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
    // Creates a zero size array.
    
    SArray2dC(SizeT dim1,SizeT dim2)
      : m_data(dim1,dim2)
    { Attach(m_data,dim1,dim2); }
    //: Constructor.
    // Create a dim1 by dim2 array.
    
    SArray2dC(IndexC dim1,IndexC dim2)
      : m_data(dim1.V(),dim2.V())
    { Attach(m_data,dim1.V(),dim2.V()); }
    //: Constructor.
    // Create a dim1 by dim2 array.
    
    SArray2dC(const Index2dC &size)
      : m_data(size[0].V(),size[1].V())
    { Attach(m_data,size[0].V(),size[1].V()); }
    //: Constructor.
    // Create a size[0] by size[1] array.
    
    SArray2dC(const BufferC<DataT> & bf, SizeT size1,SizeT size2,SizeT startOffset = 0,IntT byteStride = 0)
      : m_data(AttachedBuffer2dC<DataT>(bf,size1,size2,byteStride))
    { Attach(m_data,size1,size2); }
    //: Constructor using the buffer 'bf'. 
    // This can be used, for example to view a 1d array, as a 2d array.
    // startOffset is the location in the buffer to use as 0,0.
    // Both start offset and byteStride are in bytes.
    // If stride is set to zero, size2 is used.

    SArray2dC(SArray2dC<DataT> &arr,SizeT size1,SizeT size2)
      : SizeBufferAccess2dC<DataT>(arr,size1,size2),
        m_data(arr.m_data)
    {}
    //: Construct an access to a sub array of this one.
    
    SArray2dC(SArray2dC<DataT> &arr,const IndexRange2dC &rng)
      : SizeBufferAccess2dC<DataT>(&(arr[rng.TRow()][rng.LCol()]),rng.Rows(),rng.Cols(),arr.Buffer().ByteStride()),
        m_data(arr.Buffer())
    {
      RavlAssert(rng.TRow() >= 0 && rng.LCol() >= 0);
      RavlAssert(rng.BRow() < arr.Size1() && rng.RCol() < arr.Size2());
    }
    //: Create a new access to 'rng' of 'arr'.
    // 'rng' must be within 'arr'. The origin of the new array will be at 'rng.Origin()' of 'arr'.
    
    SArray2dC(DataT *data,SizeT size1,SizeT size2,bool copyMemory = false,bool freeMemory = false,IntT byteStride = 0)
      : m_data(data,size1,size2,byteStride,copyMemory,freeMemory)
    { Attach(m_data,size1,size2); }
    //: Create size1 x size2 array from memory given in 'data'
    // If freeMemory is true it 'data' will be freed with a 'delete []' call when no longer required.
    
    static SArray2dC<DataT> ConstructAligned(const SizeT dim1,const SizeT dim2,UIntT align) { 
      RavlAssert((align % sizeof(DataT)) == 0); // We should do something about the requirement.
      IntT stride = dim2;
      const UIntT elemAlign = align / sizeof(DataT);
      const UIntT remainder = (dim2 % elemAlign);
      if(remainder > 0) {
        RavlAssert(remainder < elemAlign);
        stride += elemAlign - remainder;
      }
      return SArray2dC(SingleBufferC<DataT>(stride*dim1,align), dim1,dim2,0,stride); 
    }
    //: Creates an uninitialized array with the range <0, 'dim1'-1>,<0, 'dim2'-1> and 
    //: the given byte alignment of the start of each row.
    // align must be a power of 2.
    // Currently the align must be an integer muliple of the element size.
    
    SArray2dC<DataT> Copy() const;
    //: Copy array.
    
    inline SizeT Size1() const
    { return SizeBufferAccess2dC<DataT>::Size1(); }
    //: Range of 1st index is [0..Size1()-1]
    
    inline SizeT Size2() const
    { return SizeBufferAccess2dC<DataT>::Size2(); }
    //: Range of 2nd index is [0..Size2()-1]
    
    //:------------------
    // Special operations
    
    Buffer2dC<DataT> &Buffer() 
    { return m_data; }
    //: Access base data buffer.
    // Experts only!
    
    const Buffer2dC<DataT> &Buffer() const
    { return m_data; }
    //: Constant access base data buffer.
    // Experts only!
    
    SArray1dC<DataT> AsVector(bool alwaysCopy = false);
    //: Access 2d array as 1d vector.
    // This will only copy the data if the data isn't continuous or
    // alwaysCopy is true, this can make it much more effecient than
    // a straigh copy.

    SArray2dC<DataT> operator+(const SArray2dC<DataT> & arr) const;
    // Sums 2 numerical arrays. The operator returns the result as a new array.
    
    SArray2dC<DataT> operator-(const SArray2dC<DataT> & arr) const;
    // Subtracts 2 numerical arrays. The operator returns
    // the result as a new array.
    
    SArray2dC<DataT> operator*(const SArray2dC<DataT> & arr) const;
    // Multiplies 2 numerical arrays. The operator returns the result as a new array.
    
    SArray2dC<DataT> operator/(const SArray2dC<DataT> & arr) const;
    // Divides 2 numerical arrays. The operator returns
    // the result as a new array.
    
    SArray2dC<DataT> operator*(const DataT &number) const;
    // Multiplies the array by the 'number'. The operator
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
    
    bool operator==(const SArray2dC<DataT> &op) const;
    //: Do arrays have identical ranges and contents ?
    
    bool operator!=(const SArray2dC<DataT> &op) const
    { return !operator==(op); }
    //: Do arrays have different ranges and contents ?
    
    DataT SumOfSqr() const;
    //: Calculate the sum of the squares of all the elements in the array
    
    DataT Sum() const;      
    //: Returns the sum all elements of the array.
    
    Slice1dC<DataT> Diagonal() {
      return Slice1dC<DataT>(m_data,
			     &((*this)[0][0]),
			     Min(Size1(),Size2()),
			     this->ByteStride()+sizeof(DataT));
    }
    //: Take a slice along the diagonal of the array.
    
    SArray1dC<DataT> SliceRow(IndexC i)
    { return SArray1dC<DataT>(m_data,(*this)[i]); }
    //: Access row as 1d array.
    // NB. Changes made to the slice will also affect this array!
    
    Slice1dC<DataT> SliceColumn(IndexC i) { 
      return Slice1dC<DataT>(m_data,
			     &((*this)[0][i]),
			     Size1(),
			     this->ByteStride());
    }
    //: Access column as 1d slice.
    // NB. Changes made to the slice will also affect this array!
    
    void SetColumn(IndexC i,const SArray1dC<DataT> &val);
    //: Set the values in the column i to those in 'val'.
    // 'val' must have a size equal to the number of rows.
    
    void SetRow(IndexC i,const SArray1dC<DataT> &val);
    //: Set the values in the row i to those in 'val'.
    // 'val' must have a size equal to the number of columns
    
    void SetSubArray(const Index2dC &origin,const SArray2dC<DataT> &vals);
    //: Set sub array of this one. 
    // The origin of 'vals' will be places at 'origin' of this array.
    // NOTE: all of vals must fit within this array.
    
  protected:
    SArray2dC(Buffer2dC<DataT> & bf, 
	      const SizeBufferAccess2dC<DataT> &ab,
	      SizeT dim1,SizeT dim2)
      : SizeBufferAccess2dC<DataT>(ab,dim1,dim2,ab.ByteStride()),
	m_data(bf)
    {}
    //: Construct from a buffer, and an existing buffer access.
        
    Buffer2dC<DataT> m_data; // Handle to data.
    
    friend class Array2dC<DataT>;
  };
  
  template <class DataT>
  ostream & operator<<(ostream & s, const SArray2dC<DataT> & arr) {
    s  << arr.Size1() << " " << arr.Size2() << "\n";
    s << ((SizeBufferAccess2dC<DataT> &) arr);
    return s;
  }
  // Prints into the stream 's'
  
  template <class DataT>
  istream & operator>>(istream & s, SArray2dC<DataT> & arr) {
    SizeT size1,size2;
    s >> size1 >> size2;
    arr = SArray2dC<DataT>(size1,size2);
    s >> ((SizeBufferAccess2dC<DataT> &) arr);
    return s;
  }
  // Reads the array from the stream 's'
  
  template<class DataT>
  BinOStreamC &operator<<(BinOStreamC & s, const SArray2dC<DataT> & arr) {
    s << arr.Size1() << arr.Size2();
    s << ((SizeBufferAccess2dC<DataT> &) arr);
    return s;
  }

  template<class DataT>
  BinIStreamC &operator>>(BinIStreamC & s, SArray2dC<DataT> & arr) {
    SizeT size1,size2;
    s >> size1 >> size2;
    SizeT size = size1 * size2;
    if((size * sizeof(DataT)) > s.ArraySizeLimit() || size > s.ArraySizeLimit())
      throw ExceptionOutOfRangeC("Incoming array size exceeds limit for stream.");
    arr = SArray2dC<DataT>(size1,size2);
    return s >> ((SizeBufferAccess2dC<DataT> &) arr);
  }
  
  /////////////////////////////////////////////////////
    
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::Copy() const {
    SArray2dC<DataT> newun(this->Size1(),this->Size2()); // Allocate new array.
    for(BufferAccess2dIter2C<DataT,DataT > it(*this,newun,this->Size1(),this->Size2());
	it;it++)
      it.Data2() = it.Data1();
    return newun;
  }

  template<class DataT>
  SArray1dC<DataT> SArray2dC<DataT>::AsVector(bool alwaysCopy) {
    if(!alwaysCopy && this->IsContinuous()) {
      DataT *start = &((*this)[0][0]);
      return SArray1dC<DataT>(m_data,SizeBufferAccessC<DataT>(start,Size1() * Size2()));
    }
    SArray1dC<DataT> ret(Size1() * Size2());
    BufferAccessIterC<DataT> rit(ret);
    for(BufferAccess2dIterC<DataT> it(*this);it;it++,rit++)
      *rit = *it;
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator+(const SArray2dC<DataT> & arr) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,*this,arr,
                                                   ret.Size1(),ret.Size2());
	it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator-(const SArray2dC<DataT> & arr) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,*this,arr,ret.Size1(),ret.Size2());it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator*(const SArray2dC<DataT> & arr) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,*this,arr,ret.Size1(),ret.Size2());it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator/(const SArray2dC<DataT> & arr) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,*this,arr,ret.Size1(),ret.Size2());it;it++)
      it.Data1() = it.Data2() / it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator+(const DataT &number) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,*this,ret.Size1(),ret.Size2());it;it++)
      it.Data1() = it.Data2() + number;
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator-(const DataT &number) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,*this,ret.Size1(),ret.Size2());it;it++)
      it.Data1() = it.Data2() - number;
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator*(const DataT &number) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,*this,ret.Size1(),ret.Size2());it;it++)
      it.Data1() = it.Data2() * number;
    return ret;
  }
  
  template<class DataT>
  SArray2dC<DataT> SArray2dC<DataT>::operator/(const DataT &number) const {
    SArray2dC<DataT> ret(Size1(),Size2());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,*this,ret.Size1(),ret.Size2());it;it++)
      it.Data1() = it.Data2() / number;
    return ret;
  }
    
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator+=(const SArray2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,arr,this->Size1(),this->Size2());it;it++)
      it.Data1() += it.Data2();
    return *this;
  }
  
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator-=(const SArray2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,arr,this->Size1(),this->Size2());it;it++)
      it.Data1() -= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator*=(const SArray2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,arr,this->Size1(),this->Size2());it;it++)
      it.Data1() *= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator/=(const SArray2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,arr,this->Size1(),this->Size2());it;it++)
      it.Data1() /= it.Data2();
    return *this;
  }
  
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator+=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this);it;it++)
      it.Data1() += number;
    return *this;
  }
    
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator-=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this);it;it++)
      it.Data1() -= number;
    return *this;
  }
  
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator*=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this);it;it++)
      it.Data1() *= number;
    return *this;
  }
  
  template<class DataT>
  const SArray2dC<DataT> & SArray2dC<DataT>::operator/=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this);it;it++)
      it.Data() /= number;
    return *this;
  }
  
  template<class DataT>
  bool SArray2dC<DataT>::operator==(const SArray2dC<DataT> &op) const {
    if(this->Size() != op.Size()) return false;
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,op,this->Size1(),this->Size2());it;it++)
      if(it.Data1() != it.Data2()) return false;
    return true;
  }
  
  template<class DataT>
  DataT SArray2dC<DataT>::Sum() const {
    BufferAccess2dIterC<DataT> it(*this);
    if(!it) {
      DataT ret;
      SetZero(ret);
      return ret;
    }
    DataT ret = StdCopy(*it);
    for(it++;it;it++)
      ret += *it;
    return ret;
  }
  
  template<class DataT>
  DataT SArray2dC<DataT>::SumOfSqr() const {
    BufferAccess2dIterC<DataT> it(*this);
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
    char *d1 = reinterpret_cast<char *>(&((*this)[0][i]));
    const int s = this->ByteStride();
    for(BufferAccessIterC<DataT> it(val);it;it++,d1 += s)
      *reinterpret_cast<DataT*>(d1) = *it;
  }
  
  template<class DataT>
  void SArray2dC<DataT>::SetRow(IndexC i,const SArray1dC<DataT> &val) {
    RavlAssert(val.Size() == Size2());
    for(BufferAccessIter2C<DataT,DataT> it((*this)[i],val);it;it++)
      it.Data1() = it.Data2();
  }

  template<class DataT>
  void SArray2dC<DataT>::SetSubArray(const Index2dC &origin,const SArray2dC<DataT> &vals) {
    IndexRangeC trng1(origin[0],(origin[0] + vals.Size1()) - 1);
    IndexRangeC trng2(origin[1],(origin[1] + vals.Size2()) - 1);
    RavlAssert(trng1.Max() < Size1());
    RavlAssert(trng2.Max() < Size2());
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,this->ByteStride(),trng1,trng2,
					     vals,vals.ByteStride(),IndexRangeC(0,vals.Size1()-1),IndexRangeC(0,vals.Size2()-1));
	it;it++)
      it.Data1() = it.Data2();
  }
  
}

#endif
