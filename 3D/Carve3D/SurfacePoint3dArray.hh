// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=Ravl3D
//! file="Ravl/3D/Carve3D/SurfacePoint3dArray.hh"

#ifndef RAVL3D_SURFACE_POINT_3D_ARRAY_HEADER
#define RAVL3D_SURFACE_POINT_3D_ARRAY_HEADER 1

#include "Ravl/SArray1d.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Vector3d.hh"

namespace Ravl3DN
{
  using namespace RavlN;
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using RavlN::RCBodyC;
  using RavlN::SArray1dC;
  using RavlN::SArray1dIterC;
  using RavlN::UIntT;
  using RavlN::RCHandleC;
  using RavlN::Vector3dC;
#endif 
  
  //! userlevel=Normal
  //: Array of 3D vertices and attributes
  //  The following can render certain types of surface point arrays:
  //    Ravl-GUI-3D-DSurfacePointVertexArrayC
  //    Ravl-GUI-3D-DSurfacePointVertexByteRGBArrayC
  
  template<class VertexTypeC> class SurfacePoint3dArrayC : public SArray1dC<VertexTypeC>
  {
  public:
    SurfacePoint3dArrayC()
    {
    }
    //: Default constructor - makes invalid surface point array

    SurfacePoint3dArrayC(BinIStreamC &is);
    //: Stream constructor.

    SurfacePoint3dArrayC(UIntT numPoints) :
      SArray1dC<VertexTypeC> (numPoints)
    { 
    }
    //:Construct a surface point array with a number of points.
    
  public:

    void Centroid(Vector3dC& c) const;
    //: Centroid of point locations

    Vector3dC Centroid() const
    { 
      Vector3dC c;
      Centroid(c);
      return c;
    }
    //: Centroid of point locations (return value)

  };
}

#endif
