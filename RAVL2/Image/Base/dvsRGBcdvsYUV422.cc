// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="se"
//! lib=RavlImage
//! file="Ravl/Image/Base/dvsRGBcdvsYUV422.cc"

#include "Ravl/Image/dvsRGBcdvsYUV422.hh"
#include "Ravl/Image/RealYUVValue.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/Image/RealDVSYUVValue.hh"
#include "Ravl/Image/RealDVSRGBValue.hh"

namespace RavlImageN {
  
  /*
   From DVSRGB to DVSYUV422, the definition comes from the DVS capture cards.

   Y = 0.212R + 0.715G + 0.072B
   U = 0.511 (B-Y)
   V = 0.511 (R-Y)
  */

  static const RealT Init_DVSRGBtoDVSYUV422_Matrix[] =
    { 0.21259,		0.71521,	0.07220,
     -0.11719, 	 	-0.39423, 	0.51141,
      0.51141,		-0.46454,	-0.04688};
  
  
  const TFMatrixC<RealT,3,3> ImageDVSRGBtoDVSYUV422MatrixStd(Init_DVSRGBtoDVSYUV422_Matrix );
  
  // So from DVSYUV422 to DVSRGB should just be the inverse:

  static const RealT Init_DVSYUV422toDVSRGB_Matrix[] =
    {1.00000,	0.00000,	1.53967,
     1.00000,  -0.18317,	-0.45764,
     1.00000,	1.81421,	0.00000};
  
  const TFMatrixC<RealT,3,3> ImageDVSYUV422toDVSRGBMatrix(Init_DVSYUV422toDVSRGB_Matrix);
  
  const TFMatrixC<RealT,3,3> ImageDVSRGBtoDVSYUV422Matrix(ImageDVSRGBtoDVSYUV422MatrixStd * ((1./1.175)));


  IntT *UBDVSLookup() {
    static IntT values[256];
    IntT *off = &(values[128]);
        for(int i = -128;i < 128;i++) {
           off[i] = Round((RealT) i * 1.81421);
        }
    return off;
  }

  IntT *VRDVSLookup() {
    static IntT values[256];
    IntT *off = &(values[128]);
    for(int i = -128;i < 128;i++) {
      off[i] = Round((RealT) i * 1.53967);
    }
    return off;
  }

  IntT *UVGDVSLookup() {
    static IntT values[256 * 256];
    for(int u = 0;u < 256;u++)
      for(int v = 0;v < 256;v++)
	values[u + 256 * v] = Round((RealT) (u-128) * -0.18317 + (RealT) (v-128) * -0.45764);
    return &(values[128 + 256 * 128]);
  }
  
  const IntT *DVSRGBcDVSYUV422_ubLookup = UBDVSLookup();
  const IntT *DVSRGBcDVSYUV422_vrLookup = VRDVSLookup();
  const IntT *DVSRGBcDVSYUV422_uvgLookup = UVGDVSLookup();

}


