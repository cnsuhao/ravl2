// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/StateVectorHomog2d.hh"

namespace RavlN {

  //: Constructor
  StateVectorHomog2dBodyC::StateVectorHomog2dBodyC(const VectorC &nx,
						   RealT nzh1, RealT nzh2,
						   RealT ngauge_weight)
    : StateVectorBodyC(nx)
  {
    zh1 = nzh1;
    zh2 = nzh2;
    gauge_weight = ngauge_weight;
    Postprocess();
  }

  //: Constructor
  StateVectorHomog2dBodyC::StateVectorHomog2dBodyC(const VectorC &nx,
						   RealT nzh1, RealT nzh2,
						   RealT ngauge_weight,
						   const VectorC &nxstep)
    : StateVectorBodyC(nx,nxstep)
  {
    zh1 = nzh1;
    zh2 = nzh2;
    gauge_weight = ngauge_weight;
    Postprocess();
  }

  //: Constructor.
  StateVectorHomog2dBodyC::StateVectorHomog2dBodyC(const VectorC &nx,
						   RealT nzh1, RealT nzh2,
						   RealT ngauge_weight,
						   const VectorC &nxstep,
						   const Matrix3dC &Pnew) 
    : StateVectorBodyC(nx,nxstep),
      P(Pnew)
  {
    zh1 = nzh1;
    zh2 = nzh2;
    gauge_weight = ngauge_weight;
    Postprocess();
  }
  
  //: Increment the linear system
  // This assumes that the homography is normalised to unit Frobenius norm,
  // so there is nothing to add to vector a.
  bool StateVectorHomog2dBodyC::IncrementLS(MatrixRSC &A, VectorC &a)
  {
    MatrixC xxT = x.OuterProduct();
    MatrixRSC xxTS(xxT);

    xxTS *= gauge_weight;
    A += xxTS;
    return true;
  }

  //: Postprocess 2D homography state vector after an adjustment to the
  //: parameters.
  bool StateVectorHomog2dBodyC::Postprocess()
  {
    // normalise to unit Frobenius norm
    x /= sqrt(x.SumOfSqr());

    // construct new 2D homography matrix
    P = Matrix3dC(x[0], x[1], x[2],
		  x[3], x[4], x[5],
		  x[6], x[7], x[8]);

    return true;
  }

  //: Get 2D homography represented by state vector
  const Matrix3dC StateVectorHomog2dBodyC::GetHomog() const
  {
    return P;
  }

  //: Return 3rd homogeneous coordinate of first plane
  RealT StateVectorHomog2dBodyC::GetZH1() const
  {
    return zh1;
  }

  //: Return 3rd homogeneous coordinate of second plane
  RealT StateVectorHomog2dBodyC::GetZH2() const
  {
    return zh2;
  }

}
