#ifndef RAVL_SAMPLESTATE_HEADER
#define RAVL_SAMPLESTATE_HEADER 1
//! rcsid="$Id$"
//! author="Charles Galambos"

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
