// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImageIO
//! file="Ravl/Image/ImageIO/ImgTypeCnv3.cc"

#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Types.hh"
#include "Ravl/Image/ByteRGBMedian.hh"
#include "Ravl/Image/RealRGBAverage.hh"
#include "Ravl/Image/RealHSVValue.hh"
#include "Ravl/TypeName.hh"

namespace RavlImageN
{
  void InitStdImageCnv3()
  {}

  static TypeNameC type1(typeid(ImageC<RealRGBAverageC>),"ImageC<RealRGBAverageC>");  
  static TypeNameC type2(typeid(ImageC<ByteRGBMedianC>),"ImageC<ByteRGBMedianC>");  
  static TypeNameC type3(typeid(ImageC<RealHSVValueC>),"ImageC<RealHSVValueC>");  
  
  // Real RGB rolling average -> RGB

  ImageC<ByteRGBValueC>  RealRGBAverageImageC2ByteRGBImageCT(const ImageC<RealRGBAverageC> &dat)   { 
    ImageC<ByteRGBValueC> ret(dat.Rectangle()); 
    for(Array2dIter2C<ByteRGBValueC,RealRGBAverageC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = it.Data2();
    return ret;
  }

  // Byte RGB median -> RGB

  ImageC<ByteRGBValueC>  ByteRGBMedianImageC2ByteRGBImageCT(const ImageC<ByteRGBMedianC> &dat)   { 
    ImageC<ByteRGBValueC> ret(dat.Rectangle()); 
    for(Array2dIter2C<ByteRGBValueC,ByteRGBMedianC> it(ret,dat);it.IsElm();it.Next()) 
      it.Data1() = it.Data2();
    return ret;
  }
  

 
  // Real RGB to Real HLS 
  ImageC<RealHSVValueC> RealRGBImageCT2RealHSVImageCT(const ImageC<RealRGBValueC> & dat) {
    ImageC<RealHSVValueC> ret(dat.Rectangle() ) ;
    for(Array2dIter2C<RealHSVValueC,RealRGBValueC> it(ret,dat);it.IsElm();it.Next()) {
      RealHSVValueC v( it.Data2() ) ;
      it.Data1() = v ;}
    return ret ;
  }
  
  // Real HLS to Real RGB 
  ImageC<RealRGBValueC> RealHSVImageCT2RealRGBImageCT(const ImageC<RealHSVValueC> & dat ) {
    ImageC<RealRGBValueC> ret ( dat.Rectangle() ) ;
    for(Array2dIter2C<RealRGBValueC,RealHSVValueC> it(ret,dat);it.IsElm();it.Next()) {
      it.Data1() = (it.Data2().RGB() ) ;}
      return ret ;
  }


  DP_REGISTER_CONVERSION_NAMED(RealRGBAverageImageC2ByteRGBImageCT,1,
			       "ImageC<ByteRGBValueC>  RavlImageN::Convert(const ImageC<RealRGBAverageC> &)");

  DP_REGISTER_CONVERSION_NAMED(ByteRGBMedianImageC2ByteRGBImageCT,1,
			       "ImageC<ByteRGBValueC>  RavlImageN::Convert(const ImageC<ByteRGBMedianC> &)");
  
  DP_REGISTER_CONVERSION_NAMED(RealRGBImageCT2RealHSVImageCT,1,
			       "ImageC<RealHSVValueC> RavlImageN::Convert(const ImageC<RealRGBValueC> &)");
  
  DP_REGISTER_CONVERSION_NAMED(RealHSVImageCT2RealRGBImageCT,1,
			       "ImageC<RealRGBValueC> RavlImageN::Convert(const ImageC<RealHSVValueC> &)");

}
