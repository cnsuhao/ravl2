///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"


#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/TypeName.hh"


namespace RavlN {
  
  void InitImgIOByteRGB()
    {}

  
  FileFormatStreamC<ImageC<ByteRGBValueC> > FileFormatStream_ImageC_ByteRGBValueC;
  FileFormatBinStreamC<ImageC<ByteRGBValueC> > FileFormatBinStream_ImageC_ByteRGBValueC;
  
  
  ////////////////////////////////////////////////////////////
  // Accelerated IO routines...
  
  BinOStreamC &operator << (BinOStreamC &out,const ImageC<ByteRGBValueC> &img) { 
    out << img.Rectangle();
    
    IntT width = img.Cols() * 3;
    IndexC atrow = img.TRow();
    IndexC offset = img.LCol();
    
    IndexC brow = img.BRow();
    for(;atrow <= brow;atrow++) 
      out.OBuff((const char *) &(img[atrow][offset]),width);  
    return out;
  }
  
  BinIStreamC &operator >> (BinIStreamC &in,ImageC<ByteRGBValueC> &img) { 
    ImageRectangleC rect;
    in >> rect;
    img = ImageC<ByteRGBValueC>(rect);
    
    IntT width = img.Cols() * 3;
    IndexC atrow = img.TRow();
    IndexC offset = img.LCol();
    IndexC brow = img.BRow();
    for(;atrow <= brow;atrow++) 
      in.IBuff((char *) &(img[atrow][offset]),width);  

    return in;
  }
  

}
