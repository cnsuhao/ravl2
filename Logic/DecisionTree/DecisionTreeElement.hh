#ifndef RAVLLOGIC_DECISIONTREEELEMENT_HEADER
#define RAVLLOGIC_DECISIONTREEELEMENT_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

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
    
    DecisionExamplesC &Examples()
    { return examples; }
    //: Access examples of decisions below this node.
    
    virtual DecisionTreeElementC Find(const StateC &state);
    //: Find next level in the decision tree for given 'state'.
    
    virtual bool IsLeaf() const
    { return false; }
    //: Is this a leaf in the decision tree ?
    
  protected:
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
  };
  
}

#endif
