// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOptimise

#include "Ravl/StoredState.hh"

namespace RavlN {

  //: Constructor for optimisation base class
  StoredStateC::StoredStateC()
  {
    state_vec = StateVectorC();
  }

  //: Constructor for optimisation base class
  StoredStateC::StoredStateC(StateVectorC &state_vec_init)
  {
    state_vec = state_vec_init.Copy();
  }

  //: Solution parameters x for sample with lowest residual
  const StateVectorC & StoredStateC::GetSolution() const {
    return state_vec;
  }
}
