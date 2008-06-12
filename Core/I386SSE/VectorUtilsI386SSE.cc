#include "Ravl/VectorUtils.hh"
#include "Ravl/VectorUtilsI386SSE.hh"
#include <emmintrin.h>
#include "Ravl/Stream.hh"
#include "Ravl/CPUID.hh"

namespace RavlBaseVectorN {

  using namespace RavlN;

  
  static double SSEDotProduct(const double* v1, const double* v2, size_t Size) {
    const double* wPtr = v1;
    const double* const ewPtr = wPtr + (Size & ~0x1);
    const double* dPtr = v2;
    __m128d sum = _mm_setzero_pd();
    if((((unsigned long int) wPtr) & 0xf) == 0) { // this 16-byte aligned ?
      if((((unsigned long int) dPtr) & 0xf) == 0) {// v    16-byte aligned ?
        while(wPtr != ewPtr) {
          const __m128d val = _mm_load_pd(dPtr);
          sum = _mm_add_pd(sum, _mm_mul_pd(val, _mm_load_pd(wPtr)));
          dPtr += 2;
          wPtr += 2;
        }
      }
      else {
        while(wPtr != ewPtr) {
          const __m128d val = _mm_loadu_pd(dPtr);
          sum = _mm_add_pd(sum, _mm_mul_pd(val, _mm_load_pd(wPtr)));
          dPtr += 2;
          wPtr += 2;
        }
      }
    }
    else {
      if((((unsigned long int) dPtr) & 0xf) == 0) {// v    16-byte aligned ?
        while(wPtr != ewPtr) {
          const __m128d val = _mm_load_pd(dPtr);
          sum = _mm_add_pd(sum, _mm_mul_pd(val, _mm_loadu_pd(wPtr)));
          dPtr += 2;
          wPtr += 2;
        }
      }
      else {
        while(wPtr != ewPtr) {
          const __m128d val = _mm_loadu_pd(dPtr);
          sum = _mm_add_pd(sum, _mm_mul_pd(val, _mm_loadu_pd(wPtr)));
          dPtr += 2;
          wPtr += 2;
        }
      }
    }

    if(Size & 1) { // Odd length ?
      const __m128d val = _mm_load_sd(dPtr++);
      sum = _mm_add_pd(sum, _mm_mul_sd(val, _mm_load_sd(wPtr++)));
    }
    double tmp[2];
    _mm_storeu_pd(tmp, sum);
    return tmp[0] + tmp[1];
  }

  
  int VectorSSEInit() {
    if (SSE2()) {
      g_DotProductD = &SSEDotProduct;
      //cerr<<"SSE:yes\n";
    } else {
      //cerr<<"SSE:no\n";
    }
    return 0;
  }
  
  static int a = VectorSSEInit();
  
}
