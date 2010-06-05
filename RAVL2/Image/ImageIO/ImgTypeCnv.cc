// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////
//! rcsid="$Id: ImgTypeCnv.cc 7074 2009-01-29 14:22:05Z ees1wc $"
//! lib=RavlImageIO
//! file="Ravl/Image/ImageIO/ImgTypeCnv.cc"

#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Array2dIter2.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Types.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/Image/ByteYUVValue.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/TypeName.hh"

namespace RavlImageN
{
  void InitStdImageCnv()
  {}
  
  static TypeNameC type1(typeid(ImageRectangleC),"RavlImageN::ImageRectangleC");
  
  static IndexRange2dC ImageRectangle2IndexRange(const ImageRectangleC &rect) 
  { return IndexRange2dC(rect); }
  
  static ImageRectangleC IndexRange2ImageRectangle(const IndexRange2dC &rect) 
  { return IndexRange2dC(rect); }
  
  DP_REGISTER_CONVERSION_NAMED(ImageRectangle2IndexRange   ,1,
			       "RavlN::IndexRange2dC RavlImageN::ImageRectangle2IndexRange(const RavlImageN::ImageRectangleC &)");

  DP_REGISTER_CONVERSION_NAMED(IndexRange2ImageRectangle   ,1,
			       "RavlImageN::ImageRectangleC RavlImageN::IndexRange2ImageRectangle(const RavlN::IndexRange2dC &)");
  
  
  // Handle converters.
  
  DP_REGISTER_CONVERSION_NAMED(ByteImageCT2ByteRGBImageCT   ,1,
			       "ImageC<ByteRGBValueC> RavlImageN::Convert(const ImageC<ByteT> &)");
  DP_REGISTER_CONVERSION_NAMED(RealImageCT2RealRGBImageCT   ,1,
			       "ImageC<RealRGBValueC> RavlImageN::Convert(const ImageC<RealT> &)");
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
