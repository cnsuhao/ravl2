#ifndef RAVLPATRECDISTANCEEUCLIDEAN_HEADER 
#define RAVLPATRECDISTANCEEUCLIDEAN_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/PatternRec/Distance.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Distance body.
  
  class DistanceEuclideanBodyC
    : public DistanceBodyC
  {
  public:
    DistanceEuclideanBodyC()
      {}
    //: Default constructor.
    
    virtual RealT Measure(const VectorC &d1,const VectorC &d2) const;
    //: Measure the distance from d1 to d2.
    
  };

  //! userlevel=Develop
  //: Distance Metric
  
  class DistanceEuclideanC
    : public DistanceC
  {
  public:
    DistanceEuclideanC()
      : DistanceC(*new DistanceEuclideanBodyC())
      {}
    //: Default constructor.
    
    
  };
  
}



#endif
