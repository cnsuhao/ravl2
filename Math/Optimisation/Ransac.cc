// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/Ransac.hh"

namespace RavlN {

  //: Constructor for RANSAC
  RansacC::RansacC(ObservationManagerC &nobs_manager,
		   FitToSampleC &nmodel_fitter,
		   EvaluateSolutionC &nevaluator)
    : StoredStateC::StoredStateC(),
		    obs_manager(nobs_manager),
		    model_fitter(nmodel_fitter),
		    evaluator(nevaluator)
  {
    highest_vote = DBL_MIN;
  }

  //: Generate sample, compute vote and update best solution and vote
  bool RansacC::ProcessSample(UIntT min_num_constraints)
  {
    // reset "selected" flags
    obs_manager.UnselectAllObservations();

    // generate sample
    DListC<ObservationC> sample = obs_manager.RandomSample(min_num_constraints);

    // fit model
    StateVectorC sv = model_fitter.FitModel(sample);

    // generate list of observations to be evaluated
    DListC<ObservationC> obs_list = obs_manager.ObservationList(sv);
    RealT new_vote = evaluator.SolutionScore(sv, obs_list);

    if ( new_vote > highest_vote ) {
      state_vec = sv.Copy();
      highest_vote = new_vote;
    }

    return true;
  }

  //: Return the highest vote found so far 
  RealT RansacC::GetHighestVote() const
  {
    return highest_vote;
  }
}
