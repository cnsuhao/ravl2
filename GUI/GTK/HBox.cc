///////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/GUI/VBox.hh"
#include <gtk/gtk.h>
#include <iostream.h>

//: Create the widget.

BooleanT GUIVBoxBodyC::Create()
{
  widget = gtk_vbox_new (FALSE, 0);
  for(DLIterC<GUIWidgetC> it(children);it.IsElm();it.Next()) {
    if(!it.Data().Create()) 
      cerr << "GUIVBoxBodyC::Create(), Widget create failed ! \n";
    gtk_box_pack_start (GTK_BOX (widget), it.Data().Widget(), FALSE, FALSE, 0);
    gtk_widget_show (it.Data().Widget());
  }
  ConnectSignals();
  return TRUE;
}

///////////////////////////////////////////

//: Default constructor

GUIVBoxC::GUIVBoxC()
  : DPEntityC(*new GUIVBoxBodyC())
{}

