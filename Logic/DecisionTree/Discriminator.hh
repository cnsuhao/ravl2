#ifndef RAVLLOGIC_DISCRIMINATOR_HEADER
#define RAVLLOGIC_DISCRIMINATOR_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Logic/DecisionExamples.hh"
#include "Ravl/RefCounter.hh"

namespace RavlLogicN {
  using namespace RavlN;
  
  //! userlevel=Normal
  //: Tool to find an expression which discriminates between sets of states.
  
  class DiscriminatorBodyC
    : public RCBodyVC
  {
  public:
    DiscriminatorBodyC()
    {}
    //: Default constructor.
    
    virtual LiteralC Distinguish(const DecisionExamplesC &set1,const DecisionExamplesC &set2);
    //: Distinguish between the the two sets of examples.
    
    virtual LiteralC BestDiscriminator(const DecisionExamplesC &set);
    //: Choose the best distriminator to seperate the decisions made in 'set'. 
  protected:
  };

  //! userlevel=Normal
  //: Tool to find an expression which discriminates between sets of states.
  
  class DiscriminatorC
    : public RCHandleC<DiscriminatorBodyC>
  {
  public:
    DiscriminatorC()
    {}
    //: Constructor.
    
    LiteralC Distinguish(const DecisionExamplesC &set1,const DecisionExamplesC &set2)
    { return Body().Distinguish(set1,set2); }
    //: Distinguish between the the two sets of examples.
    
    LiteralC BestDiscriminator(const DecisionExamplesC &set)
    { return Body().Distinguish(set1,set2); }
    //: Choose the best distriminator to seperate the decisions made in 'set'. 
    
  };

}

#endif
