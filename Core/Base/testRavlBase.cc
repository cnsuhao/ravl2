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

using namespace RavlN;

class TestBodyC
  : public RCBodyVC
{
public:
  TestBodyC()
  {}
};

int testIndex();
int testMisc();

int main()
{
  int ln;
  if((ln = testIndex()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  if((ln = testMisc()) != 0) {
    cerr << "Test failed at line:" << ln << "\n";
    return 1;
  }
  
  cerr << "Test passed ok. \n";
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

template class RCHandleC<TestBodyC>;
template class RCWrapC<IntT>;
