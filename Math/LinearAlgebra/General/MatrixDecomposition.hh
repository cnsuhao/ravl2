// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_MATRIXDECOMPOSITION_HEADER
#define RAVL_MATRIXDECOMPOSITION_HEADER 1
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/General/MatrixDecomposition.hh"

#include "Ravl/Matrix.hh"

namespace RavlN {
  
  SArray1dC<IntT> LUDecomposition(MatrixC &mat,RealT &d);
  //: LU Decomposition with partial pivoting.
  // This transforms 'mat' into (L + U - I). 'd' is set to
  // the determinant of the matrix. <br>
  // The order of the rows in the matrix is changed. the mapping
  // is returned if the decomposition was succesfull, if not
  // an invalid array is returned.
  
  bool LUDecompositionPD(MatrixC &mat,RealT &det);
  //: LUDecomposition for positive definite matrices.
  

}


#endif
