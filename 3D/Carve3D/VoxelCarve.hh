// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/3D/VoxelCameraLookup.hh"
#include "Ravl/3D/PointSet.hh"
//! rcsid="$Id$"
//! lib=RavlCarve3D

namespace Ravl3DN
{
  using namespace RavlN;
  using namespace RavlImageN;

  //!userlevel:Develop
  //:Efficient multi-view voxel carving

  class VoxelCarveBodyC : public RCBodyVC
  {
  public:
    VoxelCarveBodyC(Pinhole0ArrayC camera,
		    UIntT image_rows,
		    UIntT image_cols,
		    VoxelSetC nvoxel)
    {
      // FIXME: have lots more lookups for multi-threads
 
      voxel = nvoxel;
      lookup = Array1dC<VoxelCameraLookupC> (camera.Size());
      for (UIntT iview = 0; iview < camera.Size(); iview++)
      {
	lookup[iview] = VoxelCameraLookupC(camera[iview],
					   image_rows,
					   image_cols,
					   voxel);
      }
    }

    void Update(Array1dC< ImageC<ByteT> > image)
    {
      voxel.Fill(0);
      RavlAssert(image.Size() == lookup.Size());
      for (UIntT iview = 0; iview < lookup.Size(); iview++)
	lookup[iview].Apply(image[iview], 1 << iview);
    }

    PointSetC PointSet();
    UIntT NumViews() const { return lookup.Size(); }
    const PinholeCamera0C& Camera(UIntT iview) const { return lookup[iview].Camera(); }

  protected:
    VoxelSetC voxel;
    Array1dC< VoxelCameraLookupC > lookup;
  };

  //!userlevel:Normal
  //:Efficient multi-view voxel carving
  // Carves volume cells (voxels) given segmented images
  // from 1 or more calibrated cameras. A lookup table
  // is used for speed

  class VoxelCarveC : public RCHandleC<VoxelCarveBodyC>
  {
  public:
    VoxelCarveC()
    {
    }
    //: default constructor

    VoxelCarveC(Pinhole0ArrayC camera,
		    UIntT image_rows,
		    UIntT image_cols,
		    VoxelSetC voxel)
      : RCHandleC<VoxelCarveBodyC>(*new VoxelCarveBodyC(camera,
							image_rows,
							image_cols,
							voxel))
    {
    }
    //:Lookup creation constructor
    // Prepare lookups for the set of cameras specified by camera,
    // using input images of image_rows x image_cols, for carving
    // voxels in the given voxel class

  public:
    void Update(Array1dC< ImageC<ByteT> > image)
      { Body().Update(image); }
    //:Apply lookups to the given array of images

    PointSetC PointSet()
      { return Body().PointSet(); }
    //:Compute the set of points occupied by the current carved voxels
    // Use after a call to Update(...)

    UIntT NumViews() const { return Body().NumViews(); }
    //:Get number of camera views for which lookups are stored

    const PinholeCamera0C& Camera(UIntT iview) const { return Body().Camera(iview); }
    //:Get camera parameters for the ith view
  };
}

