// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_MEANVARIANCE_HEADER
#define RAVL_MEANVARIANCE_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! docentry="Ravl.API.Math.Statistics"
//! lib=RavlMath
//! file="Ravl/Math/Statistics/MeanCovariance/MeanVariance.hh"

#include "Ravl/Math.hh"
#include "Ravl/SArray1d.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Mean and variance of a single variable.
  // If you want to build up statistics about a sample use the Sums1d2C
  // class to accumulate the information and create a MeanVarianceC from
  // there.
  
  class MeanVarianceC {
  public:
    MeanVarianceC(const SArray1dC<RealT> &data,bool sampleStatistics = true);
    //: Calculate the mean and variance from an array of numbers.
    
    MeanVarianceC()
      : n(0),
	mean(0),
	var(0)
    {}
    //: Default constructor.
    
    MeanVarianceC(SizeT nn,RealT nmean,RealT nvar)
      : n(nn),
	mean(nmean),
	var(nvar)
    {}
    //: Constructor.
    
    RealT StdDeviation() const
    { return Sqrt(var); }
    //: Get the standard deviation.
    
    RealT Variance() const
    { return var; }
    //: Access the variance.
    
    SizeT Number() const
    { return n; }
    //: Access the number of samples.
    
    RealT Mean() const
    { return mean; }
    //: Access the mean.
    
    RealT Probability(RealT low,RealT high) const;
    //: Find the probability of getting a sample with a values between low and high.
    
    RealT ProbabilityOfHigherValue(RealT threshold) const;
    //: Compute the probability of a value higher than the threshold
    
    RealT Gauss(RealT x) const;
    //: Value of the gauss distribution at x.
    // Also known as the normal distribution.
    
    MeanVarianceC &operator+=(const MeanVarianceC &mv);
    //: Add another MeanVariance to this one.
    
    MeanVarianceC &operator-=(const MeanVarianceC &mv);
    //: Remove another MeanVariance from this one.
    
    MeanVarianceC operator*(const MeanVarianceC &oth) const;
    //: Calculate the product of the two probability density functions.
    // This assumes the estimates of the distributions are accurate. (The number
    // of samples is ignored) 
    
  protected:
    SizeT n;
    RealT mean;
    RealT var; 
  };
  
  ostream& operator<<(ostream &s,const MeanVarianceC &mv);
  istream& operator>>(istream &s, MeanVarianceC &mv);
  BinOStreamC& operator<<(BinOStreamC &s,const MeanVarianceC &mv);
  BinIStreamC& operator>>(BinIStreamC &s, MeanVarianceC &mv);
}


#endif
