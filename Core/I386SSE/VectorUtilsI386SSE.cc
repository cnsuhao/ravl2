#include "Ravl/VectorUtils.hh"
#include <emmintrin.h>
#include "Ravl/Stream.hh"
#include "Ravl/CPUID.hh"

namespace RavlBaseVectorN {
  
  using namespace RavlN;

  // FIXME:- In both these routines if vectors have the same alignment we could process 
  // the first few entries then process as aligned .
  
  static double SSEDotProductD(const double* v1, const double* v2, size_t size) {
    if(size < 12) {
      // For small vectors all the messing about is not worth it.
      double sum = 0.0;
      for(unsigned int i=size; i>0; --i)
        sum += *v1++ * *v2++;
      return sum;
    }
    const double* const ewPtr = v1 + (size & ~0x1);
    __m128d sum = _mm_setzero_pd();
    if((((unsigned long int) v1) & 0xf) == 0) {  // v1 16-byte aligned ?
      if((((unsigned long int) v2) & 0xf) == 0) {// v2 16-byte aligned ?
        while(v1 != ewPtr) {
          sum = _mm_add_pd(sum, _mm_mul_pd(_mm_load_pd(v2), _mm_load_pd(v1)));
          v2 += 2;
          v1 += 2;
        }
      }
      else {
        while(v1 != ewPtr) {
          sum = _mm_add_pd(sum, _mm_mul_pd(_mm_loadu_pd(v2), _mm_load_pd(v1)));
          v2 += 2;
          v1 += 2;
        }
      }
    }
    else {
      if((((unsigned long int) v2) & 0xf) == 0) {// v2 16-byte aligned ?
        while(v1 != ewPtr) {
          sum = _mm_add_pd(sum, _mm_mul_pd(_mm_load_pd(v2), _mm_loadu_pd(v1)));
          v2 += 2;
          v1 += 2;
        }
      }
      else {
        while(v1 != ewPtr) {
          sum = _mm_add_pd(sum, _mm_mul_pd(_mm_loadu_pd(v2), _mm_loadu_pd(v1)));
          v2 += 2;
          v1 += 2;
        }
      }
    }

    if(size & 1) { // Odd length ?
      sum = _mm_add_pd(sum, _mm_mul_sd(_mm_load_sd(v2++), _mm_load_sd(v1++)));
    }
    double tmp[2];
    _mm_storeu_pd(tmp, sum);
    return tmp[0] + tmp[1];
  }
  
  static float SSEDotProductF(const float *v1,const float *v2,size_t n) {
    if(n < 12) {
      // Not worth using this code for small vectors.
      float sum = 0;
      for(unsigned int i=n; i>0; --i)
        sum += *v1++ * *v2++;
      return sum;
    }
    UIntT quadLen = (n & ~0x3);
    const float* const ewPtr = v1 + quadLen;
    __m128 sum = _mm_setzero_ps ();
    
    
    if((((unsigned long int) v1) & 0xf) == 0) {  // v1 16-byte aligned ?
      if((((unsigned long int) v2) & 0xf) == 0) {// v2 16-byte aligned ?
        while(v1 != ewPtr) {
          sum = _mm_add_ps(sum,_mm_mul_ps(_mm_load_ps(v1),_mm_load_ps(v2)));
          v1 += 4;
          v2 += 4;
        }
      } else {
        while(v1 != ewPtr) {
          sum = _mm_add_ps(sum,_mm_mul_ps(_mm_load_ps(v1),_mm_loadu_ps(v2)));
          v1 += 4;
          v2 += 4;
        }
      }
    } else {
      if((((unsigned long int) v2) & 0xf) == 0) {// v2 16-byte aligned ?
        while(v1 != ewPtr) {
          sum = _mm_add_ps(sum,_mm_mul_ps(_mm_loadu_ps(v1),_mm_load_ps(v2)));
          v1 += 4;
          v2 += 4;
        }
      } else {
        while(v1 != ewPtr) {
          sum = _mm_add_ps(sum,_mm_mul_ps(_mm_loadu_ps(v1),_mm_loadu_ps(v2)));
          v1 += 4;
          v2 += 4;
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
      ret += *(v1++) * *(v2++);
    }
    return ret;
  }

  
  
  static double SSEQuadProductD(const double *data, 
				const double *weights1,
				const double *weights2, 
				size_t size) 
  {
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

  static float SSEQuadProductF(const float *data, 
			       const float *weights1,
			       const float *weights2, 
			       size_t size
			       ) 
  {
    const float* wPtr = weights1;
    const float* w2Ptr = weights2;
    const float* const ewPtr = weights1 + (size & ~0x3);
    const float* dPtr = data;
    __m128 sum = _mm_setzero_ps();
    
    if(((((unsigned long int) dPtr) & 0xf) == 0) && ((((unsigned long int) wPtr) & 0xf) == 0)  && ((((unsigned long int) w2Ptr) & 0xf) == 0))  { // Data 16-byte aligned ?
      while(wPtr != ewPtr) {
        const __m128 val = _mm_load_ps(dPtr);
        sum = _mm_add_ps(sum,
                         _mm_mul_ps(val,
                                    _mm_add_ps(_mm_mul_ps(val,
                                                          _mm_load_ps(w2Ptr)),
                                               _mm_load_ps(wPtr))));
        dPtr += 4;
        wPtr += 4;
        w2Ptr += 4;
      }
    }
    else {
      while(wPtr != ewPtr) {
        const __m128 val = _mm_loadu_ps(dPtr);
        sum = _mm_add_ps(sum,
                         _mm_mul_ps(val,
                                    _mm_add_ps(_mm_mul_ps(val,
                                                          _mm_loadu_ps(w2Ptr)),
                                               _mm_loadu_ps(wPtr))));
        dPtr += 4;
        wPtr += 4;
        w2Ptr += 4;
      }
    }
    
    if(size & 3) {// Odd length ?
      int c = size & 3;
      for(int i = 0; i< c;i++) {
	const __m128 val = _mm_load_ss(dPtr++);
	sum = _mm_add_ps(sum,
			 _mm_mul_ss(val,
				    _mm_add_ss(_mm_mul_ss(val,
							  _mm_load_ss(w2Ptr++)),
					       _mm_load_ss(wPtr++))));
      }
    }
    float tmp[4];
    _mm_storeu_ps(tmp, sum);
    return tmp[0] + tmp[1] + tmp[2]+ tmp[3];
  }
  
  
  static void SSEReal2ByteD(unsigned char * byteData, const double *realData, size_t size) {
    __m128d min = _mm_set1_pd (0);
    __m128d max = _mm_set1_pd (255);
    __m128d voff = _mm_set1_pd (0.5);
    unsigned char *ber = &(byteData[size&~1]);
    for(;byteData < ber;) {
      __m128i ivs = _mm_cvttpd_epi32(_mm_max_pd (_mm_min_pd (_mm_add_pd (_mm_loadu_pd (realData),voff),max),min));
      *(byteData++) = (ByteT) _mm_cvtsi128_si32 (ivs);
      *(byteData++) = (ByteT) _mm_cvtsi128_si32 ( _mm_shuffle_epi32(ivs,_MM_SHUFFLE (1,1,1,1)));
      realData += 2;
    }
    if(size & 1) {
      __m128i ivs = _mm_cvttpd_epi32(_mm_max_pd (_mm_min_pd (_mm_add_pd (_mm_load_sd (realData),voff),max),min));
      *byteData = (ByteT) _mm_cvtsi128_si32 (ivs);
    }
  }

  
  int VectorSSEInit() {
    if (SSE2() && 1) {
      g_DotProductD = &SSEDotProductD;
      g_DotProductF = &SSEDotProductF;
      g_QuadProductD = &SSEQuadProductD;
      g_QuadProductF = &SSEQuadProductF;
      g_Real2ByteD = &SSEReal2ByteD;
      //cerr<<"SSE:yes\n";
    } else {
      //cerr<<"SSE:no\n";
    }
    return 0;
  }
  
  static int a = VectorSSEInit();
  
}
