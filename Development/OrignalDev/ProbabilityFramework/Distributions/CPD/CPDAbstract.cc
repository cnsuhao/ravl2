// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/CPDAbstract.hh"
#include "Ravl/Prob/ProbabilityDistribution.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  CPDAbstractBodyC::CPDAbstractBodyC(const VariableC& variable, const VariableSetC& parentVariableSet) {
    SetVariable(variable);
    SetParentVariableSet(parentVariableSet);
  }

  CPDAbstractBodyC::CPDAbstractBodyC(const VariableC& variable, const VariableC& parentVariable) {
    SetVariable(variable);
    SetSingleParentVariable(parentVariable);
  }

  CPDAbstractBodyC::~CPDAbstractBodyC() {
  }

  RealT CPDAbstractBodyC::ConditionalProbability(const VariablePropositionC& value, const PropositionSetC& parentValues) const {
    if (!value.IsValid())
      throw ExceptionC("CPDAbstractBodyC::ConditionalProbability(), value is invalid");
    if (value.Variable() != Variable())
      throw ExceptionC("CPDAbstractBodyC::ConditionalProbability(), value isn't of correct variable");
    ProbabilityDistributionC pdf(ConditionalDistribution(parentValues));
    return pdf.MeasureProbability(value);
  }

  VariableC CPDAbstractBodyC::Variable() const {
    return m_variable;
  }

  VariableSetC CPDAbstractBodyC::ParentVariableSet() const {
    return m_parentVariableSet;
  }

  void CPDAbstractBodyC::SetVariable(const VariableC& variable) {
    if (!variable.IsValid())
      throw ExceptionC("CPDAbstractBodyC::SetVariable(), variable is invalid");
    m_variable = variable;
  }

  void CPDAbstractBodyC::SetParentVariableSet(const VariableSetC& parentVariableSet) {
  	if (!parentVariableSet.IsValid())
      throw ExceptionC("CPDAbstractBodyC::SetParentVariableSet(), parentVariableSet is invalid");
    m_parentVariableSet = parentVariableSet;
  }

  void CPDAbstractBodyC::SetSingleParentVariable(const VariableC& parentVariable) {
    if (!parentVariable.IsValid())
      throw ExceptionC("CPDAbstractBodyC::SetSingleParentVariable(), parent variable is invalid");
    HSetC<VariableC> parents;
    parents.Insert(parentVariable);
    m_parentVariableSet = VariableSetC(parents);
  }

}
