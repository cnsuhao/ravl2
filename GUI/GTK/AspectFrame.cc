// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! date="7/10/2003"
//! file="Ravl/GUI/GTK/AspectFrame.cc"

#include "Ravl/GUI/AspectFrame.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {
  
  //: Default constructor.
  
  AspectFrameBodyC::AspectFrameBodyC()
    : alignx(0.5),
      aligny(0.5),
      aspect(1),
      obeyChild(false)
  {}
  
  AspectFrameBodyC::AspectFrameBodyC(const WidgetC &widge,RealT naspect,int nborder,const StringC &ntitle)
    : FrameBodyC(widge,nborder,ntitle),
      alignx(0.5),
      aligny(0.5),
      aspect(naspect),
      obeyChild(false)
  {}
  
  //: Create the widget.
  
  bool AspectFrameBodyC::Create() {
    if(widget != 0)
      return true;
    //cerr << "EventBoxBodyC::Create(), Called. \n";
    if(title == "")
      widget = gtk_aspect_frame_new(0,alignx,aligny,aspect,obeyChild);
    else
      widget = gtk_aspect_frame_new(title.chars(),alignx,aligny,aspect,obeyChild);
    if(border != 0)
      gtk_container_set_border_width (GTK_CONTAINER (widget), border);
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

  //: Set obey child.
  
  void AspectFrameBodyC::GUIObeyChild(bool nobeyChild) {
    obeyChild = nobeyChild;
    if(widget == 0)
      return ;
    gtk_aspect_frame_set (GTK_ASPECT_FRAME(widget),alignx,aligny,aspect,obeyChild);
  }
  
  //: Set aspect ratio.
  // GUI thread only.
  
  bool AspectFrameBodyC::GUIAspect(RealT ratio) {
    aspect = ratio;
    if(widget == 0)
      return true;
    gtk_aspect_frame_set (GTK_ASPECT_FRAME(widget),alignx,aligny,aspect,obeyChild);
    return true;
  }
  
}


