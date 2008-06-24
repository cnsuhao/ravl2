#include "Ravl/VectorUtils.hh"
#include <emmintrin.h>
#include "Ravl/Stream.hh"
#include "Ravl/CPUID.hh"

namespace RavlBaseVectorN {
  
  using namespace RavlN;

  // FIXME:- In both these routines if vectors have the same alignment we could process 
  // the first few entries then process as aligned .
  
  static double SSEDotProductD(const double* v1, const double* v2, size_t size) {
    const double* wPtr = v1;
    const double* dPtr = v2;
    if(size < 12) {
      // For small vectors all the messing about is not worth it.
      double sum = 0.0;
      for(unsigned int i=size; i>0; --i)
        sum += *wPtr++ * *dPtr++;
      return sum;
    }
    const double* const ewPtr = wPtr + (size & ~0x1);
    __m128d sum = _mm_setzero_pd();
    if((((unsigned long int) wPtr) & 0xf) == 0) {  // v1 16-byte aligned ?
      if((((unsigned long int) dPtr) & 0xf) == 0) {// v2 16-byte aligned ?
        while(wPtr != ewPtr) {
          sum = _mm_add_pd(sum, _mm_mul_pd(_mm_load_pd(dPtr), _mm_load_pd(wPtr)));
          dPtr += 2;
          wPtr += 2;
        }
      }
      else {
        while(wPtr != ewPtr) {
          sum = _mm_add_pd(sum, _mm_mul_pd(_mm_loadu_pd(dPtr), _mm_load_pd(wPtr)));
          dPtr += 2;
          wPtr += 2;
        }
      }
    }
    else {
      if((((unsigned long int) dPtr) & 0xf) == 0) {// v2 16-byte aligned ?
        while(wPtr != ewPtr) {
          sum = _mm_add_pd(sum, _mm_mul_pd(_mm_load_pd(dPtr), _mm_loadu_pd(wPtr)));
          dPtr += 2;
          wPtr += 2;
        }
      }
      else {
        while(wPtr != ewPtr) {
          sum = _mm_add_pd(sum, _mm_mul_pd(_mm_loadu_pd(dPtr), _mm_loadu_pd(wPtr)));
          dPtr += 2;
          wPtr += 2;
        }
      }
    }

    if(size & 1) { // Odd length ?
      sum = _mm_add_pd(sum, _mm_mul_sd(_mm_load_sd(dPtr++), _mm_load_sd(wPtr++)));
    }
    double tmp[2];
    _mm_storeu_pd(tmp, sum);
    return tmp[0] + tmp[1];
  }
  
  static float SSEDotProductF(const float *v1,const float *v2,size_t n) {
    const float* wPtr = v1;
    const float* dPtr = v2;
    if(n < 12) {
      // Not worth using this code for small vectors.
      float sum = 0;
      for(unsigned int i=n; i>0; --i)
        sum += *wPtr++ * *dPtr++;
      return sum;
    }
    UIntT quadLen = (n & ~0x3);
    const float* const ewPtr = wPtr + quadLen;
    __m128 sum = _mm_setzero_ps ();
    
    
    if((((unsigned long int) wPtr) & 0xf) == 0) {  // v1 16-byte aligned ?
      if((((unsigned long int) dPtr) & 0xf) == 0) {// v2 16-byte aligned ?
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
      if((((unsigned long int) dPtr) & 0xf) == 0) {// v2 16-byte aligned ?
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

  
  
  static double SSEQuadProductD(const double *data, const double *weights1,
                            const double *weights2, size_t size) {
    const double* wPtr = weights1;
    const double* w2Ptr = weights2;
    const double* const ewPtr = weights1 + (size & ~0x1);
    const double* dPtr = data;
    __m128d sum = _mm_setzero_pd();
    if(((((unsigned long int) dPtr) & 0xf) == 0) && ((((unsigned long int) wPtr) & 0xf) == 0)  && ((((unsigned long int) w2Ptr) & 0xf) == 0))  { // Data 16-byte aligned ?
      while(wPtr != ewPtr) {
        const __m128d val = _mm_load_pd(dPtr);
        sum = _mm_add_pd(sum,
                         _mm_mul_pd(val,
                                    _mm_add_pd(_mm_mul_pd(val,
                                                          _mm_load_pd(w2Ptr)),
                                               _mm_load_pd(wPtr))));
        dPtr += 2;
        wPtr += 2;
        w2Ptr += 2;
      }
    }
    else {
      while(wPtr != ewPtr) {
        const __m128d val = _mm_loadu_pd(dPtr);
        sum = _mm_add_pd(sum,
                         _mm_mul_pd(val,
                                    _mm_add_pd(_mm_mul_pd(val,
                                                          _mm_loadu_pd(w2Ptr)),
                                               _mm_loadu_pd(wPtr))));
        dPtr += 2;
        wPtr += 2;
        w2Ptr += 2;
      }
    }
    
    if(size & 1) // Odd length ?
      {
        const __m128d val = _mm_load_sd(dPtr++);
        sum = _mm_add_pd(sum,
                         _mm_mul_sd(val,
                                    _mm_add_sd(_mm_mul_sd(val,
                                                          _mm_load_sd(w2Ptr++)),
                                               _mm_load_sd(wPtr++))));
      }
    double tmp[2];
    _mm_storeu_pd(tmp, sum);
    return tmp[0] + tmp[1];
  }
  
  
  
  int VectorSSEInit() {
    if (SSE2() && 1) {
      g_DotProductD = &SSEDotProductD;
      g_DotProductF = &SSEDotProductF;
      g_QuadProductD = & SSEQuadProductD;
      //cerr<<"SSE:yes\n";
    } else {
      //cerr<<"SSE:no\n";
    }
    return 0;
  }
  
  static int a = VectorSSEInit();
  
}
