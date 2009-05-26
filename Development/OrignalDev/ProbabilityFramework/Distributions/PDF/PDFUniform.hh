// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_PDFUNIFORM_HEADER
#define RAVLPROB_PDFUNIFORM_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/PDFContinuousAbstract.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Probability distribution class for a continuous variable using a uniform function
  class PDFUniformBodyC
    : public PDFContinuousAbstractBodyC {
  public:
    PDFUniformBodyC(const VariableContinuousC& variable, const RealRangeC& interval);
    //: Constructor
    //!param: variable - the random variable for the distribution
    //!param: interval - the interval over which the distribution != 0

    virtual ~PDFUniformBodyC();
    //: Destructor
    
    virtual RealT MeasureProbability(RealRangeC valueRange) const;
    //: Calculate the probability that the variable takes the specified value
    //!param: valueRange - a value for the variable
    //!return: the probability that the variable takes the specified value

    virtual StringC ToString() const;
    //: Get a string representation of the distribution
    
    RealRangeC Interval() const;
    //: Get the interval of the distribution
    
  private:
    void SetInterval(const RealRangeC& interval);
    //: Set the interval

  private:
    RealT m_probability;
    //: The uniform probability

    RealRangeC m_interval;
    //: The interval over which the probability != 0
  };

  //! userlevel=Normal
  //: Probability distribution class for a continuous variable using a uniform function
  //!cwiz:author
  
  class PDFUniformC
    : public PDFContinuousAbstractC
  {
  public:
    PDFUniformC(const VariableContinuousC& variable, const RealRangeC& interval)
      : PDFContinuousAbstractC(new PDFUniformBodyC(variable, interval))
    {}
    //: Constructor
    //!param: variable - the random variable for the distribution

    PDFUniformC(const ProbabilityDistributionC& pdf)
      : PDFContinuousAbstractC(dynamic_cast<const PDFUniformBodyC *>(BodyPtr(pdf)))
    {}
    //: Upcast constructor
    // Creates an invalid handle if types don't match
    
    RealRangeC Interval() const
    { return Body().Interval(); }
    //: Get the interval of the distribution
    
  protected:
    PDFUniformC(PDFUniformBodyC &bod)
     : PDFContinuousAbstractC(bod)
    {}
    //: Body constructor. 
    
    PDFUniformC(const PDFUniformBodyC *bod)
     : PDFContinuousAbstractC(bod)
    {}
    //: Body constructor. 
    
    PDFUniformBodyC& Body()
    { return static_cast<PDFUniformBodyC &>(PDFContinuousAbstractC::Body()); }
    //: Body Access. 
    
    const PDFUniformBodyC& Body() const
    { return static_cast<const PDFUniformBodyC &>(PDFContinuousAbstractC::Body()); }
    //: Body Access. 
    
  };

}

#endif
