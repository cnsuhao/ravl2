// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_CPDDISCRETEDISCRETE_HEADER
#define RAVLPROB_CPDDISCRETEDISCRETE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/CPDAbstract.hh"
#include "Ravl/Prob/VariableDiscrete.hh"
#include "Ravl/Prob/PDFDiscrete.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Conditional probability distribution of a discrete variable with discrete parents
  class CPDDiscreteDiscreteBodyC
    : public CPDAbstractBodyC {
  public:
    CPDDiscreteDiscreteBodyC(const VariableDiscreteC& randomVariable,
                             const VariableSetC& parentVariableSet,
                             const RCHashC<PropositionSetC,PDFDiscreteC>& probabilityDistributionTable);
    //: Constructor

    virtual ~CPDDiscreteDiscreteBodyC();
    //: Destructor
    
    virtual ProbabilityDistributionC ConditionalDistribution(const PropositionSetC& parentValues) const;
    //: Calculate the probability distribution for P(V|parentValues)
    //!param: parentValues - a proposition with fixed values for all parent variables
    //!return: the probability distribution of the random variable

  private:
    void SetProbabilityDistributionTable(const RCHashC<PropositionSetC,PDFDiscreteC>& probabilityDistributionTable);
    //: Set the table of distributions

  private:
    RCHashC<PropositionSetC,PDFDiscreteC> m_probabilityDistributionTable;
    //: Table of distributions for each value of the discrete parent
  };

  //! userlevel=Normal
  //: Conditional probability distribution of a discrete variable with discrete parents
  //!cwiz:author
  
  class CPDDiscreteDiscreteC
    : public CPDAbstractC
  {
  public:
  	CPDDiscreteDiscreteC()
  	{}
  	//: Default constructor makes invalid handle
  	
    CPDDiscreteDiscreteC(const VariableDiscreteC& randomVariable,
                         const VariableSetC& parentVariableSet,
                         const RCHashC<PropositionSetC,PDFDiscreteC>& probabilityDistributionTable)
      : CPDAbstractC(new CPDDiscreteDiscreteBodyC(randomVariable, parentVariableSet, probabilityDistributionTable))
    {}
    //: Constructor

  };

}

#endif
