// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_RANSACOBSLISTSAMPLING_HEADER
#define RAVLMATH_RANSACOBSLISTSAMPLING_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"
//! example="OrthogonalRegressionTest.cc"

#include "Ravl/RansacObsList.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: RANSAC algorithm class for 2D line fitting
  // RANSAC using a list of observations as the data to be fitted to, and
  // providing a simple randomised sampling and fitting scheme.
  class RansacObsListSamplingC
    : public RansacObsListC
  {
  public:
    RansacObsListSamplingC(DListC<ObservationC> obs_list, UIntT sample_size,
			   RealT chi2_thres);
    //: Constructor for RANSAC with random sampling from an observation list.
    // You must provide the list of observations obs_list, the size of random
    // sample sample_size to take from the list, and the threshold chi2_thres
    // on the residual of each observation (negative log-likelihood) for it
    // to be treated as an inlier.

    StateVectorC SampleSolution();
    //: Generate a solution computed from a RANSAC sample
    // Uses pure random sampling from the observation list, and calls the
    // method FitToSample() to compute the sample solution.

    UIntT SampleVote(StateVectorC &state_vec);
    //: Compute vote (number of inliers) for given sample state vector

    virtual StateVectorC FitToSample(DListC<ObservationC> sample);
    //: Fit parameters to sample of observations
    // Supply this function in a sub-class.

  protected:
    UIntT sample_size; // number of observations making up a sample
    RealT chi2_thres; // threshold on chi-squared residual for inliers

  private:
    DListC<ObservationC> Sample();
    //: Generate random sample of observations
  };
}


#endif
