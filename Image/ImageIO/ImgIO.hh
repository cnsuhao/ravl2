// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef IMGIOINIT_HEADER
#define IMGIOINIT_HEADER 1
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/ImageIO/ImgIO.hh"
//! lib=RavlImage
//! userlevel=Advanced
//! docentry="Ravl.Images.IO"
//! author="Charles Galambos"
//! date="13/05/99"

namespace RavlN {
  extern void InitDPImageIO(); // This calls all the following functions.
  
  extern void InitStdImageCnv();
  extern void InitStdImageCnv2();
  extern void InitStdImageCnv3();
  extern void InitPNMFormat();
  extern void InitImgIOByte();
  extern void InitImgIObool();
  extern void InitImgIOReal();
  extern void InitImgIOInt();
  extern void InitImgIOUInt16();
  extern void InitImgIOUInt16RGB();
  extern void InitImgIOByteRGB();
  extern void InitImgIORealRGB();
  extern void InitImgIOByteRGBA();
  extern void InitImgIOByteYUV();
  extern void InitImgIORealYUV();
  extern void InitRGBImageCnv();
  extern void InitRGB16ImageCnv();
  extern void InitImgIOU16RGB();
  extern void InitPixelIO();
  extern void InitImgIOByteVYU();
  extern void InitFrameImageCnv();

  extern void InitCompatIORGB();
  extern void InitCompatIOYUV();
  extern void InitCompatIOY();
}
#endif
