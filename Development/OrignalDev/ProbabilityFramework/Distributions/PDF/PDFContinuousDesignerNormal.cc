// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/PDFContinuousDesignerNormal.hh"
#include "Ravl/Prob/PDFNormal.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  PDFContinuousDesignerNormalBodyC::PDFContinuousDesignerNormalBodyC() {
  }

  PDFContinuousDesignerNormalBodyC::~PDFContinuousDesignerNormalBodyC() {
  }

  PDFContinuousAbstractC PDFContinuousDesignerNormalBodyC::CreatePDF(const VariableContinuousC& variable, const DListC<RealT>& realSamples) const {
    RealT n = realSamples.Size();
    RealT sum = 0;
    RealT sum2 = 0;
    for (DLIterC<RealT> it(realSamples); it; it++) {
      sum += *it;
      sum2 += Sqr(*it);
    }
    RealT mean = sum / n;
    RealT variance = (sum2 - Sqr(sum) / n) / (n-1);
    return PDFNormalC(variable, mean, variance);
  }

  PDFContinuousDesignerNormalC PDFContinuousDesignerNormalC::m_instance;

  PDFContinuousDesignerNormalC PDFContinuousDesignerNormalC::GetInstance() {
    if (!m_instance.IsValid())
      m_instance = PDFContinuousDesignerNormalC(true);
    return m_instance;
  }

}
