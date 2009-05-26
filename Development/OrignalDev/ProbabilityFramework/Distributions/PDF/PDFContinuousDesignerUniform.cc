// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/PDFContinuousDesignerUniform.hh"
#include "Ravl/Prob/PDFUniform.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  PDFContinuousDesignerUniformBodyC::PDFContinuousDesignerUniformBodyC() {
  }

  PDFContinuousDesignerUniformBodyC::~PDFContinuousDesignerUniformBodyC() {
  }

  PDFContinuousAbstractC PDFContinuousDesignerUniformBodyC::CreatePDF(const VariableContinuousC& variable, const DListC<RealT>& realSamples) const {
    RealT min = RavlConstN::maxReal;
    RealT max = RavlConstN::minReal;
    for (DLIterC<RealT> it(realSamples); it; it++) {
      min = Min(*it,min);
      max = Max(*it,max);
    }
    RealRangeC interval(min,max);
    return PDFUniformC(variable, interval);
  }

  PDFContinuousDesignerUniformC PDFContinuousDesignerUniformC::m_instance;

  PDFContinuousDesignerUniformC PDFContinuousDesignerUniformC::GetInstance() {
    if (!m_instance.IsValid())
      m_instance = PDFContinuousDesignerUniformC(true);
    return m_instance;
  }

}
