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
//! file="Ravl/Image/ImageIO/ImgIOByte.cc"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/Stream.hh"
#include "Ravl/FunctionRegister.hh"

#ifdef __sgi__
istream &operator>>(istream &s,RavlN::SByteT b) {
  s >> ((signed char &) b);
  return s;
}
#endif

namespace RavlImageN {
  
  void InitImgIOByte()
  {}
  
  static TypeNameC type1(typeid(ImageC<ByteT>),"ImageC<ByteT>");  
  static TypeNameC type2(typeid(ImageC<SByteT>),"ImageC<SByteT>");
  
  ImageC<ByteT>  DPConvBoolImageC2ByteImageCT(const ImageC<bool> &dat)   { 
    ImageC<ByteT> ret(dat.Rectangle()); 
    for(Array2dIter2C<ByteT,bool> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = it.Data2() ? 255 : 0;
    return ret;
  }
  
  DP_REGISTER_CONVERTION_NAMED(DPConvBoolImageC2ByteImageCT,1,
			       "ImageC<ByteT>  RavlImageN::Convert(const ImageC<bool> &)");
  
  FileFormatStreamC<ImageC<ByteT> > FileFormatStream_ImageC_ByteT;
  FileFormatBinStreamC<ImageC<ByteT> > FileFormatBinStream_ImageC_ByteT;
  FileFormatStreamC<ImageC<SByteT> > FileFormatStream_ImageC_SByteT;
  FileFormatBinStreamC<ImageC<SByteT> > FileFormatBinStream_ImageC_SByteT;
  
  /// ByteT ////////////////////////////////////////////////////////////////////////
  
  BinOStreamC &operator << (BinOStreamC &out,const ImageC<ByteT> &img) { 
    out << img.Rectangle();
    
    IntT width = img.Cols();
    IndexC atrow = img.TRow();
    IndexC offset = img.LCol();
    
    IndexC brow = img.BRow();
    for(;atrow <= brow;atrow++) 
      out.OBuff((const char *) &(img[atrow][offset]),width);  
    return out;
  }
  
  BinIStreamC &operator >> (BinIStreamC &in,ImageC<ByteT> &img) { 
    ImageRectangleC rect;
    in >> rect;
    img = ImageC<ByteT>(rect);
    
    IntT width = img.Cols();
    IndexC atrow = img.TRow();
    IndexC offset = img.LCol();
    IndexC brow = img.BRow();
    for(;atrow <= brow;atrow++) 
      in.IBuff((char *) &(img[atrow][offset]),width);  
    return in;
  }

}
