// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_CANVAS_HEADER
#define RAVLGUI_CANVAS_HEADER 1
////////////////////////////////////////////////
//! docentry="Ravl.GUI.Control"
//! file="Ravl/GUI/2D/Canvas.hh"
//! lib=RavlGUI2D
//! author="Charles Galambos"
//! example=exCanvas.cc
//! date="17/03/1999"
//! rcsid="$Id$"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/DList.hh"
#include "Ravl/Trigger.hh"
#include <gdk/gdktypes.h>

namespace RavlGUIN {
  using namespace RavlImageN;
  class CanvasC;
  
  //! userlevel=Develop
  //: Widget in which graphics can be rendered.
  
  class CanvasBodyC 
    : public WidgetBodyC 
  {
  public:
    CanvasBodyC(int sx,int sy,bool direct = false);
    //: Constructor.
    
    ~CanvasBodyC();
    //: Destructor.
    
    GtkWidget *DDrawArea() 
    { return widget; }
    //: Direct draw area.
  
    GdkPixmap * &Pixmap() 
    { return pixmap; }
    //: Pixmap.
    
    GdkDrawable *DrawArea();
    //: Get draw area.
    
    GdkColor &GetColour(int n);
    //: Access colour.
    // GUI thread only.
    
    bool Resize(int nsx,int nsy);
    //: Resize canvas.
    // The canvas will be resized on the next render event.
    
    bool GUIResize(int &nsx,int &nsy);
    //: Resize canvas.
    // GUI Thread only
    
    bool &ConfigDone() 
    { return configDone; }
    //: Flag configure as done.
    
    GdkGC *DrawGC() 
    { return drawGC; }
    //: Drawing context.
    
    void DoSomeSetup();
    //: Don't call directly!!!!!!!!!!
    
    void DrawImage(const ImageC<ByteT> &img,Index2dC offset=Index2dC(0,0));
    //: Draw an image on the canvas.
    
    void DrawImage(const ImageC<ByteRGBValueC> &img,Index2dC offset=Index2dC(0,0));
    //: Draw an rgb image on the canvas.
    
    void DrawLine(IntT x1,IntT y1,IntT x2,IntT y2,IntT colId = 0); 
    //: Draw a line.

    void DrawText(IntT x1,IntT y1,StringC text,IntT colId = 0);
    //: Draw some text
    
    bool GUIDrawImage(ImageC<ByteT> &img,Index2dC &offset);
    //: Draw an image on the canvas.
    // Call with GUI thread only!
    
    bool GUIDrawRGBImage(ImageC<ByteRGBValueC> &img,Index2dC &offset);
    //: Draw an rgb image on the canvas.
    // Call with GUI thread only!
    
    bool GUIDrawLine(IntT &x1,IntT &y1,IntT &x2,IntT &y2,IntT &colId); 
    //: Draw a line.
    // Call with GUI thread only!
    
    bool GUIDrawText(IntT &x1,IntT &y1,StringC &text,IntT &colId);
    //: Draw some text
    // Call with GUI thread only!
    
    bool IsReady() const { 
      if(widget == 0) return false;
      if(direct) return true;
      return pixmap != 0;
    }
    //: Is Canvas ready for drawing.
    
  protected:
    
    virtual bool Create();
    //: Create the widget.
    
    virtual void WidgetDestroy();
    //: Called when the underlying widget it destroyed.
    // The default version of this method simpily 0's the widget ptr.
    
    bool GUIRefresh();
    //: Refresh display.
    
    int sx,sy;
    bool direct;
    
    GdkPixmap *pixmap;       // Map.
    bool configDone;
    
    void SetupColours();
    //: Setup colour table.
    
    GdkGC *drawGC;
    SArray1dC<GdkColor> colourTab; // Colour table.
    
    DListC<TriggerC> toDo; // List of things to do as soon as we're initalised.
    
    friend class CanvasC;
  };
  
  //! userlevel=Normal
  //: Widget in which graphics can be rendered.
  
  class CanvasC 
    : public WidgetC 
  {
  public:
    CanvasC()
    {}
    //: Default constructor.
    // NB. This creates an invalid handle.
    
    CanvasC(int xs,int ys,bool direct = false);
    //: Constructor.
    
    CanvasC(CanvasBodyC &body)
      : WidgetC(body)
    {}
    //: Body constructor.
    
  protected:
    
    CanvasBodyC &Body() 
    { return static_cast<CanvasBodyC &>(WidgetC::Body()); }
    
    const CanvasBodyC &Body() const
    { return static_cast<const CanvasBodyC &>(WidgetC::Body()); }
    
  public:
    GdkDrawable *DrawArea() 
    { return Body().DrawArea(); }
    //: Get drawing area.
    
    bool GUIResize(int &nsx,int &nsy)
    { return Body().GUIResize(nsx,nsy); }
    //: Resize canvas.
    // Call with the GUI Thread only
    
    bool Resize(int nsx,int nsy)
    { return Body().Resize(nsx,nsy); }
    //: Resize canvas.
    
    GdkColor &GetColour(int n)
    { return Body().GetColour(n); }
    //: Access colour.
    // GUI thread only.
    
    GdkGC *DrawGC() 
    { return Body().DrawGC(); }
    //: Drawing context.
    // GUI thread only.
    
    void DrawImage(const ImageC<ByteT> &img,Index2dC offset=Index2dC(0,0))
    { Body().DrawImage(img,offset); }
    //: Draw an image on the canvas.
    
    void DrawImage(const ImageC<ByteRGBValueC> &img,Index2dC offset=Index2dC(0,0))
    { Body().DrawImage(img,offset); }
    //: Draw an rgb image on the canvas.

    bool DrawRGBImage(const ImageC<ByteRGBValueC> &img)
    { Body().DrawImage(img,Index2dC(0,0)); return true; }
    //: Draw an rgb image on the canvas.
    
    void DrawLine(IntT x1,IntT y1,IntT x2,IntT y2,IntT colId = 0)
    { Body().DrawLine(x1,y1,x2,y2,colId); }
    //: Draw a line.
    
    void DrawText(IntT x1,IntT y1,StringC text,IntT colId = 0)
    { Body().DrawText(x1,y1,text,colId); }
    //: Draw a line.
    
    bool GUIDrawLine(IntT &x1,IntT &y1,IntT &x2,IntT &y2,IntT &colId)
    { return Body().GUIDrawLine(x1,y1,x2,y2,colId); }
    //: Draw a line.

    bool GUIDrawLine(Index2dC &p1,Index2dC &p2,IntT &colId)
      { return Body().GUIDrawLine(p1.Row().V(),p1.Col().V(),p2.Row().V(),p2.Col().V(),colId); }
    //: Draw a line.
    // Call with GUI thread only!
    
    bool GUIDrawImage(ImageC<ByteT> &img,Index2dC &offset)
    { return Body().GUIDrawImage(img,offset); }
    //: Draw an image on the canvas.
    // Call with GUI thread only!
    
    bool GUIDrawRGBImage(ImageC<ByteRGBValueC> &img,Index2dC &offset)
    { return Body().GUIDrawRGBImage(img,offset); }
    //: Draw an rgb image on the canvas.
    // Call with GUI thread only!
    
    bool GUIDrawText(IntT &x1,IntT &y1,StringC &text,IntT &colId)
    { return Body().GUIDrawText(x1,y1,text,colId); }
    //: Draw some text.
    // Call with GUI thread only!
    
    bool IsReady() const 
    { return Body().IsReady(); }
    //: Is Canvas ready for drawing ?
    
    friend class CanvasBodyC;
  };
}

#endif
