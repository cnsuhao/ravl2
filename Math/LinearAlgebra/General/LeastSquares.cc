// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/LeastSquares.cc"

#include "Ravl/LeastSquares.hh"
#include "ccmath/ccmath.h"
#include "Ravl/Exception.hh"

namespace RavlN {
  
  //: Find a least squares solution to A*x = b
  // Uses the QR algorithm.
  
  VectorC LeastSquaresQR(const MatrixC &xA,const VectorC &xb,RealT &residual) {
    MatrixC A = xA.Copy();
    VectorC b = xb.Copy();
    int f = 0;
    RavlAssert(A.Size1() == xb.Size());
    residual = qrlsq(&(A[0][0]),&(b[0]),A.Size1(),A.Size2(),&f);
    if(f != 0) 
      return VectorC();
    return VectorC(SArray1dC<RealT>(b,A.Size2()));
  }
  
  //: Find a least squares solution to A*x = b
  // This destroys the contents of A, and replaces b with the solution vector.
 
  bool LeastSquaresQR_IP(MatrixC &A,VectorC &b,RealT &residual) {
    int f = 0;
    residual = qrlsq(&(A[0][0]),&(b[0]),A.Size1(),A.Size2(),&f);
    b = VectorC(SArray1dC<RealT>(b,A.Size2()));
    return f == 0;
  }
 
}
