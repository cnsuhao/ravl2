// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/Conic2d.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/LineABC2d.hh"
#include "Ravl/LeastSquares.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  //: Get the coefficient matrix. 'C'
  // Such that  x.T() * C * x = 0
  
  Matrix3dC Conic2dC::C() const { 
    return Matrix3dC(p[0]  ,p[1]/2,p[3]/2,
		     p[1]/2,p[2]  ,p[4]/2,
		     p[3]/2,p[4]/2,p[5]); 
  }
  
  //: Find the tangent at point 'pnt', where pnt is on the conic.
  
  LineABC2dC Conic2dC::Tangent(const Point2dC &pnt) {
    // FIXME:- This can be simplified alot.
    Vector3dC x(pnt[0],pnt[1],1);
    Vector3dC res= C() * x;
    return LineABC2dC(res[0],res[1],res[2]);
  }
  
  //: Fit a conic to a set of points.
  
  Conic2dC FitConic(const SArray1dC<Point2dC> &points) {
    UIntT samples = points.Size();
    if(samples < 5) {
      cerr << "ERROR: Need 5 points or more to fit Conic2dC.\n";
      return Conic2dC();
    }
    if(samples == 5)
      samples++;
    MatrixC A(samples,6);
    IntT i = 0;
    VectorC c(6);
    c.Fill(1);
    for(SArray1dIterC<Point2dC> it(points);it;it++,i++) {
      Point2dC &p = *it;
      A[i][0] = Sqr(p[0]);
      A[i][1] = p[0] * p[1];
      A[i][2] = Sqr(p[1]);
      A[i][3] = p[0];
      A[i][4] = p[1];
      A[i][5] = 1;
    }
    // Duplicate row to avoid problem current SVD.
    if(samples != points.Size()) {
      i = points.Size();
      const Point2dC &p = points[0];
      A[i][0] = Sqr(p[0]);
      A[i][1] = p[0] * p[1];
      A[i][2] = Sqr(p[1]);
      A[i][3] = p[0];
      A[i][4] = p[1];
      A[i][5] = 1;
    }
    VectorC result = LeastSquaresFixedRank(A,c,5);
    result[5]--;
    //cerr << "Result=" << result << "\n";
    return Conic2dC(result);
  }
  
  //: Write ellipse to text stream.
  ostream &operator<<(ostream &s,const Conic2dC &obj) {
    s << obj.Parameters();
    return s;
  }
  
  //: Read ellipse from text stream.
  istream &operator>>(istream &s,Conic2dC &obj) {
    TFVectorC<RealT,6> p;
    s >> p;
    obj = Conic2dC(p);
    return s;
  }

  
  //: Write ellipse to binary stream.
  BinOStreamC &operator<<(BinOStreamC &s,const Conic2dC &obj) {
    s << obj.Parameters();
    return s;
  }

  
  //: Read ellipse from binary stream.
  BinIStreamC &operator>>(BinIStreamC &s,Conic2dC &obj) {
    TFVectorC<RealT,6> p;
    s >> p;
    obj = Conic2dC(p);
    return s;
  }


}
