// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_PROBABILITYDISTRIBUTION_HEADER
#define RAVLPROB_PROBABILITYDISTRIBUTION_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Prob/VariableProposition.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Base class for probability distributions
  class ProbabilityDistributionBodyC
    : public RCBodyVC {
  public:
    ProbabilityDistributionBodyC();
    //: Constructor

    virtual ~ProbabilityDistributionBodyC();
    //: Destructor
    
    virtual RealT MeasureProbability(const VariablePropositionC& value) const=0;
    //: Calculate the probability that the variable takes the specified value
    //!param: value - a value for the variable
    //!return: the probability that the variable takes the specified value

    virtual VariableC Variable() const=0;
    //: Get the variable for the probability distribution
    
    virtual StringC ToString() const=0;
    //: Get a string representation of the distribution
  };

  //! userlevel=Normal
  //: Base class for probability distributions
  //!cwiz:author
  
  class ProbabilityDistributionC
    : public RCHandleC<ProbabilityDistributionBodyC>
  {
  public:
    ProbabilityDistributionC()
    {}
    //: Default constructor makes invalid handle

    RealT MeasureProbability(const VariablePropositionC& value) const
    { return Body().MeasureProbability(value); }
    //: Calculate the probability that the variable takes the specified value
    //!param: value - a value for the variable
    //!return: the probability that the variable takes the specified value

    VariableC Variable() const
    { return Body().Variable(); }
    //: Get the variable for the probability distribution

    StringC ToString() const
    { return Body().ToString(); }
    //: Get a string representation of the distribution

  protected:
    ProbabilityDistributionC(ProbabilityDistributionBodyC &bod)
     : RCHandleC<ProbabilityDistributionBodyC>(bod)
    {}
    //: Body constructor. 
    
    ProbabilityDistributionC(const ProbabilityDistributionBodyC *bod)
     : RCHandleC<ProbabilityDistributionBodyC>(bod)
    {}
    //: Body constructor. 
    
    ProbabilityDistributionBodyC& Body()
    { return static_cast<ProbabilityDistributionBodyC &>(RCHandleC<ProbabilityDistributionBodyC>::Body()); }
    //: Body Access. 
    
    const ProbabilityDistributionBodyC& Body() const
    { return static_cast<const ProbabilityDistributionBodyC &>(RCHandleC<ProbabilityDistributionBodyC>::Body()); }
    //: Body Access. 
    
  };

}

#endif
