// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Euclidean/2D/testGeom2d.cc"

#include "Ravl/Moments2d2.hh"
#include "Ravl/Stream.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/Matrix2d.hh"
#include "Ravl/Circle2d.hh"

using namespace RavlN;

int testMoments();
int testBinIO();
int testCircle2d();

int main() {
  int ln;
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
  Vector2dC principleAxis = mom.PrincipalAxis();
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
  SArray1dC<Point2dC> pnts(5);
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
  return 0;
}
