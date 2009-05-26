// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_PDFCONTINUOUSABSTRACT_HEADER
#define RAVLPROB_PDFCONTINUOUSABSTRACT_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/PDFAbstract.hh"
#include "Ravl/Prob/VariableContinuous.hh"
#include "Ravl/Prob/VariablePropositionContinuous.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Abstract probability distribution class for a continuous variable
  class PDFContinuousAbstractBodyC
    : public PDFAbstractBodyC {
  public:
    PDFContinuousAbstractBodyC(const VariableContinuousC& variable);
    //: Constructor
    //!param: variable - the continuous random variable for the distribution

    virtual ~PDFContinuousAbstractBodyC();
    //: Destructor
    
    virtual RealT MeasureProbability(const VariablePropositionC& value) const;
    //: Calculate the probability that the variable takes the specified value
    //!param: value - a value for the variable
    //!return: the probability that the variable takes the specified value
    // Note that this much check that the value is continuous

    virtual RealT MeasureProbability(const VariablePropositionContinuousC& value) const;
    //: Calculate the probability that the variable takes the specified value
    //!param: value - a value for the variable
    //!return: the probability that the variable takes the specified value
    // Note that this much check that the value is of the correct variable

    virtual RealT MeasureProbability(RealRangeC valueRange) const=0;
    //: Calculate the probability that the variable takes the specified value
    //!param: value - a value for the variable
    //!return: the probability that the variable takes the specified value
    // Note that this does not type checking
    
    virtual StringC ToString() const;
    //: Get a string representation of the distribution

  protected:
    VariableContinuousC VariableContinuous() const;
    //: Get access to the continuous random variable that this is a distribution of

  };

  //! userlevel=Normal
  //: Abstract probability distribution class for a continuous variable
  //!cwiz:author
  
  class PDFContinuousAbstractC
    : public PDFAbstractC
  {
  public:
    PDFContinuousAbstractC()
    {}
    //: Default constructor makes invalid handle

    PDFContinuousAbstractC(const ProbabilityDistributionC& distribution)
      : PDFAbstractC(dynamic_cast<const PDFContinuousAbstractBodyC *>(BodyPtr(distribution)))
    {}
    //: Upcast constructor
    // Creates an invalid handle if types don't match
    
    RealT MeasureProbability(const VariablePropositionContinuousC& value) const
    { return Body().MeasureProbability(value); }
    //: Calculate the probability that the variable takes the specified value
    //!param: value - a value for the variable
    //!return: the probability that the variable takes the specified value
    // Note that this much check that the value is of the correct variable

    RealT MeasureProbability(RealRangeC valueRange) const
    { return Body().MeasureProbability(valueRange); }
    //: Calculate the probability that the variable takes the specified value
    //!param: value - a value for the variable
    //!return: the probability that the variable takes the specified value
    // Note that this does not type checking

  protected:
    PDFContinuousAbstractC(PDFContinuousAbstractBodyC &bod)
     : PDFAbstractC(bod)
    {}
    //: Body constructor. 
    
    PDFContinuousAbstractC(const PDFContinuousAbstractBodyC *bod)
     : PDFAbstractC(bod)
    {}
    //: Body constructor. 
    
    PDFContinuousAbstractBodyC& Body()
    { return static_cast<PDFContinuousAbstractBodyC &>(PDFAbstractC::Body()); }
    //: Body Access. 
    
    const PDFContinuousAbstractBodyC& Body() const
    { return static_cast<const PDFContinuousAbstractBodyC &>(PDFAbstractC::Body()); }
    //: Body Access. 
    
  };

}

#endif
