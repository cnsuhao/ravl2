// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLARRAY1D_HH
#define RAVLARRAY1D_HH
//////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Array/Array1d.hh"
//! lib=RavlCore
//! userlevel=Basic
//! author="Radek Marik"
//! docentry="Ravl.Core.Arrays.1D"
//! date="2/12/1993"
//! example=exArray1d.cc
//! rcsid="$Id$"

#include "Ravl/Buffer.hh"
#include "Ravl/RBfAcc.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/BfAccIter.hh"
#include "Ravl/BfAccIter2.hh"

class ostream;
class istream;

namespace RavlN {
  class BinIStreamC;
  class BinOStreamC;
  
  template<class DataT> class Array1dIterC;
  template<class DataT> class Slice1dC;
  template<class DataT> class Slice1dIterC;
  
  //: 1 Dimensional array
  // The class Array1dC is a  reference counted container with a fixed number
  // of items which can accessed in randomly using indexing in a specified
  // range of indeces. The item is expected
  // to have a default constructor, a copy constructor, and an assigment.
  // The class Array1dC is a big object, eg. it has a reference counter. <p>
  //  BIG OBJECT
  
  template <class DataC>
  class Array1dC
    : public RangeBufferAccessC<DataC> 
  { 
  public:  
    // Type definitions.
    // -----------------
    
    enum ExtensionT {
      SoftExt, // The new values are taken from a father array if it exists.
      HardExt  // The new values are always taken from the current subarray.
    };
    
    typedef DataC ElementT;
    //: Allow function templates to find type of array.
    
    typedef IndexC KeyT;
    //: Allow function templates to find type of index.
    
    typedef Array1dIterC<DataC> IteratorT;
    //: Iterator for this container.
    
    //typedef Array1dIterC<DataC> IteratorT;
    //: Type of iterator.
    
    // Constructors, copy, assigment, and destructor
    // ---------------------------------------------
    
    Array1dC();
    //: Creates an empty array.
    
    Array1dC(const Slice1dC<DataC> &slice,bool alwaysCopy = true);
    //: Make an array from a slice.
    // This will create an array with the values from the slice.
    // if the stride of the slice is not 1, and alwaysCopy is true the
    // a copy is done.
    
    Array1dC(SizeT dim);
    //: An array with the range <0, 'dim'-1>.
    
    Array1dC(IndexC min,IndexC max);
    //: An array with the range <min,max>.
    
    Array1dC(IntT min,IntT max);
    //: An array with the range <min,max>.
    
    Array1dC(const IndexRangeC & range);
    //: An array with the range <'range'.Min(), 'range'.Max()>.
    
    Array1dC(istream & s);
    //: Creates an 1-dimensional array from the input stream.
    
    Array1dC(const Array1dC<DataC> & vv);
    //: Another access to the array 'vv'.
    
    Array1dC(DataC *             data,
	     const IndexRangeC & range,
	     bool            removable = true);
    //: An array is created from the memory location 'data' with the range
    //: of access in <'range'.Min(), 'range'.Max()>. <p>
    // 'data' is assumed to point to the location 'range.min()' <p>
    // If flag 'removable' is false,
    // 'data' is not deallocated during destructing of the array, unless
    // 'removable' is set to true.
    
    Array1dC(BufferC<DataC> & bf, const IndexRangeC & range);
    //: Creates the array with limits 'range' using the buffer 'bf'.
    
    Array1dC(BufferC<DataC> & bf, const RangeBufferAccessC<DataC>  & rbf);
    //: Creates the array in 'bf' using access rbf..
    
    Array1dC(const Array1dC<DataC> & vv, const IndexRangeC & range);
    //: The subarray of the 'vv' with the 'range'.
    
    Array1dC(const SArray1dC<DataC> &oth);
    //: Construct an array from a SArray1dC.
    // Note: This does NOT make a copy, it just creates
    // another access to the buffer.
    
    Array1dC<DataC> Copy() const;
    //: Creates a new physical copy of the array.
    
    Array1dC<DataC> & Copy(const Array1dC<DataC> & orig);
    //: Copies values from the 'orig' array into this array. 
    // Only items
    // from the overlapping part of the ranges are copied. The function
    // returns this array.
    
    Array1dC<DataC> & Copy(const IndexRangeC & r, const IndexC off);
    //: Copies values from the index range 'r' into the new position 
    //: with the offset 'off'. 
    // Only those items
    // which original position and destination are inside of the index range
    // of this array are copied.
    
    Array1dC<DataC> & Copy(const IndexC off, const Array1dC<DataC> & a);
    //: Copies the maximum possible part of array 'a' into this array.
    // The first element of array 'a' is placed into the element 
    // of this array with index  'off'. The functio returns this array.
    
    const Array1dC<DataC> & operator=(const Array1dC<DataC> & vv);
    //: Assigment, as for a BIG_OBJECT.
    
    // Access to the object elements.
    // ------------------------------
    
    inline const Array1dC<DataC> & Array1d() const
      { return *this; }
    //: Access to the whole array.
    
    inline Array1dC<DataC> & Array1d()
      { return *this; }
    //: Access to the whole array.
    
    inline SArray1dC<DataC> SArray1d(bool doShift = false);
    //: Create an access as an sarray.
    // NB. This does NOT copy the data, it only make a new access to it.
    // If doShift is true element IMin() will become element 0 of the 
    // SArray while the size stays the same. Otherwise if the array 
    // does not contain element '0' an error will occure in check mode, 
    // when optimised is enabled an empty array will be returned. 
    
    // Array representation modifications.
    // -----------------------------------
    
    Array1dC<DataC> Extend(SizeT n) const;
    //: Returns the array whose range is extended by adding 'n' items with
    //: default value from both limits of the range. 
    // This array value are
    // copied into the same index positions in the returned array.
    
    Array1dC<DataC> & Append(const Array1dC<DataC> & a);
    //: This array is extended by the length of the array 'a' and the contents
    //: of both arrays are copied to it.
    // The function supports empty arrays.
    
    // Logical operations.
    // -------------------
    
    inline bool IsSharing(const Array1dC<DataC> & arr) const
      { return buff.IsSharing(arr.buff); }
    //: Returns true if this array and the array 'arr' are subarrays of the
    //: the same array.
    
    // Special operations.
    // -------------------
    
    BufferC<DataC> &Buffer()
      { return buff; }
    //: Access buffer in which data is stored.
    
    const BufferC<DataC> &Buffer() const
      { return buff; }
    //: Access buffer in which data is stored.

    void Reverse();
    //: Reverse the order of elements in this array in place.
    
    Array1dC<DataC> operator+(const Array1dC<DataC> & arr) const;
    // Sums 2 numerical arrays. The operator returns the result as a new array.
    
    Array1dC<DataC> operator-(const Array1dC<DataC> & arr) const;
    // Subtracts 2 numerical arrays. The operator returns
    // the result as a new array.
    
    Array1dC<DataC> operator*(const Array1dC<DataC> & arr) const;
    // Mutliplies 2 numerical arrays. The operator returns the result as a new array.
    
    Array1dC<DataC> operator/(const Array1dC<DataC> & arr) const;
    // Devides 2 numerical arrays. The operator returns
    // the result as a new array.
    
    Array1dC<DataC> operator*(const DataC &number) const;
    // Multiplys the array by the 'number'. The operator
    // returns the result as a new array.
    
    Array1dC<DataC> operator/(const DataC &number) const;
    // Divides all array items by the 'number'. The operator 
    // returns the result as a new array.
    
    Array1dC<DataC> operator+(const DataC &number) const;
    // Adds 'number' to the array. The operator
    // returns the result as a new array.
    
    Array1dC<DataC> operator-(const DataC &number) const;
    // Subtracts 'number' from all array items. The operator 
    // returns the result as a new array.
    
    const Array1dC<DataC> & operator+=(const Array1dC<DataC> & arr);
    // Adds the 2nd array to this array.
    
    const Array1dC<DataC> & operator-=(const Array1dC<DataC> & arr);
    // Subtracts the 2nd array from this array.
    
    const Array1dC<DataC> & operator*=(const Array1dC<DataC> & arr);
    // Multiplies the 2nd array to this array.
    
    const Array1dC<DataC> & operator/=(const Array1dC<DataC> & arr);
    // Divides the 2nd array from this array.
    
    const Array1dC<DataC> & operator+=(const DataC &number);
    // Adds 'number' to all array items.
    
    const Array1dC<DataC> & operator-=(const DataC &number);
    // Subtracts 'number' from all array items.
    
    const Array1dC<DataC> & operator*=(const DataC &number);
    // Multiplies the array by the 'number'.
    
    const Array1dC<DataC> & operator/=(const DataC &number);
    // Divides the array elements by the 'number'.

    Array1dC<DataC> Apply(DataC (*op)(const DataC &func)) const;
    //: Apply a function to each item in the array.
    // The results are put in a new array.
    
    Array1dC<DataC> &ApplyIP(void (*op)(DataC &func));
    //: Apply a function In Place to each item in the array.
    // the changes are made to this array.

    Array1dC<DataC> From(IndexC offset) { 
      if(offset > Range().Max())
	return Array1dC<DataC>(); // Empty array.
      RavlAssert(offset >= Range().Min()); // Ensure its within the array.
      return SArray1dC<DataC>(*this,IndexRangeC(offset,Range().Max())); 
    }
    //: Return array from offset to the end of the array.
    // If offset is larger than the array an empty array
    // is returned.  
    
    Array1dC<DataC> After(IndexC offset) 
    { return From(offset+1); }
    //: Return array after offset to the end of the array.
    // If offset is larger than the array an empty array
    // is returned.
    
  private:
    
    // Object representation
    // ---------------------
    
    BufferC<DataC> buff;  // The reference counted storage.
  };
  
  template <class DataC>
  ostream & 
  operator<<(ostream & s, const Array1dC<DataC> & arr);
  // Prints array into the stream 's'.

  template <class DataC>
  istream & 
  operator>>(istream & s, Array1dC<DataC> & arr);
  // Assigns the values into the array 'arr'.
  
  template <class DataC>
  BinOStreamC & operator<<(BinOStreamC & s, const SArray1dC<DataC> & arr);
  // Prints array into the stream 's'.
  
  template <class DataC>
  BinIStreamC & operator>>(BinIStreamC& s, SArray1dC<DataC> & arr);
  // Assigns the values into the array 'arr'.
  
  template <class DataC>
  Array1dC<DataC> &
  BubbleSort(Array1dC<DataC> & arr);
  // Sorts the array 'arr' using operator <.
  
  ///////////////////////////////////////////////
  
  template <class DataC>
  inline
  const Array1dC<DataC> &
  Array1dC<DataC>::operator=(const Array1dC<DataC> & vv) {
    if (this == &vv) return *this;
    RangeBufferAccessC<DataC>::operator=(vv);
    buff=vv.buff;
    return *this;
  }
  
  template <class DataC>
  Array1dC<DataC>::Array1dC()
    : RangeBufferAccessC<DataC>(),
      buff()
  {}
  
  template <class DataC>
  Array1dC<DataC>::Array1dC(const SizeT dim)
    : RangeBufferAccessC<DataC>(),
      buff(dim)
  { Attach(buff,dim); }

  
  template <class DataC>
  Array1dC<DataC>::Array1dC(IntT min,IntT max)
    : RangeBufferAccessC<DataC>(),
      buff(IndexRangeC(min,max).Size())
  {
    RavlAssert(min <= max);
    Attach(buff,IndexRangeC(min,max)); 
  }
  
  template <class DataC>
  Array1dC<DataC>::Array1dC(IndexC min,IndexC max)
    : RangeBufferAccessC<DataC>(),
      buff(IndexRangeC(min,max).Size())
  {
    RavlAssert(min <= max);
    Attach(buff,IndexRangeC(min,max)); 
  }
  
  template <class DataC>
  Array1dC<DataC>::Array1dC(const IndexRangeC & range)
    : RangeBufferAccessC<DataC>(),
      buff(range.Size())
  { Attach(buff,range); }
  

  template <class DataC>
  Array1dC<DataC>::Array1dC(const Array1dC<DataC> & vv)
    : RangeBufferAccessC<DataC>(vv),
      buff(vv.buff)
  {}
  
  template <class DataC>
  Array1dC<DataC>::Array1dC(const Slice1dC<DataC> &slice,bool alwaysCopy) { 
    if(!alwaysCopy && slice.Stride() == 1) {
      buff = slice.Buffer();
      RangeBufferAccessC<DataC>::operator=(RangeBufferAccessC<DataC>(&slice[0],Range1dC(0,slice.Size())));
      return ;
    }
    buff = BufferC<DataC>(slice.Size());
    Attach(buff,Range1dC(0,slice.Size()));
    // Copy data.
    DataC *at = buff.ReferenceElm();
    for(Slice1dIterC<DataC> it(slice);it;it++,at++)
      *at = *it;
  }
  
  template <class DataC>
  Array1dC<DataC>::Array1dC(DataC * data, 
			    const IndexRangeC & range,
			    bool    removable)
    : RangeBufferAccessC<DataC>(data, range),
      buff(range.Size(),data,false, removable)
  {}
  
  template <class DataC>
  Array1dC<DataC>::Array1dC(BufferC<DataC> & bf, const IndexRangeC & range)
    : RangeBufferAccessC<DataC>(bf.Access(), range),
      buff(bf)
  {}
  
  template <class DataC>
  Array1dC<DataC>::Array1dC(BufferC<DataC> & bf, const RangeBufferAccessC<DataC>  & rbf) 
    : RangeBufferAccessC<DataC>(rbf),
      buff(bf)
  {}
  
  template <class DataC>
  Array1dC<DataC>::Array1dC(const Array1dC<DataC> & vv, 
			    const IndexRangeC & range)
    : RangeBufferAccessC<DataC>(vv.RAccess(), range),
      buff(vv.buff)
  {}
  
  template <class DataC>
  Array1dC<DataC>::Array1dC(const SArray1dC<DataC> &oth)
    : RangeBufferAccessC<DataC>(oth.Buffer(),IndexRangeC(0,oth.Size()-1)),
      buff(oth.Buffer())
  {}
  
  template <class DataC>
  Array1dC<DataC>
  Array1dC<DataC>::Copy() const {
    return Array1dC<DataC>(RangeBufferAccessC<DataC>::Copy().DataStart(), 
			   Range());
  }
  
  template <class DataC>
  Array1dC<DataC> & 
  Array1dC<DataC>::Copy(const Array1dC<DataC> & orig) {
    IndexRangeC r(orig.Range());
    r.ClipBy(Range());
    for(BufferAccessIter2C<DataC,DataC> it(*this,orig,r);it;it++)
      it.Data1() = it.Data2();
    return *this;
  }
  
  template <class DataC>
  Array1dC<DataC> & 
  Array1dC<DataC>::Copy(const IndexRangeC & r, const IndexC off) {
    // Construct the destination range.
    IndexRangeC destination(r);
    destination.ClipBy(Range());   // the clipped source domain
    destination += off;
    destination.ClipBy(Range());   // destination.Size() <= source.Size()
    // Both 'destination' and 'source' ranges are inside the array.
    
    const IndexC min = destination.Min();
    const IndexC max = destination.Max();
    if (off <= 0)
      for (IndexC c = min; c <= max; c++)
	(*this)[c] = (*this)[c+off];
    else 
      for (IndexC c = max; c >= min; c--)
	(*this)[c] = (*this)[c-off];
    return *this;
  }
  
  template <class DataC>
  Array1dC<DataC> & 
  Array1dC<DataC>::Copy(const IndexC off, const Array1dC<DataC> & a) {
    const SizeT mySize = (IMax() - off +1).V();
    DataC * myElm = &((*this)[off]);
    DataC const * aElm  = &(a[a.IMin()]);
    const DataC * myEnd  = mySize < a.Size() ? (myElm+mySize-1)
      : (myElm+a.Size()-1);
    while (myElm <= myEnd)
      *(myElm++) = *(aElm++);
    return *this;
  }
  
  template <class DataC>
  Array1dC<DataC> 
  Array1dC<DataC>::Extend(const SizeT n) const {
    IndexRangeC rng(IMin(),IMax() + n);
    Array1dC<DataC> x(rng);
    x.Copy(*this);
    return x;
  }

  template <class DataC>
  Array1dC<DataC> & 
  Array1dC<DataC>::Append(const Array1dC<DataC> & a) {
    if (!a.IsValid()) return *this;
    if (!IsValid()) {
      *this = a.Copy();
      return *this;
    }
    const IndexRangeC newRange(IMin(), IMax() + a.Size());
    Array1dC<DataC>   newArr(newRange);
    newArr.Copy(*this);
    newArr.Copy(IMax()+1,a);
    *this = newArr;
    return *this;
  }
  
  template <class DataC>
  inline 
  SArray1dC<DataC> Array1dC<DataC>::SArray1d(bool doShift = false) {
    if(doShift)
      return SArray1dC<DataC>(buff,&((*this)[IMin()]),Size());
    if(!Contains(0)) {
      RavlAssert(Contains(0)); // Cause assertion failure in debug/check mode
      return SArray1dC<DataC>();
    }
    return SArray1dC<DataC>(buff,&((*this)[0]) ,IMax().V());
  }

  template <class DataC>
  ostream &
  operator<<(ostream & s, const Array1dC<DataC> & arr) {
    const IndexRangeC range(arr.Range());
    s << range << '\n'; 
    for(BufferAccessIterC<DataC> it(arr);it;it++)
      s  << ((const DataC &) *it) << '\n';
    return s;
  }
  
  
  template <class DataC>
  istream &
  operator>>(istream & s, Array1dC<DataC> & arr) {
    IndexRangeC range(s);
    if (range != arr.Range()) {
      Array1dC<DataC> brr(range);
      arr = brr;
    }
    for(BufferAccessIterC<DataC> it(arr);it;it++)
      s >> *it;
    return s;
  }
  
  template<class DataC>
  BinOStreamC &
  operator<<(BinOStreamC & s, const Array1dC<DataC> & arr) {
    s << arr.Range().Min() << arr.Range().Max();
    for(BufferAccessIterC<DataC> it(arr);it;it++)
      s << *it;
    return s;
  }

  template<class DataC>
  BinIStreamC &
  operator>>(BinIStreamC & s, Array1dC<DataC> & arr) {
    IndexRangeC rng;
    s >> rng.Min() >> rng.Max();
    arr = Array1dC<DataC>(rng);
    for(BufferAccessIterC<DataC> it(arr);it;it++)
      s >> *it;
    return s;
  }
  
  template<class DataC>
  Array1dC<DataC> Array1dC<DataC>::operator+(const Array1dC<DataC> & arr) const {
    Array1dC<DataC> ret(Size());
    for(BufferAccessIter3C<DataC,DataC,DataC> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }
  
  template<class DataC>
  Array1dC<DataC> Array1dC<DataC>::operator-(const Array1dC<DataC> & arr) const {
    Array1dC<DataC> ret(Size());
    for(BufferAccessIter3C<DataC,DataC,DataC> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;
  }
  
  template<class DataC>
  Array1dC<DataC> Array1dC<DataC>::operator*(const Array1dC<DataC> & arr) const {
    Array1dC<DataC> ret(Size());
    for(BufferAccessIter3C<DataC,DataC,DataC> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataC>
  Array1dC<DataC> Array1dC<DataC>::operator/(const Array1dC<DataC> & arr) const {
    Array1dC<DataC> ret(Size());
    for(BufferAccessIter3C<DataC,DataC,DataC> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() / it.Data3();
    return ret;
  }
  
  template<class DataC>
  Array1dC<DataC> Array1dC<DataC>::operator+(const DataC &number) const {
    Array1dC<DataC> ret(Size());
    for(BufferAccessIter2C<DataC,DataC> it(ret,*this);it;it++)
      it.Data1() = it.Data2() + number;
    return ret;
  }
  
  template<class DataC>
  Array1dC<DataC> Array1dC<DataC>::operator-(const DataC &number) const {
    Array1dC<DataC> ret(Size());
    for(BufferAccessIter2C<DataC,DataC> it(ret,*this);it;it++)
      it.Data1() = it.Data2() - number;
    return ret;
  }
  
  template<class DataC>
  Array1dC<DataC> Array1dC<DataC>::operator*(const DataC &number) const {
    Array1dC<DataC> ret(Size());
    for(BufferAccessIter2C<DataC,DataC> it(ret,*this);it;it++)
      it.Data1() = it.Data2() * number;
    return ret;
  }
  
  template<class DataC>
  Array1dC<DataC> Array1dC<DataC>::operator/(const DataC &number) const {
    Array1dC<DataC> ret(Size());
    for(BufferAccessIter2C<DataC,DataC> it(ret,*this);it;it++)
      it.Data1() = it.Data2() / number;
    return ret;
  }
  
  template<class DataC>
  const Array1dC<DataC> & Array1dC<DataC>::operator+=(const Array1dC<DataC> & arr) {
    for(BufferAccessIter2C<DataC,DataC> it(*this,arr);it;it++)
      it.Data1() += it.Data2();
    return *this;
  }
  
  template<class DataC>
  const Array1dC<DataC> & Array1dC<DataC>::operator-=(const Array1dC<DataC> & arr) {
    for(BufferAccessIter2C<DataC,DataC> it(*this,arr);it;it++)
      it.Data1() -= it.Data2();
    return *this;
  }
    
  template<class DataC>
  const Array1dC<DataC> & Array1dC<DataC>::operator*=(const Array1dC<DataC> & arr) {
    for(BufferAccessIter2C<DataC,DataC> it(*this,arr);it;it++)
      it.Data1() *= it.Data2();
    return *this;
  }
    
  template<class DataC>
  const Array1dC<DataC> & Array1dC<DataC>::operator/=(const Array1dC<DataC> & arr) {
    for(BufferAccessIter2C<DataC,DataC> it(*this,arr);it;it++)
      it.Data1() /= it.Data2();
    return *this;
  }
  
  template<class DataC>
  const Array1dC<DataC> & Array1dC<DataC>::operator+=(const DataC &number) {
    for(BufferAccessIterC<DataC> it(*this);it;it++)
      it.Data1() += number;
    return *this;
  }
  
  
  template<class DataC>
  const Array1dC<DataC> & Array1dC<DataC>::operator-=(const DataC &number) {
    for(BufferAccessIterC<DataC> it(*this);it;it++)
      it.Data1() -= number;
    return *this;
  }
  
  template<class DataC>
  const Array1dC<DataC> & Array1dC<DataC>::operator*=(const DataC &number) {
    for(BufferAccessIterC<DataC> it(*this);it;it++)
      it.Data1() *= number;
    return *this;
  }
  
  template<class DataC>
  const Array1dC<DataC> & Array1dC<DataC>::operator/=(const DataC &number) {
    for(BufferAccessIterC<DataC> it(*this);it;it++)
      it.Data1() /= number;
    return *this;
  }
  
  template<class DataC>
  Array1dC<DataC> Array1dC<DataC>::Apply(DataC (*op)(const DataC &func)) const {
    Array1dC<DataC> ret(Range());
    for(BufferAccessIter2C<DataC,DataC> it(ret,*this);it;it++)
      it.Data1() = op(it.Data2());
    return ret;
  }
  
  template<class DataC>
  Array1dC<DataC> &Array1dC<DataC>::ApplyIP(void (*op)(DataC &func)) {
    for(BufferAccessIterC<DataC> it(*this);it;it++)
      op(*it);
    return *this;
  }
  

  template <class DataC>
  Array1dC<DataC> &
  BubbleSort(Array1dC<DataC> & arr) {
    IndexC    low = arr.Range().Min();
    IndexC    upp = arr.Range().Max();
    bool  change;
    DataC  *  ev = new DataC(); // A big piggish ...... according G. Matas.
    do {
      change = false;
      for (IndexC i = low; i < upp; ++i) {
	if (arr[i] < arr[i+1]) {
	  *ev = arr[i];
	  arr[i] = arr[i+1];
	  arr[i+1] = *ev;
	  change = true;
	}
      }
      --upp; // at the moment the last item is the smallest one
    } while(change);
    return(arr);
  }
  
}
#endif
