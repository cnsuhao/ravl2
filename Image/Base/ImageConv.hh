// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_IMAGECONV_HEADER
#define RAVLIMAGE_IMAGECONV_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Base/ImageConv.hh"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="16/03/1999"
//! docentry="Ravl.API.Images.Converters"

#include "Ravl/Image/Image.hh"

namespace RavlImageN {

  class ByteYUVValueC;
  class ByteYUVAValueC;
  class ByteYUV422ValueC;
  class ByteVYUValueC;
  class RealYUVValueC;
  class ByteRGBValueC;
  class RealRGBValueC;
  class ByteRGBAValueC;
  class RealRGBAValueC;
  class ByteRGBMedianC;
  class RealRGBAverageC;
  class UInt16RGBValueC;
  class RealHSVValueC ; 
  template<typename CompT> class RGBValueC; 
  template<typename CompT> class YCbCrBT601ValueC; 
  template<typename CompT> class YCbCr422BT601ValueC; 
  class ByteYCbCrBT601ValueC ; 
  class UInt16YCbCrBT601ValueC ; 
  
  ImageC<ByteRGBValueC> ByteRGBAImageCT2ByteRGBImageCT(const ImageC<ByteRGBAValueC> &dat);
  //: Byte RGBA to Byte RGB image
  
  ImageC<ByteRGBAValueC> ByteRGBImageCT2ByteRGBAImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte RGB to Byte RGBA image
  
  ImageC<RealRGBValueC> RealRGBAImageCT2RealRGBImageCT(const ImageC<RealRGBAValueC> &dat);
  //: Real RGBA to Real RGB image
  
  ImageC<RealRGBAValueC> RealRGBImageCT2RealRGBAImageCT(const ImageC<RealRGBValueC> &dat);
  //: Real RGB to Real RGBA image
  
  ImageC<RealT> ByteImageCT2DoubleImageCT(const ImageC<ByteT> &dat);
  //: Byte to double image.
    
  ImageC<IntT> ByteImageCT2IntImageCT(const ImageC<ByteT> &dat);
  //: Byte to int image.
  
  ImageC<RealT> IntImageCT2DoubleImageCT(const ImageC<IntT> &dat);
  //: Int to double image.
  
  ImageC<ByteRGBValueC> ByteImageCT2ByteRGBImageCT(const ImageC<ByteT> &dat);
  //: Byte grey level to byte RGB image.
    
  ImageC<ByteYUVValueC> ByteImageCT2ByteYUVImageCT(const ImageC<ByteT> &dat);
  //: Byte grey level to byte YUV colour image.
  
  ImageC<ByteT> DoubleImageCT2ByteImageCT(const ImageC<RealT> &dat) ; 
  //: Double -> Byte (clipped to fit)
  // This will clip, then round the double value (NOT floor!) to fit in a byte value 0 to 255.
  
  ImageC<RealRGBValueC> RealYUVImageCT2RealRGBImageCT(const ImageC<RealYUVValueC> &dat);
  //: Real YUV -> RGB
  
  ImageC<RealYUVValueC> RealRGBImageCT2RealYUVImageCT(const ImageC<RealRGBValueC> &dat);
  //: Real RGB -> YUV

  ImageC<ByteT> ByteYUVImageCT2ByteImageCT(const ImageC<ByteYUVValueC> &dat);
  //: Byte grey level to byte YUV colour image.
  
  ImageC<ByteT> RGBImageCT2ByteImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte colour to byte grey image.
  
  ImageC<RealT> RGBImageCT2DoubleImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte Colour to double image.
  
  ImageC<ByteRGBValueC> YUVImageCT2RGBImageCT(const ImageC<ByteYUVValueC> &dat);
  //: Byte YUV to byte RGB image.
  
  ImageC<ByteYUVValueC> RGBImageCT2YUVImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte RGB to byte YUV image.

  ImageC<ByteRGBValueC>  RealRGBAverageImageC2ByteRGBImageCT(const ImageC<RealRGBAverageC> &dat);
  //: Real RGB rolling average -> RGB

  ImageC<ByteRGBValueC>  ByteRGBMedianImageC2ByteRGBImageCT(const ImageC<ByteRGBMedianC> &dat);
  //: Byte RGB median -> RGB

  ImageC<RealRGBValueC>  ByteRGBImageCT2RealRGBImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte RGB -> Real RGB

  ImageC<ByteRGBValueC>  RealRGBImageCT2ByteRGBImageCT(const ImageC<RealRGBValueC> &dat);
  //: Real RGB -> Byte RGB

  ImageC<UInt16RGBValueC> ByteRGBImageCT2UInt16RGBImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte RGB -> UInt16 RGB

  ImageC<ByteRGBValueC>  UInt16RGBImageCT2ByteRGBImageCT(const ImageC<UInt16RGBValueC> &dat);
  //: UInt16 RGB -> Byte RGB

  ImageC<ByteYUVValueC> ByteYUVAImageCT2ByteYUVImageCT(const ImageC<ByteYUVAValueC> &dat);
  //: YUVA -> YUV
  
  ImageC<ByteYUVAValueC> ByteYUVImageCT2ByteYUVAImageCT(const ImageC<ByteYUVValueC> &dat);
  //: YUV -> YUVA
  
  ImageC<RealYUVValueC> ByteYUVImageCT2RealYUVImageCT(const ImageC<ByteYUVValueC> &dat);
  //: Byte YUV -> Read YUV
  
  ImageC<ByteYUVValueC> RealYUVImageCT2ByteYUVImageCT(const ImageC<ByteYUVValueC> &dat);
  //: Real YUV -> Byte YUV
  
  ImageC<ByteT> BoolImageC2ByteImageCT(const ImageC<bool> &dat);
  //: Boolean Image -> Byte Image
  
  ImageC<ByteYUVValueC> ByteVYUImageCT2ByteYUVImageCT(const ImageC<ByteVYUValueC> &dat);
  //: Byte VYU -> Byte YUV
  
  ImageC<ByteVYUValueC> ByteYUVImageCT2ByteVYUImageCT(const ImageC<ByteYUVValueC> &dat);
  //: Byte YUV -> Byte VYU
  
  ImageC<ByteYUVValueC> ByteYUV422ImageCT2ByteYUVImageCT(const ImageC<ByteYUV422ValueC> &dat);
  //: Byte YUV422 -> Byte YUV
  
  ImageC<ByteRGBValueC> ByteYUV422ImageCT2ByteRGBImageCT(const ImageC<ByteYUV422ValueC> &dat);
  //: Byte YUV -> Byte YUV422
  
  ImageC<ByteRGBValueC> ByteDVSYUV422ImageCT2ByteDVSRGBImageCT(const ImageC<ByteYUV422ValueC> &dat);
  //: Byte DVSYUV422 -> Byte DVSRGB

  ImageC<ByteT> ByteYUV422ImageCT2ByteImageCT(const ImageC<ByteYUV422ValueC> &dat);
  //: Byte YUV422 -> Byte
  
  ImageC<ByteYUV422ValueC> ByteImageCT2ByteYUV422ImageCT(const ImageC<ByteT> &dat);
  //: Byte -> Byte YUV422

  ImageC<ByteYUV422ValueC> ByteRGBImageCT2ByteYUV422ImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte RGB -> Byte YUV422

  ImageC<RealT> UIntTImageCT2DoubleImageCT(const ImageC<UIntT> &dat);
  //: UIntT -> RealT

  ImageC<UIntT> UInt16TImageCT2UIntTImageCT(const ImageC<UInt16T> &dat);
  //: UInt16T -> UIntT

  ImageC<UInt16T> UIntTImageCT2UInt16TImageCT(const ImageC<UIntT> &dat);
  //: UIntT -> UInt16T

  ImageC<RealHSVValueC> RealRGBImageCT2RealHSVImageCT(const ImageC<RealRGBValueC> & dat) ;
  //: Real RGB -> Real HLS 
  
  ImageC<RealRGBValueC> RealHSVImageCT2RealRGBImageCT(const ImageC<RealHSVValueC> & dat) ;
  //: Real HLS -> Real RGB
  
  ImageC<RealT> FloatTImageCT2RealImageCT(const ImageC<FloatT> &dat);
  //: FloatT -> RealT
  
  ImageC<FloatT> RealTImageCT2FloatImageCT(const ImageC<RealT> &dat);
  //: RealT -> FloatT
  
  ImageC<FloatT> ByteRGBImageCT2FloatImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte Colour to double image.
  
  ImageC<ByteT> BoolImage2ByteImage(const ImageC<bool> &dat);
  //: Convert an image of bool's to a byte image.
  
  ImageC<bool> ByteImage2BoolImage(const ImageC<ByteT> &dat);
  //: Convert an image of byte's to a bool image.
  
  ImageC<ByteT> ByteYCbCrBT601ValueImage2ByteImage(const ImageC<ByteYCbCrBT601ValueC> &dat);
  //: Convert an ByteYCbCrBT601ValueC to a byte value.
  
  ImageC<UInt16T> UInt16YCbCrBT601ValueImage2UInt16Image(const ImageC<UInt16YCbCrBT601ValueC> &dat);
  //: Convert an UInt16YCbCrBT601ValueC to a UInt16T value.
  
  ImageC<UInt16YCbCrBT601ValueC> ByteYCbCrBT601ValueImage2UInt16YCbCrBT601ValueImage(const ImageC<UInt16YCbCrBT601ValueC> &dat);
  //: Convert an ByteYCbCrBT601ValueC to a UInt16YCbCrBT601Value value.
  
  ImageC<RGBValueC<float> > YCbCrBT601ValueFloatImage2ImageRGBValueFloat(const ImageC<YCbCrBT601ValueC<float> > &dat);
  //: Convert YCbCrBT601 to RGB in floating point format.
  
  ImageC<ByteRGBValueC> ByteYCbCrBT601ValueImage2ByteRGBImage(const ImageC<ByteYCbCrBT601ValueC > &dat);
  //: Convert YCbCrBT601 to byte RGB.
  
  ImageC<ByteYCbCrBT601ValueC > ByteRGBImage2ByteYCbCrBT601ValueImage(const ImageC<ByteRGBValueC>  &dat);
  //: Convert byte RGB to YCbCrBT601.
  
  ImageC<YCbCrBT601ValueC<float> > ImageRGBValueFloat2YCbCrBT601ValueFloatImage(const ImageC<RGBValueC<float> > &dat);
  //: Convert RGB to YCbCrBT601 in floating point format.
  
  ImageC<RGBValueC<float> > RealRGBImageCT2RGBImageCFloat(const ImageC<RealRGBValueC> & dat );
  //: Convert between real and float RGB values.
  
  ImageC<RealRGBValueC> RGBImageCFloat2RealRGBImageCT(const ImageC<RGBValueC<float> > & dat );
  //: Convert between float and real RGB values.
  
  
};

#endif
