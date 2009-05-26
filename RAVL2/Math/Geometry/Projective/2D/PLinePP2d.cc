// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Geometry/Projective/2D/PLinePP2d.cc"

#include "Ravl/LinePP2d.hh"
#include "Ravl/PPoint2d.hh"
#include "Ravl/PLine2d.hh"

namespace RavlN {
  
  PLine2dC::PLine2dC(const LinePP2dC & l)
    : PPointLine2dC(PPoint2dC(l.FirstPoint()),PPoint2dC(l.SecondPoint()))
  {}
  
}
