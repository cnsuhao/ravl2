
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
