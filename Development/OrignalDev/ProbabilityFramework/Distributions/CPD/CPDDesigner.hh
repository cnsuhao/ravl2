// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_CPDDESIGNER_HEADER
#define RAVLPROB_CPDDESIGNER_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Prob/ConditionalProbabilityDistribution.hh"
#include "Ravl/DList.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Base class for conditional probability distributions designers
  class CPDDesignerBodyC
    : public RCBodyVC {
  public:
    CPDDesignerBodyC();
    //: Constructor

    virtual ~CPDDesignerBodyC();
    //: Destructor
    
    virtual ConditionalProbabilityDistributionC CreateCPD(const DListC<Tuple2C<VariablePropositionC,PropositionSetC> >& propositionPairs) const=0;
    //: Create a conditional probability distribution according to the sample of propositions
    //!param: propositionPairs - a sample of propositions pairs, ie dependent value and parent proposition
    //!return: the conditional probability distribution

  };

  //! userlevel=Normal
  //: Base class for conditional probability distributions designers
  //!cwiz:author
  
  class CPDDesignerC
    : public RCHandleC<CPDDesignerBodyC>
  {
  public:
    CPDDesignerC()
    {}
    //: Default constructor makes invalid handle

    ConditionalProbabilityDistributionC CreateCPD(const DListC<Tuple2C<VariablePropositionC,PropositionSetC> >& propositionPairs) const
    { return Body().CreateCPD(propositionPairs); }
    //: Create a conditional probability distribution according to the sample of propositions
    //!param: propositionPairs - a sample of propositions pairs, ie dependent value and parent proposition
    //!return: the conditional probability distribution

  protected:
    CPDDesignerC(CPDDesignerBodyC &bod)
     : RCHandleC<CPDDesignerBodyC>(bod)
    {}
    //: Body constructor. 
    
    CPDDesignerC(const CPDDesignerBodyC *bod)
     : RCHandleC<CPDDesignerBodyC>(bod)
    {}
    //: Body constructor. 
    
    CPDDesignerBodyC& Body()
    { return static_cast<CPDDesignerBodyC &>(RCHandleC<CPDDesignerBodyC>::Body()); }
    //: Body Access. 
    
    const CPDDesignerBodyC& Body() const
    { return static_cast<const CPDDesignerBodyC &>(RCHandleC<CPDDesignerBodyC>::Body()); }
    //: Body Access. 
    
  };

}

#endif
