// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: Plug.cc 4511 2004-08-11 13:35:02Z kier $"
//! lib=RavlIO
//! file="Ravl/Core/IO/Plug.cc"

#include "Ravl/DP/Plug.hh"

namespace RavlN {
  
  //: Set port.
  
  bool DPIPlugBaseBodyC::ConnectPort(const DPIPortBaseC &port) {
    RavlAssertMsg(0,"DPIPlugBaseBodyC::ConnectPort(), Abstract method called. \n");
    return false;
  }

  //: Return type of port.
  
  const type_info &DPIPlugBaseBodyC::InputType() const
  { return typeid(void); }
  
  ////////////////////////////////////////////////////////////////
  
  //: Set port.
  
  bool DPOPlugBaseBodyC::ConnectPort(const DPOPortBaseC &port) {
    RavlAssertMsg(0,"DPOPlugBaseBodyC::ConnectPort(), Abstract method called. \n");
    return false;
  }
  
  //: Return type of port.
  
  const type_info &DPOPlugBaseBodyC::OutputType() const 
  { return typeid(void); }

}
