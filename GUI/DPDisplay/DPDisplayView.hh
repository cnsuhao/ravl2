// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_DPDISPLAYVIEW_HEADER
#define RAVLGUI_DPDISPLAYVIEW_HEADER 1
////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUIDisplay

#include "Ravl/GUI/Table.hh"
#include "Ravl/GUI/RawCanvas.hh"
#include "Ravl/GUI/DPDisplayObj.hh"
#include "Ravl/Threads/RWLock.hh"
#include "Ravl/GUI/Ruler.hh"
#include "Ravl/GUI/Slider.hh"
#include "Ravl/GUI/TextEntry.hh"
#include "Ravl/GUI/Label.hh"
#include "Ravl/Vector2d.hh"

namespace RavlGUIN {
  class DPDisplayViewC;
  class MouseEventC;
  //! userlevel=Develop
  //: Widget for displaying DPDisplayObjC's.
  
  class DPDisplayViewBodyC
    : public TableBodyC
  {
  public:
    DPDisplayViewBodyC(const IndexRange2dC &size);
    //: Default constructor.
    
    virtual bool Create();
    //: Create the widget.
    
    bool AddObject(const DPDisplayObjC &obj);
    //: Add object to the display list.
    
    bool Clear();
    //: Clear the display list.
    
    bool Refresh();
    //: Refresh the display.
    
    RawCanvasC &Canvas()
    { return canvas; }
    //: Access canvas.

    const RawCanvasC &Canvas() const
    { return canvas; }
    //: Access canvas.
    
    Vector2dC Offset() const
    { return offset; }
    //: Current offset for origin of window.
    
  protected:
    bool GUIRefresh();
    //: Refresh the display.
    
    bool UpdateRuler();
    //: Update ruler info.
    
    bool UpdateSlider();
    //: Update sliders info.
    
    bool Query(Vector2dC pos,StringC &info);
    //: Query position,
    
    bool CallbackExpose(GdkEvent *&event);
    //: Handle an expose event.
    
    bool CallbackConfigure(GdkEvent *&event);
    //: Handle configure callback.
    
    bool CallbackXOffset(RealT &val);
    //: Set X offset.
    
    bool CallbackYOffset(RealT &val);
    //: Set Y offset.
    
    bool CallbackMouseMotion(MouseEventC &mouseEvent);
    //: Call back for mouse movements in the window.
    
    IndexRange2dC winSize;
    RawCanvasC canvas;
    RWLockC lockDisplayList;
    DListC<DPDisplayObjC> displayList;
    bool refreshQueued;
    
    RulerC vRuler,hRuler;
    SliderC vSlider,hSlider;
    LabelC xpos,ypos,info;
    
    Vector2dC offset;
    IndexRange2dC displaySize; // Size of displayable objects.
    
    friend class DPDisplayViewC;
  };

  //! userlevel=Normal
  //: Widget for displaying DPDisplayObjC's.
  
  class DPDisplayViewC
    : public TableC
  {
  public:
    DPDisplayViewC(const IndexRange2dC &size)
      : TableC(*new DPDisplayViewBodyC(size))
    {}
    //: Constructor.

    DPDisplayViewC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
  protected:
    DPDisplayViewC(DPDisplayViewBodyC &body)
      : TableC(body)
    {}
    //: Body constructor.
    
    DPDisplayViewBodyC &Body()
    { return static_cast<DPDisplayViewBodyC &>(WidgetC::Body()); }
    //: Access body.

    const DPDisplayViewBodyC &Body() const
    { return static_cast<const DPDisplayViewBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    bool GUIRefresh()
    { return Body().GUIRefresh(); }
    //: Refresh the display.
    
  public:
    
    bool AddObject(const DPDisplayObjC &obj) 
    { return Body().AddObject(obj); }
    //: Add object to the display list.
    
    bool Clear()
    { return Body().Clear(); }
    //: Clear the display list.
    
    bool Refresh()
    { return Body().Refresh(); }
    //: Refresh the display.
    friend class DPDisplayViewBodyC;
  };
}


#endif
