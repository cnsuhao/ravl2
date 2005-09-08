// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImage
//! file="Ravl/Image/Base/testImage.cc"
//! docentry="Ravl.Images"
//! author="Charles Galambos"
//! userlevel=Develop

#include "Ravl/String.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/RGBcYUV.hh"
#include "Ravl/Image/Deinterlace.hh"
#include "Ravl/Image/Font.hh"
#include "Ravl/Image/DrawLine.hh"
#include "Ravl/Image/DrawFrame.hh"
#include "Ravl/Image/DrawCircle.hh"
#include "Ravl/Image/DrawEllipse.hh"
#include "Ravl/Image/Reflect.hh"
#include "Ravl/Image/BilinearInterpolation.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/IO.hh"

using namespace RavlImageN;

int TestBasic();
int TestIO();
int TestColorCnv();
int TestInterlace();
int TestFont();
int TestDraw();
int TestBilinear();

template class ImageC<int>; // Make sure all functions are compiled.

int main()
{
  cerr << "Testing basic image ops. \n";
  int lineno;
  if((lineno = TestBasic()) != 0) {
    cerr << "Image test failed : " << lineno << "\n";
     return 1;
  }
  if((lineno = TestIO()) != 0) {
    cerr << "Image io test failed : " << lineno << "\n";
     return 1;
  }
  if((lineno = TestColorCnv()) != 0) {
    cerr << "Image test failed : " << lineno << "\n";
     return 1;
  }
  if((lineno = TestInterlace()) != 0) {
    cerr << "Image test failed : " << lineno << "\n";
     return 1;
  }
  if((lineno = TestFont()) != 0) {
    cerr << "Image test failed : " << lineno << "\n";
     return 1;
  }
  if((lineno = TestDraw()) != 0) {
    cerr << "Image test failed : " << lineno << "\n";
     return 1;
  }
  if((lineno = TestBilinear()) != 0) {
    cerr << "Image test failed : " << lineno << "\n";
     return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

////////////////////////////////
// Check iterators, and image copying

int TestBasic()
{
  cerr << "Starting basic tests... \n";
  // Create test image.
  
  ImageRectangleC rect(5,10,6,9);
  cerr << "Size1:" << rect.Range1().Size() << " Size2:" << rect.Range2().Size() << "\n";
  ImageC<int> testImg(rect);
  
  int i = 0;
  
  Array2dIterC<int> it(testImg);
  if(it.Index() != rect.Origin()) {
    cerr << "Origin check failed. \n";
    return __LINE__;
  }
  
  for(;it.IsElm();it.Next()) 
    it.Data() = i++;

  if(rect.Area() != (UIntT) i) {
    cerr << "Iterator check failed. Area mis-match. Count:" << i << " should be " << rect.Area() <<  "\n";
    return __LINE__;
  }
  if(testImg[10][9] != (i-1)) {
    cerr<< "Inital spot value check failed. " << testImg[10][9]  << " Expected:" << (i-1)<< "\n";
    cerr << testImg;
    return __LINE__;
  }
  // Make copy...
  
  ImageC<int> testInImg = testImg.Copy();

  if(testInImg[10][9] != (i-1)) {
    cerr<< "Spot value check 2 failed. " << testInImg[10][9]  << " Expected:" << (i-1)<< "\n";
    cerr << testInImg;
    return __LINE__;
  }
  if(testImg[10][9] != (i-1)) {
    cerr<< "Spot value check 3 failed. " << testImg[10][9]  << " Expected:" << (i-1)<< "\n";
    cerr << testImg;
    return __LINE__;
  }
  cerr <<"Copy " << testInImg<<"\n";
  // check image.
  
  if(testInImg[6][7] != testImg[6][7]) {
    cerr<< "Spot value check failed. \n";
    return __LINE__;
  }

  if(testInImg[5][6] != 0 || testImg[5][6] != 0) {
    cerr<< "Spot value check failed. \n";
    return __LINE__;
  }
  
  if(testInImg.Rectangle() != testImg.Rectangle()) {
    cerr<< "Rectangle size mismatch. \n";
    return __LINE__;
  }
  
  for(Array2dIter2C<int,int> it2(testInImg,testImg);it2;it2++) {
    if(it2.Data1() != it2.Data2()) {
      cerr<< "Image contents mismatch at " <<it2.Index() << ":" << it2.Data1() << " " << it2.Data2() << "\n";
      return __LINE__;
    }
  }
  
  testImg[10][9] = 0;
  if(testInImg[10][9] != (i-1)) {
    cerr<< "Spot value check 4 failed. " << testInImg[10][9]  << " Expected:" << (i-1)<< "\n";
    cerr << testImg;
    return __LINE__;
  }

  return 0;
}

////////////////////////////////
// Check image io opreators.

int TestIO()
{
  cerr << "Starting IO test... \n";
  FilenameC testFn("/tmp/testImage.zyx");
  testFn = testFn.MkTemp();
  cerr << "Using file '" << testFn << "'\n";
  // Create test image.
  
  ImageRectangleC rect(5,10,4,11);
  ImageC<int> testImg(rect);
  
  int i = 0;
  Array2dIterC<int> it(testImg);
  if(it.Index() != rect.Origin()) {
    cerr << "Origin check failed. \n";
    return __LINE__;
  }
  
  for(;it.IsElm();it.Next()) 
    it.Data() = i++;
  
  if(testImg.Rectangle().Area() != ((UIntT) i)) {
    cerr << "Area test failed! \n";
    return __LINE__;
  }
  
  // Write out test image.
  {
    OStreamC out(testFn);
    out << testImg;
    if(!out) {
      cerr << "Image write failed! \n";
      return __LINE__;
    }
  }
  
  ImageC<int> testInImg;
  
  // Read in test image.
  {
    IStreamC in(testFn); 
    if(!in) {
      cerr << "Image read failed! \n";
      return __LINE__;
    }
    in >> testInImg;
  }
  
  if(testInImg.Rectangle() != testImg.Rectangle()) {
    cerr<< "Rectangle size mismatch. \n";
    return __LINE__;
  }
  
  for(Array2dIter2C<int,int> it2(testInImg,testImg);it2.IsElm();it2.Next()) {
    if(it2.Data1() != it2.Data2()) {
      cerr<< "Image contents mismatch at " <<it2.Index() << ":" << it2.Data1() << " " << it2.Data2() << "\n";
      return __LINE__;
    }
  }
  
  if(testFn.Exists())
    testFn.Remove();
  
  return 0;
}

int TestColorCnv() {
  RealYUVValueC yuv(20,30,40);
  cerr << "yuv=" << yuv << "\n";
  RealRGBValueC rgb(yuv);
  cerr << "rgb=" << rgb << "\n";
  RealYUVValueC yuv2(rgb);
  cerr << "yuv2=" << yuv2 << "\n";
  RealT diff = (yuv - yuv2).SumOfSqr();
  if(diff > 0.002) return __LINE__;
  return 0;
}

int TestInterlace() {
  cerr << "TestInterlace(), Called \n";
  ImageC<IntT> img(10,10);
  img.Fill(0);
  ImageC<IntT> res = Interlace(img);
  if(res.RowPtr(0) != img.RowPtr(0)) return __LINE__;
  if(res.RowPtr(1) != img.RowPtr(5)) return __LINE__;
  if(res.RowPtr(2) != img.RowPtr(1)) return __LINE__;
  if(res.RowPtr(3) != img.RowPtr(6)) return __LINE__;
  if(res.RowPtr(4) != img.RowPtr(2)) return __LINE__;
  if(res.RowPtr(5) != img.RowPtr(7)) return __LINE__;
  if(res.RowPtr(6) != img.RowPtr(3)) return __LINE__;
  if(res.RowPtr(7) != img.RowPtr(8)) return __LINE__;
  if(res.RowPtr(8) != img.RowPtr(4)) return __LINE__;
  if(res.RowPtr(9) != img.RowPtr(9)) return __LINE__;
  return 0;
}

int TestFont() {
  cerr << "TestFont(), Called. \n";
  //FontC fnt = LoadPSF1("default8x16.psf");
  FontC fnt(true);
  if(!fnt.IsValid()) return __LINE__;
  ImageC<ByteT> img(100,100);
  img.Fill(0);
  DrawText(fnt,(ByteT) 255,Index2dC(50,10),"Hello",img);
  //Save("@X",img);
  return 0;
}

int TestDraw() {
  // Do some quick tests on the draw functions.
  ImageC<ByteT> img(100,100);
  img.Fill(0);
  Index2dC from(10,10);
  Index2dC to(90,90);
  DrawLine(img,(ByteT) 255,from,to);
  if(img[50][50] != 255) return __LINE__;
  if(img[from] != 255) return __LINE__;
  if(img[to] != 255) return __LINE__;
  DrawCircle(img,(ByteT) 254,Index2dC(50,50),30);
  DrawFrame(img,(ByteT) 255,5,img.Frame());
  //Save("@X",img);
  if(img[0][0] != 255) return __LINE__;
  if(img[99][99] != 255) return __LINE__;
  if(img[15][10] != 0) return __LINE__;
  Ellipse2dC ellipse(Point2dC(50,50),40,20,0);
  DrawEllipse(img,(ByteT) 255,ellipse);
  DrawFrame(img,(ByteT) 128,img.Frame());
  if(img[0][0] != 128) return __LINE__;
  if(img[99][99] != 128) return __LINE__;
  if(img[0][99] != 128) return __LINE__;
  if(img[99][0] != 128) return __LINE__;
  //Save("@X",img);
  return 0;
}

int TestBilinear() {
  ImageC<RealT> img(4,4);
  img.Fill(0);
  img[1][1] = 1.0;
  
  RealT value;
  for(int i = 0;i < 3;i++) {
    for(int j = 0;j < 3;j++) {
      BilinearInterpolation(img,Point2dC((RealT) i,(RealT) j),value);
      cerr << "Value=" << value << "\n";
      if(Abs(img[i][j] - value) > 0.001) return __LINE__;
    }
  }
  
  return 0;
}
