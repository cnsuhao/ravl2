// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_CLASSIFYAVERAGENEARESTNEIGHBOUR_HEADER
#define RAVL_CLASSIFYAVERAGENEARESTNEIGHBOUR_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! userlevel=Normal
//! docentry="Ravl.Pattern Recognition.Classify"
//! author="Charles Galambos"
//! file="Ravl/PatternRec/Classify/ClassifyAverageNearestNeighbour.hh"

#include "Ravl/PatternRec/ClassifyKNearestNeighbour.hh"

namespace RavlN {

  //! userlevel=Develop
  //: ClassifyAverage k nearest neighbour classifier.
  // Amoung the k nearest neighours to the probe choose the label with the smallest average distance.
    
  class ClassifyAverageNearestNeighbourBodyC 
    : public ClassifyKNearestNeighbourBodyC
  {
  public:
    ClassifyAverageNearestNeighbourBodyC(const DataSet2C<SampleVectorC,SampleLabelC> &data,
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
  //: ClassifyAverage k nearest neighbour classifier.
  // Amoung the k nearest neighours to the probe choose the label with the smallest average distance.
  
  class ClassifyAverageNearestNeighbourC 
    : public ClassifyKNearestNeighbourC
  {
  public:
    ClassifyAverageNearestNeighbourC(const DataSet2C<SampleVectorC,SampleLabelC> &data,UIntT defaultK = 5,const DistanceC &xdistMetric = DistanceSqrEuclideanC())
      : ClassifyKNearestNeighbourC(*new ClassifyAverageNearestNeighbourBodyC(data,defaultK,xdistMetric))
    {}
    //: Constructor.
    
  protected:
    ClassifyAverageNearestNeighbourC(ClassifyAverageNearestNeighbourBodyC &bod)
      : ClassifyKNearestNeighbourC(bod)
    {}
    //: Body constructor.
    
    ClassifyAverageNearestNeighbourBodyC &Body()
    { return static_cast<ClassifyAverageNearestNeighbourBodyC &>(ClassifyVectorC::Body()); }
    //: Access body.
    
    const ClassifyAverageNearestNeighbourBodyC &Body() const
    { return static_cast<const ClassifyAverageNearestNeighbourBodyC &>(ClassifyVectorC::Body()); }
    //: Access body.
    
  public:
    
  };
  
}
#endif
