///////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Logic/DecisionTreeBranch.hh"

namespace RavlLogicN {

  DecisionTreeBranchBodyC::DecisionTreeBranchBodyC()
  {}
  
  //: Dump node in human readable form,
  
  void DecisionTreeBranchBodyC::Dump(ostream &out,IntT level = 0) const {
    cerr << "DecisionTreeBranchBodyC::Dump(), Abstract method called \n";
  }
  
}
