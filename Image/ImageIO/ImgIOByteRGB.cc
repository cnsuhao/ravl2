///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "amma/DP/FileFormatStream.hh"
#include "amma/DP/FileFormatBinStream.hh"
#include "amma/DP/Converter.hh"
#include "amma/BinImgIO.hh"
#include "amma/BinIORGBValue.hh"
#include "amma/RGBImage.hh"

void InitImgIOByteRGB()
{}

namespace StdImageN
{
  ImageC<ByteRGBValueC> DPConvRGBImageC2ImageCT(const RGBImageC &dat)  
  { return ImageC<ByteRGBValueC>(dat); }
  
  RGBImageC DPConvImageCT2RGBImageC(const ImageC<ByteRGBValueC> &dat)  
  { return RGBImageC(dat); }
  
  DP_REGISTER_CONVERTION(DPConvRGBImageC2ImageCT,1);
  DP_REGISTER_CONVERTION(DPConvImageCT2RGBImageC,1);

  FileFormatStreamC<ImageC<ByteRGBValueC> > FileFormatStream_ImageC_ByteRGBValueC;
  FileFormatBinStreamC<ImageC<ByteRGBValueC> > FileFormatBinStream_ImageC_ByteRGBValueC;
}


////////////////////////////////////////////////////////////
// Accelerated IO routines...

BinOStreamC &operator << (BinOStreamC &out,const ImageC<ByteRGBValueC> &img)
{ 
  out << img.Rectangle();
  
  IntT width = img.Cnum() * 3;
  IndexT atrow = img.TRow();
  IndexT offset = img.LCol();
  
  IndexT brow = img.BRow();
  for(;atrow <= brow;atrow++) 
    out.OBuff((const char *) &(img[atrow][offset]),width);
  
  return out;
}

BinIStreamC &operator >> (BinIStreamC &in,ImageC<ByteRGBValueC> &img)
{ 
  ImageRectangleC rect;
  in >> rect;
  img = ImageC<ByteRGBValueC>(rect);
  
  IntT width = img.Cnum() * 3;
  IndexT atrow = img.TRow();
  IndexT offset = img.LCol();
  
  IndexT brow = img.BRow();
  for(;atrow <= brow;atrow++)
    in.IBuff((char *) &(img[atrow][offset]),width);
  return in;
}

