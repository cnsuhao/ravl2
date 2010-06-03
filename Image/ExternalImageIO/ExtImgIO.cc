// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id: ExtImgIO.cc 5006 2005-07-04 16:31:40Z craftit $"
//! lib=RavlExtImgIO
//! file="Ravl/Image/ExternalImageIO/ExtImgIO.cc"

#include "Ravl/Image/ExtImgIO.hh"

namespace RavlImageN {

  void ExtImgIO_Init() {
    InitJPEGCompressConv();
    InitTIFFFormat();
    InitJPEGFormat();
    InitPNGFormat();
  }
}
