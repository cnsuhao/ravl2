
#include "Ravl/PatternRec/DistanceEuclidean.hh"
#include "Ravl/Stream.hh"

using namespace RavlN;

int testEuclidian();

int main() {
  int ln;
  if((ln = testEuclidian()) != 0) {
    cerr << "Test failed " << ln <<"\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}


int testEuclidian() {
  cerr << "testEuclidian(). Started. \n";  
  DistanceEuclideanC de;
  if(Abs(de.Measure(VectorC(1,0),VectorC(2,0)) - 1) > 0.000000001)
    return __LINE__;
  return 0;
}
