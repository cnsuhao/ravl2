// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Euclidean/2D/Affine2d.cc"

#include "Ravl/Affine2d.hh"

namespace RavlN {
  
  void Affine2dC::Rotate(RealT A) {
    RealT TC = Cos(A),TS = Sin(A);    
    Matrix2dC result;
#if !RAVL_COMPILER_VISUALCPP
    MulM(SR,Matrix2dC(TC,-TS,TS,TC),result);
#else
    MulM<RealT,2,2,2>(SR,Matrix2dC(TC,-TS,TS,TC),result);
#endif
    SR = result;
  }
  
}
