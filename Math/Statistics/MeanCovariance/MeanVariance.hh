// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMEANVARIANCE_HEADER
#define RAVLMEANVARIANCE_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! docentry="Ravl.Math.Statistics"
//! lib=RavlMath

#include "Ravl/Math.hh"
#include "Ravl/SArray1d.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Mean and variance of a single variable.
  
  class MeanVarianceC {
  public:
    MeanVarianceC(const SArray1dC<RealT> &data);
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
    
    MeanVarianceC &operator+=(const MeanVarianceC &mv);
    //: Add another MeanVariance to this one.
    
    MeanVarianceC &operator-=(const MeanVarianceC &mv);
    //: Remove another MeanVariance from this one.
    
  protected:
    SizeT n;
    RealT mean;
    RealT var; 
  };


  inline
  ostream& operator<<(ostream &s,const MeanVarianceC &mv) {
    s << mv.Number() << ' ' << mv.Mean() << ' ' << mv.Variance();
    return s;
  }

  inline
  istream& operator>>(istream &s, MeanVarianceC &mv) {
    SizeT n;
    RealT v1,v2;
    s >> n >> v1 >> v2;
    mv = MeanVarianceC(n,v1,v2);
    return s;
  }
  
}


#endif
