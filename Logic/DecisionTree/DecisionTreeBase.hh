#ifndef RAVLLOGIC_DECISIONTREEBASE_HEADER
#define RAVLLOGIC_DECISIONTREEBASE_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Logic/DecisionTreeElement.hh"
#include "Ravl/Logic/DecisionTreeLeaf.hh"
#include "Ravl/Logic/Discriminator.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Decision tree body.
  
  class DecisionTreeBaseBodyC 
    : public RCBodyC
  {
  public:
    DecisionTreeBaseBodyC();
    //: Default constructor.
    
    DecisionTreeLeafC Find(const StateC &state);
    //: Find the decision for given 'state'.
    
    bool Add(const StateC &state,const LiteralC &decision);
    //: Add a new example to the tree.
    
  protected:
    DiscriminatorC discriminator; // Used in building the tree.
    DecisionTreeElementC root; // Root of tree.    
  };
  
  //! userlevel=Develop
  //: Decision tree.
  
  class DecisionTreeBaseC 
    : public RCHandleC<DecisionTreeBaseBodyC>
  {
  public:
    DecisionTreeBaseC()
      {}
    //: Default constructor.
    // creates an invalid handle.
    
  protected:
    DecisionTreeBaseC(DecisionTreeBaseBodyC &bod)
      : RCHandleC<DecisionTreeBaseBodyC>(bod)
      {}
    //: Body constructor.
    
    DecisionTreeBaseBodyC &Body()
    { return RCHandleC<DecisionTreeBaseBodyC>::Body(); }
    //: Access body.

    const DecisionTreeBaseBodyC &Body() const
    { return RCHandleC<DecisionTreeBaseBodyC>::Body(); }
    //: Access body.
    
  public:
    
    DecisionTreeLeafC Find(const StateC &state)
    { return Body().Find(state); }
    //: Find the decision for given 'state'.
    
    bool Add(const StateC &state,const LiteralC &decision)
    { return Body().Add(state,decision); }
    //: Add a new example to the tree.

  };
  
}

#endif
