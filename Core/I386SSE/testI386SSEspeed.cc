
#include "Ravl/VectorUtils.hh"
#include "Ravl/Stream.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Array2d.hh"
#include "Ravl/OS/Date.hh"

int testConvolveKernelSpeed();

int main() {
  int ln;
  if((ln = testConvolveKernelSpeed()) != 0) {
    std::cerr << "Test failed on line " << ln << "\n";
    return ln;
  }
  std::cout << "Test passed ok. \n";
  return 0;
}


int testConvolveKernelSpeed() {
  int numIter = 250000;
  int matrRows = 512;
  std::cerr << "matrRows:" << matrRows << std::endl;
  int matrCols = 512;
  std::cerr << "matrCols:" << matrCols << std::endl;
  int kernRows = 256;
  std::cerr << "kernRows:" << kernRows << std::endl;
  for(int kernCols = 256; kernCols <= 256 + 48; kernCols += 16) {
    std::cerr << "kernCols:" << kernCols << std::endl;
    RavlN::Array2dC<float> matrix(matrRows,matrCols);
    RavlN::Array2dC<float> kernel(kernRows,kernCols);

    //create kernel
    for(int r = 0; r < kernRows; r++)
      for(int c = 0; c < kernCols; c++) {
        kernel[r][c] = (r-c) * (r-c);
      }

    //create matrix
    for(int r = 0; r < matrRows; r++)
      for(int c = 0; c < matrCols; c++) {
        matrix[r][c] = (r + c) / 2.;
      }

    int posRow = 16;
    //std::cerr << "posRow:" << posRow << std::endl;
    double totTime = 0;
    for(int posCol = 16; posCol <= 16; posCol += 1) {
      //std::cerr << "posCol:" << posCol << std::endl;

      float res;
      RavlN::DateC start = RavlN::DateC::NowLocal();
      for(int i = 0; i < numIter; i++) {
        RavlBaseVectorN::ConvolveKernel(&(matrix[posRow][posCol]), &(kernel[0][0]), kernRows, kernCols, matrCols*sizeof(float), &res);
      }
      double time = RavlN::DateC::NowLocal().Double() - start.Double();
      totTime += time;
      double numPixels = double(kernRows) * double(kernCols) * double(numIter);
      printf("time:%6.3f   iters:%3i   numPixels:%6lg  speed:%6.4f\n", float(time), numIter, numPixels, float(numPixels/1000000000./time));
    }
    if(totTime < 5)
      numIter *= 1.3;
    else if(totTime > 10)
      numIter /= 1.3;
  }
  return 0;
}
