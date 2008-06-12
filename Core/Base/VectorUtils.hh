#ifndef RAVLBASEVECTORNDOTPRODUCT_HH
#define RAVLBASEVECTORNDOTPRODUCT_HH

#include <cstddef>

namespace RavlBaseVectorN {
  
  extern double (*pDot)(const double*, const double*, size_t) ;

  inline double DotProduct(const double* v1, const double* v2, size_t Size) {
    return (*pDot)(v1,v2,Size);
  }

}

#endif
