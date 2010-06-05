/////////////////////////////////////////////////
//! rcsid="$Id: BinImgIO.cc 4 2001-04-11 12:45:55Z craftit $"


#include "amma/BinImgIO.hh"
#include "amma/RGBValue.hh"
#include "amma/YUVValue.hh"
#include "amma/GreyVal.hh"

#include "amma/BinIORGBValue.hh"
#include "amma/BinIOYUVValue.hh"

// Some faster implementations for byte images that arn't endian sensitive.
// Assumes images are allocated in a single block. 

#define ASSUME_BLOCK 1

/// ByteGreyValueT ////////////////////////////////////////////////////////////////////////

BinOStreamC &operator << (BinOStreamC &out,const ImageC<ByteGreyValueT> &img)
{ 
  out << img.Rectangle();
  
  IntT width = img.Cnum();
  IndexT atrow = img.TRow();
  IndexT offset = img.LCol();

  IndexT brow = img.BRow();
  for(;atrow <= brow;atrow++) 
    out.OBuff((const char *) &(img[atrow][offset]),width);
  return out;
}

BinIStreamC &operator >> (BinIStreamC &in,ImageC<ByteGreyValueT> &img)
{ 
  ImageRectangleC rect;
  in >> rect;
  img = ImageC<ByteGreyValueT>(rect);
  
  IntT width = img.Cnum();
  IndexT atrow = img.TRow();
  IndexT offset = img.LCol();
  
  IndexT brow = img.BRow();
  for(;atrow <= brow;atrow++) 
    in.IBuff((char *) &(img[atrow][offset]),width);  
  return in;
}

/// ByteRGBValueC ////////////////////////////////////////////////////////////////////////

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

/// ByteRGBValueC ////////////////////////////////////////////////////////////////////////

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

