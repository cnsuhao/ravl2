////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/EventBox.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {
  //: Create the widget.
  
  bool EventBoxBodyC::Create() {
    //cerr << "EventBoxBodyC::Create(), Called. \n";
    widget = gtk_event_box_new ();
    if(child.IsValid()) {
      if(!child.Create())
	return false;
      gtk_container_add (GTK_CONTAINER (widget), child.Widget());
      gtk_widget_show (child.Widget());
    }
    ConnectSignals();
    return true;
  }
}
