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

namespace RavlImageN {
  template<class PixelT> class ImageC;
  class ByteRGBValueC;
}

namespace RavlGUIN {
  using namespace RavlImageN;
  
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
    
    GdkGC *GUIDrawGC();
    //: Get drawing context.
    
    GdkFont *GUIDrawFont();
    //: Font to use.
    
    GdkGC *GUIDrawGCBlack();
    //: Get black drawing context.
    
    GdkGC *GUIDrawGCWhite();
    //: Get white drawing context.
    
    GdkGC *GUIDrawGCGrey();
    //: Get grey drawing context.
    
    GdkWindow *GUIDrawWindow();
    //: Get get draw area.
    
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
