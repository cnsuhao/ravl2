#ifndef RAVLGTKTYPES_HEADER
#define RAVLGTKTYPES_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/GTKTypes.hh"
//! lib=GUI
//! userlevel=Develop
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Internal"
//! date="23/03/99"

extern "C" {
  typedef struct _GtkWidget GtkWidget;
  typedef struct _GtkObject GtkObject;
  
  typedef struct _GdkWindow GdkWindow;
  typedef struct _GdkWindow GdkPixmap;
  typedef struct _GdkWindow GdkDrawable;
  typedef struct _GdkCursor GdkCursor;
  typedef union  _GdkEvent  GdkEvent;
  typedef struct _GdkEventExpose GdkEventExpose;
  typedef struct _GdkEventButton GdkEventButton;
  typedef struct _GdkGC	  GdkGC;
}
#endif
