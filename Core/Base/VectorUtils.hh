#ifndef RAVLBASEVECTORNDOTPRODUCT_HH
#define RAVLBASEVECTORNDOTPRODUCT_HH

#include <cstddef>

//! docentry="Ravl.API.Math.Linear Algebra"
//! userlevel=Develop
//! author="Bill Christmas; Charles Galambos"

namespace RavlBaseVectorN {
  
  extern double (*g_DotProductD)(const double*, const double*, size_t) ;
  extern float (*g_DotProductF)(const float*, const float*, size_t) ;
  extern double (*g_QuadProductD)(const double*, const double*, const double*, size_t) ;
  
  inline double DotProduct(const double* v1, const double* v2, size_t size) 
  { return (*g_DotProductD)(v1,v2,size); }
  //: Fast double dot product, with optional hardware speedup

  inline float DotProduct(const float* v1, const float* v2, size_t size) 
  { return (*g_DotProductF)(v1,v2,size); }
    //: Fast float dot product, with optional hardware speedup

  inline double QuadProduct(const double* v1, const double* v2, const double* v3, size_t size) 
  { return (*g_QuadProductD)(v1,v2,v3,size); }
  //: Fast double quadratic product, with optional hardware speedup
  // Performs: Sum over arrays of v1 * (v1 * v3 + v2)

}

#endif
