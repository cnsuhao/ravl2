// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Euclidean/2D/Point2d.cc"

#include "Ravl/Point2d.hh"

namespace RavlN {
   RealT Point2dC::Area2(const Point2dC & second, const Point2dC & third) const {
      // Area of tringle (*this, second, third) is equal to the area
      // of the tringle which the first point represents the origin
      // of the coordinate system. In fact the points 'aa' and 'bb'
      // represents two vectors and the computed area is equal to
      // the size of the cross product of these two vectors.
      Point2dC aa(second - *this);   // O'Rourke 1.2
      Point2dC bb(third  - *this);
      return aa[0]*bb[1] - aa[1]*bb[0];
   }

}
