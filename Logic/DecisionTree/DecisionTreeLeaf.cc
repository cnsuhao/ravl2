
#include "Ravl/Logic/DecisionTreeLeaf.hh"

namespace RavlLogicN {

  DecisionTreeLeafBodyC::DecisionTreeLeafBodyC()
  {}

  //: Constructor.
  DecisionTreeLeafBodyC::DecisionTreeLeafBodyC(const StateC &state,const LiteralC &ndecision) 
    : decision(ndecision)
  {
    Examples().AddExample(state,ndecision);
  }
  
}
