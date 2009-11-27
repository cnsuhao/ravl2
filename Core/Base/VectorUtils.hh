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
  extern float (*g_QuadProductF)(const float*, const float*, const float*, size_t) ;
  extern void (*g_Real2ByteD)(unsigned char*, const double*, size_t) ;
  extern void (*g_Real2ByteF)(unsigned char*, const float*, size_t) ;
  
  extern void (*g_MatrixMulVectorD)(const double *matrix,const double *vector,unsigned int rows,unsigned int cols,int stride,double *result);
  extern void (*g_MatrixMulVectorF)(const float *matrix,const float *vector,unsigned int rows,unsigned int cols,int stride,float *result);
  extern void (*g_MatrixTMulVectorD)(const double *matrix,const double *vector,unsigned int rows,unsigned int cols,int stride,double *result);
  extern void (*g_MatrixTMulVectorF)(const float *matrix,const float *vector,unsigned int rows,unsigned int cols,int stride,float *result);
  
  extern void (*g_ConvolveKernelF)(const float *matrix,const float *kernel,unsigned int rows,unsigned int cols,unsigned int matrixByteStride,float *result);

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
  
  inline float QuadProduct(const float* v1, const float* v2, const float* v3, size_t size) 
  { return (*g_QuadProductF)(v1,v2,v3,size); }
  //: Fast double quadratic product, with optional hardware speedup
  // Performs: Sum over arrays of v1 * (v1 * v3 + v2)
  
  inline void Real2ByteD(unsigned char* byteData, const double* realData, size_t size)
  { return (*g_Real2ByteD)(byteData, realData, size); }
  //: Fast real to byte round and clip, with optional hardware speedup
  
  inline void Real2ByteF(unsigned char* byteData, const float* data, size_t size)
  { return (*g_Real2ByteF)(byteData, data, size); }
  //: Fast float to byte round and clip, with optional hardware speedup
  
  inline void MatrixMulVector(const float *matrix, 
                              const float *vector,
                              unsigned int rows,
                              unsigned int cols,         
                              int stride,        
                              float *result       
                              ) 
  { (*g_MatrixMulVectorF)(matrix,vector,rows,cols,stride,result); }
  //: Perform matrix vector multiplication
  //!param: matrix - 2d matrix, row major of size 'rows','cols'
  //!param: vector - column vector, must have at least 'cols' elements.
  //!param: rows - Number of rows in matrix 
  //!param: cols - Number of cols in matrix 
  //!param: stride - Stride of matrix, the number of elements in each row.
  //!param: result - Result vector, must have at least 'rows' elements
  // Performs:  result = matrix * vector, C=A * B
  // <code>
  // |A00 A01| B0  = | A00 * B0 + A01 * B1 |
  // |A10 A11| B1    | A10 * B0 + A11 * B1 |
  // </code>
  
  inline void MatrixMulVector(const double *matrix, 
                              const double *vector, 
                              unsigned int rows,
                              unsigned int cols,         
                              int stride,        
                              double *result       
                              ) 
  { (*g_MatrixMulVectorD)(matrix,vector,rows,cols,stride,result); }
  //: Perform matrix vector multiplication
  //!param: matrix - 2d matrix, row major of size 'rows','cols'
  //!param: vector - column vector, must have at least 'cols' elements.
  //!param: rows - Number of rows in matrix 
  //!param: cols - Number of cols in matrix 
  //!param: stride - Stride of matrix, the number of elements in each row.
  //!param: result - Result vector, must have at least 'rows' elements
  // Performs:  result = matrix * vector, C=A * B
  // <code>
  // |A00 A01| B0  = | A00 * B0 + A01 * B1 |
  // |A10 A11| B1    | A10 * B0 + A11 * B1 |
  // </code>
  
  inline void MatrixTMulVector(const float *matrix, 
                               const float *vector,
                               unsigned int rows,
                               unsigned int cols,         
                               int stride,        
                               float *result       
                               )
  { (*g_MatrixTMulVectorF)(matrix,vector,rows,cols,stride,result); }
  //: Perform transposed matrix vector multiplication
  //!param: matrix - 2d matrix, row major of size 'rows','cols'
  //!param: vector - column vector, must have at least 'cols' elements.
  //!param: rows - Number of rows in matrix 
  //!param: cols - Number of cols in matrix 
  //!param: stride - Stride of matrix, the number of elements in each row.
  //!param: result - Result vector, must have at least 'rows' elements
  // Performs:  result = matrix * vector, C=A*B
  // <code>
  // |A00 A01| B0  = | A00 * B0 + A10 * B1 |
  // |A10 A11| B1    | A01 * B0 + A11 * B1 |
  // </code>
  
  inline void MatrixTMulVector(const double *matrix, 
                               const double *vector, 
                               unsigned int rows,
                               unsigned int cols,         
                               int stride,        
                               double *result       
                               ) 
  { (*g_MatrixTMulVectorD)(matrix,vector,rows,cols,stride,result); }
  //: Perform  transposed matrix  vector multiplication
  //!param: matrix - 2d matrix, row major of size 'rows','cols'
  //!param: vector - column vector, must have at least 'cols' elements.
  //!param: rows - Number of rows in matrix 
  //!param: cols - Number of cols in matrix 
  //!param: stride - Stride of matrix, the number of elements in each row.
  //!param: result - Result vector, must have at least 'rows' elements
  // Performs:  result = matrix * vector,  C=A*B
  // <code>
  // |A00 A01| B0  = | A00 * B0 + A10 * B1 |
  // |A10 A11| B1    | A01 * B0 + A11 * B1 |
  // </code>

  inline void ConvolveKernel(const float *matrix,const float *kernel,unsigned int rows,unsigned int cols,unsigned int matrixByteStride,float *result)
  { (*g_ConvolveKernelF)(matrix,kernel,rows,cols,matrixByteStride,result); }
  //! Convolve kernel with a matrix.
  //!param: rows - Number of rows in the matrix and kernel
  //!param: cols - Number of cols

}

#endif
