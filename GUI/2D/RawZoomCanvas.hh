// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPereception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_RAWZOOMCANVAS_HEADER
#define RAVL_RAWZOOMCANVAS_HEADER 1
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlGUI2D
//! docentry="Ravl.GUI.Control"
//! example=exRawZoomCanvas.cc

#include "Ravl/GUI/RawCanvas.hh"
#include "Ravl/Vector2d.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/RealRange2d.hh"

namespace RavlGUIN {
  
  //! userlevel=Developer
  //: Raw Zoomable Canvas.
  
  class RawZoomCanvasBodyC
    : public RawCanvasBodyC 
  {
  public:
    RawZoomCanvasBodyC(IntT rows,IntT cols);
    //: Constructor.
    
    const Vector2dC &Offset() const
    { return offset; }
    //: Access current offset.
    
    const Vector2dC &Scale() const
    { return scale; }
    //: Access current scale.
    
    void GUISetOffset(const Vector2dC &off);
    //: Access current offset.
    
    void GUISetScale(const Vector2dC &scale);
    //: Access current scale.
    
    Point2dC World2GUI(const Point2dC &at) const
    { return  at * scale + offset; }
    //: Convert world coordinates to GUI coordinates.

    Index2dC World2GUIi(const Point2dC &at) const
    { return  Index2dC(World2GUI(at)); }
    //: Convert world coordinates to GUI coordinates.
    
    RealRange2dC World2GUI(const IndexRange2dC &at) const
    { return  RealRange2dC(World2GUI(at.Origin()),World2GUI(at.End())); }
    //: Convert world coordinates to GUI coordinates.

    IndexRange2dC World2GUIi(const IndexRange2dC &at) const
    { return  IndexRange2dC(World2GUIi(at.Origin()),World2GUIi(at.End())); }
    //: Convert world coordinates to GUI coordinates.
    
    Point2dC GUI2World(const Point2dC &at) const
    { return  (at - offset) / scale; }
    //: Convert GUI coordinates to world coordinates
    
    RealRange2dC GUI2World(const IndexRange2dC &at) const
    { return  RealRange2dC(GUI2World(at.Origin()),GUI2World(at.End())); }
    //: Convert world coordinates to GUI coordinates.
    
    void GUIDrawLine(GdkGC *gc,Point2dC p1,Point2dC p2);
    //: Draw a line.
    
    void GUIDrawRectangle(GdkGC *gc,const RealRange2dC &rect,bool fill = false);
    //: Draw a rectangle.
    
    void GUIDrawRectangle(GdkGC *gc,Point2dC topLeft,Point2dC bottomRight,bool fill = false);
    //: Draw a rectangle.
    
    void GUIDrawText(GdkGC *gc,GdkFont *font,Point2dC at,const StringC &txt);
    //: Draw text.
    // 'at' is the bottom left of the text to be drawn.
    
    void GUITextSize(GdkFont *font,const StringC &txt,Point2dC &size);
    //: Find the size of 'text' rendered in 'font'.
    
    void GUIDrawCircle(GdkGC *gc,Point2dC cent,RealT size,bool fill);
    //: Draw a circle.
    
    void GUIDrawImage(const ImageC<ByteRGBValueC> &image,const Point2dC &offset,bool ignoreImageOrigin = false);
    //: Draw an image into the canvas with its origin offset by 'offset'.
    // Note: You have to include the RavlGUI2d library to use this function.
    
    void GUIDrawImage(const ImageC<ByteT> &image,const Point2dC &offset,bool ignoreImageOrigin = false);
    //: Draw an image into the canvas with its origin offset by 'offset'.
    // Note: You have to include the RavlGUI2d library to use this function.
    
    bool TranslateExposeEvent(const GdkEvent* event,RealRange2dC &rect,IntT &toFollow);
    //: Translate an expose event.
    // 'rect' is the area to be updated.
    // 'toFollow' is a count of how many expose events queued to follow this one.
    
    bool TranslateConfigureEvent(const GdkEvent* event,RealRange2dC &widgeSize);
    //: Translate a configure event.
    // 'rect' is the new size for the widget.
    
    // Override Index based versions.
    
    void GUIDrawLine(GdkGC *gc,Index2dC p1,Index2dC p2);
    //: Draw a line.
    
    void GUIDrawRectangle(GdkGC *gc,const IndexRange2dC &rect,bool fill = false);
    //: Draw a rectangle.
    
    void GUIDrawRectangle(GdkGC *gc,Index2dC topLeft,Index2dC bottomRight,bool fill = false);
    //: Draw a rectangle.
    
    void GUIDrawText(GdkGC *gc,GdkFont *font,Index2dC at,const StringC &txt);
    //: Draw text.
    // 'at' is the bottom left of the text to be drawn.
    
    Index2dC GUITextSize(GdkFont *font,const StringC &txt);
    //: Find the size of 'text' rendered in 'font'.
    
    void GUIDrawCircle(GdkGC *gc,Index2dC cent,UIntT size,bool fill);
    //: Draw a circle.
    
    void GUIDrawImage(const ImageC<ByteRGBValueC> &image,const Index2dC &offset = Index2dC(0,0),bool ignoreImageOrigin = false);
    //: Draw an image into the canvas with its origin offset by 'offset'.
    // Note: You have to include the RavlGUI2d library to use this function.
    
    void GUIDrawImage(const ImageC<ByteT> &image,const Index2dC &offset = Index2dC(0,0),bool ignoreImageOrigin = false);
    //: Draw an image into the canvas with its origin offset by 'offset'.
    // Note: You have to include the RavlGUI2d library to use this function.
    
    bool TranslateExposeEvent(const GdkEvent* event,IndexRange2dC &rect,IntT &toFollow);
    //: Translate an expose event.
    // 'rect' is the area to be updated.
    // 'toFollow' is a count of how many expose events queued to follow this one.
    
    bool TranslateConfigureEvent(const GdkEvent* event,IndexRange2dC &widgeSize);
    //: Translate a configure event.
    // 'rect' is the new size for the widget.

  protected:  
    virtual bool Create();
    //: Create the widget.
    
    virtual bool EventConfigure(GdkEvent* &event);
    //: Handle configure event.
    
    Vector2dC offset;
    Vector2dC scale;
    
    IndexRange2dC widgetSize;
  };
  
  
  //! userlevel=Normal
  //: Raw Zoomable Canvas.
  
  class RawZoomCanvasC
    : public RawCanvasC 
  {
  public:
    RawZoomCanvasC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    RawZoomCanvasC(IntT rows,IntT cols)
      : RawCanvasC(*new RawZoomCanvasBodyC(rows,cols))
    {}
    //: Default constructor.
    
  protected:
    RawZoomCanvasC(RawZoomCanvasBodyC &bod)
      : RawCanvasC(bod)
    {}
    //: Body constructor.
    
    RawZoomCanvasBodyC &Body()
    { return static_cast<RawZoomCanvasBodyC &>(WidgetC::Body()); }
    //: Access body.

    const RawZoomCanvasBodyC &Body() const
    { return static_cast<const RawZoomCanvasBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
    const Vector2dC &Offset() const
    { return Body().Offset(); }
    //: Access current offset.
    
    const Vector2dC &Scale() const
    { return Body().Scale(); }
    //: Access current scale.
    
    void GUISetOffset(const Vector2dC &off)
    { Body().GUISetOffset(off); }
    //: Access current offset.
    
    void GUISetScale(const Vector2dC &scale)
    { Body().GUISetScale(scale); }
    //: Access current scale.
    
    void GUIDrawLine(GdkGC *gc,Point2dC p1,Point2dC p2)
    { return Body().GUIDrawLine(gc,p1,p2); }
    //: Draw a line.
    
    void GUIDrawRectangle(GdkGC *gc,const RealRange2dC &rect,bool fill = false)
    { return Body().GUIDrawRectangle(gc,rect,fill); }
    //: Draw a rectangle.
    
    void GUIDrawRectangle(GdkGC *gc,Point2dC topLeft,Point2dC bottomRight,bool fill = false)
    { return Body().GUIDrawRectangle(gc,topLeft,bottomRight,fill); }
    //: Draw a rectangle.
    
    void GUIDrawText(GdkGC *gc,GdkFont *font,Point2dC at,const StringC &txt)
    { return Body().GUIDrawText(gc,font,at,txt); }
    //: Draw text.
    // 'at' is the bottom left of the text to be drawn.
    
    void GUITextSize(GdkFont *font,const StringC &txt,Point2dC &size)
    { Body().GUITextSize(font,txt,size); }
    //: Find the size of 'text' rendered in 'font'.
    
    void GUIDrawCircle(GdkGC *gc,Point2dC cent,RealT size,bool fill = false)
    { return Body().GUIDrawCircle(gc,cent,size,fill); }
    //: Draw a circle.
    
    void GUIDrawImage(const ImageC<ByteRGBValueC> &image,const Point2dC &offset = Point2dC(0,0),bool ignoreImageOrigin = false)
    { return Body().GUIDrawImage(image,offset,ignoreImageOrigin); }
    //: Draw an image into the canvas with its origin offset by 'offset'.
    // Note: You have to include the RavlGUI2d library to use this function.
    
    void GUIDrawImage(const ImageC<ByteT> &image,const Point2dC &offset = Point2dC(0,0),bool ignoreImageOrigin = false)
    { return Body().GUIDrawImage(image,offset,ignoreImageOrigin); }
    //: Draw an image into the canvas with its origin offset by 'offset'.
    // Note: You have to include the RavlGUI2d library to use this function.
    
    bool TranslateExposeEvent(const GdkEvent* event,RealRange2dC &rect,IntT &toFollow)
    { return Body().TranslateExposeEvent(event,rect,toFollow); }
    //: Translate an expose event.
    // 'rect' is the area to be updated.
    // 'toFollow' is a count of how many expose events queued to follow this one.
    
    bool TranslateConfigureEvent(const GdkEvent* event,RealRange2dC &widgeSize)
    { return Body().TranslateConfigureEvent(event,widgeSize); }
    //: Translate a configure event.
    // 'rect' is the new size for the widget.

    void GUIDrawLine(GdkGC *gc,Index2dC p1,Index2dC p2)
    { return Body().GUIDrawLine(gc,p1,p2); }
    //: Draw a line.
    
    void GUIDrawRectangle(GdkGC *gc,const IndexRange2dC &rect,bool fill = false)
    { return Body().GUIDrawRectangle(gc,rect,fill); }
    //: Draw a rectangle.
    
    void GUIDrawRectangle(GdkGC *gc,Index2dC topLeft,Index2dC bottomRight,bool fill = false)
    { return Body().GUIDrawRectangle(gc,topLeft,bottomRight,fill); }
    //: Draw a rectangle.
    
    void GUIDrawText(GdkGC *gc,GdkFont *font,Index2dC at,const StringC &txt)
    { return Body().GUIDrawText(gc,font,at,txt); }
    //: Draw text.
    // 'at' is the bottom left of the text to be drawn.
    
    Index2dC GUITextSize(GdkFont *font,const StringC &txt)
    { return Body().GUITextSize(font,txt); }
    //: Find the size of 'text' rendered in 'font'.
    
    void GUIDrawCircle(GdkGC *gc,Index2dC cent,UIntT size,bool fill)
    { return Body().GUIDrawCircle(gc,cent,size,fill); }
    //: Draw a circle.
    
    void GUIDrawImage(const ImageC<ByteRGBValueC> &image,const Index2dC &offset,bool ignoreImageOrigin = false)
    { return Body().GUIDrawImage(image,offset,ignoreImageOrigin); }
    //: Draw an image into the canvas with its origin offset by 'offset'.
    // Note: You have to include the RavlGUI2d library to use this function.
    
    void GUIDrawImage(const ImageC<ByteT> &image,const Index2dC &offset,bool ignoreImageOrigin = false)
    { return Body().GUIDrawImage(image,offset,ignoreImageOrigin); }
    //: Draw an image into the canvas with its origin offset by 'offset'.
    // Note: You have to include the RavlGUI2d library to use this function.
    
    bool TranslateExposeEvent(const GdkEvent* event,IndexRange2dC &rect,IntT &toFollow)
    { return Body().TranslateExposeEvent(event,rect,toFollow); }
    //: Translate an expose event.
    // 'rect' is the area to be updated.
    // 'toFollow' is a count of how many expose events queued to follow this one.
    
    bool TranslateConfigureEvent(const GdkEvent* event,IndexRange2dC &widgeSize)
    { return Body().TranslateConfigureEvent(event,widgeSize); }
    //: Translate a configure event.
    // 'rect' is the new size for the widget.
    
  };
  
}



#endif

