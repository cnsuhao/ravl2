// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/PDFContinuousAbstract.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  PDFContinuousAbstractBodyC::PDFContinuousAbstractBodyC(const VariableContinuousC& variable)
    : PDFAbstractBodyC(variable)
  {
  }

  PDFContinuousAbstractBodyC::~PDFContinuousAbstractBodyC() {
  }

  RealT PDFContinuousAbstractBodyC::MeasureProbability(const VariablePropositionC& value) const {
  	VariablePropositionContinuousC propositionContinuous(value);
    if (!propositionContinuous.IsValid())
      throw ExceptionC("PDFContinuousAbstractBodyC::MeasureProbability(), value is not continuous");
    return MeasureProbability(propositionContinuous);
  }

  RealT PDFContinuousAbstractBodyC::MeasureProbability(const VariablePropositionContinuousC& value) const {
    if (!value.IsValid())
      throw ExceptionC("PDFContinuousAbstractBodyC::MeasureProbability(), value object is not valid");
    if (value.Variable() != Variable())
      throw ExceptionC("PDFContinuousAbstractBodyC::MeasureProbability(), value doesn't match variable of this distribution");
   return MeasureProbability(value.ValueRange());
  }

  VariableContinuousC PDFContinuousAbstractBodyC::VariableContinuous() const {
    return (VariableContinuousC)Variable();
  }

  StringC PDFContinuousAbstractBodyC::ToString() const {
    RavlAssertMsg(0, "PDFContinuousAbstractBodyC::ToString(), not implemented");
    return "";
  }

}
