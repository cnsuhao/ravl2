// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_MEANCOVARIANCE2D_HEADER
#define RAVL_MEANCOVARIANCE2D_HEADER 1
//! author="Radek Marik"
//! date="01.01.1994"
//! docentry="Ravl.Math.Statistics"
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/FMeanCovariance.hh"

namespace RavlN {

  class MeanCovariance2dC
    : public FMeanCovarianceC<2>
  {
  public:
    MeanCovariance2dC()
    {}
    //: Default constructor.
    // Creates zero mean and zero covariance matrix representing
    // the fixed-dimensional set containing no data points.
    
    MeanCovariance2dC(const FVectorC<2> & point)
      : FMeanCovarianceC<2>(point)
    {}
    //: Constructor 
    // Creates the mean vector and zero covariance matrix representing
    // the data set containing just one data point. 
    
    MeanCovariance2dC(const FMeanC<2> & mean)
      : FMeanCovarianceC<2>(mean)
    {}
    //: Creates the mean vector and zero covariance matrix representing
    //: the data set represented by the 'mean'.
    
    MeanCovariance2dC(SizeT  n, 
		     const FVectorC<2> & mean, 
		     const FMatrixC<2,2> & ncov)
      : FMeanCovarianceC<2>(n,mean,ncov)
    {}
    //: Creates the mean vector and zero covariance matrix representing
    //: the data set containing 'n' points and represented by the 'mean'
    //: and the covariance matrix 'cov'. 
    
  };
}


#endif
