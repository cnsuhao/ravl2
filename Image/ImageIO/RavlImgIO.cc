// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImage


#include "Ravl/Image/ImgIO.hh"

namespace RavlN {
  void InitDPImageIO(){
#if 0
    InitStdImageCnv();
    InitStdImageCnv2();
    InitFrameImageCnv();
#endif    
    InitPNMFormat();
    InitImgIOInt();
#if 0
    InitImgIOByte();
    InitImgIOReal();
    InitImgIOUInt16();
    
    InitImgIOByteRGB();
    InitImgIORealRGB();
    InitImgIOU16RGB();
    
    InitImgIOByteYUV();
    InitImgIOByteVYU();
    InitImgIORealYUV();
    
    InitRGBImageCnv();
    InitRGB16ImageCnv();
    
    InitCompatIORGB();
    InitCompatIOYUV();
    InitCompatIOY();
    
    InitPixelIO();
#endif
  }
}
  
