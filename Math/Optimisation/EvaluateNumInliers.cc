// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/EvaluateNumInliers.hh"

namespace RavlN {

  //: Constructor.
  EvaluateNumInliersC::EvaluateNumInliersC(RealT nchi2_thres,
					   RealT ncompat_chi2_thres)
    : EvaluateSolutionC::EvaluateSolutionC()
  {
    chi2_thres = nchi2_thres;
    compat_chi2_thres = (ncompat_chi2_thres == 0.0)
                        ? chi2_thres : ncompat_chi2_thres;
  }

  //: Returns the number of inliers for the given state parameters
  RealT EvaluateNumInliersC::SolutionScore(const StateVectorC &state_vec,
					   DListC<ObservationC> &obs_list) const
  {
    UIntT total_vote=0;
    for(DLIterC<ObservationC> it(obs_list);it;it++)
      // only use observations that have not already been selected
      if(!it.Data().GetSelected()) {
	// compute the residual
	RealT residual = it.Data().NonRobustResidual(state_vec);

	// increment counter if residual is within threshold
	if ( residual < chi2_thres )
	  total_vote++;
      }

    return (RealT)total_vote;
  }

  //: Returns the observations compatible with the given state parameters
  DListC<ObservationC> EvaluateNumInliersC::CompatibleObservations(
					const StateVectorC &state_vec,
					DListC<ObservationC> &obs_list) const
  {
    DListC<ObservationC> compatible_list;

    for(DLIterC<ObservationC> it(obs_list);it;it++) {
      // compute the residual
      RealT residual = it.Data().NonRobustResidual(state_vec);

      // add to list if residual is within threshold
      if ( residual < compat_chi2_thres )
	compatible_list.InsLast(it.Data());
    }

    return compatible_list;
  }
}
