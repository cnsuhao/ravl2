///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "amma/DP/FileFormatStream.hh"
#include "amma/DP/FileFormatBinStream.hh"
#include "amma/DP/Converter.hh"
#include "amma/BinIOYUVValue.hh"
#include "amma/BinImgIO.hh"
#include "amma/YUVImage.hh"

void InitImgIOByteYUV()
{}

ImageC<ByteYUVValueC> DPConvYUVImageC2ImageCT(const YUVImageC &dat)  
{ return ImageC<ByteYUVValueC>(dat); }

YUVImageC DPConvImageCT2YUVImageC(const ImageC<ByteYUVValueC> &dat)  
{ return YUVImageC(dat); }

DP_REGISTER_CONVERTION(DPConvYUVImageC2ImageCT,1);
DP_REGISTER_CONVERTION(DPConvImageCT2YUVImageC,1);

FileFormatStreamC<ImageC<ByteYUVValueC> > FileFormatStream_ImageC_ByteYUVValueC;
FileFormatBinStreamC<ImageC<ByteYUVValueC> > FileFormatBinStream_ImageC_ByteYUVValueC;


BinOStreamC &operator << (BinOStreamC &out,const ImageC<ByteYUVValueC> &img)
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

BinIStreamC &operator >> (BinIStreamC &in,ImageC<ByteYUVValueC> &img)
{ 
  ImageRectangleC rect;
  in >> rect;
  img = ImageC<ByteYUVValueC>(rect);
  
  IntT width = img.Cnum() * 3;
  IndexT atrow = img.TRow();
  IndexT offset = img.LCol();
  
  IndexT brow = img.BRow();
  for(;atrow <= brow;atrow++)
    in.IBuff((char *) &(img[atrow][offset]),width);
  return in;
}

