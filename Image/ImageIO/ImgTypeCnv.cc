// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImageIO
//! file="Ravl/Image/ImageIO/ImgTypeCnv.cc"

#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Array2dIter2.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Types.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Image/ImageConv.hh"

namespace RavlImageN
{
  void InitStdImageCnv()
  {}
  
  // Handle converters.
  
  DP_REGISTER_CONVERSION_NAMED(ByteImageCT2ByteRGBImageCT   ,1,
			       "ImageC<ByteRGBValueC> RavlImageN::Convert(const ImageC<ByteT> &)");
  DP_REGISTER_CONVERSION_NAMED(ByteImageCT2ByteYUVImageCT   ,1,
			       "ImageC<ByteYUVValueC> RavlImageN::Convert(const ImageC<ByteT> &)");
  DP_REGISTER_CONVERSION_NAMED(ByteImageCT2IntImageCT       ,1,
			       "ImageC<IntT> RavlImageN::Convert(const ImageC<ByteT> &)");
  DP_REGISTER_CONVERSION_NAMED(ByteImageCT2DoubleImageCT    ,1,
			       "ImageC<RealT> RavlImageN::Convert(const ImageC<ByteT> &)");
  DP_REGISTER_CONVERSION_NAMED(DoubleImageCT2ByteImageCT    ,8,
			       "ImageC<ByteT> RavlImageN::Convert(const ImageC<RealT> &)");
  DP_REGISTER_CONVERSION_NAMED(IntImageCT2DoubleImageCT     ,1,
			       "ImageC<RealT> RavlImageN::Convert(const ImageC<IntT> &)");

}
