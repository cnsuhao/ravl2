// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SAMPLESTATE_HEADER
#define RAVL_SAMPLESTATE_HEADER 1
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlLogic
//! file="Ravl/Logic/DecisionTree/SampleState.hh"

#include "Ravl/PatternRec/SampleDiscrete.hh"
#include "Ravl/Logic/State.hh"

namespace RavlLogicN {

  class SampleStateC
    : public SampleDiscreteC<StateC>
  {
  public:
    SampleStateC()
    {}
    //: Default constructor.
    
  };
  
}


#endif
