// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_DECISIONTREEBINARY_HEADER
#define RAVLLOGIC_DECISIONTREEBINARY_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/DecisionTree/DecisionTreeBranchBinary.hh"
//! author="Charles Galambos"
//! docentry="Ravl.Logic.Decision Tree"

#include "Ravl/Logic/DecisionTreeBranch.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Decision tree body.
  
  class DecisionTreeBranchBinaryBodyC 
    : public DecisionTreeBranchBodyC
  {
  public:
    DecisionTreeBranchBinaryBodyC();
    //: Default constructor.
    
    DecisionTreeBranchBinaryBodyC(const LiteralC &test);
    //: Construct with a test.
    
    virtual DecisionTreeElementC Find(const StateC &state);
    //: Find next level in the decision tree for given 'state'.

    virtual void BuildRuleSet(const LiteralC &preCond,StateC &ruleSet) const;
    //: Go through the tree building a rule set.
    
    virtual void Dump(ostream &out,IntT level = 0) const;
    //: Dump node in human readable form,
    
    DecisionTreeElementC &TrueChild()
    { return children[1]; }
    //: Access true child.
    
    DecisionTreeElementC &FalseChild()
    { return children[0]; }
    //: Access false child.
    
  protected:
    LiteralC test; // Test for branch.
    DecisionTreeElementC children[2]; // 0-False 1-True.
  };
  
  //! userlevel=Develop
  //: Decision tree.
  
  class DecisionTreeBranchBinaryC 
    : public DecisionTreeBranchC
  {
  public:
    DecisionTreeBranchBinaryC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    DecisionTreeBranchBinaryC(bool)
      : DecisionTreeBranchC(*new DecisionTreeBranchBinaryBodyC())
    {}
    //: Constructor.
    
    DecisionTreeBranchBinaryC(const LiteralC &test)
      : DecisionTreeBranchC(*new DecisionTreeBranchBinaryBodyC(test))
    {}
    //: Construct with a test.
    
  protected:
    DecisionTreeBranchBinaryC(DecisionTreeBranchBinaryBodyC &bod)
      : DecisionTreeBranchC(bod)
      {}
    //: Body constructor.
    
    DecisionTreeBranchBinaryBodyC &Body()
    { return static_cast<DecisionTreeBranchBinaryBodyC &>(DecisionTreeElementC::Body()); }
    //: Access body.
    
    const DecisionTreeBranchBinaryBodyC &Body() const
    { return static_cast<const DecisionTreeBranchBinaryBodyC &>(DecisionTreeElementC::Body()); }
    //: Access body.
    
  public:
    DecisionTreeElementC &TrueChild()
    { return Body().TrueChild(); }
    //: Access true child.
    
    DecisionTreeElementC &FalseChild()
    { return Body().FalseChild(); }
    //: Access false child.
    
  };
  
}

#endif
