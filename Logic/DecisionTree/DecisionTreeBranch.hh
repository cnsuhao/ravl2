#ifndef RAVLLOGIC_DECISIONTREBRANCH_HEADER
#define RAVLLOGIC_DECISIONTREBRANCH_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Logic/DecisionTreeElement.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Decision tree body.
  
  class DecisionTreeBranchBodyC 
    : public DecisionTreeElementBodyC
  {
  public:
    DecisionTreeBranchBodyC();
    //: Default constructor.
    
    virtual void Dump(ostream &out,IntT level = 0) const;
    //: Dump node in human readable form,
    
  protected:
    
  };
  
  //! userlevel=Develop
  //: Decision tree.
  
  class DecisionTreeBranchC 
    : public DecisionTreeElementC
  {
  public:
    DecisionTreeBranchC()
      {}
    //: Default constructor.
    // creates an invalid handle.
    
  protected:
    DecisionTreeBranchC(DecisionTreeBranchBodyC &bod)
      : DecisionTreeElementC(bod)
    {}
    //: Body constructor.
    
    DecisionTreeBranchBodyC &Body()
    { return static_cast<DecisionTreeBranchBodyC &>(DecisionTreeElementC::Body()); }
    //: Access body.

    const DecisionTreeBranchBodyC &Body() const
    { return static_cast<const DecisionTreeBranchBodyC &>(DecisionTreeElementC::Body()); }
    //: Access body.
    
  public:
    
  };
  
}

#endif
