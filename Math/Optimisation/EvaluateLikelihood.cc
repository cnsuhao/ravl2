// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOptimise

#include "Ravl/EvaluateLikelihood.hh"

namespace RavlN {

  //: Constructor.
  EvaluateLikelihoodC::EvaluateLikelihoodC(RealT nchi2_thres)
  {
    chi2_thres = nchi2_thres;
  }

  //: Returns the log likelihood for the given state parameters
  RealT EvaluateLikelihoodC::SolutionScore(const StateVectorC &state_vec,
					   DListC<ObservationC> &obs_list) const
  {
    RealT total_loglikelihood=0.0;
    for(DLIterC<ObservationC> it(obs_list);it;it++)
      // only use observations that have not already been selected
      if(!it.Data().GetSelected())
	// compute the residual and decrement likelihood with it
	total_loglikelihood -= it.Data().Residual(state_vec);

    return total_loglikelihood;
  }

  //: Returns the observations compatible with the given state parameters
  DListC<ObservationC> EvaluateLikelihoodC::CompatibleObservations(
					const StateVectorC &state_vec,
					DListC<ObservationC> &obs_list) const
  {
    DListC<ObservationC> compatible_list;

    for(DLIterC<ObservationC> it(obs_list);it;it++) {
      // compute the residual
      RealT residual = it.Data().NonRobustResidual(state_vec);

      // add to list if residual is within threshold
      if ( residual < chi2_thres )
	compatible_list.InsLast(it.Data());
    }

    return compatible_list;
  }
}
