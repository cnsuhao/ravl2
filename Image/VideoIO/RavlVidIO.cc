// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id: RavlVidIO.cc 2626 2003-03-31 16:23:16Z craftit $"
//! lib=RavlVideoIO
//! file="Ravl/Image/VideoIO/RavlVidIO.cc"

#include "Ravl/Image/VidIO.hh"
#include "Ravl/Image/ImgIO.hh"

namespace RavlImageN {
  
  void InitVidIO() {
    //InitDPImageIO();
    InitRawIOFormat();
    InitCifFormat();
    InitYUVFormat();
    InitRGBFormat();
    InitSYUVFormat();
    InitJSFormat();
    InitAviFormat();
    // InitImgIOComposites(); 
  }
}

