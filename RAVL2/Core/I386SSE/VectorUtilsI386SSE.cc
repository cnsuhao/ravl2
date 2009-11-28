#include "Ravl/VectorUtils.hh"
#include <emmintrin.h>
#include "Ravl/Stream.hh"
#include "Ravl/CPUID.hh"

namespace RavlBaseVectorN {
  
  using namespace RavlN;
  
  template<typename DataT>
  static inline bool Is16ByteAligned(const DataT *data) 
  { return (((unsigned long int) data) & 0xf) == 0; }
  
  // FIXME:- In both these routines if vectors have the same alignment we could process 
  // the first few entries then process as aligned .
  
  static double SSEDotProductD(const double* v1, const double* v2, size_t size) {
    register double dsum = 0.0;
    if(size < 8) {
      // For small vectors all the messing about is not worth it.
      for(unsigned int i=size; i>0; --i)
        dsum += *v1++ * *v2++;
      return dsum;
    }
    const double* const ewPtr = v1 + (size & ~0x1);
    __m128d sum = _mm_setzero_pd();
    if(Is16ByteAligned(v1)) {  // v1 16-byte aligned ?
      if(Is16ByteAligned(v2)) {// v2 16-byte aligned ?
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
      if(Is16ByteAligned(v2)) {// v2 16-byte aligned ?
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
    // Sum the two accumulators together.
    sum = _mm_add_sd(sum,_mm_shuffle_pd(sum,sum,_MM_SHUFFLE2(0,1)));
    _mm_store_sd(&dsum, sum);
    return dsum;
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
    
    
    if(Is16ByteAligned(v1)) {  // v1 16-byte aligned ?
      if(Is16ByteAligned(v2)) {// v2 16-byte aligned ?
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
      if(Is16ByteAligned(v2)) {// v2 16-byte aligned ?
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
    if(Is16ByteAligned(dPtr) && Is16ByteAligned(wPtr) && Is16ByteAligned(w2Ptr))  { // Data 16-byte aligned ?
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
    
    if(size & 1) { // Odd length ?
      const __m128d val = _mm_load_sd(dPtr++);
      sum = _mm_add_pd(sum,
                       _mm_mul_sd(val,
                                  _mm_add_sd(_mm_mul_sd(val,
                                                        _mm_load_sd(w2Ptr++)),
                                             _mm_load_sd(wPtr++))));
    }
    
    double dsum;
    sum = _mm_add_sd(sum,_mm_shuffle_pd(sum,sum,_MM_SHUFFLE2(0,1)));
    _mm_store_sd(&dsum, sum);
    return dsum;
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
    
    if(Is16ByteAligned(wPtr)  && Is16ByteAligned(w2Ptr)) {
      if(Is16ByteAligned(dPtr))  { // Data 16-byte aligned ?
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
      } else {
        while(wPtr != ewPtr) {
          const __m128 val = _mm_loadu_ps(dPtr);
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

    sum = _mm_add_ps(sum,_mm_shuffle_ps(sum,sum, _MM_SHUFFLE(2,3,0,1)));
    sum = _mm_add_ps(sum,_mm_shuffle_ps(sum,sum, _MM_SHUFFLE(1,0,3,2)));
    
    float ret = 0;
    _mm_store_ss(&ret,sum);
    return ret;
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
  
  static void SSEMatrixMulVectorD(const double *matrix, 
                                  const double *vec, // Must be 'col' entries
                                  UIntT rows,
                                  UIntT cols,         
                                  IntT stride,        // Stride of matrix, number of elements in a row
                                  double *result       // Must have 'rows' entries
                                  ) 
  {
    if(rows == 1) {
      *result = SSEDotProductD(matrix,vec,cols);
      return ;
    }
    const double *rowStart = matrix;
    double *resultAt = result;
    if(cols < 12) {
      for(unsigned int i = 0;i < rows;i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
        register double accum = rowStart[0]*vec[0];
        for(unsigned int j = 1;j < cols;j++)
          accum += rowStart[j]*vec[j];
        *(resultAt++) = accum;
      }
      return ;
    }
    if((Is16ByteAligned(matrix) && Is16ByteAligned(vec) && ((stride % 16) == 0))) {
      if((cols & 1) == 0) {
        for(unsigned int i = 0;i < rows;i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
          register const double *rowAt = rowStart;
          register const double *vecAt = vec;
          register __m128d accum =  _mm_mul_pd(_mm_load_pd(rowAt),_mm_load_pd(vecAt));
          for(unsigned int j = 2;j < cols;j += 2) {
            rowAt += 2;
            vecAt += 2;
            accum = _mm_add_pd(accum,_mm_mul_pd(_mm_load_pd(rowAt),_mm_load_pd(vecAt)));
          }
          // Add two accumulators together
          accum = _mm_add_sd(accum,_mm_shuffle_pd(accum,accum,_MM_SHUFFLE2(0,1)));
          _mm_store_sd(resultAt++,accum);
        }
      } else {
        UIntT fastCols = (cols & ~0x1);
        for(unsigned int i = 0;i < rows;i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
          register const double *rowAt = rowStart;
          register const double *vecAt = vec;
          register __m128d accum =  _mm_mul_pd(_mm_load_pd(rowAt),_mm_load_pd(vecAt));
          for(unsigned int j = 2;j < fastCols;j += 2) {
            rowAt += 2;
            vecAt += 2;
            accum = _mm_add_pd(accum,_mm_mul_pd(_mm_load_pd(rowAt),_mm_load_pd(vecAt)));
          }
          rowAt += 2;
          vecAt += 2;
          accum = _mm_add_pd(accum,_mm_mul_sd(_mm_load_sd(rowAt),_mm_load_sd(vecAt)));
          // Add two accumulators together
          accum = _mm_add_sd(accum,_mm_shuffle_pd(accum,accum,_MM_SHUFFLE2(0,1)));
          _mm_store_sd(resultAt++,accum);
        }        
      }
    } else {
      if((cols & 1) == 0) {
        for(unsigned int i = 0;i < rows;i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
          register const double *rowAt = rowStart;
          register const double *vecAt = vec;
          register __m128d accum = _mm_mul_pd(_mm_loadu_pd(rowAt),_mm_loadu_pd(vecAt));
          for(unsigned int j = 2;j < cols;j += 2) {
            rowAt += 2;
            vecAt += 2;
            accum = _mm_add_pd(accum,_mm_mul_pd(_mm_loadu_pd(rowAt),_mm_loadu_pd(vecAt)));
          }
          // Add two accumulators together
          accum = _mm_add_sd(accum,_mm_shuffle_pd(accum,accum,_MM_SHUFFLE2(0,1)));
          _mm_store_sd(resultAt++,accum);
        }
      } else {
        UIntT fastCols = (cols & ~0x1);
        for(unsigned int i = 0;i < rows;i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
          register const double *rowAt = rowStart;
          register const double *vecAt = vec;
          register __m128d accum = _mm_mul_pd(_mm_loadu_pd(rowAt),_mm_loadu_pd(vecAt));
          for(unsigned int j = 2;j < fastCols;j += 2) {
            rowAt += 2;
            vecAt += 2;
            accum = _mm_add_pd(accum,_mm_mul_pd(_mm_loadu_pd(rowAt),_mm_loadu_pd(vecAt)));
          }
          rowAt += 2;
          vecAt += 2;
          accum = _mm_add_pd(accum,_mm_mul_sd(_mm_load_sd(rowAt),_mm_load_sd(vecAt)));
          // Add two accumulators together
          accum = _mm_add_sd(accum,_mm_shuffle_pd(accum,accum,_MM_SHUFFLE2(0,1)));
          _mm_store_sd(resultAt++,accum);
          
        }        
      }
    }
    
  }
  
  static void SSEMatrixMulVectorF(const float *matrix, 
                                  const float *vec, // Must be 'col' entries
                                  UIntT rows,
                                  UIntT cols,         
                                  IntT stride,        // Stride of matrix, number of elements in a row
                                  float *result       // Must have 'rows' entries
                                  ) 
  {
    if(rows == 1) {
      *result = SSEDotProductF(matrix,vec,cols);
      return ;
    }
    //std::cerr << "Rows=" << rows << " Cols=" << cols << " Stride=" << stride <<"\n";
    if(cols < 8 || 1) { // || !(Is16ByteAligned(matrix) && Is16ByteAligned(vec) && ((stride % 16) == 0))
      const float *rowStart = matrix;
      for(unsigned int i = 0;i < rows;i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
        register float accum = rowStart[0]*vec[0];
        for(unsigned int j = 1;j < cols;j++)
          accum += rowStart[j]*vec[j];
        result[i] = accum;
      }
      return ;      
    }
    float *resultAt = result;
    const float *rowStart = matrix;
    if(Is16ByteAligned(matrix) && Is16ByteAligned(vec) && ((stride % 16) == 0)) {
      // Everything is aligned
      UIntT fastCols = (cols & ~0x3);
      //std::cerr << " A fastCols=" << fastCols << " Rem=" << (cols % 4)  <<"\n";
      if((cols % 4) == 0) {
        for(unsigned int i = 0;i < rows;i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
          register const float *rowAt = rowStart;
          register const float *vecAt = vec;
          register __m128 accum =  _mm_mul_ps(_mm_load_ps(rowAt),_mm_load_ps(vecAt));
          for(unsigned int j = 4;j < cols;j += 4) {
            rowAt += 4;
            vecAt += 4;
            accum = _mm_add_ps(accum,_mm_mul_ps(_mm_load_ps(rowAt),_mm_load_ps(vecAt)));
          }
          accum = _mm_add_ps(accum,_mm_shuffle_ps(accum,accum, _MM_SHUFFLE(2,3,0,1)));
          accum = _mm_add_ps(accum,_mm_shuffle_ps(accum,accum, _MM_SHUFFLE(1,0,3,2)));
          _mm_store_ss(resultAt++,accum);
        }
      } else {
        for(unsigned int i = 0;i < rows;i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
          register const float *rowAt = rowStart;
          register const float *vecAt = vec;
          register __m128 accum =  _mm_mul_ps(_mm_load_ps(rowAt),_mm_load_ps(vecAt));
          unsigned int j;
          for(j = 4;j < fastCols;j += 4) {
            rowAt += 4;
            vecAt += 4;
            accum = _mm_add_ps(accum,_mm_mul_ps(_mm_load_ps(rowAt),_mm_load_ps(vecAt)));
          }
          // Finish off row
          rowAt += 4;
          vecAt += 4;
          for(;j < cols;j++) {
            accum = _mm_add_ps(accum,_mm_mul_ss(_mm_load_ss(rowAt++),_mm_load_ss(vecAt++)));            
          }
          accum = _mm_add_ps(accum,_mm_shuffle_ps(accum,accum, _MM_SHUFFLE(2,3,0,1)));
          accum = _mm_add_ps(accum,_mm_shuffle_ps(accum,accum, _MM_SHUFFLE(1,0,3,2)));
          _mm_store_ss(resultAt++,accum);
        }     
      }
        
    } else {
      // 
      if((cols % 4) == 0) {
        //std::cerr << " B fastCols=" << fastCols << " cols=" << cols << " Rem=" << (cols % 4)  <<"\n";
        // Unaligned with no extra columns
        for(unsigned int i = 0;i < rows;i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
          register const float *rowAt = rowStart;
          register const float *vecAt = vec;
          register __m128 accum =  _mm_mul_ps(_mm_loadu_ps(rowAt),_mm_loadu_ps(vecAt));
          unsigned int j;
          for(j = 4;j < cols;j += 4) {
            rowAt += 4;
            vecAt += 4;
            accum = _mm_add_ps(accum,_mm_mul_ps(_mm_loadu_ps(rowAt),_mm_loadu_ps(vecAt)));
          }
          accum = _mm_add_ps(accum,_mm_shuffle_ps(accum,accum, _MM_SHUFFLE(2,3,0,1)));
          accum = _mm_add_ps(accum,_mm_shuffle_ps(accum,accum, _MM_SHUFFLE(1,0,3,2)));
          _mm_store_ss(resultAt++, accum);
        }
      } else {
        //std::cerr << " C fall back.\n";
        // Unaligned with extra columns
        UIntT fastCols = (cols & ~0x3);
        for(unsigned int i = 0;i < rows;i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
          register const float *rowAt = rowStart;
          register const float *vecAt = vec;
          register __m128 accum =  _mm_mul_ps(_mm_loadu_ps(rowAt),_mm_loadu_ps(vecAt));
          unsigned int j;
          for(j = 4;j < fastCols;j += 4) {
            rowAt += 4;
            vecAt += 4;
            accum = _mm_add_ps(accum,_mm_mul_ps(_mm_loadu_ps(rowAt),_mm_loadu_ps(vecAt)));
          }
          // Finish off row
          rowAt += 4;
          vecAt += 4;
          for(;j < cols;j++) {
            accum = _mm_add_ps(accum,_mm_mul_ss(_mm_load_ss(rowAt++),_mm_load_ss(vecAt++)));            
          }
          accum = _mm_add_ps(accum,_mm_shuffle_ps(accum,accum, _MM_SHUFFLE(2,3,0,1)));
          accum = _mm_add_ps(accum,_mm_shuffle_ps(accum,accum, _MM_SHUFFLE(1,0,3,2)));
          _mm_store_ss(resultAt++, accum);
        }
      }
    }
  }
  
  void SSEConvolveKernelSSE(const float *vk, // Kernel, expected to be aligned.
                               const float *vi, // Scanned image, probably not aligned.
                               size_t rows,
                               size_t cols,
                               size_t byteStride,
                               float *result
                               )
  {
    //std::cerr << "Rows=" << rows << " Cols=" << cols << " vk=" << std::hex << (void*) vk << " vi=" << (void*) vi << " Stride=" << byteStride << std::dec <<"\n";
    __m128 sum = _mm_setzero_ps ();

    if(Is16ByteAligned(vk)) {
      // Kernel is byte aligned.
      for(size_t i = 0;i < rows;i++) {
        const float *vir = vi; // Image row.
        if(Is16ByteAligned(vir)) {
          for(size_t j = 0;j < cols;j+=4) {
            sum = _mm_add_ps(sum,_mm_mul_ps(_mm_load_ps(vk),_mm_load_ps(vir)));
            vk += 4;
            vir += 4;
          }
        } else {
          size_t j = 0;
          for(;j < cols;j+=4) {
            sum = _mm_add_ps(sum,_mm_mul_ps(_mm_load_ps(vk),_mm_loadu_ps(vir)));
            vk += 4;
            vir += 4;
          }
        }
        // Add stride bytes.
        vi = reinterpret_cast<const float *>(reinterpret_cast<const char *>(vi) + byteStride);
      }
    } else {
      // Kernel is not byte aligned.
      for(size_t i = 0;i < rows;i++) {
        const float *vir = vi; // Image row.
        if(Is16ByteAligned(vir)) {
          for(size_t j = 0;j < cols;j+=4) {
            sum = _mm_add_ps(sum,_mm_mul_ps(_mm_loadu_ps(vk),_mm_load_ps(vir)));
            vk += 4;
            vir += 4;
          }
        } else {
          size_t j = 0;
          for(;j < cols;j+=4) {
            sum = _mm_add_ps(sum,_mm_mul_ps(_mm_loadu_ps(vk),_mm_loadu_ps(vir)));
            vk += 4;
            vir += 4;
          }
        }
        // Add stride bytes.
        vi = reinterpret_cast<const float *>(reinterpret_cast<const char *>(vi) + byteStride);
      }
    }

    sum = _mm_add_ps(sum,_mm_shuffle_ps(sum,sum, _MM_SHUFFLE(2,3,0,1)));
    sum = _mm_add_ps(sum,_mm_shuffle_ps(sum,sum, _MM_SHUFFLE(1,0,3,2)));

    _mm_store_ss(result,sum);
  }


  
  int VectorSSEInit() {
    if (SSE2() && 1) {
      g_DotProductD = &SSEDotProductD;
      g_DotProductF = &SSEDotProductF;
      g_QuadProductD = &SSEQuadProductD;
      g_QuadProductF = &SSEQuadProductF;
      g_MatrixMulVectorF = &SSEMatrixMulVectorF;
      g_MatrixMulVectorD = &SSEMatrixMulVectorD;
      g_Real2ByteD = &SSEReal2ByteD;
      //cerr<<"SSE:yes\n";
    } else {
      //cerr<<"SSE:no\n";
    }
    return 0;
  }
  
  static int a = VectorSSEInit();
  
}
