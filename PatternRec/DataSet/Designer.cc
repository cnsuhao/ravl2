//! author="Charles Galambos"

#include "Ravl/PatternRec/Designer.hh"

namespace RavlN {
  
  VectorC DesignerBodyC::Paramiters() {
    RavlAssertMsg(0,"DesignerBodyC::Paramiters(), Abstract method called. \n");
    return VectorC();
  }
  //: Get the current paramiters.
  
  VectorC DesignerBodyC::Paramiters(const VectorC &params) {
    RavlAssertMsg(0,"DesignerBodyC::Paramiters(const VectorC &), Abstract method called. \n");
    return params;
  }
  //: Set the current paramiters.
  // Returns the current paramiters, which may not be exactly those
  // set in 'params', but will be the closest legal values.

}
