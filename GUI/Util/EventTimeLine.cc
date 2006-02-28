// This file is part of Magellan, Broadcast Video Library 
// Copyright (C) 2005, OmniPerception Ltd.
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=OmniMagGUI

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

  //: Default constructor.
  
  EventTimeLineBodyC::EventTimeLineBodyC()
    : RawCanvasBodyC(15,15),
      timeSelected(0.0),
      atMarker(0),
      updateId(0),
      markerGc(0)
  {}
  
  EventTimeLineBodyC::EventTimeLineBodyC(IntT srow,IntT scol,const RealRangeC &rng,const DListC<Tuple2C<IntT,RealRangeC> > &_events)
    : RawCanvasBodyC(srow,scol),
      displayRange(rng),
      events(_events),
      timeSelected(0.0),
      atMarker(0),
      updateId(0),
      markerGc(0)
  {}
  
  //: Constructor.
  //!param: rng - Range of times to display.
  //!param: events - List of events.
  
  EventTimeLineBodyC::EventTimeLineBodyC(const RealRangeC &rng,const DListC<Tuple2C<IntT,RealRangeC> > &_events) 
    : RawCanvasBodyC(15,15),
      displayRange(rng),
      events(_events),
      timeSelected(0.0),
      updateId(0),
      markerGc(0)
  {}

  EventTimeLineBodyC::EventTimeLineBodyC(IntT srow,IntT scol,const RealRangeC &rng)
    : RawCanvasBodyC(srow,scol),
      displayRange(rng),
      timeSelected(0.0),
      updateId(0),
      markerGc(0)
  {}
  
  //: Constructor.
  //!param: rng - Range of times to display.
  //!param: events - List of events.
  
  EventTimeLineBodyC::EventTimeLineBodyC(const RealRangeC &rng) 
    : RawCanvasBodyC(15,15),
      displayRange(rng),
      timeSelected(0.0),
      updateId(0),
      markerGc(0)
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
  }
  
  //: Create the widget.
  
  bool EventTimeLineBodyC::Create() {
    ConnectRef(Signal("expose_event"),*this,&EventTimeLineBodyC::EventExpose);
    ConnectRef(Signal("configure_event"),*this,&EventTimeLineBodyC::EventConfigure);
    ConnectRef(Signal("button_press_event"),*this,&EventTimeLineBodyC::EventMousePress);
    
    if(!RawCanvasBodyC::Create())
      return false;
        
    return true;
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

  //: Set marker position.
  
  bool EventTimeLineBodyC::SetMarker(RealT time) {
    Manager.Queue(Trigger(EventTimeLineC(*this),&EventTimeLineC::GUISetMarker,time));    
    return true;
  }
  
  //: Set marker position.
  
  bool EventTimeLineBodyC::GUISetMarker(RealT time) {
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
    ONDEBUG(cerr << "EventTimeLineBodyC::GUIGotot(). Time=" << time << " \n");
    RealT size = displayRange.Size()/2;
    displayRange = RealRangeC(time - size ,time + size);
    // atMarker = time;
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
    RealT scale = (RealT)displayArea.Range2().Size() / displayRange.Size();
    RealT time = (static_cast<RealT>(mousePress.At()[1]) / scale) + displayRange.Min();
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
    if(displayArea.Cols() < 1 || displayArea.Rows() < 1)
      return true; // No display area.
    GUIDrawRectangle(GUIDrawGCWhite(),displayArea,true);
    
    RealT scale = (RealT)displayArea.Range2().Size() / displayRange.Size();
    IndexRangeC vertRange = displayArea.Range1().Shrink(4);
    
#if 1
    if(markerGc != 0) {
      IndexRange2dC markRange(displayArea.Range1(),
			      IndexRangeC((atMarker - displayRange.Min()) * scale,
					  ((atMarker+1) - displayRange.Min()) * scale));
      
      if(markRange.Range2().Size() < 3) {// Make tiny bars are big enough to see.
	markRange.Range2().Expand((3 - markRange.Range2().Size())/2);
      }
      
      GUIDrawRectangle(markerGc,markRange,true);
    }
#endif
    
    DLIterC<Tuple2C<IntT,RealRangeC> > it(events);
    
    // Skip though stuff before.
    // FIXME:-Could cache ?
    for(;it && it->Data2().Max() < displayRange.Min();it++) ; 
    
    // Render visible part.
    
    
    ONDEBUG(cerr << "VertRange=" << vertRange << " Scale=" << scale << "\n");
    IndexC midV = vertRange.Center();
    GUIDrawLine(GUIDrawGCGrey(),Index2dC(midV,displayArea.Range2().Min()),Index2dC(midV,displayArea.Range2().Max()));
    
    for(;it && (it->Data2().Min() <= displayRange.Max());it++) {
      IndexRangeC rng2((it->Data2().Min() - displayRange.Min()) * scale,
		       (it->Data2().Max() - displayRange.Min()) * scale);
      //cerr << "Elm=" << rng2 << "\n";
      IndexRange2dC box(vertRange,rng2);
      if(box.Range2().Size() == 0)// Make tiny bars at least 1 pixel wide.
	box.Range2().Max()++; 
      box.ClipBy(displayArea);
      GUIDrawRectangle(GUIDrawGCBlack(),box,true);
    }
    
    
#if 0
    IndexC midH = displayArea.Range2().Center();
    GUIDrawLine(GUIDrawGCGrey(),Index2dC(displayArea.Range1().Min(),midH),Index2dC(displayArea.Range1().Max(),midH));
#endif
    return true;
  }

  
}
