// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlImageIO
//! file="Ravl/Image/ImageIO/ImgIOByteYUVA.cc"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteYUVAValue.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/TypeName.hh"

namespace RavlImageN {
  
  void InitImgIOByteYUVA()
    {}
  
  static TypeNameC type1(typeid(ImageC<ByteYUVAValueC>),"ImageC<ByteYUVAValueC>");  
  
  FileFormatStreamC<ImageC<ByteYUVAValueC> > FileFormatStream_ImageC_ByteYUVAValueC;
  FileFormatBinStreamC<ImageC<ByteYUVAValueC> > FileFormatBinStream_ImageC_ByteYUVAValueC;
  
  ////////////////////////////////////////////////////////////
  // Accelerated IO routines...
  
  BinOStreamC &operator << (BinOStreamC &out,const ImageC<ByteYUVAValueC> &img) { 
    out << img.Rectangle();
    
    IntT width = img.Cols() * 4;
    IndexC atrow = img.TRow();
    IndexC offset = img.LCol();
    
    IndexC brow = img.BRow();
    for(;atrow <= brow;atrow++) 
      out.OBuff((const char *) &(img[atrow][offset]),width);  
    return out;
  }
  
  BinIStreamC &operator >> (BinIStreamC &in,ImageC<ByteYUVAValueC> &img) { 
    ImageRectangleC rect;
    in >> rect;
    img = ImageC<ByteYUVAValueC>(rect);
    
    IntT width = img.Cols() * 4;
    IndexC atrow = img.TRow();
    IndexC offset = img.LCol();
    IndexC brow = img.BRow();
    for(;atrow <= brow;atrow++) 
      in.IBuff((char *) &(img[atrow][offset]),width);  

    return in;
  }
  

}

