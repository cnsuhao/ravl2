// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/LevenbergMarquardt.hh"
#include "Ravl/StateVectorQuadratic.hh"
#include "Ravl/ObservationQuadraticPoint.hh"
#include "Ravl/ObservationImpQuadraticPoint.hh"
#include "Ravl/ObsVectorBiGaussian.hh"
#include "Ravl/Random.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/EntryPnt.hh"

using namespace RavlN;

// Initialisation function for state vector
static bool
 InitialiseQuadratic ( DListC<ObservationC> &obs_list, // observation list
		       RealT &a, RealT &b, RealT &c ) // quadratic parameters
{
  Matrix3dC Am = Matrix3dC();
  Vector3dC bv = Vector3dC();

  // we need at least three points to fit a quadratic
  if ( obs_list.Size() < 3 ) return false;

  // initialise quadratic by interpolating three points: the first, middle and
  // last point in the list of point observations. We construct equations
  //
  //     (y1)   (x1*x1 x1 1) (a)
  //     (y2) = (x2*x2 x2 1) (b) = A * b for 3x3 matrix A and 3-vector b
  //     (y3)   (x3*x3 x3 1) (c)
  //
  //  and solve the equations by direct matrix inversion (not pretty...) to
  //  obtain our first estimate of a, b, c given points (x1,y1), (x2,y2) and
  //  (x3,y3).

  // dummy state vector
  StateVectorQuadraticC state_vec(0.0,0.0,0.0);

  // first point
  {
    ObservationQuadraticPointC obs = obs_list.First();
    MatrixC Hx = obs.EvaluateJacobianHx(state_vec); // evaluate Jacobian
    Am[0][0] = Hx[0][0]; Am[0][1] = Hx[0][1]; Am[0][2] = Hx[0][2]; // first row
    bv[0] = obs.GetZ()[0]; // fill first entry in b vector
  }

  // middle point
  {
    ObservationQuadraticPointC obs = obs_list.Nth(obs_list.Size()/2-1);
    MatrixC Hx = obs.EvaluateJacobianHx(state_vec); // evaluate Jacobian
    Am[1][0] = Hx[0][0]; Am[1][1] = Hx[0][1]; Am[1][2] = Hx[0][2]; //second row
    bv[1] = obs.GetZ()[0]; // fill second entry in b vector
  }
    
  // last point
  {
    ObservationQuadraticPointC obs = obs_list.Last();
    MatrixC Hx = obs.EvaluateJacobianHx(state_vec); // evaluate Jacobian
    Am[2][0] = Hx[0][0]; Am[2][1] = Hx[0][1]; Am[2][2] = Hx[0][2]; // third row
    bv[2] = obs.GetZ()[0]; // fill third entry in b vector */
  }

  // invert matrix and solve (don't do this at home)
  Matrix3dC Ainv = Am.Inverse();
  Vector3dC Ainvb = Ainv*bv;
  a = Ainvb[0];
  b = Ainvb[1];
  b = Ainvb[2];
  return true;
}

// Initialisation function for state vector from implicit observations
static bool
 InitialiseImpQuadratic ( DListC<ObservationC> &obs_list, // observation list
			  RealT &a, RealT &b, RealT &c ) //quadratic parameters
{
  Matrix3dC Am = Matrix3dC();
  Vector3dC bv = Vector3dC();

  // we need at least three points to fit a quadratic
  if ( obs_list.Size() < 3 ) return false;

  // initialise quadratic by interpolating three points: the first, middle and
  // last point in the list of point observations. We construct equations
  //
  //     (y1)   (x1*x1 x1 1) (a)
  //     (y2) = (x2*x2 x2 1) (b) = A * b for 3x3 matrix A and 3-vector b
  //     (y3)   (x3*x3 x3 1) (c)
  //
  //  and solve the equations by direct matrix inversion (not pretty...) to
  //  obtain our first estimate of a, b, c given points (x1,y1), (x2,y2) and
  //  (x3,y3).

  // dummy state vector
  StateVectorQuadraticC state_vec(0.0,0.0,0.0);

  // first point
  {
    ObservationImpQuadraticPointC obs = obs_list.First();
    MatrixC Hx = obs.EvaluateJacobianFx(state_vec); // evaluate Jacobian
    Am[0][0] = Hx[0][0]; Am[0][1] = Hx[0][1]; Am[0][2] = Hx[0][2]; // first row
    bv[0] = obs.GetZ()[0]; // fill first entry in b vector
  }

  // middle point
  {
    ObservationImpQuadraticPointC obs = obs_list.Nth(obs_list.Size()/2-1);
    MatrixC Hx = obs.EvaluateJacobianFx(state_vec); // evaluate Jacobian
    Am[1][0] = Hx[0][0]; Am[1][1] = Hx[0][1]; Am[1][2] = Hx[0][2]; //second row
    bv[1] = obs.GetZ()[0]; // fill second entry in b vector
  }

  // last point
  {
    ObservationImpQuadraticPointC obs = obs_list.Last();
    MatrixC Hx = obs.EvaluateJacobianFx(state_vec); // evaluate Jacobian
    Am[2][0] = Hx[0][0]; Am[2][1] = Hx[0][1]; Am[2][2] = Hx[0][2]; // third row
    bv[2] = obs.GetZ()[0]; // fill third entry in b vector */
  }

  // invert matrix and solve (don't do this at home)
  Matrix3dC Ainv = Am.Inverse();
  Vector3dC Ainvb = Ainv*bv;
  a = Ainvb[0];
  b = Ainvb[1];
  c = Ainvb[2];
  return true;
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

  // invert matrix and solve (don't do this at home)
  Matrix3dC Ainv = A.Inverse();
  Vector3dC Ainvb = Ainv*b;
  cout << "Best estimate: a=" << Ainvb[0] << " b=" << Ainvb[1] << " c=" << Ainvb[2] << endl;
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

  // initialise Levenberg-Marquardt algorithm
  RealT a, b, c;
  InitialiseQuadratic(obs_list, a, b, c);
  StateVectorQuadraticC state_vec_init(a,b,c);
  LevenbergMarquardtC lm = LevenbergMarquardtC(state_vec_init,obs_list);

  cout << "Explicit quadratic test: Initial residual=" << lm.Residual() <<endl;

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

    StateVectorQuadraticC sv = lm.GetStateVec();
    cout << " a=" << sv.GetA() << " b=" << sv.GetB() << " c=" << sv.GetC();
    cout << " Accepted=" << accepted << " Residual=" << lm.Residual();
    cout << " DOF=" << NPOINTS-3 << endl;
  }

  StateVectorQuadraticC sv = lm.GetStateVec();
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

  // initialise Levenberg-Marquardt algorithm
  RealT a, b, c;

  InitialiseQuadratic(obs_list, a, b, c);
  StateVectorQuadraticC state_vec_init(a,b,c);
  LevenbergMarquardtC lm = LevenbergMarquardtC(state_vec_init,obs_list);

  cout << "Explicit robust quadratic test: Initial residual=" << lm.Residual() << endl;
  PrintInlierFlags(obs_list);

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

    StateVectorQuadraticC sv = lm.GetStateVec();
    cout << " a=" << sv.GetA() << " b=" << sv.GetB() << " c=" << sv.GetC();
    cout << " Accepted=" << accepted << " Residual=" << lm.Residual();
    cout << " DOF=" << NPOINTS-3 << endl;
  }

  StateVectorQuadraticC sv = lm.GetStateVec();
  cout << "Final solution: a=" << sv.GetA() << " b=" << sv.GetB() << " c=" << sv.GetC() << " Residual=" << lm.Residual() << endl;
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

  // initialise Levenberg-Marquardt algorithm
  RealT a, b, c;

  InitialiseImpQuadratic(obs_list, a, b, c);
  StateVectorQuadraticC state_vec_init(a,b,c);
  LevenbergMarquardtC lm = LevenbergMarquardtC(state_vec_init,obs_list);

  cout << "Implicit quadratic test: Initial residual=" << lm.Residual() <<endl;

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

    StateVectorQuadraticC sv = lm.GetStateVec();
    cout << " a=" << sv.GetA() << " b=" << sv.GetB() << " c=" << sv.GetC();
    cout << " Accepted=" << accepted << " Residual=" << lm.Residual();
    cout << " DOF=" << NPOINTS-3 << endl;
  }

  StateVectorQuadraticC sv = lm.GetStateVec();
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
