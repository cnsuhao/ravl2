// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOptimise

#include "Ravl/ObservationAffine2dPoint.hh"
#include "Ravl/StateVectorAffine2d.hh"
#include "Ravl/ObsVectorBiGaussian.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Exception.hh"

namespace RavlN {

  //: Constructor.
  
  ObservationAffine2dPointBodyC::ObservationAffine2dPointBodyC(const VectorC &nz1, const MatrixRSC &nNi1,
							       const VectorC &nz2, const MatrixRSC &nNi2)
    : ObservationExplicitBodyC(ObsVectorC(nz2,nNi2))
  {
    z1 = nz1;
    Ni1 = nNi1;
  }
  
  //: Evaluate an observation for a single point
  
  VectorC ObservationAffine2dPointBodyC::EvaluateFunctionH(const StateVectorC &stateVec) {
    // we know that the state vector actually represents a 2D affine homography
    const StateVectorAffine2dC sv(stateVec);
    RavlAssert(sv.IsValid());
    Vector2dC p = sv.GetAffine() * Vector2dC(z1[0],z1[1]);
    return VectorC(p);
  }
  
  //: Evaluate the Jacobian of an observation for a single point
  
  MatrixC ObservationAffine2dPointBodyC::EvaluateJacobianHx(const StateVectorC &stateVec) {
    // we know that the state vector actually represents a 2D affine homography
    const StateVectorAffine2dC sv(stateVec);
    RavlAssert(sv.IsValid());
    Vector2dC p = sv.GetAffine() * Vector2dC(z1[0],z1[1]);
    
    MatrixC H(2,6); // Jacobian matrix
    
    H[0][0] = p[0];   H[1][0] = 0;
    H[0][1] = p[1];   H[1][1] = 0;
    H[0][2] = 1;      H[1][2] = 0;
    H[0][3] = 0;      H[1][3] = p[0];
    H[0][4] = 0;      H[1][4] = p[1];
    H[0][5] = 0;      H[1][5] = 1;
    
    return H;
  }
}
