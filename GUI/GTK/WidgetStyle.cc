// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/WidgetStyle.cc"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/GUI/WidgetStyle.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>
#include <gdk/gdktypes.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  using namespace RavlImageN;
  using namespace RavlN;
  
  WidgetStyleBodyC::WidgetStyleBodyC(WidgetC nwidge) 
    : widge(nwidge) 
  {
    // Load default style
    LoadDefault();
  }

  WidgetStyleBodyC::~WidgetStyleBodyC() {
    // Unref background pixmaps
    for (int i=0; i<5; i++) {
      if (style->bg_pixmap[i]) {
	gdk_pixmap_unref(style->bg_pixmap[i]);
	style->bg_pixmap[i] = NULL;
      }
    }
  }

  void WidgetStyleBodyC::LoadDefault() {
    Manager.Queue(Trigger(WidgetStyleC(*this),&WidgetStyleC::GUILoadDefault));
  }

  bool WidgetStyleBodyC::GUILoadDefault() {
    // Copy default style
    style = gtk_style_copy(gtk_widget_get_default_style());
    // Done
    return static_cast<bool>(style);
  }

  GdkPixmap* WidgetStyleBodyC::GUIImage2Pixmap(ImageC<ByteRGBValueC>& im) {
    // Check required data
    if (style == NULL || im.IsEmpty()) return NULL;
    // Create new pixmap
    GdkPixmap* pixmap = gdk_pixmap_new(widge.Widget()->window,
				       im.Cols(),
				       im.Rows(),
				       -1);
    // Load image into pixmap
    if (pixmap && style->black_gc) {
      gdk_draw_rgb_image(pixmap,
			 style->black_gc,
			 0,0,
			 im.Cols(),im.Rows(),
			 GDK_RGB_DITHER_NORMAL,
			 (unsigned char *) im.Row(im.TRow()),
			 im.Cols() * 3);
    }
    // Done
    return pixmap;
  }

  bool WidgetStyleBodyC::GUISetBackground(GdkPixmap* pixmap, GtkStateType state) {
    if (pixmap!=NULL) {
      // Increment refcount
      pixmap = gdk_pixmap_ref(pixmap);
    }
    // Set pointer
    style->bg_pixmap[state] = pixmap;
    // Done
    return true;
  }

  bool WidgetStyleBodyC::GUISetBackground(ImageC<ByteRGBValueC>& im, GtkStateType& state) {
    return GUISetBackground(GUIImage2Pixmap(im),state);
  }
  
  bool WidgetStyleBodyC::GUISetBackground(ImageC<ByteRGBValueC>& im) {
    GdkPixmap* pixmap = GUIImage2Pixmap(im);
    return 
      GUISetBackground(pixmap,GTK_STATE_NORMAL) &&
      GUISetBackground(pixmap,GTK_STATE_ACTIVE) &&
      GUISetBackground(pixmap,GTK_STATE_PRELIGHT) &&
      GUISetBackground(pixmap,GTK_STATE_SELECTED) &&
      GUISetBackground(pixmap,GTK_STATE_INSENSITIVE);
  }

  //: Set the background of the window.
  
  void WidgetStyleBodyC::SetBackground(const ImageC<ByteRGBValueC>& im, GtkStateType& state) {
    Manager.Queue(Trigger(WidgetStyleC(*this),&WidgetStyleC::GUISetBackground,im,state));
  }
  
  void WidgetStyleBodyC::SetBackground(const ImageC<ByteRGBValueC>& im) {
    Manager.Queue(Trigger(WidgetStyleC(*this),&WidgetStyleC::GUISetBackground,im));
  }

}

