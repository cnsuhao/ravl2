// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/CPDDesignerContinuousDiscrete1.hh"
#include "Ravl/Prob/CPDContinuousDiscrete1.hh"
#include "Ravl/Prob/PDFDesignerFactory.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  CPDDesignerContinuousDiscrete1BodyC::CPDDesignerContinuousDiscrete1BodyC() {
  }

  CPDDesignerContinuousDiscrete1BodyC::~CPDDesignerContinuousDiscrete1BodyC() {
  }

  ConditionalProbabilityDistributionC CPDDesignerContinuousDiscrete1BodyC::CreateCPD(const DListC<Tuple2C<VariablePropositionC,PropositionSetC> >& propositionPairs) const {
    // check that there is at least one sample!
    if (propositionPairs.Size() == 0)
      throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::CreateCPD(), propositionPairs must contain at least one sample!");
    VariableContinuousC dependentVariable = CheckDependentVariable(propositionPairs.First().Data1().Variable());
    // check that the domain is suitable
    VariableSetC parentVariableSet = propositionPairs.First().Data2().VariableSet();
    if (parentVariableSet.Size() != 1)
      throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::CreateCPD(), parent variable set must have 1 variable");
    VariableDiscreteC parentVariable = CheckParentVariable(parentVariableSet.Variable(0));
    // create a list for each value of the parent variable
    RCHashC<VariablePropositionDiscreteC,DListC<RealT> > valuesByParent;
    // put each entry into the correct list
    for (DLIterC<Tuple2C<VariablePropositionC,PropositionSetC> > it(propositionPairs); it; it++) {
      if (it->Data1().Variable() != dependentVariable)
        throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::CreateCPD(), incorrect dependent value in sample");
      if (it->Data2().VariableSet() != parentVariableSet)
        throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::CreateCPD(), all proposition sets must belong to correct variable sets");
      if (it->Data2().Size() != 1) {
      	throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::CreateCPD(), all propositions must have 1 fixed value");
      }
      VariablePropositionDiscreteC parent(it->Data2().Value(0));
      RealT value = ((VariablePropositionContinuousC)it->Data1()).ValueRange().Center();
      valuesByParent[parent].InsLast(value);
    }
    // check that there are samples for each parent value
    if (valuesByParent.Size() != parentVariable.DomainSize())
      throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::CreateCPD(), there must be examples for each parent value");
    // create all the probability distributions
    RCHashC<VariablePropositionDiscreteC,PDFContinuousAbstractC> probabilityDistributionTable;
    for (HashIterC<VariablePropositionDiscreteC,DListC<RealT> > ht(valuesByParent); ht; ht++) {
      PDFContinuousAbstractC pdf = PDFDesignerFactoryC::GetInstance().DesignPDFContinuous(dependentVariable, ht.Data());
      probabilityDistributionTable.Insert(ht.Key(), pdf);
    }
    // and finally create the CPD
    return CPDContinuousDiscrete1C(dependentVariable, parentVariable, probabilityDistributionTable);
  }

  VariableContinuousC CPDDesignerContinuousDiscrete1BodyC::CheckDependentVariable(const VariableContinuousC& dependentVariable) {
    if (!dependentVariable.IsValid())
      throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::SetDependentVariable(), dependent variable must be valid continuous");
    return dependentVariable;
  }

  VariableDiscreteC CPDDesignerContinuousDiscrete1BodyC::CheckParentVariable(const VariableDiscreteC& parentVariable) {
    if (!parentVariable.IsValid())
      throw ExceptionC("CPDDesignerContinuousDiscrete1BodyC::SetParentVariable(), parent variable must be valid discrete");
    return parentVariable;
  }

  CPDDesignerContinuousDiscrete1C CPDDesignerContinuousDiscrete1C::m_instance;

  CPDDesignerContinuousDiscrete1C CPDDesignerContinuousDiscrete1C::GetInstance() {
    if (!m_instance.IsValid())
      m_instance = CPDDesignerContinuousDiscrete1C(true);
    return m_instance;
  }

}
