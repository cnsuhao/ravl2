// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/DesignMeanShiftCluster.hh"
#include "Ravl/HSet.hh"
#include "Ravl/Math.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter3.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/PatternRec/ClassifierNearestNeighbour.hh"
#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/VirtualConstructor.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Load from stream.
  
  DesignMeanShiftClusterBodyC::DesignMeanShiftClusterBodyC(istream &strm) 
    : DesignClusterBodyC(strm)
  {
    IntT version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("DesignMeanShiftClusterBodyC(istream &), Unrecognised version number in stream. ");
    strm >> distance >> k >> termiter;
  }
  
  //: Load from binary stream.
  
  DesignMeanShiftClusterBodyC::DesignMeanShiftClusterBodyC(BinIStreamC &strm) 
    : DesignClusterBodyC(strm)
  {
    IntT version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("DesignMeanShiftClusterBodyC((BinIStreamC &), Unrecognised version number in stream. ");
    strm >> distance >> k >> termiter;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignMeanShiftClusterBodyC::Save (ostream &out) const {
    if(!DesignClusterBodyC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << distance << ' ' << k << ' ' << termiter;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignMeanShiftClusterBodyC::Save (BinOStreamC &out) const {
    if(!DesignClusterBodyC::Save(out))
      return false;
    IntT version = 0;
    out << version << distance << k << termiter;
    return true;
  }
  
  //: Find means for 'in'.
  
  DListC<VectorC> DesignMeanShiftClusterBodyC::FindMeans(const SampleC<VectorC> &in) {
    DListC<VectorC> clusters;
    if(in.Size() == 0) {
      cerr << "DesignMeanShiftClusterBodyC::Apply(), WARNING: No data samples given. \n";
      return clusters;
    }
    
    UIntT count = 0;
    VectorC shift(in.First().Size());
    VectorC mean;
    for(SampleIterC<VectorC> sit(in);sit;sit++) { // Got through all possible start points.
      do {
	mean = sit->Copy();
	shift.Fill(0);
	for(SampleIterC<VectorC> it(in);it;it++) {
	  VectorC diff = *it - mean ;
	  RealT mag = distance.Magnitude(diff);
	  if(mag > k)
	    continue;
	  shift += diff;
	  count++;
	}
	shift /= (RealT) count;
	if(distance.Magnitude(shift) < termiter)
	  break;
	mean += shift;
      } while(1);
      
      DLIterC<VectorC> cit(clusters);
      for(;cit;cit++) {
	if(distance.Measure(mean,*cit) < (k * 0.2))
	  break; // Already got cluster.
      }
      if(!cit) // Cluster not found.
	clusters.InsLast(mean.Copy());
    }
    return clusters;
  }
  
  //: Create a clasifier.
  
  FunctionC DesignMeanShiftClusterBodyC::Apply(const SampleC<VectorC> &in) {
    ONDEBUG(cerr << "DesignMeanShiftClusterBodyC::Apply(), Called with " << in.Size() << " vectors. K=" << k << "\n");
    DListC<VectorC> clusters = FindMeans(in);    
    SampleC<VectorC> newMeans(clusters.Size());
    for(DLIterC<VectorC> cit(clusters);cit;cit++)
      newMeans.Append(*cit);
    return ClassifierNearestNeighbourC(newMeans,distance);
  }
  
  //: Compute cluster means.

  SArray1dC<MeanCovarianceC> DesignMeanShiftClusterBodyC::Cluster(const SampleC<VectorC> &in) {
    DListC<VectorC> clusters = FindMeans(in);
    SArray1dC<MeanCovarianceC> ret(clusters.Size());
    DLIterC<VectorC> lit(clusters);
    for(SArray1dIterC<MeanCovarianceC> ait(ret);ait;ait++,lit++) {
      *ait = MeanCovarianceC(1,*lit,MatrixC::Identity(lit->Size()) * k);
    }
    return ret;
  }
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(DesignMeanShiftClusterBodyC,DesignMeanShiftClusterC,DesignClusterC);

}

  

