// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_CPDBOOLEANCONTINUOUS1_HEADER
#define RAVLPROB_CPDBOOLEANCONTINUOUS1_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/CPDAbstract.hh"
#include "Ravl/Prob/VariableBoolean.hh"
#include "Ravl/Prob/VariableContinuous.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Conditional probability distribution of a boolean variable with only a single continuous parent
  class CPDBooleanContinuous1BodyC
    : public CPDAbstractBodyC {
  public:
    CPDBooleanContinuous1BodyC(const VariableBooleanC& randomVariable,
                               const VariableContinuousC& parentVariable,
                               RealT mean,
                               RealT variance,
                               bool sign);
    //: Constructor

    virtual ~CPDBooleanContinuous1BodyC();
    //: Destructor
    
    virtual ProbabilityDistributionC ConditionalDistribution(const PropositionSetC& parentValues) const;
    //: Calculate the probability distribution for P(V|parentValues)
    //!param: parentValues - a proposition with fixed values for some (or all) parent variables
    //!return: the probability distribution of the random variable

  private:
    void SetTransform(RealT mean, RealT variance, bool sign);
    //: Set the table of distributions

    VariableContinuousC ParentVariable() const;
    //: Get access to the parent variable directly

    void SetParentVariable(const VariableContinuousC& parentVariable);
    //: Cache the parent variable for direct access

  private:
    RealT m_mean;
    RealT m_variance;
    bool m_sign;

    VariableContinuousC m_parentVariable;
    //: Cached copy of parent variable for direct access
  };

  //! userlevel=Normal
  //: Conditional probability distribution of a continuous variable with only a single discrete parent
  //!cwiz:author
  
  class CPDBooleanContinuous1C
    : public CPDAbstractC
  {
  public:
  	CPDBooleanContinuous1C()
  	{}
  	//: Default constructor makes invalid handle
  	
    CPDBooleanContinuous1C(const VariableBooleanC& randomVariable,
                           const VariableContinuousC& parentVariable,
                           RealT mean,
                           RealT variance,
                           bool sign)
      : CPDAbstractC(new CPDBooleanContinuous1BodyC(randomVariable, parentVariable, mean, variance, sign))
    {}
    //: Constructor

  };

}

#endif
