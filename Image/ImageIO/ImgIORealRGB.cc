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
//! file="Ravl/Image/ImageIO/ImgIORealRGB.cc"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/TypeName.hh"
//#include "Ravl/DP/Converter.hh"
//#include "Ravl/Array2dIter2.hh"

namespace RavlImageN {
  
  void InitImgIORealRGB()
  {}
  
  static TypeNameC type1(typeid(ImageC<RealRGBValueC>),"ImageC<RealRGBValueC>");  
  
  FileFormatStreamC<ImageC<RealRGBValueC> > FileFormatStream_ImageC_RealRGBValueC;
  FileFormatBinStreamC<ImageC<RealRGBValueC> > FileFormatBinStream_ImageC_RealRGBValueC;
}
