// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "PointSet.hh"
#include "Ravl/SArr1Iter.hh"
//! rcsid="$Id$"
//! lib=RavlCarve3D

namespace Ravl3DN {
  
  // Make a copy of the point set.
  
  RCBodyC& PointSetBodyC::Copy() const 
  {
    SArray1dC<VertexC> nverts = m_vertices.Copy();
    SArray1dC<ByteRGBValueC> ncolours = m_colours.Copy();
    return *new PointSetBodyC(nverts,ncolours,m_haveColour);
  }

  Vector3dC PointSetBodyC::Centroid() const
  {
    Vector3dC c(0,0,0);
    if(m_vertices.Size() <= 0)
      return c; // Avoid devision by zero.
    for (SArray1dIterC<VertexC> i(m_vertices); i; i++)
      c += (*i).Position();
    c *= 1.0 / m_vertices.Size();
    return c;
  }
}
