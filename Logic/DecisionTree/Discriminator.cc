/////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Logic/Discriminator.hh"

namespace RavlLogicN {
  
  //: Distinguish between the the two sets of examples.
  
  LiteralC DiscriminatorBodyC::Distinguish(DecisionExamplesC &set1,DecisionExamplesC &set2) {
    LiteralC ret;
    RavlAssert(0,"DiscriminatorBodyC::Distinguish(), Not implemented. ");
    return ret;
  }

  //: Choose the best distriminator to seperate the decisions made in 'set'. 
  
  LiteralC DiscriminatorBodyC::BestDiscriminator(const DecisionExamplesC &set) {
    LiteralC ret;    
    // Build occurance histograms.
    HashC<LiteralC,HistogramC<LiteralC> > freqTab;
    for(HashIterC<LiteralC,HSetC<StateC> > it(set.Examples());it;it++) {
      HistogramC<LiteralC> &hist = freqTab[it.Key()];
      for(HSetIterC<StateC> sit(it.Data());sit;sit++) {
	for(LiteralIterC lit(sit->List());lit;lit++)
	  hist.Vote(*lit);
      }
    }
    IntT maxDiff = -1;
    // Look for most descriminating literal between any two
    // decisions.
    HSetC<LiteralC> done;
    for(HashIterC<LiteralC,HistogramC<LiteralC> > it2(freqTab);it2;it2++) {
      done += it2.Key();
      for(HashIterC<LiteralC,HistogramC<LiteralC> > nit(freqTab);nit;nit++) {
	if(done[nit.Key()])
	  continue;
	LiteralC nkey;
	IntT ldiff;
	nit.Data().LargestDifference(it2.Data(),nkey,ldiff);
	if(ldiff > maxDiff) {
	  maxDiff = ldiff;
	  ret = nkey;
	}
      }
    }
    return ret;
  }

}
