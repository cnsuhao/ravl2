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
//! file="Ravl/Math/Geometry/Projective/3D/PProjection3d.cc"

//! author="Radek Marik"
//! date="26.06.1995"
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/PProjection3d.hh"

namespace RavlN {
  PProjection3dC::PProjection3dC(istream & inS)
  { inS >> *this; }
  
  ostream & operator<<(ostream & outS, const PProjection3dC & p)
  {
    for (UIntT i = 0; i< 4; ++i)
      for (UIntT j = 0; j < 4; ++j)
	outS << p[i][j] << ' ';
    return outS;
  }

  istream & 
  operator>>(istream & inS, PProjection3dC & p)
  {
    for (UIntT i = 0; i < 4; ++i)
      for (UIntT j = 0; j < 4; ++j)
	inS >> p[i][j];
    return inS;
  }
}
