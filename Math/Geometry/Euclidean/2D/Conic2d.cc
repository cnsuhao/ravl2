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
#include "Ravl/VectorMatrix.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/Matrix3d.hh"
#include "Ravl/LineABC2d.hh"
#include "Ravl/LeastSquares.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Ellipse2d.hh"
#include "Ravl/Eigen.hh"

#define DODEBUG  0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Get the coefficient matrix. 'C'
  // Such that  x.T() * C * x = 0
  
  Matrix3dC Conic2dC::C() const { 
    return Matrix3dC(p[0]  ,p[1]/2,p[3]/2,
		     p[1]/2,p[2]  ,p[4]/2,
		     p[3]/2,p[4]/2,p[5]); 
  }

  //: Construct from matrix.
  //!param: matrix - 3 x 3 symetric matrix.
  
  Conic2dC::Conic2dC(Matrix3dC &matrix) {
    // Should check matrix is symetric ?
    p[0] = matrix[0][0];
    p[1] = matrix[0][1] + matrix[1][0];
    p[2] = matrix[1][1];
    p[3] = matrix[0][2] + matrix[2][0];
    p[4] = matrix[1][2] + matrix[2][1];
    p[5] = matrix[2][2];
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
    ONDEBUG(cerr << "FitConic(), Points=" << points.Size() << "\n");
    if(samples < 5) {
      cerr << "ERROR: Need 5 points or more to fit Conic2dC.\n";
      return Conic2dC();
    }
    // ---------- Compute normalisation for points ----------------------
#if 1
    // Compute mean.
    Point2dC mean(0,0);
    for(SArray1dIterC<Point2dC> it(points);it;it++)
      mean += *it;
    mean /= samples;
    RealT scale = 0;
    // Normalise magnitude
    for(SArray1dIterC<Point2dC> it(points);it;it++)
      scale += Sqrt((*it - mean).SumOfSqr());
    scale /= samples;
#else
    Point2dC mean(0,0);
    RealT scale = 2;
#endif
    // ---------- Compute paramiters ----------------------
    if(samples == 5)
      samples++;
    MatrixC A(samples,6);
    IntT i = 0;
    VectorC c(samples);
    c.Fill(1);
    for(SArray1dIterC<Point2dC> it(points);it;it++,i++) {
      Point2dC p = (*it - mean) / scale; // Normalise point.
      A[i][0] = Sqr(p[0]);
      A[i][1] = p[0] * p[1];
      A[i][2] = Sqr(p[1]);
      A[i][3] = p[0];
      A[i][4] = p[1];
      A[i][5] = 1;
    }
    // Duplicate row to avoid problem with current SVD.
    if(samples != points.Size()) {
      i = points.Size();
      Point2dC p = (points[0] - mean) / scale;  // Normalise point.
      A[i][0] = Sqr(p[0]);
      A[i][1] = p[0] * p[1];
      A[i][2] = Sqr(p[1]);
      A[i][3] = p[0];
      A[i][4] = p[1];
      A[i][5] = 1;
    }
    //cerr << "A=" << A.Rows() << " " << A.Cols() << " Vec=" << c.Size() << "\n";
    VectorC result = LeastSquaresFixedRank(A,c,5);
    result[5]--;
    
    //cerr << "Result1=" << result << "\n Cr=" << Cr<< "\n";
    // --------- Undo normalisation ----------------
    // FIXME:- Make this more efficient by expanding out manually.
#if RAVL_COMPILER_VISUALCPP
    Conic2dC Cr(static_cast<const FVectorC<6> &>(result));
#else
    Conic2dC Cr(static_cast<const TFVectorC<RealT,6> &>(result));
#endif
    Matrix3dC Hi(1/scale,0,-1 * mean[0]/scale,
		 0,1/scale,-1 * mean[1]/scale,
		 0,0,1);
    Matrix3dC nC = Hi.TMul(Cr.C()) * Hi;
    return Conic2dC(nC);
  }
  
  //: Compute ellipse parameters.
  
  bool Conic2dC::ComputeEllipse(Point2dC &c,Matrix2dC &mat) const {
    TFVectorC<RealT,6> u = p;    
    RealT idet = 1 / (u[0] * u[2] - Sqr(u[1]) * 0.25);
    if(idet <= 0) {
      //cerr << "Not an ellipse.\n";
      return false;
    }
    ONDEBUG(cerr << "idet=" << idet << "\n");
    
    u *= Sqrt(idet * 0.25);
    
    c = Point2dC((-u[3] * u[2] + u[4] * u[1] * 0.5) * 2,
		 (-u[0] * u[4] + u[3] * u[1] * 0.5) * 2);
    
    RealT scale = 1/(u[0] * Sqr(c[0]) + 
 		     u[1] * c[0] * c[1] + 
		     u[2] * Sqr(c[1]) + 
		     u[3] * c[0] + 
		     u[4] * c[1] +
		     u[5]);
    
    RealT t = u[1] * scale * 0.5;
    mat = Matrix2dC(u[0] * scale,t,
		    t,u[2] * scale);
    
    ONDEBUG(cerr << "Scale=" << scale << "\n");
    ONDEBUG(cerr << "mat=" << mat << "\n");
    ONDEBUG(cerr << "c=" << c << "\n");
    return true;
  }
  
  //: Represent conic as an ellipse.
  //!param: ellipse - Ellipse into which representation is written.
  //!return: true if conversion is possible.
  // Returns false if conic is a hyperbola or is
  // otherwise degenerate.
  
  bool Conic2dC::AsEllipse(Ellipse2dC &ellipse) const {
    Matrix2dC t;
    Point2dC c;
    if(!ComputeEllipse(c,t))
      return false;
    Matrix2dC su,sv;
    Vector2dC dv = SVD(t,su,sv);
    Matrix2dC d(-1/Sqrt(dv[0]),0,
		0,-1/Sqrt(dv[1]));
    // FIXME:- Multiply out by hand to make it faster.
    Matrix2dC sr = (su * d).MulT(sv);
    ellipse = Ellipse2dC(sr,c);
    return true;
  }
  
  //: Compute various ellipse parameters.
  //!param: centre - Centre of ellipse.
  //!param: major - Size of major axis.
  //!param: minor - Size of minor axis
  //!param: angle - Angle of major axis.
  
  bool Conic2dC::EllipseParameters(Point2dC &centre,RealT &major,RealT &minor,RealT &angle) const {
    Matrix2dC t;
    if(!ComputeEllipse(centre,t))
      return false;
    angle = -atan2(2*t[0][1],t[0][0]-t[1][1])/2;
    RealT cosa=Cos(angle);
    RealT sina=Sin(angle);
    RealT w = 2*t[0][1]*cosa*sina;
    major =Sqrt(1.0/(-t[0][0]*cosa*cosa+w-t[1][1]*sina*sina));
    minor =Sqrt(1.0/(-t[0][0]*sina*sina-w-t[1][1]*cosa*cosa));
    ONDEBUG(cerr << "Center=" << c << " Major=" << major << " Minor=" << minor << " Angle=" << angle << "\n");
    return true;
    
  }
  
  
  //: Fit a conic to a set of points.
  
  Conic2dC FitConic(const Array1dC<Point2dC> &points)
  { return FitConic(const_cast<Array1dC<Point2dC> &>(points).SArray1d(true)); } 


  //: Fit ellipse to points.
  
  bool FitEllipse(const SArray1dC<Point2dC> &points,Conic2dC &conic) {
    if(points.Size() < 5)
      return false;
    Point2dC mean(0,0);
#if 1
    // Find the mean point.
    for(SArray1dIterC<Point2dC> it(points);it;it++)
      mean += *it;
    mean /= (RealT)points.Size();
    // Normalise magnitude.  How critical this is isn't clear but
    // it does improve things a bit.
    RealT scale = 0;
    for(SArray1dIterC<Point2dC> it(points);it;it++)
      scale += Sqrt((*it - mean).SumOfSqr());
    scale /= (RealT)points.Size();
#else
    RealT scale = 1;
#endif
    
    // Fill in 'D'
    MatrixC D1(points.Size(),3);
    for(BufferAccessIter2C<Point2dC,BufferAccessC<RealT> > it(points,D1);it;it++) {
      Point2dC l = (it.Data1() - mean)/scale;
      it.Data2()[0] = Sqr(l[0]);
      it.Data2()[1] = l[0] * l[1];
      it.Data2()[2] = Sqr(l[1]);
    }
    MatrixC D2(points.Size(),3);
    for(BufferAccessIter2C<Point2dC,BufferAccessC<RealT> > it(points,D2);it;it++) {
      Point2dC l = (it.Data1() - mean)/scale;
      it.Data2()[0] = l[0];
      it.Data2()[1] = l[1];
      it.Data2()[2] = 1;
    }
    
    MatrixC S1 = D1.TMul(D1);
    MatrixC S2 = D1.TMul(D2);
    MatrixC S3 = D2.TMul(D2);
    S3.InverseIP();
    MatrixC T = S3.MulT(S2) * -1;
    MatrixC M = S1 + S2 * T;
    M = MatrixC(M[2][0]/2,M[2][1]/2,M[2][2]/2,
		-M[1][0],-M[1][1],-M[1][2],
		M[0][0]/2,M[0][1]/2,M[0][2]/2);
    
    ONDEBUG(cerr << "M=" << M << "\n");
    EigenValueC<RealT> evs(M);
    MatrixC eD;
    evs.getD(eD);
    ONDEBUG(cerr << "D=" << eD << "\n");
    MatrixC ev = evs.EigenVectors();
    ONDEBUG(cerr << "ev=" << ev << "\n");
    VectorC cond = 
      VectorC(ev.SliceRow(0)) * VectorC(ev.SliceRow(2)) * 4 
      - VectorC(ev.SliceRow(1)) * VectorC(ev.SliceRow(1));
    
    //cerr << "Cond=" << cond << "\n";
    VectorC a1 = ev.SliceColumn(cond.IndexOfMax());
    VectorC a = a1.Append(T * a1);

    // Undo normalisation.
#if 1
#if RAVL_COMPILER_VISUALCPP
    Conic2dC Cr(static_cast<const FVectorC<6> &>(a));
#else
    Conic2dC Cr(static_cast<const TFVectorC<RealT,6> &>(a));
#endif
    Matrix3dC Hi(1/scale,0,-1 * mean[0]/scale,
		 0,1/scale,-1 * mean[1]/scale,
		 0,0,1);
    //Hi = Hi.Inverse();
    Matrix3dC nC = Hi.TMul(Cr.C()) * Hi;
    conic = Conic2dC(nC);
#else
    conic = Conic2dC(a);
#endif
    
    return true;
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
