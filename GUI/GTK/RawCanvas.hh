// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_RAWCANVAS_HEADER 
#define RAVLGUI_RAWCANVAS_HEADER  1
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/RawCanvas.hh"
//! lib=RavlGUI
//! author="Charles Galambos"
//! date="23/09/1999"
//! docentry="Ravl.GUI.Control"

#include "Ravl/GUI/Widget.hh"

namespace RavlGUIN {

  //! userlevel=Develop
  //: RawCanvas body.
  
  class RawCanvasBodyC
    : public WidgetBodyC 
  {
  public:
    RawCanvasBodyC(int nsx,int nsy)
      : sx(nsx),sy(nsy)
      {}
    //: Default constructor.
    
    GdkDrawable *DrawArea();
    //: Access draw area.
    
  protected:  
    virtual bool Create();
    //: Create the widget.
    
    virtual void Destroy()
      { WidgetBodyC::Destroy(); }
    //: Undo all references.
    // Placeholder only.
    
  private:
    int sx,sy;
  };
  
  //! userlevel=Normal
  //: RawCanvas handle.
  
  class RawCanvasC
    : public WidgetC 
  {
  public:
    RawCanvasC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    RawCanvasC(int sx,int sy)
      : WidgetC(*new RawCanvasBodyC(sx,sy))
      {}
    //: Constructor.  

  protected:
    RawCanvasC(RawCanvasBodyC &body)
      : WidgetC(body)
    {}
    //: Body constructor.
    
    RawCanvasBodyC &Body()
    { return static_cast<RawCanvasBodyC &>(WidgetC::Body()); }
    //: Access body.

    const RawCanvasBodyC &Body() const
    { return static_cast<const RawCanvasBodyC &>(WidgetC::Body()); }
    //: Access body.
  public:
    GdkDrawable *DrawArea()
    { return Body().DrawArea(); }
    //: Access draw area.
    
  };
  
}

#endif
