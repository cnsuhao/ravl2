// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/LevenbergMarquardt.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/MatrixRUT.hh"
#include "Ravl/DList.hh" // Need this for some reason to get the linker to work

namespace RavlN {

  //: Constructor for Levenberg-Marquardt.
  LevenbergMarquardtC::LevenbergMarquardtC(StateVectorC &state_vec_init,
					   DListC<ObservationC> obs_list)
    : StoredStateC::StoredStateC(state_vec_init)
  {
    A = MatrixRSC(state_vec.GetX().Size());
    Ainv = MatrixRSC(state_vec.GetX().Size());
    residual = ComputeResidual(obs_list);
    A_updated = Ainv_updated = false;
  }

  // compute residual given existing state vector
  RealT LevenbergMarquardtC::ComputeResidual(DListC<ObservationC> obs_list) const
  {
    RealT residual = 0.0;

    // go through observations one by one, adding up residual
    for(DLIterC<ObservationC> it(obs_list);it;it++) {
      ObservationC obs = it.Data();

      // accumulate residual
      residual += obs.Residual(state_vec);
    }

    return residual;
  }

  // Apply an iteration, processing observations and updating the state
  // Returns true if the iteration succeeded in reducing the residual,
  // false otherwise.
  bool LevenbergMarquardtC::Iteration ( DListC<ObservationC> obs_list,
					RealT lambda )
  {
    VectorC a = state_vec.GetX().Copy();

    // force recalculation of (inverse) covariance matrix
    A_updated = Ainv_updated = false;

    // initialise information to zero
    A.Fill(0.0);
    a.Fill(0.0);

    // store existing state vector
    VectorC xold = state_vec.GetX().Copy();

    // go through observations one by one
    for(DLIterC<ObservationC> it(obs_list);it;it++) {
      ObservationC obs = it.Data();

      // accumulate information sum
      obs.IncrementLS ( state_vec, A, a );
    }

    // add any adjustments specified by the state vector
    state_vec.IncrementLS ( A, a );

    IntT i;
#if 1
    // add lambda*I to A
    for ( i = (IntT)A.Rows()-1; i >= 0; i-- )
      A[i][i] += lambda;
#else
    // scale diagonal of A by 1+lambda
    for ( i = (IntT)A.Rows()-1; i >= 0; i-- )
      A[i][i] = (1.0+lambda)*A[i][i];
#endif

    // compute inverse of the information matrix
    Ainv = A.Inverse();

    // compute A^-1*a
    a = Ainv*a;

    // add A^-1*a to state vector x
    state_vec.IncX(a);

    // compute residual after update
    RealT new_residual = ComputeResidual ( obs_list );

    // reinstate state vector if the new residual is equal or higher
    if ( new_residual >= residual ) {
      state_vec.SetX(xold);

      // restore state of observations
      for(DLIterC<ObservationC> it(obs_list); it; it++) {
	ObservationC obs = it.Data();
	ObsVectorC obs_vec = obs.GetObsVec();
	obs_vec.Restore();
      }

      return false;
    }
    else {
      // update best residual
      residual = new_residual;
      return true;
    }
  }

  // Latest estimate of solution parameters
  const VectorC &LevenbergMarquardtC::SolutionVector() const
  {
    return state_vec.GetX();
  }

  // Inverse covariance matrix of solution
  const MatrixRSC &LevenbergMarquardtC::InverseCovarianceMatrix(DListC<ObservationC> obs_list)
  {
    // invalid vector
    VectorC a;

    // initialise information to zero
    A.Fill(0.0);

    // go through observations one by one
    for(DLIterC<ObservationC> it(obs_list);it;it++) {
      ObservationC obs = it.Data();

      // accumulate information sum
      obs.IncrementLS ( state_vec, A, a );
    }

    return A;
  }

  // Chi-squared residual at latest estimate
  RealT LevenbergMarquardtC::GetResidual() const
  {
    return residual;
  }
}
