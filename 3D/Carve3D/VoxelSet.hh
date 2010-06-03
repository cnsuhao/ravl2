// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL3D_VOXEL_SET_HH_
#define RAVL3D_VOXEL_SET_HH_
//! rcsid="$Id: VoxelSet.hh 5240 2005-12-06 17:16:50Z plugger $"
//! lib=Ravl3D
//! author="Joel Mitchelson"
//! docentry="Ravl.API.3D.Carve3D"
//! file="Ravl/3D/Carve3D/VoxelSet.hh"

#include "Ravl/Vector3d.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Array3d.hh"


namespace Ravl3DN
{
  using namespace RavlN;
  class VoxelSetC;

  //! userlevel=Develop
  //: A cuboid of volume cells (voxels) in 3D space

  class VoxelSetBodyC : public RCBodyVC
  {
  public:
    VoxelSetBodyC(const Matrix3dC& nR,
		  const Vector3dC& nt,
		  RealT nvoxel_size,
		  UIntT cube_side_num_voxels,
		  ByteT noccupied_threshold) :
      vox(cube_side_num_voxels,
	  cube_side_num_voxels,
	  cube_side_num_voxels),
      _R(nR),
      _t(nt),
      voxel_size(nvoxel_size),
      occupied_threshold(noccupied_threshold)
    {
    }

    VoxelSetBodyC(BinIStreamC &is);
    //: Stream constructor.
    
    virtual ~VoxelSetBodyC()
    {
    }

  public:

    RealT voxelSize() const { return voxel_size; };
    const Matrix3dC& R() const { return _R; };
    const Vector3dC& t() const { return _t; };
    const Array3dC<ByteT>& Array() const { return vox; };
    Array3dC<ByteT>& Array() { return vox; };
    ByteT& OccupiedThreshold() { return occupied_threshold; }
    const ByteT& OccupiedThreshold() const { return occupied_threshold; }

    Index3dC VoxelIndex(const Vector3dC& xw) const
    {
      Vector3dC x = _R*xw + _t;
      return Index3dC(IndexC(x[0]/voxel_size+0.5),IndexC(x[1]/voxel_size+0.5),IndexC(x[2]/voxel_size+0.5));
    }

    bool IsOccupied(const Vector3dC& x)
    {
      Index3dC i(VoxelIndex(x));
      return (vox.Contains(i) && (vox[i] >= occupied_threshold));
    }

    bool GetVoxelCheck(ByteT& v, const Vector3dC& x) const
    {
      Index3dC i(VoxelIndex(x));
      if (!vox.Contains(i))
	return false;
      v = vox[i];
      return true;
    }

    bool GetVoxelPointerCheck(ByteT*& pv, const Vector3dC& x)
    {
     Index3dC i(VoxelIndex(x));
      if (!vox.Contains(i))
	return false;
      pv = &vox[i];
      return true;
    }
    
  protected:
   VoxelSetBodyC(const Matrix3dC& nR,
		 const Vector3dC& nt,
		 RealT nvoxel_size,
		 Array3dC<ByteT> nvox) :
	       
     vox(nvox),
     _R(nR),
     _t(nt),
     voxel_size(nvoxel_size)
    {}    
    
  public:
    void Fill(ByteT v);
    VoxelSetC ContiguousPortion(UIntT total_portions, UIntT portion_index);

  protected:
    Array3dC<ByteT> vox;
    Matrix3dC _R;
    Vector3dC _t;
    RealT voxel_size;
    ByteT occupied_threshold;
  };



  //! userlevel=Normal
  //: A cuboid of volume cells (voxels) in 3D space
  // Each voxel has an 8-bit flag for storing any user-defined attributes.
  // <p>
  // The voxel set has a coordinate system with xyz corresponding to index 0,1,2.
  // The origin of the coordinate system is at the centre of the voxel with index (0,0,0)
  // <p>
  // Voxel subsets created with ContiguousPortion(...) have the same world 
  // to voxel set transformation but different ranges of indices
  class VoxelSetC : public RCHandleC<VoxelSetBodyC>
  {
  public:
    VoxelSetC()
    {
    }
    //:Default constructor

    VoxelSetC(BinIStreamC &is)
      : RCHandleC<VoxelSetBodyC>(*new VoxelSetBodyC(is))
    {}
    //: Stream constructor
    
    VoxelSetC(const Matrix3dC& R,
	      const Vector3dC& t,
	      RealT voxel_size,
	      UIntT cube_side_num_voxels,
	      ByteT occupied_threshold = 1) :
      RCHandleC<VoxelSetBodyC>(*new VoxelSetBodyC(R,
						  t,
						  voxel_size,
						  cube_side_num_voxels,
						  occupied_threshold))
    {
    }
    //: Construct a cube of voxels
    // R*x + t transforms a 3D point x from world co-ordinates to voxel co-ordinates
    // <p>
    // voxel_size is the length of each side of a single voxel
    // <p>
    // Units of voxel_size must match those of t
    // <p>
    // cube_side_num_voxels is the number of voxels along each side of the cube

  public:
    RealT voxelSize() const { return Body().voxelSize(); }
    //: Length of a side of a single voxel

    const Matrix3dC& R() const { return Body().R(); }
    //:Orientation
    // R*x + t transforms a 3D point x from world co-ordinates to voxel co-ordinates

    const Vector3dC& t() const { return Body().t(); }
    //:Position
    // R*x + t transforms a 3D point x from world co-ordinates to voxel co-ordinates

    void Fill(ByteT v) { Body().Fill(v); }
    //:Set all voxel attributes equal to v

    bool IsOccupied(const Vector3dC& x);
    //: Checks the specified location against the occupied threshold.
    //  Returns true if the voxel is occupied, false if unoccupied or if x is not
    //  in the voxel set.

    bool GetVoxelCheck(ByteT& v, const Vector3dC& x) const { return Body().GetVoxelCheck(v,x); }
    //:Get the current attributes of voxel at location x
    // returns true if x is inside the voxel array, 0 otherwise

    bool GetVoxelPointerCheck(ByteT*& v, const Vector3dC& x) { return Body().GetVoxelPointerCheck(v,x); }
    //:Get a pointer to voxel attributes at location x
    // returns true if x is inside the voxel array, 0 otherwise

    const Array3dC<ByteT>& Array() const { return Body().Array(); }
    //:Direct access to voxel attributes(const)

    Array3dC<ByteT>& Array() { return Body().Array(); }
    //:Direct access to voxel attributes

    Index3dC VoxelIndex(const Vector3dC& x) const { return Body().VoxelIndex(x); }
    //:Index of voxel corresponding to point x in space
    // Can be used to index Array() directly, but GetVoxelCheck does this for you

    ByteT& OccupiedThreshold() { return Body().OccupiedThreshold(); }
    //:A voxel is said to be occupied if it has an attributes >= OccupiedThreshold

    const ByteT& OccupiedThreshold() const { return Body().OccupiedThreshold(); }
    //:A voxel is said to be occupied if it has an attributes >= OccupiedThreshold
   

  protected:
    VoxelSetC(VoxelSetBodyC& body)
      : RCHandleC<VoxelSetBodyC>(body)
    {
    }
  };

  BinOStreamC & operator<<(BinOStreamC & is, const VoxelSetC& oVoxelSet);
  // Prints the voxel set into the stream
  
  BinIStreamC & operator>>(BinIStreamC& os, VoxelSetC& oVoxelSet);
  // Assigns the values into the voxel set 

}

#endif
