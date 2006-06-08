// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Math/Complex.cc"

#include "Ravl/Complex.hh"
#include "Ravl/Stream.hh"
#include "ccmath/ccmath.h"

namespace RavlN {
  ostream & 
  operator<<(ostream & outS, const ComplexC & x) {
    outS << x.Re() << ' ' << x.Im();
    return(outS);
  }

  istream & 
  operator>>(istream & inS, ComplexC & x) {
    inS >> x.Re() >> x.Im();
    return(inS);
  }
  
  inline
  ComplexC Sqrt(const ComplexC & a) {
    struct ccomplex arg;
    arg.re = a.Re();
    arg.im = a.Im();
    struct ccomplex root = csqrt(arg);
    return ComplexC (root.re, root.im);
  }
  //: Returns one of the complex square roots of a complex number
  // The 2nd root is the -ve of the given one
}

