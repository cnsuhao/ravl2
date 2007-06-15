#ifndef RAVL_OPENCVCONVERT_HH
#define RAVL_OPENCVCONVERT_HH

//! lib=RavlOpenCV
//! docentry="Ravl.API.Images.Converters.OpenCV"
//! example="exOpenCV.cc"

#include <opencv/cv.h>
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteBGRValue.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/RealBGRValue.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/DP/DataConv.hh"
#include "Ravl/Assert.hh"

namespace RavlImageN {
  
  using namespace RavlN;
  
//! userlevel=Normal
  
  template <class PixelT> 
  bool RavlImage2IplImage(const ImageC<PixelT> & src, IplImage*& pdest)
  {
    RavlIssueError("\nRavlImage2IplImage handles only these pixel types: ByteT, RealT, ByteRGBValueC, RealRGBValueC\n"
                   "Use DPTypeConvert() to convert to required type before calling RavlImage2IplImage.\n");
    return false;
  }
  //: Converts selected RAVL image types to OpenCVformat
  // Only converts the following RAVL image types:<br>
  // ByteT, RealT, ByteRGBValueC, RealRGBValueC

//:-
//! userlevel=Develop

  template <>
  bool RavlImage2IplImage(const ImageC<ByteT> & src, IplImage*& pdest);
  //: (template specialisation)

  template <>
  bool RavlImage2IplImage(const ImageC<ByteRGBValueC> & src, IplImage*& pdest);
  //: (template specialisation)

  template <>
  bool RavlImage2IplImage(const ImageC<RealT> & src, IplImage*& pdest);
  //: (template specialisation)

  template <>
  bool RavlImage2IplImage(const ImageC<RealRGBValueC> & src, IplImage*& pdest);
  //: (ttemplate specialisation)

  
//:-
//! userlevel=Normal

  template <class PixelT> 
  bool IplImage2RavlImage(IplImage* src, ImageC<PixelT> & dest)
  {
    RavlAssertMsg((src->depth == (int)IPL_DEPTH_8U) || (src->depth == (int)IPL_DEPTH_8S) || (src->depth == (int)IPL_DEPTH_64F), "IplImage2RavlImage: can only convert IPL_DEPTH_8U|S and IPL_DEPTH_64F image depths");
    RavlAssertMsg((src->nChannels == 1) || (src->nChannels == 3), "IplImage2RavlImage: can only convert 1 or 3 channel formats");
    switch (src->depth) {
    case IPL_DEPTH_8U: case IPL_DEPTH_8S:
      switch (src->nChannels) {
      case 1: 
        return DPTypeConvert(ImageC<ByteT>(src->height, src->width, (ByteT*)src->imageData, false), dest);
        break;
      case 3:
        return DPTypeConvert(ImageC<ByteBGRValueC>(src->height, src->width, (ByteBGRValueC*)src->imageData, false), dest);
        break;
      default:
        return false;
      }
    case IPL_DEPTH_64F:
      switch (src->nChannels) {
      case 1: 
        return DPTypeConvert(ImageC<RealT>(src->height, src->width, (RealT*)src->imageData, false), dest);
        break;
      case 3:
        return DPTypeConvert(ImageC<RealBGRValueC>(src->height, src->width, (RealBGRValueC*)src->imageData, false), dest);
        break;
      default:
        return false;
      }
    default: 
      return false;
    }
  }
  //: Converts these OpenCV images - BRG colour or grey-level, ByteT or RealT -  to any RAVL image type

  
}

#endif
