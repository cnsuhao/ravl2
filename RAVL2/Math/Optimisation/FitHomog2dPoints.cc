// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlOptimise
//! file="Ravl/Math/Optimisation/FitHomog2dPoints.cc"

#include "Ravl/FitHomog2dPoints.hh"
#include "Ravl/StateVectorHomog2d.hh"
#include "Ravl/ObservationHomog2dPoint.hh"
#include "Ravl/ObservationImpHomog2dPoint.hh"
#include "Ravl/Matrix3d.hh"

namespace RavlN {

  //: Constructor.
  FitHomog2dPointsBodyC::FitHomog2dPointsBodyC(RealT nzh1, RealT nzh2)
  {
    zh1 = nzh1;
    zh2 = nzh2;
  }

  //: Constructor.
  FitHomog2dPointsBodyC::FitHomog2dPointsBodyC()
  {
    zh1 = zh2 = 1.0;
  }

  //: Fit parameters to sample of observations
  StateVectorC FitHomog2dPointsBodyC::FitModel(DListC<ObservationC> sample)
  {
    // we need at least four points to fit a 2D line
    if ( sample.Size() < 4 )
      throw ExceptionC("Sample size too small in FitHomog2dPointsBodyC::FitToSample(). ");

    if ( sample.Size() == 4 ) {
      // initialise homography P by fitting to four point pairs, assuming that
      // bottom-right element P[2][2] is not zero.

      // Construct 8x8 matrix of linear equations
      MatrixC A(8,8);
      A.Fill(0.0);
      VectorC b(8);

      // distinguish between explicit and implicit forms of point observations
      IntT i=0;
      for(DLIterC<ObservationC> it(sample);it;it++, i++) {
	const ObservationC &obs = it.Data();
	RealT x1, y1, x2, y2;
	if ( dynamic_cast<const ObservationExplicitBodyC *>(&obs.Body()) != 0 ) {
	  // explicit form of point observation
	  const ObservationHomog2dPointC &eobs = obs;
	  x1=eobs.GetZ1()[0]; y1=eobs.GetZ1()[1];
	  x2=eobs.GetZ()[0];  y2=eobs.GetZ()[1];
	}
	else {
	  // implicit form of point observation
	  const ObservationImpHomog2dPointC &iobs = obs;
	  x1=iobs.GetZ()[0]; y1=iobs.GetZ()[1];
	  x2=iobs.GetZ()[2]; y2=iobs.GetZ()[3];
	}

	A[i*2][0] = x1*zh2; A[i*2][1] = y1*zh2; A[i*2][2] = zh1*zh2;
	A[i*2][6] = -x1*x2; A[i*2][7] = -y1*x2;
	b[i*2] = zh1*x2;
	A[i*2+1][3] = x1*zh2; A[i*2+1][4] = y1*zh2; A[i*2+1][5] = zh1*zh2;
	A[i*2+1][6] = -x1*y2; A[i*2+1][7] = -y1*y2;
	b[i*2+1] = zh1*y2;
      }

      // solve for solution vector
      if(!SolveIP(A,b))
	throw ExceptionNumericalC("Dependent linear equations in FitHomog2dPointsBodyC::FitModel(DListC<ObservationC>). ");

      Matrix3dC P(b[0], b[1], b[2],
		  b[3], b[4], b[5],
		  b[6], b[7], 1.0);
      return StateVectorHomog2dC (P,zh1,zh2);
    }

    // compute solution for homography parameters using symmetric eigensystem
    // method
    throw ExceptionC("Null-space method not implemented in FitHomog2dPointsBodyC::FitToSample(). ");
    Matrix3dC P(1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0);
    StateVectorHomog2dC sv(P,zh1,zh2);
    return sv;
  }
}
