/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Matrix2d.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/Matrix4d.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/SArray1d.hh"

namespace RavlN {
  static TypeNameC type1(typeid(Matrix2dC),"Matrix2dC");
  static TypeNameC type2(typeid(Matrix3dC),"Matrix3dC");
  static TypeNameC type3(typeid(Matrix4dC),"Matrix4dC");
  
  static TypeNameC type4(typeid(SArray1dC<Matrix2dC>),"SArray1dC<Matrix2dC>");
  static TypeNameC type5(typeid(SArray1dC<Matrix3dC>),"SArray1dC<Matrix3dC>");
  static TypeNameC type6(typeid(SArray1dC<Matrix4dC>),"SArray1dC<Matrix4dC>");
  
  void InitFixedMatrixIO()
  {}
  
  FileFormatStreamC<Matrix2dC> FileFormatStream_Matrix2d;
  FileFormatStreamC<Matrix3dC> FileFormatStream_Matrix3d;
  FileFormatStreamC<Matrix4dC> FileFormatStream_Matrix4d;
  
  FileFormatBinStreamC<Matrix2dC> FileFormatBinStream_Matrix2d;
  FileFormatBinStreamC<Matrix3dC> FileFormatBinStream_Matrix3d;
  FileFormatBinStreamC<Matrix4dC> FileFormatBinStream_Matrix4d;
  
  // Add some IO for arrays of Matrixs.

  FileFormatStreamC<SArray1dC<Matrix2dC> > FileFormatStream_SArray1dC_Matrix2d;
  FileFormatStreamC<SArray1dC<Matrix3dC> > FileFormatStream_SArray1dC_Matrix3d;
  FileFormatStreamC<SArray1dC<Matrix4dC> > FileFormatStream_SArray1dC_Matrix4d;
  
  FileFormatBinStreamC<SArray1dC<Matrix2dC> > FileFormatBinStream_SArray1dC_Matrix2d;
  FileFormatBinStreamC<SArray1dC<Matrix3dC> > FileFormatBinStream_SArray1dC_Matrix3d;
  FileFormatBinStreamC<SArray1dC<Matrix4dC> > FileFormatBinStream_SArray1dC_Matrix4d;
}
