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

  static float BaseQuadProductF(const float *Data, const float *Weights1,
				const float *Weights2, size_t Size) {
    float retVal = 0.;
    const float* wPtr = Weights1;
    const float* w2Ptr = Weights2;
    const float* const ewPtr = wPtr + Size;
    const float* dPtr = Data;
    while(wPtr != ewPtr)
      {
        const float val = *dPtr++;
        retVal += val * (*wPtr++ + *w2Ptr++ * val);
      }
    return retVal;
  }
  
  static void BaseReal2ByteD(unsigned char * byteData, const double *realData, size_t size) {
    for (int i=size; i>0; --i) {
      *(byteData++) = (*realData >= 255.0) ? 255
                                         : (*realData<=0.0) ? 0
                                                            : ((unsigned char) (*realData + 0.5));
      realData++;
    }
  }
   
  double (*g_DotProductD)(const double*, const double*, size_t) = &BaseDotProductD;
  float (*g_DotProductF)(const float*, const float*, size_t) = &BaseDotProductF;
  double (*g_QuadProductD)(const double*, const double*, const double*, size_t) = &BaseQuadProductD;
  float (*g_QuadProductF)(const float*, const float*, const float*, size_t) = &BaseQuadProductF;
  void (*g_Real2ByteD)(unsigned char*, const double*, size_t) = &BaseReal2ByteD;

}
