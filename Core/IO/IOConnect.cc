///////////////////////////////////////////////
//! rcsid="$Id$"

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
  
  //: Do a single processing step.
  
  bool DPIOConnectBaseBodyC::Step() {
    RavlAssertMsg(0,"DPIOConnectBaseBodyC::Step(), Abstract method called.");
    return false;
  }
  
}
