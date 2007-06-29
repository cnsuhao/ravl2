#include "Ravl/Image/OpenCVConvert.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/RealRGBValue.hh"


using namespace RavlN;
using namespace RavlImageN;

int TestOpenCVConv () {
  ImageC<ByteT>         im1(35,45);  im1.ShiftArray(Index2dC(3,5));
  ImageC<RealT>         im2(35,45);  im2.ShiftArray(Index2dC(3,5));
  ImageC<ByteRGBValueC> im3(35,45);  im3.ShiftArray(Index2dC(3,5));
  ImageC<RealRGBValueC> im4(35,45);  im4.ShiftArray(Index2dC(3,5));
  IplImage* ocvim = 0;

  if (!RavlImage2IplImage(im1, ocvim))  return __LINE__;

  if (!IplImage2RavlImage(ocvim, im1))  return __LINE__;
  if (!IplImage2RavlImage(ocvim, im2))  return __LINE__;
  if (!IplImage2RavlImage(ocvim, im3))  return __LINE__;
  if (!IplImage2RavlImage(ocvim, im4))  return __LINE__;
  cvReleaseImage(&ocvim);

  if (!RavlImage2IplImage(im2, ocvim))  return __LINE__;

  if (!IplImage2RavlImage(ocvim, im1))  return __LINE__;
  if (!IplImage2RavlImage(ocvim, im2))  return __LINE__;
  if (!IplImage2RavlImage(ocvim, im3))  return __LINE__;
  if (!IplImage2RavlImage(ocvim, im4))  return __LINE__;
  cvReleaseImage(&ocvim);

  if (!RavlImage2IplImage(im3, ocvim))  return __LINE__;

  if (!IplImage2RavlImage(ocvim, im1))  return __LINE__;
  if (!IplImage2RavlImage(ocvim, im2))  return __LINE__;
  if (!IplImage2RavlImage(ocvim, im3))  return __LINE__;
  if (!IplImage2RavlImage(ocvim, im4))  return __LINE__;
  cvReleaseImage(&ocvim);

  if (!RavlImage2IplImage(im4, ocvim))  return __LINE__;

  if (!IplImage2RavlImage(ocvim, im1))  return __LINE__;
  if (!IplImage2RavlImage(ocvim, im2))  return __LINE__;
  if (!IplImage2RavlImage(ocvim, im3))  return __LINE__;
  if (!IplImage2RavlImage(ocvim, im4))  return __LINE__;
  cvReleaseImage(&ocvim);

  return 0;
}

int main()
{

  cerr << "Testing OpenCV image conversion \n";
  int lineno;
  if((lineno = TestOpenCVConv()) != 0) {
    cerr << "Image conversion test failed : " << lineno << "\n";
     return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}


  /*  
  cout << src->nSize << endl; // size of this struct
  cout << src->nChannels << endl; // 3 for colour
  cout << src->depth << endl; // bits per channel - 8 for byte
  cout << src->dataOrder << endl; // 0 for interleaved
  cout << src->origin << endl; // 0 for top left corner; 1 for bottom left
  cout << src->width << endl;
  cout << src->height << endl;
  cout << src->imageSize << endl; // # of bytes (I think)
  cout << src->widthStep << endl; // row length in bytes (I think)
  */

