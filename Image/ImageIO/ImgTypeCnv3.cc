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


namespace RavlImageN
{
  void InitStdImageCnv3()
  {}

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
  
  DP_REGISTER_CONVERSION_NAMED(RealRGBAverageImageC2ByteRGBImageCT,1,
			       "ImageC<ByteRGBValueC>  RavlImageN::Convert(const ImageC<RealRGBAverageC> &)");

  DP_REGISTER_CONVERSION_NAMED(ByteRGBMedianImageC2ByteRGBImageCT,1,
			       "ImageC<ByteRGBValueC>  RavlImageN::Convert(const ImageC<ByteRGBMedianC> &)");
  
}
