// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Euclidean/2D/Affine2d.cc"

#include "Ravl/Affine2d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/LeastSquares.hh"
#include "Ravl/Matrix.hh"

namespace RavlN {
  
  //: Fit an affine transform given to the mapping between original and newPos.
  
  // FIXME :- This can be done more efficiently.
  
  Affine2dC FitAffine(SArray1dC<Point2dC> org,SArray1dC<Point2dC> newPos) {
    RavlAssert(org.Size() == newPos.Size());
    
    UIntT samples = org.Size();
    if ( samples < 3 )
      throw ExceptionC("Sample size too small in FitAffine2dPointsBodyC::FitModel(). ");
    
    MatrixC A(samples,3);
    VectorC b(samples);
    VectorC c(samples);
    UIntT i = 0;
    for(SArray1dIter2C<Point2dC,Point2dC> it(org,newPos);it;it++,i++) {
      RealT x1, y1, x2, y2;
      x1=it.Data1()[0]; y1=it.Data1()[1];
      x2=it.Data2()[0]; y2=it.Data2()[1];
      
      A[i][0] = x1; 
      A[i][1] = y1; 
      A[i][2] = 1;
      b[i] = x2;
      c[i] = y2;
    }
    MatrixC tA = A.Copy();
    if(A.Rows() == A.Cols()) {
      // solve for solution vector
      if(!SolveIP(tA,b))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine() ");
      if(!SolveIP(A,c))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine() ");
    } else {
      RealT residual;
      if(!LeastSquaresQR_IP(tA,b,residual))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine() ");
      if(!LeastSquaresQR_IP(A,c,residual))
	throw ExceptionNumericalC("Dependent linear equations in FitAffine() ");
    }
    
    Matrix2dC sr(b[0],b[1],
		 c[0],c[1]);
    Vector2dC tr(b[2],c[2]);
    return Affine2dC(sr,tr);
  }
  
  void Affine2dC::Rotate(RealT A) {
    RealT TC = Cos(A),TS = Sin(A);    
    Matrix2dC result;
#if !RAVL_COMPILER_VISUALCPP
    MulM(SR,Matrix2dC(TC,-TS,TS,TC),result);
#else
    MulM<RealT,2,2,2>(SR,Matrix2dC(TC,-TS,TS,TC),result);
#endif
    SR = result;
  }
  
}
