#ifndef RAVLPATRECDISTANCECITYBLOCK_HEADER 
#define RAVLPATRECDISTANCECITYBLOCK_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/PatternRec/Distance.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Distance body.
  
  class DistanceCityBlockBodyC
    : public DistanceBodyC
  {
  public:
    DistanceCityBlockBodyC()
      {}
    //: Default constructor.
    
    virtual RealT Measure(const VectorC &d1,const VectorC &d2) const;
    //: Measure the distance from d1 to d2.
    
  };

  //! userlevel=Develop
  //: Distance Metric
  
  class DistanceCityBlockC
    : public DistanceC
  {
  public:
    DistanceCityBlockC()
      : DistanceC(*new DistanceCityBlockBodyC())
      {}
    //: Default constructor.
    
    
  };
  
}



#endif
