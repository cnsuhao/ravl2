// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/PDFNormal.hh"
#include "Ravl/StdMath.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  PDFNormalBodyC::PDFNormalBodyC(const VariableContinuousC& variable, RealT mean, RealT variance)
    : PDFContinuousAbstractBodyC(variable)
  {
    SetMeanAndVariance(mean, variance);
  }

  PDFNormalBodyC::~PDFNormalBodyC() {
  }

  RealT PDFNormalBodyC::MeasureProbability(RealRangeC valueRange) const {
  	RealT max = (valueRange.Max() - m_mean) * m_oneOverSigma;
  	RealT min = (valueRange.Min() - m_mean) * m_oneOverSigma;
  	return (Erf(max) - Erf(min)) * 0.5;
  }
  
  StringC PDFNormalBodyC::ToString() const {
  	return Variable().ToString() + "=" + StringC(Mean()) + "+-" + Sqrt(Variance());
  }
  
  RealT PDFNormalBodyC::Mean() const {
  	return m_mean;
  }
  
  RealT PDFNormalBodyC::Variance() const {
  	return m_variance;
  }

  void PDFNormalBodyC::SetMeanAndVariance(RealT mean, RealT variance) {
    m_mean = mean;
    m_variance = variance;
    m_oneOverSigma = 1.0 / (Sqrt (variance));
  }

}
