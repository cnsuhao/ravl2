// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/DecisionTreeLeaf.hh"
#include "Ravl/Logic/Tuple.hh"
#include "Ravl/Logic/NamedLiteral.hh"

namespace RavlLogicN {

  DecisionTreeLeafBodyC::DecisionTreeLeafBodyC()
  {}

  //: Constructor.
  
  DecisionTreeLeafBodyC::DecisionTreeLeafBodyC(const LiteralC &ndecision,const DecisionExamplesC  &nexamples) 
    : DecisionTreeElementBodyC(nexamples),
      decision(ndecision)
  {}

  //: Go through the tree building a rule set.
  
  void DecisionTreeLeafBodyC::BuildRuleSet(const LiteralC &preCond,StateC &ruleSet) const {
    ruleSet.Tell(Tuple(Literal("Rule"),preCond,decision));
  }
  
  //: Dump node in human readable form,
  
  void DecisionTreeLeafBodyC::Dump(ostream &out,IntT level = 0) const {
    Pad(out,level) << "Leaf: " << decision << "\n";
  }
  
}
