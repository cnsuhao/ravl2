/////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/IndRect.hh"
#include "Ravl/GUI/Graph1d.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/Array1dIter2.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/PRect2d.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/StdMath.hh"
#include <string.h>
#include <gtk/gtk.h>
#include <stdio.h>

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x) 
#endif

namespace RavlGUIN {

  //: Constructor.
  
  Graph1dBodyC::Graph1dBodyC(const Point2dC &org,const Point2dC &nmax,const Vector2dC &nscale)
    : RawCanvasBodyC(300,300),
      origin(org),
      max(nmax),
      scale(nscale),
      doneInit(false)
  { Init(); }
  
  //: Constructor.
  
  Graph1dBodyC::Graph1dBodyC(int sx,int sy)
    : RawCanvasBodyC(sx,sy),
      origin(0,0),
      max(1,1),
      scale(1,1),
      doneInit(false)
  { Init(); }
  
  //: Destructor.
  
  Graph1dBodyC::~Graph1dBodyC() {
    if(winGC != 0) {
      gdk_gc_destroy(winGC);
      winGC = 0;
    }
  }
  
  void Graph1dBodyC::Init() {
    winGC = 0;
    yValueWidth = 5;
    xValueWidth = 1;
    minorTickSize = 3;
    majorTickSize = 6;
    doMinorTick = true;
    doMajorTick = true;
    textWidth = 8;
    textHeight = 8;
    plotMode = PLOTM_NONE;
    plotJoin = PLOTJ_LINE;
    
    PlaceTicks();  
#if 0
    Array1dC<Point2dC> dat(3);
    dat[0] = Point2dC(10,10);
    dat[1] = Point2dC(10,30);
    dat[2] = Point2dC(20,10);
    SetData(dat);
#endif
  }
  
  //: Create the widget.

  bool Graph1dBodyC::Create() {
    using namespace StdDP;
    using namespace RavlGUIN;
    
    ConnectRef(Signal("expose_event"),*this,&Graph1dBodyC::ExposeEvent);
    ConnectRef(Signal("configure_event"),*this,&Graph1dBodyC::ConfigureEvent);
    ConnectRef(Signal("button_press_event"),*this,&Graph1dBodyC::MousePressEvent);
    ConnectRef(Signal("button_release_event"),*this,&Graph1dBodyC::MouseReleaseEvent);
    //  ConnectRef(Signal("motion_notify_event"),*this,&Graph1dBodyC::MouseMoveEvent);
    
    if(!RawCanvasBodyC::Create())
      return false;
    
    // Setup backmenu.
    backMenu = MenuC("back",
		     MenuItemR("Fit",*this,&Graph1dBodyC::FitAll) 
		     //MenuCheckItemR("Auto Scale",*this,&View3DBodyC::AutoScale)
		     );
    
    using namespace RavlGUIN;
    return true;
  }
  
  //: Mouse event.
  
  void Graph1dBodyC::MouseMoveEvent(MouseEventC &me) {
    //ONDEBUG(cerr << "Graph1dBodyC::MouseMoveEvent() Called. \n");
    Index2dC mpos = me.Position();
    if(!me.HasChanged()) {
    }
  }
  
  //: Mouse event.
  
  void Graph1dBodyC::MousePressEvent(MouseEventC &me) {
    //ONDEBUG(cerr << "Graph1dBodyC::MousePressEvent() Called. \n");
    if(me.HasChanged(2)) {
      ONDEBUG(cerr << "Show menu. \n");
      if(backMenu.IsValid())
	backMenu.Popup();
    }
  }
  
  //: Mouse event.
  
  void Graph1dBodyC::MouseReleaseEvent(MouseEventC &me) {
    //ONDEBUG(cerr << "Graph1dBodyC::MouseReleaseEvent() Called. \n");
  }
  
  
  //: Handle configure event.
  // Resize as well ?
  
  void Graph1dBodyC::ConfigureEvent(GdkEvent* &event) {
    ONDEBUG(cerr << "Graph1dBodyC::ConfigureEvent(), Got event. \n");
    GtkWidget *widget = Widget();
    
    // Make sure we have a drawing context.
    
    if(winGC == 0) {
      winGC = gdk_gc_new(widget->window);
      gdk_gc_copy(winGC,widget->style->white_gc);
    }
    
    // Just in case the fonts changed.
    
    textWidth = gdk_char_width(widget->style->font,'0');
    textHeight = gdk_char_height(widget->style->font,'0');
    
    // Update data area.
    
    Index2dC windowSize = Size();  
    IntT lxmargin = (IntT) (textWidth * yValueWidth + 2) + majorTickSize; // Left X
    IntT bymargin = (IntT) (textHeight * 1.5) + majorTickSize; // Bottom Y  
    Index2dC drawOrigin(windowSize.Row() - bymargin,lxmargin);
    Index2dC drawMax(textHeight,windowSize.Col() - textWidth);
    dataArea = IndexRectangleC(drawOrigin,drawMax);
    max = ReverseMap(drawMax);
    
    ONDEBUG(cerr << "Graph1dBodyC::ConfigureEvent(), TextWidth=" << textWidth << " TextHeight=" << textHeight << "\n");
  }
  
  //: Draw the graph into the window.
  
  void Graph1dBodyC::ExposeEvent(GdkEvent * &event) {
    //cerr << "Graph1dBodyC::ExposeEvent(), Got event. \n";
    RavlAssert(winGC != 0);
    GtkWidget *widget = Widget();
    GdkEventExpose &expose = *((GdkEventExpose *)event);
    
    // Draw filled rectangle, for background.
    gdk_draw_rectangle(widget->window,
		       widget->style->black_gc,1,
		       expose.area.x,expose.area.y,
		       expose.area.width + expose.area.x,
		       expose.area.height + expose.area.y);
    
    
    //ONDEBUG(cerr << "Graph1dBodyC::ExposeEvent(), Max:" << max << "\n");
    DrawXAxis();
    DrawYAxis();
    DrawData();
  }

  
  //: Update data display.
  
  void Graph1dBodyC::RefreshData() {
    Manager.Queue(Trigger(Graph1dC(*this),&Graph1dC::GUIRefreshData));
  }
  
  //: Refresh all of graph.
  
  void Graph1dBodyC::RefreshAll() {
    Manager.Queue(Trigger(Graph1dC(*this),&Graph1dC::GUIRefreshAll));
  }
  
  //: Refresh all of graph.
  
  void Graph1dBodyC::GUIRefreshAll() {
    // Draw filled rectangle, for background.
    
    Index2dC windowSize = Size();
    
    gdk_draw_rectangle(widget->window,
		       widget->style->black_gc,1,
		       0,0,
		       windowSize.Row().V(),
		       windowSize.Col().V());
    
    
    ONDEBUG(cerr << "Graph1dBodyC::ExposeEvent(), Max:" << max << "\n");
    DrawXAxis();
    DrawYAxis();
    DrawData();
  }
  
  //: Update data display.
  
  void Graph1dBodyC::GUIRefreshData() {
    Index2dC &org = dataArea.Origin();
    Index2dC &end = dataArea.End();
    
    gdk_draw_rectangle(widget->window,
		       widget->style->black_gc,1,
		       org.Col().V()+1,
		       end.Row().V(),
		       end.Col().V() - org.Col().V(),
		       org.Row().V() - end.Row().V()
		       );
    DrawData();
  }
  
  
  //: Take a pixel and map back to a value.

  inline 
  Point2dC Graph1dBodyC::ReverseMap(const Index2dC &pnt) {
    Index2dC pix = pnt - dataArea.Origin();
    Point2dC v(pix.Col(),-pix.Row());
    return (v / scale) + origin;
  }
  
  //: Map data point to place in display.
  
  inline 
  Index2dC Graph1dBodyC::MapPoint(const Point2dC &pnt) {
    Point2dC comp = (pnt - origin) * scale;
    return Index2dC(-(RealT) comp.Y(),(RealT) comp.X()) + dataArea.Origin();
  }
  
  
  //: Map x value to place in display.
  
  inline 
  IntT Graph1dBodyC::MapX(RealT d) {
    RealT comp = (d - origin.X())  * scale.X();
    return dataArea.Origin().Col().V() + (IntT) comp;
  }
  
  //: Map y value to place in display.
  
  inline 
  IntT Graph1dBodyC::MapY(RealT d) {
    RealT comp = (d - origin.Y())  * scale.Y();
    return dataArea.Origin().Row().V() - (IntT) comp;
  }
  
  //: Draw X axis.
  
  void Graph1dBodyC::DrawXAxis() {
    GtkWidget *widget = Widget();
    
    const Index2dC &drawOrigin = dataArea.Origin();
    // Draw x axis
    
    Index2dC xto(drawOrigin.Row(),dataArea.End().Col());
    gdk_draw_line(widget->window,
		  winGC,
		  drawOrigin.Col().V(),
		  drawOrigin.Row().V(),
		  xto.Col().V(),
		  xto.Row().V()
		  );
    
    RealT tick = origin.X();
    char buff[20];
    IntT tickSize = majorTickSize;
    bool writeNum = true;
    RealT inc = majorTick.X();
    for(int majorMinor = 0;majorMinor < 2;majorMinor++) {
      if(majorMinor == 1) {
	//cerr << "Doing minor. \n";
	if(!doMinorTick)
	  continue;
	tickSize = minorTickSize;
	writeNum = false;
	inc = minorTick.X();
	tick = origin.X();
      } else {
	//cerr << "Doing major. \n";
	if(!doMajorTick)
	  continue;
      }
      for(;tick < max.X();tick += inc) {
	IntT xat = MapX(tick);
	gdk_draw_line (widget->window,
		       winGC,
		       xat,
		       drawOrigin.Row().V(),
		       xat,
		       drawOrigin.Row().V() + tickSize
		       );
	if(writeNum) {
	  sprintf(buff,"%1.1f",tick);
	  int len = strlen(buff);
	  int w = gdk_text_width(widget->style->font,buff,len);
	  int ts = xat - w/2;
	  gdk_draw_text(widget->window,widget->style->font,winGC,ts, drawOrigin.Row().V() + majorTickSize + textHeight+ 2,buff,len);
	}
      }
    }
  }
  
  //: Draw Y axis.
  
  void Graph1dBodyC::DrawYAxis() {
    GtkWidget *widget = Widget();
    
    const Index2dC &drawOrigin = dataArea.Origin();
    // Draw y axis
    
    Index2dC xto(dataArea.End().Row(),drawOrigin.Col());
    gdk_draw_line(widget->window,
		  winGC,
		  drawOrigin.Col().V(),
		  drawOrigin.Row().V(),
		  xto.Col().V(),
		  xto.Row().V()
		  );
    
    
    RealT tick = origin.Y();
    char buff[20];
    IntT tickSize = majorTickSize;
    bool writeNum = true;
    RealT inc = majorTick.Y();
    for(int majorMinor = 0;majorMinor < 2;majorMinor++) {
      if(majorMinor == 1) {
	//cerr << "Doing minor. \n";
	if(!doMinorTick)
	  continue;
	tickSize = minorTickSize;
	writeNum = false;
	inc = minorTick.Y();
	tick = origin.Y();
      } else {
	//cerr << "Doing major. \n";
	if(!doMajorTick)
	  continue;
      }
      for(;tick < max.Y();tick += inc) {
	IntT yat = MapY(tick);
	gdk_draw_line (widget->window,
		       winGC,
		       drawOrigin.Col().V(),
		       yat,
		     drawOrigin.Col().V() - tickSize,
		       yat
		       );
	if(writeNum) {
	  sprintf(buff,"%1.1f",tick);
	  int len = strlen(buff);
	  int w = gdk_text_width(widget->style->font,buff,len);
	  int xt = drawOrigin.Col().V() - (w + tickSize + 2);
	  int yt = yat + textHeight/2;
	  gdk_draw_text(widget->window,widget->style->font,winGC,xt,yt,buff,len);
	}
      }
    }
    
  }
  
  //: Draw data.
  
  void Graph1dBodyC::DrawData() {
    GtkWidget *widget = Widget();
    
    // Setup clip rectangle.
    GdkRectangle rect;
#if 1
    rect.x = dataArea.Origin().Col().V();
    rect.y = dataArea.End().Row().V();
    rect.width = (dataArea.End().Col().V() - rect.x);
    rect.height = (dataArea.Origin().Row().V() - rect.y);
    //cerr << "DataArea:" << dataArea << "\n";
    //  cerr << "ClipRect:" << rect.x << " " << rect.y << "   Ext:" << rect.width << " " << rect.height << " \n";
    gdk_gc_set_clip_rectangle(winGC,&rect);
#endif
    
    for(UIntT gr = 0;gr < data.Size();gr++) {
      Array1dC<Point2dC> &dat = data[gr];
      if(dat.Size() <= 0)
	continue;
      Index2dC lat;
      bool doneFirst = false;
      for(Array1dIterC<Point2dC> it(dat);it.IsElm();it.Next()) {
	Index2dC at = MapPoint(it.Data());
	switch(plotMode) 
	  {
	  case PLOTM_NONE:
	    break;
	  case PLOTM_BAR:
	  case PLOTM_CIRCLE:
	    {
	      int csize = 6;
	      gdk_draw_arc(widget->window,
			   winGC,
			   1, // Fill
			 at.Col().V() - csize/2,
			   at.Row().V() - csize/2,
			   csize,csize,
			   0,360 * 65);
	    }
	    break;
	  case PLOTM_SQUARE:
	    {
	      int csize = 6;
	      gdk_draw_rectangle(widget->window,
				 winGC,
				 1, // Fill !
				 at.Col().V() - csize/2,
				 at.Row().V() - csize/2,
				 csize,csize);
	    }
	    break;
	  case PLOTM_POINT:
	    gdk_draw_point(widget->window,
			   winGC,
			   at.Col().V(),
			   at.Row().V()
			   );
	  }
	if(!doneFirst) 
	  doneFirst = true;
	else {
	  switch(plotJoin) 
	    {
	    case PLOTJ_NONE:
	      break;
	    case PLOTJ_DASHEDLINE:
	    case PLOTJ_LINE:
	      gdk_draw_line (widget->window,
			     winGC,
			     at.Col().V(),
			     at.Row().V(),
			     lat.Col().V(),
			     lat.Row().V()
			     );
	      break;
	    }
	}
	lat = at;
      }
    }
    
    // Restore Clip rectangle.
  
    Index2dC windowSize = Size();  
    rect.x = 0;
    rect.y = 0;
    rect.width = windowSize.Col().V();
    rect.height = windowSize.Row().V();
    gdk_gc_set_clip_rectangle(winGC,&rect);
    
  }
  
  
  //: Make graph fit all points.
  
  void Graph1dBodyC::FitAll() {
    if(data.Size() <= 0)
      return ;
    Fit(data[0]);
  }

  //: Fit view of data.
  
  void Graph1dBodyC::Fit(const Array1dC<Point2dC> &ndata) {
    Array1dIterC<Point2dC> it(ndata);
    if(!it.IsElm())
      return ;
    PRectangle2dC rect(it.Data(),it.Data());
    for(;it.IsElm();it.Next())
      rect.Involve(it.Data());
    origin = rect.Origin();
    int width = dataArea.End().Col().V() - dataArea.Origin().Col().V();
    int height = dataArea.Origin().Row().V() - dataArea.End().Row().V();
    cerr << "Width=" << width << " Height=" << height << "\n";
    scale = Point2dC(width,height) / rect.Size();
    cerr << "Origin=" << origin << " Scale=" << scale << "\n";
    PlaceTicks();
    RefreshAll();
  }
  
  //: Work out default tick setting.
  
  void Graph1dBodyC::PlaceTicks() {
    char buff[100];
    
    Vector2dC ovec = origin * scale;
    Vector2dC mvec = max * scale;
    
    // Find the longest yvalue;
    sprintf(buff,"%1.1f",ovec.Y());
    yValueWidth = strlen(buff) ;
    sprintf(buff,"%1.1f",mvec.Y());
    yValueWidth = Max(yValueWidth,(IntT) strlen(buff)) + 1;
    
    // Find the longest xvalue;
    sprintf(buff,"%1.1f",ovec.X());
    xValueWidth = strlen(buff) ;
    sprintf(buff,"%1.1f",mvec.X());
    xValueWidth = Max(xValueWidth,(IntT) strlen(buff)) + 1;
    
    // Work out where to put the ticks...
    
    majorTick = 50 / scale;
    minorTick = majorTick/5;
  }
  
  //: Do rounding of origin and scale so the sit on nice numbers.
  
  void Graph1dBodyC::RoundOriginAndScale() {
    
  }
  
  
  //: Setup some new data.
  
  IntT Graph1dBodyC::SetData(const Array1dC<Point2dC> &ndata,IntT graphNo) {
    if(graphNo < 0 || graphNo >= data.Size()) {
      // Extend array and add data.
      SArray1dC<Array1dC<Point2dC> > newun(data.Size() + 1);
      for(SArray1dIter2C<Array1dC<Point2dC>,Array1dC<Point2dC> > it(data,newun);
	  it.IsElm();it.Next()) 
	it.Data2() = it.Data1();
      graphNo = data.Size();
      data = newun;
    }
    data[graphNo] = ndata;
    if(!doneInit) {
      Fit(ndata);
      doneInit = true;
    } else
      RefreshData(); // Update the data.
    return graphNo;
  }
  
  //: Plot data on the graph.
  // the index is multiplied by inc, and off is added to get the 'x' values.
  
  IntT Graph1dBodyC::Plot(const Array1dC<RealT> &data,RealT inc,RealT off,IntT graphNo) {
    Array1dC<Point2dC> ent(data.Size());
    RealT at = (data.Range().Min() * inc) + off;
    for(Array1dIter2C<Point2dC,RealT> it(ent,data);it.IsElm();it.Next(),at += inc) 
      it.Data1() = Point2dC(at,it.Data2());
    return SetData(ent,graphNo);
  }

}
