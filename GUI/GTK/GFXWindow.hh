#ifndef GUIWINDOW_HEADER
#define GUIWINDOW_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/String.hh"
#include "amma/ByteImag.hh"
#include "amma/YUVImage.hh"
#include "amma/RGBImage.hh"

#include "amma/DP/Port.hh"
#include "amma/Thread/MsgPipe.hh"

#include "amma/GUI/Widget.hh"
#include "amma/GUI/Render.hh"
#include "amma/GUI/GTKTypes.hh"

/////////////////////////////////////
//! userlevel=Develop
//: Window body.

class GUIWindowBodyC 
  : public DPOPortBodyC<GUIRenderC>,
    public GUIWidgetBodyC
{
public:
  GUIWindowBodyC();
  //: Default constructor.
  
  GUIWindowBodyC(int xs,int ys,StringC title,BooleanT direct = FALSE);
  //: Constructor.
  
  ~GUIWindowBodyC();
  //: Destructor.
  
  virtual BooleanT Create();
  //: Create the widget.
  
  virtual BooleanT Service();
  //: Service render request.
  
  virtual BooleanT Put(const GUIRenderC &r);
  //: Put render instructon into pipe.

  virtual void PutEOS();
  //: Put End Of Stream marker.
  
  virtual BooleanT IsPutReady() const;
  //: Is port ready for data ?
  
  IntT WinID() const { return winId; }
  //: Get window id.
  
  GtkWidget *Widget() { return drawing_area; }
  //: Get widget.
  
  GtkWidget *Window() { return widget; }
  //: Get window.
  
  GdkPixmap *Pixmap() { return pixmap; }
  //: Pixmap.
  
  GdkDrawable *DrawArea();
  //: Get draw area.
  
protected:
  int xs,ys;
  StringC title;
  BooleanT direct;
  
  GtkWidget *drawing_area; // Where.
  GdkPixmap *pixmap;       // Map.
  int winId;            // Id for window.
  VPipe<GUIRenderC> in; // Pipe of render operations.
};

////////////////////////////////////
//! userlevel=Normal
//: Window handle.
// Window for displaying graphics.

class GUIWindowC 
  : public DPOPortC<GUIRenderC>,
    public GUIWidgetC
{
public:
  GUIWindowC()
    : DPEntityC(TRUE)
  {}
  //: Default constructor.
  // Creates an invalid handle !
  
  GUIWindowC(int xs,int ys,StringC title = "",BooleanT direct = FALSE);
  //: Constructor.
  
  GUIWindowC(GUIWindowBodyC &bod)
    : DPEntityC(bod)
  {}
  //: Body Constructor.
  
  GUIWindowBodyC &Body() 
    { return dynamic_cast<GUIWindowBodyC &>(DPEntityC::Body()); }

  const GUIWindowBodyC &Body() const
    { return dynamic_cast<const GUIWindowBodyC &>(DPEntityC::Body()); }
  
  inline BooleanT Service() 
    { return Body().Service(); }
  //: Service prog request.
  
  inline IntT WinID() const 
    { return Body().WinID(); }
  //: Get window id.
  
  GtkWidget *Widget() 
    { return Body().Widget(); }
  //: Get widget.
  
  GdkPixmap *Pixmap() 
  { return Body().Pixmap(); }
  //: Pixmap.
  
  GdkDrawable *DrawArea()
  { return Body().DrawArea(); }
  //: Get draw area.

  GtkWidget *Window() 
    { return Body().Window(); }
  //: Get window.
  
  DPOPortC<ImageC<ByteGreyValueT> > Grey() const;
  // Make grey level output image.
  
  DPOPortC<ImageC<ByteYUVValueC> > YUV() const;
  // Make YUV level output image.
  
  DPOPortC<ImageC<ByteRGBValueC> > RGB() const;
  // Make YUV level output image.
  
};

#endif
