/////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Logic/DecisionTreeElement.hh"

namespace RavlLogicN {
  DecisionTreeElementBodyC::DecisionTreeElementBodyC()
  {}
  
  //: Find next level in the decision tree for given 'state'.
  
  DecisionTreeElementC DecisionTreeElementBodyC::Find(const StateC &state) {
    RavlAssertMsg(0,"DecisionTreeElementBodyC::Find(), Abstract method called. ");
    return DecisionTreeElementC();
  }
  

}
