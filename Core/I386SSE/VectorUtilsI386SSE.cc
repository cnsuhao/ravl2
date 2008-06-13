#include "Ravl/VectorUtils.hh"
#include "Ravl/VectorUtilsI386SSE.hh"
#include <emmintrin.h>
#include "Ravl/Stream.hh"
#include "Ravl/CPUID.hh"

namespace RavlBaseVectorN {

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
  
  using namespace RavlN;

  // FIXME:- In both these routines if vectors have the same alignment we could process 
  // the first few entries then process as aligned .
  
  static double SSEDotProductD(const double* v1, const double* v2, size_t Size) {
    // For small vectors all the messing about is not worth it.
    if(Size < 12) return BaseDotProductD(v1,v2,Size);
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
  
  
  
  static float SSEDotProductF(const float *v1,const float *v2,unsigned n) {
    // Not worth using this code for small vectors.
    if(n < 12) return BaseDotProductF(v1,v2,n);
    const float* wPtr = v1;
    UIntT quadLen = (n & ~0x3);
    const float* const ewPtr = wPtr + quadLen;
    const float* dPtr = v2;
    __m128 sum = _mm_setzero_ps ();
    
    
    if((((unsigned long int) wPtr) & 0xf) == 0) { // this 16-byte aligned ?
      if((((unsigned long int) dPtr) & 0xf) == 0) {// v    16-byte aligned ?
        while(wPtr != ewPtr) {
          sum = _mm_add_ps(sum,_mm_mul_ps(_mm_load_ps(wPtr),_mm_load_ps(dPtr)));
          wPtr += 4;
          dPtr += 4;
        }
      } else {
        while(wPtr != ewPtr) {
          sum = _mm_add_ps(sum,_mm_mul_ps(_mm_load_ps(wPtr),_mm_loadu_ps(dPtr)));
          wPtr += 4;
          dPtr += 4;
        }
      }
    } else {
      if((((unsigned long int) dPtr) & 0xf) == 0) {// v    16-byte aligned ?
        while(wPtr != ewPtr) {
          sum = _mm_add_ps(sum,_mm_mul_ps(_mm_loadu_ps(wPtr),_mm_load_ps(dPtr)));
          wPtr += 4;
          dPtr += 4;
        }
      } else {
        while(wPtr != ewPtr) {
          sum = _mm_add_ps(sum,_mm_mul_ps(_mm_loadu_ps(wPtr),_mm_loadu_ps(dPtr)));
          wPtr += 4;
          dPtr += 4;
        }
      }
    }
    
    sum = _mm_add_ps(sum,_mm_shuffle_ps(sum,sum, _MM_SHUFFLE(2,3,0,1)));
    sum = _mm_add_ps(sum,_mm_shuffle_ps(sum,sum, _MM_SHUFFLE(1,0,3,2)));
    
    float ret = 0;
    _mm_store_ss(&ret,sum);
    
    UIntT remainder = n - quadLen;
    // Add in leftovers
    for(;remainder > 0;remainder--) {
      ret += *(wPtr++) * *(dPtr++);
    }
    return ret;
  }
  
  
  int VectorSSEInit() {
    if (SSE2() && 1) {
      g_DotProductD = &SSEDotProductD;
      g_DotProductF = &SSEDotProductF;
      cerr<<"SSE:yes\n";
    } else {
      cerr<<"SSE:no\n";
    }
    return 0;
  }
  
  static int a = VectorSSEInit();
  
}
