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
//! lib=RavlDPDisplay
//! file="Ravl/GUI/DPDisplay/DPDisplayView.hh"
//! author="Charles Galambos"
//! docentry="Ravl.API.GUI.Data Display"

#include "Ravl/GUI/Table.hh"
#include "Ravl/GUI/RawCanvas.hh"
#include "Ravl/GUI/DPDisplayObj.hh"
#include "Ravl/Threads/RWLock.hh"
#include "Ravl/GUI/Ruler.hh"
#include "Ravl/GUI/Slider.hh"
#include "Ravl/GUI/TextEntry.hh"
#include "Ravl/GUI/Label.hh"
#include "Ravl/GUI/Menu.hh"
#include "Ravl/GUI/FileSelector.hh"
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
    
    void Offset(const Vector2dC &vec2)
    { offset = vec2; }
    //: Set the offset.
    
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
    
    bool CallbackMousePress(MouseEventC &mouseEvent);
    //: Call back for mouse press events.
    
    bool UpdateInfo(const Vector2dC &at);
    //: Update info for mouse position.
    
    bool CallbackStartSave();
    //: Start image save.
    
    bool CallbackSave(StringC &str);
    //: Save image to a file.
    
    IndexRange2dC winSize;
    RawCanvasC canvas;
    RWLockC lockDisplayList;
    DListC<DPDisplayObjC> displayList;
    
    
    bool refreshQueued;
    
    RulerC vRuler,hRuler;
    SliderC vSlider,hSlider;
    LabelC rowPos,  colPos,info;
    
    Vector2dC offset;
    IndexRange2dC displaySize; // Size of displayable objects.
    
    Vector2dC lastMousePos;
    
    MenuC backMenu;
    MenuBarC menuBar;
    FileSelectorC fileSelector;
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
    
    bool CallbackSave(StringC &str)
    { return Body().CallbackSave(str); }
    //: Save image to a file.
    
  public:
    
    bool CallbackStartSave()
    { return Body().CallbackStartSave(); } 
    //: Start image save.
    
    bool AddObject(const DPDisplayObjC &obj) 
    { return Body().AddObject(obj); }
    //: Add object to the display list.
    
    bool Clear()
    { return Body().Clear(); }
    //: Clear the display list.
    
    bool Refresh()
    { return Body().Refresh(); }
    //: Refresh the display.
    
    void Offset(const Vector2dC &vec)
    { Body().Offset(vec); }
    //: Set the offset.

    friend class DPDisplayViewBodyC;
  };
}


#endif
