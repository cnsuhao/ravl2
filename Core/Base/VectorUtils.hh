#ifndef RAVLBASEVECTORNDOTPRODUCT_HH
#define RAVLBASEVECTORNDOTPRODUCT_HH

#include <cstddef>

namespace RavlBaseVectorN {
  
  extern double (*g_DotProductD)(const double*, const double*, size_t) ;
  extern float (*g_DotProductF)(const float*, const float*, size_t) ;
  
  inline double DotProduct(const double* v1, const double* v2, size_t Size) 
  { return (*g_DotProductD)(v1,v2,Size); }

  inline float DotProduct(const float* v1, const float* v2, size_t Size) 
  { return (*g_DotProductF)(v1,v2,Size); }
  

}

#endif
