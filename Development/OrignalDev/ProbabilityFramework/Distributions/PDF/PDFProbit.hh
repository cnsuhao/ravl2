// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_PDFPROBIT_HEADER
#define RAVLPROB_PDFPROBIT_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/PDFContinuousAbstract.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Probability distribution class for a continuous variable using cumulative normal
  class PDFProbitBodyC
    : public PDFContinuousAbstractBodyC {
  public:
    PDFProbitBodyC(const VariableContinuousC& variable, RealT mean, RealT variance, bool complement);
    //: Constructor
    //!param: variable - the random variable for the distribution
    //!param: mean - the mean of the distribution
    //!param: variance - the variance of the distribution
    //!param: complement - do we want the complement distribution, ie erfc

    virtual ~PDFProbitBodyC();
    //: Destructor
    
    virtual RealT MeasureProbability(RealRangeC valueRange) const;
    //: Calculate the probability that the variable takes the specified value
    //!param: value - a value for the variable
    //!return: the probability that the variable takes the specified value
    // Note that this uses erf() and the centre of the valueRange
    
    virtual StringC ToString() const;
    //: Get a string representation of the distribution
    
    RealT Mean() const;
    //: Get the mean of the distribution
    
    RealT Variance() const;
    //: Get the variance of the distribution

  private:
    void SetMeanVarianceAndComplement(RealT mean, RealT variance, bool complement);
    //: Set the mean and variance and complement

  private:
    RealT m_mean;
    //: The mean of the distribution
    
    RealT m_variance;
    //: The variance of the distribution
    
    bool m_complement;
    //: Do we use the complement distribution
    
    RealT m_oneOverSigma;
    //: Cached 1/Sqrt(variance)
  };

  //! userlevel=Normal
  //: Probability distribution class for a continuous variable using a gaussian function
  //!cwiz:author
  
  class PDFProbitC
    : public PDFContinuousAbstractC
  {
  public:
    PDFProbitC(const VariableContinuousC& variable, RealT mean, RealT variance, bool complement)
      : PDFContinuousAbstractC(new PDFProbitBodyC(variable, mean, variance, complement))
    {}
    //: Constructor
    //!param: variable - the random variable for the distribution
    //!param: mean - the mean of the distribution
    //!param: variance - the variance of the distribution
    //!param: complement - do we want the complement distribution, ie erfc

    PDFProbitC(const ProbabilityDistributionC& pdf)
      : PDFContinuousAbstractC(dynamic_cast<const PDFProbitBodyC *>(BodyPtr(pdf)))
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
    PDFProbitC(PDFProbitBodyC &bod)
     : PDFContinuousAbstractC(bod)
    {}
    //: Body constructor. 
    
    PDFProbitC(const PDFProbitBodyC *bod)
     : PDFContinuousAbstractC(bod)
    {}
    //: Body constructor. 
    
    PDFProbitBodyC& Body()
    { return static_cast<PDFProbitBodyC &>(PDFContinuousAbstractC::Body()); }
    //: Body Access. 
    
    const PDFProbitBodyC& Body() const
    { return static_cast<const PDFProbitBodyC &>(PDFContinuousAbstractC::Body()); }
    //: Body Access. 
    
  };

}

#endif
