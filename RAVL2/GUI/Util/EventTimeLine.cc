// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlGUIUtil

#include "Ravl/GUI/EventTimeLine.hh"
#include "Ravl/GUI/Manager.hh"
#include  <gdk/gdk.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {

  const RealT EventTimeLineBodyC::m_arrowWidth  = 0.025;
  const RealT EventTimeLineBodyC::m_arrowBorder = 0.25;
  
  //: Default constructor.
  
  EventTimeLineBodyC::EventTimeLineBodyC()
    : RawCanvasBodyC(15,15),
      m_localSegment(3,-8),
      timeSelected(0.0),
      atMarker(0),
      updateId(0),
      markerGc(0),
      segmentGc(0)
  {}
  
  EventTimeLineBodyC::EventTimeLineBodyC(IntT srow,IntT scol,const RealRangeC &rng,const DListC<Tuple2C<IntT,RealRangeC> > &_events)
    : RawCanvasBodyC(srow,scol),
      displayRange(rng),
      events(_events),
      m_localSegment(3,-8),
      timeSelected(0.0),
      atMarker(0),
      updateId(0),
      markerGc(0),
      segmentGc(0)
  {}
  
  //: Constructor.
  //!param: rng - Range of times to display.
  //!param: events - List of events.
  
  EventTimeLineBodyC::EventTimeLineBodyC(const RealRangeC &rng,const DListC<Tuple2C<IntT,RealRangeC> > &_events) 
    : RawCanvasBodyC(15,15),
      displayRange(rng),
      events(_events),
      m_localSegment(3,-8),
      timeSelected(0.0),
      updateId(0),
      markerGc(0),
      segmentGc(0)
  {}

  EventTimeLineBodyC::EventTimeLineBodyC(IntT srow,IntT scol,const RealRangeC &rng)
    : RawCanvasBodyC(srow,scol),
      displayRange(rng),
      m_localSegment(3,-8),
      timeSelected(0.0),
      updateId(0),
      markerGc(0),
      segmentGc(0)
  {}
  
  //: Constructor.
  //!param: rng - Range of times to display.
  //!param: events - List of events.
  
  EventTimeLineBodyC::EventTimeLineBodyC(const RealRangeC &rng) 
    : RawCanvasBodyC(15,15),
      displayRange(rng),
      m_localSegment(3,-8),
      timeSelected(0.0),
      updateId(0),
      markerGc(0),
      segmentGc(0)
  {}

  static bool DestroyGc(GdkGC *gc) {
    g_object_unref(gc);
    return true;
  }
  
  //: Destructor.
  
  EventTimeLineBodyC::~EventTimeLineBodyC() {
    if(markerGc != 0) {
      Manager.Queue(Trigger(DestroyGc,markerGc));
      markerGc = 0;
    }
    if(segmentGc != 0) {
      Manager.Queue(Trigger(DestroyGc,segmentGc));
      segmentGc = 0;      
    }
  }
  
  //: Create the widget.
  
  bool EventTimeLineBodyC::CommonCreate(GtkWidget *_widget) {
    ConnectRef(Signal("expose_event"),*this,&EventTimeLineBodyC::EventExpose);
    ConnectRef(Signal("configure_event"),*this,&EventTimeLineBodyC::EventConfigure);
    ConnectRef(Signal("button_press_event"),*this,&EventTimeLineBodyC::EventMousePress);
    
    bool ret = false;
    if (_widget == NULL)
      ret = RawCanvasBodyC::Create();
    else
      ret = RawCanvasBodyC::Create(_widget);
    
    return ret;
  }

  //: Set range of times to display
  
  bool EventTimeLineBodyC::SetDisplayRange(RealRangeC &rng) 
  {
    Manager.QueueOnGUI(Trigger(EventTimeLineC(*this),&EventTimeLineC::GUISetDisplayRange,rng));
    return true; 
  }

  //: Set range of times to display
  
  bool EventTimeLineBodyC::GUISetDisplayRange(RealRangeC &rng) {
    displayRange = rng; 
    ONDEBUG(cerr << "EventTimeLineBodyC::GUISetDisplayRange(). Range=" << displayRange << " \n");
    GUIDraw();
    return true;
  }
  
  //: Set the local segment.
  
  bool EventTimeLineBodyC::GUISetLocalSegment(const RealRangeC &segRange) {
    ONDEBUG(cerr << "EventTimeLineBodyC::GUISetLocalSegment(const RealRangeC &segRange="<<segRange<<")\n");
    if(m_localSegment != segRange) {
      m_localSegment = segRange;
      GUIDraw();
    }
    return true;
  }
  
  //: Set marker position.
  
  bool EventTimeLineBodyC::SetMarker(RealT time) {
    Manager.Queue(Trigger(EventTimeLineC(*this),&EventTimeLineC::GUISetMarker,time));    
    return true;
  }
  
  //: Set marker position.
  
  bool EventTimeLineBodyC::GUISetMarker(RealT time) {
    ONDEBUG(cerr << "EventTimeLineBodyC::GUISetMarker(RealT time=" << time << ")\n");
    atMarker = time;
    GUIDraw();
    return true;
  }
  
  //: Centre on a specific time.
  
  bool EventTimeLineBodyC::Goto(RealT &time) {
    Manager.Queue(Trigger(EventTimeLineC(*this),&EventTimeLineC::GUIGoto,time));
    return true;
  }
  
  //: Centre on a specific time.
  
  bool EventTimeLineBodyC::GUIGoto(RealT &time) {
    ONDEBUG(cerr << "EventTimeLineBodyC::GUIGoto(). Time=" << time << " \n");
    RealT size = displayRange.Size()/2;
    displayRange = RealRangeC(time - size ,time + size);
    //atMarker = time;
    GUIDraw();
    return true;
  }
  
  //: Set the length of time to display.
  
  bool EventTimeLineBodyC::SetDisplaySpan(RealT &size) {
    Manager.Queue(Trigger(EventTimeLineC(*this),&EventTimeLineC::GUISetDisplaySpan,size)); 
    return true;
  }
  
  //: Set the length of time to display.
  
  bool EventTimeLineBodyC::GUISetDisplaySpan(RealT &size) {
    ONDEBUG(cerr << "bool EventTimeLineBodyC::GUISetDisplaySpan(RealT &size=" << size << ")\n");
    RealT time = displayRange.Center();
    RealT val = size / 2;
    displayRange = RealRangeC(time - val,time + val);
    GUIDraw();
    return true;
  }


  //: Set event list.
  
  bool EventTimeLineBodyC::SetEvents(DListC<Tuple2C<IntT,RealRangeC> > &_events) {
    Manager.Queue(Trigger(EventTimeLineC(*this),&EventTimeLineC::GUISetEvents,_events));
    return true;
  }
  
  //: Set event list.
  
  bool EventTimeLineBodyC::GUISetEvents(DListC<Tuple2C<IntT,RealRangeC> > &_events) {
    events = _events;
    GUIDraw();
    return true;
  }

  //: Set the inactive segment list
  bool EventTimeLineBodyC::SetActiveSegments(DListC<RealRangeC> & _segments)
  {
    Manager.Queue(Trigger(EventTimeLineC(*this), &EventTimeLineC::GUISetActiveSegments, _segments));
    return true;
  }


  //: Set the inactive segment list
  bool EventTimeLineBodyC::GUISetActiveSegments(DListC<RealRangeC> & _segments)
  {
    m_activeSegments = _segments;
    GUIDraw();
    return true;
  }



  //: Handle configure event.
  
  bool EventTimeLineBodyC::EventConfigure(GdkEvent* &event) {
    ONDEBUG(cerr << "EventTimeLineBodyC::EventConfigure(). \n");
    IndexRange2dC newRec;
    TranslateConfigureEvent(event,newRec);
    if(newRec == displayArea)
      return true; // Same size, nothing to do!
    displayArea = newRec;
    // Other config...
    if(markerGc == 0) {
      markerGc = gdk_gc_new(DrawArea()); 
      gdk_gc_copy(markerGc,GUIDrawGC());
      
      GdkColor colour;
      colour.pixel = 0;
      colour.red = 255 * 255;
      colour.green = 0;
      colour.blue = 0;
      gdk_gc_set_rgb_fg_color (markerGc,&colour);
    }
    if(segmentGc == 0) {
      segmentGc = gdk_gc_new(DrawArea()); 
      gdk_gc_copy(segmentGc,GUIDrawGC());
      
      GdkColor colour;
      colour.pixel = 0;
      colour.red = 128 * 255;
      colour.green = 128 * 255;
      colour.blue = 255 * 255;
      gdk_gc_set_rgb_fg_color (segmentGc,&colour);      
    }
    return true;
  }
  
  //: Expose of area.
  
  bool EventTimeLineBodyC::EventExpose(GdkEvent* &event) {
    ONDEBUG(cerr << "EventTimeLineBodyC::EventExpose(). \n");
    IntT toFollow;
    IndexRange2dC newRec;
    TranslateExposeEvent(event,newRec,toFollow);
    GUIDraw();
    return true;
  }
  
  //: Event mouse press.
  
  bool EventTimeLineBodyC::EventMousePress(MouseEventC &mousePress) {
    ONDEBUG(cerr << "EventTimeLineBodyC::EventMousePress(). \n");
    IndexC mouseCol = mousePress.At()[1];
    IntT arrowWidth = Floor(displayArea.Range2().Size() * m_arrowWidth);

    ONDEBUG(cerr << "mouseCol:" << mouseCol << "\tarrowWidth: " << arrowWidth);
    if (mouseCol < displayArea.Range2().Min() + arrowWidth) {
      // Left arrow clicked
      DLIterC< Tuple2C<IntT, RealRangeC> > it(events);
      for (it.Last(); it; it--) {
        if (it->Data2().Min() < atMarker)
          break;
      }
      
      if (it) {
        if (it->Data2().Contains(atMarker))
          atMarker--;
        else
          atMarker = it->Data2().Max() - 1;
        timeSelected(atMarker);
      }
      
      return true;
    }
    
    if (mouseCol > displayArea.Range2().Max() - arrowWidth) {
      // Right arrow clicked
      DLIterC< Tuple2C<IntT, RealRangeC> > it(events);
      for(; it; it++) {
        if (it->Data2().Max() - 1 > atMarker)
          break;
      }
      
      if (it) {
        if (it->Data2().Contains(atMarker))
          atMarker++;
        else
          atMarker = it->Data2().Min();
        timeSelected(atMarker);
      }
      
      return true;
    }

    // Get the time
    RealT scale = static_cast<RealT>(displayArea.Range2().Size()) / displayRange.Size();
    RealT time = (static_cast<RealT>(mouseCol.V()) / scale) + displayRange.Min();

#if 0
    // Dump range click is in.
    for(DLIterC<Tuple2C<IntT,RealRangeC> > it(events);it;it++) {
      if(it->Data2().Contains(time))
        cerr << "Time " << time << " in " << it->Data2() << "\n";
    }
#endif
    
    //cerr << "Press time=" << time << "\n";
    timeSelected(time);
    return true;
  }


  //: Draw widget on screen.
  
  bool EventTimeLineBodyC::GUIDraw() {
    ONDEBUG(cerr << "EventTimeLineBodyC::GUIDraw(). Range=" << displayRange << " Events=" << events.Size() << "\n");

    cerr << "display area " << displayArea
         << "\ndisplay range" << displayRange
         << "\nlocal segment" << m_localSegment
      << "\n at marker" << atMarker << endl;


    if(displayArea.Cols() < 1 || displayArea.Rows() < 1)
      return true; // No display area.
    
    // Clear the box
    GUIDrawRectangle(GUIDrawGCGrey(), displayArea, true);
    
    RealT scale = static_cast<RealT>(displayArea.Range2().Size()) / displayRange.Size();
    ONDEBUG(cerr << "scale=" << scale << "\n");
    
    // Render visible part.
    IndexC midV = displayArea.Range1().Center();
    IntT arrowWidth = Floor(displayArea.Range2().Size() * m_arrowWidth);
    IntT arrowBorder = Floor(static_cast<RealT>(arrowWidth) * m_arrowBorder);
    IndexC minCol = displayArea.Range2().Min() + arrowWidth;
    IndexC maxCol = displayArea.Range2().Max() - arrowWidth;
    IndexRangeC vertRange(displayArea.Range1().Shrink(4));
    
    // How much time do the arrow obscure?
    RealT arrowTime = m_arrowWidth * displayRange.Size();
    IndexRange2dC arrowBox(vertRange, displayArea.Range2().Shrink(arrowWidth));


    // draw active segments
    for (DLIterC<RealRangeC> iter(m_activeSegments) ; iter.IsElm() ; iter.Next())
    {
      IndexRangeC rng2((iter->Min() - displayRange.Min()) * scale,
                       (iter->Max() - displayRange.Min()) * scale);
      IndexRangeC rng1 = displayArea.Range1();
      IndexRange2dC box(rng1, rng2);
      box.Range2().ClipBy(arrowBox.Range2());
      GUIDrawRectangle(GUIDrawGCWhite(),box,true);
    }



    if(markerGc != 0) {
      IndexRange2dC markRange(displayArea.Range1(),
                              IndexRangeC((atMarker - displayRange.Min()) * scale,
                                          ((atMarker+1) - displayRange.Min()) * scale));
      
      if(markRange.Range2().Size() < 3) {// Make tiny bars are big enough to see.
        markRange.Range2().Expand((3 - markRange.Range2().Size())/2);
      }
      
      markRange.Range2().ClipBy(arrowBox.Range2());
      cerr << "\n markerGc range = " << markRange << "******&&&&&&&&&&********** \n" ;

      GUIDrawRectangle(markerGc,markRange,true);
    }



    // Draw segment.
    if(segmentGc != 0 && m_localSegment.Size() > 0 && m_localSegment.IsOverlapping(displayRange)) {
      RealRangeC dispSegment((m_localSegment.Min() - displayRange.Min()) * scale,
                             (m_localSegment.Max() - displayRange.Min()) * scale);
      
      if(dispSegment.Size() == 0) // Make tiny bars at least 1 pixel wide.
        dispSegment.Max()++;
      IndexRange2dC markRange(displayArea.Range1().Shrink(3),
                              dispSegment.IndexRange());
      
      markRange.Range2().ClipBy(arrowBox.Range2());
      if(markRange.Range2().Size() > 0)
        GUIDrawRectangle(segmentGc,markRange,true);
    }
    
    // Draw the centre line
    GUIDrawLine(GUIDrawGCBlack(),Index2dC(midV,minCol),Index2dC(midV,maxCol));

    // Draw the arrow (left)
    GUIDrawLine(GUIDrawGCBlack(), Index2dC(midV, displayArea.Range2().Min() + arrowBorder), Index2dC(vertRange.Min(), minCol - arrowBorder));
    GUIDrawLine(GUIDrawGCBlack(), Index2dC(midV, displayArea.Range2().Min() + arrowBorder), Index2dC(vertRange.Max(), minCol - arrowBorder));
    GUIDrawLine(GUIDrawGCBlack(), Index2dC(vertRange.Min(), minCol - arrowBorder),          Index2dC(vertRange.Max(), minCol - arrowBorder));
    // Draw the arrow (right)
    GUIDrawLine(GUIDrawGCBlack(), Index2dC(midV, displayArea.Range2().Max() - arrowBorder), Index2dC(vertRange.Min(), maxCol + arrowBorder));
    GUIDrawLine(GUIDrawGCBlack(), Index2dC(midV, displayArea.Range2().Max() - arrowBorder), Index2dC(vertRange.Max(), maxCol + arrowBorder));
    GUIDrawLine(GUIDrawGCBlack(), Index2dC(vertRange.Min(), maxCol + arrowBorder),          Index2dC(vertRange.Max(), maxCol + arrowBorder));
    
    
    // Skip though stuff before.
    // FIXME: Could cache?
    DLIterC< Tuple2C<IntT, RealRangeC> > it(events);
    const RealT maxLimit = displayRange.Min() + arrowTime;
    for(;it && it->Data2().Max() < maxLimit;it++) ;
    
    // Draw until end of displayed time
    const RealT minLimit = displayRange.Max() - arrowTime;
    for( ; it && it->Data2().Min() <= minLimit; it++) {
      IndexRangeC rng2((it->Data2().Min() - displayRange.Min()) * scale,
                       (it->Data2().Max() - displayRange.Min()) * scale);
      //      ONDEBUG(cerr << "Elm=" << rng2 << "\n");
      IndexRange2dC box(vertRange, rng2);
      if(box.Range2().Size() == 0) // Make tiny bars at least 1 pixel wide.
        box.Range2().Max()++; 
      box.ClipBy(arrowBox);
      GUIDrawRectangle(GUIDrawGCBlack(),box,true);
    }
#if 0
    IndexC midH = displayArea.Range2().Center();
    GUIDrawLine(GUIDrawGCGrey(),Index2dC(displayArea.Range1().Min(),midH),Index2dC(displayArea.Range1().Max(),midH));
#endif
    return true;
  }

  
}
