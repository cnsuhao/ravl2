// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_MATRIX3D_HEADER
#define RAVL_MATRIX3D_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Math/LinearAlgebra/FixedSize/Matrix3d.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Math.Geometry.3D"

#include "Ravl/FMatrix.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: 3 by 3 matrix of real values.
  
  class Matrix3dC
    : public FMatrixC<3,3>
  {
  public:
    Matrix3dC()
    {}
    //: Default constructor.
    
    Matrix3dC(const TFMatrixC<RealT,3,3> &base)
      : FMatrixC<3,3>(base)
    {}
    //: Constructor.
    
    Matrix3dC(RealT v00,RealT v01,RealT v02,
	      RealT v10,RealT v11,RealT v12,
	      RealT v20,RealT v21,RealT v22) { 
      data[0][0] = v00;
      data[0][1] = v01;
      data[0][2] = v02;
      data[1][0] = v10;
      data[1][1] = v11;
      data[1][2] = v12;
      data[2][0] = v20;
      data[2][1] = v21;
      data[2][2] = v22;
    }
    //: Constructor.
    
    inline 
    RealT Det() const {
      return data[0][0] * (data[1][1]*data[2][2] - data[1][2]*data[2][1])
	+ data[1][0] * (data[2][1]*data[0][2] - data[2][2]*data[0][1])
	+ data[2][0] * (data[0][1]*data[1][2] - data[0][2]*data[1][1]);
    }
    
    bool Invert(Matrix3dC &op) const;
    //: Invert this matrix put the result in 'op'
    // Returns false if matrix is singular.
    // Note 'op' must no be this matrix.
    
    Matrix3dC Invert() const {
      Matrix3dC ret;
      Invert(ret);
      return ret;
    }
    //: Invert matrix and return result.
    
    bool InvertIP() {
      Matrix3dC org = (*this);
      return org.Invert(*this);
    }
    //: Invert matrix in place.
    
  protected:
  };

  inline
  TFVectorC<RealT,3> TFMatrixC<RealT,3,3>::operator*(const TFVectorC<RealT,3> & vec) const {
    TFVectorC<RealT,3> ret;
    ret[0] = data[0][0] * vec[0] + data[0][1] * vec[1] + data[0][2] * vec[2];
    ret[1] = data[1][0] * vec[0] + data[1][1] * vec[1] + data[1][2] * vec[2];
    ret[2] = data[2][0] * vec[0] + data[2][1] * vec[1] + data[2][2] * vec[2];
    return ret;
  }
  
  inline
  void MulAdd(const TFMatrixC<RealT,3,3> & R,const TFVectorC<RealT,3> & x, const TFVectorC<RealT,3> & t, TFVectorC<RealT,3> &result) {
    result[0] = R[0][0]*x[0] + R[0][1]*x[1] + R[0][2]*x[2] + t[0];    
    result[1] = R[1][0]*x[0] + R[1][1]*x[1] + R[1][2]*x[2] + t[1];    
    result[2] = R[2][0]*x[0] + R[2][1]*x[1] + R[2][2]*x[2] + t[2];    
  }
  
  inline
  void Mul(const TFMatrixC<RealT,3,3> & R,const TFVectorC<RealT,3> & x, TFVectorC<RealT,3> &result) {
    result[0] = R[0][0]*x[0] + R[0][1]*x[1] + R[0][2]*x[2];
    result[1] = R[1][0]*x[0] + R[1][1]*x[1] + R[1][2]*x[2];
    result[2] = R[2][0]*x[0] + R[2][1]*x[1] + R[2][2]*x[2];
  }
  
  inline
  void MulM(const TFMatrixC<RealT,3,3> & R1,const TFMatrixC<RealT,3,3> &R2,TFMatrixC<RealT,3,3> & result) {
    result[0][0] = R1[0][0]*R2[0][0] + R1[0][1]*R2[1][0] + R1[0][2]*R2[2][0];
    result[0][1] = R1[0][0]*R2[0][1] + R1[0][1]*R2[1][1] + R1[0][2]*R2[2][1];
    result[0][2] = R1[0][0]*R2[0][2] + R1[0][1]*R2[1][2] + R1[0][2]*R2[2][2];
    result[1][0] = R1[1][0]*R2[0][0] + R1[1][1]*R2[1][0] + R1[1][2]*R2[2][0];
    result[1][1] = R1[1][0]*R2[0][1] + R1[1][1]*R2[1][1] + R1[1][2]*R2[2][1];
    result[1][2] = R1[1][0]*R2[0][2] + R1[1][1]*R2[1][2] + R1[1][2]*R2[2][2];
    result[2][0] = R1[2][0]*R2[0][0] + R1[2][1]*R2[1][0] + R1[2][2]*R2[2][0];
    result[2][1] = R1[2][0]*R2[0][1] + R1[2][1]*R2[1][1] + R1[2][2]*R2[2][1];
    result[2][2] = R1[2][0]*R2[0][2] + R1[2][1]*R2[1][2] + R1[2][2]*R2[2][2];
  }
  
  inline
  void TMul(const TFMatrixC<RealT,3,3> & R,const TFVectorC<RealT,3> & x,TFVectorC<RealT,3> &result) {
    result[0] = R[0][0]*x[0] + R[1][0]*x[1] + R[2][0]*x[2];
    result[1] = R[0][1]*x[0] + R[1][1]*x[1] + R[2][1]*x[2];
    result[2] = R[0][2]*x[0] + R[1][2]*x[1] + R[2][2]*x[2];
  }
  
  inline
  RealT Determinant(const TFMatrixC<RealT,3,3> &mat) 
  { return ((const Matrix3dC &)mat).Det(); }
  //: Compute the determinant of a 3x3 matrix.
  
}

#endif
