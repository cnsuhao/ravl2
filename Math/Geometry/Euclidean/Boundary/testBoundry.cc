// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Euclidean/Boundary/testBoundry.cc"
//! userlevel=Develop
//! author="Radek Marik"
//! docentry="Ravl.Math.Geometry.2D.Boundry"

#include "Ravl/Boundary.hh"
#include "Ravl/Stream.hh"

using namespace RavlN;

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

int testBoundry();
int testEdge();

int main() {
  int ln;
  if((ln = testEdge()) != 0) {
    cerr << "Test failed at line " << ln << "\n";
    return 1;
  }
  if((ln = testBoundry()) != 0) {
    cerr << "Test failed at line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

int testEdge() {
  Index2dC start(5,6);
  EdgeC edge(start,CR_DOWN);
  Index2dC at = edge.RPixel();
  ONDEBUG(cerr << "iAt=" << at << " Start=" << start << "\n");
  if(at != (start + Index2dC(0,-1))) return __LINE__;
  if(start != edge.LPixel()) return __LINE__;
  // Go around a pixel clockwise.
  for(int i = 0;i < 5;i++) {
    edge.Begin() = edge.End();
    edge.TurnClock();
    ONDEBUG(cerr << "At=" << edge.RPixel() << " Code:" << edge.Code() << "\n");
    if(at == edge.LPixel()) return __LINE__;
  }
  // Go around a pixel counter clockwise.
  edge = EdgeC(start,CR_DOWN);
  at = edge.LPixel();
  if(at != start) return __LINE__;
  ONDEBUG(cerr << "iAt=" << at << "\n");
  for(int i = 0;i < 5;i++) {
    edge.Begin() = edge.End();
    edge.TurnCClock();
    ONDEBUG(cerr << "At=" << edge.LPixel() << " Code:" << edge.Code() << "\n");
    if(at != edge.LPixel()) return __LINE__;
  }
  //                       DOWN          RIGHT         UP            LEFT           None
  Index2dC offsets[5] = { Index2dC(0,-1),Index2dC(1,0),Index2dC(0,1),Index2dC(-1,0),Index2dC(0,0) };
  for(int i = 0;i < 5;i++) {
    edge = EdgeC(start,i);
    cerr << " " << i << " RPixel=" << edge.RPixel() << "\n";
    if(edge.LPixel() != start) return __LINE__;
    if(edge.RPixel() != (start + offsets[i])) return __LINE__; 
  }
  return 0;
}

int testBoundry() {
  IndexRange2dC rect(IndexRangeC(1,3),IndexRangeC(2,4));
  BoundaryC bnd(rect,true);
  //cout << "Bounds:\n " << bnd << "\n";
  if(bnd.Size() != 12) return __LINE__;
  ONDEBUG(cout << "Area=" << bnd.Area() << "\n");
  if(bnd.Area() != - (IntT) rect.Area()) return __LINE__;
  IndexRange2dC tmpbb = bnd.BoundingBox();
  if(tmpbb == rect) return __LINE__;
  bnd.BReverse();
  if(tmpbb != bnd.BoundingBox()) return __LINE__;
  if(bnd.Area() != - (IntT) rect.Area()) return __LINE__;  
  bnd.Invert();
  ONDEBUG(cout << "RArea=" << bnd.Area() << "\n");
  if(bnd.Area() != (IntT) rect.Area()) return __LINE__;
  
  IndexRange2dC bb = bnd.BoundingBox();
  ONDEBUG(cerr << "Bounding box=" << bb << " Inv=" << tmpbb << "\n");
  if(bb != rect) return __LINE__;
  
  return 0;
}
