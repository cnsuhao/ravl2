// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/PDFProbit.hh"
#include "Ravl/StdMath.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  PDFProbitBodyC::PDFProbitBodyC(const VariableContinuousC& variable, RealT mean, RealT variance, bool complement)
    : PDFContinuousAbstractBodyC(variable)
  {
    SetMeanVarianceAndComplement(mean, variance, complement);
  }

  PDFProbitBodyC::~PDFProbitBodyC() {
  }

  RealT PDFProbitBodyC::MeasureProbability(RealRangeC valueRange) const {
  	RealT centre = (valueRange.Center() - Mean()) * m_oneOverSigma;
  	return m_complement? (Erfc(centre) * 0.5): ((Erf(centre) +1.0) * 0.5);
  }
  
  StringC PDFProbitBodyC::ToString() const {
  	return Variable().ToString() + "=" + StringC(Mean()) + "+-" + Sqrt(Variance()) + (m_complement?StringC("\\"):StringC("/"));
  }
  
  RealT PDFProbitBodyC::Mean() const {
  	return m_mean;
  }
  
  RealT PDFProbitBodyC::Variance() const {
  	return m_variance;
  }

  void PDFProbitBodyC::SetMeanVarianceAndComplement(RealT mean, RealT variance, bool complement) {
    m_mean = mean;
    m_variance = variance;
    m_complement = complement;
    m_oneOverSigma = 1.0 / (Sqrt (variance));
  }

}
