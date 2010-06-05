// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: PointSet.cc 1959 2002-10-30 14:43:09Z vap-james $"
//! lib=Ravl3D
//! file="Ravl/3D/Carve3D/PointSet.cc"

#include "Ravl/3D/PointSet.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/BinStream.hh"

namespace Ravl3DN {
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using namespace RavlN;
  using namespace RavlImageN;
#endif
  
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

  // Prints the point set into the stream
  BinOStreamC & operator<<(BinOStreamC & os, const PointSetC& oPointSet)
  {
    os << oPointSet.HaveColour();
    os << oPointSet.Vertices();
    if (oPointSet.HaveColour()) os << oPointSet.Colours();
    return os;
  }
  
  // Stream constructor.  
  PointSetBodyC::PointSetBodyC(BinIStreamC &is) 
  {
    is >> m_haveColour;
    is >> m_vertices;
    if (m_haveColour) is >> m_colours;
  }
  

  // Assigns the values into the point set 
  BinIStreamC & operator>>(BinIStreamC& is, PointSetC& oPointSet)
  {
    oPointSet = PointSetC(is);
    return is;
  }

}
