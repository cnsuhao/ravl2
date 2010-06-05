// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: testLineDet.cc 3073 2003-06-13 07:18:32Z craftit $"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Lines/testLineDet.cc"

#include "Ravl/Image/PPHT.hh"

using namespace RavlImageN;

int testLineSegment();

int main(int nargs,char **argv) {
  int ln;
  if((ln = testLineSegment()) != 0) {
    cerr << "test failed on line " << ln << "\n";
    return 1;
  }
  
  return 0;
}

int testLineSegment() {
  SArray1dC<Point2dC> points(20);
  for(int i = 0;i < (int) points.Size();i++) {
    points[i] = Point2dC((RealT) 100 - i,(RealT) 10.0 + i *0.5);
  }
  Curve2dLineSegmentC aline(points); // Fit line to remaining points.

  cerr << "Normal=" << aline.Normal() << "\n";
  cerr << "Start=" << aline.StartPnt() << " End=" << aline.EndPnt() << "\n";
  cerr << "Real =" << points[0] << " End=" << points[points.Size()-1] << "\n";
  
  if(aline.StartPnt().SqrEuclidDistance(points[0]) > 0.0001)   return __LINE__;
  if(aline.EndPnt().SqrEuclidDistance(points[points.Size()-1]) > 0.0001)   return __LINE__;
  return 0;
}
