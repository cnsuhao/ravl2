
#include "Ravl/PatternRec/DistanceMax.hh"

namespace RavlN {

  
  //: Measure the distance from d1 to d2.
  
  RealT DistanceMaxBodyC::Measure(const VectorC &d1,const VectorC &d2) const {
    return VectorC(d1 - d2).MaxMagintude();
  }
  
}
