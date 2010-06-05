// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! rcsid="$Id: Angle.cc 7334 2009-10-26 17:21:58Z cyberplug $"
//! lib=RavlCore
//! file="Ravl/Core/Math/Angle.cc"

#include "Ravl/Angle.hh"
#include "Ravl/Stream.hh"

namespace RavlN {
  // Dump to stream.
  
  void AngleC::Dump(ostream &out) {
    out << "Ang:" << angle << " Max:" << m_max << "\n";
  }
}

