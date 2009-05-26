// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/CPDBooleanContinuous1.hh"
#include "Ravl/Prob/PDFDiscrete.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  CPDBooleanContinuous1BodyC::CPDBooleanContinuous1BodyC(const VariableBooleanC& randomVariable,
                                                         const VariableContinuousC& parentVariable,
                                                         RealT mean,
                                                         RealT variance,
                                                         bool sign)
    : CPDAbstractBodyC(randomVariable, parentVariable) {
    SetParentVariable(parentVariable);
    SetTransform(mean, variance, sign);
  }

  CPDBooleanContinuous1BodyC::~CPDBooleanContinuous1BodyC() {
  }

  ProbabilityDistributionC CPDBooleanContinuous1BodyC::ConditionalDistribution(const PropositionSetC& parentValues) const {
    PDFDiscreteC pdf;
    return pdf;
  }
  
  void CPDBooleanContinuous1BodyC::SetTransform(RealT mean, RealT variance, bool sign) {
  	m_mean = mean;
  	m_variance = variance;
  	m_sign = sign;
  }

  VariableContinuousC CPDBooleanContinuous1BodyC::ParentVariable() const {
    return m_parentVariable;
  }

  void CPDBooleanContinuous1BodyC::SetParentVariable(const VariableContinuousC& parentVariable) {
    if (!parentVariable.IsValid())
      throw ExceptionC("CPDBooleanContinuous1BodyC::SetParentVariable(), parent variable is invalid");
    m_parentVariable = parentVariable;
  }

}
