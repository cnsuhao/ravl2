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

#include "Ravl/Image/RGBcYUV.hh"
#include "Ravl/Image/RealYUVValue.hh"
#include "Ravl/Image/RealRGBValue.hh"

namespace RavlImageN {
  
  static const RealT Init_YUVtoRGB_Matrix[] = {0.299,  0.587,  0.114,
					       -0.148, -0.289,  0.437,
					       0.615, -0.515, -0.100 };
  
  const TFMatrixC<RealT,3,3> ImageYUVtoRGBMatrix(Init_YUVtoRGB_Matrix);
  
  const TFMatrixC<RealT,3,3> ImageRGBtoYUVMatrix((1./1.175) * ImageYUVtoRGBMatrix);
  //: This has been taken from the AMMA code.
  // Is it right ??
  
}


