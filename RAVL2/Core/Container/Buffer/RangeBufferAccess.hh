// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_RBFACC_HEADER
#define RAVL_RBFACC_HEADER
//////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Buffer/RangeBufferAccess.hh"
//! lib=RavlCore
//! userlevel=Develop
//! author="Radek Marik"
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! rcsid="$Id$"
//! date="26/2/1997"
//! example=exRBfAcc.cc

#include "Ravl/BufferAccess.hh"
#include "Ravl/Assert.hh"
#include "Ravl/IndexRange1d.hh"
#include "Ravl/Types.hh"

namespace RavlN {
  template <class DataT> class SizeBufferAccessC;
  template <class DataT> class Slice1dC;
  
  class BinOStreamC;
  class BinIStreamC;


  //: Basic access to buffer with limited range
  // The class RangeBufferAccessC enables to random indexed access to
  // a sequentially organised continous part of memory called buffer.
  // The access functions check if an accessed element is valid only in
  // debug mode.
  
  template <class DataT>
  class RangeBufferAccessC 
    : public BufferAccessC<DataT>
  {
  public:
    
    typedef DataT ElementT;
  
    // Constructors, copies, assigment, and destructor
    // -----------------------------------------------


    inline RangeBufferAccessC(DataT * bp = 0, const IndexRangeC & r = 0) 
     : BufferAccessC<DataT>(bp - r.Min().V()),
       m_range(r)
    {}
    //: Creates an access to a buffer pointed by the pointer 'bp'. 
    // If 'bp' is 0, the access is not valid.
    // 'bp' Is assumed to point to the r.Min() element of the array. 
    
    inline RangeBufferAccessC(const IndexRangeC & r,DataT * bp) 
      : BufferAccessC<DataT>(bp),
        m_range(r)
    {}
    //: Creates an access to a buffer pointed by the pointer 'bp'. 
    // Where bp has already had r.LCol() subtracted from it.
    
    inline RangeBufferAccessC(const BufferAccessC<DataT> & bp,
			      const IndexRangeC          & r)
      : BufferAccessC<DataT>(const_cast<BufferAccessC<DataT> &>(bp) - r.Min().V()),
        m_range(r)
    {}
    //: Creates an access to a buffer referenced by 'bp' with range 'r'.
    // the first element in 'bp' will be moved to offset 'r.Min()'.
    
    inline RangeBufferAccessC(const IndexRangeC & r,const BufferAccessC<DataT> & bp)
      : BufferAccessC<DataT>(const_cast<BufferAccessC<DataT> &>(bp)),
        m_range(r)
    {}
    //: Creates an access to a buffer referenced by 'bp' with range 'r'.
    // This assumes 'bp' has already been shifted so range 'r' will index
    // valid elements.
    
    inline RangeBufferAccessC(const RangeBufferAccessC<DataT> & ba)
      : BufferAccessC<DataT>(ba),
        m_range(ba.Range())
    {}
    //: Creates a new access to 'ba'.
    
    inline RangeBufferAccessC(const RangeBufferAccessC<DataT> & ba,
			      const IndexRangeC               & r)
      : BufferAccessC<DataT>(ba),
        m_range(r)
    {
#if RAVL_CHECK
      if ((!r.In(ba.Range()) && (r.Size() > 0)) || !ba.Range().Contains(r.Min()))
        IssueError(__FILE__,__LINE__,"Subrange %d to %d is not subset of buffer range %d - %d  ",
                  r.Min().V(),r.Max().V(),ba.Range().Min().V(),ba.Range().Max().V());
#endif
    }
    //: Creates a new access to 'ba' limited by range 'r'.
    
    inline RangeBufferAccessC(const SizeBufferAccessC<DataT> &sbf)
      : BufferAccessC<DataT>(sbf.ReferenceElm()), 
	m_range(0,sbf.Size()-1)
    {}
    //: Convert from a size buffer access.

    inline RangeBufferAccessC<DataT> DeepCopy(UIntT levels = (UIntT) -1) const ;
    //: Make a deep copy 
    
    inline const RangeBufferAccessC<DataT> & operator=(DataT * bp);
    //: Changes the reference element to the element pointed by 'bp'.
    
    // Access to the object
    // --------------------
        
    //inline const BufferAccessC<DataT> & Access(void) const;
    // Returns this object.

    inline DataT * ReferenceElm() const
    { return this->m_buff; }
    // Returns the pointer to the reference element of the attached buffer.
    // The reference element need not to be the valid element of the buffer.
    
    inline void * ReferenceVoid() const
    { return (void *) this->m_buff; }
    // Returns the pointer to the reference element of the attached buffer.
    // The reference element need not to be the valid element of the buffer.
    // The function is intended to be used in printing.
    
    inline DataT * DataStart()
    { return ReferenceElm() + m_range.Min().V(); }
    //: Returns the address of the first element of the buffer.
    
    inline const DataT * DataStart() const
    { return ReferenceElm() + m_range.Min().V(); }
    //: Returns the address of the first element of the buffer.
    
    inline SizeT Size() const
    { return m_range.Size(); }
    // Returns the number of elements of the array.
    
    inline const IndexRangeC & Range() const
    { return m_range; }
    // Returns the usable range of indeces expressed by this object.
    
    inline IndexC IMin() const
    { return m_range.Min(); }
    // Returns the minimum index of the range of this access.
    
    inline IndexC IMax() const
    { return m_range.Max(); }
    // Returns the maximum index of the range of this access.
    
    inline const DataT  & operator[](IntT i) const;
    // Read-only access to the 'i'-th element of the buffer.     
    
    inline DataT & operator[](IntT i);
    // Read-write access  to the 'i'-th element of the buffer. 
    
    inline const DataT  & operator[](IndexC i) const
    { return (*this)[i.V()]; }
    // Read-only access to the 'i'-th element of the buffer.     
    
    inline DataT & operator[](IndexC i)
    { return (*this)[i.V()]; }
    // Read-write access  to the 'i'-th element of the buffer. 
    
    inline const RangeBufferAccessC<DataT> & RAccess(void) const
    { return *this; }
    // Returns this object.
    
    // Logical functions
    // -----------------
        
    inline bool IsEmpty() const
    { return m_range.IsEmpty(); }
    // Returns TRUE if the size of the array is zero.
    
    inline bool Contains(IndexC i) const
    { return m_range.Contains(i); }
    // Returns TRUE if the array contains an item with the index 'i'.
    
    inline 
    bool IsOverlapping(const RangeBufferAccessC<DataT> & acc) const
    { return m_range.IsOverlapping(acc.m_range); }
    // Returns TRUE if this access has an item with the same index as
    // an item of the access 'acc'.
    
    // Modifications of the access
    // ---------------------------
    
    inline 
    const RangeBufferAccessC<DataT> & operator+=(SizeT i);
    // Changes indeces of the access to be 'i' units higher.
    
    inline 
    RangeBufferAccessC<DataT> operator+(SizeT i) const;
    // Creates the new access object with the indeces 'i' units higher
    // than those used in this access object.
  
    inline const IndexRangeC & ShrinkHigh(SizeT k)
    { return m_range.ShrinkHigh(k); }
    //: Changes the number of elements by subtracting the last 'k' elements.
    
    inline void ShiftIndexes(IndexC offset);
    //: All indexes of the items will be changed by 'offset'.
    // The range will be shifted by -offset.
    
    inline void SetSubRange(IndexC newMin, IndexC newMax)
    { m_range.ClipBy(IndexRangeC(newMin, newMax)); }
    //: Constrain the indexs that can be accessed from the array.
    // The range of indexes of this array will be constrained to cover
    // the index range <newMin, newMax> at most.
    
    inline 
    const RangeBufferAccessC<DataT> & Swap(RangeBufferAccessC<DataT> & a);
    // Exchanges the contents of this buffer with buffer 'a'.
    
    inline void Swap(IndexC i1, IndexC i2);
    // Exchanges the contents of elements with indeces 'i1' and 'i2'.
    
    inline void Attach(const RangeBufferAccessC<DataT> & b);
    // Changes this buffer access to have the same access rights as 'b'.
    
    inline void Attach(const BufferAccessC<DataT> & b,
		       const IndexRangeC          & r);
    // Changes this buffer access to have the access rights as 'b' limited
    // by range 'r'. so the first element in 'b' is accessed at 'r.Min()'.
    
    RangeBufferAccessC<DataT> BufferFrom(IndexC first);
    //: Get an access for this buffer starting from the 'first' element to the end of the buffer.
    
    RangeBufferAccessC<DataT> BufferFrom(IndexC first,UIntT len);
    //: Get an access for this buffer starting from the 'first' element for 'len' elements.
    // An error will be generated if the requested buffer isn't contains within this one.
    
    // Modifications of the buffer contents
    // ------------------------------------
    
    void Fill(const DataT & d);
    //: Fill the buffer with the value 'd'.
    
    void Reverse();
    //: Reverse the order of elements in this array in place.
    
    bool operator==(const RangeBufferAccessC<DataT> &ba) const
    { return (this->m_buff == ba.m_buff) && (m_range == ba.m_range); }
    //: Are two accesses the same ?
    
    void CopyFrom(const Slice1dC<DataT> &slice);
    //: Copy slice into this array.
    // slice must have the same length as this buffer. <br>
    // Implementation can be found in Slice1d.hh
  protected:
    
    // Copy
    // ----
    
    RangeBufferAccessC<DataT> Copy(void) const;
    // Returns a physical copy of this access pointing to the physical 
    // copy of the accessed buffer in the range accessible by this access.
    // The new copy is necessary to attach to reference counted buffer
    // or to delete at the end of the life of this object.
    
    IndexRangeC m_range; // Information on the limits of the buffer
  };
  
  /////////////////////////////////////////////////////////////////////////////
  
  //: Wrtie buffer to stream.
  // NB. This size of the buffer is NOT written.
  
  template <class DataT>
  ostream &operator<<(ostream &out,const RangeBufferAccessC<DataT> &dat) {
    const DataT *at = dat.DataStart();
    const DataT *endOfRow = &at[dat.Size()];
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
  
  template <class DataT>
  istream &operator>>(istream &strm,RangeBufferAccessC<DataT> &dat) {
    DataT *at = dat.DataStart();
    DataT *endOfRow = &at[dat.Size()];
    for(;at != endOfRow;at++)
      strm >> *at;
    return strm;
  }
  
  
  //: Wrtie buffer to stream.
  // NB. This size of the buffer is NOT written.
  
  template <class DataT>
  BinOStreamC &operator<<(BinOStreamC &out,const RangeBufferAccessC<DataT> &dat) {
    const DataT *at = dat.DataStart();
    const DataT *endOfRow = &at[dat.Size()];
    if(dat.Size() == 0)
      return out;
    for(;at != endOfRow;at++)
      out << *at;
    return out;
  }
  
  //: Read buffer from stream.
  // NB. The buffer must be pre-allocated.
  
  template <class DataT>
  BinIStreamC &operator>>(BinIStreamC &strm,RangeBufferAccessC<DataT> &dat) {
    DataT *at = dat.DataStart();
    DataT *endOfRow = &at[dat.Size()];
    for(;at != endOfRow;at++)
      strm >> *at;
    return strm;
  }
  
  
  
  template<class DataT> 
  inline RangeBufferAccessC<DataT> RangeBufferAccessC<DataT>::DeepCopy(UIntT levels) const {
    if ( levels == 0) return *this ;
    DataT * newBuf = new DataT[Size()];
    RangeBufferAccessC<DataT> ret (newBuf, m_range);
    
    const DataT *at = DataStart();
    DataT *at2 = ret.DataStart();
    const DataT *endOfRow = &at[m_range.Size()];
    for(;at != endOfRow;at++,at2++)
      *at2 = StdDeepCopy(*at,levels-1) ;
    return ret;
  }
  
  ///////////////////////////////////////////////////////////
  
  
  template <class DataT>
  inline const RangeBufferAccessC<DataT> & RangeBufferAccessC<DataT>::operator=(DataT * bp) {
    ((BufferAccessC<DataT> &) *this) = bp;
    return *this;
  }
  
  template <class DataT>
  inline const DataT &RangeBufferAccessC<DataT>::operator[](IntT i) const {
#if RAVL_CHECK
    if (!Contains(i)) 
      IssueError(__FILE__,__LINE__,"Index  %d  out of  range %d - %d  ",
		 i,Range().Min().V(),Range().Max().V());
#endif
    return BufferAccessC<DataT>::operator[](i);
  }
  
  template <class DataT>
  inline DataT & RangeBufferAccessC<DataT>::operator[](IntT i) {
#if RAVL_CHECK
    if (!Contains(i)) 
      IssueError(__FILE__,__LINE__,"Index  %d  out of  range %d - %d  ",
		 i,Range().Min().V(),Range().Max().V());
#endif
    return BufferAccessC<DataT>::operator[](i);
  }


  template <class DataT>
  inline const RangeBufferAccessC<DataT> &RangeBufferAccessC<DataT>::Swap(RangeBufferAccessC<DataT> & a) {
    DataT *tmp(this->m_buff);
    this->m_buff = a.m_buff;
    a.buff = tmp;
    m_range.Swap(a.m_range);
    return *this;
  }
  
  template <class DataT>
  inline void RangeBufferAccessC<DataT>::Swap(IndexC i1, IndexC i2) {
    DataT d     = (*this)[i1];
    (*this)[i1] = (*this)[i2];
    (*this)[i2] = d;
  }
 
  template <class DataT>
  inline void RangeBufferAccessC<DataT>::Attach(const RangeBufferAccessC<DataT> & b)
  { *this=b; }
  
  template <class DataT>
  inline void  RangeBufferAccessC<DataT>::Attach(const BufferAccessC<DataT> & b,
						 const IndexRangeC &          r) {
    ((BufferAccessC<DataT> &)(*this)) = b - r.Min();
    m_range=r;
  }

  template <class DataT>
  inline const RangeBufferAccessC<DataT> &RangeBufferAccessC<DataT>::operator+=(SizeT i) {
    this->m_buff -= i;
    m_range += i;
    return *this;
  }
  
  template <class DataT>
  inline RangeBufferAccessC<DataT> RangeBufferAccessC<DataT>::operator+(SizeT i) const
  { return RangeBufferAccessC<DataT>(this->m_buff - i, m_range + i); }
  
  template <class DataT>
  inline void RangeBufferAccessC<DataT>::ShiftIndexes(IndexC offset) { 
    ((BufferAccessC<DataT> &) *this) += offset.V(); 
    m_range -= offset.V();
  }

  template <class DataT>
  RangeBufferAccessC<DataT> RangeBufferAccessC<DataT>::Copy(void) const {
    if (IsEmpty()) 
      return RangeBufferAccessC<DataT>();
    DataT * bp = new DataT[Size()];
    RangeBufferAccessC<DataT> b(bp, m_range);
    const DataT *at = DataStart();
    DataT *at2 = b.DataStart();
    const DataT *endOfRow = &at[m_range.Size()];
    for(;at != endOfRow;at++,at2++)
      *at2 = *at;
    return b;
  }
  
  template <class DataT>
  void RangeBufferAccessC<DataT>::Fill(const DataT & d) {
    DataT *at = DataStart();
    DataT *endOfRow = &at[m_range.Size()];
    for(;at != endOfRow;at++)
      *at = d;
  }

  template<class DataT>
  void RangeBufferAccessC<DataT>::Reverse() {
    DataT *at = &((*this)[IMin()]);
    DataT *end = &((*this)[IMax()]);
    DataT tmp;
    for(;at < end;at++,end--) {
      tmp = *at;
      *at = *end;
      *end = tmp;
    }
  }

  template<class DataT>
  RangeBufferAccessC<DataT> RangeBufferAccessC<DataT>::BufferFrom(IndexC first) {
    RavlAssert(Range().Contains(first));
    return RangeBufferAccessC<DataT>(&((*this)[first]),IndexRangeC(first,Range().Max()));
  }
  
  template<class DataT>
  RangeBufferAccessC<DataT> RangeBufferAccessC<DataT>::BufferFrom(IndexC first,UIntT len) {
    RavlAssert(Range().Contains(first) && Range().Contains((first + len) - 1));
    return RangeBufferAccessC<DataT>(&((*this)[first]),IndexRangeC(first,(first+len)-1));
  }
  
  
  //: Save real array to binary stream 
  BinOStreamC &operator<<(BinOStreamC &out,const RangeBufferAccessC<RealT> &img);
  
  //: Load real array image from binary stream 
  BinIStreamC &operator>>(BinIStreamC &in,RangeBufferAccessC<RealT> &img);  
  
  //: Save float array image to binary stream 
  BinOStreamC &operator<<(BinOStreamC &out,const RangeBufferAccessC<FloatT> &img);
  
  //: Load float array image from binary stream 
  BinIStreamC &operator>>(BinIStreamC &in,RangeBufferAccessC<FloatT> &img);  
  
  //: Save byte array to binary stream 
  BinOStreamC &operator<<(BinOStreamC &out,const RangeBufferAccessC<ByteT> &img);
  
  //: Load byte array from binary stream 
  BinIStreamC &operator>>(BinIStreamC &in,RangeBufferAccessC<ByteT> &img);  
  
}
#endif



