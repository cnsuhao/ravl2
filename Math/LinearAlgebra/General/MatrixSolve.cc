// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/MatrixSolve.cc"

#include "Ravl/Matrix.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Vector.hh"
#include "Ravl/CCMath.hh"

namespace RavlN {
  
  //: Solve a general linear system  A*x = b
  // The input matix A is this one.  The input
  // vector is b, which is replaced by the ouput x.
  // This matrix is altered to L-U factored form by the computation.
  
  bool SolveIP(MatrixC &mat,VectorC &b) {
    RavlAlwaysAssertMsg(mat.Cols() == mat.Rows(),"MatrixC::SolveIP(), Matrix must be square. ");
    RavlAlwaysAssertMsg(mat.Cols() == b.Size(),"MatrixC::SolveIP(), Matrix must be the same size as the vector to solve. ");
    return solv(&mat[0][0],&b[0],mat.Rows()) == 0;
  }
  
  
  //: Solve a general linear system  A*x = b
  // Where a is this matrix, and X is the returned.
  // If matrix is singular a zero length vector is returned.
  
  VectorC Solve(const MatrixC &mat,const VectorC &b)  {
    VectorC ret(b.Copy());
    MatrixC tmp(mat.Copy());
    if(!SolveIP(tmp,ret))
      return VectorC();
    return ret;
  }
  

  static void SolveLU(const MatrixC &lu,const Slice1dC<RealT> &sb,Slice1dC<RealT> &x) {
    RealT sum;
    IntT i,n = lu.Rows();
    SArray1dC<RealT> b = sb; // Copy into a linear array, its faster.
    for(i = 0;i < n;i++) {
      sum = b[i];
      // FIXME: Could be sped up with points
      for(int j = 0;j < i;j++)
	sum -= lu[i][j] * b[j];
      b[i] = sum;
    }
    for(i = n;i > 0;i--) {
      sum = b[i];
      // FIXME: Could be sped up with points
      for(int j = i+1;j < n;j++)
	sum -= lu[i][j] * b[j];
      RealT v = sum/lu[i][i];
      b[i] = v;
      x[i] = v;
    }
  }
  
  //: Solve a general linear system  A*X = b
  // This return's X, or a 0 by 0 matrix if it fails.
  
  MatrixC Solve(const MatrixC &A,const MatrixC &B) {
    RavlAlwaysAssertMsg(A.Cols() == B.Rows(),"MatrixC::Solve(), Matrix must be square. ");
    MatrixC ret;
    const IntT n = B.Cols();
    MatrixC Ac = A.Copy();
    VectorC col = const_cast<MatrixC &>(B).SliceColumn(0);
    if(!SolveIP(Ac,col))
      return MatrixC();
    ret.SliceColumn(0).Copy(col); // Copy in first result.
    
    // Ac is now in LU form.
    for(int i = 1;i < n;i++) {
      Slice1dC<RealT> out = ret.SliceColumn(i);
      SolveLU(Ac,const_cast<MatrixC &>(B).SliceColumn(i),out);
    }
    return ret;
  }

}
