

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
  SampleC<IntT> sample(true);
  for(int i = 0;i < 10;i++)
    sample.Append(i);
  if(sample.Size() != 10) return __LINE__;
  
  return 0;
}

int testDataSet1() {
  DataSet1C<SampleC<IntT> > dataset(true);
  dataset.Append(10);
  dataset.Append(11);
  UIntT count = 0;
  for(DataSet1IterC<SampleC<IntT> > it(dataset);it;it++)
    count++;
  if(count != 2) return __LINE__;
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
  UIntT count = 0;
  for(DataSet3IterC<SampleC<IntT>,SampleC<RealT>,SampleC<bool> > it(dataset);it;it++)
    count++;
  if(count != 2) return __LINE__;
  return 0;
}
