//////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/RawCanvas.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {

  //: Create the widget.
  
  bool RawCanvasBodyC::Create() {
    if(widget != 0)
      return true; // Done already.
    widget =  gtk_drawing_area_new ();
    gtk_drawing_area_size(GTK_DRAWING_AREA(widget),sx,sy);
    ConnectSignals();
    return true;
  }
}
