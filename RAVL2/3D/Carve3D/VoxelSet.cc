// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! file="Ravl/3D/Carve3D/VoxelSet.cc"

#include "Ravl/3D/VoxelSet.hh"
#include "Ravl/BinStream.hh"

//! rcsid="$Id: VoxelSet.cc 1533 2002-08-08 16:03:23Z craftit $"
//! lib=Ravl3D

namespace Ravl3DN
{
  using namespace RavlN;
  
  void VoxelSetBodyC::Fill(ByteT v)
  { vox.Fill(v); }

  VoxelSetC VoxelSetBodyC::ContiguousPortion(UIntT total_portions, UIntT portion_index)
  { return VoxelSetC(); }

  // Prints the voxel set into the stream
  BinOStreamC & operator<<(BinOStreamC & os, const VoxelSetC& oVoxelSet)
  {
    os << oVoxelSet.OccupiedThreshold();
    os << oVoxelSet.voxelSize();
    os << oVoxelSet.R();
    os << oVoxelSet.t();
    os << oVoxelSet.Array();
    return os;
  }
  
  //: Stream constructor.  
  VoxelSetBodyC::VoxelSetBodyC(BinIStreamC &is) 
  {
    is >> occupied_threshold;
    is >> voxel_size;
    is >> _R;
    is >> _t;
    is >> vox;
  }
  
  // Assigns the values into the voxel set 
  BinIStreamC & operator>>(BinIStreamC& is, VoxelSetC& oVoxelSet)
  {
    oVoxelSet = VoxelSetC(is);
    return is;
  }

}
