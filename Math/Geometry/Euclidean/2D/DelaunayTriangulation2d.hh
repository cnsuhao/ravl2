// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DELAUNAYTRIANGULATION2D_HEADER
#define RAVL_DELAUNAYTRIANGULATION2D_HEADER 1
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlMath
//! userlevel=Normal
//! docentry="Ravl.Math.Geometry.2D"
//! file="Ravl/Math/Geometry/Euclidean/2D/DelaunayTriangulation2d.hh"

#include "Ravl/HEMesh2d.hh"

namespace RavlN {
  
  HEMesh2dC DelaunayTriangulation(const Array1dC<Point2dC> &points);
  //: Create a delaunay triangulation of the given set of points.
  
  bool IsDelaunayTriangulation(const HEMesh2dC &mesh);
  //: Test if mesh is a delaunay triangulation. 
}

#endif
