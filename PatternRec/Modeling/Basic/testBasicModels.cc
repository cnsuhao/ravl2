
#include "Ravl/PatternRec/DesignFuncLSQ.hh"
#include "Ravl/PatternRec/SampleVector.hh"

using namespace RavlN;

int testDesignFuncLSQ();

int main() {
  int ln;
  if((ln = testDesignFuncLSQ()) != 0) {
    cerr << "Test failed line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}

int testDesignFuncLSQ() {
  SampleVectorC ins(10);
  SampleVectorC outs(10);
  
  for(int i = 0;i < 3;i++) {
    for(int j = 0;j < 3;j++) {
      ins += VectorC(i,j);
      outs += VectorC(i * 2 + 1,j * i);
    }
  }
  
  DesignFuncLSQC design(1,false);
  FunctionC func = design.Apply(ins,outs);
  if(!func.IsValid()) return __LINE__;
  VectorC to = func.Apply(VectorC(1,2));
  if((to - VectorC(3,2)).SumSqr() > 0.000000001) return __LINE__;
  //cerr << "Testout=" << to << "\n";
  return 0;
}
