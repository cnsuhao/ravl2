////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/Frame.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {
  
  //: Default constructor.
  
  FrameBodyC::FrameBodyC()
    : boarder(0),
      shadow(GTK_SHADOW_ETCHED_IN)
  {}
  
  FrameBodyC::FrameBodyC(const WidgetC &widge,int nboarder,const StringC &ntitle)
    : OneChildBodyC(widge),
      title(ntitle),
      boarder(nboarder),
      shadow(GTK_SHADOW_ETCHED_IN)
  {}
  
  //: Create the widget.
  
  bool FrameBodyC::Create() {
    if(widget != 0)
      return true;
    //cerr << "EventBoxBodyC::Create(), Called. \n";
    if(title == "")
      widget = gtk_frame_new (0);
    else
      widget = gtk_frame_new (title.chars());
    if(boarder != 0)
      gtk_container_set_border_width (GTK_CONTAINER (widget), boarder);
    gtk_frame_set_shadow_type (GTK_FRAME(widget),shadow);
    if(child.IsValid()) {
      if(!child.Create())
	return false;
      gtk_container_add (GTK_CONTAINER (widget), child.Widget());
      gtk_widget_show (child.Widget());
    }
    //gtk_container_set_resize_mode(resizeMode);
    ConnectSignals();
    return true;
  }
  
  //: Setup shadow.
  
  bool FrameBodyC::GUISetShadow(GtkShadowType &nshadow) {
    shadow = nshadow;
    if(widget == 0) 
      return true;
    if(GTK_FRAME(widget)->shadow_type == shadow)
      return true;
    gtk_frame_set_shadow_type (GTK_FRAME(widget),shadow);
    return true;
  }
  
  //: Set frame type.
  
  void FrameBodyC::SetShadowType(GtkShadowType nShadow) {
    Manager.Queue(Trigger(FrameC(*this),&FrameC::GUISetShadow,nShadow));
  }

}


