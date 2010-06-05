// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////
//! rcsid="$Id: ImgCnvYUV.cc 6624 2008-02-26 15:16:50Z ees1wc $"
//! lib=RavlImageIO
//! file="Ravl/Image/ImageIO/ImgCnvYUV.cc"

#include "Ravl/DP/Converter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Image/RealYUVValue.hh"
#include "Ravl/Image/ByteYUVAValue.hh"


namespace RavlImageN
{

  void InitYUVImageCnv()
  {}
  
  // Byte YUVA to Byte YUV 
  
  ImageC<ByteYUVValueC> ByteYUVAImageCT2ByteYUVImageCT(const ImageC<ByteYUVAValueC> &dat) {
    ImageC<ByteYUVValueC> ret(dat.Rectangle());
    for(Array2dIter2C<ByteYUVValueC,ByteYUVAValueC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = ByteYUVValueC(it.Data2().Y(),it.Data2().U(),it.Data2().V());
    return ret;
  }
  
  // Byte YUV to Byte YUVA 
  
  ImageC<ByteYUVAValueC> ByteYUVImageCT2ByteYUVAImageCT(const ImageC<ByteYUVValueC> &dat) {
    ImageC<ByteYUVAValueC> ret(dat.Rectangle());
    for(Array2dIter2C<ByteYUVAValueC,ByteYUVValueC> it(ret,dat);it.IsElm();it.Next()) {
      it.Data1() = ByteYUVAValueC(it.Data2().Y(),it.Data2().U(),it.Data2().V(),(char) 0xff);
    }
    return ret;
  }

  // Register conversions...
  DP_REGISTER_CONVERSION_NAMED(ByteYUVAImageCT2ByteYUVImageCT,1.25,
			       "ImageC<ByteYUVValueC> RavlImageN::Convert(const ImageC<ByteYUVAValueC> &)");
  DP_REGISTER_CONVERSION_NAMED(ByteYUVImageCT2ByteYUVAImageCT,1,
			       "ImageC<ByteYUVAValueC> RavlImageN::Convert(const ImageC<ByteYUVValueC> &)");
  
  //////////////////////////////////////////////////////////////////////////////////////////
  
  // Byte colour to real colour image.
  
  ImageC<RealYUVValueC> ByteYUVImageCT2RealYUVImageCT(const ImageC<ByteYUVValueC> &dat) {
    ImageC<RealYUVValueC> ret(dat.Rectangle());
    for(Array2dIter2C<RealYUVValueC,ByteYUVValueC> it(ret,dat);it.IsElm();it.Next()) {
      it.Data1() = RealYUVValueC(it.Data2().Y(),it.Data2().U(),it.Data2().V());
    }
    return ret;
  }
  
  // Real colour to byte colour image.

  ImageC<ByteYUVValueC> RealYUVImageCT2ByteYUVImageCT(const ImageC<RealYUVValueC> &dat) {
    ImageC<ByteYUVValueC> ret(dat.Rectangle());
    for(Array2dIter2C<ByteYUVValueC,RealYUVValueC> it(ret,dat);it.IsElm();it.Next()) {
      RealYUVValueC v(it.Data2());
      v.Limit(0,255);
      it.Data1() = ByteYUVValueC((ByteT)v.Y(),(ByteT)v.U(),(ByteT)v.V());
    }
    return ret;
  }
  
  DP_REGISTER_CONVERSION_NAMED(ByteYUVImageCT2RealYUVImageCT ,1,
			       "ImageC<RealYUVValueC> RavlImageN::Convert(const ImageC<ByteYUVValueC> &)");
  DP_REGISTER_CONVERSION_NAMED(RealYUVImageCT2ByteYUVImageCT ,8,
			       "ImageC<ByteYUVValueC> RavlImageN::Convert(const ImageC<RealYUVValueC> &)");
  
}
