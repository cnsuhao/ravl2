// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_GRADIENT_HEADER
#define RAVLIMAGE_GRADIENT_HEADER 1
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.API.Images.Edges"
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Edges/Gradient.hh"

#include "Ravl/Vector2d.hh"
#include "Ravl/Array2d.hh"

namespace RavlImageN {
  using namespace RavlN;
  
  template<class DataT>
  Vector2dC SobelGradient3(const Array2dC<DataT> &img,const Index2dC &pos) {
    const DataT *rt0 = &(img[pos[0]-1][pos[1]]);
    const DataT *rt1 = &(img[pos]);
    const DataT *rt2 = &(img[pos[0]+1][pos[1]]);
    return Vector2dC((RealT)((rt1[-1] - rt1[1]) * 2 + (rt0[-1] - rt0[1]) + (rt2[-1] - rt2[1]))/4, 
		     (RealT)((rt0[0] - rt2[0]) * 2 + (rt0[1] - rt2[1]) + (rt0[-1] - rt2[-1]))/4);
  }
  //: Measure the gradient at a point in an image using a 3x3 Sobel operator.
  // Currently this returns the gradient vector in the order: horizontal, vertical.  This conflicts with (a) RAVL convention and (b) EdgeSobelC.  It may change.
  
}

#endif
