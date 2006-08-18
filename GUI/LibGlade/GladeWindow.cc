// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLibGlade
//! file="Ravl/GUI/LibGlade/GladeWindow.cc"

#include "Ravl/GUI/GladeWindow.hh"
#include "Ravl/GUI/Manager.hh"

#include <gtk/gtk.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  //: Constructor
  
  GladeWindowBodyC::GladeWindowBodyC(const GladeXMLC &gladeXml,const StringC &widgetName,bool aCustomWidget) 
    : GladeWidgetBodyC(gladeXml,widgetName,aCustomWidget)
  {}
  
  //: Constructor
  
  GladeWindowBodyC::GladeWindowBodyC(const StringC &widgetName,bool aCustomWidget) 
    : GladeWidgetBodyC(widgetName,aCustomWidget)
  {}
  
  //: Raise window to top
  
  bool GladeWindowBodyC::Raise() {
    Manager.Queue(Trigger(GladeWindowC(*this),&GladeWindowC::GUIRaise));
    return true;
  }
  
  //: Raise window to top
  
  bool GladeWindowBodyC::GUIRaise() {
    if (widget!=0)
      gdk_window_raise(widget->window);
    return true;
  }
  
  

  bool GladeWindowBodyC::SetTitle(const StringC &title)
  {
    Manager.Queue(Trigger(GladeWindowC(*this), &GladeWindowC::GUISetTitle, title));
    return true;
  }
  
  
  
  bool GladeWindowBodyC::GUISetTitle(const StringC &title)
  {
    if (widget != NULL)
      gtk_window_set_title(GTK_WINDOW(widget), title.chars());
    return true;
  }
  
  
  
}
