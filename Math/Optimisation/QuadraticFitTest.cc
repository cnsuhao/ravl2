// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOptimise

#include "Ravl/LevenbergMarquardt.hh"
#include "Ravl/StateVectorQuadratic.hh"
#include "Ravl/ObservationQuadraticPoint.hh"
#include "Ravl/ObservationImpQuadraticPoint.hh"
#include "Ravl/ObsVectorBiGaussian.hh"
#include "Ravl/Random.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/EntryPnt.hh"

// RANSAC headers
#include "Ravl/Ransac.hh"
#include "Ravl/FitQuadraticPoints.hh"
#include "Ravl/EvaluateNumInliers.hh"

using namespace RavlN;

#define RANSAC_ITERATIONS 100

// Initialisation function for state vector
static StateVectorQuadraticC
 InitialiseQuadratic ( DListC<ObservationC> &obs_list, // input observation list
		       DListC<ObservationC> &compatible_obs_list ) // output list of compatible observations
{
  UIntT iteration;
  ObservationListManagerC obs_manager(obs_list);
  FitQuadraticPointsC fitter;
  EvaluateNumInliersC evaluator(3.0, 10.0);
  
  // use RANSAC to fit line
  RansacC ransac(obs_manager, fitter, evaluator);

  // select and evaluate the given number of samples
  for ( iteration=0; iteration < RANSAC_ITERATIONS; iteration++ )
    ransac.ProcessSample(3);

  // select observations compatible with solution
  compatible_obs_list = evaluator.CompatibleObservations(ransac.GetSolution(),
							 obs_list);
  return ransac.GetSolution();
}

static void
 PrintInlierFlags(DListC<ObservationC> obs_list)
{
  cout << "Inlier flags: ";
  for(DLIterC<ObservationC> it(obs_list);it;it++) {

    // get observation vector/inverse covariance object
    ObservationC& obs(it.Data());
    const ObsVectorBiGaussianC& obs_vec = obs.GetObsVec();

    // ignore observations that are not robust
    if(!obs_vec.IsValid()) {
      cout << "N";
      continue;
    }

    if(obs_vec.Outlier()) cout << "0";
    else cout << "1";
  }
    
  cout << endl;
}

// number of points
#define NPOINTS 100

// ground-truth quadratic coefficients a,b,c
#define A_TRUE 2.0
#define B_TRUE 3.0
#define C_TRUE 4.0

// noise standard deviation
#define SIGMA 0.1

// outlier noise standard deviation
#define OUTLIER_SIGMA 1.0

static void
 PrintBestEstimate ( SArray1dC<VectorC> coords )
{
  Matrix3dC A;
  Vector3dC b;

  A.Fill(0.0);
  b.Fill(0.0);

  // compute solution
  for(SArray1dIterC<VectorC> it(coords);it;it++) {
    VectorC xy = it.Data();
    RealT xc = xy[0];
    A[0][0] += xc*xc*xc*xc;
    A[0][1] += xc*xc*xc;
    A[0][2] += xc*xc;
    A[1][0] += xc*xc*xc;
    A[1][1] += xc*xc;
    A[1][2] += xc;
    A[2][0] += xc*xc;
    A[2][1] += xc;
    A[2][2] += 1.0;
    b[0] += xc*xc*xy[1];
    b[1] += xc*xy[1];
    b[2] += xy[1];
  }

  // solve linear equations
  SolveIP(A,b);
  cout << "Best estimate: a=" << b[0] << " b=" << b[1] << " c=" << b[2] << endl;
}

static bool
 TestExplicitQuadratic()
{
  SArray1dC<VectorC> coords(NPOINTS);
  DListC<ObservationC> obs_list;

  // build arrays of x & y coordinates
  IntT i = 0;
  for(SArray1dIterC<VectorC> it(coords);it;i++, it++) {
    // x-coordinates evenly spaced
    RealT x = (RealT) i;

    // construct y = a*x^2 + b*y + c + w with added Gaussian noise w
    it.Data() = VectorC ( x, A_TRUE*x*x + B_TRUE*x + C_TRUE
			     + SIGMA*RandomGauss() );
  }
  
  // construct point observations
  i=0;
  for(SArray1dIterC<VectorC> it(coords);it;it++, i++) {
    VectorC xy = it.Data();

    // construct observation and add to list
    obs_list.InsLast(ObservationQuadraticPointC(xy[0], xy[1], SIGMA));
  }

  // list of compatible observations
  DListC<ObservationC> compatible_obs_list;

  // fit initial quadratic parameters using RANSAC, selecting observations
  // compatible with initial quadratic parameters
  StateVectorQuadraticC state_vec_init = InitialiseQuadratic(obs_list, compatible_obs_list);

  // initialise Levenberg-Marquardt algorithm
  LevenbergMarquardtC lm = LevenbergMarquardtC(state_vec_init, obs_list);

  cout << "Explicit quadratic test: Initial residual=" << lm.GetResidual();
  cout << endl;

  // apply iterations
  RealT lambda = 10.0;
  for ( i = 0; i < 10; i++ ) {
    bool accepted = lm.Iteration(obs_list, lambda);
    if ( accepted )
      // iteration succeeded in reducing the residual
      lambda /= 10.0;
    else
      // iteration failed to reduce the residual
      lambda *= 10.0;

    StateVectorQuadraticC sv = lm.GetSolution();
    cout << " a=" << sv.GetA() << " b=" << sv.GetB() << " c=" << sv.GetC();
    cout << " Accepted=" << accepted << " Residual=" << lm.GetResidual();
    cout << " DOF=" << obs_list.Size()-3 << endl;
  }

  StateVectorQuadraticC sv = lm.GetSolution();
  cout << "Final solution: a=" << sv.GetA() << " b=" << sv.GetB() << " c=" << sv.GetC() << endl;
  PrintBestEstimate(coords);
  cout << endl;

  return true;
}

static bool
 TestRobustExplicitQuadratic()
{
  SArray1dC<VectorC> coords(NPOINTS);
  DListC<ObservationC> obs_list;

  // build arrays of x & y coordinates
  IntT i = 0;
  for(SArray1dIterC<VectorC> it(coords);it;i++, it++) {
    // x-coordinates evenly spaced
    RealT x = (RealT) i;

    // construct y = a*x^2 + b*y + c + w with added Gaussian noise w
    it.Data() = VectorC ( x, A_TRUE*x*x + B_TRUE*x + C_TRUE
			     + SIGMA*RandomGauss() );
  }
  
  // construct point observations
  i=0;
  for(SArray1dIterC<VectorC> it(coords);it;it++, i++) {
    VectorC xy = it.Data();

    // construct observation and add to list
    obs_list.InsLast(ObservationQuadraticPointC(
					xy[0],
					(i == 1)
					? xy[1]+OUTLIER_SIGMA*RandomGauss()
					: xy[1], SIGMA,
					Sqr(OUTLIER_SIGMA/SIGMA), 5.0));
  }

  // list of compatible observations
  DListC<ObservationC> compatible_obs_list;

  // fit initial quadratic parameters using RANSAC, selecting observations
  // compatible with initial quadratic parameters
  StateVectorQuadraticC state_vec_init = InitialiseQuadratic(obs_list, compatible_obs_list);

  // initialise Levenberg-Marquardt algorithm
  LevenbergMarquardtC lm = LevenbergMarquardtC(state_vec_init,
					       compatible_obs_list);

  cout << "Explicit robust quadratic test: Initial residual=" << lm.GetResidual() << endl;
  cout << "Selected " << compatible_obs_list.Size() << " observations using RANSAC" << endl;
  PrintInlierFlags(obs_list);

  // apply iterations
  RealT lambda = 10.0;
  for ( i = 0; i < 10; i++ ) {
    bool accepted = lm.Iteration(compatible_obs_list, lambda);
    if ( accepted )
      // iteration succeeded in reducing the residual
      lambda /= 10.0;
    else
      // iteration failed to reduce the residual
      lambda *= 10.0;

    StateVectorQuadraticC sv = lm.GetSolution();
    cout << " a=" << sv.GetA() << " b=" << sv.GetB() << " c=" << sv.GetC();
    cout << " Accepted=" << accepted << " Residual=" << lm.GetResidual();
    cout << " DOF=" << compatible_obs_list.Size()-3 << endl;
  }

  StateVectorQuadraticC sv = lm.GetSolution();
  cout << "Final solution: a=" << sv.GetA() << " b=" << sv.GetB() << " c=" << sv.GetC() << " Residual=" << lm.GetResidual() << endl;
  PrintInlierFlags(obs_list);
  cout << endl;

  return true;
}

static bool
 TestImplicitQuadratic()
{
  SArray1dC<VectorC> coords(NPOINTS);
  DListC<ObservationC> obs_list;

  // build arrays of x & y coordinates
  IntT i = 0;
  for(SArray1dIterC<VectorC> it(coords);it;i++, it++) {
    // x-coordinates evenly spaced
    RealT x = (RealT) i;

    // construct y = a*x^2 + b*y + c + w with added Gaussian noise w
    it.Data() = VectorC (x + SIGMA*RandomGauss(),
			 A_TRUE*x*x + B_TRUE*x + C_TRUE + SIGMA*RandomGauss());
  }
  
  // construct point observations
  for(SArray1dIterC<VectorC> it(coords);it;it++) {
    VectorC xy = it.Data();

    // construct observation and add to list
    obs_list.InsLast(ObservationImpQuadraticPointC(xy[0], xy[1], SIGMA));
  }

  // list of compatible observations
  DListC<ObservationC> compatible_obs_list;

  // fit initial quadratic parameters using RANSAC, selecting observations
  // compatible with initial quadratic parameters
  StateVectorQuadraticC state_vec_init = InitialiseQuadratic(obs_list, compatible_obs_list);

  // initialise Levenberg-Marquardt algorithm
  LevenbergMarquardtC lm = LevenbergMarquardtC(state_vec_init,obs_list);

  cout << "Implicit quadratic test: Initial residual=" << lm.GetResidual();
  cout << endl;

  // apply iterations
  RealT lambda = 0.1;
  for ( i = 0; i < 10; i++ ) {
    bool accepted = lm.Iteration(obs_list, lambda);
    if ( accepted )
      // iteration succeeded in reducing the residual
      lambda /= 10.0;
    else
      // iteration failed to reduce the residual
      lambda *= 10.0;

    StateVectorQuadraticC sv = lm.GetSolution();
    cout << " a=" << sv.GetA() << " b=" << sv.GetB() << " c=" << sv.GetC();
    cout << " Accepted=" << accepted << " Residual=" << lm.GetResidual();
    cout << " DOF=" << obs_list.Size()-3 << endl;
  }

  StateVectorQuadraticC sv = lm.GetSolution();
  cout << "Final solution: a=" << sv.GetA() << " b=" << sv.GetB() << " c=" << sv.GetC() << endl;
  cout << endl;
  return true;
}

int Main(int nargs,char **argv)
{
  if ( !TestExplicitQuadratic() ) {
    cout << "TestQuadraticExplicit() failed" << endl;
    return 1;
  }

  if ( !TestRobustExplicitQuadratic() ) {
    cout << "TestRobustQuadraticExplicit() failed" << endl;
    return 1;
  }

  if ( !TestImplicitQuadratic() ) {
    cout << "TestQuadraticImplicit() failed" << endl;
    return 1;
  }

  return 0;
}

RAVL_ENTRY_POINT(Main);
