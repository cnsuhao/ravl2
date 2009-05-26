// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_CPDABSTRACT_HEADER
#define RAVLPROB_CPDABSTRACT_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/ConditionalProbabilityDistribution.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Abstract implementation for conditional probability distributions containing common domain
  class CPDAbstractBodyC
    : public ConditionalProbabilityDistributionBodyC {
  public:
    CPDAbstractBodyC(const VariableC& variable, const VariableSetC& parentVariableSet);
    //: Constructor
    //!param: variable - the conditioned random variable
    //!param: parentVariableSet - the conditioning parent variables

    CPDAbstractBodyC(const VariableC& variable, const VariableC& parentVariable);
    //: Constructor
    //!param: variable - the conditioned random variable
    //!param: parentVariable - single conditioning parent variable

    virtual ~CPDAbstractBodyC();
    //: Destructor
    
    virtual RealT ConditionalProbability(const VariablePropositionC& value, const PropositionSetC& parentValues) const;
    //: Calculate the conditional probability P(value|parentValues)
    //!param: value - a value for the random variable
    //!param: parentValues - a proposition with fixed values for some (or all) parent variables
    //!return: the conditional probability of the proposition
    // This is the sum of probabilities for the subset of variable values

    virtual VariableC Variable() const;
    //: Get the random variable that is the subject of the distribution

    virtual VariableSetC ParentVariableSet() const;
    //: Get the domain for the parent variables

  private:
    void SetVariable(const VariableC& variable);
    //: Set the random variable

    void SetParentVariableSet(const VariableSetC& parentVariableSet);
    //: Set the domain

    void SetSingleParentVariable(const VariableC& parentVariable);
    //: Sets up a domain with a single parent variable

  private:
    VariableC m_variable;
    //: The random variable

    VariableSetC m_parentVariableSet;
    //: The domain
  };

  //! userlevel=Normal
  //: Abstract implementation for conditional probability distributions containing common domain
  //!cwiz:author
  
  class CPDAbstractC
    : public ConditionalProbabilityDistributionC
  {
  public:
    CPDAbstractC()
    {}
    //: Default constructor makes invalid handle

  protected:
    CPDAbstractC(CPDAbstractBodyC &bod)
     : ConditionalProbabilityDistributionC(bod)
    {}
    //: Body constructor. 
    
    CPDAbstractC(const CPDAbstractBodyC *bod)
     : ConditionalProbabilityDistributionC(bod)
    {}
    //: Body constructor. 
    
    CPDAbstractBodyC& Body()
    { return static_cast<CPDAbstractBodyC &>(ConditionalProbabilityDistributionC::Body()); }
    //: Body Access. 
    
    const CPDAbstractBodyC& Body() const
    { return static_cast<const CPDAbstractBodyC &>(ConditionalProbabilityDistributionC::Body()); }
    //: Body Access. 
    
  };

}

#endif
