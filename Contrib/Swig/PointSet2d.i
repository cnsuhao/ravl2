// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%include "Ravl/Swig/Types.i"
%include "Ravl/Swig/Point2d.i"
%include "Ravl/Swig/RealRange2d.i"

%{
#ifdef SWIGPERL
#undef Copy
#endif

#include "Ravl/PointSet2d.hh"

#ifdef SWIGPERL
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
#endif
%}

namespace RavlN
{
  class PointSet2dC :
    public DListC<Point2dC>
  {
  public:
    PointSet2dC();

    Point2dC Centroid() const;
    // Returns the centroid (mean) of the points

    RealRange2dC BoundingRectangle() const;
    //: Compute the bounding rectangle for the point set.
  };
}

