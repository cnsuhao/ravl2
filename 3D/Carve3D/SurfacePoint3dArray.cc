// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Ravl3D

#include "Ravl/3D/SurfacePoint3dArray.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/BinStream.hh"

namespace Ravl3DN {

  using namespace RavlN;

#if RAVL_VISUALCPP_NAMESPACE_BUG
  using namespace RavlN;
#endif
  
  // stream constructor
  template<class VertexTypeC> SurfacePoint3dArrayC<VertexTypeC>::SurfacePoint3dArrayC(BinIStreamC &is) 
  {
    is >> *static_cast< SArray1dC<VertexTypeC>* > (this);
  }

  // centroid of 3d points
  template<class VertexTypeC> void SurfacePoint3dArrayC<VertexTypeC>::Centroid(Vector3dC& c) const
  {
    c[0] = c[1] = c[2] = 0.0;
    if(Size())
    {
      for (SArray1dIterC<VertexTypeC> i(*this); i; i++)
	c += (*i).Position();
      c *= 1.0 / Size();
    }
  }
   
}
