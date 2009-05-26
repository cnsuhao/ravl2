// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/BayesianNetworkAbstract.hh"
#include "Ravl/OS/SysLog.hh"
#include "Ravl/Prob/VariablePropositionDiscrete.hh"
#include "Ravl/Prob/PDFDiscrete.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlProbN {
  using namespace RavlN;
  
  BayesianNetworkAbstractBodyC::BayesianNetworkAbstractBodyC(const RCHashC<VariableC,ConditionalProbabilityDistributionC>& nodeCPDs) {
    RCHashC<VariableC,ConditionalProbabilityDistributionC> nodeCPDsCopy = nodeCPDs.Copy();
    m_nodeCPDs = nodeCPDs.Copy();
    HSetC<VariableC> variables;
    while (nodeCPDsCopy.Size() > 0) {
      UIntT sizeCPDs = nodeCPDsCopy.Size();
      for (HashIterC<VariableC,ConditionalProbabilityDistributionC> ht(nodeCPDsCopy); ht; ht++) {
        // check if all parents of current node are already in variables
        bool parentsAlreadyPresent = true;
        for (HSetIterC<VariableC> st(ht.Data().ParentVariableSet().Variables()); st; st++) {
          if (!variables.Contains(*st)) {
            parentsAlreadyPresent = false;
            break;
          }
        }
        if (parentsAlreadyPresent == true) {
          variables.Insert(ht.Key());
          m_orderedNodes.InsLast(ht.Key());
          ht.Del();
          break; // because the iterator is probably invalid
        }
      }
      if (nodeCPDsCopy.Size() == sizeCPDs)
        throw ExceptionC("BayesianNetworkAbstractBodyC::BayesianNetworkAbstractBodyC(), graph must be acyclic");
    }
#if DODEBUG
    for (DLIterC<VariableC> it(m_orderedNodes); it; it++)
      SysLog(SYSLOG_DEBUG) << "BayesianNetworkAbstractBodyC::BayesianNetworkAbstractBodyC(), " << it->ToString();
#endif
    m_variableSet = VariableSetC(variables);
  }

  BayesianNetworkAbstractBodyC::~BayesianNetworkAbstractBodyC() {
  }

  //: This function's implementation is based on ENUMERATION-ASK(X,e,bn) from
  //: Figure 14.9 in Artificial Intelligence: A Modern Approach, 2nd edition

  ProbabilityDistributionC BayesianNetworkAbstractBodyC::CalculateDistribution(const VariableC& variable, 
                                                                               const PropositionSetC& evidence) const {
    VariableDiscreteC discrete(variable);
    if (!discrete.IsValid())
      throw ExceptionC("BayesianNetworkSimpleBodyC::CalculateDistribution(), only works for discrete variables");
    // check if evidence contains variable
    VariablePropositionC varProposition;
    VariablePropositionDiscreteC prior;
    if(evidence.FindProposition(variable,varProposition)) 
      prior = varProposition;
    
    // calculate probability of each value independently
    RealT sum = 0;
    RCHashC<VariablePropositionDiscreteC,RealT> probabilityLookupTable;
    for (SArray1dIterC<StringC> ht(discrete.Domain().Iterator()); ht; ht++) {
      VariablePropositionDiscreteC value(discrete, *ht);    
      RealT probability;
      if (!prior.IsValid()) {
        PropositionSetC allEvidence(evidence, value);
        probability = CalculateProbability(allEvidence);
      }
      else {
        probability = (value == prior);
      }
      sum += probability;
      probabilityLookupTable.Insert(value,probability);
    }
    // normalise the values to sum to 1.0
    RealT alpha = 1.0 / sum;
    for (HashIterC<VariablePropositionDiscreteC,RealT> ht(probabilityLookupTable); ht; ht++) {
      ht.Data() *= alpha;
    }
    return PDFDiscreteC(discrete, probabilityLookupTable);
  }

  VariableSetC BayesianNetworkAbstractBodyC::VariableSet() const {
    return m_variableSet; 
  }

  DListC<VariableC> BayesianNetworkAbstractBodyC::Variables(const PropositionSetC& evidence) const {
    //:FIXME- this ought to consider the markov blanket of the evidence
    return m_orderedNodes;
  }

  ConditionalProbabilityDistributionC BayesianNetworkAbstractBodyC::NodeCPD(const VariableC& variable) const {
    return m_nodeCPDs[variable];
  }

}
