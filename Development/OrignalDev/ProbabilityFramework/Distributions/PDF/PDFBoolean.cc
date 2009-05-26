// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/PDFBoolean.hh"
#include "Ravl/Prob/VariablePropositionBoolean.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  PDFBooleanBodyC::PDFBooleanBodyC(const VariableBooleanC& variable, RealT probabilityTrue)
    : PDFDiscreteBodyC(variable)
  {
    RCHashC<VariablePropositionDiscreteC,RealT> probabilityLookupTable;
    probabilityLookupTable.Insert(VariablePropositionBooleanC(variable, true), probabilityTrue);
    probabilityLookupTable.Insert(VariablePropositionBooleanC(variable, false), 1.0-probabilityTrue);
    SetProbabilityLookupTable(probabilityLookupTable);
  }

  PDFBooleanBodyC::~PDFBooleanBodyC() {
  }

}
