#ifndef RAVLPATRECDISTANCEMAHALANOBIS_HEADER 
#define RAVLPATRECDISTANCEMAHALANOBIS_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/PatternRec/Distance.hh"
#include "Ravl/Matrix.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Distance body.
  
  class DistanceMahalanobisBodyC
    : public DistanceBodyC
  {
  public:
    DistanceMahalanobisBodyC(const MatrixC &covVar);
    //: Constructor.
    
    virtual RealT Measure(const VectorC &d1,const VectorC &d2) const;
    //: Measure the distance from d1 to d2.

  protected:
    MatrixC iCovar; // Inverse covariance matrix.
  };

  //! userlevel=Develop
  //: Distance Metric
  
  class DistanceMahalanobisC
    : public DistanceC
  {
  public:
    DistanceMahalanobisC(const MatrixC &covVar)
      : DistanceC(*new DistanceMahalanobisBodyC(covVar))
      {}
    //: Default constructor.
    
    
  };
  
}



#endif
