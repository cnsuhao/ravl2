///////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Logic/DecisionTreeBase.hh"
#include "Ravl/Logic/DecisionTreeLeaf.hh"

namespace RavlLogicN {
  
  //: Default constructor.
  DecisionTreeBaseBodyC::DecisionTreeBaseBodyC()
  {}

  //: Find the decision for given 'state'.
  
  DecisionTreeLeafC DecisionTreeBaseBodyC::Find(const StateC &state) {
    DecisionTreeElementC at = root;
    while(at.IsValid()) {
      at = at.Find(state);
      if(at.IsLeaf())
	return DecisionTreeLeafC(at);
    }
    RavlAssert(0); // Should never fail.
    return DecisionTreeLeafC(); // Failed.
  }
  
  //: Add a new example to the tree.
  
  bool DecisionTreeBaseBodyC::Add(const StateC &state,const LiteralC &decision) {
    DecisionTreeElementC next,at = root;
    while(at.IsValid()) {
      next = at.Find(state);
      if(next.IsLeaf()) {
	DecisionTreeLeafC leaf(next);
	if(leaf.Decision() == decision) {
	  leaf.Examples().AddExample(state,decision);
	  return true; // Already 
	}
	// Need to replace the leaf.
	//discriminator.Distinguish( 
      }
      next = at;
    }
    root = DecisionTreeLeafC(state,decision);
    return false;
  }

}
