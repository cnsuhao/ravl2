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
//! docentry="Ravl.Pattern Recognition.Classifier"
//! file="Ravl/PatternRec/Classifier/ClassifierNearestNeighbour.hh"

#include "Ravl/PatternRec/Distance.hh"
#include "Ravl/PatternRec/DataSet2.hh"
#include "Ravl/PatternRec/DistanceSqrEuclidean.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/PatternRec/SampleLabel.hh"
#include "Ravl/PatternRec/SampleVector.hh"
#include "Ravl/PatternRec/Classifier.hh"

namespace RavlN {

  //! userlevel=Develop
  //: k nearest neighbours classifier.
  // Classifier probe vector as the most common amoung its k nearest neighbours.
  // If there's a conflict the label with the smallest average distance is used.
  
  class ClassifierNearestNeighbourBodyC 
    : public ClassifierBodyC
  {
  public:
    ClassifierNearestNeighbourBodyC(const SampleVectorC &vectors,
				  const SampleLabelC &labels,
				  const DistanceC &xdistMetric = DistanceSqrEuclideanC());
    //: Constructor.

    ClassifierNearestNeighbourBodyC(const SampleVectorC &vectors,
				  const DistanceC &xdistMetric = DistanceSqrEuclideanC());
    //: Constructor.
    
    virtual UIntT Classifier(const VectorC &data) const;
    //: Classifier vector 'data' return the most likely label.
    
  protected:    
    DistanceC distanceMetric; // Distance metric to use.
    SampleVectorC vectors;
    SampleLabelC vlabels;
  };
  
  //! userlevel=Normal
  //: k nearest neighbours classifier.
  // Classifier probe vector as the most common amoung its k nearest neighbours.
  // If there's a conflict the label with the smallest average distance is used.
  
  class ClassifierNearestNeighbourC 
    : public ClassifierC
  {
  public:
    ClassifierNearestNeighbourC(const SampleVectorC &vectors,
			      const SampleLabelC &labels,
			      const DistanceC &xdistMetric = DistanceSqrEuclideanC())
      : ClassifierC(*new ClassifierNearestNeighbourBodyC(vectors,labels,xdistMetric))
    {}
    //: Constructor.
    
    ClassifierNearestNeighbourC(const SampleVectorC &vectors,
			      const DistanceC &xdistMetric = DistanceSqrEuclideanC())
      : ClassifierC(*new ClassifierNearestNeighbourBodyC(vectors,xdistMetric))
    {}
    //: Constructor.
    
  protected:
    ClassifierNearestNeighbourC(ClassifierNearestNeighbourBodyC &bod)
      : ClassifierC(bod)
    {}
    //: Body constructor.
    
    ClassifierNearestNeighbourBodyC &Body()
    { return static_cast<ClassifierNearestNeighbourBodyC &>(ClassifierC::Body()); }
    //: Access body.
    
    const ClassifierNearestNeighbourBodyC &Body() const
    { return static_cast<const ClassifierNearestNeighbourBodyC &>(ClassifierC::Body()); }
    //: Access body.
    
  public:
    
  };
  
}
#endif
