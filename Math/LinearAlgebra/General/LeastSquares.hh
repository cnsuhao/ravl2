// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_LEASTSQUARES_HEADER
#define RAVL_LEASTSQUARES_HEADER 1
//! rcsid="$Id$"
//! lib=RavlMath
//! docentry="Ravl.Math.Linear Algebra"
//! userlevel=Normal
//! file="Ravl/Math/LinearAlgebra/General/LeastSquares.hh"

#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  
  VectorC LeastSquaresQR(const MatrixC &A,const VectorC &b);
  //: Find a least squares solution to A*x = b
  // Uses the QR algorithm.
  
  
}

#endif
