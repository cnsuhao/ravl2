// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Distance/testMeasure.cc"
//! docentry="Ravl.API.Pattern Recognition.Distance"
//! author="Charles Galambos"

#include "Ravl/PatternRec/DistanceEuclidean.hh"
#include "Ravl/Stream.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/EntryPnt.hh"

using namespace RavlN;

int testEuclidian();
int testIO();

int testMeasure(int args,char **argv) {
  int ln;
  if((ln = testEuclidian()) != 0) {
    cerr << "Test failed " << ln <<"\n";
    return 1;
  }
  if((ln = testIO()) != 0) {
    cerr << "Test failed " << ln <<"\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

RAVL_ENTRY_POINT(testMeasure);

int testEuclidian() {
  cerr << "testEuclidian(). Started. \n";  
  DistanceEuclideanC de;
  if(Abs(de.Measure(VectorC(1,0),VectorC(2,0)) - 1) > 0.000000001)
    return __LINE__;
  return 0;
}

int testIO() {
  DistanceEuclideanC de;
  StrOStreamC os;
  os << de;
  StrIStreamC is(os.String());
  DistanceC de2;
  is >> de2;
  if(!de2.IsValid()) return __LINE__;
  DistanceEuclideanC tst(de2);
  if(!tst.IsValid()) return __LINE__;
  return 0;
}
