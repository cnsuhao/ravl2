/////////////////////////////////////////////////
//! docentry="GUI.Widget"
//! rcsid="$Id$"
//! lib=GUI
//! author="Charles Galambos"

#include "Ravl/GUI/OneChild.hh"

namespace RavlGUIN {

  //: Constructor.
  
  OneChildBodyC::OneChildBodyC(const WidgetC &widge)
    : child(widge)
  {}
  
  //: Create the widget.
  
  bool OneChildBodyC::Create() {
    RavlAssert(0);
    return false;
  }
  
  //: Add widget.
  
  bool OneChildBodyC::Add(const WidgetC &nchild) {
    child=nchild;
    return true;
  }
  

  void OneChildBodyC::Destroy() {
    if(child.IsValid())
      child.Destroy();
    WidgetBodyC::Destroy();
  }
}
