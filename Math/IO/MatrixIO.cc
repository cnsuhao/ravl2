// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMathIO
//! file="Ravl/Math/IO/MatrixIO.cc"

#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"
#include "Ravl/VectorMatrix.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"

namespace RavlN {
  static TypeNameC type1(typeid(MatrixC),"RavlN::MatrixC");
  static TypeNameC type2(typeid(VectorC),"RavlN::VectorC");
  static TypeNameC type3(typeid(VectorMatrixC),"RavlN::VectorMatrixC");
  static TypeNameC type4(typeid(SArray1dC<MatrixC>),"RavlN::SArray1dC<MatrixC>");
  static TypeNameC type5(typeid(SArray1dC<VectorC>),"RavlN::SArray1dC<VectorC>");
  static TypeNameC type6(typeid(SArray1dC<VectorMatrixC>),"RavlN::SArray1dC<VectorMatrixC>");
  
  void InitMatrixIO()
  {}
  
  FileFormatStreamC<MatrixC> FileFormatStream_Matrix;
  FileFormatStreamC<VectorC> FileFormatStream_Vector;
  FileFormatStreamC<VectorMatrixC> FileFormatStream_VectorMatrix;
  
  FileFormatBinStreamC<MatrixC> FileFormatBinStream_Matrix;
  FileFormatBinStreamC<VectorC> FileFormatBinStream_Vector;
  FileFormatBinStreamC<VectorMatrixC> FileFormatBinStream_VectorMatrix;
  
  FileFormatStreamC<SArray1dC<MatrixC> > FileFormatStream_SArray1dC_Matrix;
  FileFormatStreamC<SArray1dC<VectorC> > FileFormatStream_SArray1dC_Vector;
  FileFormatStreamC<SArray1dC<VectorMatrixC> > FileFormatStream_SArray1dC_VectorMatrix;
  
  FileFormatBinStreamC<SArray1dC<MatrixC> > FileFormatBinStream_SArray1dC_Matrix;
  FileFormatBinStreamC<SArray1dC<VectorC> > FileFormatBinStream_SArray1dC_Vector;
  FileFormatBinStreamC<SArray1dC<VectorMatrixC> > FileFormatBinStream_SArray1dC_VectorMatrix;
}
