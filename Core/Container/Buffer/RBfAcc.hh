// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLRBFACC_HEADER
#define RAVLRBFACC_HEADER
//////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Buffer/RBfAcc.hh"
//! lib=RavlCore
//! userlevel=Develop
//! author="Radek Marik"
//! docentry="Ravl.Core.Arrays.Buffer"
//! rcsid="$Id$"
//! date="26/2/1997"
//! example=exRBfAcc.cc

#include "Ravl/BufferAccess.hh"
#include "Ravl/Assert.hh"
#include "Ravl/IndexRange1d.hh"

class istream;
class ostream;

namespace RavlN {
  
  class BinOStreamC;
  class BinIStreamC;
  
  // -------------------------------------------------------------------------
  // ********** RangeBufferAccessC *******************************************
  // -------------------------------------------------------------------------
  
  //: Basic access to buffer with limited range
  // The class RangeBufferAccessC enables to random indexed access to
  // a sequentially organised continous part of memory called buffer.
  // The access functions check if an accessed element is valid only in
  // debug mode.
  
  template <class DataC>
  class RangeBufferAccessC 
    : public BufferAccessC<DataC>
  {
  public:
    
    typedef DataC ElementT;
  
    // Constructors, copies, assigment, and destructor
    // -----------------------------------------------
    
    inline RangeBufferAccessC(DataC * bp = 0, const IndexRangeC & r = 0);
    //: Creates an access to a buffer pointed by the pointer 'bp'. 
    // If 'bp' is 0, the access is not valid.
    // 'bp' Is assumed to point to the r.Min() element of the array. 
    
    inline RangeBufferAccessC(const IndexRangeC & r,DataC * bp);
    //: Creates an access to a buffer pointed by the pointer 'bp'. 
    // Where bp has already had r.LCol() subtracted from it.
    // This is has been introduced to allow a bug fix in the class 
    // ImageC<T>. 
    
    inline RangeBufferAccessC(const BufferAccessC<DataC> & bp,
			      const IndexRangeC          & r);
    //: Creates an access to a buffer referenced by 'bp' with range 'r'.
    // the first element in 'bp' will be moved to offset 'r.Min()'.
    
    inline RangeBufferAccessC(const IndexRangeC & r,const BufferAccessC<DataC> & bp);
    //: Creates an access to a buffer referenced by 'bp' with range 'r'.
    // This assumes 'bp' has already been shifted so range 'r' will index
    // valid elements.
    
    inline RangeBufferAccessC(const RangeBufferAccessC<DataC> & ba);
    //: Creates a physical copy of the access 'ba'.
    
    inline RangeBufferAccessC(const RangeBufferAccessC<DataC> & ba,
			      const IndexRangeC               & r);
    //: Creates a physical copy of the access 'ba' limited by new range 'r'.
    
    inline const RangeBufferAccessC<DataC> & operator=(DataC * bp);
    //: Changes the reference element to the element pointed by 'bp'.
    
    // Access to the object
    // --------------------
        
    //inline const BufferAccessC<DataC> & Access(void) const;
    // Returns this object.
    
    inline DataC * DataStart()
      { return ReferenceElm() + range.Min().V(); }
    //: Returns the address of the first element of the buffer.
    
    inline const DataC * DataStart() const
      { return ReferenceElm() + range.Min().V(); }
    //: Returns the address of the first element of the buffer.
    
    inline SizeT Size() const
      { return range.Size(); }
    // Returns the number of elements of the array.
    
    inline const IndexRangeC & Range() const
      { return range; }
    // Returns the usable range of indeces expressed by this object.
    
    inline IndexC IMin() const
      { return range.Min(); }
    // Returns the minimum index of the range of this access.
    
    inline IndexC IMax() const
      { return range.Max(); }
    // Returns the maximum index of the range of this access.
    
    inline const DataC  & operator[](IndexC i) const;
    // Read-only access to the ('i'+1)-th element of the buffer.     
    
    inline DataC & operator[](IndexC i);
    // Read-write access  to the ('i'+1)-th element of the buffer. 
    
    inline const RangeBufferAccessC<DataC> & RAccess(void) const;
    // Returns this object.
    
    // Logical functions
    // -----------------
        
    inline bool IsEmpty() const
      { return range.IsEmpty(); }
    // Returns TRUE if the size of the array is zero.
    
    inline bool Contains(IndexC i) const
      { return range.Contains(i); }
    // Returns TRUE if the array contains an item with the index 'i'.
    
    inline 
    bool IsOverlapping(const RangeBufferAccessC<DataC> & acc) const
      { return range.IsOverlapping(acc.range); }
    // Returns TRUE if this access has an item with the same index as
    // an item of the access 'acc'.
    
    // Modifications of the access
    // ---------------------------
    
    inline 
      const RangeBufferAccessC<DataC> & operator+=(SizeT i);
    // Changes indeces of the access to be 'i' units higher.
    
    inline 
      RangeBufferAccessC<DataC> operator+(SizeT i) const;
    // Creates the new access object with the indeces 'i' units higher
    // than those used in this access object.
  
    inline const IndexRangeC & ShrinkHigh(SizeT k)
      { return range.ShrinkHigh(k); }
    //: Changes the number of elements by subtracting the last 'k' elements.
    
    inline void ShiftIndexes(IndexC offset);
    //: All indexes of the items will be changed by 'offset'.
    // The range will be shifted by -offset.
    
    inline void SetSubRange(IndexC newMin, IndexC newMax)
      { range.Clip(IndexRangeC(newMin, newMax)); }
    //: Constrain the indexs that can be accessed from the array.
    // The range of indexes of this array will be constrained to cover
    // the index range <newMin, newMax> at most.
    
    inline 
      const RangeBufferAccessC<DataC> & Swap(RangeBufferAccessC<DataC> & a);
    // Exchanges the contents of this buffer with buffer 'a'.
    
    inline void Swap(IndexC i1, IndexC i2);
    // Exchanges the contents of elements with indeces 'i1' and 'i2'.
    
    inline void Attach(const RangeBufferAccessC<DataC> & b);
    // Changes this buffer access to have the same access rights as 'b'.
    
    inline void Attach(const BufferAccessC<DataC> & b,
		       const IndexRangeC          & r);
    // Changes this buffer access to have the access rights as 'b' limited
    // by range 'r'. so the first element in 'b' is accessed at 'r.Min()'.
    
    // Modifications of the buffer contents
    // ------------------------------------
    
    void Fill(const DataC & d);
    //: Fill the buffer with the value 'd'.
    
  protected:
    
    // Copy
    // ----
    
    RangeBufferAccessC<DataC> Copy(void) const;
    // Returns a physical copy of this access pointing to the physical 
    // copy of the accessed buffer in the range accessible by this access.
    // The new copy is necessary to attach to reference counted buffer
    // or to delete at the end of the life of this object.
    
    
  private:
    
    // Object representation
    // ---------------------
    // This could be implemented nicely by private inheritance. Unfortunately,
    // g++2.7.2 has got some problems with the scope of typedef.
    
    IndexRangeC range; // Information on the limits of the buffer 
  };
  
  /////////////////////////////////////////////////////////////////////////////
  
  //: Wrtie buffer to stream.
  // NB. This size of the buffer is NOT written.
  
  template <class DataC>
  ostream &operator<<(ostream &out,const RangeBufferAccessC<DataC> &dat) {
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
  istream &operator>>(istream &strm,RangeBufferAccessC<DataC> &dat) {
    DataC *at = dat.DataStart();
    DataC *endOfRow = &at[dat.Size()];
    for(;at != endOfRow;at++)
      strm >> *at;
    return strm;
  }
  
  
  //: Wrtie buffer to stream.
  // NB. This size of the buffer is NOT written.
  
  template <class DataC>
  BinOStreamC &operator<<(BinOStreamC &out,const RangeBufferAccessC<DataC> &dat) {
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
  BinIStreamC &operator>>(BinIStreamC &strm,RangeBufferAccessC<DataC> &dat) {
    DataC *at = dat.DataStart();
    DataC *endOfRow = &at[dat.Size()];
    for(;at != endOfRow;at++)
      strm >> *at;
    return strm;
  }
  
  template <class DataC>
  inline 
  RangeBufferAccessC<DataC>::RangeBufferAccessC(DataC * bp, 
						const IndexRangeC & r)
    : BufferAccessC<DataC>(bp - r.Min().V()), 
      range(r)
  {}
  
  template <class DataC>
  inline 
  RangeBufferAccessC<DataC>::RangeBufferAccessC( const IndexRangeC & r,
						 DataC * bp)
    : BufferAccessC<DataC>(bp), 
      range(r)
  {}

  template <class DataC>
  inline 
  RangeBufferAccessC<DataC>::RangeBufferAccessC(const BufferAccessC<DataC> & bp,
						const IndexRangeC          & r)
    : BufferAccessC<DataC>(const_cast<BufferAccessC<DataC> &>(bp) - r.Min().V()), 
      range(r)
  {}

  template <class DataC>
  inline 
  RangeBufferAccessC<DataC>::RangeBufferAccessC(const IndexRangeC & r,const BufferAccessC<DataC> & bp)
    : BufferAccessC<DataC>(const_cast<BufferAccessC<DataC> &>(bp)), 
      range(r)
  {}
  
  template <class DataC>
  inline 
  RangeBufferAccessC<DataC>::RangeBufferAccessC(const RangeBufferAccessC<DataC> & ba)
    : BufferAccessC<DataC>(ba), 
      range(ba.range)
  {}
  
  template <class DataC>
  inline 
  RangeBufferAccessC<DataC>::RangeBufferAccessC(const RangeBufferAccessC<DataC> & ba,
						const IndexRangeC & r)
    : BufferAccessC<DataC>(ba), range(r)
  {
#if RAVL_CHECK
    if (!r.In(ba.Range()))
      IssueError(__FILE__,__LINE__,"Index range %d to %d out of  range 0 - %u  ",
		 r.Min().V(),r.Max().V(),ba.Range().Min().V(),ba.Range().Max().V());
#endif
  }
  
  ///////////////////////////////////////////////////////////
  
  
  template <class DataC>
  inline 
  const RangeBufferAccessC<DataC> & 
  RangeBufferAccessC<DataC>::operator=(DataC * bp) {
    BufferAccessC<DataC>::operator=(bp);
    return *this;
  }
  
  template <class DataC>
  inline 
  const DataC  & 
  RangeBufferAccessC<DataC>::operator[](IndexC i) const {
#if RAVL_CHECK
    if (!Contains(i)) 
      IssueError(__FILE__,__LINE__,"Index  %d  out of  range 0 - %u  ",
		 i.V(),Range().Min().V(),Range().Max().V());
#endif
    return BufferAccessC<DataC>::operator[](i);
  }
  
  template <class DataC>
  inline 
  DataC & RangeBufferAccessC<DataC>::operator[](IndexC i) {
#if RAVL_CHECK
    if (!Contains(i)) 
      IssueError(__FILE__,__LINE__,"Index  %d  out of  range 0 - %u  ",
		 i.V(),Range().Min().V(),Range().Max().V());
#endif
    return BufferAccessC<DataC>::operator[](i);
  }
  
  template <class DataC>
  inline 
  const RangeBufferAccessC<DataC> & 
  RangeBufferAccessC<DataC>::RAccess(void) const
  { return *this; }

  template <class DataC>
  inline 
  const RangeBufferAccessC<DataC> & 
  RangeBufferAccessC<DataC>::Swap(RangeBufferAccessC<DataC> & a) {
    DataC *tmp(buff);
    buff = a.buff; 
    a.buff = tmp;
    range.Swap(a.range);
    return *this;
  }
  
  template <class DataC>
  inline 
  void  RangeBufferAccessC<DataC>::Swap(IndexC i1, IndexC i2) {
    DataC d     = (*this)[i1];
    (*this)[i1] = (*this)[i2];
    (*this)[i2] = d;
  }
 
  template <class DataC>
  inline 
  void 
  RangeBufferAccessC<DataC>::Attach(const RangeBufferAccessC<DataC> & b)
  { *this=b; }
  
  template <class DataC>
  inline 
  void 
  RangeBufferAccessC<DataC>::Attach(const BufferAccessC<DataC> & b,
				    const IndexRangeC &          r) {
    ((BufferAccessC<DataC> &)(*this)) = b - r.Min();
    range=r;
  }

  template <class DataC>
  inline 
  const RangeBufferAccessC<DataC> & 
  RangeBufferAccessC<DataC>::operator+=(SizeT i) {
    buff -= i;
    range += i;
    return *this;
  }
  
  template <class DataC>
  inline 
  RangeBufferAccessC<DataC> 
  RangeBufferAccessC<DataC>::operator+(SizeT i) const
  { return RangeBufferAccessC<DataC>(buff - i, range + i); }
  
  template <class DataC>
  inline
  void
  RangeBufferAccessC<DataC>::ShiftIndexes(IndexC offset) { 
    ((BufferAccessC<DataC> &) *this) += offset.V(); 
    range -= offset.V();
  }

  template <class DataC>
  RangeBufferAccessC<DataC> 
  RangeBufferAccessC<DataC>::Copy(void) const {
    if (IsEmpty()) 
      return RangeBufferAccessC<DataC>();
    DataC * bp = new DataC[Size()];
    RangeBufferAccessC<DataC> b(bp, range);
    const DataC *at = DataStart();
    DataC *at2 = b.DataStart();
    const DataC *endOfRow = &at[range.Size()];
    for(;at != endOfRow;at++,at2++)
      *at2 = *at;
    return b;
  }
  
  template <class DataC>
  void 
  RangeBufferAccessC<DataC>::Fill(const DataC & d) {
    DataC *at = DataStart();
    DataC *endOfRow = &at[range.Size()];
    for(;at != endOfRow;at++)
      *at = d;
  }
  
}
#endif



