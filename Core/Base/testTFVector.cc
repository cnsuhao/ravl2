
#include "Ravl/TFVector.hh"
#include "Ravl/Pair.hh"
#include "Ravl/FIndex.hh"

#include <iostream.h>

using namespace RavlN;

int testTFVector();
int testPair();

int main(int nargs,char **argv) {
  int ln;
  if((ln = testTFVector()) != 0) {
    cerr << "Error line :" << ln << "\n";
    return 1;
  }
  if((ln = testPair()) != 0) {
    cerr << "Error line :" << ln << "\n";
    return 1;
  }
  cerr <<"Test passed ok. \n";
  return 0;
}

int testPair() {
  PairC<IntT> apair(1,2);
  if(apair[0] != 1) return __LINE__;
  if(apair[1] != 2) return __LINE__;
  if(apair.A() != 1) return __LINE__;
  if(apair.B() != 2) return __LINE__;
  apair.Swap();
  if(apair.A() != 2) return __LINE__;
  if(apair.B() != 1) return __LINE__;
  return 0;
}

int testTFVector() {
  TFVectorC<IntT,2> test1;
  test1[0] = 1;
  test1[1] = 2;  
  TFVectorC<IntT,2> test2 = test1 * 2;
  if(test2[0] != 2) return __LINE__;
  if(test2[1] != 4) return __LINE__;
  test2 *= 2;
  if(test2[0] != 4) return __LINE__;
  if(test2[1] != 8) return __LINE__;
  if(test2.SumSqr() != 80) return __LINE__;
  TFVectorC<IntT,2> test3 = test1 * 4;
  if(test3 == test1) return __LINE__;
  test3 /= 4;
  if(test3 != test1) return __LINE__;
  
  return 0;
}


template class TFVectorC<SByteT,1>;
template class TFVectorC<IntT,2>;
template class TFVectorC<RealT,3>;
template class PairC<IntT>;
template class FIndexC<3>;
