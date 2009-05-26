// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_CPDDESIGNERCONTINUOUSDISCRETE1_HEADER
#define RAVLPROB_CPDDESIGNERCONTINUOUSDISCRETE1_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/CPDDesigner.hh"
#include "Ravl/Prob/VariableContinuous.hh"
#include "Ravl/Prob/VariableDiscrete.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: CPD designer class for continuous variable with single parent discrete variable
  class CPDDesignerContinuousDiscrete1BodyC
    : public CPDDesignerBodyC {
  public:
    CPDDesignerContinuousDiscrete1BodyC();
    //: Constructor

    virtual ~CPDDesignerContinuousDiscrete1BodyC();
    //: Destructor
    
    virtual ConditionalProbabilityDistributionC CreateCPD(const DListC<Tuple2C<VariablePropositionC,PropositionSetC> >& propositionPairs) const;
    //: Create a conditional probability distribution according to the sample of propositions
    //!param: propositionPairs - a sample of propositions pairs, ie dependent value and parent proposition
    //!return: the conditional probability distribution

  private:
    static VariableContinuousC CheckDependentVariable(const VariableContinuousC& dependentVariable);
    //: Check the dependent variable

    static VariableDiscreteC CheckParentVariable(const VariableDiscreteC& parentVariable);
    //: Check the parent variable

  };

  //! userlevel=Normal
  //: CPD designer class for continuous variable with single parent discrete variable
  //!cwiz:author
  
  class CPDDesignerContinuousDiscrete1C
    : public CPDDesignerC
  {
  public:
    CPDDesignerContinuousDiscrete1C()
    {}
    //: Default constructor makes invalid handle

    CPDDesignerContinuousDiscrete1C(const CPDDesignerC& pdf)
      : CPDDesignerC(dynamic_cast<const CPDDesignerContinuousDiscrete1BodyC *>(BodyPtr(pdf)))
    {}
    //: Upcast constructor
    // Creates an invalid handle if types don't match
    
    static CPDDesignerContinuousDiscrete1C GetInstance();
    //: Get an instance of the designer

  private:
    CPDDesignerContinuousDiscrete1C(bool)
      : CPDDesignerC(new CPDDesignerContinuousDiscrete1BodyC())
    {}
    //: Private constructor
    
  private:
    static CPDDesignerContinuousDiscrete1C m_instance;
    //: The instance of the designer 

  };

}

#endif
