// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOptimise

#include "Ravl/LevenbergMarquardt.hh"
#include "Ravl/StateVectorHomog2d.hh"
#include "Ravl/ObservationHomog2dPoint.hh"
#include "Ravl/ObservationImpHomog2dPoint.hh"
#include "Ravl/ObsVectorBiGaussian.hh"
#include "Ravl/Random.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/SArr1Iter2.hh"

// RANSAC headers
#include "Ravl/Ransac.hh"
#include "Ravl/FitHomog2dPoints.hh"
#include "Ravl/EvaluateNumInliers.hh"

#include "Ravl/Point2dPair.hh"

using namespace RavlN;

#define RANSAC_ITERATIONS 100

// ground-truth 2D homography
const Matrix3dC HomogTrue = Matrix3dC(1.1, 0.0,  3.0,
				      0.1, 0.9, 10.0,
				      0.0, 0.0,  1.0);

// Initialisation function for state vector for 2D homography fitting
static const StateVectorHomog2dC
 InitialiseHomography ( DListC<ObservationC> &obsList, // observation list
			RealT zh1, RealT zh2, // 3rd homogeneous plane coordinates
			DListC<ObservationC> &compatibleObsList ) // output list of compatible observations
{
  ObservationListManagerC obsManager(obsList);
  FitHomog2dPointsC fitter(zh1, zh2);
  EvaluateNumInliersC evaluator(3.0, 10.0);
  
  // use RANSAC to fit homography
  RansacC ransac(obsManager, fitter, evaluator);

  // select and evaluate the given number of samples
  for ( UIntT iteration=0; iteration < RANSAC_ITERATIONS; iteration++ )
    ransac.ProcessSample(8);

  // select observations compatible with solution
  compatibleObsList = evaluator.CompatibleObservations(ransac.GetSolution(),
						       obsList);
  return ransac.GetSolution();
}

// Shrink-wrap homography fitting function
static const StateVectorHomog2dC
 FitHomography2d ( DListC<Point2dPairC> &matchList, // list of matches
		   RealT zh1=1.0, RealT zh2=1.0, // 3rd homogeneous plane coordinates
		   RealT varScale=10.0, // ratio of outlier/inlier standard deviation
		   RealT chi2Thres=5.0, // Inlier/outlier residual threshold
		   UIntT noRansacIterations=100, // Number of Ransac iterations
		   RealT ransacChi2Thres=3.0, // Ransac inlier threshold
		   RealT compatChi2Thres=5.0, // Threshold for compatibility
		   UIntT noLevMarqIterations=10, // Number of Levenberg-Marquardt iterations
		   RealT lambdaStart=0.1, // Starting value fo damping factor
		   RealT lambdaFactor=0.1 ) // Multiplication factor for damping factor
{
  // build list of observations
  DListC<ObservationC> obsList;
  for(DLIterC<Point2dPairC> it(matchList);it;it++)
    obsList.InsLast(ObservationHomog2dPointC(it.Data().z1(), it.Data().Ni1(),
					     it.Data().z2(), it.Data().Ni2(),
					     varScale, chi2Thres));
#if 0
  for(DLIterC<ObservationC> it(obsList);it;it++) {
    ObservationHomog2dPointC obs = it.Data();
    cout << "z1: " << obs.GetZ1() << endl;
    cout << "Ni1: " << obs.GetNi1() << endl;
    cout << "z2: " << obs.GetZ() << endl;
    cout << "Ni2: " << obs.GetNi() << endl;
  }
#endif

  // Build RANSAC components
  ObservationListManagerC obsManager(obsList);
  FitHomog2dPointsC fitter(zh1, zh2);
  EvaluateNumInliersC evaluator(ransacChi2Thres, compatChi2Thres);
  
  // use RANSAC to fit homography
  RansacC ransac(obsManager, fitter, evaluator);

  // select and evaluate the given number of samples
  for ( UIntT iteration=0; iteration < noRansacIterations; iteration++ ) {
    ransac.ProcessSample(8);
    cout << ransac.GetSolution().IsValid();
  }

  cout << endl;

  // select observations compatible with solution
  obsList = evaluator.CompatibleObservations(ransac.GetSolution(), obsList);
  
  // initialise Levenberg-Marquardt algorithm with Ransac solution
  StateVectorHomog2dC stateVecInit = ransac.GetSolution();
  LevenbergMarquardtC lm = LevenbergMarquardtC(stateVecInit, obsList);

  // apply Levenberg-Marquardt iterations
  lm.NIterations ( obsList, noLevMarqIterations, lambdaStart, lambdaFactor );

  return lm.SolutionVector();
}

// number of points
#define NPOINTS 200

// image width & height
#define IMAGE_SIZE 100

// noise standard deviation
#define SIGMA 0.5

// noise added to generate outliers
#define OUTLIER_SIGMA 10.0

// 3rd homogeneous image coordinates in images 1 and 2
#define ZHOMOG1 100.0
#define ZHOMOG2  50.0

// weight of gauge condition observation
#define GAUGE_WEIGHT 1.0e3

static void
 PrintInlierFlags(DListC<ObservationC> obsList)
{
  cout << "Inlier flags: ";
  for(DLIterC<ObservationC> it(obsList);it;it++) {

    // get observation vector/inverse covariance object
    ObservationC& obs(it.Data());
    const ObsVectorBiGaussianC& obsVec = obs.GetObsVec();

    // ignore observations that are not robust
    if(!obsVec.IsValid()) {
      cout << "N";
      continue;
    }

    if(obsVec.Outlier()) cout << "0";
    else cout << "1";
  }
    
  cout << endl;
}

static bool
 TestHomography2dFit()
{
  SArray1dC<Vector2dC> coords1(NPOINTS), coords2(NPOINTS);
  DListC<ObservationC> obsList;

  // build arrays of x & y coordinates
  IntT i = 0;
  for(SArray1dIter2C<Vector2dC,Vector2dC> it(coords1,coords2);it;i++, it++)
  {
    // choose random x,y coordinates
    RealT x1 = Random1()*IMAGE_SIZE;
    RealT y1 = Random1()*IMAGE_SIZE;
    it.Data1() = Vector2dC(x1,y1);

    // transform using true homography
    Vector2dC p2;
    RealT z = HomogTrue[2][0]*x1 + HomogTrue[2][1]*y1 + HomogTrue[2][2]*ZHOMOG1;
    p2[0] = (HomogTrue[0][0]*x1 + HomogTrue[0][1]*y1 + HomogTrue[0][2]*ZHOMOG1)
            *ZHOMOG2/z;
    p2[1] = (HomogTrue[1][0]*x1 + HomogTrue[1][1]*y1 + HomogTrue[1][2]*ZHOMOG1)
            *ZHOMOG2/z;

    // construct noisy observation, with some outliers
    if ( i >= 10 )
      it.Data2() = Vector2dC ( p2[0] + SIGMA*RandomGauss(),
			       p2[1] + SIGMA*RandomGauss() );
    else
#if 0
      it.Data2() = Vector2dC ( p2[0] + OUTLIER_SIGMA*RandomGauss(),
			       p2[1] + OUTLIER_SIGMA*RandomGauss() );
#else
      it.Data2() = Vector2dC ( Random1()*IMAGE_SIZE, Random1()*IMAGE_SIZE );
#endif

    // construct observation and add it to list
    MatrixRSC Ni = MatrixRSC(2);
    Ni.Fill(0.0);
    Ni[0][0] = Ni[1][1] = 1.0/SIGMA/SIGMA;

    // construct robust observation and add to list
    obsList.InsLast(ObservationHomog2dPointC(it.Data1(), Ni,
					     it.Data2(), Ni,
					     Sqr(OUTLIER_SIGMA/SIGMA), 5.0));
  }

  // list of compatible observations
  DListC<ObservationC> compatibleObsList;

  // fit homography using RANSAC
  StateVectorHomog2dC stateVecInit =
    InitialiseHomography(obsList, ZHOMOG1, ZHOMOG2, compatibleObsList);

  // initialise Levenberg-Marquardt algorithm
  LevenbergMarquardtC lm = LevenbergMarquardtC(stateVecInit,
					       compatibleObsList);

  cout << "2D homography fitting test (explicit): Initial residual=" << lm.GetResidual() << endl;
  cout << "Selected " << compatibleObsList.Size() << " observations using RANSAC" << endl;
  VectorC x = lm.SolutionVector();
  x *= 1.0/x[8];

  cout << "Initial: (" << x[0] << " " << x[1] << " " << x[2] << ")" << endl;
  cout << "         (" << x[3] << " " << x[4] << " " << x[5] << ")" << endl;
  cout << "         (" << x[6] << " " << x[7] << " " << x[8] << ")" << endl;
  PrintInlierFlags(obsList);

  // apply iterations
  RealT lambda = 100.0;
  for ( i = 0; i < 20; i++ ) {
    bool accepted = lm.Iteration(compatibleObsList, lambda);
    if ( accepted )
      // iteration succeeded in reducing the residual
      lambda /= 10.0;
    else
      // iteration failed to reduce the residual
      lambda *= 10.0;

    cout << " Accepted=" << accepted << " Residual=" << lm.GetResidual();
    cout << " DOF=" << 2*NPOINTS-8 << endl;
  }

  x = lm.SolutionVector();
  x *= 1.0/x[8];

  cout << "Solution: (" << x[0] << " " << x[1] << " " << x[2] << ")" << endl;
  cout << "          (" << x[3] << " " << x[4] << " " << x[5] << ")" << endl;
  cout << "          (" << x[6] << " " << x[7] << " " << x[8] << ")" << endl;
  cout << "True:" << HomogTrue[0][0] << " " << HomogTrue[0][1] << " " << HomogTrue[0][2] << ")" << endl;
  cout << "     " << HomogTrue[1][0] << " " << HomogTrue[1][1] << " " << HomogTrue[1][2] << ")" << endl;
  cout << "     " << HomogTrue[2][0] << " " << HomogTrue[2][1] << " " << HomogTrue[2][2] << ")" << endl;

  PrintInlierFlags(obsList);
  cout << endl;

  // Test shrink-wrapped function
  DListC<Point2dPairC> matchList;
  for(DLIterC<ObservationC> it(obsList);it;it++) {
      ObservationHomog2dPointC obs = it.Data();
      Vector2dC z2;
      z2[0] = obs.GetZ()[0];
      z2[1] = obs.GetZ()[1];
      matchList.InsLast(Point2dPairC(obs.GetZ1(), obs.GetNi1(),
				     z2,          obs.GetNi()));
  }
  
  StateVectorHomog2dC stateVec = FitHomography2d ( matchList,
						   ZHOMOG1, ZHOMOG2,
						   Sqr(OUTLIER_SIGMA/SIGMA),
						   5.0, RANSAC_ITERATIONS,
						   3.0, 10.0,
						   20, 100.0, 0.1 );

  return true;
}

static bool
 TestHomographyImplicit2dFit()
{
  SArray1dC<Vector2dC> coords1(NPOINTS), coords2(NPOINTS);
  DListC<ObservationC> obsList;

  // build arrays of x & y coordinates
  IntT i = 0;
  for(SArray1dIter2C<Vector2dC,Vector2dC> it(coords1,coords2);it;i++, it++)
  {
    // choose random x,y coordinates
    RealT x1 = Random1()*IMAGE_SIZE;
    RealT y1 = Random1()*IMAGE_SIZE;
    it.Data1() = Vector2dC(x1,y1);

    // transform using true homography
    Vector2dC p2;
    RealT z = HomogTrue[2][0]*x1 + HomogTrue[2][1]*y1 + HomogTrue[2][2]*ZHOMOG1;
    p2[0] = (HomogTrue[0][0]*x1 + HomogTrue[0][1]*y1 + HomogTrue[0][2]*ZHOMOG1)
            *ZHOMOG2/z;
    p2[1] = (HomogTrue[1][0]*x1 + HomogTrue[1][1]*y1 + HomogTrue[1][2]*ZHOMOG1)
            *ZHOMOG2/z;

    // construct noisy observation, with some outliers
    if ( i >= 10 ) {
      it.Data2() = Vector2dC ( p2[0] + SIGMA*RandomGauss(),
			       p2[1] + SIGMA*RandomGauss() );

      // add noise to first image as well
      it.Data1()[0] += SIGMA*RandomGauss();
      it.Data1()[1] += SIGMA*RandomGauss();
    }
    else {
      it.Data2() = Vector2dC ( Random1()*IMAGE_SIZE, Random1()*IMAGE_SIZE );
    }

    // construct observation and add it to list
    MatrixRSC Ni = MatrixRSC(2);
    Ni.Fill(0.0);
    Ni[0][0] = Ni[1][1] = 1.0/SIGMA/SIGMA;

    // construct observation and add to list
    obsList.InsLast(ObservationImpHomog2dPointC(it.Data1(), Ni,
						 it.Data2(), Ni,
						 Sqr(OUTLIER_SIGMA/SIGMA),
						 5.0));
  }

  // list of compatible observations
  DListC<ObservationC> compatibleObsList;

  // fit homography using RANSAC
  StateVectorHomog2dC stateVecInit =
    InitialiseHomography(obsList, ZHOMOG1, ZHOMOG2, compatibleObsList);

  // initialise Levenberg-Marquardt algorithm
  LevenbergMarquardtC lm = LevenbergMarquardtC(stateVecInit,
					       compatibleObsList);

  cout << "2D homography fitting test (implicit): Residual=" << lm.GetResidual() << endl;
  cout << "Selected " << compatibleObsList.Size() << " observations using RANSAC" << endl;
  VectorC x = lm.SolutionVector();
  x /= x[8];

  cout << "Initial: (" << x[0] << " " << x[1] << " " << x[2] << ")" << endl;
  cout << "         (" << x[3] << " " << x[4] << " " << x[5] << ")" << endl;
  cout << "         (" << x[6] << " " << x[7] << " " << x[8] << ")" << endl;
  PrintInlierFlags(obsList);

  // apply iterations
  RealT lambda = 0.1;
  for ( i = 0; i < 20; i++ ) {
    bool accepted = lm.Iteration(compatibleObsList, lambda);
    if ( accepted )
      // iteration succeeded in reducing the residual
      lambda /= 10.0;
    else
      // iteration failed to reduce the residual
      lambda *= 10.0;

    cout << " Accepted=" << accepted << " Residual=" << lm.GetResidual();
    cout << " DOF=" << 2*NPOINTS-8 << endl;
  }

  x = lm.SolutionVector();
  x *= 1.0/x[8];

  cout << "Solution: (" << x[0] << " " << x[1] << " " << x[2] << ")" << endl;
  cout << "          (" << x[3] << " " << x[4] << " " << x[5] << ")" << endl;
  cout << "          (" << x[6] << " " << x[7] << " " << x[8] << ")" << endl;
  PrintInlierFlags(obsList);
  cout << endl;
  return true;
}

int Main(int nargs,char **argv)
{
  if ( !TestHomography2dFit() ) {
    cout << "TestHomography2dFit() failed" << endl;
    return 1;
  }

  if ( !TestHomographyImplicit2dFit() ) {
    cout << "TestHomographyImplicit2dFit() failed" << endl;
    return 1;
  }

  return 0;
}

RAVL_ENTRY_POINT(Main);
