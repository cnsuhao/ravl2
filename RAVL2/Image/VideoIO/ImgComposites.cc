// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! rcsid="$Id: ImgComposites.cc 130 2001-05-24 22:50:53Z craftit $"
//! lib=RavlImage

#include "Ravl/DP/FileFormatComposite.hh"
#include "Ravl/Image/YUVValue.hh"
#include "Ravl/Image/RGBValue.hh"
#include "Ravl/Image/Image.hh"

namespace RavlImageN {
  void InitImgIOComposites()
  {}
  
  FileFormatCompositeC<ImageC<ByteRGBValueC> > FileFormatComposite_ImageC_ByteRGBValue;
  FileFormatCompositeC<ImageC<ByteYUVValueC> > FileFormatComposite_ImageC_ByteYUVValue;
  FileFormatCompositeC<ImageC<ByteGreyValueT> > FileFormatComposite_ImageC_ByteGreyValueT;
}
