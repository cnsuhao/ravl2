// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classify/ClassifyNearestNeighbour.cc"

#include "Ravl/PatternRec/ClassifyNearestNeighbour.hh"
#include "Ravl/PatternRec/DataSet2Iter.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/Hash.hh"
#include "Ravl/RealC.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Default constructor.
  
  ClassifyNearestNeighbourBodyC::ClassifyNearestNeighbourBodyC(const SampleVectorC &nvectors,
							       const SampleLabelC &nlabels,
							       const DistanceC &xdistanceMetric)
    : distanceMetric(xdistanceMetric),
      vectors(nvectors),
      vlabels(nlabels)
  {
    if(vlabels.Size() > 0)
      labels = vlabels.MaxValue()+1;
    else
      labels = nvectors.Size();
    ONDEBUG(cerr << "ClassifyNearestNeighbourBodyC::ClassifyNearestNeighbourBodyC(), Data=" << vectors.Size() <<" Labels=" << labels << "\n");
  }
  
  //: Constructor.
  
  ClassifyNearestNeighbourBodyC::ClassifyNearestNeighbourBodyC(const SampleVectorC &nvectors,
							       const DistanceC &xdistMetric)
    : distanceMetric(xdistMetric),
      vectors(nvectors)
  {
    labels = nvectors.Size();
    ONDEBUG(cerr << "ClassifyNearestNeighbourBodyC::ClassifyNearestNeighbourBodyC(), Data=" << vectors.Size() <<" Labels=" << labels << " vlabels=" << vlabels.Size() << "\n");
  }

  //: Classify vector 'data' return the most likely label.
  
  UIntT ClassifyNearestNeighbourBodyC::Classify(const VectorC &vec) const {
    // Find the k nearest neighbours.
    
    SampleIterC<VectorC> it(vectors);
    IndexC index = 0;
    RealT minDist = distanceMetric.Measure(*it,vec);
    for(it++;it;it++) {
      RealT dist = distanceMetric.Measure(*it,vec);
      if(dist < minDist) {
	minDist = dist;
	index = it.Index();
      }
    }
    if(vlabels.Size() == 0)
      return index.V();
    ONDEBUG(cerr << "Index=" << index << "\n");
    return vlabels[index];
  }
  
}
