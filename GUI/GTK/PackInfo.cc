///////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/PackInfo.hh"

namespace RavlGUIN {

  //: Create the widget.
  
  bool PackInfoBodyC::Create() {
    if(!child.IsValid())
      return false;
    if(!child.Create())
      return false;
    widget = child.Widget();
    return true;
  }
  
  //: Undo all refrences.
  
  void PackInfoBodyC::Destroy() {
    if(child.IsValid())
      child.Destroy();
    widget = 0; // It'll be the childs widget....
    WidgetBodyC::Destroy();
  }
  
  //: Construct packing info from other widget.
  
  PackInfoC::PackInfoC(WidgetC &other)
    : OneChildC(other)
  {
    if(!dynamic_cast<const PackInfoBodyC *>(&Body()) == 0)
      Invalidate();
  }
  
}
