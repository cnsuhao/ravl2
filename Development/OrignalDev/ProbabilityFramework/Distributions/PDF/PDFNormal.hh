// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_PDFNORMAL_HEADER
#define RAVLPROB_PDFNORMAL_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/PDFContinuousAbstract.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Probability distribution class for a continuous variable using a gaussian function
  class PDFNormalBodyC
    : public PDFContinuousAbstractBodyC {
  public:
    PDFNormalBodyC(const VariableContinuousC& variable, RealT mean, RealT variance);
    //: Constructor
    //!param: variable - the random variable for the distribution
    //!param: mean - the mean of the distribution
    //!param: variance - the variance of the distribution

    virtual ~PDFNormalBodyC();
    //: Destructor
    
    virtual RealT MeasureProbability(RealRangeC valueRange) const;
    //: Calculate the probability that the variable takes the specified value
    //!param: value - a value for the variable
    //!return: the probability that the variable takes the specified value
    
    virtual StringC ToString() const;
    //: Get a string representation of the distribution
    
    RealT Mean() const;
    //: Get the mean of the distribution
    
    RealT Variance() const;
    //: Get the variance of the distribution

  private:
    void SetMeanAndVariance(RealT mean, RealT variance);
    //: Set the mean and variance

  private:
    RealT m_mean;
    //: The mean of the distribution
    
    RealT m_variance;
    //: The variance of the distribution
    
    RealT m_oneOverSigma;
    //: Cached 1/Sqrt(variance)
  };

  //! userlevel=Normal
  //: Probability distribution class for a continuous variable using a gaussian function
  //!cwiz:author
  
  class PDFNormalC
    : public PDFContinuousAbstractC
  {
  public:
    PDFNormalC(const VariableContinuousC& variable, RealT mean, RealT variance)
      : PDFContinuousAbstractC(new PDFNormalBodyC(variable, mean, variance))
    {}
    //: Constructor
    //!param: variable - the random variable for the distribution
    //!param: mean - the mean of the distribution
    //!param: variance - the variance of the distribution

    PDFNormalC(const ProbabilityDistributionC& pdf)
      : PDFContinuousAbstractC(dynamic_cast<const PDFNormalBodyC *>(BodyPtr(pdf)))
    {}
    //: Upcast constructor
    // Creates an invalid handle if types don't match
    
    RealT Mean() const
    { return Body().Mean(); }
    //: Get the mean of the distribution
    
    RealT Variance() const
    { return Body().Variance(); }
    //: Get the variance of the distribution

  protected:
    PDFNormalC(PDFNormalBodyC &bod)
     : PDFContinuousAbstractC(bod)
    {}
    //: Body constructor. 
    
    PDFNormalC(const PDFNormalBodyC *bod)
     : PDFContinuousAbstractC(bod)
    {}
    //: Body constructor. 
    
    PDFNormalBodyC& Body()
    { return static_cast<PDFNormalBodyC &>(PDFContinuousAbstractC::Body()); }
    //: Body Access. 
    
    const PDFNormalBodyC& Body() const
    { return static_cast<const PDFNormalBodyC &>(PDFContinuousAbstractC::Body()); }
    //: Body Access. 
    
  };

}

#endif
