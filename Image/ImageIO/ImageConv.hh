// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGECNV_HEADER
#define RAVLIMAGECNV_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/DPImageIO/ImageConv.hh"
//! lib=RavlImageIO
//! userlevel=Normal
//! author="Charles Galambos"
//! date="16/03/99"
//! docentry="Ravl.Images.IO"

#include "Ravl/Image/Image.hh"

namespace RavlImageN {

  class ByteYUVValueC;
  class RealYUVValueC;
  class ByteRGBValueC;
  class RealRGBValueC;
  class ByteRGBAValueC;
  
  //: Image handleing namespace.
  
  ImageC<ByteRGBValueC> ByteRGBAImageCT2ByteRGBImageCT(const ImageC<ByteRGBAValueC> &dat);
  
  ImageC<ByteRGBAValueC> ByteRGBImageCT2ByteRGBAImageCT(const ImageC<ByteRGBValueC> &dat);

  ImageC<RealT> ByteImageCT2DoubleImageCT(const ImageC<ByteT> &dat);
  // Byte to double image.
    
  ImageC<IntT> ByteImageCT2IntImageCT(const ImageC<ByteT> &dat);
  // Byte to int image.
  
  ImageC<RealT> IntImageCT2DoubleImageCT(const ImageC<IntT> &dat);
  // Int to double image.
  
  ImageC<ByteRGBValueC> ByteImageCT2ByteRGBImageCT(const ImageC<ByteT> &dat);
  // Byte grey level to colour image.
    
  ImageC<ByteYUVValueC> ByteImageCT2ByteYUVImageCT(const ImageC<ByteT> &dat);
  // Byte grey level to byte YUV colour image.
  
  ImageC<ByteT> DoubleImageCT2ByteImageCT(const ImageC<RealT> &dat) ; 
  // Double -> Byte (clipped to fit)
  // This will clip, then round the double value (NOT floor!) to fit in a byte value 0 to 255.
  
  ImageC<RealRGBValueC> RealYUVImageCT2RealRGBImageCT(const ImageC<RealYUVValueC> &dat);
  // Real YUV -> RGB
  
  ImageC<RealYUVValueC> RealRGBImageCT2RealYUVImageCT(const ImageC<RealRGBValueC> &dat);
  // Real RGB -> YUV

  ImageC<ByteT> ByteYUVImageCT2ByteImageCT(const ImageC<ByteYUVValueC> &dat);
  // Byte grey level to byte YUV colour image.
  
  ImageC<ByteT> RGBImageCT2ByteImageCT(const ImageC<ByteRGBValueC> &dat);
  // Byte colour to byte grey image.
  
  ImageC<RealT> RGBImageCT2DoubleImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte Colour to double image.
  
  ImageC<ByteRGBValueC> YUVImageCT2RGBImageCT(const ImageC<ByteYUVValueC> &dat);
  //: Byte YUV to byte RGB image.
  
  ImageC<ByteYUVValueC> RGBImageCT2YUVImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte RGB to byte YUV image.
  
};

#endif
