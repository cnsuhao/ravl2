// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOptimise

#include "Ravl/Optimise2dAffineHomography.hh"
#include "Ravl/ObservationAffine2dPoint.hh"
#include "Ravl/Ransac.hh"
#include "Ravl/FitAffine2dPoints.hh"
#include "Ravl/EvaluateNumInliers.hh"
#include "Ravl/LevenbergMarquardt.hh"

namespace RavlN {

  // Shrink-wrap homography fitting function
  const StateVectorAffine2dC
  Optimise2dAffineHomography ( DListC<Point2dPairC> &matchList,
			       RealT varScale=10.0,
			       RealT chi2Thres=5.0,
			       UIntT noRansacIterations=100,
			       RealT ransacChi2Thres=3.0,
			       RealT compatChi2Thres=5.0,
			       UIntT noLevMarqIterations=10,
			       RealT lambdaStart=0.1,
			       RealT lambdaFactor=0.1 )
  {
    // build list of observations
    DListC<ObservationC> obsList;
    for(DLIterC<Point2dPairC> it(matchList);it;it++)
      obsList.InsLast(ObservationAffine2dPointC(it.Data().z1(),it.Data().Ni1(),
						it.Data().z2(),it.Data().Ni2(),
						varScale, chi2Thres));
#if 0
    for(DLIterC<ObservationC> it(obsList);it;it++) {
      ObservationAffine2dPointC obs = it.Data();
      cout << "z1: " << obs.GetZ1() << endl;
      cout << "Ni1: " << obs.GetNi1() << endl;
      cout << "z2: " << obs.GetZ() << endl;
      cout << "Ni2: " << obs.GetNi() << endl;
    }
#endif

    // Build RANSAC components
    ObservationListManagerC obsManager(obsList);
    FitAffine2dPointsC fitter;
    EvaluateNumInliersC evaluator(ransacChi2Thres, compatChi2Thres);
  
    // use RANSAC to fit affine homography
    RansacC ransac(obsManager, fitter, evaluator);

    // select and evaluate the given number of samples
    for ( UIntT iteration=0; iteration < noRansacIterations; iteration++ )
      ransac.ProcessSample(6);

    // select observations compatible with solution
    obsList = evaluator.CompatibleObservations(ransac.GetSolution(), obsList);

    // initialise Levenberg-Marquardt algorithm with Ransac solution
    StateVectorAffine2dC stateVecInit = ransac.GetSolution();
    LevenbergMarquardtC lm = LevenbergMarquardtC(stateVecInit, obsList);

    // apply Levenberg-Marquardt iterations
    lm.NIterations ( obsList, noLevMarqIterations, lambdaStart, lambdaFactor );

    return lm.SolutionVector();
  }
}
