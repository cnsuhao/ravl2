// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLRGBCYUV_HEADER
#define RAVLRGBCYUV_HEADER 1
/////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! userlevel=Normal
//! docentry="Ravl.Images.Pixel Types"
//! lib=RavlImage
//! file="Ravl/Image/Base/RGBcYUV.hh"

#include "Ravl/TFMatrix.hh"
#include "Ravl/Image/RealYUVValue.hh"
#include "Ravl/Image/RealRGBValue.hh"

namespace RavlImageN {
  extern const TFMatrixC<RealT,3,3> ImageYUVtoRGBMatrix;
  // Matrix to convert YUV values to RGB.
  
  extern const TFMatrixC<RealT,3,3> ImageRGBtoYUVMatrixStd;
  // Matrix to convert YUV values to RGB.

  extern const TFMatrixC<RealT,3,3> ImageRGBtoYUVMatrix;
  // Matrix to convert YUV values to RGB.
  

  inline RealYUVValueC::RealYUVValueC(const RealRGBValueC &v) 
    : YUVValueC<RealT>(ImageRGBtoYUVMatrixStd * v)
  {}
  
  inline RealRGBValueC::RealRGBValueC(const RealYUVValueC &v) 
    : RGBValueC<RealT>(ImageYUVtoRGBMatrix * v)
  {}
  
}


#endif
