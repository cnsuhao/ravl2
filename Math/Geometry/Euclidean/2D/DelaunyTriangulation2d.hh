// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DELAUNYTRIANGULATION2D_HEADER
#define RAVL_DELAUNYTRIANGULATION2D_HEADER 1
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/HEMesh2d.hh"

namespace RavlN {
  
  HEMesh2dC DelaunyTriangulation(const SArray1dC<Point2dC> &points);
  //: Create a delauny triangulation of the given set of points.
  
  bool IsDelaunyTriangulation(const HEMesh2dC &mesh);
  //: Test if mesh is a delauny triangulation. 
}

#endif
