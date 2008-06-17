#include "Ravl/VectorUtils.hh"
#include "Ravl/Stream.hh"

namespace RavlBaseVectorN {

  using namespace RavlN;
  
  static double BaseDotProductD(const double* v1, const double* v2, size_t Size) {
    double sum = 0.0;
    const double* ptr1 = v1;
    const double* ptr2 = v2;
    for(unsigned int i=Size; i>0; --i)
      sum += *ptr1++ * *ptr2++;
    return sum;  
  }

  static float BaseDotProductF(const float* v1, const float* v2, size_t Size) {
    float sum = 0.0;
    const float* ptr1 = v1;
    const float* ptr2 = v2;
    for(unsigned int i=Size; i>0; --i)
      sum += *ptr1++ * *ptr2++;
    return sum;  
  }
  
  static double BaseQuadProductD(const double *Data, const double *Weights1,
                               const double *Weights2, size_t Size) {
    double retVal = 0.;
    const double* wPtr = Weights1;
    const double* w2Ptr = Weights2;
    const double* const ewPtr = wPtr + Size;
    const double* dPtr = Data;
    while(wPtr != ewPtr)
      {
        const double val = *dPtr++;
        retVal += val * (*wPtr++ + *w2Ptr++ * val);
      }
    return retVal;
  }

  double (*g_DotProductD)(const double*, const double*, size_t) = &BaseDotProductD;
  float (*g_DotProductF)(const float*, const float*, size_t) = &BaseDotProductF;
  double (*g_QuadProductD)(const double*, const double*, const double*, size_t) = &BaseQuadProductD;

}
