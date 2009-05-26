// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_BAYESIANNETWORKSIMPLE_HEADER
#define RAVLPROB_BAYESIANNETWORKSIMPLE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"


#include "Ravl/Prob/BayesianNetworkAbstract.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Simple (inefficient) implementation of a bayesian network
  
  class BayesianNetworkSimpleBodyC
    : public BayesianNetworkAbstractBodyC {
  public:
    BayesianNetworkSimpleBodyC(const RCHashC<VariableC,ConditionalProbabilityDistributionC>& nodeCPDs);
    //: Constructor

    virtual ~BayesianNetworkSimpleBodyC();
    //: Destructor
    
    virtual ProbabilityDistributionC CalculateDistribution(const VariableC& variable, const PropositionSetC& evidence) const;
    //: Calculate the a pdf to represent P(Variable|evidence)
    //!param: variable - a random variable that we want the distribution for
    //!param: evidence - a proposition with fixed values for some (or all) evidence variables from the network
    //!return: the probability distribution of Variable given the evidence

    virtual RealT CalculateProbability(const PropositionSetC& evidence) const;
    //: Calculate the probability that the particular combination of evidence occurred
    //!param: evidence - a proposition with fixed values for some (or all) evidence variables from the network
    //!return: the probability of the random variables taking the given values

  private:
    RealT EnumerateAll(const DListC<VariableC>& vars, const PropositionSetC& evidence) const;

  };

  //! userlevel=Normal
  //: Simple (inefficient) implementation of a bayesian network
  //!cwiz:author
  
  class BayesianNetworkSimpleC
    : public BayesianNetworkAbstractC
  {
  public:
    BayesianNetworkSimpleC()
    {}
    //: Default constructor makes invalid handle

    BayesianNetworkSimpleC(const RCHashC<VariableC,ConditionalProbabilityDistributionC>& nodeCPDs)
      : BayesianNetworkAbstractC(new BayesianNetworkSimpleBodyC(nodeCPDs))
    {}
    //: Constructor
    //!param: nodeCPDs - each node and its conditional probability distribution

  protected:
    BayesianNetworkSimpleC(BayesianNetworkSimpleBodyC &bod)
     : BayesianNetworkAbstractC(bod)
    {}
    //: Body constructor. 
    
    BayesianNetworkSimpleC(const BayesianNetworkSimpleBodyC *bod)
     : BayesianNetworkAbstractC(bod)
    {}
    //: Body constructor. 
    
    BayesianNetworkSimpleBodyC& Body()
    { return static_cast<BayesianNetworkSimpleBodyC &>(BayesianNetworkAbstractC::Body()); }
    //: Body Access. 
    
    const BayesianNetworkSimpleBodyC& Body() const
    { return static_cast<const BayesianNetworkSimpleBodyC &>(BayesianNetworkAbstractC::Body()); }
    //: Body Access. 
    
  };

}

#endif
