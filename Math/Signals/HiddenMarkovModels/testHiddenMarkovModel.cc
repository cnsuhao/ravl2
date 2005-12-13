// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlHMM
//! file="Ravl/Math/Signals/HiddenMarkovModels/exHiddenMarkovModel.cc"

#include "Ravl/HiddenMarkovModel.hh"
#include "Ravl/Option.hh"

using namespace RavlN;

RealT initTrans[] = {
  0.5, 0.2, 0.3,
  0.4, 0.2, 0.4,
  0.1, 0.6, 0.3
};

RealT initObs[] = {
  0.6, 0.4, 0.1, 0.1,
  0.3, 0.4, 0.2, 0.3,
  0.1, 0.2, 0.7, 0.6,
};

VectorC observations[] = {
  VectorC(1,0,0,0),
  VectorC(1,0,0,0),
  VectorC(0,1,0,0), 
  VectorC(0,0,1,0)
};

int TestBasic() {
  cout << "TestBasic(), Called. \n";
  MatrixC trans(3,3,initTrans);
  MatrixC obs(3,4,initObs);

  VectorC sv(3);
  sv.Fill(0);
  for(int i = 0;i < 3; i++) {
    sv[i] = 1;
    //cerr << "Value=" << (trans * sv).Sum() << "\n";
    sv[i] = 0;
  }
  
  HiddenMarkovModelC mm(trans,obs);
  VectorC state(1,0,0);
  SArray1dC<VectorC> vec(4);
  for(int i = 0;i < 4;i++) {
    state = mm.Forward(state,observations[i]);
    vec[i] = observations[i];
    cerr << "State=" << state <<"\n";
  }
  VectorC istate(1,0,0);
  SArray1dC<UIntT> path;
  cerr << "Viterbi:\n";
  mm.Viterbi(vec,istate,path);
  cerr << "Path=" << path << "\n";
  return 0;
}

RealT initTrans2[] = {
  0.0, 0.0, 0.0 , 0.0,
  1.0, 0.0, 0.0 , 0.0,
  0.0, 1.0, 0.5 , 0.0,
  0.0, 0.0, 0.5 , 1.0
};

RealT initObs2[] = {
  0.25, 0.1,
  0.25, 0.1,
  0.25, 0.7,
  0.25, 0.1,
};

VectorC observations2[] = {
  VectorC(1,0),
  VectorC(1,0),
  VectorC(0,1),
  VectorC(1,0), 
  VectorC(1,0)
};

int expected2[] = {
  1,
  2,
  2,
  3,
  3
};


int TestVirterbi() {
  cout << "TestVirterbi(), Called. \n";
  MatrixC trans(4,4,initTrans2);
  MatrixC obs(4,2,initObs2);
  
  VectorC sv(4);
  sv.Fill(0);
  for(int i = 0;i < 4; i++) {
    sv[i] = 1;
    //cerr << "Value=" << (trans * sv).Sum() << "\n";
    sv[i] = 0;
  }
  
  HiddenMarkovModelC mm(trans,obs);
  VectorC state(1,0,0,0);
  SArray1dC<VectorC> vec(5);
  for(int i = 0;i < vec.Size();i++) {
    state = mm.Forward(state,observations2[i]);
    vec[i] = observations2[i];
    cerr << "State=" << state <<"\n";
  }
  VectorC istate(1,0,0,0);
  SArray1dC<UIntT> path;
  cerr << "Viterbi:\n";
  mm.Viterbi(vec,istate,path);
  cerr << "Path=" << path << "\n";
  for(int i = 0;i < vec.Size();i++) {
    if(expected2[i] != path[i])
      return __LINE__;
  }
  return 0;
}


int main() {
  int ln;
  if((ln = TestBasic()) > 0) {
    cerr << "Test failed " << ln << "\n";
    return 1;
  }
  if((ln = TestVirterbi()) > 0) {
    cerr << "Test failed " << ln << "\n";
    return 1;
  }
  cout << "Test passed. \n";
  return 0;
}
