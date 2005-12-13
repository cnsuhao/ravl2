// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlHMM
//! file="Ravl/Math/Signals/HiddenMarkovModels/HiddenMarkovModel.cc"

#include "Ravl/HiddenMarkovModel.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter3.hh"
#include "Ravl/SArray1dIterR.hh"

namespace RavlN {
  
  //: Contructor.
  
  HiddenMarkovModelC::HiddenMarkovModelC(const MatrixC &nTransition,const MatrixC &nConfusion)
    : transition(nTransition),
      confusion(nConfusion)
  {
    RavlAssert(transition.Cols() == confusion.Rows());
    for(UIntT i = 0;i < transition.Cols();i++) {
      if((Abs(transition.SliceColumn(i).Sum() - 1) > 0.00000001)) {
	cerr << "WARNING: Transition matrix col " << i << " sums to " << transition.SliceColumn(i).Sum() << "\n";
      }
    }
    for(UIntT i = 0;i < confusion.Cols();i++) {
      if(Abs(confusion.SliceColumn(i).Sum() - 1) > 0.00000001) {
	cerr << "WARNING: Confusion matrix col " << i << " sums to " << confusion.SliceColumn(i).Sum() << "\n";
      }
    }
  }
  
  //: Compute the probabilty of next state, given the current state and an observation.
  
  VectorC HiddenMarkovModelC::Forward(const VectorC &state,const VectorC &observation) {
    VectorC stateProb = (confusion * observation);
    //cerr << "StateProb=" << stateProb <<"\n";
    return (transition * state) * stateProb;
  }
  
  class HMMViterbiStateC {
  public:
    HMMViterbiStateC()
    {}
    
    HMMViterbiStateC(UIntT n)
      : source(n),
	prob(n)
    {}
    //: Constructor.
    
    SArray1dC<UIntT> &Source()
    { return source; }
    //: Access likeliest source.
    
    SArray1dC<RealT> &Prob()
    { return prob; }
    //: Access probability of source.
    
    VectorC &StateProbability()
    { return stateProb; }
    //: Access probability of states a this time.
    
  protected:
    SArray1dC<UIntT> source;
    SArray1dC<RealT> prob;
    VectorC stateProb;
  };
  //: Given a sequence of observations find the most likely 
  
  RealT HiddenMarkovModelC::Viterbi(const SArray1dC<VectorC> &observations,const VectorC &initState,SArray1dC<UIntT> &path) {
    path = SArray1dC<UIntT>(observations.Size());
    SArray1dC<HMMViterbiStateC> stateProb(observations.Size());
    
    // Compute forward probabilities.
    VectorC last = initState;
    for(SArray1dIter2C<HMMViterbiStateC,VectorC> oit(stateProb,observations);oit;oit++) {
      HMMViterbiStateC &here = oit.Data1();
      VectorC tranObs = confusion * oit.Data2();
      //cerr << "Tran=" << tranObs << "\n";
      VectorC prob(last.Size());
      here.Source() = SArray1dC<UIntT> (last.Size());
      for(SArray1dIter3C<UIntT,RealT,RealT> it(here.Source(),prob,tranObs);it;it++) {
	UIntT i = it.Index().V();
	SArray1dC<RealT> slice = transition.SliceRow(i);
	SArray1dIter2C<RealT,RealT> sit(slice,last);
	IndexC max = sit.Index();
	RealT maxval = sit.Data1() * sit.Data2();
	for(;sit;sit++) {
	  RealT val = sit.Data1() * sit.Data2();
	  if(val > maxval) {
	    max = sit.Index();
	    maxval = val;
	  }
	}
	//cerr << " " << maxval << "\n";
	it.Data1() = max.V();
	it.Data2() = maxval * it.Data3();
      }
      here.Prob() = prob;
      last = prob;
      //cerr << "Prob=" << prob <<"\n";
      //cerr << here.Source() << "\n";
    }
    // Trace path.
    IndexC max = stateProb[stateProb.Size()-1].Prob().IndexOfMax();
    //cerr << "INit=" << max << "\n";
    for(int i = stateProb.Size()-1;i >= 0;i--) {
      //cerr << i << "=" << max << "\n";
      path[i] = max.V();
      max = stateProb[i].Source()[max];
    }
    //cerr << "Path=" << path << "\n";
    return true;
  }

}
