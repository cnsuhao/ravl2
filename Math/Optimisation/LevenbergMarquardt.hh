// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_LEVENBERGMARQUARDT_HEADER
#define RAVLMATH_LEVENBERGMARQUARDT_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"
//! example="OrthogonalRegressionTest.cc;QuadraticFitTest.cc;Homography2dFitTest.cc"

#include "Observation.hh"

#include "Ravl/DList.hh"
#include "Ravl/Vector.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/MatrixRS.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: Levenberg-Marquardt algorithm class
  // This is a generic implementation of Levenberg-Marquardt least-squares
  // minimisation. The algorithm is described mathematically in a separate
  // document
  // <a href="/user/cvsspst/ees1pm/Ravl/doc/levmarq/levmarq.html">here</a>.
  // <p>
  // This class contains a constructor for initialising the algorithm, a method
  // for a applying a damped Levenberg-Marquardt iteration, which should be
  // successively applied until convergence, and methods for returning the
  // state and covariance results.
  class LevenbergMarquardtC {

  public:
    LevenbergMarquardtC(StateVectorC &state_vec_init,
			DListC<ObservationC> obs_list);
    //: Constructor.
    // Initialises the Levenberg-Marquardt algorithm with the given state
    // parameter vector state_vec_init. The observation list obs_list is used
    // to initialise the least-squares residual.

    bool Iteration ( DListC<ObservationC> obs_list, RealT lambda );
    //: Apply an iteration
    // Process observations in the provided list (obs_list) to build the
    // inverse covariance matrix A and vector a in the
    // <a href="/user/cvsspst/ees1pm/Ravl/doc/levmarq/levmarq.html#LM_update">state update equation</a>,
    // apply damping by adding lambda*identity to A, and update the state
    // vector x.
    // <p>
    // Returns true if the iteration succeeded in reducing the residual,
    // false otherwise. In the latter case, the state vector is not adjusted,
    // and the user program should reduce the value of lambda before calling
    // this method again.

    const VectorC &SolutionVector() const;
    //: Latest estimate of solution parameters x

    const MatrixRSC &InverseCovarianceMatrix(DListC<ObservationC> obs_list);
    //: Inverse covariance matrix of solution
    // This is the matrix A in the <a href="/user/cvsspst/ees1pm/Ravl/doc/levmarq/levmarq.html#LM_update">state update equation</a>,
    // but computed without any damping, i.e. lambda set to zero.
    // The observation list is reprocessed to produce the matrix.
    // This will normally be called once, after convergence has been achieved.
    // <p>
    // If all gauge freedoms have been dealt with using gauge condition
    // observations (see e.g. the class StateVectorLine2dC), then this matrix
    // should be invertible should the covariance matrix A^-1 be required.
    // However there may be data-dependent conditioning issues, and it is
    // safer to leave the inversion for the user program.

    RealT Residual() const;
    //: Get stored Chi-squared residual for latest state estimate
    // This is the
    // <a href="/user/cvsspst/ees1pm/Ravl/doc/levmarq/levmarq.html#chi2-def">error function</a>
    // evaluated for the latest state estimate x.

  private:
    StateVectorC state_vec; // state parameter vector
    MatrixRSC A; // Inverse covariance matrix
    bool A_updated; // Whether A is up to date
    MatrixRSC Ainv; // Covariance matrix
    bool Ainv_updated; // Whether Ainv is up to date
    RealT residual; // current minimum value of Chi-squared residual

    RealT ComputeResidual(DListC<ObservationC> obs_list) const;
    //: Compute least-squares residual

  public:
    const StateVectorC& GetStateVec() const;
    //: Get handle to state vector object
  };
}


#endif
