// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/Discriminator.hh"

namespace RavlLogicN {
  
  //: Distinguish between the the two sets of examples.
  
  LiteralC DiscriminatorBodyC::Distinguish(const DecisionExamplesC &set1,const DecisionExamplesC &set2) {
    LiteralC ret;
    RavlAssertMsg(0,"DiscriminatorBodyC::Distinguish(), Not implemented. ");
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
