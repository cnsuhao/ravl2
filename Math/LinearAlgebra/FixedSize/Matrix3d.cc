// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/FixedSize/Matrix3d.cc"

#include "Ravl/Matrix3d.hh"

namespace RavlN {

  //: Invert this matrix.
  
  bool Matrix3dC::Invert(TFMatrixC<RealT,3,3> &op) const {
    RealT d1 = data[1][1]*data[2][2]-data[1][2]*data[2][1];
    RealT d2 = data[1][2]*data[2][0]-data[1][0]*data[2][2];
    RealT d3 = data[1][0]*data[2][1]-data[1][1]*data[2][0];
    RealT det = data[0][0]*d1 + data[0][1]*d2 + data[0][2]*d3;
    
    if(det == 0.0)
      return false; // Matrix singular.
    
    op[0][0] = d1/det; 
    op[0][1] = (data[2][1]*data[0][2]-data[2][2]*data[0][1])/det;
    op[0][2] = (data[0][1]*data[1][2]-data[0][2]*data[1][1])/det;
    op[1][0] = d2/det; 
    op[1][1] = (data[2][2]*data[0][0]-data[2][0]*data[0][2])/det;
    op[1][2] = (data[0][2]*data[1][0]-data[0][0]*data[1][2])/det;
    op[2][0] = d3/det; 
    op[2][1] = (data[2][0]*data[0][1]-data[2][1]*data[0][0])/det;
    op[2][2] = (data[0][0]*data[1][1]-data[0][1]*data[1][0])/det;
    
    return true;
  }

}
