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
//! file="Ravl/Image/ImageIO/ImgIOByteYUV.cc"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/UInt16YCbCrBT709Value.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/TypeName.hh"

namespace RavlImageN {
  
  void InitImgIOUInt16YCbCrBT709Value() {
  }
  
  static TypeNameC type3(typeid(ImageC<UInt16YCbCrBT709ValueC>),"RavlImageN::ImageC<UInt16YCbCrBT709ValueC>");
  
  FileFormatStreamC<ImageC<UInt16YCbCrBT709ValueC> > FileFormatStream_ImageC_UInt16YCbCrBT709ValueC;
  FileFormatBinStreamC<ImageC<UInt16YCbCrBT709ValueC> > FileFormatBinStream_ImageC_UInt16YCbCrBT709ValueC;
  
}

