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
//! docentry="Ravl.API.Core.Arrays.2D"
//! rcsid="$Id$"
//! example=exArray2d.cc
//! userlevel=Normal

#include "Ravl/RangeBufferAccess2d.hh"
#include "Ravl/Buffer2d.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/IndexRange2d.hh"
#include "Ravl/BufferAccess2dIter.hh"
#include "Ravl/BufferAccessIter.hh"
#include "Ravl/BufferAccess2dIter2.hh"
#include "Ravl/BufferAccess2dIter3.hh"
#include "Ravl/SArray2d.hh"
#include "Ravl/Math.hh"
#include "Ravl/Slice1d.hh"
#include "Ravl/Types.hh" 
#include "Ravl/DeepCopy.hh"
#include "Ravl/AttachedBuffer2d.hh"

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
    
    Array2dC(SizeT rows, SizeT cols)
      : m_data(rows,cols)
    { Attach(m_data,rows,cols); }
    //: Creates 2D array with the range &lt; &lt;0,rows-1&gt;, &lt;0,cols-1&gt; &gt;
    
    Array2dC(IntT minRow,IntT maxRow,IntT minCol,IntT maxCol)
      : m_data(IndexRangeC(minRow,maxRow).Size(),IndexRangeC(minCol,maxCol).Size())
    {
      RavlAssert(minRow <= maxRow);
      RavlAssert(minCol <= maxCol);
      Attach(m_data,IndexRange2dC(minRow,maxRow,minCol,maxCol));
    }
    //: Creates 2D array with the range minRow to maxRow by minCol to maxCol.
    
    Array2dC(IndexC minRow,IndexC maxRow,IndexC minCol,IndexC maxCol)
      : m_data(IndexRangeC(minRow,maxRow).Size(),IndexRangeC(minCol,maxCol).Size())
    {
      RavlAssert(minRow <= maxRow);
      RavlAssert(minCol <= maxCol);
      Attach(m_data,IndexRange2dC(minRow,maxRow,minCol,maxCol));
    }
    //: Creates 2D array with the range minRow to maxRow by minCol to maxCol.
    
    Array2dC(const Index2dC & min, const Index2dC & max)
      : m_data(IndexRangeC(min[0],max[0]).Size(),IndexRangeC(min[1],max[1]).Size())
    { Attach(m_data,IndexRange2dC(min[0],max[0],min[1],max[1])); }
    //: Creates 2D array with the range &lt; &lt;min[0], max[0]&gt;, &lt;min[1], max[1]&gt; &gt;.
    // Index 0 ~ rows; index 1 ~ columns
    
    Array2dC(const IndexRangeC & rowRange, const IndexRangeC & colRange)
      : m_data(rowRange.Size(),colRange.Size())
    { Attach(m_data,rowRange,colRange); }
    //: Creates 2D array with the range &lt;rowRng, colRng&gt;
    
    Array2dC(const IndexRange2dC & rect)
      : m_data(rect.Range1().Size(),rect.Range2().Size())
    { Attach(m_data,rect); }
    //: Create 2D array with the range covering indices in 'rect'
    
    Array2dC(const BufferC<DataT> &data,const IndexRange2dC & rect,DataT *refElement,IntT byteStride)
      : m_data(AttachedBuffer2dC<DataT>(data,rect.Rows(),rect.Cols(),byteStride))
    { Attach(refElement,rect,byteStride); }
    //: Create 2D array with the range covering indices in 'rect' from data.
    // Note: It is the users responsibility to ensure that 'data' is
    // large enough to contain 'rect'. refElement is taken to be the origin. 0,0
    
    Array2dC(const Array2dC<DataT> &arr,const IndexRange2dC & rect)
      : RangeBufferAccess2dC<DataT> (arr,rect),
        m_data(arr.m_data)
    {}
    //: Create a sub array of 'arr' covering indices 'rect'.
    // Note: This does NOT copy data elements, its just another view on the same data.
    
    Array2dC(const Array2dC<DataT> &arr,const IndexRange2dC & rect,const Index2dC &newOrigin)
      : m_data(arr.m_data)
    {
      IndexRange2dC newFrame(newOrigin,rect.End() + rect.Size());
      Attach(this->PointerTo(newOrigin.Row(),newOrigin.Col()),newFrame,arr.ByteStride());
    }
    //: Create a sub array of 'arr' covering indices 'rect', with origin 'newOrigin'.
    // Note: This does NOT copy data elements, its just another view on the same data.
    
    Array2dC(const SArray2dC<DataT> &sarr)
      : RangeBufferAccess2dC<DataT>(sarr.BufferAccess(),
                                    IndexRangeC(0,sarr.Range1().Size()-1),
                                    IndexRangeC(0,sarr.Range2().Size()-1),
                                    sarr.ByteStride()),
        m_data(sarr.m_data)
    {}
    //: Construct 2d array from SArray.
    // Note: This does NOT copy data elements, its just another view on the same data.

    Array2dC(Buffer2dC<DataT> &buf,const RangeBufferAccess2dC<DataT> &rbf)
      : RangeBufferAccess2dC<DataT>(rbf),
        m_data(buf)
    {}
    //: Construct an array with buffer access 'rbf' and data area 'buf'
    // Expert users only! This allows the creation of arrays that have
    // unusual access structures. e.g. de-interlacing an image without 
    // copying any data.
    
    Array2dC<DataT> Copy() const;
    //: Make a copy of the array.

    Array2dC<DataT> DeepCopy (UIntT levels = (UIntT) -1 ) const ; 
    //: Make a deep copy of this array
    
    inline SArray2dC<DataT> SArray2d(bool doShift = false);
    //: Create an access as an SArray.
    // Note: This does NOT copy the data, it only make a new access to it.
    // If doShift is true element Range1().Min(),Range2().Min() will
    // become 0,0 of the SArray. Otherwise if the array does not 
    // contain element '0,0' an error will occur in check mode, 
    // when optimised is enabled an empty array  will be returned. 
    
    SArray1dC<DataT> AsVector(bool alwaysCopy = false);
    //: Access 2d array as 1d vector.
    // This will only copy the data if the data isn't continuous or
    // alwaysCopy is true, this can make it much more efficient than
    // a straight copy.
    
    Array1dC<DataT> SliceRow(IndexC i)
    { return Array1dC<DataT>(m_data,(*this)[i]); }
    //: Access row as 1d array.
    // Note: Changes made to the slice will also affect this array!
    
    Slice1dC<DataT> SliceColumn(IndexC i) { 
      DataT *refElm = reinterpret_cast<DataT *>(reinterpret_cast<char *>(&((*this)[Range1().Min()][i])) - (Range1().Min().V() * this->ByteStride()));
      return Slice1dC<DataT>(m_data,
                             refElm,
			     Range1(),
			     this->ByteStride());
    }
    //: Access column as 1d slice.
    // NB. Changes made to the slice will also affect this array!
    
    Slice1dC<DataT> Diagonal() {
      return Slice1dC<DataT>(m_data,
			     &((*this)[Range1().Min()][Range2().Min()]),
			     Min(Range1().Size(),Range2().Size()),
			     this->ByteStride()+sizeof(DataT));
    }
    //: Take a slice along the diagonal of the array.
    // NB. Changes made to the slice will also affect this array!
    
    inline const Array2dC<DataT> & Array2d() const
    { return(*this); }
    //: access to the constant object
    
    inline Array2dC<DataT> & Array2d()
    { return(*this); }
    //: access to the object
        
    void ShiftArray(Index2dC offset)
      { ShiftRows(offset.Row()); ShiftCols(offset.Col()); }
    //: The array is shifted by <code>offset</code> w.r.t. the coordinate origin
    // This combines the functionality of <code>ShiftRows</code> and <code>ShiftCols</code><br>
    // Thus to shift an array so that the top left element has indices (0,0), use:
    //<pre>array.ShiftArray(-array.Frame().TopLeft())</pre>
    
    Array2dC<DataT> CopyAccess(IndexC rowShift = 0,IndexC colShift = 0);
    //: This will create a copy of the access structure without copying the data itself.
    // The access is shifted by rowShift vertically and colShift horizontally. 
    
    //!section: Operators -  These operators assume that the arrays have equal size, although they do not need to have the same origin.  The returned image has the same coordinates as <code>*this</code>.
  
    Array2dC<DataT> operator+(const Array2dC<DataT> & arr) const;
    //: Sums 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array2dC<DataT> operator-(const Array2dC<DataT> & arr) const;
    //: Subtracts 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array2dC<DataT> operator*(const Array2dC<DataT> & arr) const;
    //: Multiplies 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array2dC<DataT> operator/(const Array2dC<DataT> & arr) const;
    //: Divides 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    Array2dC<DataT> operator*(const DataT &number) const;
    //: Multiplies the array by the 'number'. 
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
    
    bool operator==(const Array2dC<DataT> &op) const;
    //: Do arrays have identical ranges and contents ?
    
    bool operator!=(const Array2dC<DataT> &op) const
    { return !operator==(op); }
    //: Do arrays have different ranges and contents ?
    
    DataT SumOfSqr() const;
    //: Calculate the sum of the squares of all elements in the array
    
    DataT Sum() const;
    //: Calculate the sum of all elements in the array

    Index2dC IndexOfMax() const {
      RavlAssertMsg(this->Frame().Area() > 0,"Array2dC::IndexOfMax() Called on an empty array");
      BufferAccess2dIterC<DataT> i(*this);
      const DataT *maxElem = &(*i) ;
      for (i++ ; i; i++) {
	if (*maxElem < *i)
          maxElem = &(*i);
      }
      return IndexOf(*maxElem);
    }
    //: Calculate the index of the maximum value in the array

    Index2dC IndexOfMin() const {
      RavlAssertMsg(this->Frame().Area() > 0,"Array2dC::IndexOfMin() Called on an empty array");
      BufferAccess2dIterC<DataT> i(*this);
      const DataT *minElem = &(*i) ;
      for (i++ ; i; i++) {
	if (*minElem < *i)
          minElem = &(*i);
      }
      return IndexOf(*minElem);
    }
    //: Calculate the index of the minimum value in the array

    
    Buffer2dC<DataT> &Buffer2d()
    { return m_data; }
    //: Access raw 2d buffer.
    
    void SetColumn(IndexC i,const Array1dC<DataT> &val);
    //: Set the values in the column i to those in 'val'.
    // The columns modified depend on the index range of 'val' and all values
    // of 'val' must map to valid locations in this array.
    
    void SetRow(IndexC i,const Array1dC<DataT> &val);
    //: Set the values in the row i to those in 'val'.
    // The rows modified depend on the index range of 'val' and all values
    // of 'val' must map to valid locations in this array.
    
    void SetSubArray(const Index2dC &origin,const Array2dC<DataT> &vals);
    //: Set sub array of this one. 
    // vals[0][0] will be places at 'origin'.
    // all of 'vals' must fit within this array.

    inline const IndexRangeC &Range1() const
    { return RangeBufferAccess2dC<DataT>::Range1(); }
    //: Range of first index.
    
    inline const IndexRangeC &Range2() const
    { return RangeBufferAccess2dC<DataT>::Range2(); }
    //: Range of second index.

    SizeT Size() const 
    { return RangeBufferAccess2dC<DataT>::Size(); }
    //: Get the total number of elements in the array.
    
    IntT ByteStride() const
    { return RangeBufferAccess2dC<DataT>::ByteStride(); }
    //: Get number of elements between rows in the array.
    
  protected:
    void ConstructAccess(const IndexRangeC &rng1,SizeT bufferOffset = 0);
    //: Construct access for buffer.
    // This assumes a suitable amount of space has been allocated
    // in 'data'
    
    Buffer2dC<DataT> m_data; // Raw data stored in array.
  };
  
  
  template <class DataT>
  ostream & operator<<(ostream & s, const Array2dC<DataT> & arr);
  // Prints into the stream 's'
  
  template <class DataT>
  istream & operator>>(istream & s, Array2dC<DataT> & arr);
  // Reads the array from the stream 's'
  
  ////////////////////////////////////////////////////////////////////////////////
    
      
  //: Create a sub array of 'arr' covering indices 'rect', with origin 'newOrigin'.
  // This copies the access.
  
  template <class DataT>
  Array2dC<DataT> Array2dC<DataT>::Copy() const {
    Array2dC<DataT> ret(this->Rectangle());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,*this,ret.Range1(),ret.Range2());it;it++)
      it.Data1() = it.Data2();
    return ret;
  }
  
  template <class DataT> 
  Array2dC<DataT> Array2dC<DataT>::DeepCopy(UIntT levels) const{
    if (levels == 0) return *this;
    if (levels == 1) return Copy(); 
    Array2dC<DataT> ret(this->Rectangle()); 
    --levels ; 
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,*this,ret.Range1(),ret.Range2());it;it++)
      it.Data1() = StdDeepCopy(it.Data2(), levels); 
    return ret ; 
  }

  template <class DataT>
  Array2dC<DataT> Array2dC<DataT>::CopyAccess(IndexC shift1,IndexC shift2) {
    IndexRangeC newRange1 = Range1() + shift1;
    IndexRangeC newRange2 = Range2() + shift2;
    RangeBufferAccess2dC<DataT> rba(this->PointerTo(shift1,shift2),newRange1,newRange2,m_data.ByteStride());
    return Array2dC<DataT>(m_data,rba);
  }
  
  template <class DataT>
  inline SArray2dC<DataT> Array2dC<DataT>::SArray2d(bool doShift) {
    if(Range1().Size() == 0 || Range2().Size() == 0)
      return SArray2dC<DataT>(); // Empty array.
    if(doShift)
      return SArray2dC<DataT>(m_data,Range1().Size(),Range2().Size(),this->PointerTo(Range1().Min(),Range2().Min()),this->ByteStride());
    if(!this->Contains(Index2dC(0,0))) {
      RavlAssertMsg(this->Contains(Index2dC(0,0)),"Array2dC must contain the element 0,0 to convert to an SArray without shifting. "); // Cause assertion failure in debug/check mode
      return SArray2dC<DataT>();
    }
    return SArray2dC<DataT>(m_data,Range1().Max().V()+1,Range2().Max().V()+1,this->PointerTo(0,0),this->ByteStride());
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
    SizeT area = rng1.Size() * rng2.Size();
    if((area * sizeof(DataT)) > s.ArraySizeLimit() || area > s.ArraySizeLimit())
      throw ExceptionOutOfRangeC("Incoming array size exceeds limit for stream.");
    arr = Array2dC<DataT>(rng1,rng2);
    return s >> ((RangeBufferAccess2dC<DataT> &)arr);
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator+(const Array2dC<DataT> & arr) const {
    Array2dC<DataT> ret(this->Rectangle());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,*this,arr,ret.Range1(),ret.Range2());
	it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator-(const Array2dC<DataT> & arr) const {
    Array2dC<DataT> ret(this->Rectangle());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,*this,arr,ret.Range1(),ret.Range2());it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator*(const Array2dC<DataT> & arr) const {
    Array2dC<DataT> ret(this->Rectangle());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,*this,arr,ret.Range1(),ret.Range2());it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator/(const Array2dC<DataT> & arr) const {
    Array2dC<DataT> ret(this->Rectangle());
    for(BufferAccess2dIter3C<DataT,DataT,DataT> it(ret,*this,arr,ret.Range1(),ret.Range2());it;it++)
      it.Data1() = it.Data2() / it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator+(const DataT &number) const {
    Array2dC<DataT> ret(this->Rectangle());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,(*this),ret.Range1(),ret.Range2());it;it++)
      it.Data1() = it.Data2() + number;
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator-(const DataT &number) const {
    Array2dC<DataT> ret(this->Rectangle());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,(*this),ret.Range1(),ret.Range2());it;it++)
      it.Data1() = it.Data2() - number;
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator*(const DataT &number) const {
    Array2dC<DataT> ret(this->Rectangle());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,(*this),ret.Range1(),ret.Range2());it;it++)
      it.Data1() = it.Data2() * number;
    return ret;
  }
  
  template<class DataT>
  Array2dC<DataT> Array2dC<DataT>::operator/(const DataT &number) const {
    Array2dC<DataT> ret(this->Rectangle());
    for(BufferAccess2dIter2C<DataT,DataT> it(ret,(*this),ret.Range1(),ret.Range2());it;it++)
      it.Data1() = it.Data2() / number;
    return ret;
  }
    
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator+=(const Array2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,arr,this->Range1(),this->Range2());it;it++)
      it.Data1() += it.Data2();
    return *this;
  }
  
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator-=(const Array2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,arr,this->Range1(),this->Range2());it;it++)
      it.Data1() -= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator*=(const Array2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,arr,this->Range1(),this->Range2());it;it++)
      it.Data1() *= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator/=(const Array2dC<DataT> & arr) {
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,arr,this->Range1(),this->Range2());it;it++)
      it.Data1() /= it.Data2();
    return *this;
  }
  
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator+=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this);it;it++)
      it.Data1() += number;
    return *this;
  }
    
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator-=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this);it;it++)
      it.Data1() -= number;
    return *this;
  }
  
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator*=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this);it;it++)
      it.Data1() *= number;
    return *this;
  }
  
  template<class DataT>
  const Array2dC<DataT> & Array2dC<DataT>::operator/=(const DataT &number) {
    for(BufferAccess2dIterC<DataT> it(*this);it;it++)
      it.Data() /= number;
    return *this;
  }

  template<class DataT>
  DataT Array2dC<DataT>::SumOfSqr() const {
    DataT ret;
    SetZero(ret);
    for(BufferAccess2dIterC<DataT> it(*this);it;it++)
      ret += Sqr(*it);
    return ret;
  }
  
  template<class DataT>
  DataT Array2dC<DataT>::Sum() const {
    DataT ret;
    SetZero(ret);
    for(BufferAccess2dIterC<DataT> it(*this);it;it++)
      ret += *it;
    return ret;
  }
  
  template <class DataT>
  SArray1dC<DataT> Array2dC<DataT>::AsVector(bool alwaysCopy) {
    if(!alwaysCopy && this->IsContinuous()) {
      DataT *start = &((*this)[this->Frame().Origin()]);
      return SArray1dC<DataT>(m_data,SizeBufferAccessC<DataT>(start,this->Frame().Area()));
    }
    SArray1dC<DataT> ret(this->Frame().Area());
    BufferAccessIterC<DataT> rit(ret);
    for(BufferAccess2dIterC<DataT> it(*this);it;it++,rit++)
      *rit = *it;
    return ret;
  }
  
  template <class DataT>
  void Array2dC<DataT>::SetColumn(IndexC i,const Array1dC<DataT> &val) {
    RavlAssert(Range1().Contains(val.Range()));
    // Avoid including to many headers by just using a ptr, not a slice.
    DataT *d1 = &((*this)[val.Range().Min()][i]);
    for(BufferAccessIterC<DataT> it(val);it;it++,d1 = ShiftPointer(d1,ByteStride()))
      *d1 = *it;   
  }
  
  template <class DataT>
  void Array2dC<DataT>::SetRow(IndexC i,const Array1dC<DataT> &val) {
    RavlAssert(Range2().Contains(val.Range()));
    DataT *d1 = &((*this)[i][val.Range().Min()]);
    for(BufferAccessIterC<DataT> it(val);it;it++,d1++)
      *d1 = *it;
  }
  
  template <class DataT>
  void Array2dC<DataT>::SetSubArray(const Index2dC &origin,const Array2dC<DataT> &vals) {
    IndexRange2dC srng = this->Frame();
    srng += origin;
    srng += vals.Frame().Origin();
    srng.ClipBy(this->Frame());
    for(BufferAccess2dIter2C<DataT,DataT> it(vals,vals.ByteStride(),vals.Frame(),
					    *this,this->ByteStride(),srng);it;it++)
      it.Data2() = it.Data1();
  }
  
  template <class DataT>
  bool Array2dC<DataT>::operator==(const Array2dC<DataT> &op) const {
    if(this->Frame() != op.Frame()) return false;
    for(BufferAccess2dIter2C<DataT,DataT> it(*this,op,Range1(),Range2());it;it++)
      if(it.Data1() != it.Data2()) return false;
    return true;
  }
  
}
#endif

