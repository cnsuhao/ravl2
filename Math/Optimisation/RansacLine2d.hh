// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_RANSACLINE2D_HEADER
#define RAVLMATH_RANSACLINE2D_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.Math.Optimisation.Examples"
//! example="OrthogonalRegressionTest.cc"

#include "Ravl/RansacObsListSampling.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //! autoLink=on
  //: RANSAC algorithm class for 2D line fitting
  // This is an implementation of RANSAC for 2D line fitting to points.
  class RansacLine2dC
    : public RansacObsListSamplingC
 {
 public:
   RansacLine2dC(DListC<ObservationC> obs_list, RealT chi2_thres, RealT zh);
   //: Constructor.
   // Stores the given list of point observations, invokes the RANSAC
   // constructor with automatic sampling of pairs of points, using the
   // given threshold chi2_thres on the negative log-likelihood.
   // zh is the 3rd homogeneous coordinate of the plane on which the line lies.

   RansacLine2dC(DListC<ObservationC> obs_list, RealT chi2_thres);
   //: Constructor.
   // Stores the given list of point observations, invokes the RANSAC
   // constructor with automatic sampling of pairs of points, using the
   // given threshold chi2_thres on the negative log-likelihood.

   StateVectorC FitToSample(DListC<ObservationC> sample);
   //: Fit line parameters to sample two or more points

 private:
   RealT zh; // 3rd homogeneous coordinate of plane on which line lies
  };
}


#endif
