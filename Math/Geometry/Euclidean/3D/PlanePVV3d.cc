// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Euclidean/3D/PlanePVV3d.cc"

#include "Ravl/PlanePVV3d.hh"
#include "Ravl/PlaneABCD3d.hh"
#include "Ravl/Stream.hh"

namespace RavlN {

  PlaneABCD3dC PlanePVV3dC::PlaneABCD3d() const
  { return PlaneABCD3dC(Normal(), Point()); }
  
  ostream & operator<<(ostream & outS, const PlanePVV3dC & plane) {
    const Point3dC  & p  = plane.Point();
    const Vector3dC & v1 = plane.Vector1();
    const Vector3dC & v2 = plane.Vector2();
    outS << p << ' ' << v1 << ' ' << v2;
    return(outS);
  }
  
  istream & operator>>(istream & inS, PlanePVV3dC & plane) {
    Point3dC  & p  = plane.Point();
    Vector3dC & v1 = plane.Vector1();
    Vector3dC & v2 = plane.Vector2();
    inS >> p >> v1 >> v2;
    return(inS);
  }
  
}



