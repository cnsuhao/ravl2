// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOptimise

#include "Ravl/ObservationLine2dPoint.hh"
#include "Ravl/StateVectorLine2d.hh"
#include "Ravl/ObsVectorBiGaussian.hh"

namespace RavlN {

  //: Constructor.
  ObservationLine2dPointBodyC::ObservationLine2dPointBodyC(
				   const VectorC &nz, const MatrixRSC &nNi)
    : ObservationImplicitBodyC(ObsVectorC(nz,nNi),1)
  {
  }

  //: Constructor for robust bi-Gaussian observation.
  ObservationLine2dPointBodyC::ObservationLine2dPointBodyC(
			     const VectorC &nz, const MatrixRSC &nNi,
			     RealT nvar_scale, RealT nchi2_thres)
    : ObservationImplicitBodyC(ObsVectorBiGaussianC(nz,nNi,nvar_scale,nchi2_thres),1)
  {
  }

  //: Evaluate an observation for a single point
  VectorC ObservationLine2dPointBodyC::EvaluateFunctionF(const StateVectorC &state_vec)
  {
    // we know that the state vector actually represents a 2D line
    const StateVectorLine2dC sv = state_vec;
    RavlAssert(sv.IsValid());
    
    const VectorC &z = GetZ(); // 2D image point

    // compute F = (lx*xc + ly*yc + lz*zh)/sqrt(lx*lx + ly*ly)
    // but assuming lx*lx + ly*ly = 1
    VectorC Fv(1);
    Fv[0] = sv.GetLx()*z[0] + sv.GetLy()*z[1] + sv.GetLz()*sv.GetZH();
#if 0
    cout << "l=(" << sv.GetLx() << " " << sv.GetLy() << " " << sv.GetLz() << " (x,y)= " << z[0] << " " << z[1] << " F=" << Fv[0] << endl;
#endif
    // store computed function value
    F = Fv[0];

    return Fv;
  }
#if 1
  //: Evaluate the Jacobian of an observation for a single point w.r.t. the
  //: 2D point observation
  MatrixC ObservationLine2dPointBodyC::EvaluateJacobianFz(const StateVectorC &state_vec)
  {
    // we know that the state vector actually represents a 2D line
    const StateVectorLine2dC& sv = state_vec;
    RavlAssert(sv.IsValid());
    
    MatrixC Fz(1,2); // Jacobian matrix

    // evaluate Jacobian
    Fz[0][0] = sv.GetLx();
    Fz[0][1] = sv.GetLy();
    return Fz;
  }

  //: Evaluate the Jacobian of an observation for a single point w.r.t. the
  //: line parameters
  MatrixC ObservationLine2dPointBodyC::EvaluateJacobianFx(const StateVectorC &state_vec)
  {
    // we know that the state vector actually represents a 2D line
    const StateVectorLine2dC& sv = state_vec;
    RavlAssert(sv.IsValid());
    
    const VectorC &z = GetZ(); // 2D image point pair
    MatrixC Fx(1,3); // Jacobian matrix

    // evaluate Jacobian
    Fx[0][0] = z[0] - sv.GetLx()*F;
    Fx[0][1] = z[1] - sv.GetLy()*F;
    Fx[0][2] = sv.GetZH();
    return Fx;
  }
#endif
}
