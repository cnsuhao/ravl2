// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/PDFAbstract.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  PDFAbstractBodyC::PDFAbstractBodyC(const VariableC& variable) {
    SetVariable(variable);
  }

  PDFAbstractBodyC::~PDFAbstractBodyC() {
  }

  VariableC PDFAbstractBodyC::Variable() const {
    return m_variable;
  }

  void PDFAbstractBodyC::SetVariable(const VariableC& variable) {
    m_variable = variable;
  }

}
