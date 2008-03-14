// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%include "Ravl/Swig/Types.i"
%include "Ravl/Swig/RealRange.i"

%{
#ifdef SWIGPERL
#undef Copy
#endif

#include "Ravl/RealRange2d.hh"

#ifdef SWIGPERL
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
#endif
%}

namespace RavlN
{
  class RealRange2dC
  {
  public:
    RealRange2dC()
    {}
    //: Default constructor.

    RealRange2dC(RealT rowNumber, RealT colNumber);
    //: Constructor.

    RealRange2dC(const RealRangeC &rowRange, const RealRangeC &colRange);
    //: Constructor.

    RealRange2dC(const RealRange2dC &range);
    //: Constructor.

    RealRange2dC(RealT minRow, RealT maxRow, RealT minCol, RealT maxCol);
    //: Create rectangle from indvidual values.

    RealT TRow() const;
    //: Returns the top row index.

    RealT LCol() const;
    //: Returns the left side column index.

    RealT BRow() const;
    //: Returns the bottom row index.

    RealT RCol() const;
    //: Returns the right side column index.

    RealT TRow();
    //: Returns the top row index.

    RealT LCol();
    //: Returns the left side column index.

    RealT BRow();
    //: Returns the bottom row index.

    RealT RCol();
    //: Returns the right side column index.

    RealT Rows() const;
    //: The number of rows in the rectangle.

    RealT Cols() const;
    //: The number of rows in the rectangle.

    RealT Area() const;
    //: Returns the area of the image rectangle expressed in number of indexs.

    RealRange2dC Dilate() const;
    //: Returns a new rectangle one index larger on each side.

    RealRange2dC Erode() const;
    //: Returns an rectangle with each side 1 index closer to the center.

    RealRange2dC Expand(RealT n);
    //: Returns an rectangle expanded by 'n' indexs on each side.

    RealRange2dC Shrink(RealT n) const;
    //: Returns a new rectangle which has layer of the width of 'n' indexs
    //: removed.

    RealRange2dC & ClipBy(const RealRange2dC & r);
    //: This index range is clipped to contain at most the index range 'r'.

    bool Contains(const RealRange2dC & oth) const;
    //: Returns true if this range contains the subrange 'oth'.

    RealRangeC RowRange();
    //: Access row range.

    RealRangeC ColRange();
    //: Access col range.

    RealRangeC Range1();
    //: Access row range.

    RealRangeC Range2();
    //: Access col range.

    void Involve(const RealRange2dC &subrectangle);
    //: Ensures this rectangle contains given sub rectangle.
    // This method checks and changes, if necessary, the 2 dimensional range
    // to contain the 'subrectangle'.

    bool IsValid() const;
    //: Returns true if this rectangle contains at least one index.

    bool operator==(const RealRange2dC &oth) const
    { return oth.Range1() == Range1() && oth.Range2() == Range2(); }
    //: Are two ranges equal ?

    bool operator!=(const RealRange2dC &oth) const
    { return oth.Range1() != Range1() || oth.Range2() != Range2(); }
    //: Are two ranges unequal ?

    bool IsOverlapping(const RealRange2dC & r) const;
    //: Returns true if this range contains a common area with
    //: the range 'r'.
  };
}

