// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Distance/DistanceEuclidean.cc"

#include "Ravl/PatternRec/DistanceEuclidean.hh"

namespace RavlN {

  
  //: Measure the distance from d1 to d2.
  
  RealT DistanceEuclideanBodyC::Measure(const VectorC &d1,const VectorC &d2) const {
    return VectorC(d1 - d2).Modulus();
  }
  
  //: Measure the magnitude of d1.
  
  RealT DistanceEuclideanBodyC::Magnitude(const VectorC &x) const {
    return x.Modulus();
  }

  //: Calculates Jacobian matrix at X
  
  MatrixC DistanceEuclideanBodyC::Jacobian (const VectorC &X) const {
    // dS/dX = 1/|X|X^T using chain rule since S=|X|
    MatrixC dSdX = MatrixC(X).T() * (1.0/X.Modulus());
    return dSdX;
  }
  
}
