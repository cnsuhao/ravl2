// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/CallMethods.hh"
#include <gtk/gtk.h>

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x) 
#endif

namespace RavlGUIN {
  
  /* when invoked (via signal delete_event), terminates the application.
   */
  static void close_application( GtkWidget *widget, GdkEvent *event, gpointer data ) { 
    Manager.Quit(); 
  }
  
  //: Constructor.
  
  WindowBodyC::WindowBodyC(int nsx,int nsy,const char *ntitle,GtkWindowType nWinType,int nboarder,bool nrootWin)
    : sx(nsx), sy(nsy),
      boarder(nboarder),
      title(ntitle),
      rootWin(nrootWin),
      closeDown(false),
      cursorChange(false),
    winType(nWinType)
  {
    if(rootWin)
      Manager.GetRootWindow() = WindowC(*this);
  }
  
  //: Destructor.
  
  WindowBodyC::~WindowBodyC() {
    ONDEBUG(cerr << "WindowBodyC::~WindowBodyC() Started." << ((void *) this) << " \n");
    Destroy();
    ONDEBUG(cerr << "WindowBodyC::~WindowBodyC() Done. " << ((void *) this) << " \n");
  }
  
  //: Create the widget.
  
  bool WindowBodyC::Create() {
    if(widget == 0) {
      widget = gtk_window_new (winType);  
      if(rootWin && winType == GTK_WINDOW_TOPLEVEL) {
	gtk_signal_connect( GTK_OBJECT (widget), "delete_event",
			    GTK_SIGNAL_FUNC (close_application), NULL );
      }
      
    if(title != 0)
      gtk_window_set_title (GTK_WINDOW (widget),title.chars());
    if(boarder != 0)
      gtk_container_set_border_width( GTK_CONTAINER (widget), boarder );    
    }
    if(child.IsValid()) {
      if(child.Create()) {
	gtk_container_add (GTK_CONTAINER (widget), child.Widget());
	gtk_widget_show(child.Widget());
      }
    }
    ConnectSignals();
    return true;
  }
  
  void WindowBodyC::Destroy() {
    if(cursor.IsValid()) 
      cursor.Invalidate();
    
    OneChildBodyC::Destroy();
#if 0
    // Pre-empt destructor...
    // This ensures a expected behavour even
    // if there are still handles to the window
    // somewhere in the program.
    if(!rootWin) {
      if(widget != 0) {
	gtk_widget_hide (widget);
	gtk_widget_destroy(widget);
	widget = 0;
      }
    if(widgetId != 0)
      Manager.Deregister(*this); 
    }
#endif
  }
  
  //: Close window.
  // Thread safe.
  
  void WindowBodyC::Close() {
    Manager.Queue(Trigger(WindowC(*this),&WindowC::GUICloseDown));
  }
  
  //: Set cursor.
  
  void WindowBodyC::SetCursor(CursorC &cur) {
    Manager.Queue(Trigger(WindowC(*this),&WindowC::GUIUpdateCursor,cur));
  }
  
  //: Update cursor.


  bool WindowBodyC::GUIUpdateCursor(CursorC &newCursor) {
    if(widget == 0 && newCursor.IsValid())
      newCursor.SetWindow(widget->window);
    cursor = newCursor;
    return true;
  }

  //: Set the title of the window.

  bool WindowBodyC::GUISetTitle(StringC &str) {
    title = str.Copy();
    if(widget != 0)
      gtk_window_set_title (GTK_WINDOW (widget),title.chars());
    return true;
  }

  //: Set the title of the window.
  
  void WindowBodyC::SetTitle(const StringC &str) {
    Manager.Queue(Trigger(WindowC(*this),&WindowC::GUISetTitle,str));
  }
  
  //: Close down window.
  
  bool WindowBodyC::GUICloseDown() {
    if(closeDown)
      return true;
    closeDown = true;
    if(rootWin) {  // Killing the root window exits the application...
      Manager.Quit();
      return true;
    }
    Hide();
    Destroy();
    return true;
  }
  
  
  //////////////////////////////////////////////
  //: Constructor.
  
  WindowC::WindowC(int sx,int sy,const char *ntitle,GtkWindowType nWinType,int nboarder,bool nrootWin)
    : OneChildC(*new WindowBodyC(sx,sy,ntitle,nWinType,nboarder,nrootWin))
  {}
}

