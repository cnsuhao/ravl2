

#include "Ravl/PatternRec/DataSet1.hh"
#include "Ravl/PatternRec/DataSet2.hh"
#include <iostream.h>

using namespace RavlN;

int testSample();
int testDataSet1();
int testDataSet2();

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
  DataSet1C<SampleC<IntT> > dataset;
  dataset.Append(10);
  return 0;
}

int testDataSet2() {
  DataSet2C<SampleC<IntT>,SampleC<RealT> > dataset;
  dataset.Append(10,0.3);
  return 0;
}
