//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/Separator.hh"
#include <gtk/gtkhseparator.h>
#include <gtk/gtkvseparator.h>

namespace RavlGUIN {
  //: Create the widget.
  
  bool SeparatorBodyC::Create() {
    if(widget != 0)
      return true;
    if(vert)
      widget = gtk_vseparator_new();
    else
      widget = gtk_hseparator_new();
    ConnectSignals();
    return true;
  }
}
