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
#include "Ravl/OS/Date.hh"
#include <iostream.h>

using namespace RavlN;

#define USE_SPEEDTEST 0

int testSample();
int testDataSet1();
int testDataSet2();
int testDataSet3();

#if USE_SPEEDTEST
int testSpeed();
#endif

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
#if USE_SPEEDTEST
  if((ln = testSpeed()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
#endif
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

#if USE_SPEEDTEST
const int testSize = 1000000;
int testSpeed() {
  DataSet1C<SampleC<IntT> > dataset1(true);
  DateC start(true);
  for(int i = 0;i < testSize;i++) 
    dataset1.Append(i);
  DateC end(true);
  cerr << "Create Time1 = " << (end.Double() - start.Double()) << "\n";
  
  DataSet2C<SampleC<IntT>,SampleC<RealT> > dataset2(true);
  start.SetToNow();
  for(int i = 0;i < testSize;i++) 
    dataset2.Append(i,0.3);
  end.SetToNow();
  cerr << "Create Time2 = " << (end.Double() - start.Double()) << "\n";
  
  DataSet3C<SampleC<IntT>,SampleC<RealT>,SampleC<bool> > dataset3(true);
  start.SetToNow();
  for(int i = 0;i < testSize;i++) 
    dataset3.Append(i,0.3,true);
  end.SetToNow();
  cerr << "Create Time3 = " << (end.Double() - start.Double()) << "\n";
  
  UIntT val = 0;
  start.SetToNow();
  for(DataSet1IterC<SampleC<IntT> > it1(dataset1);it1;it1++)
    val += it1.Data();
  end.SetToNow();
  cerr << "Iter Time1 = " << (end.Double() - start.Double()) << "\n";
  
  start.SetToNow();
  for(DataSet2IterC<SampleC<IntT>,SampleC<RealT> > it2(dataset2);it2;it2++) {
    val += it2.Data1() + it2.Data2();
  }
  end.SetToNow();
  cerr << "Iter Time2 = " << (end.Double() - start.Double()) << "\n";

  start.SetToNow();
  for(DataSet3IterC<SampleC<IntT>,SampleC<RealT>,SampleC<bool> > it3(dataset3);it3;it3++) {
    val += it3.Data1() + it3.Data2() + ((int) it3.Data3());
  }
  end.SetToNow();
  cerr << "Iter Time3 = " << (end.Double() - start.Double()) << "\n";
  
  return 0;
}
#endif
