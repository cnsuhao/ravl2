// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classifier/DesignKNearestNeighbour.cc"

#include "Ravl/PatternRec/DesignKNearestNeighbour.hh"
#include "Ravl/PatternRec/ClassifierKNearestNeighbour.hh"
#include "Ravl/PatternRec/ClassifierAverageNearestNeighbour.hh"

namespace RavlN {
  
  //: Constructor.
  
  DesignKNearestNeighbourBodyC::DesignKNearestNeighbourBodyC(UIntT nk,const DistanceC &distMetric,bool nuseAverageKNN)
    : k(nk),
      distanceMetric(distMetric),
      useAverageKNN(nuseAverageKNN)
  {}
  
  //: Create a clasifier.
  
  ClassifierC DesignKNearestNeighbourBodyC::Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out) {
    RavlAssertMsg(in.Size() == out.Size(),"DesignKNearestNeighbourBodyC::Apply(), Sample of vector and labels should be the same size.");
    if(useAverageKNN)
      return ClassifierAverageNearestNeighbourC (DataSet2C<SampleVectorC,SampleLabelC>(in,out),k,distanceMetric);
    return ClassifierKNearestNeighbourC (DataSet2C<SampleVectorC,SampleLabelC>(in,out),k,distanceMetric);
  }
  
  //: Create a clasifier with weights for the samples.
  
  ClassifierC DesignKNearestNeighbourBodyC::Apply(const SampleC<VectorC> &in,
						      const SampleC<UIntT> &out,
						      const SampleC<RealT> &weight) {
    RavlAssertMsg(0,"DesignKNearestNeighbourBodyC::Apply(in,out,weight), Not implemented. Send a feature request! ");
    return ClassifierC();
  }
  
}
