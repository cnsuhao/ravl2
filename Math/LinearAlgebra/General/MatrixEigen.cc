// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/MatrixEigen.cc"

#include "Ravl/StdConst.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"
#include "Ravl/CCMath.hh"
#include "Ravl/VectorMatrix.hh"

// matrix functions.

namespace RavlN {
  // n*m row*col
  
  VectorC EigenValues(const MatrixC &mat) {
    MatrixC ret = mat.Copy();
    return EigenValuesIP(ret);
  }
  
  VectorC EigenValuesIP(MatrixC &mat) {
    RavlAlwaysAssert(mat.IsContinuous()); // Should we cope with this silently ?
    RavlAlwaysAssertMsg(mat.Rows() == mat.Cols(),"MatrixC::EigenValuesIP() Matrix must be square. ");
    if(mat.Rows() == 0)
      return VectorC(0);
    VectorC ret(mat.Rows());
    eigval(&mat[0][0],&ret[0],mat.Rows());
    return ret;
  }
  
  VectorC EigenVectors(const MatrixC &mat,MatrixC &E) {
    E = mat.Copy();
    return EigenVectorsIP(E);
  }

  VectorMatrixC EigenVectors(const MatrixC &mat) {
    MatrixC ret = mat.Copy();
    VectorC vec =  EigenVectorsIP(ret);
    return VectorMatrixC(vec,ret);
  }
  
  VectorC EigenVectorsIP(MatrixC &mat) {
    RavlAlwaysAssert(mat.IsContinuous()); // Should we cope with this silently ?
    RavlAlwaysAssertMsg(mat.Rows() == mat.Cols(),"MatrixC::EigenVectorsIP() Matrix must be square. ");
    VectorC ret(mat.Rows());
    eigen(&mat[0][0],&ret[0],mat.Rows());
    return ret;
  }
  
  //: Get the maximum eigen value and its vector.
  
  RealT MaxEigenValue(const MatrixC &mat,VectorC &maxv) {
    RavlAlwaysAssert(mat.IsContinuous()); // Should we cope with this silently ?
    RavlAlwaysAssertMsg(mat.Rows() == mat.Cols(),"MatrixC::MaxEigenValue() Matrix must be square. ");
    maxv = VectorC(mat.Rows());
    RealT ret = evmax(const_cast<RealT *>(&mat[0][0]),&maxv[0],mat.Rows());
#if 0
    if(ret == HUGE) {
      return RavlConstN::nanReal;
    }
#endif
    return ret;
  }

  

}
