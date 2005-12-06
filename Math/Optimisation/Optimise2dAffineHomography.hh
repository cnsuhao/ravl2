// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATH_OPTIMISE2DAFFINEHOMOGRAPHY_HEADER
#define RAVLMATH_OPTIMISE2DAFFINEHOMOGRAPHY_HEADER 1
//! userlevel=Normal
//! author="Phil McLauchlan"
//! date="24/7/2002"
//! rcsid="$Id$"
//! docentry="Ravl.API.Math.Optimisation.Examples"
//! example="Affine2dFitTest.cc"
//! lib=RavlOptimise
//! file="Ravl/Math/Optimisation/Optimise2dAffineHomography.hh"

#include "Ravl/StateVectorAffine2d.hh"
#include "Ravl/Point2dPairObs.hh"
#include "Ravl/DList.hh"

namespace RavlN {

  //: Shrink-wrap affine homography fitting function
  // <ul>
  //  <li> matchList: A list of 2D point pair matches on two planes.
  //  <li> varScale: The ratio of outlier and inlier error standard deviations.
  //  <li> noRansacIterations: The number of RANSAC iterations to perform.
  //  <li> ransacChi2Thres: The RANSAC inlier error threshold.
  //  <li> compatChi2Thres: The threshold for compatibility used to select
  //                        the final inlier matches
  //  <li> noLevMarqIterations: The number of Levenberg-Marquardt iterations.
  //  <li> lambdaStart: Starting value for the damping factor lambda.
  //  <li> lambdaFactor: Multiplication factor for damping factor lambda.
  // </ul>
  const StateVectorAffine2dC
  Optimise2dAffineHomography ( DListC<Point2dPairObsC> &matchList,
			       RealT varScale=10.0,
			       RealT chi2Thres=5.0,
			       UIntT noRansacIterations=100,
			       RealT ransacChi2Thres=3.0,
			       RealT compatChi2Thres=5.0,
			       UIntT noLevMarqIterations=10,
			       RealT lambdaStart=0.1,
			       RealT lambdaFactor=0.1 );

}  


#endif
