// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNKMEANS_HEADER
#define RAVL_DESIGNKMEANS_HEADER 1
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! docentry="Ravl.Pattern Recognition.Cluster"

#include "Ravl/PatternRec/DesignClassifyVectorUnsupervised.hh"
#include "Ravl/PatternRec/DistanceSqrEuclidean.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Design a k means classifer.
  
  class DesignKMeansBodyC
    : public DesignClassifyVectorUnsupervisedBodyC
  {
  public:
    DesignKMeansBodyC(UIntT nk,const DistanceC &distanceMetric = DistanceSqrEuclideanC())
      : distance(distanceMetric),
	k(nk)
    {}
    //: Constructor.
    
    virtual ClassifyVectorC Apply(const SampleC<VectorC> &in);
    //: Create a clasifier.
    
    UIntT K() const
    { return k; }
    //: Access number of clusters.
    
  protected:
    DistanceC distance;
    UIntT k;
  };

  //! userlevel=Normal
  //: Design a k means classifer.
  
  class DesignKMeansC 
    : public  DesignClassifyVectorUnsupervisedC
  {
  public:
    DesignKMeansC()
    {}
    //: Default constructor.
    // Creates an invalid constructor.
    
    DesignKMeansC(UIntT k,const DistanceC &distanceMetric = DistanceSqrEuclideanC())
      : DesignClassifyVectorUnsupervisedC(*new DesignKMeansBodyC(k,distanceMetric))
    {}
    //: Default constructor.
    // Creates an invalid constructor.
    
  protected:
    DesignKMeansC(DesignKMeansBodyC &bod)
      : DesignClassifyVectorUnsupervisedC(bod)
    {}
    //: Body constructor.
    
    DesignKMeansBodyC &Body()
    { return static_cast<DesignKMeansBodyC &>(DesignClassifyVectorUnsupervisedC::Body()); }
    //: Access body.

    const DesignKMeansBodyC &Body() const
    { return static_cast<const DesignKMeansBodyC &>(DesignClassifyVectorUnsupervisedC::Body()); }
    //: Access body.
    
  public:
    UIntT K() const
    { return Body().K(); }
    //: Access number of clusters.
    
  };
}


#endif
