// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SARRAY1D_HEADER
#define RAVL_SARRAY1D_HEADER
////////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/SArray/SArray1d.hh"
//! lib=RavlCore
//! author="Radek Marik"
//! docentry="Ravl.Core.Arrays.1D"
//! date="21/2/1996"
//! rcsid="$Id$"

#include "Ravl/Buffer.hh"
#include "Ravl/SBfAcc.hh"
#include "Ravl/Pair.hh"
#include "Ravl/BfAccIter.hh"
#include "Ravl/BfAccIter2.hh"
#include "Ravl/BfAccIter3.hh"
#include "Ravl/StdHash.hh"
#include "Ravl/Stream.hh"

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
  
  template <class DataT>
  class SArray1dC
    : public SizeBufferAccessC<DataT> 
  { 
  public:
    typedef DataT ElementT;
    //: Allow function templates to find type of array.
    
    typedef IndexC KeyT;
    //: Allow function templates to find type of index.
    
    typedef SArray1dIterC<DataT> IteratorT;
    //: Type of iterator.
    
    //:---------------------------------------
    // Constructors, assigment, and destructor
    
    SArray1dC();
    //: Create an array of zero length
    
    SArray1dC(const SizeT dim);
    //: Creates an uninitialized array with the range <0, 'dim'-1>.
    
    SArray1dC(const Slice1dC<DataT> &slice,bool alwaysCopy = true);
    //: Make an array from a slice.
    // This will create an array with the values from the slice.
    // if the stride of the slice is not 1, and alwaysCopy is true the
    // a copy is done.
    
    SArray1dC(const PairC<DataT> & pr);
    //: Creates an array with two elements from a PairC object.
    
    SArray1dC(const SArray1dC<DataT> & vv);
    //: Another access to the array 'vv'.
    
    SArray1dC(DataT *      data,
	      const SizeT  dim,
	      bool     removable = true);
    //: The array is created from the memory location 'data' with the range
    //: of access in <0, 'dim'-1>. 
    // If flag 'removable' is false, 'data' is not deallocated during 
    // destructing of the array.
    
    SArray1dC(const BufferC<DataT> & bf,SizeT dim,SizeT offsetInBuff = 0);
    //: Creates the array of size 'dim' using the buffer 'bf'.
    // Use buffer 'bf',  make access of 'dim' elements. 
    // the start of the buffer should be 'offsetInBuff' elements into
    // the buffer.
    
    SArray1dC(const SArray1dC<DataT> & vv, const SizeT dim,SizeT offsetInBuff = 0);
    //: The subarray of the 'vv' with size 'dim'.
    
    SArray1dC(const BufferC<DataT> & vv, const SizeBufferAccessC<DataT> &sbf);
    //: Construct from a buffer an size buffer access.
    
    SArray1dC<DataT> Copy() const;
    //: Creates a new physical copy of the array.
    
    SArray1dC<DataT> Copy(UIntT extend) const;
    //: Creates a new physical copy of the array.
    // 'extend' extra elements initalised by the default constuctor
    // are appended to the end of the array.
    
    void CopyFrom(const Slice1dC<DataT> &slice)
    { SizeBufferAccessC<DataT>::CopyFrom(slice); }
    //: Copy contents of slice into array.
    // The first element of the slice is copied to element
    // 0 of this array, second to 1 etc.  If this array isn't
    // large enough an exception is thrown.
    
    inline const SArray1dC<DataT> & operator=(const SArray1dC<DataT> & vv);
    //: Assign this handle to the data in VV.
    
    SArray1dC<DataT> operator+(const SArray1dC<DataT> & arr) const;
    //: Sums 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    SArray1dC<DataT> operator-(const SArray1dC<DataT> & arr) const;
    //: Subtract 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    SArray1dC<DataT> operator*(const SArray1dC<DataT> & arr) const;
    //: Multiplies 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    SArray1dC<DataT> operator/(const SArray1dC<DataT> & arr) const;
    //: Divides 2 numerical arrays. 
    // The operator returns the result as a new array.
    
    SArray1dC<DataT> operator*(const DataT &number) const;
    //: Multiplies the array by the 'number'. 
    // The operator returns the result as a new array.
    
    SArray1dC<DataT> operator/(const DataT &number) const;
    //: Divides all array items by the 'number'. 
    // The operator returns the result as a new array.
    
    SArray1dC<DataT> operator+(const DataT &number) const;
    //: Adds 'number' to the array. 
    // The operator returns the result as a new array.
    
    SArray1dC<DataT> operator-(const DataT &number) const;
    //: Subtracts 'number' from all array items.
    // The operator  returns the result as a new array.
    
    const SArray1dC<DataT> & operator+=(const SArray1dC<DataT> & arr);
    //: Adds the 2nd array to this array.
    
    const SArray1dC<DataT> & operator-=(const SArray1dC<DataT> & arr);
    //: Subtracts the 2nd array from this array.
    
    const SArray1dC<DataT> & operator*=(const SArray1dC<DataT> & arr);
    //: Multiplies the 2nd array to this array.
    
    const SArray1dC<DataT> & operator/=(const SArray1dC<DataT> & arr);
    //: Divides the 2nd array from this array.
    
    const SArray1dC<DataT> & operator+=(const DataT &number);
    //: Adds 'number' to all array items.
    
    const SArray1dC<DataT> & operator-=(const DataT &number);
    //: Subtracts 'number' from all array items.
    
    const SArray1dC<DataT> & operator*=(const DataT &number);
    //: Multiplies the array by the 'number'.
    
    const SArray1dC<DataT> & operator/=(const DataT &number);
    //: Divides the array elements by the 'number'.
    
    DataT Sum() const;
    //: Calculate the sum of all elements in the array
    
    DataT SumOfSqr() const;
    //: Calculate the sum of the squares of all elements in the array
    
    //:-----------------------------------
    // Access to the object and its parts.
    
    inline const SArray1dC<DataT> & SArray1d() const
      { return *this; }
    //: Access to the whole constant array.
    
    inline SArray1dC<DataT> & SArray1d()
      { return *this; }
    //: Access to the whole array.

    Slice1dC<DataT> Slice1d()
    { return Slice1dC<DataT>(buff,DataStart(),Size(),1); }
    //: Access array as a slice.
    
    //:-----------------------------------
    // Modifications of the representation
        
    inline SArray1dC<DataT> & Append(const SArray1dC<DataT> & a);
    // This array is extended by the length of the array 'a' and the contents
    // of both arrays are copied to it. Empty arrays are handled correctly.
    
    SArray1dC<DataT> Join(const SArray1dC<DataT> &Oth) const;
    // Join this Array and another into a new Array which
    // is returned. This does not change either of its arguments.
    // This is placed in the array first, followed by 'Oth'.
    
    SArray1dC<DataT> From(UIntT offset) { 
      if(offset >= Size())
	return SArray1dC<DataT>(); // Empty array.
      SizeT nsize = Size() - offset;
      return SArray1dC<DataT>(*this,nsize,offset); 
    }
    //: Return array from offset to the end of the array.
    // If offset is larger than the array an empty array
    // is returned,

    SArray1dC<DataT> From(UIntT offset,UIntT size) { 
      if((offset + size) > Size())
	return SArray1dC<DataT>(); // Empty array.
      return SArray1dC<DataT>(*this,size,offset); 
    }
    //: Return array from offset to the end of the array.
    // If offset is larger than the array an empty array
    // is returned,
    
    SArray1dC<DataT> After(UIntT offset) 
    { return From(offset+1); }
    //: Return array after offset to the end of the array.
    // If offset is larger than the array an empty array
    // is returned,
    
    //:------------------
    // Special operations
    
    BufferC<DataT> &Buffer()
      { return buff; }
    //: Access base data buffer.
    // Experts only.

    const BufferC<DataT> &Buffer() const
      { return buff; }
    //: Constant access base data buffer.
    // Experts only.
    
    void Sort();
    //: Sort the array in place.
    // This does a simple bubble sort.
    // FIXME:- we could do with something better!

    bool operator==(const SArray1dC<DataT> & vv) const;
    //: Comparison operator
    // Returns true if the two arrays are the same length and
    // their contents are identical.
    
    UIntT Hash() const;
    //: Compute a hash value for the array.

    inline DataT * DataStart() const
      { return SizeBufferAccessC<DataT>::ReferenceElm(); }
    //: Returns the address of element 0.
    // If the array has zero length a null pointer may
    // be returned.
  protected:
    SArray1dC(BufferC<DataT> & bf,DataT *start, const SizeT dim);
    //: Creates the array of size 'dim' using the buffer 'bf', with
    //: 0'th element at start.
    // Used for building SArray's from Arrays.
    
  private:
        
    BufferC<DataT> buff;  // The reference counted storage.
    
    friend class SArray1dIterC<DataT>;
    friend class Array1dC<DataT>;
  };
  
  template <class DataT>
  BinOStreamC & operator<<(BinOStreamC & s, const SArray1dC<DataT> & arr);
  // Prints array into the stream 's'.
  
  template <class DataT>
  BinIStreamC & operator>>(BinIStreamC& s, SArray1dC<DataT> & arr);
  // Assigns the values into the array 'arr'.
  
  template <class DataT>
  SArray1dC<DataT> & BubbleSort(SArray1dC<DataT> & arr);
  // Sorts arr using operator <.
  
  template <class DataT>
  istream & operator>>(istream & s, SArray1dC<DataT> & arr);
  // Assigns the values into the array 'arr'.
  
  template <class DataT>
  SArray1dC<DataT> & BubbleSort(SArray1dC<DataT> & arr);
  // Sorts arr using operator <.
  
  /////////////////////////////////////////////////////////////////////////////
  
  template <class DataT>
  inline
  const SArray1dC<DataT> &
  SArray1dC<DataT>::operator=(const SArray1dC<DataT> & vv) {
    if (this == &vv) return *this;
    SizeBufferAccessC<DataT>::operator=(vv);
    buff=vv.buff;
    return *this;
  }
  
  
  template <class DataT>
  inline 
  SArray1dC<DataT> & 
  SArray1dC<DataT>::Append(const SArray1dC<DataT> & a)  {
    (*this) = Join(a);
    return *this;
  }
  
  template <class DataT>
  SArray1dC<DataT>::SArray1dC()
    : SizeBufferAccessC<DataT>(),
      buff()
  {}

  template <class DataT>
  SArray1dC<DataT>::SArray1dC(const PairC<DataT> & pr)
    : SizeBufferAccessC<DataT>(),
      buff(2)
  {
    Attach(buff,2);
    (*this)[0] = pr[0];
    (*this)[1] = pr[1];
  }

  template <class DataT>
  SArray1dC<DataT>::SArray1dC(const Slice1dC<DataT> &slice,bool alwaysCopy) {
    if(!alwaysCopy && slice.Stride() == 1) {
      buff = slice.Buffer();
      SizeBufferAccessC<DataT>::operator=(SizeBufferAccessC<DataT>(const_cast<DataT *>(&(slice[0])),
								   slice.Size()));
      return ;
    }
    buff = BufferC<DataT>(slice.Size());
    Attach(buff,slice.Size());
    // Copy data.
    DataT *at = buff.ReferenceElm();
    for(Slice1dIterC<DataT> it(slice);it;it++,at++)
      *at = *it;

  }
  
  template <class DataT>
  SArray1dC<DataT>::SArray1dC(const SizeT dim)
    : SizeBufferAccessC<DataT>(),
      buff(dim)
  { Attach(buff,dim); }
  
  template <class DataT>
  SArray1dC<DataT>::SArray1dC(const SArray1dC<DataT> & vv)
    : SizeBufferAccessC<DataT>(vv),
      buff(vv.buff)
  {}

  template <class DataT>
  SArray1dC<DataT>::SArray1dC(DataT *data, 
			      SizeT dim,
			      bool removable)
    : SizeBufferAccessC<DataT>(data, dim),
      buff(dim,data,false, removable)
  {}
  
  template <class DataT>
  SArray1dC<DataT>::SArray1dC(const BufferC<DataT> & bf,SizeT dim,SizeT offsetInBuff)
    : SizeBufferAccessC<DataT>(const_cast<BufferC<DataT> &>(bf).BufferAccess() + offsetInBuff, dim),
      buff(bf)
  {}

  template <class DataT>
  SArray1dC<DataT>::SArray1dC(BufferC<DataT> & bf,
			      DataT *start, 
			      const SizeT dim)
    : SizeBufferAccessC<DataT>(start, dim),
      buff(bf)
  {}

  template <class DataT>
  SArray1dC<DataT>::SArray1dC(const BufferC<DataT> & bf, const SizeBufferAccessC<DataT> &sbf) 
    : SizeBufferAccessC<DataT>(sbf),
      buff(bf)
  {}
  
  template <class DataT>
  SArray1dC<DataT>::SArray1dC(const SArray1dC<DataT> & vv, 
			      const SizeT             dim,
			      SizeT offsetInBuff)
  : SizeBufferAccessC<DataT>(vv.SAccess() + offsetInBuff, dim),
    buff(vv.buff)
  {
    RavlAssert(vv.Size() >= (offsetInBuff + dim)); // Make sure its big enought.
  }

  template <class DataT>
  SArray1dC<DataT> SArray1dC<DataT>::Copy() const {
    return SArray1dC<DataT>(SizeBufferAccessC<DataT>::Copy().ReferenceElm(), 
			    Size(),true);
  }

  template <class DataT>
  SArray1dC<DataT> SArray1dC<DataT>::Copy(UIntT extend) const {
    SArray1dC<DataT> ret(Size() + extend);
    for(BufferAccessIter2C<DataT,DataT> it(*this,ret);it;it++)
      it.Data2() = it.Data1();
    return ret;
  }
  

  template <class DataT>
  SArray1dC<DataT> 
  SArray1dC<DataT>::Join(const SArray1dC<DataT> &Oth) const  {
    // FIXME :- Do this more efficently, with ptrs.
    const SizeT len1 = Size();
    const SizeT len2 = Oth.Size();
    SArray1dC<DataT> newarr(len1 + len2);
    for(BufferAccessIter2C<DataT,DataT> it(*this,newarr);it;it++)
      it.Data2() = it.Data1();
    for(BufferAccessIter2C<DataT,DataT> it2(Oth,newarr,0,len1);it2;it2++)
      it2.Data2() = it2.Data1();
    return newarr;
  }

  template <class DataT>
  ostream &
  operator<<(ostream & s, const SArray1dC<DataT> & arr) {
    s << arr.Size() << '\n'; 
    for(BufferAccessIterC<DataT> it(arr);it;it++)
      s << ((const DataT &) *it) << '\n';
    return s;
  }
  
  template <class DataT>
  istream &
  operator>>(istream & s, SArray1dC<DataT> & arr) { 
    SizeT n = 0;
    s >> n;
    s.get(); // Get '\n' after size to avoid trouble with reading StringC's.
    if (n != arr.Size()) {
      SArray1dC<DataT> brr(n);
      arr = brr;
    }
    for(BufferAccessIterC<DataT> it(arr);it;it++)
      s >> *it;
    return s;
  }

  template <class DataT>
  SArray1dC<DataT> &
  BubbleSort(SArray1dC<DataT> & arr) {
    IndexC    low = 0;
    IndexC    upp = arr.Size()-1;
    bool  change;
    DataT     ev;
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
  
  
  template<class DataT>
  BinOStreamC &
  operator<<(BinOStreamC & s, const SArray1dC<DataT> & arr) {
    s << arr.Size();
    for(BufferAccessIterC<DataT> it(arr);it;it++)
      s << it.Data();
    return s;
  }
  
  template<class DataT>
  BinIStreamC &
  operator>>(BinIStreamC & s, SArray1dC<DataT> & arr) {
    SizeT size;
    s >> size;
    arr = SArray1dC<DataT>(size);
    for(BufferAccessIterC<DataT> it(arr);it;it++)
      s >> it.Data();
    return s;
  }

  template<class DataT>
  SArray1dC<DataT> SArray1dC<DataT>::operator+(const SArray1dC<DataT> & arr) const {
    SArray1dC<DataT> ret(Size());
    for(BufferAccessIter3C<DataT,DataT,DataT> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray1dC<DataT> SArray1dC<DataT>::operator-(const SArray1dC<DataT> & arr) const {
    SArray1dC<DataT> ret(Size());
    for(BufferAccessIter3C<DataT,DataT,DataT> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray1dC<DataT> SArray1dC<DataT>::operator*(const SArray1dC<DataT> & arr) const {
    SArray1dC<DataT> ret(Size());
    for(BufferAccessIter3C<DataT,DataT,DataT> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray1dC<DataT> SArray1dC<DataT>::operator/(const SArray1dC<DataT> & arr) const {
    SArray1dC<DataT> ret(Size());
    for(BufferAccessIter3C<DataT,DataT,DataT> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() / it.Data3();
    return ret;
  }
  
  template<class DataT>
  SArray1dC<DataT> SArray1dC<DataT>::operator+(const DataT &number) const {
    SArray1dC<DataT> ret(Size());
    for(BufferAccessIter2C<DataT,DataT> it(ret,*this);it;it++)
      it.Data1() = it.Data2() + number;
    return ret;
  }
  
  template<class DataT>
  SArray1dC<DataT> SArray1dC<DataT>::operator-(const DataT &number) const {
    SArray1dC<DataT> ret(Size());
    for(BufferAccessIter2C<DataT,DataT> it(ret,*this);it;it++)
      it.Data1() = it.Data2() - number;
    return ret;
  }
  
  template<class DataT>
  SArray1dC<DataT> SArray1dC<DataT>::operator*(const DataT &number) const {
    SArray1dC<DataT> ret(Size());
    for(BufferAccessIter2C<DataT,DataT> it(ret,*this);it;it++)
      it.Data1() = it.Data2() * number;
    return ret;
  }
  
  template<class DataT>
  SArray1dC<DataT> SArray1dC<DataT>::operator/(const DataT &number) const {
    SArray1dC<DataT> ret(Size());
    for(BufferAccessIter2C<DataT,DataT> it(ret,*this);it;it++)
      it.Data1() = it.Data2() / number;
    return ret;
  }
  
  template<class DataT>
  const SArray1dC<DataT> & SArray1dC<DataT>::operator+=(const SArray1dC<DataT> & arr) {
    for(BufferAccessIter2C<DataT,DataT> it(*this,arr);it;it++)
      it.Data1() += it.Data2();
    return *this;
  }
  
  template<class DataT>
  const SArray1dC<DataT> & SArray1dC<DataT>::operator-=(const SArray1dC<DataT> & arr) {
    for(BufferAccessIter2C<DataT,DataT> it(*this,arr);it;it++)
      it.Data1() -= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const SArray1dC<DataT> & SArray1dC<DataT>::operator*=(const SArray1dC<DataT> & arr) {
    for(BufferAccessIter2C<DataT,DataT> it(*this,arr);it;it++)
      it.Data1() *= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const SArray1dC<DataT> & SArray1dC<DataT>::operator/=(const SArray1dC<DataT> & arr) {
    for(BufferAccessIter2C<DataT,DataT> it(*this,arr);it;it++)
      it.Data1() /= it.Data2();
    return *this;
  }
  
  template<class DataT>
  const SArray1dC<DataT> & SArray1dC<DataT>::operator+=(const DataT &number) {
    for(BufferAccessIterC<DataT> it(*this);it;it++)
      it.Data1() += number;
    return *this;
  }
  
  
  template<class DataT>
  const SArray1dC<DataT> & SArray1dC<DataT>::operator-=(const DataT &number) {
    for(BufferAccessIterC<DataT> it(*this);it;it++)
      it.Data1() -= number;
    return *this;
  }
  
  template<class DataT>
  const SArray1dC<DataT> & SArray1dC<DataT>::operator*=(const DataT &number) {
    for(BufferAccessIterC<DataT> it(*this);it;it++)
      it.Data1() *= number;
    return *this;
  }
  
  template<class DataT>
  const SArray1dC<DataT> & SArray1dC<DataT>::operator/=(const DataT &number) {
    for(BufferAccessIterC<DataT> it(*this);it;it++)
      it.Data1() /= number;
    return *this;
  }
  
  template<class DataT>
  DataT SArray1dC<DataT>::Sum() const {
    if(Size() == 0) {
      DataT ret;
      SetZero(ret);
      return ret;
    }
    BufferAccessIterC<DataT> it(*this);
    DataT ret = StdCopy(*it);
    for(it++;it;it++)
      ret += *it;
    return ret;    
  }

  template<class DataT>
  DataT SArray1dC<DataT>::SumOfSqr() const {
    if(Size() == 0) {
      DataT ret;
      SetZero(ret);
      return ret;
    }
    BufferAccessIterC<DataT> it(*this);
    DataT ret = Sqr(*it);
    for(it++;it;it++)
      ret += Sqr(*it);
    return ret;
  }
  
  template<class DataT>
  void SArray1dC<DataT>::Sort() {
    BufferAccessIterC<DataT> it(*this);
    if(!it)
      return ; // Empty, so we're done.
    DataT *lv;
    bool changed = true;
    do {
      changed = false;
      it.First(*this);
      lv = &(*it);
      it++;
      for(;it;it++) {
	if(*lv < *it) {
	  DataT t = *lv;
	  *lv = *it;
	  *it = t;
	  changed = true;
	}
	lv = &(*it);
      }
    } while(changed) ;
    return ;
  }

  template<class DataT>
  bool SArray1dC<DataT>::operator==(const SArray1dC<DataT> & vv) const {
    if(Size() != vv.Size())
      return false;
    for(BufferAccessIter2C<DataT,DataT> it(*this,vv);it;it++)
      if(it.Data1() != it.Data2())
	return false;
    return true;
  }
  
  template<class DataT>
  UIntT SArray1dC<DataT>::Hash() const {
    UIntT ret = Size();
    for(BufferAccessIterC<DataT> it(*this);it;it++)
      ret += StdHash(it.Data()) ^ (ret >> 1) ;
    return ret;
  }

}
#endif

