// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI

#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/PackInfo.hh"
#include <gtk/gtk.h>
#include <iostream.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x) 
#endif

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
	  ONDEBUG(cerr << "LBoxBodyC::Create(), Found pack info :" << pi.Expand() << " " << pi.Fill() << " " << pi.Padding() << "\n");
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
}

