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
    // Check required data
    if (style == NULL) return false;
    // Increment refcount
    if (pixmap!=NULL) {
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

  GdkColor WidgetStyleBodyC::GUIRGB2Colour(ByteRGBValueC& rgb) {
    // Get system colourmap
    GdkColormap *cmap = gdk_colormap_get_system();
    // Create colour
    GdkColor col;
    col.pixel = 0;
    col.red   = rgb.Red()   * 256;
    col.green = rgb.Green() * 256;
    col.blue  = rgb.Blue()  * 256;
    // Allocate our new colour in the colour map
    if (!gdk_colormap_alloc_color(cmap,&col,TRUE,TRUE)) {
      cerr << "Could not allocate colour!" << endl;
    }
    // Done
    return col;
  }

  bool WidgetStyleBodyC::GUISetColour(WidgetColourTypeT type, GdkColor color, GtkStateType state) {
    // Check required data
    if (style==NULL) return false;
    // Set colour
    switch (type) {
    case WIDGET_COLOUR_FG:
      style->fg[state] = color;
      break;
    case WIDGET_COLOUR_BG:
      style->bg[state] = color;
      break;
    case WIDGET_COLOUR_LIGHT:
      style->light[state] = color;
      break;
    case WIDGET_COLOUR_DARK:
      style->dark[state] = color;
      break;
    case WIDGET_COLOUR_MID:
      style->mid[state] = color;
      break;
    case WIDGET_COLOUR_TEXT:
      style->text[state] = color;
      break;
    case WIDGET_COLOUR_BASE:
      style->base[state] = color;
      break;
    case WIDGET_COLOUR_BLACK:
      style->black = color;
      break;
    case WIDGET_COLOUR_WHITE:
      style->white = color;
      break;
    default:
      break;
    }
    return true;
  }

  bool WidgetStyleBodyC::GUISetColour(WidgetColourTypeT& type, ByteRGBValueC& col, GtkStateType& state) {
    return GUISetColour(type,GUIRGB2Colour(col),state);
  }

  bool WidgetStyleBodyC::GUISetColour(WidgetColourTypeT& type, ByteRGBValueC& col) {
    GdkColor gdkcol = GUIRGB2Colour(col);
    return 
      GUISetColour(type,gdkcol,GTK_STATE_NORMAL) &&
      GUISetColour(type,gdkcol,GTK_STATE_ACTIVE) &&
      GUISetColour(type,gdkcol,GTK_STATE_PRELIGHT) &&
      GUISetColour(type,gdkcol,GTK_STATE_SELECTED) &&
      GUISetColour(type,gdkcol,GTK_STATE_INSENSITIVE);
  }

  void WidgetStyleBodyC::SetColour(WidgetColourTypeT& type, ByteRGBValueC& col, GtkStateType& state) {
    Manager.Queue(Trigger(WidgetStyleC(*this),&WidgetStyleC::GUISetColour,type,col,state));
  }

  void WidgetStyleBodyC::SetColour(WidgetColourTypeT& type, ByteRGBValueC& col) {
    Manager.Queue(Trigger(WidgetStyleC(*this),&WidgetStyleC::GUISetColour,type,col));
  }

}

