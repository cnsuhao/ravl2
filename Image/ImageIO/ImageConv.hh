#ifndef IMAGECNV_HEADER
#define IMAGECNV_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="amma/Image/DPImageIO/ImageConv.hh"
//! lib=DPImageIO
//! userlevel=Normal
//! author="Charles Galambos"
//! date="16/03/99"
//! docentry="Ravl.Images.IO"

#include "amma/Image.hh"
#include "amma/GreyVal.hh"
//#include "amma/RGBValue.hh"

class ByteYUVValueC;
class YUVPointC;
class ByteRGBValueC;
class RGBPointC;
class ByteRGBXValueC;
//: Image handleing namespace.

namespace StdImageN
{
  ImageC<ByteRGBValueC> ByteRGBXImageCT2ByteRGBImageCT(const ImageC<ByteRGBXValueC> &dat);
  
  ImageC<ByteRGBXValueC> ByteRGBImageCT2ByteRGBXImageCT(const ImageC<ByteRGBValueC> &dat);

  ImageC<DoubleImageValueT> ByteImageCT2DoubleImageCT(const ImageC<ByteGreyValueT> &dat);
  // Byte to double image.
    
  ImageC<IntT> ByteImageCT2IntImageCT(const ImageC<ByteGreyValueT> &dat);
  // Byte to int image.
  
  ImageC<DoubleImageValueT> IntImageCT2DoubleImageCT(const ImageC<IntT> &dat);
  // Int to double image.
  
  ImageC<ByteRGBValueC> ByteImageCT2ByteRGBImageCT(const ImageC<ByteGreyValueT> &dat);
  // Byte grey level to colour image.
    
  ImageC<ByteYUVValueC> ByteImageCT2ByteYUVImageCT(const ImageC<ByteGreyValueT> &dat);
  // Byte grey level to byte YUV colour image.
  
  ImageC< ByteGreyValueT> DoubleImageCT2ByteImageCT(const ImageC< DoubleImageValueT> &dat) ; 
  // Double -> Byte (clipped to fit)
  // This will clip, then round the double value (NOT floor!) to fit in a byte value 0 to 255.
  
  ImageC<RGBPointC> RealYUVImageCT2RealRGBImageCT(const ImageC<YUVPointC> &dat);
  // Real YUV -> RGB

  ImageC<YUVPointC> RealRGBImageCT2RealYUVImageCT(const ImageC<RGBPointC> &dat);
  // Real RGB -> YUV

  ImageC<ByteGreyValueT> ByteYUVImageCT2ByteImageCT(const ImageC<ByteYUVValueC> &dat);
  // Byte grey level to byte YUV colour image.
  
  ImageC<ByteGreyValueT> RGBImageCT2ByteImageCT(const ImageC<ByteRGBValueC> &dat);
  // Byte colour to byte grey image.
  
  ImageC<DoubleImageValueT> RGBImageCT2DoubleImageCT(const ImageC<ByteRGBValueC> &dat);
  // Byte Colour to double image.
  
  ImageC<ByteRGBValueC> YUVImageCT2RGBImageCT(const ImageC<ByteYUVValueC> &dat);
  // Byte YUV to byte RGB image.
  
  ImageC<ByteYUVValueC> RGBImageCT2YUVImageCT(const ImageC<ByteRGBValueC> &dat);
  // Byte RGB to byte YUV image.
  

};

namespace StdImageConv = StdImageN; // For backward compability.

#endif
