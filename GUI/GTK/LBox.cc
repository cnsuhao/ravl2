///////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/PackInfo.hh"
#include <gtk/gtk.h>
#include <iostream.h>

namespace RavlGUIN {

  //: Create the widget.
  
  bool LBoxBodyC::Create() {
    if(widget == 0) {
      if(vert)
	widget = gtk_vbox_new (homogeneous,spacing);
      else
	widget = gtk_hbox_new (homogeneous,spacing);
      if(boarder != 0)
	gtk_container_set_border_width (GTK_CONTAINER (widget), boarder);
    }
  
    for(DLIterC<WidgetC> it(children);it.IsElm();it.Next()) {
      if(it.Data().Widget() == 0) {
	if(!it.Data().Create()) 
	  cerr << "LBoxBodyC::Create(), Widget create failed ! \n";
	PackInfoC pi(it.Data());
	if(pi.IsValid()) {
	  gtk_box_pack_start (GTK_BOX (widget), it.Data().Widget(), 
			      pi.Expand(), pi.Fill(), pi.Padding());
	} else {
	  gtk_box_pack_start (GTK_BOX (widget), it.Data().Widget(), 
			      true, true, 0);
	}
	gtk_widget_show (it.Data().Widget());
      }
    }
    ConnectSignals();
    return true;
  }
  
  ///////////////////////////////////////////
  
  //: Default constructor
  
  LBoxC::LBoxC()
    : ContainerWidgetC(*new LBoxBodyC())
  {}
}

