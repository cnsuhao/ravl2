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
  
  bool MatrixC::SolveIP(VectorC &b) {
    RavlAlwaysAssertMsg(Cols() == Rows(),"MatrixC::SolveIP(), Matrix must be square. ");
    RavlAlwaysAssertMsg(Cols() == b.Size(),"MatrixC::SolveIP(), Matrix must be the same size as the vector to solve. ");
    return solv(&(*this)[0][0],&b[0],Rows()) == 0;
  }
  
  
  //: Solve a general linear system  A*x = b
  // Where a is this matrix, and X is the returned.
  // If matrix is singular a zero length vector is returned.
  
  VectorC MatrixC::Solve(const VectorC &b) const {
    VectorC ret(b.Copy());
    MatrixC tmp(Copy());
    if(!tmp.SolveIP(ret))
      return VectorC();
    return ret;
  }

}
