// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlImageIO
//! file="Ravl/Image/ImageIO/ImgIOByteYUV422.cc"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/ByteYUV422Value.hh"
#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter2.hh"

namespace RavlImageN {

  void InitImgIOByteYUV422()
  {}
  
  ImageC<ByteT> ByteYUV422ImageCT2ByteImageCT(const ImageC<ByteYUV422ValueC> &dat) { 
    ImageC<ByteT> ret(dat.Rectangle());
    for(Array2dIter2C<ByteT,ByteYUV422ValueC> it(ret,dat);it;it++) 
      it.Data1() = it.Data2().Y();
    return ret;
  }
  
  // Convert a YUV422 image into a YUV444 image.
  // What to do about interlace ?
  
  ImageC<ByteYUVValueC> ByteYUV422ImageCT2ByteYUVImageCT(const ImageC<ByteYUV422ValueC> &dat) { 
    ImageRectangleC outRect = dat.Rectangle();
    // Make sure we're aligned correctly.
    if(outRect.LCol().V() & 1)
      outRect.LCol().V()++; // Start on even boundry in image.
    if(!(outRect.RCol().V() & 1))
      outRect.RCol().V()--; // End on odd boundry in image.
    assert(outRect.LCol() < outRect.RCol()); // Make sure there's something left!
    
    ImageC<ByteYUVValueC> ret(outRect);
    for(Array2dIter2C<ByteYUVValueC,ByteYUV422ValueC> it(ret,dat);it;it++) {
      SByteT u = it.Data2().UV() - 128;
      ByteT y1 = it.Data2().Y();
      ByteYUVValueC &p1 = it.Data1();
      it++;
      SByteT v = it.Data2().UV() - 128;
      p1 = ByteYUVValueC(y1,u,v);
      it.Data1() = ByteYUVValueC(it.Data2().Y(),u,v);
    }
    return ret;
  }
  
  DP_REGISTER_CONVERTION(ByteYUV422ImageCT2ByteYUVImageCT,1);
  DP_REGISTER_CONVERTION(ByteYUV422ImageCT2ByteImageCT,2);
  
  FileFormatStreamC<ImageC<ByteYUV422ValueC> > FileFormatStream_ImageC_ByteYUV422ValueC;
  FileFormatBinStreamC<ImageC<ByteYUV422ValueC> > FileFormatBinStream_ImageC_ByteYUV422ValueC;
  
  BinOStreamC &operator << (BinOStreamC &out,const ImageC<ByteYUV422ValueC> &img)
  { 
    out << img.Rectangle();
    
    IntT width = img.Cols() * 2;
    IndexC atrow = img.TRow();
    IndexC offset = img.LCol();
    IndexC brow = img.BRow();
    for(;atrow <= brow;atrow++)
      out.OBuff((const char *) &(img[atrow][offset]),width);  
    return out;
  }
  
  BinIStreamC &operator >> (BinIStreamC &in,ImageC<ByteYUV422ValueC> &img)
  { 
    ImageRectangleC rect;
    in >> rect;
    img = ImageC<ByteYUV422ValueC>(rect);
    
    IntT width = img.Cols() * 2;
    IndexC atrow = img.TRow();
    IndexC offset = img.LCol();
    
    IndexC brow = img.BRow();
    for(;atrow <= brow;atrow++)
      in.IBuff((char *) &(img[atrow][offset]),width);
    return in;
  }

}
