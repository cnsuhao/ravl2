// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Radek Marik"
//! lib=RavlImage
//! file="Ravl/Image/Base/RGBcYUV.cc"

#include "Ravl/Image/RGBcYUV.hh"
#include "Ravl/Image/RealYUVValue.hh"
#include "Ravl/Image/RealRGBValue.hh"

namespace RavlImageN {
  
  // These are taken directly from the equivelent amma code.
  // they probably could do with some checking.

  static const RealT Init_YUVtoRGB_Matrix[] = {1.000,  0.000,  1.140,
					       1.000, -0.395, -0.581,
					       1.000,  2.032,  0.000};
  
  const TFMatrixC<RealT,3,3> ImageYUVtoRGBMatrix(Init_YUVtoRGB_Matrix);
  
  static const RealT Init_RGBtoYUV_Matrix[] = { 0.299,  0.587,  0.114,
					       -0.148, -0.289,  0.437,
					        0.615, -0.515, -0.100 };
  
  
  const TFMatrixC<RealT,3,3> ImageRGBtoYUVMatrixStd(Init_RGBtoYUV_Matrix );
  
  const TFMatrixC<RealT,3,3> ImageRGBtoYUVMatrix(ImageRGBtoYUVMatrixStd * ((1./1.175)));

  //: This has been taken from the AMMA code.
  // Is it right ??
  



  //     y       u       v
  // r   1.000,  0.000,  1.140,
  // g   1.000, -0.395, -0.581,
  // b   1.000,  2.032,  0.000};

  IntT *UBLookup() {
    static IntT values[256];
    IntT *off = &(values[128]);
    for(int i = -128;i < 128;i++)
      off[i] = Round((RealT) i * 2.032);
    return off;
  }

  IntT *VRLookup() {
    static IntT values[256];
    IntT *off = &(values[128]);
    for(int i = -128;i < 128;i++)
      off[i] = Round((RealT) i * 1.140);
    return off;
  }

  IntT *UVGLookup() {
    static IntT values[256 * 256];
    for(int u = 0;u < 256;u++)
      for(int v = 0;v < 256;v++)
	values[u + 256 * v] = Round((RealT) (u-128) * -0.395 + (RealT) (v-128) * -0.581);
    return &(values[128 + 256 * 128]);
  }
  
  const IntT *RGBcYUV_ubLookup = UBLookup();
  const IntT *RGBcYUV_vrLookup = VRLookup();
  const IntT *RGBcYUV_uvgLookup = UVGLookup();

}


