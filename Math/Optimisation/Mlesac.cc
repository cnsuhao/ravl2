// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/Mlesac.hh"
#include "Ravl/StdConst.hh"

namespace RavlN {

  //: Constructor for maximum likelihood RANSAC (MLESAC)
  MlesacC::MlesacC()
    : StoredStateC::StoredStateC()
  {
    likelihood = DBL_MAX; // maxReal
  }

  //: Generate a solution computed from a MLESAC sample
  StateVectorC MlesacC::SampleSolution() {
    RavlAssertMsg(0,"MlesacC::SampleSolution(), Abstract method called ");
    return StateVectorC();
  }

  //: Compute negative log likelihood for given sample state vector
  RealT MlesacC::SampleLikelihood(StateVectorC &state_vec) {
    RavlAssertMsg(0,"MlesacC::SampleLikelihood(StateVectorC &state_vec), Abstract method called ");
    return -1.0;
  }
 
  //: Generate sample, compute likelihood and update best solution
  bool MlesacC::ProcessSample() {
    StateVectorC sv = SampleSolution();
    RealT new_likelihood = SampleLikelihood(sv);

    if ( new_likelihood < likelihood ) {
      state_vec = sv.Copy();
      likelihood = new_likelihood;
    }

    return true;
  }

  //: Return the lowest likelihood found so far 
  RealT MlesacC::GetLikelihood() const {
    return likelihood;
  }
}
