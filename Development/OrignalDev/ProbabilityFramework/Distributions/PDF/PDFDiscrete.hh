// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_PDFDISCRETE_HEADER
#define RAVLPROB_PDFDISCRETE_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/PDFAbstract.hh"
#include "Ravl/Prob/VariablePropositionDiscrete.hh"
#include "Ravl/RCHash.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Probability distribution class for a discrete variable using a lookup table
  class PDFDiscreteBodyC
    : public PDFAbstractBodyC {
  public:
    PDFDiscreteBodyC(const VariableDiscreteC& variable, const RCHashC<VariablePropositionDiscreteC,RealT>& probabilityLookupTable);
    //: Constructor
    //!param: variable - the random variable for the distribution
    //!param: probabilityLookupTable - a lookup table for the probabilities of the values of the variable

    virtual ~PDFDiscreteBodyC();
    //: Destructor
    
    virtual RealT MeasureProbability(const VariablePropositionC& value) const;
    //: Calculate the probability that the variable takes the specified value
    //!param: value - a value for the variable
    //!return: the probability that the variable takes the specified value

    virtual StringC ToString() const;
    //: Get a string representation of the distribution

  protected:
    PDFDiscreteBodyC(const VariableDiscreteC& variable);
    //: Constructor
    //!param: variable - the random variable for the distribution

    void SetProbabilityLookupTable(const RCHashC<VariablePropositionDiscreteC,RealT>& probabilityLookupTable);
    //: Set the table after checking that it is valid
    // This involves ensuring that there each possible value of the variable is
    // represented in the table and that the values sum to 1.0

  private:
    VariableDiscreteC VariableDiscrete() const;
    //: Get access to the discrete random variable that this is a distribution of

  private:
    RCHashC<VariablePropositionDiscreteC,RealT> m_probabilityLookupTable;
  };

  //! userlevel=Normal
  //: Probability distribution class for a discrete variable using a lookup table
  //!cwiz:author
  
  class PDFDiscreteC
    : public PDFAbstractC
  {
  public:
    PDFDiscreteC()
    {}
    //: Default constructor makes invalid handle

    PDFDiscreteC(const VariableDiscreteC& variable, const RCHashC<VariablePropositionDiscreteC,RealT>& probabilityLookupTable)
      : PDFAbstractC(new PDFDiscreteBodyC(variable, probabilityLookupTable))
    {}
    //: Constructor
    //!param: variable - the random variable for the distribution
    //!param: probabilityLookupTable - a lookup table for the probabilities of the values of the variable

  protected:
    PDFDiscreteC(PDFDiscreteBodyC &bod)
     : PDFAbstractC(bod)
    {}
    //: Body constructor. 
    
    PDFDiscreteC(const PDFDiscreteBodyC *bod)
     : PDFAbstractC(bod)
    {}
    //: Body constructor. 
    
    PDFDiscreteBodyC& Body()
    { return static_cast<PDFDiscreteBodyC &>(PDFAbstractC::Body()); }
    //: Body Access. 
    
    const PDFDiscreteBodyC& Body() const
    { return static_cast<const PDFDiscreteBodyC &>(PDFAbstractC::Body()); }
    //: Body Access. 
    
  };

}

#endif
