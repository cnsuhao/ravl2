// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImage

#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Array2dIter2.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Types.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/Image/RealYUVValue.hh"
#include "Ravl/Image/RGBcYUV.hh"


namespace RavlImageN
{
  void InitStdImageCnv2()
  {}
  

  // Real YUV -> RGB
  
  ImageC<RealRGBValueC> RealYUVImageCT2RealRGBImageCT(const ImageC<RealYUVValueC> &dat) {
    ImageC<RealRGBValueC> ret(dat.Rectangle());
    for(Array2dIter2C<RealRGBValueC,RealYUVValueC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = RealRGBValueC(it.Data2());
    return ret;
  }


  // Real RGB -> YUV

  ImageC<RealYUVValueC> RealRGBImageCT2RealYUVImageCT(const ImageC<RealRGBValueC> &dat) {
    ImageC<RealYUVValueC> ret(dat.Rectangle());
    for(Array2dIter2C<RealYUVValueC,RealRGBValueC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = RealRGBValueC(it.Data2());
    return ret;
  }


  // Byte grey level to byte YUV colour image.
  ImageC<ByteT> ByteYUVImageCT2ByteImageCT(const ImageC<ByteYUVValueC> &dat) { 
    ImageC<ByteT> ret(dat.Rectangle());
    for(Array2dIter2C<ByteT,ByteYUVValueC> it(ret,dat);it.IsElm();it.Next())
      it.Data1() = it.Data2().Y();
    return ret;  
  }

  // Byte colour to byte grey image.
  
  ImageC<ByteT> RGBImageCT2ByteImageCT(const ImageC<ByteRGBValueC> &dat) {
    ImageC<ByteT> ret(dat.Rectangle());
    for(Array2dIter2C<ByteT,ByteRGBValueC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = (ByteT) ((IntT) ((IntT) it.Data2().Red() + it.Data2().Green() + it.Data2().Blue()) / 3);
    return ret;
  }
  // Byte Colour to double image.

  ImageC<RealT> RGBImageCT2DoubleImageCT(const ImageC<ByteRGBValueC> &dat)  { 
    ImageC<RealT> ret(dat.Rectangle());
    for(Array2dIter2C<RealT,ByteRGBValueC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = (RealT) ((RealT) it.Data2().Red() + it.Data2().Green() + it.Data2().Blue()) / 3;
    return ret;
  }
  
  // Byte YUV to byte RGB image.

  ImageC<ByteRGBValueC> YUVImageCT2RGBImageCT(const ImageC<ByteYUVValueC> &dat) {
    ImageC<ByteRGBValueC> ret(dat.Rectangle());
    for(Array2dIter2C<ByteRGBValueC,ByteYUVValueC> it(ret,dat);it.IsElm();it.Next()) {
      RealRGBValueC p(RealYUVValueC(it.Data2()));
      p.Limit(0,255);
      it.Data1() = ByteRGBValueC(p.Red(),p.Green(),p.Blue());
    }
    return ret;
  }

  // Byte RGB to byte YUV image.
  
  ImageC<ByteYUVValueC> RGBImageCT2YUVImageCT(const ImageC<ByteRGBValueC> &dat) {
    ImageC<ByteYUVValueC> ret(dat.Rectangle());
    for(Array2dIter2C<ByteYUVValueC,ByteRGBValueC> it(ret,dat);it.IsElm();it.Next()) {
      RealYUVValueC v(RealRGBValueC(it.Data2()));
      v.Limit(0,255);
      it.Data1() = ByteYUVValueC(v.Y(),v.U(),v.V());
    }
    return ret;
  }

  
  DP_REGISTER_CONVERTION(ByteYUVImageCT2ByteImageCT   ,3);
  DP_REGISTER_CONVERTION(YUVImageCT2RGBImageCT              ,1);
  DP_REGISTER_CONVERTION(RGBImageCT2YUVImageCT              ,1);
  
  DP_REGISTER_CONVERTION(RGBImageCT2DoubleImageCT     ,3);
  DP_REGISTER_CONVERTION(RGBImageCT2ByteImageCT       ,3.1);
  
  DP_REGISTER_CONVERTION(RealYUVImageCT2RealRGBImageCT,1);
  DP_REGISTER_CONVERTION(RealRGBImageCT2RealYUVImageCT,1);
  
}
