#ifndef RAVLGUIGRAPH1D_HEADER
#define RAVLGUIGRAPH1D_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id: Graph1d.hh 6596 2008-02-21 14:06:00Z ees1wc $"

#include "Ravl/GUI/RawCanvas.hh"
#include "Ravl/GUI/Menu.hh"
#include "Ravl/Point2d.hh"
#include "Ravl/Vector2d.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/SArray1d.hh"

namespace RavlGUIN {

  class Graph1dC;
  class MouseEventC;
  
  //! userlevel=Develop
  //: Graph of a 1d function
  
  class Graph1dBodyC
    : public RawCanvasBodyC
  {
  public:
    Graph1dBodyC(const Point2dC &org,const Point2dC &max,const Vector2dC &scale);
    //: Constructor.
    
    Graph1dBodyC(int sx,int sy);
    //: Constructor.
    
    virtual ~Graph1dBodyC();
    //: Destructor.
    
    void Init();
    //: Set things up...
    
    IntT SetData(const Array1dC<Point2dC> &data,IntT graphNo = -1);
    //: Setup some new data.
    
    void Fit(const Array1dC<Point2dC> &ndata);
    //: Fit view of data.
    
    void PlaceTicks();
    //: Work out default tick setting.
    
    IntT Plot(const Array1dC<RealT> &data,RealT inc = 1,RealT off = 0,IntT graphNo = -1);
    //: Plot data on the graph.
    // the index is multiplied by inc, and off is added to get the 'x' values.
    // returns the graph no.
    
    enum PlotModeT { PLOTM_NONE,PLOTM_POINT,PLOTM_CIRCLE,PLOTM_SQUARE,PLOTM_BAR };
    //: Point plotting mode.
    
    enum PlotJoinT { PLOTJ_NONE,PLOTJ_LINE,PLOTJ_DASHEDLINE };
    //: Point plotting mode.
    
    void RefreshData();
    //: Update data display.
    
    void RefreshAll();
    //: Update data display.
    
    void RoundOriginAndScale();
    //: Do rounding of origin and scale so the sit on nice numbers.
    
    //void GUISetData(const Array1dC<Point2dC> &data,IntT graphNo = -1);
    //: Set data.
    
    void FitAll();
    //: Make graph fit all points.
    
protected:
    void MouseMoveEvent(MouseEventC &me);
    //: Mouse event.

    void MousePressEvent(MouseEventC &me);
    //: Mouse event.
    
    void MouseReleaseEvent(MouseEventC &me);
    //: Mouse event.
    
    void ExposeEvent(GdkEvent* &event);
    //: Draw the graph into the window.
    
    void GUIRefreshAll();
    //: Refresh all of graph.
    
    void GUIRefreshData();
    //: Update data display.
    
    void ConfigureEvent(GdkEvent* &event);
    //: Configuration event.
   
    virtual bool Create();
    //: Create the widget.
    
    void DrawXAxis();
    //: Draw X axis.
    
    void DrawYAxis();
    //: Draw Y axis.

    void DrawData();
    //: Draw Y axis.
    
    Index2dC MapPoint(const Point2dC &pnt);
    //: Map data point to place in display.
    
    IntT MapX(RealT d);
    //: Map x value to place in display.
    
    IntT MapY(RealT d);
    //: Map y value to place in display.
    
    Point2dC ReverseMap(const Index2dC &pnt);
    //: Take a pixel and map back to a value.
    
    GdkGC *winGC;  // Graphical context for drawing.
    
    Point2dC origin; // Origin of graph.
    Point2dC max;    // Maximum of graph.
    Vector2dC scale; // Scaling of graph.
    Vector2dC minorTick; // Fequency of minor ticks.
    Vector2dC majorTick; //  Fequency of major ticks.
    
    SArray1dC<Array1dC<Point2dC> > data; // Data to plot.
    IntT textWidth;
    IntT textHeight;
    
    IndexRectangleC dataArea;
    
    IntT minorTickSize;
    IntT majorTickSize;
    bool doMinorTick; // Display minor ticks ?
    bool doMajorTick; // Display major ticks ?
    PlotModeT plotMode;
    PlotJoinT plotJoin;
    
    IntT yValueWidth;
    IntT xValueWidth;
    StringC caption;
    StringC xAxisLabel;
    StringC yAxisLabel;
    
    bool doneInit; // Have we got an inital scale and offset ?
    
    MenuC backMenu;
    
    friend class Graph1dC;
  };
  
  //! userlevel=Normal
  //: Graph of a 1d function.
  
  class Graph1dC
    : public RawCanvasC
  {
  public:
    Graph1dC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    Graph1dC(int width,int height)
      : RawCanvasC(*new Graph1dBodyC(width,height))
    {}
    //: Default constructor.
    
    Graph1dC(const Point2dC &org  = Point2dC(0,0),const Point2dC &max = Point2dC(0,0),const Vector2dC &scale = Vector2dC(0.1,0.1))
      : RawCanvasC(*new Graph1dBodyC(org,max,scale))
    {}
    //: Constructor.
    
  protected:
    Graph1dC(Graph1dBodyC &bod)
      : RawCanvasC(bod)
    {}
    //: Body constructor.
    
    Graph1dBodyC &Body()
    { return static_cast<Graph1dBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const Graph1dBodyC &Body() const
    { return static_cast<const Graph1dBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    void GUIRefreshData()
    { return Body().GUIRefreshData(); }
    //: Update data display.
    
    void GUIRefreshAll()
    { return Body().GUIRefreshAll(); }
    //: Update display.
    
    //  IntT GUISetData(const Array1dC<Point2dC> &data,IntT graphNo = -1)
    //{ return Body().GUISetData(data,graphNo); }
    //: Setup some new data.
    
  public:
    
    IntT SetData(const Array1dC<Point2dC> &data,IntT graphNo = -1)
    { return Body().SetData(data,graphNo); }
    //: Setup some new data.
    
    void RefreshAll()
    { Body().RefreshAll(); }
    //: Update display.
    
    void RefreshData()
    { return Body().RefreshData(); }
    //: Update data display.
    
    void Fit(const Array1dC<Point2dC> &ndata)
    { return Body().Fit(ndata); }
    //: Fit view of data.
    
    IntT Plot(const Array1dC<RealT> &data,RealT inc = 1,RealT off = 0,IntT graphNo = -1)
    { return Body().Plot(data,inc,off,graphNo); }
    //: Plot data on the graph.
    // the index is multiplied by inc, and off is added to get the 'x' values.
    // returns the graph no.
    
    IntT Plot(const SArray1dC<RealT> &data,RealT inc = 1,RealT off = 0,IntT graphNo = -1)
    { return Body().Plot(Array1dC<RealT>(data),inc,off,graphNo); }
    //: Plot data on the graph.
    // the index is multiplied by inc, and off is added to get the 'x' values.
    // returns the graph no.
    
    friend class Graph1dBodyC;
  };

}

#endif
