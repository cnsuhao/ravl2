// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/testRavlBase.cc"

#include "Ravl/RefCounter.hh"
#include "Ravl/RCWrap.hh"
#include "Ravl/IndexRange1d.hh"
#include "Ravl/IntC.hh"
#include "Ravl/SubIndexRange2dIter.hh"
#include "Ravl/SubIndexRange3dIter.hh"
#include "Ravl/Stream.hh"

using namespace RavlN;

class TestBodyC
  : public RCBodyVC
{
public:
  TestBodyC()
  {}
};

int testTypes();
int testIndex();
int testMisc();
int testSubIndexRange2dIter();
int testSubIndexRange3dIter();

int main()
{
  int ln;
  if((ln = testTypes()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testIndex()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testMisc()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testSubIndexRange2dIter()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testSubIndexRange3dIter()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}

int testTypes()
{
  if(sizeof(Int16T) != 2) return __LINE__;
  if(sizeof(UInt16T) != 2) return __LINE__;
  if(sizeof(Int64T) != 8) return __LINE__;
  if(sizeof(UInt64T) != 8) return __LINE__;
#if RAVL_USE_LARGEFILESUPPORT
  if(sizeof(StreamSizeT) < 8) return __LINE__;
  if(sizeof(StreamOffsetT) < 8) return __LINE__;
#else
  if(sizeof(StreamSizeT) < 4) return __LINE__;
  if(sizeof(StreamOffsetT) < 4) return __LINE__;
#endif
  return 0;
}

int testIndex()
{
  IndexRangeC r1(0,3);
  IndexRangeC r2(1,2);
  IndexRangeC r3(r1);
  r3.ClipBy(r2);
  if(!r1.Contains(r3)) {
    cerr << "IndexRange test 1 failed " << r1 << " does not contain " << r3 << "\n";
    return __LINE__;
  }
  if(!r2.Contains(r3)) {
    cerr << "IndexRange test 2 failed. " << r2 << " does not contain " << r3 << "\n";
    return __LINE__;
  }
  
  IndexRangeC xr1(r1);
  IndexRangeC xr2(4,5);
  xr1.ClipBy(xr2);
  if(xr1.Size() != 0) return __LINE__;
  xr1 = r1;
  xr2 = IndexRangeC (-10,-2);
  xr1.ClipBy(xr2);
  if(xr1.Size() != 0) return __LINE__;
  
  return 0;
}

int testMisc() {
  if(Abs((IntT) -2) != 2) return __LINE__;
  if(Abs((IntT) 2) != 2) return __LINE__;
  if(Sign((IntT) -2) != -1) return __LINE__;
  if(Sign((IntT) 2) != 1) return __LINE__;
  if(Round(0.3) != 0) return __LINE__;
  if(Round(0.7) != 1) return __LINE__;
  if(Floor(0.3) != 0) return __LINE__;
  if(Floor(0.7) != 0) return __LINE__;
  if(Floor(1.2) != 1) return __LINE__;

  UIntC x = 4;
  UIntC y = 5;
  IntT v = Abs((int) x -  y);
  if(v != 1) return __LINE__;

  return 0;
}

int testSubIndexRange2dIter() {
  IndexRange2dC rect1(0,6,0,5);
  IndexRange2dC rect2(IndexC(5),IndexC(5));
  //cerr << "Area=" << rect2.Area() << "\n";
  int rects = 0;
  for(SubIndexRange2dIterC it(rect1,rect2);it;it++) {
    if(it.Window().Area() != rect2.Area()) return __LINE__;
    rects++;
  }
  if(rects != 6) return __LINE__;
  return 0;
}

int testSubIndexRange3dIter() {
  IndexRange3dC rect1(0,5,0,6,0,7);
  IndexRange3dC rect2(IndexC(5),IndexC(5),IndexC(5));
  //cerr << "Area=" << rect2.Area() << "\n";
  int rects = 0;
  for(SubIndexRange3dIterC it(rect1,rect2);it;it++) {
    if(it.Window().Volume() != rect2.Volume()) return __LINE__;
    rects++;
  }
  if(rects != 24) return __LINE__;
  return 0;
}


template class RCHandleC<TestBodyC>;
template class RCWrapC<IntT>;
