#ifndef RAVLGUI_WIDGETDNDINFO_HEADER
#define RAVLGUI_WIDGETDNDINFO_HEADER 1

#include "Ravl/SArray1d.hh"
#include "Ravl/GUI/Widget.hh"

namespace RavlGUIN {
  
  //: Extra drag and drop info, where its needed.
  
  class WidgetDndInfoC {
  public:
    WidgetDndInfoC()
      : isSource(false),
	isTarget(false)
    {}
    //: Constructor.
    
    bool isSource;
    bool isTarget;
    DestDefaultsT TargFlags;
    ModifierTypeT SrcFlags;
    SArray1dC<GtkTargetEntry> TargEntries;
    SArray1dC<GtkTargetEntry> SrcEntries;
    DragActionT TargActions,SrcActions;
  };
  
}


#endif
