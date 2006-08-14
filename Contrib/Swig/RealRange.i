// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%include "Ravl/Swig/Types.i"
%include "Ravl/Swig/IndexRange2d.i"

%{
#include "Ravl/RealRange1d.hh"
%}

namespace RavlN
{
  class RealRangeC
  {
  public:	
    RealRangeC(RealT size = 0);
    //: Creates the index range <0, dim-1>.
    
    RealRangeC(RealT minReal, RealT maxReal);
    //: Creates the index range <minReal, maxReal>.
    
    RealT Size() const;
    //: Returns the number of elements in the range.
    
    const RealRangeC &Range() const;
    //: Returns this object.
    
    const RealT &Min() const;
    //: Returns the minimum index of the range.
    
    const RealT &Max() const;
    //: Returns the maximum index of the range.
    
    RealT &Min();
    //: Returns the minimum index of the range.
    
    RealT &Max();
    //: Returns the maximum index of the range.
    
    RealT Center() const;
    //: Returns the index in the middle of the range, eg. (Max()+Min())/2.
    
    RealT CenterD() const;
    //: Returns the index previous the middle of the range, eg. (Max()+Min())/2.

    RealT Percentage(RealT p) const;
    //: Returns the index which is in the 'p' % of the whole range.
    
    bool IsEmpty() const;
    //: Returns true if the minimum limit is bigger than the maximum limit. 
    
    bool IsValid() const;
    //: Returns true if the minimum limit is bigger than the maximum limit. 
    
    bool Contains(RealT i) const;
    //: Returns true if this range contains the index 'i'.
    
    bool Contains(const RealRangeC & range) const;
    //: Returns true if this range contains the subrange 'range'.
    
    bool operator==(const RealRangeC & range) const;
    //: Returns true if both index ranges have the same limits.
    
    bool operator!=(const RealRangeC & range) const;
    //: Returns true if both the ranges have different limits.
    
    bool In(const RealRangeC & range) const;
    //: Returns true if this range is inside of the 'range'.
    
    bool IsOverlapping(const RealRangeC & r) const;
    //: Returns true if this range contains at least one common index with 
    //: the range 'r'.
    
    const RealRangeC &SetOrigin(RealT position);
    //: Set the origin of the range to 'position'.
    // Returns a reference to this range.
    
    const RealRangeC & operator+=(RealT i);
    //: Both minimum and maximum limits are shifted by adding the offset 'i'.
    // Returns a reference to this range.
    
    const RealRangeC & operator-=(RealT i);
    //: Both minimum and maximum limits are shifted by subtracting the offset 'i'.
    // Returns a reference to this range.
    
    RealRangeC operator+(RealT i) const;
    //: Create a new RealRangeC with minimum and maximum limits shifted by adding the offset 'i'.
    
    RealRangeC operator-(RealT i) const;
    //: Create a new RealRangeC with minimum and maximum limits shifted by subtracting the offset 'i'.
    
    RealRangeC & ClipBy(const RealRangeC & r);
    //: This index range is clipped to contain at most the index range 'r'.

    RealT Clip(const RealT & r);
    //: The value 'r' is clipped to be within this range.
    
    RealRangeC FirstHalf() const;
    //: Returns the index range < Min(), (Max()+Min())/2 >.
    
    RealRangeC FirstHalfD() const;
    //: Returns the index range < Min(), (Max()+Min())/2 >.
    
    RealRangeC Enlarge(RealT f) const;
    //: Returns the index range whose number of elements is enlarged by
    //: the factor 'f'. The upper limits is changed.
    
    RealRangeC Expand(RealT n) const;
    //: Returns the range extended by adding 'n' items on both limits of
    //: this range. 
    
    RealRangeC Shrink(RealT n) const;
    //: Returns the range extended by adding 'n' items on both limits of
    //: this range. 
    
    RealRangeC & ShrinkHigh(RealT n);
    //: Returns the range shrinked by removing of the 
    //: last 'n' items on both limits of this range. 
    
    RealRangeC & Swap(RealRangeC & r);
    //: Exchanges the contents of this range and range 'r'. The function
    //: returns this range. 

    const RealRangeC &Involve(RealT i);
    //: Modify this range to ensure index i is contained within it.

    const RealRangeC &Involve(const RealRangeC &subRange);
    //: Modify this range to ensure subRange is contained within it.
  };
}

