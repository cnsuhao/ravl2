///////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Logic/DecisionTreeBranchBinary.hh"
#include "Ravl/Logic/State.hh"

namespace RavlLogicN {

  DecisionTreeBranchBinaryBodyC::DecisionTreeBranchBinaryBodyC()
  {}
  
  //: Find next level in the decision tree for given 'state'.
  
  DecisionTreeElementC DecisionTreeBranchBinaryBodyC::Find(const StateC &state) {
    return children[state.Ask(test)];
  }
  
}
