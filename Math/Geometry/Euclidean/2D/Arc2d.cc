// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! date="10/3/1997"
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/Arc2d.hh"
#include "Ravl/Angle.hh"

namespace RavlN {
  
  bool Arc2dC::FitLSQ(const SArray1dC<Point2dC> &points,RealT &residual) {
    if(!Circle2dC::FitLSQ(points,residual))
      return false;
    // This may not be right.
    
    AngleC mid = Angle(points[1]);
    ends[0] = Angle(points[0]);
    ends[1] = Angle(points[points.Size()-1]);
    if(!mid.IsBetween(ends[0],ends[1]))
      Swap(ends[0],ends[1]);
    return true;
  }
  //: Fit points to a circle.
  // 'residual' is from the least squares fit and can be used to assess the quality of the
  // fit. Assumes the points are ordered around the arc.
  // Returns false if fit failed.
}
