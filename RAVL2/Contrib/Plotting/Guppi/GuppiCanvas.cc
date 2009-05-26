// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiCanvas.cc"

#include "Ravl/Plot/GuppiCanvas.hh"
#include "Ravl/Plot/GuppiHeaders.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlPlotN {
  
  //: Constructor.
  
  GuppiCanvasBodyC::GuppiCanvasBodyC(RealT nsizey,RealT nsizex)
    : sizex(nsizex),
      sizey(nsizey),
      root_view(0)
  {
    root_view = GUPPI_ROOT_GROUP_VIEW (guppi_root_group_view_new ());
    guppi_root_group_view_set_size (root_view,sizex,sizey); 
    group = GuppiGroupC(GUPPI_GROUP_VIEW(root_view));
  }
  
  //: Get name of widget.
  
  StringC GuppiCanvasBodyC::Name() const
  { return StringC("GuppiCanvasC"); }
  
  //: Create the widget.
  
  bool GuppiCanvasBodyC::Create() {
    ONDEBUG(cerr << "GuppiCanvasBodyC::Create(), Called. \n");
    
    GuppiCanvasItem *root_item;
    widget = (GtkWidget *) guppi_root_group_view_make_canvas (root_view, &root_item);
    guppi_root_group_item_set_resize_semantics (GUPPI_ROOT_GROUP_ITEM (root_item),ROOT_GROUP_RESIZE_FILL_SPACE);
    gtk_widget_show (widget);
    ConnectSignals();
    
    ONDEBUG(cerr << "GuppiCanvasBodyC::Create(), Done. \n");
    return true;
  }

}
