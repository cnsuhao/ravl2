// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_DFVIEW_HEADER
#define RAVLDF_DFVIEW_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/GUIView.hh"

#include "Ravl/GUI/RawCanvas.hh"
#include "Ravl/GUI/DragAndDrop.hh"

#include "Ravl/DF/DFSystem.hh"
#include "Ravl/DF/Factory.hh"
#include "Ravl/DF/ViewElement.hh"
#include "Ravl/DF/FactorySet.hh"

#include "Ravl/Hash.hh"
#include "Ravl/HSet.hh"

#include "Ravl/Threads/SignalConnectionSet.hh"

namespace RavlGUIN {
  class MouseEventC;
}

namespace RavlDFN {
  using namespace RavlGUIN;
  using namespace RavlN;
  
  //! userlevel=Develop
  //: View of data flow system.
  
  class GUIViewBodyC
    : public RawCanvasBodyC
  {
  public:
    GUIViewBodyC(const DFSystemC &nsys,
		 const FactorySetC &nfactories,
		 int nsx = 400,int nsy = 400);
    //: Construct with a system.
    
    ~GUIViewBodyC();
    //: Destructor.
    
    DFSystemC &System()
    { return system; }
    //: Access system.
    
    GdkGC *DrawGC();
    //: Get drawing context.
    
    GdkFont *DrawFont();
    //: Font to use.
    
    GdkGC *DrawGCBlack();
    //: Get black drawing context.
    
    GdkGC *DrawGCWhite();
    //: Get white drawing context.
    
    GdkGC *DrawGCGrey();
    //: Get grey drawing context.
    
    GdkWindow *DrawWindow();
    //: Get get draw area.

    void DrawLine(GdkGC *gc,Index2dC p1,Index2dC p2);
    //: Draw a line.
    
    void DrawRectangle(GdkGC *gc,const IndexRange2dC &rect,bool fill = false);
    //: Draw a rectangle.
    
    void DrawRectangle(GdkGC *gc,Index2dC topLeft,Index2dC bottomRight,bool fill = false);
    //: Draw a rectangle.
    
    void DrawText(GdkGC *gc,GdkFont *font,Index2dC at,const StringC &txt);
    //: Draw text.
    
    void DrawCircle(GdkGC *gc,Index2dC cent,UIntT size,bool fill);
    //: Draw a circle.
    
    GdkGC *DrawModeBG(DFRenderModeT mode);
    //: Get background for given draw mode.
    
    GdkGC *DrawModeFG(DFRenderModeT mode);
    //: Get forground for given draw mode.
    
    Index2dC TextSize(GdkFont *font,const StringC &txt);
    //: Find the size of the font.
    
    ViewElementC FindElement(const Index2dC &at);
    //: Find the view element containing 'at'.
    // Will return an invalid handle if none where found.
    
    bool CreateLink(const ViewElementC &elm1,const ViewElementC &elm2);
    //: Attempt to create a link between elm1 and elm2.
    
    bool LoadObject(const StringC &fn,Index2dC at);
    //: Load an object and put it at location 'at'.
    
    bool ClearSelection();
    //: Clear the selection.
    
    bool DeleteSelection();
    //: Delete the selected objects.
    
    bool AutoConvert() const
    { return autoConvert; }
    //: Auto conversion enabled ?
    
    bool SetAutoConvert(bool nautoConvert)
    { return autoConvert = nautoConvert; }
    //: Set auto conversion
    
    bool AttachSystem(DFSystemC &nsys);
    //:  Attach system to this view.
    
  protected:
    
    void BuildAll();
    //: build view of the complete system.
    
    
    ViewElementC AddObject(const DFObjectC &obj,const Index2dC &at);
    //: Add object to view.
    // Returns handle to view element
    
    bool DelObject(const DFObjectC &obj);
    //: Remove object from view,
    
    void Render();
    //: Render entire view.
    
    void Render(const IndexRange2dC &area);
    //: Update an area of the view.
    
    bool Render(const DFObjectC &area);
    //: Update rendering of an object.
    // This will return false if the object is not
    // in the current view, otherwise it will return true.
    
    bool Render(ViewElementC &ve);
    //: Render a particular view element..
    
    virtual bool Create();
    //: Create the widget.
    
    bool EventMouseMove(MouseEventC &me);
    //: Mouse move.
    
    bool EventMousePress(MouseEventC &me);
    //: Mouse press.
    
    bool EventMouseRelease(MouseEventC &me);
    //: Mouse release.
    
    bool EventConfigure(GdkEvent* &event);
    //: Configure.
    
    bool EventExpose(GdkEvent* &event);
    //: Expose of area.
    
    bool EventKeyPress(GdkEventKey *&key);
    //: Handle key press events.
    
    bool EventKeyRelease(GdkEventKey *&key);
    //: Handle key release events.
    
    bool ObjectUpdate(DFObjectUpdateT &type,DFObjectC &obj);
    //: Handle object updates.

    // Drag and drop
    
    bool DNDMotion(GdkDragContext * &dc,PositionTimeC &pt);
    //: Handle drag and drop motion.
    
    bool DNDDrop(GdkDragContext * &dc,PositionTimeC &pt);
    //: Drop.
    
    bool DNDBegin(GdkDragContext * &dc);
    //: Drag and drop begin.
    
    bool DNDEnd(GdkDragContext * &dc);
    //: Drag and drop end.
    
    bool DNDDataRecieved(DNDDataInfoC &info);
    //: Drag and drop data recieved
    
    virtual void Destroy();
    //: Undo all references.
    
    // Internal data.....
    enum ViewStateT { VS_READY,VS_DRAG,VS_LINK } viewState;
    
    DFSystemC system;
    DListC<ViewElementC> elements;
    bool autoConvert;
    
    ViewElementC hold; // View element held by mouse, invalid if none.
    Index2dC holdOffset; // Position on object when it was held.
    Index2dC mouseAt;
    
    HashC<DFObjectC,ViewElementC> obj2elem; // Map object to view elements.
    
    Signal2C<DFObjectUpdateT,DFObjectC> sigObjChange;
    
    FactorySetC factories;
    
    SignalConnectionSetC connectSet;
    SignalConnectionSetC sysConnectSet;
  };
  
  //! userlevel=Normal
  //: View of data flow system.
  
  class GUIViewC 
    : public RawCanvasC
  {
  public:
    GUIViewC()
    {}
    //: Default constructor.
    
    GUIViewC(const DFSystemC &sys,
	     const FactorySetC &nfactories,
	     int sx = 400,int sy = 400)
      : RawCanvasC(*new GUIViewBodyC(sys,nfactories,sx,sy))
    {}
    //: Construct from a system.
    
  protected:
    GUIViewBodyC &Body() 
    { return static_cast<GUIViewBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const GUIViewBodyC &Body() const
    { return static_cast<const GUIViewBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:    
    DFSystemC &System()
    { return Body().System(); }
    //: Access system.
     
    bool AttachSystem(DFSystemC &sys)
    { return Body().AttachSystem(sys); }
    //: Replace system.
   
    bool AutoConvert() const
    { return Body().AutoConvert(); }
    //: Auto conversion enabled ?
    
    bool SetAutoConvert(bool &nautoConvert)
    { return Body().SetAutoConvert(nautoConvert); }
    //: Set auto conversion.
    
  };
}


#endif
