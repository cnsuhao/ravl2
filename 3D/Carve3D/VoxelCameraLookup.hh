// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL3D_VOXEL_CAMERA_LOOKUP_HH_
#define RAVL3D_VOXEL_CAMERA_LOOKUP_HH_
//! rcsid="$Id$"
//! lib=RavlCarve3D
//! author="Joel Mitchelson"
//! docentry="Ravl.3D.Carve3D"

#include "Ravl/3D/PinholeCamera0.hh"
#include "Ravl/3D/VoxelSet.hh"
#include "Ravl/Image/Image.hh"

namespace Ravl3DN
{
  using namespace RavlN;
  using namespace RavlImageN;
  
  //! userlevel=Develop
  //:Lookup for fast mapping from image pixels to voxels

  class VoxelCameraLookupBodyC : public RCBodyVC
  {
  public:
    VoxelCameraLookupBodyC(const PinholeCamera0C& ncamera,
			   UIntT image_rows,
			   UIntT image_cols,
			   const VoxelSetC &nvoxel);
    
  public:
    const PinholeCamera0C& Camera() const { return camera; }
    void Apply(const ImageC<ByteT>& image, ByteT mask);

  protected:
    bool ClipRay(const Vector3dC& oWorldOrigin, const Vector3dC& oWorldDirection,
          Vector3dC& oVoxelStart, Vector3dC& oVoxelEnd);
    //:Clip a ray against the voxel set

    void SetRayLookup(const Vector3dC& oVoxelStart, const Vector3dC& oVoxelEnd,
          SArray1dC<ByteT*>& pixelLookup);
    //:Voxelize a ray and fill the voxels in the lookup for the pixel corresponding to a ray

  protected:
    const PinholeCamera0C camera;
    VoxelSetC voxel;
    Array2dC< SArray1dC<ByteT*> > lookup;
  };

  //! userlevel=Develop
  //:Lookup for fast mapping from image pixels to voxels

  class VoxelCameraLookupC : public RCHandleC<VoxelCameraLookupBodyC>
  {
  public:
    VoxelCameraLookupC()
    {
    }
    //:Default constructor

    VoxelCameraLookupC(const PinholeCamera0C& camera,
		       UIntT image_rows,
		       UIntT image_cols,
		       const VoxelSetC &voxel) :
      RCHandleC<VoxelCameraLookupBodyC>(*new VoxelCameraLookupBodyC(camera,
								    image_rows,
								    image_cols,
								    voxel))
    {}
    //:Lookup constuctor
    // Makes lookup for calibrated camera with specified parameters,
    // Image of size image_rows x image_cols
    // Using the specified voxel set

    void Apply(const ImageC<ByteT>& image, ByteT mask)
      { Body().Apply(image, mask); }
    //:Apply the lookup to a segmented image

    const PinholeCamera0C& Camera() const
      { return Body().Camera(); }
    //:Get the camera parameters used to construct the lookup

  protected:
    VoxelCameraLookupC(VoxelCameraLookupBodyC& body)
      : RCHandleC<VoxelCameraLookupBodyC>(body)
    {
    }
  };

}

#endif
