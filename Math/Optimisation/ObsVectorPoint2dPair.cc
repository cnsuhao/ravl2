// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/ObsVectorPoint2dPair.hh"

namespace RavlN {

  //: static method to build observation vector from sub-vectors
  VectorC ObsVectorPoint2dPairBodyC::BuildZ(const VectorC &nz1,
					    const VectorC &nz2)
  {
    VectorC z(4);

    z[0] = nz1[0];
    z[1] = nz1[1];
    z[2] = nz2[0];
    z[3] = nz2[1];
    return z;
  }

  //: static method to build observation inverse covariance from sub-matrices
  MatrixRSC ObsVectorPoint2dPairBodyC::BuildNi(const MatrixRSC &nNi1,
					       const MatrixRSC &nNi2)
  {
    MatrixRSC Ni(4);

    Ni.Fill(0.0);
    Ni[0][0] = nNi1[0][0]; Ni[0][1] = nNi1[0][1];
    Ni[1][0] = nNi1[1][0]; Ni[1][1] = nNi1[1][1];
    Ni[2][2] = nNi2[0][0]; Ni[2][3] = nNi2[0][1];
    Ni[3][2] = nNi2[1][0]; Ni[3][3] = nNi2[1][1];
    return Ni;
  }

  //: Constructor
  ObsVectorPoint2dPairBodyC::ObsVectorPoint2dPairBodyC(const VectorC &nz1,
						       const MatrixRSC &nNi1,
						       const VectorC &nz2,
						       const MatrixRSC &nNi2)
    : ObsVectorBodyC(BuildZ(nz1,nz2),BuildNi(nNi1,nNi2))
  {
  }

  //: static method to build observation vector from sub-vectors
  VectorC ObsVectorBGPoint2dPairBodyC::BuildZ(const VectorC &nz1,
					      const VectorC &nz2)
  {
    VectorC z(4);

    z[0] = nz1[0];
    z[1] = nz1[1];
    z[2] = nz2[0];
    z[3] = nz2[1];
    return z;
  }

  //: static method to build observation inverse covariance from sub-matrices
  MatrixRSC ObsVectorBGPoint2dPairBodyC::BuildNi(const MatrixRSC &nNi1,
						 const MatrixRSC &nNi2)
  {
    MatrixRSC Ni(4);

    Ni.Fill(0.0);
    Ni[0][0] = nNi1[0][0]; Ni[0][1] = nNi1[0][1];
    Ni[1][0] = nNi1[1][0]; Ni[1][1] = nNi1[1][1];
    Ni[2][2] = nNi2[0][0]; Ni[2][3] = nNi2[0][1];
    Ni[3][2] = nNi2[1][0]; Ni[3][3] = nNi2[1][1];
    return Ni;
  }

  //: Constructor
  ObsVectorBGPoint2dPairBodyC::ObsVectorBGPoint2dPairBodyC(const VectorC &nz1,
							   const MatrixRSC &nNi1,
							   const VectorC &nz2,
							   const MatrixRSC &nNi2,
							   RealT nvar_scale,
							   RealT nchi2_thres)
    : ObsVectorBiGaussianBodyC(BuildZ(nz1,nz2),BuildNi(nNi1,nNi2),
			       nvar_scale,nchi2_thres)
  {
  }

}
