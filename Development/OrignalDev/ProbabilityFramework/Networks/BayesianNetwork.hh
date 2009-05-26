// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_BAYESIANNETWORK_HEADER
#define RAVLPROB_BAYESIANNETWORK_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"


#include "Ravl/RCHandleV.hh"
#include "Ravl/Prob/ProbabilityDistribution.hh"
#include "Ravl/Prob/PropositionSet.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Base class for bayesian networks
  class BayesianNetworkBodyC
    : public RCBodyVC {
  public:
    BayesianNetworkBodyC();
    //: Constructor

    virtual ~BayesianNetworkBodyC();
    //: Destructor
    
    virtual ProbabilityDistributionC CalculateDistribution(const VariableC& variable, const PropositionSetC& evidence) const=0;
    //: Calculate the a pdf to represent P(Variable|evidence)
    //!param: variable - a random variable that we want the distribution for
    //!param: evidence - a proposition with fixed values for some (or all) evidence variables from the network
    //!return: the probability distribution of Variable given the evidence

    virtual RealT CalculateProbability(const PropositionSetC& evidence) const=0;
    //: Calculate the probability that the particular combination of evidence occurred
    //!param: evidence - a proposition with fixed values for some (or all) evidence variables from the network
    //!return: the probability of the random variables taking the given values

    virtual VariableSetC VariableSet() const=0;
    //: Get the variable set for the network
  };

  //! userlevel=Normal
  //: Base class for bayesian networks
  //!cwiz:author
  
  class BayesianNetworkC
    : public RCHandleC<BayesianNetworkBodyC>
  {
  public:
    BayesianNetworkC()
    {}
    //: Default constructor makes invalid handle

    ProbabilityDistributionC CalculateDistribution(const VariableC& variable, const PropositionSetC& evidence) const
    { return Body().CalculateDistribution(variable, evidence); }
    //: Calculate the a pdf to represent P(Variable|evidence)
    //!param: variable - a random variable that we want the distribution for
    //!param: evidence - a proposition with fixed values for some (or all) evidence variables from the network
    //!return: the probability distribution of Variable given the evidence

    RealT CalculateProbability(const PropositionSetC& evidence) const
    { return Body().CalculateProbability(evidence); }
    //: Calculate the probability that the particular combination of evidence occurred
    //!param: evidence - a proposition with fixed values for some (or all) evidence variables from the network
    //!return: the probability of the random variables taking the given values

    VariableSetC VariableSet() const
    { return Body().VariableSet(); }
    //: Get the variable set for the network

  protected:
    BayesianNetworkC(BayesianNetworkBodyC &bod)
     : RCHandleC<BayesianNetworkBodyC>(bod)
    {}
    //: Body constructor. 
    
    BayesianNetworkC(const BayesianNetworkBodyC *bod)
     : RCHandleC<BayesianNetworkBodyC>(bod)
    {}
    //: Body constructor. 
    
    BayesianNetworkBodyC& Body()
    { return static_cast<BayesianNetworkBodyC &>(RCHandleC<BayesianNetworkBodyC>::Body()); }
    //: Body Access. 
    
    const BayesianNetworkBodyC& Body() const
    { return static_cast<const BayesianNetworkBodyC &>(RCHandleC<BayesianNetworkBodyC>::Body()); }
    //: Body Access. 
    
  };

}

#endif
