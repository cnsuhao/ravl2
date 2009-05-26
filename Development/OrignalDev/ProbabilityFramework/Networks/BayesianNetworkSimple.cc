// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/BayesianNetworkSimple.hh"
#include "Ravl/Prob/VariablePropositionDiscrete.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  BayesianNetworkSimpleBodyC::BayesianNetworkSimpleBodyC(const RCHashC<VariableC,ConditionalProbabilityDistributionC>& nodeCPDs)
    : BayesianNetworkAbstractBodyC(nodeCPDs)
  {
  }

  BayesianNetworkSimpleBodyC::~BayesianNetworkSimpleBodyC() {
  }

  RealT BayesianNetworkSimpleBodyC::CalculateProbability(const PropositionSetC& evidence) const {
    return EnumerateAll(Variables(evidence), evidence);
  }

  //: Determine the distribution over the variable given the evidence
  // The default implementation in the BayesianNetworkAbstractBodyC evaluates 
  // the distribution for each value of variable. This only works if variable
  // is discrete and is not terribly efficient! This implementation attempts
  // to evaluate all values of the variable simultaneously by working with
  // complete distributions at each step instead of individual probabilities.
  // The advantage of this approach is that it can potentially be applied to
  // continuous variables as well as discrete.

  ProbabilityDistributionC BayesianNetworkSimpleBodyC::CalculateDistribution(const VariableC& variable, const PropositionSetC& evidence) const {
    //:FIXME- Not actually implemented, uses base class method...
    return BayesianNetworkAbstractBodyC::CalculateDistribution(variable, evidence);
  }

  //: This function's implementation is based on ENUMERATE-ALL(vars,e) from
  //: Figure 14.9 in Artificial Intelligence: A Modern Approach, 2nd edition

  RealT BayesianNetworkSimpleBodyC::EnumerateAll(const DListC<VariableC>& vars, const PropositionSetC& evidence) const {
    if (vars.Size() == 0)
      return 1.0;
    DListC<VariableC> restVars = vars.Copy();
    VariableC Y = restVars.PopFirst();
    
    ConditionalProbabilityDistributionC cpd = NodeCPD(Y);
    PropositionSetC parentsY = evidence.SubPropositionSet(cpd.ParentVariableSet());
    
    // if Y has value y in prop
    VariablePropositionC y;
    if (evidence.FindProposition(Y,y) && y.IsValid())
      return cpd.ConditionalProbability(y, parentsY) * EnumerateAll(restVars, evidence);
    
    RealT sumProbability = 0.0;
    VariableDiscreteC discrete(Y);
    if (!discrete.IsValid())
      throw ExceptionC("BayesianNetworkSimpleBodyC::EnumerateAll(), can only sum over discrete variables");
    for (SArray1dIterC<StringC> ht(discrete.Domain().Iterator()); ht; ht++) {
      y = VariablePropositionDiscreteC(discrete, *ht);
      PropositionSetC evidenceY(evidence, y);
      sumProbability += cpd.ConditionalProbability(y, parentsY) * EnumerateAll(restVars, evidenceY);
    }
    return sumProbability;
  }

}
