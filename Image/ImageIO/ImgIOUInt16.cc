// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlImage
//! file="Ravl/Image/ImageIO/ImgIOUInt16.cc"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
//#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/Image.hh"
//#include "Ravl/Array2dIter2.hh"
#include "Ravl/TypeName.hh"

namespace RavlN {

  void InitImgIOUInt16()
    {}
  
  static TypeNameC type1(typeid(ImageC<Int16T>),"ImageC<Int16T>");  
  static TypeNameC type2(typeid(ImageC<UInt16T>),"ImageC<UInt16T>");
  
  FileFormatStreamC<ImageC<UInt16T> > FileFormatStream_ImageC_UInt16T;
  FileFormatBinStreamC<ImageC<UInt16T> > FileFormatBinStream_ImageC_UInt16T;
  
}
