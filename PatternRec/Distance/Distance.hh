#ifndef RAVLPATRECDISTANCE_HEADER 
#define RAVLPATRECDISTANCE_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/RefCounter.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Distance body.
  
  class DistanceBodyC
    : public RCBodyVC
  {
  public:
    DistanceBodyC()
      {}
    //: Default constructor.
    
    virtual RealT Measure(const VectorC &d1,const VectorC &d2) const;
    //: Measure the distance from d1 to d2.
    
  };

  //! userlevel=Develop
  //: Distance Metric
  
  class DistanceC
    : public RCHandleC<DistanceBodyC>
  {
  public:
    DistanceC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DistanceC(DistanceBodyC &bod)
      : RCHandleC<DistanceBodyC>(bod)
      {}
    //: Body constructor.
    
    DistanceBodyC &Body()
      { return RCHandleC<DistanceBodyC>::Body(); }
    //: Access body.
    
    const DistanceBodyC &Body() const
      { return RCHandleC<DistanceBodyC>::Body(); }
    //: Access body.
    
  public:
    
    RealT Measure(const VectorC &d1,const VectorC &d2) const
      { return Body().Measure(d1,d2); }
    //: Measure the distance from d1 to d2.

  };
  
}


#endif
