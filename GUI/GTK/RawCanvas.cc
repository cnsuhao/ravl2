// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI

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
