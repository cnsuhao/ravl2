// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
//! author="Radek Marik"
//! date="26.04.1995"
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Projective/3D/PPoint3d.cc"

#include "Ravl/PPoint3d.hh"

namespace RavlN {
  ostream & 
  operator<<(ostream & outS, const PPoint3dC & p)
  {
    outS << p.P1() << ' ' << p.P2() << ' ' << p.P3() << ' ' << p.P4();
    return outS;
  }
  
  istream & 
  operator>>(istream & inS, PPoint3dC & p)
  {
    inS >> p.P1() >> p.P2() >> p.P3() >> p.P4();
    return inS;
  }

}
