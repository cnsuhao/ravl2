
#include "Ravl/PatternRec/DistanceEuclidean.hh"

namespace RavlN {

  
  //: Measure the distance from d1 to d2.
  
  RealT DistanceEuclideanBodyC::Measure(const VectorC &d1,const VectorC &d2) const {
    return VectorC(d1 - d2).Modulus();
  }
  
}
