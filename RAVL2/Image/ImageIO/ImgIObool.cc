// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id: ImgIObool.cc 130 2001-05-24 22:50:53Z craftit $"
//! lib=RavlImage

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/TypeName.hh"

namespace RavlImageN {
  
  static TypeNameC type1(typeid(ImageC<bool>),"ImageC<bool>");  
  
  void InitImgIOBool()
  {}
  
  FileFormatStreamC<ImageC<bool> > FileFormatStream_ImageC_bool;
  FileFormatBinStreamC<ImageC<bool> > FileFormatBinStream_ImageC_bool;
  
}
