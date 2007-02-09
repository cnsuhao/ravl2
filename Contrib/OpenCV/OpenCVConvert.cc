#include "Ravl/Image/OpenCVConvert.hh"

namespace RavlImageN{

  using namespace RavlN;

  template <>
  bool RavlImage2IplImage(const ImageC<ByteT> & src, IplImage*& dest)
  {
    CvSize size; size.width = src.Cols(); size.height = src.Rows();
    char *pt = *((char**) src.DataStart());
    dest = cvCreateImage(size, IPL_DEPTH_8U, 1);
    char *pd = dest->imageData;
    for (IntT i=0; i<dest->imageSize; ++i)  *pd++ = *pt++;
    return true;
  }
  
  template <>
  bool RavlImage2IplImage(const ImageC<ByteRGBValueC> & src, IplImage*& dest)
  {
    CvSize size; size.width = src.Cols(); size.height = src.Rows();
    char *pt = *((char**) src.DataStart());
    dest = cvCreateImage(size, IPL_DEPTH_8U, 3);
    char *pd = dest->imageData;
    for (IntT i=0; i<dest->imageSize/3; ++i) {
      *(pd++ +2) = *pt++;
      *pd++      = *pt++;
      *(pd++ -2) = *pt++;
    }
    return true;
  }
  
  template <>
  bool RavlImage2IplImage(const ImageC<RealT> & src, IplImage*& dest)
  {
    CvSize size; size.width = src.Cols(); size.height = src.Rows();
    char *pt = *((char**) src.DataStart());
    dest = cvCreateImage(size, IPL_DEPTH_64F, 1);
    char *pd = dest->imageData;
    for (IntT i=0; i<dest->imageSize; ++i)  *pd++ = *pt++;
    return true;
  }
  
  template <>
  bool RavlImage2IplImage(const ImageC<RealRGBValueC> & src, IplImage*& dest)
  {
    CvSize size; size.width = src.Cols(); size.height = src.Rows();
    double *pt = *((double**) src.DataStart());
    dest = cvCreateImage(size, IPL_DEPTH_64F, 3);
    double *pd = (double *)dest->imageData;
    for (IntT i=0; i<dest->imageSize/24; ++i) {
      *(pd++ +2) = *pt++;
      *pd++      = *pt++;
      *(pd++ -2) = *pt++;
    }
    return true;
  }
  
}
