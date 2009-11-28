// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DVSRGBCDVSYUV422_HEADER
#define RAVL_DVSRGBCDVSYUV422_HEADER 1
/////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! docentry="Ravl.API.Images.Pixel Types.YCbCr"
//! lib=RavlImage
//! file="Ravl/Image/Base/DVSRGBcDVSYUV422.hh"

#include "Ravl/TFMatrix.hh"
#include "Ravl/Image/RealYUVValue.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/Image/RealDVSYUVValue.hh"
#include "Ravl/Image/RealDVSRGBValue.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/CompilerHints.hh"

namespace RavlImageN {
  extern const TFMatrixC<RealT,3,3> ImageDVSYUV422toDVSRGBMatrix;
  // Matrix to convert DVSYUV422 values to DVSRGB.
  
  extern const TFMatrixC<RealT,3,3> ImageDVSRGBtoDVSYUV422MatrixStd;
  // Matrix to convert DVSYUV422 values to DVSRGB.

  extern const TFMatrixC<RealT,3,3> ImageDVSRGBtoDVSYUV422Matrix;
  // Matrix to convert DVSYUV422 values to DVSRGB.
  
  inline RealDVSYUVValueC::RealDVSYUVValueC(const RealRGBValueC &v) 
  { 
  Mul(ImageDVSRGBtoDVSYUV422MatrixStd,v,*this); 
  }
  
  inline RealDVSRGBValueC::RealDVSRGBValueC(const RealYUVValueC &v) 
  { 
   Mul(ImageDVSYUV422toDVSRGBMatrix,v,*this); 
  }


  extern const IntT *DVSRGBcDVSYUV422_ubLookup;
  extern const IntT *DVSRGBcDVSYUV422_vrLookup;
  extern const IntT *DVSRGBcDVSYUV422_uvgLookup;
  
  inline void ByteDVSYUV4222DVSRGB(ByteT y,SByteT u,SByteT v,ByteRGBValueC &pix) {
    register IntT iy = (IntT) y;
    register IntT iu = (IntT) u;
    register IntT rv = (IntT) v;
    register IntT tmp;
    tmp = iy + DVSRGBcDVSYUV422_vrLookup[v];
    if(RAVL_EXPECT(tmp < 0,0)) tmp = 0;
    if(RAVL_EXPECT(tmp > 255,0)) tmp = 255;
    pix[0] = (ByteT) tmp;
    
    tmp = iy + DVSRGBcDVSYUV422_uvgLookup[iu + 256 * rv];
    if(RAVL_EXPECT(tmp < 0,0)) tmp = 0;
    if(RAVL_EXPECT(tmp > 255,0)) tmp = 255;
    pix[1] = (ByteT) tmp;
    
    tmp = iy + DVSRGBcDVSYUV422_ubLookup[u];
    if(RAVL_EXPECT(tmp < 0,0)) tmp = 0;
    if(RAVL_EXPECT(tmp > 255,0)) tmp = 255;
    pix[2] = (ByteT) tmp;
  }
  //: Convert byte DVSYUV422 values to byte DVSRGB value.
  
  inline void ByteDVSYUV4222DVSRGB2(ByteT y1,ByteT y2,SByteT u,SByteT v,ByteRGBValueC &pix1,ByteRGBValueC &pix2) {

    register IntT iy1 = (IntT) y1;
    register IntT iy2 = (IntT) y2;
    register IntT iu = (IntT) u;
    register IntT iv = (IntT) v;
    
    register IntT tmp;
    register IntT vr = DVSRGBcDVSYUV422_vrLookup[iv];
    tmp = iy1 + vr;
    if(RAVL_EXPECT(tmp < 0,0)) tmp = 0;
    if(RAVL_EXPECT(tmp > 255,0)) tmp = 255;
    pix1[0] = (ByteT) tmp;

    tmp = iy2 + vr;
    if(RAVL_EXPECT(tmp < 0,0)) tmp = 0;
    if(RAVL_EXPECT(tmp > 255,0)) tmp = 255;
    pix2[0] = (ByteT) tmp;

    register IntT uvg = DVSRGBcDVSYUV422_uvgLookup[iu + 256 * iv];

    tmp = iy1 + uvg;
    if(RAVL_EXPECT(tmp < 0,0)) tmp = 0;
    if(RAVL_EXPECT(tmp > 255,0)) tmp = 255;
    pix1[1] = (ByteT) tmp;

    tmp = iy2 + uvg;
    if(RAVL_EXPECT(tmp < 0,0)) tmp = 0;
    if(RAVL_EXPECT(tmp > 255,0)) tmp = 255;
    pix2[1] = (ByteT) tmp;

    register IntT ub = DVSRGBcDVSYUV422_ubLookup[iu];
    
    tmp = iy1 + ub;
    if(RAVL_EXPECT(tmp < 0,0)) tmp = 0;
    if(RAVL_EXPECT(tmp > 255,0)) tmp = 255;
    pix1[2] = (ByteT) tmp;

    tmp = iy2 + ub;
    if(RAVL_EXPECT(tmp < 0,0)) tmp = 0;
    if(RAVL_EXPECT(tmp > 255,0)) tmp = 255;
    pix2[2] = (ByteT) tmp;

  }
  //: Convert byte DVSYUV422 values to byte DVSRGB value.
  
}


#endif
