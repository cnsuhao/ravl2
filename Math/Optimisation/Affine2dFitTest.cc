// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOptimise

#include "Ravl/LevenbergMarquardt.hh"
#include "Ravl/Ransac.hh"
#include "Ravl/StateVectorAffine2d.hh"
#include "Ravl/ObservationAffine2dPoint.hh"
#include "Ravl/FitAffine2dPoints.hh"
#include "Ravl/EvaluateNumInliers.hh"
#include "Ravl/Random.hh"

using namespace RavlN;

Affine2dC trueAffine(Matrix2dC(1.1,0.0,0.1,0.9),Vector2dC(3.0,10.0));

#define RANSAC_ITERATIONS 100

// Initialisation function for state vector for 2D homography fitting

static const StateVectorAffine2dC InitialiseAffine ( DListC<ObservationC> &obs_list, // observation list
						     DListC<ObservationC> &compatible_obs_list ) // output list of compatible observations
{
  UIntT iteration;
  ObservationListManagerC obs_manager(obs_list);
  FitAffine2dPointsC fitter;
  EvaluateNumInliersC evaluator(3.0, 10.0);
  
  // use RANSAC to fit homography
  RansacC ransac(obs_manager, fitter, evaluator);
  
  // select and evaluate the given number of samples
  for ( iteration=0; iteration < RANSAC_ITERATIONS; iteration++ )
    ransac.ProcessSample(6);

  // select observations compatible with solution
  compatible_obs_list = evaluator.CompatibleObservations(ransac.GetSolution(),
							 obs_list);
  return ransac.GetSolution();
}


// number of points
#define NPOINTS 200

// image width & height
#define IMAGE_SIZE 100

// noise standard deviation
#define SIGMA 0.5

// noise added to generate outliers
#define OUTLIER_SIGMA 10.0

int main() {
  DListC<ObservationC> obs_list;
  
  // build arrays of x & y coordinates
  int i;
  for(i = 0;i < NPOINTS;i++) {
    // choose random x,y coordinates
    RealT x1 = Random1()*IMAGE_SIZE;
    RealT y1 = Random1()*IMAGE_SIZE;
    Vector2dC p1( x1, y1 );
    
    // transform using true homography
    Vector2dC p2(trueAffine * p1);
    
    // construct noisy observation, with some outliers
    if ( i >= 10 )
      p2 += Vector2dC(SIGMA * RandomGauss(),SIGMA * RandomGauss());
    else
      p2 = Vector2dC ( Random1()*IMAGE_SIZE, Random1()*IMAGE_SIZE );
    
    // construct observation and add it to list
    MatrixRSC Ni = MatrixRSC(2);
    Ni.Fill(0.0);
    Ni[0][0] = Ni[1][1] = 1.0/SIGMA/SIGMA;
    
    // construct robust observation and add to list
    obs_list.InsLast(ObservationAffine2dPointC(VectorC(p1), Ni,
					       VectorC(p2), Ni));
  }

  DListC<ObservationC> compatible_obs_list;
  
  StateVectorAffine2dC sv = InitialiseAffine(obs_list,compatible_obs_list);
  
  cerr << "Ransac solution=" << sv.GetAffine() << "\n";

  // initialise Levenberg-Marquardt algorithm
  LevenbergMarquardtC lm = LevenbergMarquardtC(sv,
					       compatible_obs_list);
  

  // apply iterations
  RealT lambda = 100.0;
  for ( i = 0; i < 20; i++ ) {
    bool accepted = lm.Iteration(compatible_obs_list, lambda);
    if ( accepted )
      // iteration succeeded in reducing the residual
      lambda /= 10.0;
    else
      // iteration failed to reduce the residual
      lambda *= 10.0;
    
    cout << " Accepted=" << accepted << " Residual=" << lm.GetResidual();
    cout << " DOF=" << 2*NPOINTS-8 << endl;
  }
  VectorC x = lm.SolutionVector();
  
  cerr << "Solution=" << x << "\n";
  
  return 0;
}
