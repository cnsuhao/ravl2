// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/Ellipse2d.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/Matrix.hh"
#include "Ravl/Vector.hh"
#include "Ravl/Conic2d.hh"
#include "Ravl/SVD.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Create from conic parameters.
  //!param: conicParams - Conic paramiters a to f, where a * Sqr(row) + b * row * col + c * Sqr(col) + d * row + e * col + f = 0
  
  Ellipse2dC::Ellipse2dC(const TFVectorC<RealT,6> &conicParams) {
    Conic2dC conic(conicParams);
    conic.AsEllipse(*this); // What to do if this fails?
  }
  
  //: Create an new ellipse
  //!param: centre - Centre of ellipse.
  //!param: major - Size of major axis. (at given angle)
  //!param: minor - Size of minor axis.
  //!param: angle - Angle of major axis.
  
  Ellipse2dC::Ellipse2dC(const Point2dC &centre,RealT major,RealT minor,RealT angle) {
    p = FAffineC<2>(Matrix2dC(Cos(angle),Sin(angle),
			      -Sin(angle),Cos(angle)) * 
		    Matrix2dC(major,0,
			      0,minor),
		    centre);
  }
  
  //: Fit ellipse to points.
  
  bool FitEllipse(const SArray1dC<Point2dC> &points,Ellipse2dC &ellipse) {
    Conic2dC conic;
    if(!FitEllipse(points,conic))
      return false;
    return conic.AsEllipse(ellipse);
  }

  //: Is point on the curve ?
  
  bool Ellipse2dC::IsOnCurve(const Point2dC &pnt) const {
    Point2dC mp = p.Inverse() * pnt;
    RealT d = mp.SumOfSqr() - 1;
    //cerr << "d=" << d << "\n";
    return IsSmall(d);
  }

  //: Compute various ellipse parameters.
  //!param: centre - Centre of ellipse.
  //!param: major - Size of major axis.
  //!param: minor - Size of minor axis
  //!param: angle - Angle of major axis.
  
  bool Ellipse2dC::EllipseParameters(Point2dC &centre,RealT &major,RealT &minor,RealT &angle) const {
    centre = p.Translation();
    FMatrixC<2,2> U,V;
    FVectorC<2> S = SVD(p.SRMatrix(), U, V);
    U = U * V.T();
    angle = atan(U[0][1]/U[0][0]);
    major = S[0];
    minor = S[1];

    ONDEBUG(cerr << "Center=" << centre << " Major=" << major << " Minor=" << minor << " Angle=" << angle << "\n");
    return true;
  }
  
  //: Compute the size of major and minor axis.
  //!param: major - Size of major axis.
  //!param: minor - Size of minor axis
  
  bool Ellipse2dC::Size(RealT &major,RealT &minor) const {
    FVectorC<2> vec = SVD(p.SRMatrix());
    major = vec[0];
    minor = vec[1];
    return true;
  }
  

  //: Compute an ellipse from a covariance matrix, mean, and standard deviation.
  
  Ellipse2dC EllipseMeanCovariance(const Matrix2dC &covar,const Point2dC &mean,RealT stdDev) {
    Matrix2dC su,sv;
    Vector2dC dv = SVD(covar,su,sv);
    Matrix2dC d(stdDev*Sqrt(dv[0]),0,
		0,stdDev*Sqrt(dv[1]));
    // FIXME:- Multiply out by hand to make it faster.
    Matrix2dC sr = (su * d).MulT(sv);
    return Ellipse2dC(sr,mean);
  }


  
  //: Write ellipse to text stream.
  
  ostream &operator<<(ostream &s,const Ellipse2dC &obj) {
    s << obj.Projection();
    return s;
  }
  
  //: Read ellipse from text stream.
  
  istream &operator>>(istream &s,Ellipse2dC &obj) {
    Affine2dC aff;
    s >> aff;
    obj = Ellipse2dC(aff);
    return s;
  }
  
  //: Write ellipse to binary stream.
  
  BinOStreamC &operator<<(BinOStreamC &s,const Ellipse2dC &obj) {
    s << obj.Projection();
    return s;
  }
  
  //: Read ellipse from binary stream.
  
  BinIStreamC &operator>>(BinIStreamC &s,Ellipse2dC &obj) {
    Affine2dC aff;
    s >> aff;
    obj = Ellipse2dC(aff);
    return s;
  }

}
