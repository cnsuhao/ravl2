// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/StdMath.hh"
#include "Ravl/Logic/DecisionExamples.hh"
#include "Ravl/HashIter.hh"

namespace RavlLogicN {

  //: Add an example to the node.
  // Return's true if example is a new one.
  
  bool DecisionExamplesBodyC::AddExample(const StateC &state,const LiteralC &decision) {
    examples[decision] += state;
    return histogram.Vote(Tuple2C<StateC,LiteralC>(state,decision)) == 1;
  }
  
  //: Remove examples from this node.
  
  bool DecisionExamplesBodyC::RemoveExamples(DecisionExamplesC &ex) {
    for(HashIterC<Tuple2C<StateC,LiteralC>,UIntC> it(ex.Histogram());it;it++) {
      UIntC &c = histogram[it.Key()];
      RavlAssert(examples[it.Key().Data2()].IsMember(it.Key().Data1()));
      if(c == it.Data()) {
	histogram.Unvote(it.Key());
	examples[it.Key().Data2()] -= it.Key().Data1();
      } else
	c -= it.Data(); // Just subtract the appropriate number of examples.
    }
    return true;
  }
  
  //: Get an estimate of the information in decisions.
  
  RealT DecisionExamplesBodyC::DecisionInformation() {
    HistogramC<LiteralC> hist;
    for(HashIterC<Tuple2C<StateC,LiteralC>,UIntC> it(Histogram());it;it++) 
      hist.Vote(it.Key().Data2(),it.Data().v);
    return hist.Information();
  }
  
  //: Dump examples to a stream.
  
  void DecisionExamplesBodyC::Dump(ostream &out) {
    for(HashIterC<LiteralC,HSetC<StateC> > it(examples);it;it++)
      cerr << " " << it.Key() << " -> " << it.Data() << "\n";
  }
  
}
