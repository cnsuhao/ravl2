// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2007, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"

#include "Ravl/PPoint3d.hh"
#include "Ravl/PPlane3d.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/LeastSquares.hh"

namespace RavlN {
  
  //: Fit plane to a set of points.
 
  bool FitPPlane3d(const SArray1dC<PPoint3dC> &points,PPlane3dC &plane) {
    MatrixC A(4,points.Size());
    int i = 0;
    for(SArray1dIterC<PPoint3dC> it(points);it;it++) {
      SizeBufferAccessC<RealT> row = A[i++];
      for(int k = 0;k < 4;k++)
	row[k] = (*it)[k];
    }
    
    VectorC v;
    if(!LeastSquaresEq0Mag1(A,v))
      return false;
    plane = PPlane3dC(v[0],v[1],v[2],v[3]);
    return true;
  }
  
}
