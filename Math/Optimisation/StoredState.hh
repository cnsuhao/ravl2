// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_STOREDSTATE_HEADER
#define RAVLMATH_STOREDSTATE_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation"
//! lib=RavlOptimise

#include <Ravl/StateVector.hh>

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: This class is the base class for optimisation algorithm classes
  // It stores a state vector x of parameters.
  class StoredStateC {

  public:
    StoredStateC();
    //: Default constructor for optimisation base class

    StoredStateC(StateVectorC &state_vec_init);
    //: Constructor for optimisation base class

  protected:
    StateVectorC state_vec; // state parameter vector

  public:
    inline const StateVectorC &GetSolution() const
    { return state_vec; }
    //: Solution parameters x for sample with lowest residual
  };
}


#endif
