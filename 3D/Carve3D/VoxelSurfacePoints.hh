// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL3D_VOXELSURFACEPOINTS_HEADER
#define RAVL3D_VOXELSURFACEPOINTS_HEADER 1
//! docentry="Ravl.3D.Carve3D"
//! author="Joel Mitchelson"
//! userlevel=Normal
//! rcsid="$Id$"
//! lib=RavlCarve3D

#include "Ravl/3D/VoxelSet.hh"
#include "Ravl/3D/PointSet.hh"
#include "Ravl/3D/PinholeCamera0.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBAValue.hh"
#include "Ravl/Image/ByteRGBValue.hh"


namespace Ravl3DN
{
  using namespace RavlN;
  using namespace RavlImageN;

  PointSetC VoxelSurfacePoints(const VoxelSetC vox,
			       const SArray1dC< ImageC<ByteRGBAValueC> > image,
			       const Pinhole0ArrayC& camera,
			       const Vector3dC& viewpoint);
  //:Compute set of point locations and normals on voxel set surface

  PointSetC VoxelSurfacePoints(const VoxelSetC vox);
  //: Compute set of point locations/normals/colours on the current volume surface
  // image is used to find the colour of each surface point
}

#endif
