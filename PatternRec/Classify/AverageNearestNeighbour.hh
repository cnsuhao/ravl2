// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_AVERAGENEARESTNEIGHBOUR_HEADER
#define RAVL_AVERAGENEARESTNEIGHBOUR_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"

#include "Ravl/PatternRec/KNearestNeighbour.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Average k nearest neighbour classifier.
  // Amoung the k nearest neighours to the probe choose the label with the smallest average distance.
    
  class AverageNearestNeighbourBodyC 
    : public KNearestNeighbourBodyC
  {
  public:
    AverageNearestNeighbourBodyC(const DataSet2C<SampleVectorC,SampleLabelC> &data,
			   UIntT defaultK = 5,
			   const DistanceC &xdistMetric = DistanceSqrEuclideanC());
    //: Default constructor.
    
    virtual UIntT Classify(const VectorC &data) const;
    //: Classify vector 'data' return the most likely label.
    
    virtual VectorC Confidence(const VectorC &data) const;
     //: Estimate the confidence for each label.
    // The meaning of the confidence assigned to each label depends
    // on the classifier used. The higher the confidence the more likely
    // it is the label is correct.
    
  };
  
  //! userlevel=Normal
  //: Average k nearest neighbour classifier.
  // Amoung the k nearest neighours to the probe choose the label with the smallest average distance.
  
  class AverageNearestNeighbourC 
    : public KNearestNeighbourC
  {
  public:
    AverageNearestNeighbourC(const DataSet2C<SampleVectorC,SampleLabelC> &data,UIntT defaultK = 5,const DistanceC &xdistMetric = DistanceSqrEuclideanC())
      : KNearestNeighbourC(*new AverageNearestNeighbourBodyC(data,defaultK,xdistMetric))
    {}
    //: Constructor.
    
  protected:
    AverageNearestNeighbourC(AverageNearestNeighbourBodyC &bod)
      : KNearestNeighbourC(bod)
    {}
    //: Body constructor.
    
    AverageNearestNeighbourBodyC &Body()
    { return static_cast<AverageNearestNeighbourBodyC &>(ClassifyVectorC::Body()); }
    //: Access body.
    
    const AverageNearestNeighbourBodyC &Body() const
    { return static_cast<const AverageNearestNeighbourBodyC &>(ClassifyVectorC::Body()); }
    //: Access body.
    
  public:
    
  };
  
}
#endif
