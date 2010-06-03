// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: RavlOSIOMustLink.cc 3197 2003-07-19 09:44:13Z craftit $"
//! lib=RavlOSIO
//! file="Ravl/OS/IO/RavlOSIOMustLink.cc"

#include "Ravl/DP/DynamicIO.hh"

namespace RavlN {
  
  extern void IncludeFileFormatComposite();
    
  void RavlOSIOMustLink() {
    //InitFileFormatDynamic();
    IncludeFileFormatComposite();
  }
  
}
