// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiGraph.cc"

#include "Ravl/Plot/GuppiGraph.hh"
#include "Ravl/Plot/GuppiHeaders.hh"
#include "Ravl/Plot/GuppiLineGraph.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/Stream.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlPlotN {

  //: Constructor.
  
  GuppiGraphBodyC::GuppiGraphBodyC()
  {}
  
  //: Constructor.
    //: Constructor a line graph directly from some data.
  
  GuppiGraphBodyC::GuppiGraphBodyC(const DListC<GuppiElementC> &nplots)
    : plots(nplots)
  {}
  
  //: Constructor a line graph directly from some data.
  
  GuppiGraphBodyC::GuppiGraphBodyC(const Array1dC<RealT> &data)
  { plots.InsLast(GuppiLineGraphC(data)); }
  
  //: Constructor a line graph directly from some data.
  
  GuppiGraphBodyC::GuppiGraphBodyC(const GraphData2dC &data)
  {
    for(SArray1dIterC<Tuple2C<Array1dC<Point2dC>,StringC> > it(const_cast<GraphData2dC &>(data).Data());it;it++)
      plots.InsLast(GuppiLineGraphC(it->Data1()));
  }
  
  //: Constructor from a single plot
  
  GuppiGraphBodyC::GuppiGraphBodyC(GuppiElementC &plot)
  { plots.InsLast(plot); }
  
  //: Build guppi objects
  
  void GuppiGraphBodyC::Build() {
    ONDEBUG(cerr << "GuppiGraphBodyC::Build(), Called. \n");
    if(plots.IsEmpty()) {
      cerr << "GuppiGraphBodyC::Build(), Nothing to plot! \n";
      return ;
    }
    GuppiGroupBodyC::Build(); // Setup group.
    
    GuppiElementState *x_ax_state = guppi_element_state_new ("axis",
							     "label", "x_ax_state",
							     "position", GUPPI_SOUTH,
							     NULL);
    
    GuppiElementState *y_ax_state = guppi_element_state_new ("axis",
							     "label", "y_ax_state",
							     "position", GUPPI_WEST,
							     NULL);
    
    GuppiElementState *legend_state = guppi_element_state_new ("legend",
							       "swatch_width",   6.0,
							       "swatch_height",  6.0,
							       "edge_thickness", 0.5,
							       "edge_margin",    guppi_in2pt(1/16.0),
							       NULL);
   
    GuppiElementState *frame_state = guppi_element_state_new ("frame",
							      "minor_rule_thickness", 0.5,
							      "major_rule_thickness", 0.5,
							      "minor_rule_color",	RGBA_BLACK,
							      "major_rule_color",	RGBA_BLACK,
							      "frame_color",		RGBA_BLACK,
							      "frame_thickness",	.25,
							      NULL);
    
    static guint32 const grey = RGBA_TO_UINT(0xd7,0xd7,0xd7,0xff);
    GuppiElementState *back_state = guppi_element_state_new ("background",
#if 0
							     "color", 	0xe0e0ffff,
							     "color_final",	0xffffffff,
							     "gradient_start", GUPPI_SOUTH,
#else
							     "color",	grey,
							     "color_final",	grey,
#endif
							     NULL);
    GuppiElementView *background_view = guppi_element_view_new (back_state, NULL);
    GuppiElementView *frame_view  = guppi_element_view_new (frame_state, NULL);
    GuppiElementView  *x_ax_view  = guppi_element_view_new (x_ax_state, NULL);
    GuppiElementView  *y_ax_view  = guppi_element_view_new (y_ax_state, NULL);
    GuppiElementView  *legend_view = guppi_element_view_new (legend_state, NULL);
    ONDEBUG(cerr << " Building plots...\n");
    guppi_group_view_layout_same_place (group, background_view, frame_view);
    for(DLIterC<GuppiElementC> it(plots);it;it++) {
      if(!it->IsBuilt())
	it->Build();
      guppi_group_view_layout_same_place (group, frame_view, it->View());
    }
    GuppiElementView  *line_view = plots.First().View();
    ONDEBUG(cerr << " Building layout...\n");
    
    guppi_group_view_layout_flush_left (group, y_ax_view, 0);
    guppi_group_view_layout_horizontally_aligned (group, y_ax_view, line_view, 0);
    guppi_group_view_layout_vertically_aligned (group, line_view, x_ax_view, 0);
    guppi_group_view_layout_flush_bottom (group, x_ax_view, 0);
    guppi_group_view_layout_flush_top (group, line_view, 0);
    guppi_group_view_layout_horizontally_adjacent (group, line_view, legend_view, 0);
    guppi_group_view_layout_center_vertically (group, legend_view);
    guppi_group_view_layout_flush_right (group, legend_view, 0);
    
    guppi_element_view_connect_axis_markers (line_view, GUPPI_X_AXIS,x_ax_view, GUPPI_X_AXIS);
    guppi_element_view_connect_axis_markers (line_view, GUPPI_Y_AXIS,y_ax_view, GUPPI_Y_AXIS);
    
    guppi_element_view_connect_axis_markers (line_view, GUPPI_X_AXIS, frame_view, GUPPI_X_AXIS);
    guppi_element_view_connect_axis_markers (line_view, GUPPI_Y_AXIS, frame_view, GUPPI_Y_AXIS);
    
    /* a hack */
    guppi_element_view_set_preferred_view (line_view, GUPPI_X_AXIS);
    guppi_element_view_set_preferred_view (line_view, GUPPI_Y_AXIS);    
    
    ONDEBUG(cerr << "GuppiGraphBodyC::Build(), Done. \n");
  }
  
  //: Set plots to use.
  
  DListC<GuppiElementC> &GuppiGraphBodyC::Plots(const DListC<GuppiElementC> &nplots) {
    plots = nplots;
    return plots;
  }

  //: Add new plot to graph.
  
  bool GuppiGraphBodyC::AddPlot(GuppiElementC &plot) {
    ONDEBUG(cerr << "GuppiGraphBodyC::AddPlot(), Called. \n");
    
    return true;
  }
  
}
