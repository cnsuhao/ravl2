
#include "Ravl/VectorUtils.hh"
#include "Ravl/Stream.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Array2d.hh"

template<class DataT> int TestDot();
template<class DataT> int TestQuad();
template<class DataT> int TestMatMulVec();

int main() {
  int ln;
  if((ln = TestDot<float>()) != 0) {
    std::cerr << "Test failed on line " << ln << "\n";
    return ln;
    }
  if((ln = TestDot<double>()) != 0) {
    std::cerr << "Test failed on line " << ln << "\n";
    return ln;
  }
  if((ln = TestQuad<double>()) != 0) {
    std::cerr << "Test failed on line " << ln << "\n";
    return ln;
  }
  if((ln = TestQuad<float>()) != 0) {
    std::cerr << "Test failed on line " << ln << "\n";
    return ln;
  }
  if((ln = TestMatMulVec<float>()) != 0) {
    std::cerr << "Test failed on line " << ln << "\n";
    return ln;
  }
  if((ln = TestMatMulVec<double>()) != 0) {
    std::cerr << "Test failed on line " << ln << "\n";
    return ln;
  }
  std::cout << "Test passed ok. \n";
  return 0;
}

template<class DataT>
int TestDot() {
  RavlN::SArray1dC<DataT> data(32);
  for(int i = 0;i < 32;i++)
    data[i] = i;
  
  for(int l = 0;l <= 16;l++) {
    for(int i = 0;i < 16;i++) {
      for(int j = 0;j < 16;j++) {
        // Compute true answer
        DataT trueProduct = 0;
        for(int k = 0;k < l;k++)
          trueProduct += data[k+i] * data[k+j];
        // Compute dot product.
        DataT dp = RavlBaseVectorN::DotProduct(&data[i],&data[j],l);
        DataT diff = trueProduct - dp;
        if(RavlN::Abs(diff) > 1e-12) {
          std::cerr << "Failed l=" << l << " i=" << i << " j=" << j << " True=" << trueProduct << " Sum=" << dp << "\n";
          return __LINE__;
        }
      }
    }
  }
  return 0;
  
}

template<class DataT>
int TestQuad() {
  RavlN::SArray1dC<DataT> data(32);
  for(int i = 0;i < 32;i++)
    data[i] = i;
  
  for(int l = 0;l <= 16;l++) {
    for(int i = 0;i < 16;i++) {
      for(int j = 0;j < 16;j++) {
        for(int j2 = 0;j2 < 16;j2++) {
          // Compute true answer
          DataT trueDotAndResult = 0;
          for(int k = 0;k < l;k++)
            trueDotAndResult += data[k+i] * (data[k+j] + data[k+j2]*data[k+i]);
          // Compute dot and add.
          DataT qp = RavlBaseVectorN::QuadProduct(&data[i],&data[j],&data[j2],l);
          DataT diff = trueDotAndResult - qp;
          if(RavlN::Abs(diff) > 1e-12) {
            std::cerr << "Failed l=" << l << " i=" << i << " j=" << j << " j2=" << j2 << " True=" << trueDotAndResult << " Sum=" << qp << " Diff= " << diff << "\n";
            return __LINE__;
          }
        }
      }
    }
  }
  return 0;
  
}

template<typename DataT>
void RefMatrixMulVector(const DataT *matrix, 
                        const DataT *vec, // Must be 'col' entries
                        unsigned int rows,
                        unsigned int cols,         
                        int stride,         // Stride of matrix.
                        DataT *result       // Must have 'rows' entries
                        ) 
{
  RavlAssert(rows > 0);
  RavlAssert(cols > 0);
  const DataT *rowStart = matrix;
  for(unsigned int i = 0;i < rows;i++,rowStart = RavlN::ShiftPointerInBytes(rowStart,stride)) {
    register DataT accum = rowStart[0]*vec[0];
    for(unsigned int j = 1;j < cols;j++)
      accum += rowStart[j]*vec[j];
    result[i] = accum;
  }
}


template<class DataT> 
int TestMatMulVec() {
  
  RavlN::SArray1dC<DataT> vec(128);
  for(unsigned int i = 0;i < vec.Size();i++)
    vec[i] = i+1;
  RavlN::SArray1dC<DataT> refResult(128);
  RavlN::SArray1dC<DataT> testResult(128);
  
  // Change matrix sizes.
  for(int n = 1;n < 32;n += 3) {
    for(int m = 1;m < 32;m += 3) {
      RavlN::Array2dC<DataT> mat(n,m);
      for(int i = 0;i < n;i++)
        for(int j = 0;j < m;j++) 
          mat[i][j] = i % 5 + j % 11 + 1;
      
      // Matrix Start offsets.
      for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
          
          // Vector start offsets.
          for(int k = 0;k < 5;k++) {
            for(int q = 0;q < 5;q++) {
              int rows = n-i;
              int cols = m-j;
              RavlAssert(rows > 0 && cols > 0);
              RefMatrixMulVector(&(mat[i][j]),&vec[k],rows,cols,mat.ByteStride(),&(refResult[q]));
              RavlBaseVectorN::MatrixMulVector(&(mat[i][j]),&vec[k],rows,cols,mat.ByteStride(),&(testResult[q]));
              //RefMatrixMulVector(&(mat[i][j]),&vec[k],rows,cols,mat.ByteStride(),&(testResult[q]));
              for(int r = 0;r < rows;r++) {
                if(RavlN::Abs(testResult[q+r] - refResult[q+r]) > 0.0001) {
                  std::cerr << "Test failed. Index=" << r<< " Res=" << testResult[q+r] << " Expected=" << refResult[q+r] << " Rows=" << rows << " Cols=" << cols << "\n";
                  std::cerr << "n=" << n << " m=" << m << " i=" << i << " j=" << j << " k=" << k << " q=" << q <<"\n";
                  RavlAssert(0);
                  return __LINE__;
                }
              }
              //std::cerr << ".";
            }
          }
        }
      }
      
      //std::cerr << ".";
    }
  }
  
  return 0;
}
