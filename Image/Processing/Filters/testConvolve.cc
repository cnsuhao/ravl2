// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Filters/testConvolve.cc"

#include "Ravl/Image/Convolve2d.hh"
#include "Ravl/Image/ConvolveHorz2d.hh"
#include "Ravl/Image/ConvolveVert2d.hh"
#include "Ravl/Image/ConvolveSeparable2d.hh"
#include "Ravl/Image/BilinearInterpolation.hh"
#include "Ravl/Image/HistogramEqualise.hh"
#include "Ravl/Image/Matching.hh"
#include "Ravl/Image/ByteRGBValue.hh"

using namespace RavlImageN;

#define TESTMMX 0

int testConvolve2d();
int testConvolveHorz2d();
int testConvolveVert2d();
int testConvolveSeparable2d();
int testConvolve2dMMX();

int testBilinearInterpolation();
int testHistogramEqualise();
int testMatching();

#ifndef __sgi__
template BilinearInterpolationC<ByteRGBValueC,ByteRGBValueC>;
#endif

int main() {
  int ln;
#if !TESTMMX
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
#endif
  if((ln = testConvolve2dMMX()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testBilinearInterpolation()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testHistogramEqualise()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testMatching()) != 0) {
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
  if(res[6][4] != -2) return __LINE__;
  return 0;
}

int testConvolve2dMMX() {
  cerr <<"testConvolve2dMMX(), Started. \n";
  ImageC<short> kernel(IndexRangeC(-2,2),IndexRangeC(-2,2));
  kernel.Fill(0);
  kernel[0][0] = 2;
  kernel[0][1] = -1;
  kernel[1][0] = -1;
  kernel[0][-1] = 1;
  kernel[-1][0] = 1;
  Convolve2dC<short,short,short,short> conv(kernel);
  ImageC<short> test(200,200);
  test.Fill(0);
  test[3][5] = 1;
  test[6][3] = 1;
  ImageC<short> res;
  for(int i = 0;i < 100;i++) {
    conv.Apply(test,res);
    //cout << res;
  }
#if 0
  IntT sum = 0;
  for(Array2dIterC<short> it(res);it;it++)
    sum += *it;
  if(sum != 4) return __LINE__;
  // Check a few values....
  if(res[3][5] != 2) return __LINE__;
  if(res[6][3] != 2) return __LINE__;
  if(res[2][5] != 1) return __LINE__;
  if(res[2][4] != 0) return __LINE__;
  return 0;
#endif
  
  return 0;
}


// Tag this on the end for the moment.

int testBilinearInterpolation() {
  cerr << "testBilinearInterpolation(), Started... \n";
  ImageC<IntT> test(10,10);
  IntT i = 0;
  for(Array2dIterC<IntT> it(test);it;it++)
    *it = i++;
  //cerr << test << "\n";
  ImageRectangleC resRect(0,19,0,19);
  BilinearInterpolationC<IntT,IntT> xyz(resRect);
  ImageC<IntT> res = xyz.Apply(test);
  if(res.Rectangle() != resRect) return __LINE__;
  //cerr << res << "\n";
  if(res[resRect.Origin()] != 0) return __LINE__;
  
  // Do some more checking here.
  return 0;
}

#ifndef __sgi__
template HistogramEqualiseC<RealT>;
template HistogramEqualiseC<ByteT>;
#endif

int testHistogramEqualise() {
  ImageC<RealT> test(10,10);
  RealT v = 0;
  for(Array2dIterC<RealT> it(test);it;it++)
    *it = v++;
  HistogramEqualiseC<RealT> histEqual(0,100);
  ImageC<RealT> result = histEqual.Apply(test);
  //cerr << "Test=" << test << "\n Result=" << result << "\n";
  //cerr << (result-test) << "\n";
  if((result-test).SumSqr() > 0.000001) return __LINE__;
  return 0;
}

int testMatching() {
  Array2dC<ByteT> img1(10,10);
  ByteT v = 0;
  for(Array2dIterC<ByteT> it(img1);it;it++)
    *it = v++;
  Index2dC at(0,0);
  IntT sum;
  if(RavlImageN::MatchSumAbsDifference(img1,img1,at,sum) != 0)
    return __LINE__;
  return 0;
}
