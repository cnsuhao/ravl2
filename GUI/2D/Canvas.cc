// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI2D
//! file="Ravl/GUI/2D/Canvas.cc"

#include "Ravl/Math.hh"
#include "Ravl/GUI/Canvas.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/CallMethodRefs.hh"
#include "Ravl/Stream.hh"

#include <gtk/gtk.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {

  static int gtkCanvasDestroyGC (GtkWidget *widget,GdkGC * data) { 
    ONDEBUG(cerr << "Got destroy for GC : " << ((void *) data) << "\n");
    gdk_gc_unref(data);
    return 1;
  }
  
  void CanvasBodyC::DoSomeSetup() {
    drawGC = gdk_gc_new(Widget()->window);
    gdk_gc_copy(drawGC,widget->style->white_gc);
    //gdk_gc_ref(drawGC);
    gtk_signal_connect (GTK_OBJECT (Widget()), "destroy",
			(GtkSignalFunc) gtkCanvasDestroyGC,drawGC);
    
    //widget->style->fg_gc[0] = drawGC; // In the hope it'll take care of deleting it...
  }
  
  /* Create a new backing pixmap of the appropriate size */
  static gint win_configure_event (GtkWidget *widget, GdkEventConfigure *event, gpointer data ) {
    CanvasBodyC &body = *(CanvasBodyC *) data;
    ONDEBUG(cerr <<"Configuring pixmap. \n");
    if(body.ConfigDone())
      return true;
    GdkPixmap *orgPixmap = body.Pixmap();
    gint xs,ys;
    if(orgPixmap != 0) {
      // Do we really need to resize, or is it smaller ?
      gdk_window_get_size(orgPixmap,&xs,&ys);
      if(widget->allocation.width < xs ||
	 widget->allocation.height < ys) 
	return true; // Its smaller, don't bother.
    }
    body.Pixmap() = gdk_pixmap_new(widget->window,
				   widget->allocation.width,
				   widget->allocation.height,
				   -1);
#if 0
    GdkVisual *vis = gdk_window_get_visual (widget->window);
    cerr << "Vis:" << ((void *) vis) << endl;
    cerr << "Type: " << ((int) vis->type) << " Depth:" << ((int) vis->depth) << endl;
    cerr << "ColMapSize: " << vis->colormap_size << endl;
    cerr << "BitPerRGB:" << vis->bits_per_rgb << endl;
#endif
    if(body.DrawGC() == 0)
      body.DoSomeSetup();
    // Clear the new pixmap.
    gdk_draw_rectangle (body.Pixmap(),
			widget->style->black_gc,
			true,
			0, 0,
			widget->allocation.width,
			widget->allocation.height);
    if (orgPixmap != 0 ) { // Copy contents of old one ?
      gdk_draw_pixmap(body.Pixmap(),
		      widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
		      orgPixmap,
		      0,0,
		      0,0,
		      xs, ys);
      // Delete old pixmap.
      gdk_pixmap_unref(orgPixmap);
    } 
    
  /* Take care of pending actions that require the pixmap. */
    while(!body.ToDo().IsEmpty()) {
      ONDEBUG(cerr << "Catching up with stuff. \n");
      body.ToDo().Last().Invoke();
      body.ToDo().DelLast();
    }
    ONDEBUG(cerr <<"Configuring pixmap done. \n");
    return true;
  }
  
  /* Redraw the screen from the backing pixmap */
  static gint
  win_expose_event (GtkWidget *widget, GdkEventExpose *event, gpointer data) {
    CanvasBodyC &body = *(CanvasBodyC *) data;
    ONDEBUG(cerr <<"Expose event. \n");
    if(body.Pixmap() != 0) {
      gdk_draw_pixmap(widget->window,
		      widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
		      body.Pixmap(),
		      event->area.x, event->area.y,
		      event->area.x, event->area.y,
		      event->area.width, event->area.height);
    } else
    cerr << "WARNING: Canvas empty. \n";
    ONDEBUG(cerr <<"Expose event done. \n");
    
    return false;
  }
  
  //: Constructor.
  CanvasBodyC::CanvasBodyC(int nsx,int nsy,bool ndirect)
    : sx(nsx),sy(nsy),
      direct(ndirect),
      pixmap(0),
      configDone(false),
      drawGC(0),
      autoRefresh(true)
  {}

  //: Constructor.
  CanvasBodyC::CanvasBodyC(const ImageRectangleC& rect,bool ndirect)
    : sx(rect.Cols()),sy(rect.Rows()),
      direct(ndirect),
      pixmap(0),
      configDone(false),
      drawGC(0),
      autoRefresh(true)
  {}
  
  //: Destructor.
  
  CanvasBodyC::~CanvasBodyC()
  {}
  
  //: Create the widget.
  bool CanvasBodyC::Create() {
    if(widget != 0)
      return true; // Done already.
    ONDEBUG(cerr <<"CanvasBodyC::Create() start. \n");
    widget =  gtk_drawing_area_new ();  
    gtk_drawing_area_size (GTK_DRAWING_AREA (widget), sx, sy);  
    if(!direct) {
      gtk_signal_connect (GTK_OBJECT (widget), "expose_event",
			  (GtkSignalFunc) win_expose_event,(gpointer) this);
      
      gtk_signal_connect (GTK_OBJECT(widget),"configure_event",
			  (GtkSignalFunc) win_configure_event,(gpointer) this);
    }
    SetupColours();
    ConnectSignals();
    gtk_widget_add_events(widget,GDK_EXPOSURE_MASK);
    ONDEBUG(cerr <<"CanvasBodyC::Create() done. \n");
    return true;
  }
  
  void CanvasBodyC::WidgetDestroy() {
    if(pixmap != 0) {
      gdk_pixmap_unref(pixmap);
      pixmap = 0;
    }
    WidgetBodyC::WidgetDestroy();
  }
  
  //: Get draw area.
  
  GdkDrawable *CanvasBodyC::DrawArea() {
    if(direct)
      return widget->window;
    return pixmap; 
  }
  

  //: Draw an image on the canvas.
  
  void CanvasBodyC::DrawImage(const ImageC<ByteT> &img,Index2dC offset) {
    Manager.Queue(Trigger(CanvasC(*this),&CanvasC::GUIDrawImage,const_cast<ImageC<ByteT> &>(img),offset));
  }
  
  //: Draw an rgb image on the canvas.
  
  void CanvasBodyC::DrawImage(const ImageC<ByteRGBValueC> &img,Index2dC offset) {
    Manager.Queue(Trigger(CanvasC(*this),&CanvasC::GUIDrawRGBImage,const_cast<ImageC<ByteRGBValueC> &>(img),offset));
  }

  //: Draw an rgb image on the canvas.
  
  void CanvasBodyC::DrawLine(IntT x1,IntT y1,IntT x2,IntT y2,IntT c) {
    Manager.Queue(Trigger(CanvasC(*this),&CanvasC::GUIDrawLine,x1,y1,x2,y2,c));
  }

  //: Draw some text
  
  void CanvasBodyC::DrawText(IntT x1,IntT y1,StringC text,IntT colId) {
    Manager.Queue(Trigger(CanvasC(*this),&CanvasC::GUIDrawText,x1,y1,text,colId));
  }
  
  //: Draw a rectangle.
  
  void CanvasBodyC::DrawRectangle(IntT x1,IntT y1,IntT x2,IntT y2,IntT c) {
    Manager.Queue(Trigger(CanvasC(*this),&CanvasC::GUIDrawRectangle,x1,y1,x2,y2,c));
  }
  
  //: Turn auto refresh after draw routines on/off.
  
  bool CanvasBodyC::GUIAutoRefresh(bool &val) { 
    ONDEBUG(cerr << "CanvasBodyC::GUIAutoRefresh(bool). Val=" << val << "\n");
    if(!autoRefresh && val)
      GUIRefresh();
    autoRefresh = val;
    return true;
  }
  
  //: Turn auto refresh after draw routines on/off.
  
  void CanvasBodyC::AutoRefresh(bool val) {
    Manager.Queue(Trigger(CanvasC(*this),&CanvasC::GUIAutoRefresh,val));
  }
  
  //: Draw an image on the canvas.
  // Call with GUI thread only!
  
  bool CanvasBodyC::GUIDrawImage(ImageC<ByteT> &img,Index2dC &ioffset) {
    if(!IsReady()) {
      ONDEBUG(cerr <<"CanvasBodyC::GUIDrawImage(), WARNING: Asked to render data before canvas is initialise. \n");
      toDo.InsFirst(TriggerR(*this,&CanvasBodyC::GUIDrawImage,img,ioffset));
      return true;
    }
    if(img.IsEmpty()) {
      cerr << "CanvasBodyC::GUIDrawImage(), WARNING: Ask to render empty image. \n";
      return true;
    }
    ONDEBUG(cerr << "CanvasBodyC::GUIDrawImage(), Rendering image. \n");
    Index2dC off = ioffset + img.Rectangle().Origin();    
    int atx = off.Col().V(); // Convert between RAVL and GTK co-ordinates...
    int aty = off.Row().V();
    gdk_draw_gray_image(DrawArea(),
			widget->style->black_gc,
			atx,aty,
			img.Cols(),img.Rows(),
			GDK_RGB_DITHER_NORMAL,
			img.Row(img.TRow()),
			img.Cols());

#if 1    
    if(autoRefresh) {
      GdkRectangle update_rect;
      update_rect.x = atx;
      update_rect.y = aty;
      update_rect.width = Min((UIntT)Widget()->allocation.width,img.Cols());
      update_rect.height = Min((UIntT)Widget()->allocation.height,img.Rows());
      gtk_widget_draw (Widget(), &update_rect);  
    }
#endif
    return true;
  }
  
  //: Draw an rgb image on the canvas.
  // Call with GUI thread only!
  
  bool CanvasBodyC::GUIDrawRGBImage(ImageC<ByteRGBValueC> &img,Index2dC &ioffset) {
    if(!IsReady()) {
      ONDEBUG(cerr <<"CanvasBodyC::GUIDrawLine(), WARNING: Asked to render data before canvas is initialise. \n");
      toDo.InsFirst(TriggerR(*this,&CanvasBodyC::GUIDrawRGBImage,img,ioffset));
      return true;
    }
    if(img.IsEmpty()) {
      cerr << "GUIRenderRGBImageBodyC::GUIDrawRGBImage(), WARNING: Ask to render empty image. \n";
      return true;
    }
    Index2dC off = ioffset + img.Rectangle().Origin();    
    int atx = off.Col().V(); // Convert between RAVL and GTK co-ordinates...
    int aty = off.Row().V(); 
    
    GtkWidget *widget = Widget();
    gdk_draw_rgb_image(DrawArea(),
		       widget->style->black_gc,
		       atx,aty,
		       img.Cols(),img.Rows(),
		       GDK_RGB_DITHER_NORMAL,
		       (unsigned char *) img.Row(img.TRow()),
		       img.Cols() * 3);

#if 1
    if(autoRefresh) {
      GdkRectangle update_rect;
      update_rect.x = atx;
      update_rect.y = aty;
      update_rect.width = Min((UIntT)Widget()->allocation.width,img.Cols());
      update_rect.height = Min((UIntT)Widget()->allocation.height,img.Rows());
      gtk_widget_draw (Widget(), &update_rect);  
    }
#endif
    return true;
  }
  
  
  //: Draw a line.
  
  bool CanvasBodyC::GUIDrawLine(IntT &x1,IntT &y1,IntT &x2,IntT &y2,IntT &c) {
    if(!IsReady()) {
      ONDEBUG(cerr <<"CanvasBodyC::GUIDrawLine(), WARNING: Asked to render data before canvas is initialise. \n");
      toDo.InsFirst(TriggerR(*this,&CanvasBodyC::GUIDrawLine,x1,y1,x2,y2,c));
      return true;
    }
    GdkGC *gc;
    if(c == 0)
      gc = widget->style->white_gc;
    else{
      gc = DrawGC();
      gdk_gc_set_foreground(gc,&GetColour(c));
    }
    gdk_draw_line (DrawArea(),
		   gc,
		   x1, y1,
		   x2, y2);

    ONDEBUG(cerr <<"CanvasBodyC::GUIDrawLine(), AutoRefresh=" << autoRefresh << "\n");
    if(autoRefresh)
      GUIRefresh();
    return true;
  } 

  //: Draw some text.
  
  bool CanvasBodyC::GUIDrawText(IntT &x1,IntT &y1,StringC &text,IntT &c) {
    if(!IsReady()) {
      ONDEBUG(cerr <<"CanvasBodyC::GUIDrawText(), WARNING: Asked to render data before canvas is initialise. \n");
      toDo.InsFirst(TriggerR(*this,&CanvasBodyC::GUIDrawText,x1,y1,text,c));
      return true;
    }
    GdkGC *gc;
    if(c == 0)
      gc = widget->style->white_gc;
    else{
      gc = DrawGC();
      gdk_gc_set_foreground(gc,&GetColour(c));
    }
#if RAVL_USE_GTK2
    GdkFont *cfont = gtk_style_get_font(widget->style);
#else
    GdkFont *cfont = widget->style->font;
#endif
    gdk_draw_text(DrawArea(),
		  cfont,
		  gc,
		  x1,
		  y1,
		  text.chars(),
		  text.length());
    
    if(autoRefresh)
      GUIRefresh();
    return true;
  }

  //: Draw a rectangle.
  
  bool CanvasBodyC::GUIDrawRectangle(IntT &x1,IntT &y1,IntT &x2,IntT &y2,IntT &c) {
    if(!IsReady()) {
      ONDEBUG(cerr <<"CanvasBodyC::GUIDrawLine(), WARNING: Asked to render data before canvas is initialise. \n");
      toDo.InsFirst(TriggerR(*this,&CanvasBodyC::GUIDrawRectangle,x1,y1,x2,y2,c));
      return true;
    }
    GdkGC *gc;
    if(c == 0)
      gc = widget->style->white_gc;
    else{
      gc = DrawGC();
      gdk_gc_set_foreground(gc,&GetColour(c));
    }
    
    gdk_draw_rectangle (DrawArea(),
			gc,
			true,
			x1, y1,
			x2, y2);
    if(autoRefresh)
      GUIRefresh();
    return true;
    
  }
  
  //: Refresh display.
  
  bool CanvasBodyC::GUIRefresh() {
    if(widget == 0) {
      ONDEBUG(cerr <<"CanvasBodyC::GUIRefresh(), WARNING: Asked to refresh before canvas is initialise. \n");
      toDo.InsFirst(TriggerR(*this,&CanvasBodyC::GUIRefresh));
      return true;
    }
    GdkRectangle update_rect;
    update_rect.x = 0;
    update_rect.y = 0;
    update_rect.width = Widget()->allocation.width;
    update_rect.height = Widget()->allocation.height;
    gtk_widget_draw (Widget(), &update_rect);    
    return true;
  }

  //: Resize canvas.
  // GUI Thread only

  bool CanvasBodyC::GUIResize(int &nsx,int &nsy) {
    if(nsx == sx && nsy == sy)
      return true; // No change!
    sx = nsx;
    sy = nsy;
    if(widget == 0)
      return true;
    //: Make new pixmap....
    if(pixmap != 0)
      gdk_pixmap_unref(pixmap);
    pixmap = gdk_pixmap_new(widget->window,
			    sx,sy,
			    -1);
    //: Make it blank.
    gdk_draw_rectangle (pixmap,
			widget->style->black_gc,
			true,
			0, 0,
			sx,sy);
    //: Set size....
    configDone = true; 
    gtk_drawing_area_size (GTK_DRAWING_AREA (widget), sx, sy);  
    return true;
  }
  
  //: Resize canvas.
  
  bool CanvasBodyC::Resize(int nsx,int nsy) {
    RavlAssert(sx >= 0 && sy >= 0);
    Manager.Queue(Trigger(CanvasC(*this),&CanvasC::GUIResize,nsx,nsy));
    return true;
  }
  
  //: Access colour.
  // GUI thread only.
  
  GdkColor &CanvasBodyC::GetColour(int n) {
    static GdkColor nullColour;
    GdkColor &ret = colourTab[((UIntT)(n-1)) % colourTab.Size()];
    if(ret.pixel == 0) { // Need to allocate ?
      if(widget == 0) {
	cerr <<"CanvasBodyC::GetColour(), WARNING: Called before canvas is initalised. \n";
	return nullColour;
      }
      GdkColormap *colorMap = gdk_window_get_colormap(widget->window);
      if(!gdk_colormap_alloc_color (colorMap,
				    &ret,
				    false,
				    true)) {
	cerr << "ViewGeomCanvasBodyC::AllocColours(), ERROR: Failed to allocate colour. \n";
      }
      if(ret.pixel == 0)
	cerr << "Ooops WARNING: Pixel value of 0, and we hoped this wouldn't happen! \n";
    }
    return ret;
  }
  
  //: Setup colour table.
  
  void CanvasBodyC::SetupColours() {
    if(colourTab.IsValid())
      return ; // Done already.
    
    //GdkColormap *colorMap = gdk_window_get_colormap(widget->window);
  
    colourTab = SArray1dC<GdkColor>(64);
    static const int clookup[4] = { 0,65535,32767,49151 };
    for(int i = 0;i < (int) colourTab.Size();i++) {
      GdkColor &col = colourTab[i];
      int num = i + 1;
      col.red   = clookup[(num  & 1)       + ((num &  8) >> 2)];
      col.green = clookup[((num & 2) >> 1) + ((num & 16) >> 3)];
      col.blue  = clookup[((num & 4) >> 2) + ((num & 32) >> 4)];
      col.pixel = 0;
    }
  }

  //: Clear canvas to given colour.
  
  bool CanvasBodyC::GUIClear() {
    if(widget == 0)
      return true;
    gdk_draw_rectangle (pixmap,
			widget->style->black_gc,
			true,
			0, 0,
			sx,sy);
    
    if(autoRefresh) {
      GdkRectangle update_rect;
      update_rect.x = 0;
      update_rect.y = 0;
      update_rect.width = Widget()->allocation.width;
      update_rect.height = Widget()->allocation.height;
      gtk_widget_draw (Widget(), &update_rect);  
    }
    return true;
  }
  
  //: Clear canvas to given colour.
  
  bool CanvasBodyC::Clear() {
    Manager.Queue(Trigger(CanvasC(*this),&CanvasC::GUIClear));
    return true;
  }

  /////////////////////////////////////////////////////////
  
  //: Constructor.
  
  CanvasC::CanvasC(int xs,int ys,bool direct)
    : WidgetC(*new CanvasBodyC(xs,ys,direct))
  {}

  CanvasC::CanvasC(const ImageRectangleC& rect,bool direct)
    : WidgetC(*new CanvasBodyC(rect,direct))
  {}

}  

