// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/Pixmap.cc"

#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Pixmap.hh"
#include <gtk/gtk.h>
  
#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  //: Constructor.
  
  PixmapBodyC::PixmapBodyC(const char **ndata,const WidgetC &nrootWin)
    : rootWin(nrootWin),
      pixmap(0),
      mask(0),
      data(ndata)
  {} 
  
  //: Constructor.
  
  PixmapBodyC::PixmapBodyC(const StringC &nfilename,const WidgetC &rwin)
    : rootWin(rwin),
      pixmap(0),
      mask(0),
      filename(nfilename),
      data(0)
  {
    ONDEBUG(cerr << "PixmapBodyC::PixmapBodyC() fn:'" << filename << "'\n");
  }
  
  //: Constructor.
  
  PixmapBodyC::PixmapBodyC(int nwidth,int nheight,int ndepth) 
    : pixmap(0),
      mask(0),
      data(0),
      width(nwidth),
      height(nheight),
      depth(ndepth)
  {}
  
  //: Create the widget.
  
  bool PixmapBodyC::Create() {  
    if(widget != 0)
      return true; // Shown already.
    
    if(!rootWin.IsValid())
      rootWin = Manager.GetRootWindow();
    rootWin.GUIShow();
    RavlAssert(rootWin.Widget() != 0);
    GdkWindow *window = rootWin.Widget()->window;
    GtkStyle *style = gtk_widget_get_style(rootWin.Widget());  
    
    /* now for the pixmap from gdk */
    
    if(filename == "") {
      if(data != 0)
	pixmap = gdk_pixmap_create_from_xpm_d(window,  &mask,
					      &style->bg[GTK_STATE_NORMAL],
					      (gchar **)data );
    } else {
      if(filename != "") {
	pixmap = gdk_pixmap_create_from_xpm(window,  &mask,
					    &style->bg[GTK_STATE_NORMAL],
					    filename );
      } else {
	pixmap = gdk_pixmap_new(window,width,height,depth);
      }
      
    }
    if(pixmap == 0) {
      // As a last resort... 
      cerr << "PixmapBodyC::Create(), No pixmap specified. \n";
      pixmap = gdk_pixmap_create_from_xpm_d( window,  &mask,
					     &style->bg[GTK_STATE_NORMAL],
					     (char **) xpmData_OpenFile);
      
    }
    
    /* a pixmap widget to contain the pixmap */
    widget = gtk_pixmap_new( pixmap, mask );
    
    rootWin.Invalidate(); // Finished with it, so let it go.
    return true;
  }
  
  //: Get size of pixmap.
  // Will return false if unknown. 
  
  bool PixmapBodyC::GUIGetSize(int &width,int &height) {
    if(pixmap == 0)
      return false;
    gdk_window_get_size(pixmap,&width,&height);
    return true;
  }
  
  /* XPM data of Open-File icon */
  const char * xpmData_OpenFile[] = {
    "16 16 3 1",
    "       c None",
    ".      c #000000000000",
    "X      c #FFFFFFFFFFFF",
    "                ",
    "   ......       ",
    "   .XXX.X.      ",
"   .XXX.XX.     ",
    "   .XXX.XXX.    ",
    "   .XXX.....    ",
    "   .XXXXXXX.    ",
    "   .XXXXXXX.    ",
    "   .XXXXXXX.    ",
    "   .XXXXXXX.    ",
    "   .XXXXXXX.    ",
    "   .XXXXXXX.    ",
    "   .XXXXXXX.    ",
    "   .........    ",
    "                ",
    "                "};
}


