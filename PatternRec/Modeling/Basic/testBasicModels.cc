// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Modeling/Basic/testBasicModels.cc"

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
      ins += VectorC(i,j,1);
      outs += VectorC(i * 2 + 1,j * i);
    }
  }
  
  DesignFuncLSQC design(1,false);
  FunctionC func = design.Apply(ins,outs);
  if(!func.IsValid()) return __LINE__;
  VectorC to = func.Apply(VectorC(1,2,1));
  cerr << "Testout=" << to << "\n";
  if((to - VectorC(3,2)).SumSqr() > 0.000000001) return __LINE__;
  
  return 0;
}
