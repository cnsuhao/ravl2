// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/Ruler.cc"

#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Ruler.hh"
#include <gtk/gtk.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

#define EVENT_METHOD(i, x) GTK_WIDGET_CLASS(GTK_OBJECT(i)->klass)->x

namespace RavlGUIN {

  bool RulerBodyC::GUIAttachTo(WidgetC &widge) {
    if(!widge.IsValid()) {
      cerr << "RulerBodyC::GUIAttachTo(), Passed invalid widget. \n";
      return false;
    }
    if(widge.Widget() == 0) {
      ONDEBUG(cerr << "RulerBodyC::GUIAttachTo(), Creating target. \n");
      if(!widge.Create()) {
	cerr << "RulerBodyC::GUIAttachTo(), Create failed. \n";
	return false;
      }
    }
    ONDEBUG(cerr << "RulerBodyC::GUIAttachTo: " << widge.WidgetName() << "\n");
    if(Widget() == 0) {
      ONDEBUG(cerr << "RulerBodyC::GUIAttachTo(), Create self. \n");
      if(!Create()) {
	cerr << "RulerBodyC::GUIAttachTo(), Self create failed. \n";
	return false;
      }
    }
#if !RAVL_USE_GTK2
    gtk_signal_connect_object(GTK_OBJECT(widge.Widget()), "motion_notify_event",
			      (GtkSignalFunc)EVENT_METHOD(Widget(), motion_notify_event),
			      GTK_OBJECT(Widget()) );
#endif
    
    gtk_widget_add_events(widge.Widget(), GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK );
    ConnectSignals();
    
    return true;
  }
  
  //: Set range of ruler.
  // GUI Thread only.
  
  bool RulerBodyC::GUISetRange(RealT nlower,RealT nupper) {
    lower = nlower;
    upper = nupper;
    gtk_ruler_set_range(GTK_RULER(widget),
			lower,upper,
			position,max_size);
    return true;
  }
  
  bool RulerBodyC::Create() {
    if(widget != 0)
      return true; // Done already.
    if(vert)
      widget = gtk_vruler_new();
    else
      widget = gtk_hruler_new();
    gtk_ruler_set_range(GTK_RULER(widget),
			lower,
			upper,
			position,
			max_size);
    gtk_ruler_set_metric( GTK_RULER(widget), GTK_PIXELS );
    return true;
  }
  
  /////////////////////////////////////////////////////////////////////
  
  void RulerC::SetRange(RealT lower,RealT upper) { 
    Manager.Queue(Trigger(*this,&RulerC::GUISetRange,lower,upper)); 
  }
  
  bool RulerC::AttachTo(WidgetC &widge) {
    ONDEBUG(cerr << "RulerC::AttachTo(), Queueing... \n");
    Manager.Queue(Trigger(*this,&RulerC::GUIAttachTo,widge));
    return true;
  }
}
