// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_POLYLINE2D_HEADER
#define RAVL_POLYLINE2D_HEADER 1
//! file="Ravl/Math/Geometry/Euclidean/2D/Polygon2d.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Charles Galambos"
//! date="16/2/2006"
//! docentry="Ravl.API.Math.Geometry.2D"

#include "Ravl/PointSet2d.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: A 2d curve consisting of straigh line segments.
  
  class PolyLine2dC 
    : public PointSet2dC
  {
  public:
    PolyLine2dC() {}
    // Empty list of points.
    
    PolyLine2dC(const DListC<Point2dC>& points)
      : PointSet2dC(points)
    {}
    // Construct from list of points
    
    bool IsSelfIntersecting() const;
    //: Returns true if the polygon is self intersecting, ie do any sides cross
    
  };
}


#endif
