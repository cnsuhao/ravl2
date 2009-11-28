#include "Ravl/VectorUtils.hh"
#include "Ravl/Stream.hh"

namespace RavlBaseVectorN {

  using namespace RavlN;
  
  static double BaseDotProductD(const double* v1, const double* v2, size_t size) {
    double sum = 0.0;
    const double* ptr1 = v1;
    const double* ptr2 = v2;
    for(unsigned int i=size; i>0; --i)
      sum += *ptr1++ * *ptr2++;
    return sum;  
  }

  static float BaseDotProductF(const float* v1, const float* v2, size_t size) {
    float sum = 0.0;
    const float* ptr1 = v1;
    const float* ptr2 = v2;
    for(unsigned int i=size; i>0; --i)
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
    while(wPtr != ewPtr) {
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
    while(wPtr != ewPtr) {
      const float val = *dPtr++;
      retVal += val * (*wPtr++ + *w2Ptr++ * val);
    }
    return retVal;
  }
  
  static void BaseReal2ByteD(unsigned char * byteData, const double *realData, size_t size) {
    for (int i=size; i>0; --i) {
      *(byteData++) = (*realData >= 255.0) ? 255 : (*realData<=0.0) ? 0 : ((unsigned char) (*realData + 0.5));
      realData++;
    }
  }
  
  static void BaseReal2ByteF(unsigned char * byteData, const float *realData, size_t size) {
    for (int i=size; i>0; --i) {
      *(byteData++) = (*realData >= 255.0) ? 255 : (*realData<=0.0) ? 0 : ((unsigned char) (*realData + 0.5));
      realData++;
    }
  }
  
  
  static void MatrixMulVectorF(const float *matrix, 
                               const float *vec, // Must be 'col' entries
                               UIntT rows,
                               UIntT cols,         
                               IntT stride,        // Stride of matrix.
                               float *result       // Must have 'rows' entries
                               ) 
  {
    RavlAssert(rows > 0);
    RavlAssert(cols > 0);
    const float *rowStart = matrix;
    for(unsigned int i = 0;i < rows;i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
      register float accum = rowStart[0]*vec[0];
      for(unsigned int j = 1;j < cols;j++)
        accum += rowStart[j]*vec[j];
      result[i] = accum;
    }
  }

  static void MatrixMulVectorD(const double *matrix, 
                               const double *vec, // Must be 'col' entries
                               UIntT rows,
                               UIntT cols,         
                               IntT stride,         // Stride of matrix.
                               double *result       // Must have 'rows' entries
                               ) 
  {
    RavlAssert(rows > 0);
    RavlAssert(cols > 0);
    const double *rowStart = matrix;
    for(unsigned int i = 0;i < rows;i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
      register double accum = rowStart[0]*vec[0];
      for(unsigned int j = 1;j < cols;j++)
        accum += rowStart[j]*vec[j];
      result[i] = accum;
    }
  }
  



  static void MatrixTMulVectorF(const float *matrix, 
                                const float *vec, // Must be 'col' entries
                                UIntT rows,
                                UIntT cols,         
                                IntT stride,        // Stride of matrix.
                                float *result       // Must have 'rows' entries
                                ) 
  {
    unsigned int i = 0;
    for(;i < cols;i++)
      result[i] = 0;
    const float *rowStart = matrix;
    for(i = 0;i < rows; i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
      const float dat = vec[i];
      for(unsigned int j = 0;j < cols;j++)
        result[j] += rowStart[j] * dat;
    }
  }
  
  static void MatrixTMulVectorD(const double *matrix, 
                                const double *vec, // Must be 'col' entries
                                UIntT rows,
                                UIntT cols,         
                                IntT stride,         // Stride of matrix.
                                double *result       // Must have 'rows' entries
                                ) 
  {
    unsigned int i = 0;
    for(;i < cols;i++)
      result[i] = 0;
    const double *rowStart = matrix;
    for(i = 0;i < rows; i++,rowStart = ShiftPointerInBytes(rowStart,stride)) {
      const double dat = vec[i];
      for(unsigned int j = 0;j < cols;j++)
        result[j] += rowStart[j] * dat;
    }
  }


  static void ConvolveKernelF(const float *matrix,const float *kernel,unsigned int rows,unsigned int cols,unsigned int matrixByteStride,float *result) {
    register float ret = 0;
    const float *vi = matrix;
    const float *vir = matrix;
    const float *vk = kernel;
    for(size_t i = 0;i < rows;i++) {
      for(size_t j = 0;j < cols;j++)
        ret += *(vk++) * vir[j];
      vi = ShiftPointerInBytes(vi,matrixByteStride);
    }
    *result = ret;
  }



  
  double (*g_DotProductD)(const double*, const double*, size_t) = &BaseDotProductD;
  float (*g_DotProductF)(const float*, const float*, size_t) = &BaseDotProductF;
  double (*g_QuadProductD)(const double*, const double*, const double*, size_t) = &BaseQuadProductD;
  float (*g_QuadProductF)(const float*, const float*, const float*, size_t) = &BaseQuadProductF;
  void (*g_Real2ByteD)(unsigned char*, const double*, size_t) = &BaseReal2ByteD;
  void (*g_Real2ByteF)(unsigned char*, const float*, size_t) = &BaseReal2ByteF;
  void (*g_MatrixMulVectorD)(const double *,const double *,UIntT ,UIntT ,IntT ,double *) = &MatrixMulVectorD;
  void (*g_MatrixMulVectorF)(const float *,const float *,UIntT ,UIntT ,IntT ,float *) = &MatrixMulVectorF;
  
  void (*g_MatrixTMulVectorD)(const double *,const double *,unsigned int ,unsigned int ,int ,double *) = &MatrixTMulVectorD;
  void (*g_MatrixTMulVectorF)(const float *,const float *,unsigned int ,unsigned int ,int ,float *) = &MatrixTMulVectorF;

  void (*g_ConvolveKernelF)(const float *matrix,const float *kernel,unsigned int rows,unsigned int cols,unsigned int matrixByteStride,float *result) = &ConvolveKernelF;

}
