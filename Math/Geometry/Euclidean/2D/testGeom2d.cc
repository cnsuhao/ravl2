// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Euclidean/2D/testGeom2d.cc"
//! docentry="Ravl.Math.Geometry.2D"
//! author="Charles Galambos"
//! userlevel=Develop

#include "Ravl/Moments2d2.hh"
#include "Ravl/Stream.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/Matrix2d.hh"
#include "Ravl/Polygon2d.hh"
#include "Ravl/Circle2d.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/Affine2d.hh"
#include "Ravl/Random.hh"
#include "Ravl/DelaunayTriangulation2d.hh"
#include "Ravl/HEMesh2d.hh"
#include "Ravl/TriMesh2d.hh"
#include "Ravl/Projection2d.hh"
#include "Ravl/Conic2d.hh"
#include "Ravl/Ellipse2d.hh"
#include "Ravl/Angle.hh"

using namespace RavlN;

int testMoments();
int testBinIO();
int testCircle2d();
int testConvexHull2d();
int testDelaunayTriangulation2d();
int testFitAffine();
int testHEMesh2d();
int testProjective2d();
int testConic2d();
int testEllipse2dA();
int testEllipse2dB();
int testEllipse2dC();

int main() {
  int ln;
#if 1
  if((ln = testMoments()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testBinIO()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testCircle2d()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testHEMesh2d()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testConvexHull2d()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testDelaunayTriangulation2d()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testFitAffine()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testProjective2d()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testConic2d()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
#endif
  if((ln = testEllipse2dA()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testEllipse2dB()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testEllipse2dC()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  cout << "Test passed. \n";
  return 0;
}


int testMoments() {
  cerr << "Testing moments. \n";
  Moments2d2C mom;
  mom.AddPixel(Index2dC(9,19));
  mom.AddPixel(Index2dC(10,20));
  mom.AddPixel(Index2dC(11,22));
  RealT cx = mom.CentroidX();
  RealT cy = mom.CentroidY();
  //cerr << "Centroid=" << cx << " " << cy <<"\n";
  if((Abs(cx - 10) > 0.001) || (Abs(cy - 20.3333) > 0.001))
     return __LINE__;
  Vector2dC principleAxis = mom.PrincipalAxisSize();
  cerr << "PrincipleAxis=" << principleAxis  <<"\n"; 
  RealT elong = mom.Elongatedness(principleAxis);
  cerr <<"Elong=" << elong << "\n";
  if(Abs(elong - 0.984886) > 0.001) return __LINE__;
  return 0;
}

int testBinIO() {
  cerr << "Testing binary IO. \n";
  StrOStreamC ostr;
  Point2dC p1(0.12,0.34);
  Point2dC p2(4.5,6.7);
  Point2dC p3(8.9,10.11);
  {
    BinOStreamC bos(ostr);
    bos << p1 << p2 << p3;
  }
  Point2dC ip1,ip2,ip3;
  {
    StrIStreamC istr(ostr.String());
    BinIStreamC bis(istr);
    bis >> ip1 >> ip2 >> ip3;
  }
  if((p1 - ip1).SumOfSqr() > 0.000000001)
    return __LINE__;
  if((p2 - ip2).SumOfSqr() > 0.000000001)
    return __LINE__;
  if((p3 - ip3).SumOfSqr() > 0.000000001)
    return __LINE__;
  return 0;
}

int testCircle2d() {
  Array1dC<Point2dC> pnts(5);
  pnts[0] = Point2dC(1,0);
  pnts[1] = Point2dC(-1,2);
  pnts[2] = Point2dC(3,2);
  pnts[3] = Point2dC(1,4);
  pnts[4] = Point2dC(1,4.01); // Just to add a slight error.
  
  Circle2dC circle;
  
  RealT residual;
  if(!circle.FitLSQ(pnts,residual))
    return __LINE__;
  //cerr << "Residual=" << residual << "\n";
  //cerr << "Center=" << circle.Centre() << " Radius=" << circle.Radius() << "\n";
  if(Point2dC(circle.Centre() - Point2dC(1,2)).SumOfSqr() > 0.01)
    return __LINE__;
  if(Abs(circle.Radius() - 2) > 0.01) 
    return __LINE__;

  Circle2dC circle2;
  if(!circle2.Fit(pnts[0],pnts[1],pnts[2]))
    return __LINE__;
  //cerr << "Center=" << circle2.Centre() << " Radius=" << circle2.Radius() << "\n";
  if(Point2dC(circle2.Centre() - Point2dC(1,2)).SumOfSqr() > 0.01)
    return __LINE__;
  if(Abs(circle2.Radius() - 2) > 0.01) 
    return __LINE__;
  
  return 0;
}

int testConvexHull2d() {
  cerr << "testConvexHull2d() Called. \n";
  for(int j = 0;j < 10;j++) {
    DListC<Point2dC> pnts;
    
    // Generate a point set.
    for(int i = 0;i < (10 + j * 10);i++)
      pnts.InsLast(Point2dC(Random1() * 100,Random1() * 100));
    
    DListC<Point2dC> tmp = pnts.Copy();
    Polygon2dC poly = ConvexHull(tmp);
    //cout << "Hull=" << poly << "\n";
    
    for(DLIterC<Point2dC> it(pnts);it;it++) {
      if(!poly.Contains(*it)) {
	cerr << *it << " not in polygon. \n";
	return __LINE__;
      }
    }
  }
  
  return 0;
}

int testDelaunayTriangulation2d() {
  cerr << "testDelaunayTriangulation2d() Called. \n";
  
  // Try a mesh with a exactly aligned points.
  
  SArray1dC<Point2dC> pnts(5);
  pnts[0] = Point2dC(10,10);
  pnts[1] = Point2dC(10,90);
  pnts[2] = Point2dC(10,50);
  pnts[3] = Point2dC(90,50);
  pnts[4] = Point2dC(50,50);
  
  HEMesh2dC mesh = DelaunayTriangulation(pnts);
  if(!mesh.CheckMesh(true)) return __LINE__;
  
  for(int j = 0;j < 10;j++) {
    SArray1dC<Point2dC> pnts(10 + j * 10);
    
    // Generate a point set.
    for(UIntT i = 0;i < pnts.Size();i++)
      pnts[i] = Point2dC(Random1() * 100,Random1() * 100);
    
    HEMesh2dC mesh = DelaunayTriangulation(pnts);
    
    if(!mesh.CheckMesh(true)) return __LINE__;
    
    if(!IsDelaunayTriangulation(mesh)) return __LINE__;
    
    // Convert it into a tri mesh.
    
    TriMesh2dC triMesh = mesh.TriMesh();
    
    // Check faces are all oriented correctly.
    
    if(!triMesh.IsFlat()) return __LINE__;
    
  }
  
  return 0;
}

int testFitAffine() {
  cerr << "testFitAffine(), Called. \n";

  // Try a simple case.
  
  SArray1dC<Point2dC> ipnt(3);
  ipnt[0] = Point2dC(1,1);
  ipnt[1] = Point2dC(2,1);
  ipnt[2] = Point2dC(1,3);
  
  SArray1dC<Point2dC> opnt(3);
  opnt[0] = Point2dC(2,2);
  opnt[1] = Point2dC(3,2);
  opnt[2] = Point2dC(2,3);
  
  Affine2dC aff = FitAffine(ipnt,opnt);
  int i;
  for(i=0;i < 3;i++)
    if(((aff * ipnt[i]) - opnt[i]).SumOfSqr() > 0.001)
      return __LINE__;

  // Check polygon transform.
  
  Polygon2dC poly;
  
  for(i = 0;i < 3;i++)
    poly.InsLast(ipnt[i]);
  Polygon2dC tpoly = aff * poly;
  i = 0;
  for(DLIterC<Point2dC> it(tpoly);it;it++,i++)
    if((*it - opnt[i]).SumOfAbs() > 0.001) return __LINE__;
  
  // Try some random cases.
  
  for(int j = 0;j < 100;j++) {
    for(i = 0;i < 3;i++) {
      ipnt[i] = Point2dC(Random1() * 100,Random1() * 100);
      opnt[i] = Point2dC(Random1() * 100,Random1() * 100);
    }
    Affine2dC aff = FitAffine(ipnt,opnt);
    int i;
    for(i=0;i < 3;i++) {
      if(((aff * ipnt[i]) - opnt[i]).SumOfSqr() > 0.001) {
	cerr << "Fit failed " << j << " ipnt=" << ipnt[i] << " opnt=" << opnt[i] << "\n";
	return __LINE__;
      }
    }
  }

  
  return 0;
}

int testHEMesh2d() {
  HEMesh2dC mesh(true);
  SArray1dC<HEMeshBaseVertexC > points(3);
  
  points[0] = mesh.InsertVertex(Point2dC(0,0));
  points[1] = mesh.InsertVertex(Point2dC(0,1));
  points[2] = mesh.InsertVertex(Point2dC(1,0));
  
  
  HashC<Tuple2C<HEMeshBaseVertexC,HEMeshBaseVertexC> , HEMeshBaseEdgeC> edgeTab;
  mesh.InsertFace(points,edgeTab);
  
  ;  
  THEMeshFaceC<Point2dC> face = mesh.FindFace(Point2dC(0.1,0.1));
  if(!face.IsValid()) return __LINE__;
  
  face = mesh.FindFace(Point2dC(-1,-1));
  if(face.IsValid()) return __LINE__;
  
  face = mesh.FindFace(Point2dC(-1,0.5));
  if(face.IsValid()) return __LINE__;
  
  face = mesh.FindFace(Point2dC(0.5,-1));
  if(face.IsValid()) return __LINE__;
  
  face = mesh.FindFace(Point2dC(1,1));
  if(face.IsValid()) return __LINE__;
  
  if(!IsDelaunayTriangulation(mesh)) return __LINE__;
  
  return 0;
}

int testProjective2d() {
  IntT i;
  Projection2dC proj; // Create a unit projection.
  
  SArray1dC<Point2dC> ipnt(3);
  ipnt[0] = Point2dC(1,1);
  ipnt[1] = Point2dC(2,1);
  ipnt[2] = Point2dC(1,3);
  
  SArray1dC<Point2dC> opnt = ipnt;
  
  // Check polygon transform.
  Polygon2dC poly;
  
  for(i = 0;i < 3;i++)
    poly.InsLast(ipnt[i]);
  Polygon2dC tpoly = proj * poly;
  i = 0;
  for(DLIterC<Point2dC> it(tpoly);it;it++,i++)
    if((*it - opnt[i]).SumOfAbs() > 0.001) return __LINE__;
  
  return 0;
}

int testConic2d() {
  SArray1dC<Point2dC> pnts(5);
  pnts[0] = Point2dC(1, 0);
  pnts[1] = Point2dC(2,-1);
  pnts[2] = Point2dC(3, 0);
  pnts[3] = Point2dC(3, 1);
  pnts[4] = Point2dC(2, 4);
  Conic2dC conic = FitConic(pnts);
  for(UIntT i = 0;i < pnts.Size();i++) {
    //cerr << i << " Residue=" << conic.Residue(pnts[i]) << "\n";
    if(!conic.IsOnCurve(pnts[i]))
      return __LINE__;
  }
  return 0;
}

int testEllipse2dA() {
  SArray1dC<Point2dC> pnts(5);
  pnts[0] = Point2dC(1, 0);
  pnts[1] = Point2dC(2,-1);
  pnts[2] = Point2dC(3, 0);
  pnts[3] = Point2dC(3, 1);
  pnts[4] = Point2dC(2, 4);
  
  Conic2dC conic;
  if(!FitEllipse(pnts,conic)) {
    cerr << "Failed to fit ellipse.\n";
    return __LINE__;
  }
  
  Ellipse2dC ellipse;
  if(!conic.AsEllipse(ellipse)) {
    cerr << "Not an ellipse!\n";
    return __LINE__;
  }
  
  for(UIntT i = 0;i <pnts.Size();i++) {
    //cerr << i << " Residue=" << conic.Residue(pnts[i]) << "\n";
    if(!conic.IsOnCurve(pnts[i])) {
      cerr << "Conic fit failed on point " << i << " \n";
      return __LINE__;
    }
    if(!ellipse.IsOnCurve(pnts[i])) {
      cerr << "Ellipse fit failed on point " << i << " \n";
      return __LINE__;
    }
  }  
  return 0;
}

int testEllipse2dB() {
  for(RealT tangle = 0;tangle < RavlConstN::pi;tangle += RavlConstN::pi/10) {
    Point2dC gtc(50,50);
    Ellipse2dC ellipse(gtc,40,20,tangle);
    //  cerr << "Ellipse1=" << ellipse << "\n";
    RealT step = RavlConstN::pi/5;
    SArray1dC<Point2dC> points(10);
    IntT i = 0;
    for(RealT a = 0;i < 10;a += step,i++) {
      points[i] = ellipse.Point(a);
    }
    Conic2dC conic;
    if(!FitEllipse(points,conic)) 
      return __LINE__;
    //cerr << "Conic=" << conic.C() << "\n";
    Point2dC centre;
    RealT min,maj,ang;
    conic.EllipseParameters(centre,maj,min,ang);
    //cerr << "C Paramiters=" << centre << " " << maj << " " << min << " " << ang << "   Diff=" << AngleC(ang,RavlConstN::pi).Diff(AngleC(tangle,RavlConstN::pi)) << "\n";
    if((centre - gtc).SumOfAbs() > 0.00000001) return __LINE__;
    if(Abs(maj - 40) > 0.000000001) return __LINE__;
    if(Abs(min - 20) > 0.000000001) return __LINE__;
    if(Abs(AngleC(ang,RavlConstN::pi).Diff(AngleC(tangle,RavlConstN::pi))) > 0.000001) return __LINE__;
    Ellipse2dC ellipse2;
    if(!FitEllipse(points,ellipse2)) {
      cerr << "Failed to fit ellipse. \n";
      return __LINE__;
    }
    
    ellipse2.EllipseParameters(centre,maj,min,ang);
    //cerr << "E Paramiters=" << centre << " " << maj << " " << min << " " << ang << "  Diff=" << AngleC(ang,RavlConstN::pi).Diff(AngleC(tangle,RavlConstN::pi)) << "\n";
    if((centre - gtc).SumOfAbs() > 0.00000001) return __LINE__;
    if(Abs(maj - 40) > 0.000000001) return __LINE__;
    if(Abs(min - 20) > 0.000000001) return __LINE__;
    if(Abs(AngleC(ang,RavlConstN::pi).Diff(AngleC(tangle,RavlConstN::pi))) > 0.000001) return __LINE__;
  }
  //cerr << "Ellipse2=" << ellipse2 << "\n";
  return 0;
}

int testEllipse2dC() {
  Matrix2dC covar(4,0,
		  0,1);
  Vector2dC mean(50,50);
  
  Ellipse2dC ellipse = EllipseMeanCovariance(covar,mean,1.0);
  Point2dC centre;
  RealT min,maj,ang;
  ellipse.EllipseParameters(centre,maj,min,ang);
  //cerr << "Paramiters=" << centre << " " << maj << " " << min << " " << ang << " \n";
  if(Abs(maj - 2) > 0.0000001)
    return __LINE__;
  if(Abs(min - 1) > 0.0000001)
    return __LINE__;
  if(Abs(AngleC(ang,RavlConstN::pi).Diff(AngleC(0,RavlConstN::pi))) > 0.000001) return __LINE__;
  return 0;
}
