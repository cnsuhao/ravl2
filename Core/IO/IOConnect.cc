// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlIO
//! file="Ravl/Core/IO/IOConnect.cc"

#include "Ravl/DP/IOConnect.hh"

namespace RavlN {

  //: Default constructor.
  
  DPIOConnectBaseBodyC::DPIOConnectBaseBodyC()
  {}
  
  //: Op type name.
  
  StringC DPIOConnectBaseBodyC::OpName() const
  { return StringC("pump"); }
  
  //: Run until a stream completes.
  
  bool DPIOConnectBaseBodyC::Run() {
    RavlAssertMsg(0,"DPIOConnectBaseBodyC::Run(), Abstract method called.");
    return false;
  }

  //: Attempt to stop stream processing.
  
  bool DPIOConnectBaseBodyC::Stop() {
    return false;
  }
  
  //: Do a single processing step.
  
  bool DPIOConnectBaseBodyC::Step() {
    RavlAssertMsg(0,"DPIOConnectBaseBodyC::Step(), Abstract method called.");
    return false;
  }
  
  //: Check if we're ready to run.
  
  bool DPIOConnectBaseBodyC::IsReady() const {
    RavlAssertMsg(0,"DPIOConnectBaseBodyC::IsReady(), Abstract method called.");
    return false;
  }
  
}
