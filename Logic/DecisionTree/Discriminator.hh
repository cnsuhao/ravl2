// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_DISCRIMINATOR_HEADER
#define RAVLLOGIC_DISCRIMINATOR_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/DecisionExamples.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/Logic/SampleLiteral.hh"
#include "Ravl/Logic/SampleState.hh"

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
    
    virtual LiteralC BestDiscriminator(const DataSet2C<SampleStateC,SampleLiteralC> &data);
    //: Choose the best distriminator to seperate the decisions made in 'data'. 
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

    DiscriminatorC(bool)
      : RCHandleC<DiscriminatorBodyC>(*new DiscriminatorBodyC())
    {}
    //: Construct a default discriminator.
    
  protected:
    DiscriminatorC(DiscriminatorBodyC &bod)
      : RCHandleC<DiscriminatorBodyC>(bod)
    {}
    //: Body constructor.
    
    DiscriminatorBodyC &Body()
    { return RCHandleC<DiscriminatorBodyC>::Body(); }
    //: Access body.
    
    const DiscriminatorBodyC &Body() const
    { return RCHandleC<DiscriminatorBodyC>::Body(); }
    //: Access body.
    
  public:
    LiteralC Distinguish(const DecisionExamplesC &set1,const DecisionExamplesC &set2)
    { return Body().Distinguish(set1,set2); }
    //: Distinguish between the the two sets of examples.
    
    LiteralC BestDiscriminator(const DecisionExamplesC &set)
    { return Body().BestDiscriminator(set); }
    //: Choose the best distriminator to seperate the decisions made in 'set'. 
    
    LiteralC BestDiscriminator(const DataSet2C<SampleStateC,SampleLiteralC> &data)
    { return Body().BestDiscriminator(data); }
    //: Choose the best distriminator to seperate the decisions made in 'data'. 
    
  };

}

#endif
