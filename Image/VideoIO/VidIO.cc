//////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Image/VidIO.hh"
#include "Ravl/Image/ImgIO.hh"

namespace RavlImageN {

  void InitVidIO() {
    InitDPImageIO();
    InitRawIOFormat();
    InitCifFormat();
    InitYUVFormat();
    InitRGBFormat();
    InitSYUVFormat();
    // InitImgIOComposites(); 
  }
}

