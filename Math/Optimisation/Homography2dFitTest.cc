// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/LevenbergMarquardt.hh"
#include "Ravl/StateVectorHomog2d.hh"
#include "Ravl/ObservationHomog2dPoint.hh"
#include "Ravl/ObservationImpHomog2dPoint.hh"
#include "Ravl/ObsVectorBiGaussian.hh"
#include "Ravl/Random.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/SArr1Iter2.hh"

using namespace RavlN;

// ground-truth 2D homography
const Matrix3dC HomogTrue = Matrix3dC(1.1, 0.0,  3.0,
				      0.1, 0.9, 10.0,
				      0.0, 0.0,  1.0);

// Initialisation function for state vector for 2D homography fitting
static bool
 InitialiseHomography ( DListC<ObservationC> &obs_list, // observation list
			VectorC &x ) // state vector to be initialised
{
  // This should be using RANSAC. For now use identity
  x[0] = 1.0; x[1] = 0.0; x[2] = 0.0;
  x[3] = 0.0; x[4] = 1.0; x[5] = 0.0;
  x[6] = 0.0; x[7] = 0.0; x[8] = 1.0;

  return true;
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

static bool
 TestHomography2dFit()
{
  SArray1dC<VectorC> coords1(NPOINTS), coords2(NPOINTS);
  DListC<ObservationC> obs_list;

  // build arrays of x & y coordinates
  IntT i = 0;
  for(SArray1dIter2C<VectorC,VectorC> it(coords1,coords2);it;i++, it++)
  {
    // choose random x,y coordinates
    RealT x1 = Random1()*IMAGE_SIZE;
    RealT y1 = Random1()*IMAGE_SIZE;
    it.Data1() = VectorC ( x1, y1 );

    // transform using true homography
    VectorC p2(2);
    RealT z = HomogTrue[2][0]*x1 + HomogTrue[2][1]*y1 + HomogTrue[2][2]*ZHOMOG1;
    p2[0] = (HomogTrue[0][0]*x1 + HomogTrue[0][1]*y1 + HomogTrue[0][2]*ZHOMOG1)
            *ZHOMOG2/z;
    p2[1] = (HomogTrue[1][0]*x1 + HomogTrue[1][1]*y1 + HomogTrue[1][2]*ZHOMOG1)
            *ZHOMOG2/z;

    // construct noisy observation, with some outliers
    if ( i >= 10 )
      it.Data2() = VectorC ( p2[0] + SIGMA*RandomGauss(),
			     p2[1] + SIGMA*RandomGauss() );
    else
#if 1
      it.Data2() = VectorC ( p2[0] + OUTLIER_SIGMA*RandomGauss(),
			     p2[1] + OUTLIER_SIGMA*RandomGauss() );
#else
      it.Data2() = VectorC ( Random1()*IMAGE_SIZE, Random1()*IMAGE_SIZE );
#endif

    // construct observation and add it to list
    MatrixRSC Ni = MatrixRSC(2);
    Ni.Fill(0.0);
    Ni[0][0] = Ni[1][1] = 1.0/SIGMA/SIGMA;

    // construct robust observation and add to list
    obs_list.InsLast(ObservationHomog2dPointC(it.Data1(), Ni,
					      it.Data2(), Ni,
					      Sqr(OUTLIER_SIGMA/SIGMA), 5.0));
  }

  // initialise Levenberg-Marquardt algorithm
  VectorC x = VectorC(9);
  InitialiseHomography(obs_list, x);

  StateVectorHomog2dC state_vec_init(x, ZHOMOG1, ZHOMOG2, GAUGE_WEIGHT);
  LevenbergMarquardtC lm = LevenbergMarquardtC(state_vec_init,obs_list);

  cout << "2D homography fitting test (explicit): Initial residual=" << lm.GetResidual() << endl;
  PrintInlierFlags(obs_list);

  // apply iterations
  RealT lambda = 100.0;
  for ( i = 0; i < 20; i++ ) {
    bool accepted = lm.Iteration(obs_list, lambda);
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
  cout << "True:" << HomogTrue;

  PrintInlierFlags(obs_list);
  cout << endl;

  return true;
}

static bool
 TestHomographyImplicit2dFit()
{
  SArray1dC<VectorC> coords1(NPOINTS), coords2(NPOINTS);
  DListC<ObservationC> obs_list;

  // build arrays of x & y coordinates
  IntT i = 0;
  for(SArray1dIter2C<VectorC,VectorC> it(coords1,coords2);it;i++, it++)
  {
    // choose random x,y coordinates
    RealT x1 = Random1()*IMAGE_SIZE;
    RealT y1 = Random1()*IMAGE_SIZE;
    it.Data1() = VectorC ( x1, y1 );

    // transform using true homography
    VectorC p2(2);
    RealT z = HomogTrue[2][0]*x1 + HomogTrue[2][1]*y1 + HomogTrue[2][2]*ZHOMOG1;
    p2[0] = (HomogTrue[0][0]*x1 + HomogTrue[0][1]*y1 + HomogTrue[0][2]*ZHOMOG1)
            *ZHOMOG2/z;
    p2[1] = (HomogTrue[1][0]*x1 + HomogTrue[1][1]*y1 + HomogTrue[1][2]*ZHOMOG1)
            *ZHOMOG2/z;

    // construct noisy observation, with some outliers
    if ( i >= 10 ) {
      it.Data2() = VectorC ( p2[0] + SIGMA*RandomGauss(),
			     p2[1] + SIGMA*RandomGauss() );

      // add noise to first image as well
      it.Data1()[0] += SIGMA*RandomGauss();
      it.Data1()[1] += SIGMA*RandomGauss();
    }
    else {
      it.Data2() = VectorC ( p2[0] + OUTLIER_SIGMA*RandomGauss(),
			     p2[1] + OUTLIER_SIGMA*RandomGauss() );

      // add noise to first image as well
      it.Data1()[0] += OUTLIER_SIGMA*RandomGauss();
      it.Data1()[1] += OUTLIER_SIGMA*RandomGauss();
    }

    // construct observation and add it to list
    MatrixRSC Ni = MatrixRSC(2);
    Ni.Fill(0.0);
    Ni[0][0] = Ni[1][1] = 1.0/SIGMA/SIGMA;

    // construct observation and add to list
    obs_list.InsLast(ObservationImpHomog2dPointC(it.Data1(), Ni,
						 it.Data2(), Ni,
						 Sqr(OUTLIER_SIGMA/SIGMA),
						 5.0));
  }

  // initialise Levenberg-Marquardt algorithm
  VectorC x = VectorC(9);
  InitialiseHomography(obs_list, x);

  StateVectorHomog2dC state_vec_init(x, ZHOMOG1, ZHOMOG2, GAUGE_WEIGHT);
  LevenbergMarquardtC lm = LevenbergMarquardtC(state_vec_init,obs_list);

  cout << "2D homography fitting test (implicit): Residual=" << lm.GetResidual() << endl;
  PrintInlierFlags(obs_list);

  // apply iterations
  RealT lambda = 0.1;
  for ( i = 0; i < 20; i++ ) {
    bool accepted = lm.Iteration(obs_list, lambda);
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
  PrintInlierFlags(obs_list);
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
