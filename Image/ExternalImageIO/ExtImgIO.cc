//////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/Image/ExtImgIO.hh"

void ExtImgIO_Init() {
  InitTIFFFormat();
  InitJPEGFormat();
  InitPNGFormat();
}
