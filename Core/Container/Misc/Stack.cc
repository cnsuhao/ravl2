// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
// $Id$
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/Stack.hh"

namespace RavlN {
#if defined(VISUAL_CPP) || defined(__sgi__)
  int BaseStackTypesG::incrBlkSize = 2;
#else
  int StackDummVarThing = 1; // Avoid empty files.
#endif
}
