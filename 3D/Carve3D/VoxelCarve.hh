// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL3D_VOXELCARVE_HEADER
#define RAVL3D_VOXELCARVE_HEADER 1
#include "Ravl/3D/VoxelCameraLookup.hh"
//! rcsid="$Id$"
//! lib=RavlCarve3D
//! author="Joel Mitchelson"
//! docentry="Ravl.3D.Carve3D"

namespace Ravl3DN
{
  using namespace RavlN;
  using namespace RavlImageN;

  //! userlevel = Develop
  //: Efficient multi-view voxel carving

  class VoxelCarveBodyC : public RCBodyVC
  {
  public:
    VoxelCarveBodyC(SArray1dC<PinholeCamera0C> camera,
		    UIntT image_rows,
		    UIntT image_cols,
		    VoxelSetC nvoxel)
    {
      // FIXME: have lots more lookups for multi-threads
 
      voxel = nvoxel;
      lookup = SArray1dC<VoxelCameraLookupC> (camera.Size());
      for (UIntT iview = 0; iview < camera.Size(); iview++)
      {
	lookup[iview] = VoxelCameraLookupC(camera[iview],
					   image_rows,
					   image_cols,
					   voxel);
      }
    }

    void Update(SArray1dC< ImageC<ByteT> > image)
    {
      // set mask corresponding to bits from all cameras
      UIntT num_views = lookup.Size();
      ByteT mask = (1 << num_views) - 1;
      voxel.OccupiedThreshold() = mask;

      // empty the voxel space
      voxel.Fill(0);

      // do carving from all views
      RavlAssert(image.Size() == num_views);
      for (UIntT iview = 0; iview < num_views; iview++)
	lookup[iview].Apply(image[iview], 1 << iview);
    }

    UIntT NumViews() const { return lookup.Size(); }
    const PinholeCamera0C& Camera(UIntT iview) const { return lookup[iview].Camera(); }

  protected:
    VoxelSetC voxel;
    SArray1dC< VoxelCameraLookupC > lookup;
  };

  //! userlevel = Normal
  //: Efficient multi-view voxel carving
  // Carves volume cells (voxels) given segmented images
  // from 1 or more calibrated cameras. A lookup table
  // is used for speed.

  class VoxelCarveC : public RCHandleC<VoxelCarveBodyC>
  {
  public:
    VoxelCarveC()
    {
    }
    //: default constructor

    VoxelCarveC(SArray1dC<PinholeCamera0C> camera,
		    UIntT image_rows,
		    UIntT image_cols,
		    VoxelSetC voxel)
      : RCHandleC<VoxelCarveBodyC>(*new VoxelCarveBodyC(camera,
							image_rows,
							image_cols,
							voxel))
    {
    }
    //: Lookup creation constructor
    // Prepare lookups for the set of cameras specified by <i>camera</i>,
    // using input images of <i>image_rows</i> x <i>image_cols</i>, for carving
    // voxels in the given <i>voxel</i> class. Expect this to take several seconds
    // or even minutes depending on the size of the voxel set.

  public:
    void Update(SArray1dC< ImageC<ByteT> > image)
      { Body().Update(image); }
    //: Apply lookups to the given array of images

    UIntT NumViews() const { return Body().NumViews(); }
    //: Get number of camera views for which lookups are stored

    const PinholeCamera0C& Camera(UIntT iview) const { return Body().Camera(iview); }
    //: Get camera parameters for the ith view
  };
}


#endif
