//! rcsid="$Id$"

#include "Ravl/PatternRec/Distance.hh"
#include "Ravl/Assert.hh"

namespace RavlN {

  //: Measure the distance from d1 to d2.
  
  RealT DistanceBodyC::Measure(const VectorC &d1,const VectorC &d2) const {
    RavlAssertMsg(0,"DistanceBodyC::Measure(), Abstract method called. ");
    return 1;
  }
  
}
