//! rcsid="$Id$"

#include "Ravl/PatternRec/DistanceMahalanobis.hh"

namespace RavlN {


  //: Constructor.
  
  DistanceMahalanobisBodyC::DistanceMahalanobisBodyC(const MatrixC &covVar)
  {
    iCovar = covVar.Inverse();
  }
  
  //: Measure the distance from d1 to d2.
  
  RealT DistanceMahalanobisBodyC::Measure(const VectorC &d1,const VectorC &d2) const {
    VectorC x(d1 - d2); 
    return Sqrt(x.Dot(iCovar * x));
  }
  
}
