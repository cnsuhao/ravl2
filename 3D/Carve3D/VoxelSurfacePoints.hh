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
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using RavlImageN::ImageC;
  using RavlImageN::ByteRGBAValueC;
#endif

  //! userlevel=Normal
  //! AutoLink=on

  PointSetC VoxelSurfacePoints(const VoxelSetC vox,
			       const SArray1dC< ImageC<ByteRGBAValueC> > image,
			       const SArray1dC<PinholeCamera0C>& camera,
			       const Vector3dC& viewpoint);
  //:Compute set of point locations and normals on voxel set surface
  // Returns the set of point locations as a <a href="Ravl3DN.PointSetC.html">PointSetC</a>.
  //!param: vox - the voxel set - a <a href="Ravl3DN.VoxelSetC.html">VoxelSetC</a> object
  //!param: image - array of colour images used to find the colour of each surface point
  //!param: camera - camera parameters corresponding to each image
  //!param: viewpoint - the viewpoint from which to optimise colours

  PointSetC VoxelSurfacePoints(const VoxelSetC vox);
  //: Compute set of point locations/normals/colours on voxel set surface
  // Returns the set of point locations as a <a href="Ravl3DN.PointSetC.html">PointSetC</a>
  //!param: vox - the voxel set - a <a href="Ravl3DN.VoxelSetC.html">VoxelSetC</a> object
}

#endif
