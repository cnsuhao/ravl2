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

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/Image/Image.hh"
//#include "Ravl/DP/Converter.hh"
//#include "Ravl/Array2dIter2.hh"
#include "Ravl/TypeName.hh"

namespace RavlN {

  void InitImgIOReal()
  {}
  
  static TypeNameC type1(typeid(ImageC<RealT>),"ImageC<RealT>");  
  
  FileFormatStreamC<ImageC<RealT> > FileFormatStream_ImageC_RealT;
  FileFormatBinStreamC<ImageC<RealT> > FileFormatBinStream_ImageC_RealT;
}
