// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/EvaluateSolution.hh"

namespace RavlN {

  //: Constructor.
  EvaluateSolutionC::EvaluateSolutionC()
  {
  }

  //: Returns the score/vote/likelihood for the given state parameters
  RealT EvaluateSolutionC::SolutionScore(const StateVectorC &state_vec,
					 DListC<ObservationC> &obs_list) const
  {
    RavlAssertMsg(0,"EvaluateSolutionC::SolutionScore(const StateVectorC &, DListC<ObservationC> &) const, Abstract method called ");
    return 0.0;
  }

  //: Returns the observations compatible with the given state parameters
  DListC<ObservationC> EvaluateSolutionC::CompatibleObservations(
					const StateVectorC &state_vec,
					DListC<ObservationC> &obs_list) const
  {
    DListC<ObservationC> empty_obs_list;
    RavlAssertMsg(0,"EvaluateSolutionC::CompatibleObservations(const StateVectorC &, DListC<ObservationC> &) const, Abstract method called ");
    return empty_obs_list;
  }
}
