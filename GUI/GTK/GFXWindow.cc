
#include <gtk/gtk.h>
#include "amma/GUI/Window.hh"
#include "amma/GUI/Manager.hh"

extern "C" {

/* Create a new backing pixmap of the appropriate size */
static gint
win_configure_event (GtkWidget *widget, GdkEventConfigure *event, gpointer data )
{
  GUIWindowBodyC &body = *(GUIWindowBodyC *) data;
  
  if (body.pixmap)
    gdk_pixmap_unref(body.pixmap);
  
  body.pixmap = gdk_pixmap_new(widget->window,
			       widget->allocation.width,
			       widget->allocation.height,
			       -1);
#if 0
  GdkVisual *vis = gdk_window_get_visual (widget->window);
  cerr << "Vis:" << ((void *) vis) << endl;
  cerr << "Type: " << vis->type << " Depth:" << vis->depth << endl;
  cerr << "ColMapSize: " << vis->colormap_size << endl;
  cerr << "BitPerRGB:" << vis->bits_per_rgb << endl;
#endif
  gdk_draw_rectangle (body.pixmap,
		      widget->style->black_gc,
		      TRUE,
		      0, 0,
		      widget->allocation.width,
		      widget->allocation.height);
  
  return TRUE;
}

void
win_quit ()
{
  gtk_exit (0);
}

/* Redraw the screen from the backing pixmap */
static gint
win_expose_event (GtkWidget *widget, GdkEventExpose *event, gpointer data )
{
  GUIWindowBodyC &body = *(GUIWindowBodyC *) data;
  
  gdk_draw_pixmap(widget->window,
		  widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
		  body.pixmap,
		  event->area.x, event->area.y,
		  event->area.x, event->area.y,
		  event->area.width, event->area.height);

  return FALSE;
}

};

//: Default constructor.

GUIWindowBodyC::GUIWindowBodyC()
{}

//: Constructor.

GUIWindowBodyC::GUIWindowBodyC(int nxs,int nys,StringC ntitle,BooleanT ndirect)
  : xs(nxs),ys(nys),
    title(ntitle),
    direct(ndirect)
{}

//: Create the widget.

BooleanT GUIWindowBodyC::Create()
{
  widget = gtk_window_new (GTK_WINDOW_TOPLEVEL);  
  gtk_window_set_title (GTK_WINDOW (widget), title.chars());
  gtk_signal_connect (GTK_OBJECT (widget), "destroy",
		      GTK_SIGNAL_FUNC (win_quit), (gpointer) this);
  
  GtkWidget *vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (widget), vbox);
  gtk_widget_show (vbox);
  
  drawing_area =  gtk_drawing_area_new ();
  gtk_drawing_area_size (GTK_DRAWING_AREA (drawing_area), xs, ys);
  gtk_box_pack_start (GTK_BOX (vbox), drawing_area, TRUE, TRUE, 0);
  gtk_widget_show (drawing_area);
  gtk_widget_set_events (drawing_area, GDK_EXPOSURE_MASK);
  
  
  if(!direct) {
    gtk_signal_connect (GTK_OBJECT (drawing_area), "expose_event",
			(GtkSignalFunc) win_expose_event,(gpointer) this);
    
    gtk_signal_connect (GTK_OBJECT(drawing_area),"configure_event",
			(GtkSignalFunc) win_configure_event,(gpointer) this);
  }
  gtk_widget_show(widget);  
}

//: Destructor.

GUIWindowBodyC::~GUIWindowBodyC()
{}


//: Service prog request.

BooleanT GUIWindowBodyC::Service() 
{
  GUIWindowC x(*this);
  if(in.Get().Render(x)) {
    GdkRectangle update_rect;
    update_rect.x = 0;
    update_rect.y = 0;
    update_rect.width = Widget()->allocation.width;
    update_rect.height = Widget()->allocation.height;
    gtk_widget_draw (Widget(), &update_rect);  
  }
  return TRUE;
}

GdkDrawable *GUIWindowBodyC::DrawArea() {
  if(direct)
    return drawing_area->window;
  return pixmap; 
}
//: Get draw area.

//: Put data into render pipe.

BooleanT GUIWindowBodyC::Put(const GUIRenderC &inst) 
{
  in.Put(inst); // Put instruction into pipe.
  GUIManager.Notify(WidgetID()); // Tell manager about it.
  return TRUE;
}

//: Put End Of Stream marker.

void GUIWindowBodyC::PutEOS()
{}

//: Is port ready for data ?

BooleanT GUIWindowBodyC::IsPutReady() const 
{ return TRUE; }

/////////////////////////////////////////////////////////

//: Constructor.

GUIWindowC::GUIWindowC(int xs,int ys,StringC title,BooleanT direct) 
  : DPEntityC(*new GUIWindowBodyC(xs,ys,title,direct))
{}


#include "amma/DP/Func2Stream.hh"
#include "amma/GUI/RenderTools.hh"

GUIRenderC ByteToRender(ImageC<ByteGreyValueT> in) 
{  return GUIRenderByteImageC(in); }

GUIRenderC RGBToRender(ImageC<ByteRGBValueC> in) 
{ return GUIRenderRGBImageC(in); }

GUIRenderC YUVToRender(ImageC<ByteYUVValueC> in) 
{ return GUIRenderRGBImageC(RGBImageC(YUVImageC(in))); }


// Make grey level output image.
DPOPortC<ImageC<ByteGreyValueT> > GUIWindowC::Grey() const
{ return ByteToRender >> (*this); }

// Make RGB level output image.
DPOPortC<ImageC<ByteRGBValueC> > GUIWindowC::RGB() const
{ return RGBToRender >> (*this); }

// Make YUV level output image.
DPOPortC<ImageC<ByteYUVValueC> > GUIWindowC::YUV() const
{ return YUVToRender >> (*this); }

