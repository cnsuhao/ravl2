// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/3D/VoxelCarve.hh"
#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"
//! rcsid="$Id$"
//! lib=RavlCarve3D

namespace Ravl3DN
{
  PointSetC VoxelCarveBodyC::PointSet()
  {
    Array3dC<ByteT> vox = voxel.Array();
    DListC<Vector3dC> listPosition;
    UIntT n = vox.Range1().Size();
    UIntT num_views = lookup.Size();
    Matrix3dC R = voxel.R().T() * voxel.voxelSize();
    Vector3dC t = voxel.R().TMul(voxel.t()) * -1.0;
    ByteT mask = (1 << num_views) - 1;

    for (UIntT i = 0; i < n; i++)
      for (UIntT j = 0; j < n; j++)
	for (UIntT k = 0; k < n; k++)
	  if (vox[i][j][k] == mask)
	    listPosition.InsLast( R*Vector3dC(i,j,k) + t);

    PointSetC points(listPosition.Size());
    UIntT count = 0;
    for (DLIterC<Vector3dC> ipoint(listPosition); ipoint; ipoint++, count++)
      points.Vertices()[count].Position() = *ipoint;
    return points;
  }
}
