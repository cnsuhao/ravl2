// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_HIDDENMARKOVMODEL_HEADER
#define RAVL_HIDDENMARKOVMODEL_HEADER
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlHMM
//! docentry="Ravl.Math.Signals"

#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: Hidden Markov Model
  // 1st order hidden markov model.
  
  class HiddenMarkovModelC {
  public:
    HiddenMarkovModelC()
    {}
    //: Default contructor.
    
    HiddenMarkovModelC(const MatrixC &nTransition,const MatrixC &nConfusion);
    //: Contructor.
    
    MatrixC &Transition()
    { return transition; }
    //: Access transition matrix.
    
    MatrixC &Confusion()
    { return confusion; }
    //: Accesss confusion matrix
    
    VectorC Forward(const VectorC &state,const VectorC &observation);
    //: Compute the probabilty of next state, given the current state and an observation.
    
    RealT Viterbi(const SArray1dC<VectorC> &observations,const VectorC &initState,SArray1dC<UIntT> &path);
    //: Given a sequence of observations find the most likely path through the states.
    
  protected:
    MatrixC transition;
    MatrixC confusion;
  };
}

#endif
