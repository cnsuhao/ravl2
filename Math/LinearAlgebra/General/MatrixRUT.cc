// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/MatrixRUT.cc"

#include "Ravl/MatrixRUT.hh"
#include "Ravl/Vector.hh"
#include "Ravl/CCMath.hh"

namespace RavlN {
  
  //: Calculate the inverse of a upper right triangular matrix.
  // an invalid matrix is returned if this matrix is
  // singular. This can be tested for by IsValid().
  
  MatrixRUTC MatrixRUTC::Inverse() const {
    MatrixRUTC ret = Copy();
    if(!ret.InverseIP()) {
      // Could throw an exception ?
      return MatrixC(); 
    }
    return ret;
  }
  
  bool MatrixRUTC::InverseIP() {
    RavlAlwaysAssert(IsContinuous()); // What should we do now ?
    RavlAlwaysAssertMsg(Cols() == Rows(),"MatrixRUTC::InverseIP(), Matrix must be square to invert ");    
    return ruinv(&(*this)[0][0],Rows()) == 0; // ccmath routine.
  }
  
  //: Solve a general linear system  A*x = b
  // The input matix A is this one.  The input
  // vector is b, which is replaced by the ouput x.
  // This matrix is altered to L-U factored form by the computation.
  
  bool MatrixRUTC::SolveIP(VectorC &b) {
    RavlAlwaysAssertMsg(Cols() == Rows(),"MatrixRUTC::SolveIP(), Matrix must be square. ");
    RavlAlwaysAssertMsg(Cols() == b.Size(),"MatrixRUTC::SolveIP(), Matrix must be the same size as the vector to solve. ");
    return solvru(&(*this)[0][0],&b[0],Rows()) == 0;
  }
  
  
  //: Solve a general linear system  A*x = b
  // Where a is this matrix, and X is the returned.
  // If matrix is singular a zero length vector is returned.
  
  VectorC MatrixRUTC::Solve(const VectorC &b) const {
    VectorC ret(b.Copy());
    MatrixRUTC tmp(Copy());
    if(!tmp.SolveIP(ret))
      return VectorC();
    return ret;
  }

  
}
