#ifndef RAVLPATRECDISTANCEMAX_HEADER 
#define RAVLPATRECDISTANCEMAX_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/PatternRec/Distance.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Distance body.
  
  class DistanceMaxBodyC
    : public DistanceBodyC
  {
  public:
    DistanceMaxBodyC()
      {}
    //: Default constructor.
    
    virtual RealT Measure(const VectorC &d1,const VectorC &d2) const;
    //: Measure the distance from d1 to d2.
    
  };

  //! userlevel=Develop
  //: Distance Metric
  
  class DistanceMaxC
    : public DistanceC
  {
  public:
    DistanceMaxC()
      : DistanceC(*new DistanceMaxBodyC())
      {}
    //: Default constructor.
    
    
  };
  
}



#endif
