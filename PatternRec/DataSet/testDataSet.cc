// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/testDataSet.cc"


#include "Ravl/PatternRec/DataSet1.hh"
#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/PatternRec/DataSet3.hh"
#include "Ravl/PatternRec/DataSet1Iter.hh"
#include "Ravl/PatternRec/DataSet2Iter.hh"
#include "Ravl/PatternRec/DataSet3Iter.hh"
#include <iostream.h>

using namespace RavlN;

int testSample();
int testDataSet1();
int testDataSet2();
int testDataSet3();

int main() {
  int ln;
  if((ln = testSample()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testDataSet1()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testDataSet2()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  if((ln = testDataSet3()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  cout << "Test passed ok. \n";
  return 0;
}

int testSample() {
  SampleC<IntT> sample;
  int i = 0;
  for(;i < 10;i++)
    sample.Append(i);
  i = 0;
  for(DArray1dIterC<IntT> it(sample.DArray());it;it++,i++)
    if(*it != i) return __LINE__;
  if(sample.Size() != 10) return __LINE__;
  return 0;
}

int testDataSet1() {
  DataSet1C<SampleC<IntT> > dataset(true);
  dataset.Append(10);
  dataset.Append(11);
  dataset.Append(12);
  dataset.Append(13);
  UIntT count = 0;
  for(DataSet1IterC<SampleC<IntT> > it(dataset);it;it++)
    count++;
  if(count != 4) return __LINE__;
  return 0;
}

int testDataSet2() {
  DataSet2C<SampleC<IntT>,SampleC<RealT> > dataset(true);
  dataset.Append(10,0.3);
  dataset.Append(11,0.4);
  UIntT count = 0;
  for(DataSet2IterC<SampleC<IntT>,SampleC<RealT> > it(dataset);it;it++)
    count++;
  if(count != 2) return __LINE__;
  return 0;
}

int testDataSet3() {
  DataSet3C<SampleC<IntT>,SampleC<RealT>,SampleC<bool> > dataset(true);
  dataset.Append(10,0.3,true);
  dataset.Append(11,0.4,false);
  dataset.Append(12,0.5,false);
  UIntT count = 0;
  for(DataSet3IterC<SampleC<IntT>,SampleC<RealT>,SampleC<bool> > it(dataset);it;it++)
    count++;
  if(count != 3) return __LINE__;
  return 0;
}
