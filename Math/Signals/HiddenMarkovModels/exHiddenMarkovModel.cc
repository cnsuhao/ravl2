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
  0.5,0.25,0.25,
  0.375,0.125,0.375,
  0.125,0.625,0.375
};

RealT initObs[] = {
  0.6,0.2,0.15,0.05,
  0.25,0.25,0.25,0.25,
  0.05,0.1,0.35,0.5,
};

VectorC observations[] = {
  VectorC(1,0,0,0),
  VectorC(1,0,0,0),
  VectorC(0,1,0,0), 
  VectorC(0,0,1,0)
};
int main() {
  
  MatrixC trans(3,3,initTrans);
  MatrixC obs(3,4,initObs);
  
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
}
