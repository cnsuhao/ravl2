// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_INDEXRANGE1D_HH
#define RAVL_INDEXRANGE1D_HH
//////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Base/IndexRange1d.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Radek Marik"
//! docentry="Ravl.Core.Indexing"
//! rcsid="$Id$"
//! date="2.1.1997"

#include "Ravl/Index.hh"
#include <iostream.h>

namespace RavlN {
  class BinIStreamC;
  class BinOStreamC;

  ////////////////// IndexRangeC ////////////////////////////////////
  
  //: 1D index range of array
  // The class IndexRangeC is a representation of an interval of one
  // dimensional index.
  
  class IndexRangeC {
  public:
    //:----------------------------------------------
    // Constructors, copy, assigment, and destructor.
    
    inline IndexRangeC(SizeT dim = 0)    
      : minI(0),
	maxI(dim-1)
    {}
    //: Creates the index range <0, dim-1>.
    
    inline IndexRangeC(IndexC dim)
      : minI(0),
	maxI(dim-1)
    {}
    //: Creates the index range <0, dim-1>.
    
    inline IndexRangeC(IndexC minIndex, IndexC maxIndex)
      : minI(minIndex),
	maxI(maxIndex)
    {}
    //: Creates the index range <minIndex, maxIndex>.
    
    inline IndexRangeC(istream & s)
    { s >> minI >> maxI; }
    //: Creates the index range from the input stream.
    
    //:---------------------------------
    //: Access to the object information.
    
    inline SizeT Size() const
    { return (maxI-minI+1).V(); }
    //: Returns the number of elements in the range.
    
    inline const IndexRangeC & Range() const
    { return *this; }
    //: Returns this object.
    
    inline const IndexC & Min()  const
    { return minI; }
    //: Returns the minimum index of the range.
    
    inline const IndexC & Max()  const
    { return maxI; }
    //: Returns the maximum index of the range.
    
    inline IndexC & Min()
    { return minI; }
    //: Returns the minimum index of the range.
    
    inline IndexC & Max()
    { return maxI; }
    //: Returns the maximum index of the range.
    
    inline IndexC Center() const
    { return (Min() + Max() + 1)/2; }
    //: Returns the index in the middle of the range, eg. (Max()+Min()+1)/2.
    
    inline IndexC CenterD() const
    { return (Min() + Max())/2; }
    //: Returns the index previous the middle of the range, eg. (Max()+Min())/2.
    
    inline IndexC Percentage(const RealT p) const
    { return IntT((Max() - Min()) * p/100.0 + Min()+0.5); }
    //: Returns the index which is in the 'p' % of the whole range.
    
    //:-------------------
    //: Logical operations.
    
    inline bool IsEmpty() const
    { return Min() > Max(); }
    //: Returns TRUE if the minimum limit is bigger than the maximum limit. 

    inline bool IsValid() const
    { return Min() > Max(); }
    //: Returns TRUE if the minimum limit is bigger than the maximum limit. 
    
    inline bool Contains(IndexC i) const
    { return (Min() <= i) && (i <= Max()); }
    //: Returns TRUE if this range contains the index 'i'.
    
    inline bool Contains(const IndexRangeC & range) const
    { return Contains(range.Min()) && Contains(range.Max()); }
    //: Returns TRUE if this range contains the subrange 'range'.
    
    inline bool operator==(const IndexRangeC & range) const
    { return (Min() == range.Min()) && (Max() == range.Max()); }
    //: Returns TRUE if both index ranges have the same limits.
    
    inline bool operator!=(const IndexRangeC & range) const
    { return (Min() != range.Min()) || (Max() != range.Max()); }
    //: Returns TRUE if both the ranges have different limits.
    
    bool In(const IndexRangeC & range) const;
    //: Returns TRUE if this range is inside of the 'range'.
    
    inline bool IsOverlapping(const IndexRangeC & r) const;
    //: Returns TRUE if this range contains at least one common index with 
    //: the range 'r'.
    
    //:-------------------
    //: Special operations.
    
    inline IndexRangeC &operator++()
    { Min()++; Max()++; return *this; }
    //: Move both the max and min of the range along 1.
    
    inline IndexRangeC &operator--()
    { Min()--; Max()--; return *this; }
    //: Move both the max and min of the range back 1.
    
    inline const IndexRangeC & operator+=(IndexC i);
    //: Both minimum and maximum limits are shifted by adding the offset 'i'.
    
    inline const IndexRangeC & operator-=(IndexC i);
    //: Both minimum and maximum limits are shifted by subtracting the offset 'i'.
    
    inline IndexRangeC operator+(IndexC i) const
    { return IndexRangeC(Min() + i,Max() + i); }
    //: Create a new IndexRangeC with minimum and maximum limits shifted by adding the offset 'i'.
    
    inline IndexRangeC operator-(IndexC i) const
    { return IndexRangeC(Min() - i,Max() - i); }
    //: Create a new IndexRangeC with minimum and maximum limits shifted by subtracting the offset 'i'.
    
    inline IndexRangeC & ClipBy(const IndexRangeC & r);
    //: This index range is clipped to contain at most the index range 'r'.
    
    inline IndexRangeC FirstHalf() const
    { return IndexRangeC(Min(),Center()); }
    //: Returns the index range < Min(), (Max()+Min()+1)/2 >.
    
    inline IndexRangeC FirstHalfD() const
    { return IndexRangeC(Min(),CenterD()); }
    //: Returns the index range < Min(), (Max()+Min())/2 >.
    
    inline IndexRangeC Enlarge(IndexC f) const
    { return IndexRangeC(Min(), Min() + Size()*f - 1); }
    //: Returns the index range whose number of elements is enlarged by
    //: the factor 'f'. The upper limits is changed.
    
    inline IndexRangeC Expand(IndexC n) const
    { return IndexRangeC(minI - n,maxI + n); }
    //: Returns the range extended by adding 'n' items on both limits of
    //: this range. 
    
    inline IndexRangeC Shrink(IndexC n) const
    { return IndexRangeC(minI + n,maxI - n); }
    //: Returns the range extended by adding 'n' items on both limits of
    //: this range. 
    
    inline IndexRangeC & ShrinkHigh(IndexC n);
    //: Returns the range shrinked by removing of the 
    //: last 'n' items on both limits of this range. 
    
    inline IndexRangeC & Swap(IndexRangeC & r);
    //: Exchanges the contents of this range and range 'r'. The function
    //: returns this range. 

    const IndexRangeC &Involve(IndexC i) { 
      if(minI > i) minI = i;
      if(maxI < i) maxI = i;
      return *this;
    }
    //: Modify this range to ensure index i is contained within it.

    const IndexRangeC &Involve(const IndexRangeC &subRange) { 
      Involve(subRange.Min());
      Involve(subRange.Max());
      return *this;
    }
    //: Modify this range to ensure subRange is contained within it.
    
  private:
    
    // Object representation.
    // ----------------------
    
    IndexC minI; // Minimum index.
    IndexC maxI; // Maximum index.
    
    friend istream & operator>>(istream & s, IndexRangeC & range);
  };
  
  bool IsInside(IndexC i, const IndexRangeC & r);
  // Returns TRUE if the index 'i' is inside the index range 'r'.
  
  istream & operator>>(istream & s, IndexRangeC & r);
  // Read information from the intput stream 's' and sets the index range
  // according obtained data.
  
  ostream & operator<<(ostream & s, const IndexRangeC & r);
  // Saves the index range 'r' into the output stream 's'.
  
  BinOStreamC &operator<<(BinOStreamC &s,const IndexRangeC &ir);  
  BinIStreamC &operator>>(BinIStreamC &s,IndexRangeC &ir);
  
  inline bool IndexRangeC::IsOverlapping(const IndexRangeC & r) const {
    return (!IsEmpty() && !r.IsEmpty()) 
      && (((Min() <= r.Max()) && (r.Min() <= Max()))
	  || ((r.Min() <= Max()) && (Min() <= r.Max())));
  }
  
  inline const IndexRangeC & IndexRangeC::operator+=(IndexC i) {
    Min() += i;
    Max() += i;
    return *this;
  }

  inline const IndexRangeC &IndexRangeC::operator-=(IndexC i) {
    Min() -= i;
    Max() -= i;
    return *this;
  }
  
  inline IndexRangeC &IndexRangeC::ClipBy(const IndexRangeC & r) {
    if (Min() < r.Min()) Min() = r.Min();
    if (Max() > r.Max()) Max() = r.Max();
    return *this;
  }
  
  inline IndexRangeC &IndexRangeC::ShrinkHigh(IndexC n) {
    Max() -= n;
    return *this;
  }
  
  inline IndexRangeC &IndexRangeC::Swap(IndexRangeC & r) {
    const IndexRangeC tmp = *this;
    *this = r;
    r = tmp;
    return *this;
  }
  
}
#endif
