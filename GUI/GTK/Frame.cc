// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/Frame.cc"

#include "Ravl/GUI/Frame.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {
  
  //: Default constructor.
  
  FrameBodyC::FrameBodyC()
    : border(0),
      shadow(GTK_SHADOW_ETCHED_IN)
  {}
  
  FrameBodyC::FrameBodyC(const WidgetC &widge,int nborder,const StringC &ntitle)
    : OneChildBodyC(widge),
      title(ntitle),
      border(nborder),
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
    if(border != 0)
      gtk_container_set_border_width (GTK_CONTAINER (widget), border);
    gtk_frame_set_shadow_type (GTK_FRAME(widget),shadow);
    if(child.IsValid()) {
      if(child.Widget() == 0) {
	if(!child.Create())
	  return false;
      }
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
  
  //: Set label
  
  bool FrameBodyC::GUISetLabel(StringC &name) {
    title = name;
    if(widget == 0) 
      return true;
    gtk_frame_set_label(GTK_FRAME(widget),title.chars());
    return true;
  }

  //: Set label
  void FrameBodyC::SetLabel(StringC &name) {
    Manager.Queue(Trigger(FrameC(*this),&FrameC::GUISetLabel,name));
  }
  
  //: Set frame type.
  
  void FrameBodyC::SetShadowType(GtkShadowType nShadow) {
    Manager.Queue(Trigger(FrameC(*this),&FrameC::GUISetShadow,nShadow));
  }

}


