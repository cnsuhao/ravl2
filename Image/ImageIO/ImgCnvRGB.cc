// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImage

#include "Ravl/DP/Converter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/UInt16RGBValue.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/Image/ByteRGBAValue.hh"


namespace RavlImageN
{

  void InitRGBImageCnv()
  {}
  
  // Byte RGBA to Byte RGB 
  
  ImageC<ByteRGBValueC> ByteRGBAImageCT2ByteRGBImageCT(const ImageC<ByteRGBAValueC> &dat) {
    ImageC<ByteRGBValueC> ret(dat.Rectangle());
    for(Array2dIter2C<ByteRGBValueC,ByteRGBAValueC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = ByteRGBValueC(it.Data2().Red(),it.Data2().Green(),it.Data2().Blue());
    return ret;
  }
  
  // Byte RGB to Byte RGBA 
  
  ImageC<ByteRGBAValueC> ByteRGBImageCT2ByteRGBAImageCT(const ImageC<ByteRGBValueC> &dat) {
    ImageC<ByteRGBAValueC> ret(dat.Rectangle());
    for(Array2dIter2C<ByteRGBAValueC,ByteRGBValueC> it(ret,dat);it.IsElm();it.Next()) {
      it.Data1() = ByteRGBAValueC(it.Data2().Red(),it.Data2().Green(),it.Data2().Blue(),(char) 0xff);
    }
    return ret;
  }

  // Register conversions...
  DP_REGISTER_CONVERTION(ByteRGBAImageCT2ByteRGBImageCT,1.25);
  DP_REGISTER_CONVERTION(ByteRGBImageCT2ByteRGBAImageCT,1);

  //////////////////////////////////////////////////////////////////////////////////////////
  
  // Byte colour to real colour image.
  
  ImageC<RealRGBValueC> ByteRGBImageCT2RealRGBImageCT(const ImageC<ByteRGBValueC> &dat) {
    ImageC<RealRGBValueC> ret(dat.Rectangle());
    for(Array2dIter2C<RealRGBValueC,ByteRGBValueC> it(ret,dat);it.IsElm();it.Next()) {
      it.Data1() = RealRGBValueC(it.Data2().Red(),it.Data2().Green(),it.Data2().Blue());
    }
    return ret;
  }
  
  // Real colour to byte colour image.

  ImageC<ByteRGBValueC> RealRGBImageCT2ByteRGBImageCT(const ImageC<RealRGBValueC> &dat) {
    ImageC<ByteRGBValueC> ret(dat.Rectangle());
    for(Array2dIter2C<ByteRGBValueC,RealRGBValueC> it(ret,dat);it.IsElm();it.Next()) {
      RealRGBValueC v(it.Data2());
      v.Limit(0,255);
      it.Data1() = ByteRGBValueC((ByteT)v.Red(),(ByteT)v.Green(),(ByteT)v.Blue());
    }
    return ret;
  }
  
  DP_REGISTER_CONVERTION(ByteRGBImageCT2RealRGBImageCT ,1);
  DP_REGISTER_CONVERTION(RealRGBImageCT2ByteRGBImageCT ,8);

  /////////////////////////////////////////////////////////////////////////////////////////
  
  // Byte colour to UInt16 colour image.
  
  ImageC<UInt16RGBValueC> ByteRGBImageCT2UInt16RGBValueCImageCT(const ImageC<ByteRGBValueC> &dat) {
    ImageC<UInt16RGBValueC> ret(dat.Rectangle());
    for(Array2dIter2C<UInt16RGBValueC,ByteRGBValueC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = UInt16RGBValueC(it.Data2().Red(),it.Data2().Green(),it.Data2().Blue());
    return ret;
  }
  
  //  UInt16 colour image to Byte colour.
  
  ImageC<ByteRGBValueC> UInt16RGBValueCImageCT2ByteRGBImageCT(const ImageC<UInt16RGBValueC> &dat) {
    ImageC<ByteRGBValueC> ret(dat.Rectangle());
    for(Array2dIter2C<ByteRGBValueC,UInt16RGBValueC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = ByteRGBValueC(it.Data2().Red(),it.Data2().Green(),it.Data2().Blue());
    return ret;
  }
  
  // Register conversions...
  
  DP_REGISTER_CONVERTION(ByteRGBImageCT2UInt16RGBValueCImageCT,1);
  DP_REGISTER_CONVERTION(UInt16RGBValueCImageCT2ByteRGBImageCT,2);
  
  
}
