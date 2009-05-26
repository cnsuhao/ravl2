// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_CPDPRIORPDF_HEADER
#define RAVLPROB_CPDPRIORPDF_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/CPDAbstract.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Prior probability distribution
  class CPDPriorPDFBodyC
    : public CPDAbstractBodyC {
  public:
    CPDPriorPDFBodyC(const ProbabilityDistributionC& probabilityDistribution);
    //: Constructor

    virtual ~CPDPriorPDFBodyC();
    //: Destructor
    
    virtual ProbabilityDistributionC ConditionalDistribution(const PropositionSetC& parentValues) const;
    //: Calculate the probability distribution for P(V|parentValues)
    //!param: parentValues - a proposition with fixed values for some (or all) parent variables
    //!return: the probability distribution of the random variable

  private:
    void SetProbabilityDistribution(const ProbabilityDistributionC& probabilitDistribution);
    //: Set the table of distributions

  private:
    ProbabilityDistributionC m_pdf;
    //: The distribution of prior probabilities
  };

  //! userlevel=Normal
  //: Prior probability distribution
  //!cwiz:author
  
  class CPDPriorPDFC
    : public CPDAbstractC
  {
  public:
  	CPDPriorPDFC()
  	{}
  	//: Default constructor makes invalid handle
  	
    CPDPriorPDFC(const ProbabilityDistributionC& probabilityDistribution)
      : CPDAbstractC(new CPDPriorPDFBodyC(probabilityDistribution))
    {}
    //: Constructor

  };

}

#endif
