// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlImage
//! file="Ravl/Image/ImageIO/ImgIOByteRGB.cc"


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

  static TypeNameC type1(typeid(ImageC<ByteRGBValueC>),"ImageC<ByteRGBValueC>");  
  
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
