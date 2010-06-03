// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGRAPH_GUPPICANVAS_HEADER
#define RAVLGRAPH_GUPPICANVAS_HEADER
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Data_Plotting.Guppi"
//! rcsid="$Id: GuppiCanvas.hh 3317 2003-08-20 14:50:13Z ees1wc $"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiCanvas.hh"

#include "Ravl/Plot/GuppiGroup.hh"
#include "Ravl/GUI/Widget.hh"

namespace RavlPlotN {
  using namespace RavlGUIN;
  
  //! userlevel=Develop
  //: Guppi canvas
  
  class GuppiCanvasBodyC
    : public WidgetBodyC
  {
  public:
    GuppiCanvasBodyC(RealT sizey,RealT sizex);
    //: Constructor.
    
    virtual StringC Name() const;
    //: Get name of widget.
    
    virtual bool Create();
    //: Create the widget.
    
    GuppiGroupC Group()
    { return group; }
    //: Access group in canvas
    
  protected:
    RealT sizex,sizey;
    GuppiGroupC group;
    GuppiRootGroupView *root_view;
  };
  

  //! userlevel=Develop
  //: Guppi canvas
  
  class GuppiCanvasC
    : public WidgetC
  {
  public:
    GuppiCanvasC()
    {}
    //: Default constructor
    // creates an invalid handle

    GuppiCanvasC(RealT sizey,RealT sizex)
      : WidgetC(*new GuppiCanvasBodyC(sizey,sizex))
    {}
    //: Constructor
    // 72*11, 72*8.5
    
  protected:
    GuppiCanvasBodyC &Body()
    { return static_cast<GuppiCanvasBodyC &>(WidgetC::Body()); }
    //: Access body.

    const GuppiCanvasBodyC &Body() const
    { return static_cast<const GuppiCanvasBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
    GuppiGroupC Group()
    { return Body().Group(); }
    //: Access group in canvas
    
  };
}


#endif
