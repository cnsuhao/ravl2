// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSArray1d_HH
#define RAVLSArray1d_HH
////////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/SArray/SArray1d.hh"
//! lib=RavlCore
//! author="Radek Marik"
//! docentry="Ravl.Core.Arrays.1D"
//! date="21/2/1996"
//! rcsid="$Id$"

#include <iostream.h>
#include "Ravl/Buffer.hh"
#include "Ravl/SBfAcc.hh"
#include "Ravl/Pair.hh"
#include "Ravl/BfAccIter.hh"
#include "Ravl/BfAccIter2.hh"
#include "Ravl/BfAccIter3.hh"
#include "Ravl/StdHash.hh"

namespace RavlN {

  template<class DataT> class SArray1dIterC;
  template<class DataT> class Array1dC;
  template<class DataT> class Slice1dC;
  template<class DataT> class Slice1dIterC;
  class BinIStreamC;
  class BinOStreamC;
  
  //! userlevel=Advanced
  //: A simple 1 dimensional array
  // The class SArray1dC is a simple reference counted 
  // container with a fixed number of items
  // which can accessed randomly using indexing. The item is expected
  // to have a default constructor, a copy constructor, and an assigment.
  // The class SArray1dC is a big object, eg. it has a reference counter.
  
  template <class DataC>
  class SArray1dC
    : public SizeBufferAccessC<DataC> 
  { 
  public:
    typedef DataC ElementT;
    //: Allow function templates to find type of array.
    
    typedef IndexC KeyT;
    //: Allow function templates to find type of index.
    
    typedef SArray1dIterC<DataC> IteratorT;
    //: Type of iterator.
    
    // Constructors, assigment, and destructor
    // ---------------------------------------
    
    SArray1dC();
    // Empty array.
    
    SArray1dC(const SizeT dim);
    // Creates an uninitialized array with the range <0, 'dim'-1>.
    
    SArray1dC(const Slice1dC<DataC> &slice,bool alwaysCopy = true);
    //: Make an array from a slice.
    // This will create an array with the values from the slice.
    // if the stride of the slice is not 1, and alwaysCopy is true the
    // a copy is done.
    
    SArray1dC(const PairC<DataC> & pr);
    // Creates an array with two elements from a PairC object.
    
    SArray1dC(const SArray1dC<DataC> & vv);
    // Another access to the array 'vv'.
    
    SArray1dC(DataC *      data,
	      const SizeT  dim,
	      bool     removable = true);
    // The array is created from the memory location 'data' with the range
    // of access in <0, 'dim'-1>. If flag 'removable' is false,
    // 'data' is not deallocated during destructing of the array.
    
    SArray1dC(BufferC<DataC> & bf,SizeT dim,SizeT offsetInBuff = 0);
    //: Creates the array of size 'dim' using the buffer 'bf'.
    // Use buffer 'bf',  make access of 'dim' elements. 
    // the start of the buffer should be 'offsetInBuff' elements into
    // the buffer.
    
    SArray1dC(const SArray1dC<DataC> & vv, const SizeT dim,SizeT offsetInBuff = 0);
    //: The subarray of the 'vv' with size 'dim'.
    
    SArray1dC<DataC> Copy() const;
    //: Creates a new physical copy of the array.
    
    SArray1dC<DataC> Copy(UIntT extend) const;
    //: Creates a new physical copy of the array.
    // 'extend' extra elements initalised by the default constuctor
    // are appended to the end of the array.
    
    inline const SArray1dC<DataC> & operator=(const SArray1dC<DataC> & vv);
    // Assigment, as for a BIG_OBJECT.
    
    SArray1dC<DataC> operator+(const SArray1dC<DataC> & arr) const;
    // Sums 2 numerical arrays. The operator returns the result as a new array.
    
    SArray1dC<DataC> operator-(const SArray1dC<DataC> & arr) const;
    // Subtracts 2 numerical arrays. The operator returns
    // the result as a new array.
    
    SArray1dC<DataC> operator*(const SArray1dC<DataC> & arr) const;
    // Mutliplies 2 numerical arrays. The operator returns the result as a new array.
    
    SArray1dC<DataC> operator/(const SArray1dC<DataC> & arr) const;
    // Devides 2 numerical arrays. The operator returns
    // the result as a new array.
    
    SArray1dC<DataC> operator*(const DataC &number) const;
    // Multiplys the array by the 'number'. The operator
    // returns the result as a new array.
    
    SArray1dC<DataC> operator/(const DataC &number) const;
    // Divides all array items by the 'number'. The operator 
    // returns the result as a new array.
    
    SArray1dC<DataC> operator+(const DataC &number) const;
    // Adds 'number' to the array. The operator
    // returns the result as a new array.
    
    SArray1dC<DataC> operator-(const DataC &number) const;
    // Subtracts 'number' from all array items. The operator 
    // returns the result as a new array.
    
    const SArray1dC<DataC> & operator+=(const SArray1dC<DataC> & arr);
    // Adds the 2nd array to this array.
    
    const SArray1dC<DataC> & operator-=(const SArray1dC<DataC> & arr);
    // Subtracts the 2nd array from this array.
    
    const SArray1dC<DataC> & operator*=(const SArray1dC<DataC> & arr);
    // Multiplies the 2nd array to this array.
    
    const SArray1dC<DataC> & operator/=(const SArray1dC<DataC> & arr);
    // Divides the 2nd array from this array.
    
    const SArray1dC<DataC> & operator+=(const DataC &number);
    // Adds 'number' to all array items.
    
    const SArray1dC<DataC> & operator-=(const DataC &number);
    // Subtracts 'number' from all array items.
    
    const SArray1dC<DataC> & operator*=(const DataC &number);
    // Multiplies the array by the 'number'.
    
    const SArray1dC<DataC> & operator/=(const DataC &number);
    // Divides the array elements by the 'number'.

    
    // Access to the object and its parts.
    // -----------------------------------
    
    inline const SArray1dC<DataC> & SArray1d() const
      { return *this; }
    // Access to the whole constant array.
    
    inline SArray1dC<DataC> & SArray1d()
      { return *this; }
    // Access to the whole array.
    
    // Modifications of the representation
    // -----------------------------------
        
    inline SArray1dC<DataC> & Append(const SArray1dC<DataC> & a);
    // This array is extended by the length of the array 'a' and the contents
    // of both arrays are copied to it. Empty arrays are handled correctly.
    
    SArray1dC<DataC> Join(const SArray1dC<DataC> &Oth) const;
    // Join this Array and another into a new Array which
    // is returned. This does not change either of its arguments.
    // This is placed in the array first, followed by 'Oth'.
    
    SArray1dC<DataC> From(UIntT offset) { 
      if(offset >= Size())
	return SArray1dC<DataC>(); // Empty array.
      SizeT nsize = Size() - offset;
      return SArray1dC<DataC>(*this,nsize,offset); 
    }
    //: Return array from offset to the end of the array.
    // If offset is larger than the array an empty array
    // is returned,
    
    SArray1dC<DataC> After(UIntT offset) 
    { return From(offset+1); }
    //: Return array after offset to the end of the array.
    // If offset is larger than the array an empty array
    // is returned,
    
    // Special operations
    // ------------------
    
    BufferC<DataC> &Buffer()
      { return buff; }
    //: Access base data buffer.
    // Experts only.

    const BufferC<DataC> &Buffer() const
      { return buff; }
    //: Constant access base data buffer.
    // Experts only.
    
    void Sort();
    //: Sort the array in place.
    // This does a simple bubble sort.
    // FIXME:- we could do with something better!

    bool operator==(const SArray1dC<DataC> & vv);
    //: Comparison operator
    
    UIntT Hash() const;
    //: Compute a hash value for the array.
    
  protected:
    SArray1dC(BufferC<DataC> & bf,DataC *start, const SizeT dim);
    //: Creates the array of size 'dim' using the buffer 'bf', with
    //: 0'th element at start.
    // Used for building SArray's from Arrays.
    
    // Special operations
    // ------------------
    
    inline DataC * DataStart() const
      { return SizeBufferAccessC<DataC>::ReferenceElm(); }
    // Returns the address of the first item if exists.
    
  private:
    
    // Object representation
    // ---------------------
    
    BufferC<DataC> buff;  // The reference counted storage.
    
    friend class SArray1dIterC<DataC>;
    friend class Array1dC<DataC>;
  };
  
  template <class DataC>
  BinOStreamC & operator<<(BinOStreamC & s, const SArray1dC<DataC> & arr);
  // Prints array into the stream 's'.
  
  template <class DataC>
  BinIStreamC & operator>>(BinIStreamC& s, SArray1dC<DataC> & arr);
  // Assigns the values into the array 'arr'.
  
  template <class DataC>
  SArray1dC<DataC> & BubbleSort(SArray1dC<DataC> & arr);
  // Sorts arr using operator <.
  
  template <class DataC>
  istream & operator>>(istream & s, SArray1dC<DataC> & arr);
  // Assigns the values into the array 'arr'.
  
  template <class DataC>
  SArray1dC<DataC> & BubbleSort(SArray1dC<DataC> & arr);
  // Sorts arr using operator <.
  
  /////////////////////////////////////////////////////////////////////////////
  
  template <class DataC>
  inline
  const SArray1dC<DataC> &
  SArray1dC<DataC>::operator=(const SArray1dC<DataC> & vv) {
    if (this == &vv) return *this;
    SizeBufferAccessC<DataC>::operator=(vv);
    buff=vv.buff;
    return *this;
  }
  
  
  template <class DataC>
  inline 
  SArray1dC<DataC> & 
  SArray1dC<DataC>::Append(const SArray1dC<DataC> & a)  {
    (*this) = Join(a);
    return *this;
  }
  
  template <class DataC>
  SArray1dC<DataC>::SArray1dC()
    : SizeBufferAccessC<DataC>(),
      buff()
  {}

  template <class DataC>
  SArray1dC<DataC>::SArray1dC(const PairC<DataC> & pr)
    : SizeBufferAccessC<DataC>(),
      buff(2)
  {
    Attach(buff,2);
    (*this)[0] = pr[0];
    (*this)[1] = pr[1];
  }

  template <class DataC>
  SArray1dC<DataC>::SArray1dC(const Slice1dC<DataC> &slice,bool alwaysCopy) {
    if(!alwaysCopy && slice.Stride() == 1) {
      buff = slice.Buffer();
      RangeBufferAccessC<DataC>::operator=(RangeBufferAccessC<DataC>(&slice[0],slice.Size()));
      return ;
    }
    buff = BufferC<DataC>(slice.Size());
    Attach(buff,slice.Size());
    // Copy data.
    DataC *at = buff.ReferenceElm();
    for(Slice1dIterC<DataC> it(slice);it;it++,at++)
      *at = *it;

  }
  
  template <class DataC>
  SArray1dC<DataC>::SArray1dC(const SizeT dim)
    : SizeBufferAccessC<DataC>(),
      buff(dim)
  { Attach(buff,dim); }
  
  template <class DataC>
  SArray1dC<DataC>::SArray1dC(const SArray1dC<DataC> & vv)
    : SizeBufferAccessC<DataC>(vv),
      buff(vv.buff)
  {}

  template <class DataC>
  SArray1dC<DataC>::SArray1dC(DataC *data, 
			      SizeT dim,
			      bool removable)
    : SizeBufferAccessC<DataC>(data, dim),
      buff(dim,data,false, removable)
  {}
  
  template <class DataC>
  SArray1dC<DataC>::SArray1dC(BufferC<DataC> & bf,SizeT dim,SizeT offsetInBuff)
    : SizeBufferAccessC<DataC>(bf.Access() + offsetInBuff, dim),
      buff(bf)
  {}

  template <class DataC>
  SArray1dC<DataC>::SArray1dC(BufferC<DataC> & bf,
			      DataC *start, 
			      const SizeT dim)
    : SizeBufferAccessC<DataC>(start, dim),
      buff(bf)
  {}

  template <class DataC>
  SArray1dC<DataC>::SArray1dC(const SArray1dC<DataC> & vv, 
			      const SizeT             dim,
			      SizeT offsetInBuff)
  : SizeBufferAccessC<DataC>(vv.SAccess() + offsetInBuff, dim),
    buff(vv.buff)
  {
    RavlAssert(vv.Size() >= (offsetInBuff + dim)); // Make sure its big enought.
  }

  template <class DataC>
  SArray1dC<DataC> SArray1dC<DataC>::Copy() const {
    return SArray1dC<DataC>(SizeBufferAccessC<DataC>::Copy().ReferenceElm(), 
			    Size(),true);
  }

  template <class DataC>
  SArray1dC<DataC> SArray1dC<DataC>::Copy(UIntT extend) const {
    SArray1dC<DataC> ret(Size() + extend);
    for(BufferAccessIter2C<DataC,DataC> it(*this,ret);it;it++)
      it.Data2() = it.Data1();
    return ret;
  }
  
  template <class DataC>
  SArray1dC<DataC> 
  SArray1dC<DataC>::Join(const SArray1dC<DataC> &Oth) const  {
    // FIXME :- Do this more efficently, with ptrs.
    const SizeT len1 = Size();
    const SizeT len2 = Oth.Size();
    SArray1dC<DataC> newarr(Len1 + Len2);
    for(BufferAccessIter2C<DataC,DataC> it(*this,newarr);it;it++)
      it.Data2() = it.Data1();
    for(BufferAccessIter2C<DataC,DataC> it(Oth,newarr,0,len1);it;it++)
      it.Data2() = it.Data1();
    return newarr;
  }

  template <class DataC>
  ostream &
  operator<<(ostream & s, const SArray1dC<DataC> & arr) {
    s << arr.Size() << '\n'; 
    for(BufferAccessIterC<DataC> it(arr);it;it++)
      s << ((const DataC &) *it) << '\n';
    return s;
  }
  
  template <class DataC>
  istream &
  operator>>(istream & s, SArray1dC<DataC> & arr) { 
    SizeT n = 0;
    s >> n;
    if (n != arr.Size()) {
      SArray1dC<DataC> brr(n);
      arr = brr;
    }
    for(BufferAccessIterC<DataC> it(arr);it;it++)
      s >> *it;
    return s;
  }

  template <class DataC>
  SArray1dC<DataC> &
  BubbleSort(SArray1dC<DataC> & arr) {
    IndexC    low = 0;
    IndexC    upp = arr.Size()-1;
    bool  change;
    DataC     ev;
    do {
      change = false;
      for (IndexC i = low; i < upp; ++i) {
	if (arr[i] < arr[i+1]) {
	  ev = arr[i];
	  arr[i] = arr[i+1];
	  arr[i+1] = ev;
	  change = true;
	}
      }
      --upp; // at the moment the last item is the smallest one
    }while(change);
    return arr;
  }
  
  
  template<class DataC>
  BinOStreamC &
  operator<<(BinOStreamC & s, const SArray1dC<DataC> & arr) {
    s << arr.Size();
    for(BufferAccessIterC<DataC> it(arr);it;it++)
      s << it.Data();
    return s;
  }
  
  template<class DataC>
  BinIStreamC &
  operator>>(BinIStreamC & s, SArray1dC<DataC> & arr) {
    UIntT size;
    s >> size;
    arr = SArray1dC<DataC>(size);
    for(BufferAccessIterC<DataC> it(arr);it;it++)
      s >> it.Data();
    return s;
  }

  template<class DataC>
  SArray1dC<DataC> SArray1dC<DataC>::operator+(const SArray1dC<DataC> & arr) const {
    SArray1dC<DataC> ret(Size());
    for(BufferAccessIter3C<DataC,DataC,DataC> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }
  
  template<class DataC>
  SArray1dC<DataC> SArray1dC<DataC>::operator-(const SArray1dC<DataC> & arr) const {
    SArray1dC<DataC> ret(Size());
    for(BufferAccessIter3C<DataC,DataC,DataC> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;
  }
  
  template<class DataC>
  SArray1dC<DataC> SArray1dC<DataC>::operator*(const SArray1dC<DataC> & arr) const {
    SArray1dC<DataC> ret(Size());
    for(BufferAccessIter3C<DataC,DataC,DataC> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataC>
  SArray1dC<DataC> SArray1dC<DataC>::operator/(const SArray1dC<DataC> & arr) const {
    SArray1dC<DataC> ret(Size());
    for(BufferAccessIter3C<DataC,DataC,DataC> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() / it.Data3();
    return ret;
  }
  
  template<class DataC>
  SArray1dC<DataC> SArray1dC<DataC>::operator+(const DataC &number) const {
    SArray1dC<DataC> ret(Size());
    for(BufferAccessIter2C<DataC,DataC> it(ret,*this);it;it++)
      it.Data1() = it.Data2() + number;
    return ret;
  }
  
  template<class DataC>
  SArray1dC<DataC> SArray1dC<DataC>::operator-(const DataC &number) const {
    SArray1dC<DataC> ret(Size());
    for(BufferAccessIter2C<DataC,DataC> it(ret,*this);it;it++)
      it.Data1() = it.Data2() - number;
    return ret;
  }
  
  template<class DataC>
  SArray1dC<DataC> SArray1dC<DataC>::operator*(const DataC &number) const {
    SArray1dC<DataC> ret(Size());
    for(BufferAccessIter2C<DataC,DataC> it(ret,*this);it;it++)
      it.Data1() = it.Data2() * number;
    return ret;
  }
  
  template<class DataC>
  SArray1dC<DataC> SArray1dC<DataC>::operator/(const DataC &number) const {
    SArray1dC<DataC> ret(Size());
    for(BufferAccessIter2C<DataC,DataC> it(ret,*this);it;it++)
      it.Data1() = it.Data2() / number;
    return ret;
  }
  
  template<class DataC>
  const SArray1dC<DataC> & SArray1dC<DataC>::operator+=(const SArray1dC<DataC> & arr) {
    for(BufferAccessIter2C<DataC,DataC> it(*this,arr);it;it++)
      it.Data1() += it.Data2();
    return *this;
  }
  
  template<class DataC>
  const SArray1dC<DataC> & SArray1dC<DataC>::operator-=(const SArray1dC<DataC> & arr) {
    for(BufferAccessIter2C<DataC,DataC> it(*this,arr);it;it++)
      it.Data1() -= it.Data2();
    return *this;
  }
    
  template<class DataC>
  const SArray1dC<DataC> & SArray1dC<DataC>::operator*=(const SArray1dC<DataC> & arr) {
    for(BufferAccessIter2C<DataC,DataC> it(*this,arr);it;it++)
      it.Data1() *= it.Data2();
    return *this;
  }
    
  template<class DataC>
  const SArray1dC<DataC> & SArray1dC<DataC>::operator/=(const SArray1dC<DataC> & arr) {
    for(BufferAccessIter2C<DataC,DataC> it(*this,arr);it;it++)
      it.Data1() /= it.Data2();
    return *this;
  }
  
  template<class DataC>
  const SArray1dC<DataC> & SArray1dC<DataC>::operator+=(const DataC &number) {
    for(BufferAccessIterC<DataC> it(*this);it;it++)
      it.Data1() += number;
    return *this;
  }
  
  
  template<class DataC>
  const SArray1dC<DataC> & SArray1dC<DataC>::operator-=(const DataC &number) {
    for(BufferAccessIterC<DataC> it(*this);it;it++)
      it.Data1() -= number;
    return *this;
  }
  
  template<class DataC>
  const SArray1dC<DataC> & SArray1dC<DataC>::operator*=(const DataC &number) {
    for(BufferAccessIterC<DataC> it(*this);it;it++)
      it.Data1() *= number;
    return *this;
  }
  
  template<class DataC>
  const SArray1dC<DataC> & SArray1dC<DataC>::operator/=(const DataC &number) {
    for(BufferAccessIterC<DataC> it(*this);it;it++)
      it.Data1() /= number;
    return *this;
  }
  
  template<class DataC>
  void SArray1dC<DataC>::Sort() {
    BufferAccessIterC<DataC> it(*this);
    if(!it)
      return ; // Empty, so we're done.
    DataC *lv;
    bool changed = true;
    do {
      changed = false;
      it.First(*this);
      lv = &(*it);
      it++;
      for(;it;it++) {
	if(*lv < *it) {
	  DataC t = *lv;
	  *lv = *it;
	  *it = t;
	  changed = true;
	}
      }
    } while(changed) ;
    return ;
  }

  template<class DataC>
  bool SArray1dC<DataC>::operator==(const SArray1dC<DataC> & vv) {
    for(BufferAccessIter2C<DataC,DataC> it(*this,arr);it;it++)
      if(it.Data1() != it.Data2())
	return false;
    return true;
  }
  
  template<class DataC>
  UIntT SArray1dC<DataC>::Hash() const {
    UIntT ret = Size();
    for(BufferAccessIterC<DataC> it(*this);it;it++)
      ret += StdHash(it.Data()) ^ (ret >> 1) ;
    return ret;
  }

}
#endif

