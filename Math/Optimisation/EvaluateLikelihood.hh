// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_EVALUATELIKELIHOOD_HEADER
#define RAVLMATH_EVALUATELIKELIHOOD_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"

#include <Ravl/EvaluateSolution.hh>

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: Solution evaluation class
  // This class evaluates a proposed solution state vector by summing the
  // log-likelihoods of each observation
  class EvaluateLikelihoodC
    : public EvaluateSolutionC
  {
  public:
    EvaluateLikelihoodC(RealT chi2_thres=0.0);
    //: Constructor.
    // The chi2_thres parameter is used as a threshold on the non-robust
    // negative log-likelihood when selecting observations compatible with
    // the best model. If you only want the model parameters and don't care
    // about the selected obsrvations, pass an empty argument list.

    virtual RealT SolutionScore(const StateVectorC &state_vec,
				DListC<ObservationC> &obs_list) const;
    //: Returns the log likelihood for the given state parameters

    DListC<ObservationC> CompatibleObservations(
					const StateVectorC &state_vec,
					DListC<ObservationC> &obs_list) const;
    //: Returns the observations compatible with the given state parameters

  private:
    RealT chi2_thres; // Threshold on normalised residual
  };
}

#endif
