// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSBFACC_HEADER 
#define RAVLSBFACC_HEADER 1
/////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Buffer/SBfAcc.hh"
//! lib=RavlCore
//! author="Radek Marik"
//! docentry="Ravl.Core.Arrays.Buffer"
//! date="14/02/97"
//! userlevel=Develop
//! rcsid="$Id$"

#include "Ravl/IndexRange1d.hh"
#include "Ravl/BufferAccess.hh"
#include <assert.h>

class istream;
class ostream;

namespace RavlN {
  
  class BinOStreamC;
  class BinIStreamC;
  
  //: Basic access to buffer with limited size
  // The class SizeBufferAccessC enables to random indexed access to
  // a sequentially organised continous part of memory called buffer.
  // The access functions check if an accessed element is valid only in
  // debug mode.
  
  template <class DataC>
  class SizeBufferAccessC 
    : public BufferAccessC<DataC>
  {
  public:
    typedef DataC ElementT;
    
    // Constructors, copies, assigment, and destructor
    // -----------------------------------------------
    
    inline SizeBufferAccessC()
      : sz(0)
      {}
    //: Default constructor.
    
    inline SizeBufferAccessC(DataC * bp, SizeT size = 0);
    // Creates an access to a buffer pointed by the pointer 'bp'. If
    // 'bp' is 0, the access is not valid.
    
    inline SizeBufferAccessC(const BufferAccessC<DataC> & bp,SizeT s);
    // Creates an access to a buffer referenced by 'bp' with size 's'.
    
    inline SizeBufferAccessC(const SizeBufferAccessC<DataC> & ba);
    // Creates a physical copy of the access 'ba'.
    
    inline SizeBufferAccessC(const SizeBufferAccessC<DataC> & ba,SizeT s);
    // Creates a physical copy of the access 'ba' limited by new size 's'.
    
    inline const SizeBufferAccessC<DataC> & operator=(DataC * bp);
    // Changes the reference element to the element pointed by 'bp'.
    
    // Access to the object
    // --------------------
    
    inline DataC * DataStart() const
      { return buff; }
    // Returns the address of the first element of the buffer.
    
    inline SizeT Size() const
      { return sz; }
    // Returns the number of elements of the array.
    
    inline IndexRangeC Limits() const
      { return IndexRangeC(0,sz); }
    // Returns the usable range of indeces expressed by this object.
    
    inline IndexRangeC Range() const
      { return IndexRangeC(0,sz); }
    // Returns the usable range of indeces expressed by this object.
    
    inline IndexC IMin() const
      { return 0; }
    // Returns the minimum index of the range of this access.
    
    inline IndexC IMax() const
      { return sz-1; }
    // Returns the maximum index of the range of this access.
    
    inline const DataC  & operator[](const IndexC i) const;
    // Read-only access to the ('i'+1)-th element of the buffer.     
    
    inline DataC & operator[](const IndexC i);
    // Read-write access  to the ('i'+1)-th element of the buffer. 
    
    inline const SizeBufferAccessC<DataC> & SAccess(void) const
      { return *this; }
    // Returns this object.
    
    // Logical functions
    // -----------------
    
    inline bool IsEmpty() const
      { return sz == 0; }
    // Returns TRUE if the size of the array is zero.
    
    inline bool Contains(IndexC i) const
      { return ((UIntT) i.V()) < sz; }
    // Returns TRUE if the array contains an item with the index 'i'.
    
    // Modifications of the access
    // ---------------------------
    
    inline SizeT ShrinkHigh(SizeT k) { 
      RavlAssert(k <= sz);
      sz -= k;
      return sz;
    }
    // Changes the number of elements by subtracting the last 'k' elements.
    
    inline 
      const SizeBufferAccessC<DataC> & Swap(SizeBufferAccessC<DataC> & a);
    // Exchanges the contents of this buffer with buffer 'a'.
    
    inline void Attach(const SizeBufferAccessC<DataC> & b);
    // Changes this buffer access to have the same access rights as 'b'.
    
    inline void Attach(const BufferAccessC<DataC> & b,
		       SizeT size);
    // Changes this buffer access to have the access rights as 'b' limited
    // for 'size' elements.
    
    inline SizeBufferAccessC<DataC> operator+(SizeT i) const;
    // Creates the new access object shifted 'i' elements to the right
    // (towards next elements). The size is descreased to fit the 
    // the original range of this access.
    
    // Modifications of the buffer contents
    // ------------------------------------
    
    void Fill(const DataC & d);
    // 'd' value is assigned to all elements of the buffer.
    
    void CopyFrom(const SizeBufferAccessC<DataC> &oth);
    //: Copy contents of another buffer into this one.
    // NB. Buffers MUST be the same length.
    
  protected:
    
    // Copy
    // ----
    
    SizeBufferAccessC<DataC> Copy(void) const;
    // Returns a physical copy of this access pointing to the physical 
    // copy of the accessed buffer in the range accessible by this access.
    // The new copy is necessary to attach to reference counted buffer
    // or to delete at the end of the life of this object.
    
  private:
    UIntT sz; // size of the buffer in elements.
  };
  
  /////////////////////////////////////////////////////////////////////////////
  
  template <class DataC>
  void 
  SizeBufferAccessC<DataC>::CopyFrom(const SizeBufferAccessC<DataC> &oth) {
    RavlAssert(oth.Size() == Size());
    DataC *to = ReferenceElm();
    DataC *from = oth.ReferenceElm();
    DataC *endOfRow = &to[Size()];
    for(;to != endOfRow;to++,from++)
      *to = *from;
  }
  
  template <class DataC>
  inline 
  SizeBufferAccessC<DataC>::SizeBufferAccessC(DataC * bp,SizeT size)
    : BufferAccessC<DataC>(bp), 
      sz(size)
  {}
  
  template <class DataC>
  inline 
  SizeBufferAccessC<DataC>::SizeBufferAccessC(const BufferAccessC<DataC> & bp,SizeT s)
    : BufferAccessC<DataC>(bp), 
      sz(s)
  {}
  
  template <class DataC>
  inline 
  SizeBufferAccessC<DataC>::
  SizeBufferAccessC(const SizeBufferAccessC<DataC> & ba)
    : BufferAccessC<DataC>(ba), 
      sz(ba.sz)
  {}
  
  template <class DataC>
  inline 
  SizeBufferAccessC<DataC>::
  SizeBufferAccessC(const SizeBufferAccessC<DataC> & ba,SizeT s)
    : BufferAccessC<DataC>(ba), 
      sz(s)
  {
#if RAVL_CHECK
    if (s > ba.Size())
      IssueError(__FILE__,__LINE__,"Size %u out of index range 0-%u  ",s ,ba.Size());
#endif
  }
  
  template <class DataC>
  inline 
  const SizeBufferAccessC<DataC> & 
  SizeBufferAccessC<DataC>::operator=(DataC * bp) {
    ((BufferAccessC<DataC> &) *this) = bp;
    return *this;
  }
  
  template <class DataC>
  inline 
  const DataC  & 
  SizeBufferAccessC<DataC>::operator[](const IndexC i) const {
#if RAVL_CHECK
    if (!Contains(i))
      IssueError(__FILE__,__LINE__,"Index %d out of  range 0 - %u  ",i.V() ,Size());
#endif
    return BufferAccessC<DataC>::operator[](i);
  }
  
  template <class DataC>
  inline 
  DataC & 
  SizeBufferAccessC<DataC>::operator[](const IndexC i) {
#if RAVL_CHECK
    if (!Contains(i)) 
      IssueError(__FILE__,__LINE__,"Index %d out of range 0 - %u  ",i.V() ,Size());
#endif
    return BufferAccessC<DataC>::operator[](i);
  }
  
  template <class DataC>
  inline 
  const SizeBufferAccessC<DataC> & 
  SizeBufferAccessC<DataC>::Swap(SizeBufferAccessC<DataC> & a) {
    BufferAccessC<DataC>::Swap(a);
    sz.Swap(a.sz);
    return *this;
  }
  
  template <class DataC>
  inline 
  void 
  SizeBufferAccessC<DataC>::Attach(const SizeBufferAccessC<DataC> & b)
  { *this=b; }

  template <class DataC>
  inline 
  void 
  SizeBufferAccessC<DataC>::Attach(const BufferAccessC<DataC> & b,
				   SizeT size) {
    ((BufferAccessC<DataC> &)(*this)) = b;
    sz=size;
  }
  
  template <class DataC>
  inline 
  SizeBufferAccessC<DataC> 
  SizeBufferAccessC<DataC>::operator+(SizeT i) const { 
    RavlAssert(i <= sz);
    return SizeBufferAccessC<DataC>(buff + i, sz - i); 
  }
  
  template <class DataC>
  SizeBufferAccessC<DataC> 
  SizeBufferAccessC<DataC>::Copy(void) const {
    if (IsEmpty()) 
      return SizeBufferAccessC<DataC>();
    DataC * bp = new DataC[Size()];
    SizeBufferAccessC<DataC> b(bp, Size());
    DataC *at = DataStart();
    DataC *at2 = b.DataStart();
    DataC *endOfRow = &at[sz];
    for(;at != endOfRow;at++,at2++)
      *at2 = *at;
    return b;
  }
  
  template <class DataC>
  void 
  SizeBufferAccessC<DataC>::Fill(const DataC & d) {
    DataC *at = DataStart();
    DataC *endOfRow = &at[sz];
    for(;at != endOfRow;at++)
      *at = d;
  }
  
  
  //: Wrtie buffer to stream.
  // NB. This size of the buffer is NOT written.
  
  template <class DataC>
  ostream &operator<<(ostream &out,const SizeBufferAccessC<DataC> &dat) {
    const DataC *at = dat.DataStart();
    const DataC *endOfRow = &at[dat.Size()];
    if(dat.Size() == 0)
      return out;
    out << *at;
    at++;
    for(;at != endOfRow;at++)
      out << ' ' << *at;
    return out;
  }
  
  //: Read buffer from stream.
  // NB. The buffer must be pre-allocated.

  template <class DataC>
  istream &operator>>(istream &strm,SizeBufferAccessC<DataC> &dat) {
    DataC *at = dat.DataStart();
    DataC *endOfRow = &at[dat.Size()];
    for(;at != endOfRow;at++)
      strm >> *at;
    return strm;
  }
  
  
  //: Wrtie buffer to stream.
  // NB. This size of the buffer is NOT written.
  
  template <class DataC>
  BinOStreamC &operator<<(BinOStreamC &out,const SizeBufferAccessC<DataC> &dat) {
    const DataC *at = dat.DataStart();
    const DataC *endOfRow = &at[dat.Size()];
    if(dat.Size() == 0)
    return out;
    for(;at != endOfRow;at++)
      out << *at;
    return out;
  }
  
  //: Read buffer from stream.
  // NB. The buffer must be pre-allocated.
  
  template <class DataC>
  BinIStreamC &operator>>(BinIStreamC &strm,SizeBufferAccessC<DataC> &dat) {
    DataC *at = dat.DataStart();
    DataC *endOfRow = &at[dat.Size()];
    for(;at != endOfRow;at++)
      strm >> *at;
    return strm;
  }
}
#endif


