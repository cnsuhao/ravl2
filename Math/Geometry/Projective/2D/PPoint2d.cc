// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! date="26.04.1995"
//! author="Radek Marik"
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Projective/2D/PPoint2d.cc"

#include "Ravl/PPoint2d.hh"
#include "Ravl/PLine2d.hh"

namespace RavlN {
  
  PLine2dC PPoint2dC::PLine(const PPoint2dC & p) const
  { return PPointLine2d(p); }
  
  ostream & operator<<(ostream & outS, const PPoint2dC & p) {
    outS << p.P1() << ' ' << p.P2() << ' ' << p.P3();
    return outS;
  }
  
  istream & operator>>(istream & inS, PPoint2dC & p) {
    inS >> p.P1() >> p.P2() >> p.P3();
    return inS;
  }

}
