// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_NEARESTNEIGHBOUR_HEADER
#define RAVL_NEARESTNEIGHBOUR_HEADER 1
/////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! userlevel=Normal
//! docentry="Ravl.Pattern Recognition.Classify"
//! file="Ravl/PatternRec/Classify/ClassifyNearestNeighbour.hh"

#include "Ravl/PatternRec/Distance.hh"
#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/PatternRec/DistanceSqrEuclidean.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/PatternRec/SampleLabel.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/ClassifyVector.hh"

namespace RavlN {

  //! userlevel=Develop
  //: k nearest neighbours classifier.
  // Classify probe vector as the most common amoung its k nearest neighbours.
  // If there's a conflict the label with the smallest average distance is used.
  
  class ClassifyNearestNeighbourBodyC 
    : public ClassifyVectorBodyC
  {
  public:
    ClassifyNearestNeighbourBodyC(const SampleVectorC &vectors,
				  const SampleLabelC &labels,
				  const DistanceC &xdistMetric = DistanceSqrEuclideanC());
    //: Constructor.

    ClassifyNearestNeighbourBodyC(const SampleVectorC &vectors,
				  const DistanceC &xdistMetric = DistanceSqrEuclideanC());
    //: Constructor.
    
    virtual UIntT Classify(const VectorC &data) const;
    //: Classify vector 'data' return the most likely label.
    
  protected:    
    DistanceC distanceMetric; // Distance metric to use.
    SampleVectorC vectors;
    SampleLabelC vlabels;
  };
  
  //! userlevel=Normal
  //: k nearest neighbours classifier.
  // Classify probe vector as the most common amoung its k nearest neighbours.
  // If there's a conflict the label with the smallest average distance is used.
  
  class ClassifyNearestNeighbourC 
    : public ClassifyVectorC
  {
  public:
    ClassifyNearestNeighbourC(const SampleVectorC &vectors,
			      const SampleLabelC &labels,
			      const DistanceC &xdistMetric = DistanceSqrEuclideanC())
      : ClassifyVectorC(*new ClassifyNearestNeighbourBodyC(vectors,labels,xdistMetric))
    {}
    //: Constructor.
    
    ClassifyNearestNeighbourC(const SampleVectorC &vectors,
			      const DistanceC &xdistMetric = DistanceSqrEuclideanC())
      : ClassifyVectorC(*new ClassifyNearestNeighbourBodyC(vectors,xdistMetric))
    {}
    //: Constructor.
    
  protected:
    ClassifyNearestNeighbourC(ClassifyNearestNeighbourBodyC &bod)
      : ClassifyVectorC(bod)
    {}
    //: Body constructor.
    
    ClassifyNearestNeighbourBodyC &Body()
    { return static_cast<ClassifyNearestNeighbourBodyC &>(ClassifyVectorC::Body()); }
    //: Access body.
    
    const ClassifyNearestNeighbourBodyC &Body() const
    { return static_cast<const ClassifyNearestNeighbourBodyC &>(ClassifyVectorC::Body()); }
    //: Access body.
    
  public:
    
  };
  
}
#endif
