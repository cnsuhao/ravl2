// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id: ImgIOByteYUV.cc 3700 2003-11-19 17:44:12Z craftit $"
//! lib=RavlImageIO
//! file="Ravl/Image/ImageIO/ImgIOByteYUV.cc"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/YCbCrBT601Value16.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/TypeName.hh"

namespace RavlImageN {
  
  void InitImgIOYCbCrBT601Value16() {
  }
  
  static TypeNameC type3(typeid(ImageC<YCbCrBT601Value16C>),"RavlImageN::ImageC<YCbCrBT601Value16C>");
  
  FileFormatStreamC<ImageC<YCbCrBT601Value16C> > FileFormatStream_ImageC_YCbCrBT601Value16C;
  FileFormatBinStreamC<ImageC<YCbCrBT601Value16C> > FileFormatBinStream_ImageC_YCbCrBT601Value16C;
  
}

