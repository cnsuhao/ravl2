// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DesignKMeans.hh"
#include "Ravl/HSet.hh"
#include "Ravl/Math.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter3.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/PatternRec/ClassifyNearestNeighbour.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Create a clasifier.
  
  ClassifyVectorC DesignKMeansBodyC::Apply(const SampleC<VectorC> &in) {
    ClassifyVectorC ret;
    ONDEBUG(cerr << "DesignKMeansBodyC::Apply(), Called with " << in.Size() << " vectors. K=" << k << "\n");
    SArray1dC<VectorC> means(k);
    if(in.Size() == 0) {
      cerr << "DesignKMeansBodyC::Apply(), WARNING: No data samples given. \n";
      return ClassifyVectorC();
    }
    if(in.Size() <= k) {
      cerr << "DesignKMeansBodyC::Apply(), WARNING: Fewer samples than means. \n";
      return ClassifyNearestNeighbourC(in,distance);
    }
    
    // Pick some random points from the set to use as initial means.
    
    HSetC<UIntT> used;
    UIntT index,dim;
    dim = in.First().Size();
    
    for(SArray1dIterC<VectorC> it(means);it;it++) {
      do {
	index = RandomInt() % in.Size();
	if(used[index])
	  continue;
	*it = in[index].Copy();
	used += index;
      } while(0);
    }
    
    // Reassign according to distance.
    
    SArray1dC<VectorC> sums(k);
    SArray1dC<UIntT> counts(k);
    for(SArray1dIter2C<VectorC,UIntT> zit(sums,counts);zit;zit++) {
      zit.Data1() = VectorC(dim);
      zit.Data2() = 0;
    }
    RealT cost = 0,oldcost;
    IntT iters = 0;
    SArray1dIterC<VectorC> mit(means);

    // Update means iteratively.
    
    do {
      oldcost = cost;
      cost = 0;
      
      // Reclassify samples.
      
      for(SampleIterC<VectorC> it(in);it;it++) {
	mit.First();
	RealT minDist = distance.Measure(*mit,*it);
	index = 0;
	for(mit++;mit;mit++) {
	  RealT dist =  distance.Measure(*mit,*it);
	  if(dist < minDist) {
	    minDist = dist;
	    index = mit.Index().V();
	  }
	}
	cost += minDist;
	sums[index] += *it;
	counts[index]++;
      }
      
      // Update means.
      
      for(SArray1dIter3C<VectorC,UIntT,VectorC> uit(sums,counts,means);uit;uit++) {
	if(uit.Data2() > 0)
	  uit.Data3() = uit.Data1() / ((RealT) uit.Data2());
	else {
	  // Reinitalise from a random sample.
	  index = RandomInt() % in.Size();
	  uit.Data3() = (in[index]).Copy();
	}
	uit.Data1().Fill(0);
	uit.Data2() = 0;
      }
      iters++;
      ONDEBUG(cerr <<"Iteration complete. Cost=" << cost << " Oldcost=" << oldcost << "\n");
    } while(iters < 3 || ((oldcost - cost) > 1e-6) );
    
    return ClassifyNearestNeighbourC(SampleC<VectorC>(means),distance);
  }
  
}
