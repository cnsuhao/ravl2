// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! rcsid="$Id: FixedVectorIO.cc 737 2002-01-31 14:55:49Z craftit $"
//! lib=RavlMathIO
//! file="Ravl/Math/IO/FixedVectorIO.cc"

#include "Ravl/Vector2d.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Vector4d.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/SArray1d.hh"

namespace RavlN {
  void InitFixedVectorIO()
  {}
  
  static TypeNameC type1(typeid(Vector2dC),"Vector2dC");
  static TypeNameC type2(typeid(Vector3dC),"Vector3dC");
  static TypeNameC type3(typeid(Vector4dC),"Vector4dC");
  
  static TypeNameC type4(typeid(SArray1dC<Vector2dC>),"SArray1dC<Vector2dC>");
  static TypeNameC type5(typeid(SArray1dC<Vector3dC>),"SArray1dC<Vector3dC>");
  static TypeNameC type6(typeid(SArray1dC<Vector4dC>),"SArray1dC<Vector4dC>");
  
  
  FileFormatStreamC<Vector2dC> FileFormatStream_Vector2d;
  FileFormatStreamC<Vector3dC> FileFormatStream_Vector3d;
  FileFormatStreamC<Vector4dC> FileFormatStream_Vector4d;
  
  FileFormatBinStreamC<Vector2dC> FileFormatBinStream_Vector2d;
  FileFormatBinStreamC<Vector3dC> FileFormatBinStream_Vector3d;
  FileFormatBinStreamC<Vector4dC> FileFormatBinStream_Vector4d;
  
  // Add some IO for arrays of Vectors.

  FileFormatStreamC<SArray1dC<Vector2dC> > FileFormatStream_SArray1dC_Vector2d;
  FileFormatStreamC<SArray1dC<Vector3dC> > FileFormatStream_SArray1dC_Vector3d;
  FileFormatStreamC<SArray1dC<Vector4dC> > FileFormatStream_SArray1dC_Vector4d;
  
  FileFormatBinStreamC<SArray1dC<Vector2dC> > FileFormatBinStream_SArray1dC_Vector2d;
  FileFormatBinStreamC<SArray1dC<Vector3dC> > FileFormatBinStream_SArray1dC_Vector3d;
  FileFormatBinStreamC<SArray1dC<Vector4dC> > FileFormatBinStream_SArray1dC_Vector4d;
}
