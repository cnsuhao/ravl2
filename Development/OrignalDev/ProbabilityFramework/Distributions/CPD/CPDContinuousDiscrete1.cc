// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/CPDContinuousDiscrete1.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  CPDContinuousDiscrete1BodyC::CPDContinuousDiscrete1BodyC(const VariableContinuousC& randomVariable,
                                                           const VariableDiscreteC& parentVariable,
                                                           const RCHashC<VariablePropositionDiscreteC,PDFContinuousAbstractC>& probabilityDistributionTable)
    : CPDAbstractBodyC(randomVariable, parentVariable) 
  {
    SetParentVariable(parentVariable);
    SetProbabilityDistributionTable(probabilityDistributionTable);
  }

  CPDContinuousDiscrete1BodyC::~CPDContinuousDiscrete1BodyC() {
  }

  ProbabilityDistributionC CPDContinuousDiscrete1BodyC::ConditionalDistribution(const PropositionSetC& parentValues) const {
    PDFContinuousAbstractC pdf;
    VariablePropositionC proposition;
    if(!parentValues.FindProposition(m_parentVariable,proposition) || !proposition.IsValid()) {
      throw ExceptionC("CPDContinuousDiscrete1BodyC::ConditionalDistribution(), no value proposition!");
    }
    if (!m_probabilityDistributionTable.Lookup(proposition, pdf))
      throw ExceptionC("CPDContinuousDiscrete1BodyC::ConditionalDistribution(), couldn't find distribution");    
    return pdf;
  }
  
  void CPDContinuousDiscrete1BodyC::SetProbabilityDistributionTable(const RCHashC<VariablePropositionDiscreteC,PDFContinuousAbstractC>& probabilityDistributionTable) {
    // check that there is a table for each value
    if (ParentVariable().DomainSize() != probabilityDistributionTable.Size())
      throw ExceptionC("CPDContinuousDiscrete1BodyC::SetProbabilityDistributionTable(), need table for each value");
    
    // check that all tables are for the correct variable
    for (HashIterC<VariablePropositionDiscreteC,PDFContinuousAbstractC> ht(probabilityDistributionTable); ht; ht++) {
      if (ht.Key().Variable() != ParentVariable())
        throw ExceptionC("CPDContinuousDiscrete1BodyC::SetProbabilityDistributionTable(), each table must be for a value of the parent variable");
    }
    m_probabilityDistributionTable = probabilityDistributionTable.Copy();
  }

  VariableDiscreteC CPDContinuousDiscrete1BodyC::ParentVariable() const {
    return m_parentVariable;
  }

  void CPDContinuousDiscrete1BodyC::SetParentVariable(const VariableDiscreteC& parentVariable) {
    if (!parentVariable.IsValid())
      throw ExceptionC("CPDContinuousDiscrete1BodyC::SetParentVariable(), parent variable is invalid");
    m_parentVariable = parentVariable;
  }

}
