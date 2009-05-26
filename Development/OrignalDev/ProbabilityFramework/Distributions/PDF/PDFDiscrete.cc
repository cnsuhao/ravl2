// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"

#include "Ravl/Prob/PDFDiscrete.hh"
#include "Ravl/HashIter.hh"

namespace RavlProbN {
  using namespace RavlN;
  
  PDFDiscreteBodyC::PDFDiscreteBodyC(const VariableDiscreteC& variable, const RCHashC<VariablePropositionDiscreteC,RealT>& probabilityLookupTable)
    : PDFAbstractBodyC(variable)
  {
    SetProbabilityLookupTable(probabilityLookupTable);
  }

  PDFDiscreteBodyC::PDFDiscreteBodyC(const VariableDiscreteC& variable)
    : PDFAbstractBodyC(variable)
  {
    // Note that the probability table has not been set up, hope you know what you are doing!
  }

  PDFDiscreteBodyC::~PDFDiscreteBodyC() {
  }

  RealT PDFDiscreteBodyC::MeasureProbability(const VariablePropositionC& value) const {
  	if (!value.IsValid())
  	  throw ExceptionC("PDFDiscreteBodyC::MeasureProbability(), value is invalid");
    if (value.Variable() != Variable())
      throw ExceptionC("PDFDiscreteBodyC::MeasureProbability(), value doesn't match variable of this distribution");
    RealT probability = 0.0;
    if (!m_probabilityLookupTable.Lookup(value, probability))
      throw ExceptionC("PDFDiscreteBodyC::MeasureProbability(), couldn't find value in table");
    return probability;
  }

  VariableDiscreteC PDFDiscreteBodyC::VariableDiscrete() const {
    return VariableDiscreteC(Variable());
  }

  void PDFDiscreteBodyC::SetProbabilityLookupTable(const RCHashC<VariablePropositionDiscreteC,RealT>& probabilityLookupTable) {
    if (probabilityLookupTable.Size() != VariableDiscrete().DomainSize())
      throw ExceptionC("ProbabilityDistributionDiscreteBodyC::SetProbabilityLookupTable(), table must have entry for each value of variable");
    // check that the table has been initialized properly and that all values sum to 1.0
    RealT sum = 0.0;
    for (HashIterC<VariablePropositionDiscreteC,RealT> it(probabilityLookupTable); it; it++) {
      if (*it < 0.0)
        throw ExceptionC("ProbabilityDistributionDiscreteBodyC::SetProbabilityLookupTable(), table can't have negative entries");
      if (it.Key().Variable() != Variable())
        throw ExceptionC("ProbabilityDistributionDiscreteBodyC::SetProbabilityLookupTable(), lookup table entry doesn't match random variable!");
      sum += *it;
    }
    // check that the sum is close to 1
    if (Abs(sum - 1.0) > 1e-6)
      throw ExceptionC("ProbabilityDistributionDiscreteBodyC::SetProbabilityLookupTable(), table doesn't sum to 1.0");
    m_probabilityLookupTable = probabilityLookupTable.Copy();
  }

  StringC PDFDiscreteBodyC::ToString() const {
    StringC string = VariableDiscrete().ToString() + "=<";
    SArray1dIterC<StringC> ht(VariableDiscrete().Domain().Iterator());
    VariablePropositionDiscreteC discreteValue(VariableDiscrete(), *ht);
    string += StringC(MeasureProbability(discreteValue));
    for (ht++ ; ht; ht++) {
      string += ",";
      VariablePropositionDiscreteC discreteValue(VariableDiscrete(), *ht);
      string += StringC(MeasureProbability(discreteValue));
    }
    string += ">";
    return string;
  }

}
