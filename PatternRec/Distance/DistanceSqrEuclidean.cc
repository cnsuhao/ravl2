// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Distance/DistanceSqrEuclidean.cc"

#include "Ravl/PatternRec/DistanceSqrEuclidean.hh"

namespace RavlN {

  
  //: Measure the distance from d1 to d2.
  
  RealT DistanceSqrEuclideanBodyC::Measure(const VectorC &d1,const VectorC &d2) const {
    return VectorC(d1 - d2).SumOfSqr();
  }
  
  //: Measure the magnitude of d1.
  
  RealT DistanceSqrEuclideanBodyC::Magnitude(const VectorC &x) const {
    return x.SumOfSqr();
  }
  
  //: Calculates Jacobian matrix at X
  
  MatrixC DistanceSqrEuclideanBodyC::Jacobian (const VectorC &X) const {
    // dS/dX = 2X^T using chain rule since S=X.X
    MatrixC dSdX = MatrixC(X).T() * 2.0;
    return dSdX;
  }
  
}
