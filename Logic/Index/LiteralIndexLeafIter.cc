// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/Index/LiteralIndexLeafIter.cc"

#include "Ravl/Logic/LiteralIndexLeafIter.hh"

namespace RavlLogicN {
  
  //: Constructor
  
  LiteralIndexLeafBodyIterC::LiteralIndexLeafBodyIterC(const LiteralIndexBaseC &ind)
    : hit(ind.Body().map)
  {}
  
  
  LiteralIndexLeafIterC::LiteralIndexLeafIterC(const LiteralIndexBaseC &ind)
    : LiteralMapIterC<LiteralIndexElementC>(*new LiteralIndexLeafBodyIterC(ind))
  {}
  //: Constructor.

}

