// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! date="6/8/1995"
//! author="Radek Marik"
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/Moments2d2.hh"
#include "Ravl/Matrix2d.hh"
#include "Ravl/Vector2d.hh"

namespace RavlN {
  
  const Moments2d2C & Moments2d2C::ToPrincipalAxis() {
    Matrix2dC mat(m20,m11,m11,m02);
    Vector2dC vec;
    EigenValuesIP(mat,vec);
    if(vec[0] > vec[1]) {
      m20 = vec[0];
      m02 = vec[1];
    } else {
      m20 = vec[1];
      m02 = vec[0];
    }
    m11 = 0;
    return *this; 
  }

  
  ostream &operator<<(ostream & os, const  Moments2d2C & mom) {
    os << mom.M00() << ' ' << mom.M10() << ' ' << mom.M01() << ' '
       << mom.M20() << ' ' << mom.M11() << ' ' << mom.M02();
    return os;
  }
  
  istream &operator>>(istream & is, Moments2d2C & mom) {
    is >> mom.m00 >> mom.m10 >> mom.m01
       >> mom.m20 >> mom.m11 >> mom.m02;
    return is;
  }

}
