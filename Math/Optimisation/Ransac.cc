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
  RansacC::RansacC()
    : StoredStateC::StoredStateC()
  {
    vote = 0;
  }

  //: Generate a solution computed from a RANSAC sample
  StateVectorC RansacC::SampleSolution() {
    RavlAssertMsg(0,"RansacC::SampleSolution(), Abstract method called ");
    return StateVectorC();
  }

  //: Compute vote for given sample state vector
  UIntT RansacC::SampleVote(StateVectorC &state_vec) {
    RavlAssertMsg(0,"RansacC::SampleVote(StateVectorC &state_vec), Abstract method called ");
    return UINT_MAX;
  }
 
  //: Generate sample, compute vote and update best solution and vote
  bool RansacC::ProcessSample() {
    StateVectorC sv = SampleSolution();
    UIntT new_vote = SampleVote(sv);

    if ( new_vote > vote ) {
      state_vec = sv.Copy();
      vote = new_vote;
    }

    return true;
  }

  //: Return the highest vote found so far 
  RealT RansacC::GetVote() const {
    return vote;
  }
}
