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
#include "Ravl/Eigen.hh"

#define RAVL_USE_CCMATH_EIGEN 1
// Note this switch is for experiment use, it doesn't switch all functions accross.

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
    if(mat.Rows() == 1)
      return mat.AsVector();
    VectorC ret(mat.Rows());
    if(mat.Rows() == 1) {
      ret[0] = mat[0][0];
      return ret;
    }
    eigval(&(mat[0][0]),&(ret[0]),mat.Rows());
    return ret;
  }
  
  VectorC EigenVectors(const MatrixC &mat,MatrixC &E) {
#if RAVL_USE_CCMATH_EIGEN
    E = mat.Copy();
    return EigenVectorsIP(E);
#else
    cerr << "Using new EigenValue code. \n";
    EigenValueC<RealT> ev(mat);
    E = ev.EigenVectors();
    return ev.EigenValues();
#endif
  }

  VectorMatrixC EigenVectors(const MatrixC &mat) {
#if RAVL_USE_CCMATH_EIGEN
    MatrixC ret = mat.Copy();
    VectorC vec =  EigenVectorsIP(ret);
#else
    cerr << "Using new EigenValue code. \n";
    EigenValueC<RealT> ev(mat);
    MatrixC ret = ev.EigenVectors();
    VectorC vec = ev.EigenValues();
#endif
    return VectorMatrixC(vec,ret);
  }
  
  VectorC EigenVectorsIP(MatrixC &mat) {
    RavlAlwaysAssert(mat.IsContinuous()); // Should we cope with this silently ?
    RavlAlwaysAssertMsg(mat.Rows() == mat.Cols(),"MatrixC::EigenVectorsIP() Matrix must be square. ");
    if(mat.Rows() == 0)
      return VectorC(0);
    VectorC ret(mat.Rows());
    if(mat.Rows() == 0)
      return ret;
    if(mat.Rows() == 1) {
      ret[0] = mat[0][0];
      mat[0][0] = 1;
      return ret;
    }
    eigen(&(mat[0][0]),&(ret[0]),mat.Rows());
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

#if RAVL_COMPILER_GNU
  template<class NumT> class EigenC;
#endif
}
