#ifndef RAVL_SAMPLELITERAL_HEADER
#define RAVL_SAMPLELITERAL_HEADER 1
//! rcsid="$Id$"
//! author="Charles Galambos"

#include "Ravl/PatternRec/SampleDiscrete.hh"
#include "Ravl/Logic/Literal.hh"
#include "Ravl/HSet.hh"

namespace RavlLogicN {
  
  class SampleLiteralC
    : public SampleDiscreteC<LiteralC>
  {
  public:
    SampleLiteralC()
    {}
    //: Default constructor.

    HSetC<LiteralC> Components() const;
    //: Make a list of all LiteralC and sub LiteralC's in the sample.
    
  };
  
}


#endif
