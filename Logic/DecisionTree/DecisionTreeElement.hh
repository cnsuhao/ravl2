// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_DECISIONTREEELEMENT_HEADER
#define RAVLLOGIC_DECISIONTREEELEMENT_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/RefCounter.hh"
#include "Ravl/Logic/DecisionExamples.hh"

namespace RavlLogicN {
  class DecisionTreeElementC;

  //! userlevel=Develop
  //: Decision tree body.
  
  class DecisionTreeElementBodyC 
    : public RCBodyVC
  {
  public:
    DecisionTreeElementBodyC();
    //: Default constructor.

    DecisionTreeElementBodyC(const DecisionExamplesC &nexamples);
    //: Constructor.
    
    DecisionExamplesC &Examples()
    { return examples; }
    //: Access examples of decisions below this node.
    
    virtual DecisionTreeElementC Find(const StateC &state);
    //: Find next level in the decision tree for given 'state'.
    
    virtual bool IsLeaf() const
    { return false; }
    //: Is this a leaf in the decision tree ?
    
    virtual void Dump(ostream &out,IntT level = 0) const;
    //: Dump node in human readable form,
    
    virtual void BuildRuleSet(const LiteralC &preCond,StateC &ruleSet) const;
    //: Go through the tree building a rule set.
    
  protected:
    static ostream &Pad(ostream &out,int level);
    //: Pad line to given level.
    // Used in dump.
    
    DecisionExamplesC examples; // Examples of decisions.
  };
  
  //! userlevel=Develop
  //: Decision tree.
  // Base class for nodes in the decision tree. Both Branch's and
  // Leaves are derived from this class.
  
  class DecisionTreeElementC 
    : public RCHandleC<DecisionTreeElementBodyC>
  {
  public:
    DecisionTreeElementC()
      {}
    //: Default constructor.
    // creates an invalid handle.

  protected:
    DecisionTreeElementC(DecisionTreeElementBodyC &bod)
      : RCHandleC<DecisionTreeElementBodyC>(bod)
      {}
    //: Body constructor.
    
    DecisionTreeElementBodyC &Body()
    { return RCHandleC<DecisionTreeElementBodyC>::Body(); }
    //: Access body.
    
    const DecisionTreeElementBodyC &Body() const
    { return RCHandleC<DecisionTreeElementBodyC>::Body(); }
    //: Access body.
    
  public:
    DecisionExamplesC &Examples()
    { return Body().Examples(); }
    //: Access examples of all decisions below this node.
    
    DecisionTreeElementC Find(const StateC &state)
    { return Body().Find(state); }
    //: Find next level in the decision tree for given 'state'.
    
    bool IsLeaf() const
    { return Body().IsLeaf(); }
    //: Is this a leaf in the decision tree ?
    
    void BuildRuleSet(const LiteralC &preCond,StateC &ruleSet) const
    { return Body().BuildRuleSet(preCond,ruleSet); }
    //: Go through the tree building a rule set.
    
    void Dump(ostream &out,IntT level = 0) const
    { Body().Dump(out,level); }
    //: Dump node in human readable form,


  };
  
}

#endif
