// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCarve3D

#include "Ravl/3D/VoxelCameraLookup.hh"
#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/Array2dIter2.hh"

namespace Ravl3DN
{
  VoxelCameraLookupBodyC::VoxelCameraLookupBodyC(const PinholeCamera0C& ncamera,
						 UIntT image_rows,
						 UIntT image_cols,
						 const VoxelSetC &nvoxel) :
    camera(ncamera),
    voxel(nvoxel),
    lookup(image_rows, image_cols)
  {
    // cerr << "VoxelCameraLookupBodyC()" << endl;
    // cerr << "Camera: " << endl << camera << endl;

    // camera centre of projection
    RealT cx = camera.cx();
    RealT cy = camera.cy();
    RealT fx = camera.fx();
    RealT fy = camera.fy();

    // transform from camera to voxel co-ords
    Matrix3dC R = voxel.R() * camera.R().T();
    Vector3dC t = voxel.t() + voxel.R() * (camera.R().TMul(camera.t()) * -1.0);

    // cerr << "cam-voxel t: " << t << endl;

    // generate lookup
    UIntT row,col;
    for (row=0; row<image_rows; row++) 
    {
      // NOTE: ignoring first and last 10 pixesl in x direction
      for (col=10; col<image_cols-10; col++) 
      {
        // Get 3D ray corresponding to the pixel in the lookup table
	Vector3dC dir_cam((col - cx) / fx, (row - cy) / fy, 1.0);
        Vector3dC dir_voxel = R*dir_cam;

        Vector3dC oVoxelStart, oVoxelEnd;
        if (ClipRay(t,dir_voxel,oVoxelStart,oVoxelEnd)) 
	{
          // Voxelise the ray and fill the lookup table
          SetRayLookup(oVoxelStart, oVoxelEnd, lookup[row][col]);
	  // cerr << "camera-voxel: " << dir_cam << ": " << oVoxelStart << " -> " << oVoxelEnd << endl;
        }
	else
	{
	  lookup[row][col] = SArray1dC<ByteT*> ();
	}

	// cerr << "lookup voxels: " << lookup[row][col].Size() << endl;
      }
    }
  }

  // Clip a ray against the voxel set
  bool VoxelCameraLookupBodyC::ClipRay(
    const Vector3dC& line_origin, 
    const Vector3dC& line_dir,
    Vector3dC& voxel_start,
    Vector3dC& voxel_end)
  {
    Array3dC<ByteT>& array = voxel.Array();

    // Clip the ray against each pair of bounding planes
    RealT dStart=0.0, dEnd=1000;

    // Clip against +/- x
    if (fabs(line_dir.X()) > 1E-3) 
    {
      IndexC uiMinXIndex = array.Range1().Min();
      IndexC uiMaxXIndex = array.Range1().Max();
      RealT dXmin = (RealT)uiMinXIndex*voxel.voxelSize();
      RealT dXmax = (RealT)uiMaxXIndex*voxel.voxelSize();
      RealT dMinIntersect = (dXmin-line_origin.X())/line_dir.X();
      RealT dMaxIntersect = (dXmax-line_origin.X())/line_dir.X();
      if (line_dir.X()>0.0) 
      {
        if (dMaxIntersect<0.0) 
	  return false;
        dEnd = dMaxIntersect;
        if (dMinIntersect>dStart) 
	  dStart = dMinIntersect;
      } 
      else 
      {
        if (dMinIntersect<0.0) 
	  return false;
        dEnd = dMinIntersect;
        if (dMaxIntersect>dStart) 
	  dStart = dMaxIntersect;
      }
    }

    // Clip against +/- y
    if (fabs(line_dir.Y()) > 1E-3) 
    {
      IndexC uiMinYIndex = array.Range2().Min();
      IndexC uiMaxYIndex = array.Range2().Max();
      RealT dYmin = (RealT)uiMinYIndex*voxel.voxelSize();
      RealT dYmax = (RealT)uiMaxYIndex*voxel.voxelSize();
      RealT dMinIntersect = (dYmin-line_origin.Y())/line_dir.Y();
      RealT dMaxIntersect = (dYmax-line_origin.Y())/line_dir.Y();
      if (line_dir.Y()>0.0)
      {
        if (dMaxIntersect<0.0) 
	  return false;
        if (dMaxIntersect<dEnd) 
	  dEnd = dMaxIntersect;
        if (dMinIntersect>dStart) 
	  dStart = dMinIntersect;
      } 
      else
      {
        if (dMinIntersect<0.0) 
	  return false;
        if (dMinIntersect<dEnd) 
	  dEnd = dMinIntersect;
        if (dMaxIntersect>dStart) 
	  dStart = dMaxIntersect;
      }
    }

    // Clip against +/- z
    if (fabs(line_dir.Z()) > 1E-3)
    {
      IndexC uiMinZIndex = array.Range3().Min();
      IndexC uiMaxZIndex = array.Range3().Max();
      RealT dZmin = (RealT)uiMinZIndex*voxel.voxelSize();
      RealT dZmax = (RealT)uiMaxZIndex*voxel.voxelSize();
      RealT dMinIntersect = (dZmin-line_origin.Z())/line_dir.Z();
      RealT dMaxIntersect = (dZmax-line_origin.Z())/line_dir.Z();
      if (line_dir.Z()>0.0) 
      {
        if (dMaxIntersect<0.0)
	  return false;
        if (dMaxIntersect<dEnd) 
	  dEnd = dMaxIntersect;
        if (dMinIntersect>dStart) 
	  dStart = dMinIntersect;
      } 
      else 
      {
        if (dMinIntersect<0.0) 
	  return false;
        if (dMinIntersect<dEnd) 
	  dEnd = dMinIntersect;
        if (dMaxIntersect>dStart) 
	  dStart = dMaxIntersect;
      }
    }

    // Calculate the intersection points
    if (dStart < 0.0 || dStart > dEnd) 
      return false;
    voxel_start = line_origin + line_dir*dStart;
    voxel_end   = line_origin + line_dir*dEnd;

    return true;
  }

  // Voxelize a ray and fill the voxels in the lookup for the pixel corresponding to a ray
  void VoxelCameraLookupBodyC::SetRayLookup(const Vector3dC& oVoxelStart, 
					    const Vector3dC& oVoxelEnd,
					    SArray1dC<ByteT*>& pixelLookup)
  {
    RealT dx = oVoxelEnd[0] - oVoxelStart[0];
    RealT dy = oVoxelEnd[1] - oVoxelStart[1];
    RealT dz = oVoxelEnd[2] - oVoxelStart[2];

    RealT mdx = fabs(dx);
    RealT mdy = fabs(dy);
    RealT mdz = fabs(dz);

    if (mdx > mdy && mdx > mdz)
    { 
      dx /= mdx;
      dy /= mdx;
      dz /= mdx;
    }
    else if (mdy > mdx && mdy > mdz)
    {
      dx /= mdy;
      dy /= mdy;
      dz /= mdy;
    }
    else
    {
      dx /= mdz;
      dy /= mdz;
      dz /= mdz;
    }
    
    RealT scale = 1.0 / voxel.voxelSize();
    RealT x = oVoxelStart[0] * scale;
    RealT y = oVoxelStart[1] * scale;
    RealT z = oVoxelStart[2] * scale;

    Array3dC<ByteT>& vox = voxel.Array();
    DListC<ByteT*> oList;

    while (1)
    {
      // cerr << "testing: " << x << " " << y << " " << z << endl;

      UIntT i = (UIntT)(x + 0.5);
      UIntT j = (UIntT)(y + 0.5);
      UIntT k = (UIntT)(z + 0.5);

      if (i < vox.Range1().Min() || i > vox.Range1().Max() ||
	  j < vox.Range2().Min() || j > vox.Range2().Max() ||
	  k < vox.Range3().Min() || k > vox.Range3().Max())
	break;

      oList += &vox[i][j][k];
      x += dx;
      y += dy;
      z += dz;
    }

    // Copy the list into the array
    pixelLookup = SArray1dC<ByteT*>( oList.Size() );
    DLIterC<ByteT*> itList(oList);
    SArray1dIterC<ByteT*> itArray(pixelLookup);
    for (;itList;itList++,itArray++) 
      *itArray = *itList;
  }

  void VoxelCameraLookupBodyC::Apply(const ImageC<ByteT>& image, ByteT mask)
  {
    for (Array2dIter2C<ByteT, SArray1dC<ByteT*> > i(image, lookup); i; i++)
      if (i.Data1())
	for (SArray1dIterC<ByteT*> j(i.Data2()); j; j++)
	  *(*j) |= mask;
  }
}
