
#include "Ravl/Image/Convolve2d.hh"
#include "Ravl/Image/ConvolveHorz2d.hh"
#include "Ravl/Image/ConvolveVert2d.hh"
#include "Ravl/Image/ConvolveSeparable2d.hh"

using namespace RavlImageN;

int testConvolve2d();
int testConvolveHorz2d();
int testConvolveVert2d();
int testConvolveSeparable2d();

int main() {
  int ln;
  if((ln = testConvolve2d()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testConvolveHorz2d()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testConvolveVert2d()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testConvolveSeparable2d()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}

int testConvolve2d() {
  cerr << "testConvolve2d(), Started... \n";
  ImageC<IntT> kernel(IndexRangeC(-1,1),IndexRangeC(-1,1));
  kernel.Fill(0);
  kernel[0][0] = 2;
  kernel[0][1] = -1;
  kernel[1][0] = -1;
  kernel[0][-1] = 1;
  kernel[-1][0] = 1;
  Convolve2dC<IntT> conv(kernel);
  ImageC<IntT> test(10,10);
  test.Fill(0);
  test[3][5] = 1;
  test[6][3] = 1;
  ImageC<IntT> res;
  conv.Apply(test,res);
  //cout << res;
  IntT sum = 0;
  for(Array2dIterC<IntT> it(res);it;it++)
    sum += *it;
  if(sum != 4) return __LINE__;
  // Check a few values....
  if(res[3][5] != 2) return __LINE__;
  if(res[6][3] != 2) return __LINE__;
  if(res[2][5] != 1) return __LINE__;
  if(res[2][4] != 0) return __LINE__;
  return 0;
}


int testConvolveHorz2d() {
  cerr << "testConvolveHorz2d(), Started... \n";
  Array1dC<IntT> filt(-1,1);
  filt[-1] = 1;
  filt[0] = 2;
  filt[1] = -1;
  ConvolveHorz2dC<IntT> conv(filt);
  ImageC<IntT> test(10,10);
  test.Fill(0);
  test[3][5] = 1;
  test[6][3] = 1;
  //cout << test;
  ImageC<IntT> res;
  conv.Apply(test,res);
  //cout << res;
  IntT sum = 0;
  for(Array2dIterC<IntT> it(res);it;it++)
    sum += *it;
  if(sum != 4) return __LINE__;
  if(res[3][5] != 2) return __LINE__;
  if(res[6][3] != 2) return __LINE__;
  if(res[7][3] != 0) return __LINE__;
  return 0;
}

int testConvolveVert2d() {
  cerr << "testConvolveVert2d(), Started... \n";
  Array1dC<IntT> filt(-1,1);
  filt[-1] = 1;
  filt[0] = 2;
  filt[1] = -1;
  ConvolveVert2dC<IntT> conv(filt);
  ImageC<IntT> test(10,10);
  test.Fill(0);
  test[3][5] = 1;
  test[6][3] = 1;
  //cout << test;
  ImageC<IntT> res;
  conv.Apply(test,res);
  //cout << res;
  IntT sum = 0;
  for(Array2dIterC<IntT> it(res);it;it++)
    sum += *it;
  if(sum != 4) return __LINE__;
  if(res[3][5] != 2) return __LINE__;
  if(res[6][3] != 2) return __LINE__;
  if(res[6][4] != 0) return __LINE__;
  return 0;
}

int testConvolveSeparable2d() {
  cerr << "testConvolveSeparable2d(), Started... \n";
  Array1dC<IntT> filt(-1,1);
  filt[-1] = 1;
  filt[0] = 2;
  filt[1] = -1;
  ConvolveSeparable2dC<IntT> conv(filt,filt);
  ImageC<IntT> test(10,10);
  test.Fill(0);
  test[3][5] = 1;
  test[6][3] = 1;
  //cout << test;
  ImageC<IntT> res;
  conv.Apply(test,res);
  //cout << res;
  IntT sum = 0;
  for(Array2dIterC<IntT> it(res);it;it++)
    sum += *it;
  if(sum != 8) return __LINE__;
  if(res[3][5] != 4) return __LINE__;
  if(res[6][3] != 4) return __LINE__;
  if(res[6][4] != 2) return __LINE__;
  return 0;
}
