// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/LevenbergMarquardt.hh"
#include "Ravl/StateVectorLine2d.hh"
#include "Ravl/ObservationLine2dPoint.hh"
#include "Ravl/ObsVectorBiGaussian.hh"
#include "Ravl/Random.hh"
#include "Ravl/EntryPnt.hh"

using namespace RavlN;

#define ZHOMOG 100.0

// Initialisation function for state vector
static bool
 InitialiseLine2d ( DListC<ObservationC> &obs_list, // observation list
		    RealT &lx, RealT &ly, RealT &lz ) // line parameters
{
  ObservationLine2dPointC obs;
  RealT x1, y1, x2, y2;

  // we need at least two points to fit a 2D line
  if ( obs_list.Size() < 2 ) return false;

  // initialise line lx*x + ly*y + lz*zh by fitting to two points (x1,y1) and
  // (x2,y2) which gives us
  //
  //     lx = zh*(y2-y1), ly = zh*(x1-x2), lz = x2*y1-x1*y2
  //
  // We use the first and the last points

  obs = obs_list.First(); x1 = obs.GetZ()[0]; y1 = obs.GetZ()[1];
  obs = obs_list.Last();  x2 = obs.GetZ()[0]; y2 = obs.GetZ()[1];
  lx = ZHOMOG*(y2-y1);
  ly = ZHOMOG*(x1-x2);
  lz = x2*y1-x1*y2;
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

// ground-truth line coefficients lx,ly,lz
#define LX_TRUE 2.0
#define LY_TRUE 3.0
#define LZ_TRUE 4.0

// noise standard deviation
#define SIGMA 0.1

// outlier noise standard deviation
#define OUTLIER_SIGMA 1.0

static void
 PrintBestEstimate ( SArray1dC<VectorC> coords )
{
  RealT Sx=0.0, Sy=0.0, Sxx=0.0, Sxy=0.0, Syy=0.0;
  UIntT n=0;

  // compute solution by orthogonal regression
  for(SArray1dIterC<VectorC> it(coords);it;it++) {
    VectorC xy = it.Data();

    Sx += xy[0]; Sy += xy[1];
    Sxx += xy[0]*xy[0]; Sxy += xy[0]*xy[1]; Syy += xy[1]*xy[1];
    n++;
  }

  // compute sums normalized for centroid
  RealT nr = (RealT) n;
  RealT p = Sxx - Sx*Sx/nr;
  RealT q = Sxy - Sx*Sy/nr;
  RealT r = Syy - Sy*Sy/nr;

  // compute smallest non-zero eigenvalue of covariance
  // matrix (p q 0)
  //        (q r 0)
  //        (0 0 0)
  RealT lambda = 0.5*(p + r - sqrt((p-r)*(p-r) + 4.0*q*q));

  // compute line parameters lx*x + ly*y + lz = 0
  RealT lx = q;
  RealT ly = lambda - p;
  RealT lz = -(lx*Sx + ly*Sy)/nr;
  RealT s = sqrt(lx*lx + ly*ly);

  // normalise to lx*lx + ly*ly = 1 and convert to lx*x + ly*y + lz*zh = 0
  lx /= s;
  ly /= s;
  lz /= ZHOMOG*s;

  cout << "Orthogonal regression: lx=" << lx << " ly=" << ly << " lz=" << lz;
  cout << endl;
}

static bool
 TestLine2dFit()
{
  SArray1dC<VectorC> coords(NPOINTS);
  DListC<ObservationC> obs_list;

  // build arrays of x & y coordinates
  IntT i = 0;
  for(SArray1dIterC<VectorC> it(coords);it;i++, it++) {
    // x-coordinates evenly spaced
    RealT x = (RealT) i;

    // construct y = a*x^2 + b*y + c + w with added Gaussian noise w
    it.Data() = VectorC ( x + SIGMA*RandomGauss(),
			  -(LX_TRUE*x + LZ_TRUE*ZHOMOG)/LY_TRUE
			  + SIGMA*RandomGauss() );
  }
  
  // construct point observations and create list
  i=0;
  MatrixRSC Ni(2);
  Ni.Fill(0.0);
  Ni[0][0] = Ni[1][1] = 1.0/(SIGMA*SIGMA);
  for(SArray1dIterC<VectorC> it(coords);it;it++, i++)
    obs_list.InsLast(ObservationLine2dPointC(it.Data(), Ni));

  // initialise Levenberg-Marquardt algorithm
  RealT lx, ly, lz;
  InitialiseLine2d(obs_list, lx, ly, lz);
  StateVectorLine2dC state_vec_init(lx,ly,lz,ZHOMOG);
  LevenbergMarquardtC lm = LevenbergMarquardtC(state_vec_init,obs_list);

  cout << "Line 2D fitting test: Initial residual=" << lm.Residual() << endl;

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

    StateVectorLine2dC sv = lm.GetStateVec();
    cout << " a=" << sv.GetLx() << " b=" << sv.GetLy() << " c=" << sv.GetLz();
    cout << " Accepted=" << accepted << " Residual=" << lm.Residual();
    cout << " DOF=" << NPOINTS-2 << endl;
  }

  StateVectorLine2dC sv = lm.GetStateVec();
  cout << "Final solution: lx=" << sv.GetLx() << " ly=" << sv.GetLy() << " lz=" << sv.GetLz() << endl;
  PrintBestEstimate(coords);
  cout << endl;

  return true;
}

static bool
 TestLine2dRobustFit()
{
  SArray1dC<VectorC> coords(NPOINTS);
  DListC<ObservationC> obs_list;

  // build arrays of x & y coordinates
  IntT i = 0;
  for(SArray1dIterC<VectorC> it(coords);it;i++, it++) {
    // x-coordinates evenly spaced
    RealT x = (RealT) i;

    if ( i >= 0 && i < 10 )
      // outlier point
      it.Data() = VectorC ( x + OUTLIER_SIGMA*RandomGauss(),
			  -(LX_TRUE*x + LZ_TRUE*ZHOMOG)/LY_TRUE
			  + OUTLIER_SIGMA*RandomGauss() );
    else
      // construct y = a*x^2 + b*y + c + w with added Gaussian noise w
      it.Data() = VectorC ( x + SIGMA*RandomGauss(),
			    -(LX_TRUE*x + LZ_TRUE*ZHOMOG)/LY_TRUE
			    + SIGMA*RandomGauss() );
  }
  
  // construct point observations and create list
  i=0;
  MatrixRSC Ni(2);
  Ni.Fill(0.0);
  Ni[0][0] = Ni[1][1] = 1.0/(SIGMA*SIGMA);
  for(SArray1dIterC<VectorC> it(coords);it;it++, i++)
    obs_list.InsLast(ObservationLine2dPointC(it.Data(), Ni,
					     Sqr(OUTLIER_SIGMA/SIGMA), 5.0));

  // initialise Levenberg-Marquardt algorithm
  RealT lx, ly, lz;
  InitialiseLine2d(obs_list, lx, ly, lz);
  StateVectorLine2dC state_vec_init(lx,ly,lz,ZHOMOG);
  LevenbergMarquardtC lm = LevenbergMarquardtC(state_vec_init,obs_list);

  cout << "Line 2D robust fitting test: Initial residual=" << lm.Residual() << endl;
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

    StateVectorLine2dC sv = lm.GetStateVec();
    cout << " lx=" << sv.GetLx() << " ly=" << sv.GetLy() << " lz=" << sv.GetLz();
    cout << " Accepted=" << accepted << " Residual=" << lm.Residual();
    cout << " DOF=" << NPOINTS-2 << endl;
  }

  StateVectorLine2dC sv = lm.GetStateVec();
  cout << "Final solution: lx=" << sv.GetLx() << " ly=" << sv.GetLy() << " lz=" << sv.GetLz() << endl;
  PrintInlierFlags(obs_list);
  cout << endl;

  return true;
}

int Main(int nargs,char **argv)
{
  if ( !TestLine2dFit() ) {
    cout << "TestLine2dFit() failed" << endl;
    return 1;
  }

  if ( !TestLine2dRobustFit() ) {
    cout << "TestLine2dRobustFit() failed" << endl;
    return 1;
  }

  return 0;
}

RAVL_ENTRY_POINT(Main);
