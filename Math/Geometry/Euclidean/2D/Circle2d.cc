// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////
//! date="25/2/1997"
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/Circle2d.hh"
#include "Ravl/LineABC2d.hh"
#include "Ravl/Assert.hh"

namespace RavlN {

  inline LineABC2dC Circle2dC::Bisector(const Point2dC &p1,const Point2dC &p2) {
    Vector2dC Norm = p1 - p2;
    return LineABC2dC(Norm,(p1 + p2)/2);
  }
  
  // Fit a circle through 3 points.
  
  bool Circle2dC::Fit(Point2dC p0,Point2dC p1,Point2dC p2) {
    if(!Bisector(p0,p1).Intersection(Bisector(p1,p2),centre))
      return false; // Points are collinear.
    radius = centre.EuclidDistance(p1);
    return true;
  }
}
