// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATRIX2D_HEADER
#define RAVLMATRIX2D_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Math/LinearAlgebra/FixedSize/Matrix2d.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Math.Geometry.2D"

#include "Ravl/FMatrix.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: 2 by 2 matrix of real values.
  
  class Matrix2dC
    : public FMatrixC<2,2>
  {
  public:
    Matrix2dC()
      {}
    //: Default constructor.
    
    Matrix2dC(const TFMatrixC<RealT,2,2> &base)
      : FMatrixC<2,2>(base)
      {}
    //: Constructor.
    
    Matrix2dC(RealT v00,RealT v01,RealT v10,RealT v11) { 
      data[0][0] = v00;
      data[0][1] = v01;
      data[1][0] = v10;
      data[1][1] = v11;
    }
    //: Constructor.
    
    inline RealT Det() const 
      { return data[0][0]*data[1][1] - data[0][1]*data[1][0]; }
    //: Returns the value of the determinant of this matrix.

  };


  inline
  TFVectorC<RealT,2> TFMatrixC<RealT,2,2>::operator*(const TFVectorC<RealT,2> & vec) const {
    TFVectorC<RealT,2> ret;
    ret[0] = data[0][0] * vec[0] + data[0][1] * vec[1];
    ret[1] = data[1][0] * vec[0] + data[1][1] * vec[1];
    return ret;
  }
  
  inline
  void MulAdd(const TFMatrixC<RealT,2,2> & R,const TFVectorC<RealT,2> & x, const TFVectorC<RealT,2> & t, TFVectorC<RealT,2> &result) {
    result[0] = R[0][0]*x[0] + R[0][1]*x[1] + t[0];
    result[1] = R[1][0]*x[0] + R[1][1]*x[1] + t[1];    
  }
  
  inline
  void Mul(const TFMatrixC<RealT,2,2> & R,const TFVectorC<RealT,2> & x, TFVectorC<RealT,2> &result) {
    result[0] = R[0][0]*x[0] + R[0][1]*x[1];
    result[1] = R[1][0]*x[0] + R[1][1]*x[1];
  }

}

#endif
