////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Math.hh"
#include "Ravl/GUI/Canvas.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>
#include <iostream.h>

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
  static gint
  win_configure_event (GtkWidget *widget, GdkEventConfigure *event, gpointer data ) {
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
      drawGC(0)
  {}
  
  //: Destructor.
  
  CanvasBodyC::~CanvasBodyC()
  {}
  
  //: Create the widget.
  bool CanvasBodyC::Create() {
    if(widget != 0)
      return true; // Done already.
    ONDEBUG(cerr <<"Create start. \n");
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
    ONDEBUG(cerr <<"Create done. \n");
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
  void CanvasBodyC::DrawImage(ImageC<ByteT> &img,Index2dC offset) {
    Manager.Queue(Trigger(CanvasC(*this),&CanvasC::GUIDrawImage,img,offset));
  }
  
  //: Draw an rgb image on the canvas.
  void CanvasBodyC::DrawImage(ImageC<ByteRGBValueC> &img,Index2dC offset) {
    Manager.Queue(Trigger(CanvasC(*this),&CanvasC::GUIDrawRGBImage,img,offset));
  }

  //: Draw an rgb image on the canvas.
  void CanvasBodyC::DrawLine(IntT x1,IntT y1,IntT x2,IntT y2,IntT c) {
    Manager.Queue(Trigger(CanvasC(*this),&CanvasC::GUIDrawLine,x1,y1,x2,y2,c));
  }

  //: Draw some text
  void CanvasBodyC::DrawText(IntT x1,IntT y1,StringC text,IntT colId) {
    Manager.Queue(Trigger(CanvasC(*this),&CanvasC::GUIDrawText,x1,y1,text,colId));
  }
  
  //: Draw an image on the canvas.
  // Call with GUI thread only!
  
  bool CanvasBodyC::GUIDrawImage(ImageC<ByteT> &img,Index2dC &ioffset) {
    if(img.IsEmpty()) {
      cerr << "CanvasBodyC::GUIDrawImage(), WARNING: Ask to render empty image. \n";
      return true;
    }
    
    Index2dC off = ioffset + img.Rectangle().Origin();    
    int atx = off.Row().V();
    int aty = off.Col().V();
    
    GtkWidget *widget = Widget();
    gdk_draw_gray_image(DrawArea(),
			widget->style->black_gc,
			atx,aty,
			img.Cols(),img.Rows(),
			GDK_RGB_DITHER_NORMAL,
			img.Row(img.TRow()),
			img.Cols());

#if 0    
    GdkRectangle update_rect;
    update_rect.x = atx;
    update_rect.y = aty;
    update_rect.width = Min((UIntT)Widget()->allocation.width,img.Rows());
    update_rect.height = Min((UIntT)Widget()->allocation.height,img.Cols());
    gtk_widget_draw (Widget(), &update_rect);  
#endif
    return true;
  }
  
  //: Draw an rgb image on the canvas.
  // Call with GUI thread only!
  
  bool CanvasBodyC::GUIDrawRGBImage(ImageC<ByteRGBValueC> &img,Index2dC &ioffset) {
    if(img.IsEmpty()) {
      cerr << "GUIRenderRGBImageBodyC::Render(), WARNING: Ask to render empty image. \n";
      return true;
    }
    Index2dC off = ioffset + img.Rectangle().Origin();    
    int atx = off.Row().V();
    int aty = off.Col().V();
    
    GtkWidget *widget = Widget();
    gdk_draw_rgb_image(DrawArea(),
		       widget->style->black_gc,
		       atx,aty,
		       img.Cols(),img.Rows(),
		       GDK_RGB_DITHER_NORMAL,
		       (unsigned char *) img.Row(img.TRow()),
		       img.Cols() * 3);

#if 0    
    GdkRectangle update_rect;
    update_rect.x = atx;
    update_rect.y = aty;
    update_rect.width = Min((UIntT)Widget()->allocation.width,img.Rows());
    update_rect.height = Min((UIntT)Widget()->allocation.height,img.Cols());
    gtk_widget_draw (Widget(), &update_rect);  
#endif
    return true;
  }
  
  
  //: Draw a line.
  
  bool CanvasBodyC::GUIDrawLine(IntT &x1,IntT &y1,IntT &x2,IntT &y2,IntT &c) {
    GtkWidget *widget = Widget();
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

    GUIRefresh();
    return true;
  } 

  //: Draw some text.
  
  bool CanvasBodyC::GUIDrawText(IntT &x1,IntT &y1,StringC &text,IntT &c) {
    GtkWidget *widget = Widget();
    GdkGC *gc;
    if(c == 0)
      gc = widget->style->white_gc;
    else{
      gc = DrawGC();
      gdk_gc_set_foreground(gc,&GetColour(c));
    }
    gdk_draw_text(DrawArea(),
		  widget->style->font,
		  gc,
		  x1,
		  y1,
		  text.chars(),
		  text.length());
    return true;
  }
  
  //: Refresh display.
  
  bool CanvasBodyC::GUIRefresh() {
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

  void CanvasBodyC::GUIResize(int &nsx,int &nsy) {
    if(nsx == sx && nsy == sy)
      return ; // No change!
    sx = nsx;
    sy = nsy;
    if(widget == 0)
      return ;
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
    GdkColor &ret = colourTab[((UIntT)(n-1)) % colourTab.Size()];
    if(ret.pixel == 0) { // Need to allocate ?
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

  /////////////////////////////////////////////////////////
  
  //: Constructor.
  
  CanvasC::CanvasC(int xs,int ys,bool direct)
    : WidgetC(*new CanvasBodyC(xs,ys,direct))
  {}

}  

