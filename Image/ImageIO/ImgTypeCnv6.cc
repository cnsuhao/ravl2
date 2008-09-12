// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! rcsid="$Id: ImgTypeCnv5.cc 3700 2003-11-19 17:44:12Z craftit $"
//! lib=RavlImageIO
//! file="Ravl/Image/ImageIO/ImgTypeCnv5.cc"
//! author="Charles Galambos"

#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Types.hh"
#include "Ravl/Image/RGBValue.hh"
#include "Ravl/Image/YCbCrBT601Value.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/Array2dIter2.hh"

namespace RavlImageN
{
  void InitStdImageCnv6()
  {}
  
  DP_REGISTER_CONVERSION_NAMED(YCbCrBT601ValueFloatImage2ImageRGBValueFloat,1,
			       "RavlImageN::ImageC<RavlImageN::RGBValueC<float> > RavlImageN::YCbCrBT601ValueFloatImage2ImageRGBValueFloat(const RavlImageN::ImageC<RavlImageN::YCbCrBT601ValueC<float> > &)");

  DP_REGISTER_CONVERSION_NAMED(ImageRGBValueFloat2YCbCrBT601ValueFloatImage,1,
			       "RavlImageN::ImageC<YCbCrBT601ValueC<float> > RavlImageN::ImageRGBValueFloat2YCbCrBT601ValueFloatImage(const RavlImageN::ImageC<RavlImageN::RGBValueC<float> > &dat)");
  
  
}
