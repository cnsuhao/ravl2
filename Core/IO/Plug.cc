// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlIO

#include "Ravl/DP/Plug.hh"

namespace RavlN {
  
  //: Set port.
  
  bool DPIPlugBaseBodyC::SetPort(const DPIPortBaseC &port) {
    RavlAssertMsg(0,"DPIPlugBaseBodyC::SetPort(), Abstract method called. \n");
    return false;
  }
  
  //: Set port.
  
  bool DPOPlugBaseBodyC::SetPort(const DPOPortBaseC &port) {
    RavlAssertMsg(0,"DPOPlugBaseBodyC::SetPort(), Abstract method called. \n");
    return false;
  }
  
}
