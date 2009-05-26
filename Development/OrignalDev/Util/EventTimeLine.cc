// This file is part of Magellan, Broadcast Video Library 
// Copyright (C) 2005, OmniPerception Ltd.
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id: EventTimeLine.cc 5371 2006-02-28 08:18:33Z craftit $"
//! lib=OmniMagGUI

#include "Jack/EventTimeLine.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/Image/Font.hh"
#include  <gdk/gdk.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
using namespace RavlAudioN;
  //: Default constructor.
  
  EventTimeLineBodyC::EventTimeLineBodyC()
    : RawCanvasBodyC(15,15),
      timeSelected1(0.0,0.0,0.0),
      timeSelected(0.0),
      atMarker(0),
      markerLeft(0),
      markerRight(0),
      updateId(0),
      markerGc(0),
      markerGcL(0),
      markerGcR(0),
      text(0)
  {}
  
  EventTimeLineBodyC::EventTimeLineBodyC(IntT srow,IntT scol,const RealRangeC &rng,const TranscriptionBaseListC &_events)
    : RawCanvasBodyC(srow,scol),
      displayRange(rng),
      events(_events),
      timeSelected1(0.0,0.0,0.0),
      timeSelected(0.0),
      atMarker(0),
      markerLeft(0),
      markerRight(0),
      updateId(0),
      markerGc(0),
      markerGcL(0),
      markerGcR(0),
      text(0)
  {
  }
  
  //: Constructor.
  //!param: rng - Range of times to display.
  //!param: events - List of events.
  
  EventTimeLineBodyC::EventTimeLineBodyC(const RealRangeC &rng,const TranscriptionBaseListC &_events) 
    : RawCanvasBodyC(15,15),
      displayRange(rng),
      events(_events),
      timeSelected1(0.0,0.0,0.0),
      timeSelected(0.0),
      updateId(0),
      markerGc(0),
      markerGcL(0),
      markerGcR(0),
      text(0),
      label("label")
  {}

  EventTimeLineBodyC::EventTimeLineBodyC(IntT srow,IntT scol,const RealRangeC &rng)
    : RawCanvasBodyC(srow,scol),
      displayRange(rng),
      timeSelected1(0.0,0.0,0.0),
      timeSelected(0.0),
      updateId(0),
      markerGc(0), 
      markerGcL(0),
      markerGcR(0),
      text(0),
      label("label")
  {}
  
  //: Constructor.
  //!param: rng - Range of times to display.
  //!param: events - List of events.
  
  EventTimeLineBodyC::EventTimeLineBodyC(const RealRangeC &rng) 
    : RawCanvasBodyC(15,15),
      displayRange(rng),
      timeSelected1(0.0,0.0,0.0),
      timeSelected(0.0),
      updateId(0),
      markerGc(0),
      markerGcL(0),
      markerGcR(0),
      label("label")
  {}

  static bool DestroyGc(GdkGC *gc) {
    g_object_unref(gc);
    return true;
  }
  
  bool EventTimeLineBodyC::SetMarkers(RealT time,RealT left, RealT right){
    markerRight = right;
    markerLeft = left;
    SetMarker(time);
    return true;
  } 
  
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
  
  bool EventTimeLineBodyC::SetEvents(TranscriptionBaseListC &_events) {
    Manager.Queue(Trigger(EventTimeLineC(*this),&EventTimeLineC::GUISetEvents,_events));
    return true;
  }
  
  //: Set event list.
  
  bool EventTimeLineBodyC::GUISetEvents(TranscriptionBaseListC &_events) {
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
    if(markerGcL == 0) {
      markerGcL = gdk_gc_new(DrawArea()); 
      gdk_gc_copy(markerGcL,GUIDrawGC());
      
      GdkColor colour;
      colour.pixel = 0;
      colour.red = 0;
      colour.green = 255 * 255;
      colour.blue = 0;
      gdk_gc_set_rgb_fg_color (markerGcL,&colour);
    }
    if(markerGcR == 0) {
      markerGcR = gdk_gc_new(DrawArea()); 
      gdk_gc_copy(markerGcR,GUIDrawGC());
      
      GdkColor colour;
      colour.pixel = 0;
      colour.red = 0;
      colour.green = 0;
      colour.blue = 255 * 255;
      gdk_gc_set_rgb_fg_color (markerGcR,&colour);
    }
    if(text == 0) {
      text = gdk_gc_new(DrawArea()); 
      gdk_gc_copy(text,GUIDrawGC());
      
      GdkColor colour;
      colour.pixel = 0;
      colour.red = 255 * 255;
      colour.green = 200 * 255;
      colour.blue = 100 * 255;
      gdk_gc_set_rgb_fg_color (text,&colour);
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
    if(mousePress.HasChanged(1) && mousePress.IsCntrl()){
      DeleteEvent();
      timeSelected1(atMarker,markerLeft,markerRight);
    }
    else if(mousePress.HasChanged(1)&&mousePress.IsShift())
      SetEventVal(mousePress.At()[1] / scale + displayRange.Min());
    else if(mousePress.HasChanged(1)){
      //AddEvent();
    atMarker = (static_cast<RealT>(mousePress.At()[1]) / scale) + displayRange.Min();
#if 0
    // Dump range click is in.
    for(DLIterC<Tuple3C<IntT,RealRangeC,StringC> > it(events);it;it++) {
      if(it->Data2().Contains(time))
	cerr << "Time " << time << " in " << it->Data2() << "\n";
    }
#endif
    //cerr << "Press time=" << time << "\n";
      //timeSelected1(atMarker,markerLeft,markerRight);
      timeSelected(atMarker);
    }
    else if(mousePress.HasChanged(0)&&mousePress.IsShift())
      AddEvent();
    else if(mousePress.HasChanged(0)){
      markerLeft = mousePress.At()[1] / scale + displayRange.Min();
      timeSelected1(atMarker,markerLeft,markerRight);
    }
    else if(mousePress.HasChanged(2)){ 
      markerRight = mousePress.At()[1] / scale + displayRange.Min();
      timeSelected1(atMarker,markerLeft,markerRight);
    }	
    GUIDraw();
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
    
#if 1
    if(markerGcL != 0) {
      IndexRange2dC markRange(displayArea.Range1(),
			      IndexRangeC((markerLeft - displayRange.Min()) * scale,
					  ((markerLeft+1) - displayRange.Min()) * scale));
      
      if(markRange.Range2().Size() < 3) {// Make tiny bars are big enough to see.
	markRange.Range2().Expand((3 - markRange.Range2().Size())/2);
      }
      
      GUIDrawRectangle(markerGcL,markRange,true);
    }
#endif
    
    #if 1
    if(markerGcR != 0) {
      IndexRange2dC markRange(displayArea.Range1(),
			      IndexRangeC((markerRight - displayRange.Min()) * scale,
					  ((markerRight+1) - displayRange.Min()) * scale));
      
      if(markRange.Range2().Size() < 3) {// Make tiny bars are big enough to see.
	markRange.Range2().Expand((3 - markRange.Range2().Size())/2);
      }
      
      GUIDrawRectangle(markerGcR,markRange,true);
    }
#endif
    
    DLIterC<Tuple3C<IntT,RealRangeC,StringC> > it(events);
    
    ONDEBUG(cerr << "VertRange=" << vertRange << " Scale=" << scale << "\n");
    IndexC midV = vertRange.Center();
    GUIDrawLine(GUIDrawGCGrey(),Index2dC(midV,displayArea.Range2().Min()),Index2dC(midV,displayArea.Range2().Max()));
    
    for(;it;it++) {
      if(displayRange.IsOverlapping(it->Data2())){
      IndexRangeC rng2((it->Data2().Min() - displayRange.Min()) * scale,
		       (it->Data2().Max() - displayRange.Min()) * scale);
      //cerr << "Elm=" << rng2 << "\n";
      IndexRange2dC box(vertRange,rng2);
      if(box.Range2().Size() == 0)// Make tiny bars at least 1 pixel wide.
	box.Range2().Max()++; 
      box.ClipBy(displayArea);
      
      GdkGC* drawContext = gdk_gc_new(DrawArea()); 
      gdk_gc_copy(drawContext,GUIDrawGC());
      GdkColor colour;
      
      if(it->Data1() == 0){
        colour.pixel = 0;
        colour.red = 0;
        colour.green = 255 * 255;
        colour.blue = 0;
      }
      else if(it->Data1() == 4){
	colour.pixel = 0;
        colour.red = 255 * 255;
        colour.green = 0;
        colour.blue = 0;
      }
      else{
	colour.pixel = 0;
        colour.red = -255 * 255*it->Data1()/3;
        colour.green = -255 * 255*it->Data1()/3;
        colour.blue = -255 * 255*it->Data1()/3;
      }
      
      gdk_gc_set_rgb_fg_color (drawContext,&colour);
 
        GUIDrawRectangle(drawContext,box,true);
  
      }
    }
    
    GUIDrawText(text,GUIDrawFont(),Point2dC(10,10),label);
    
#if 0
    IndexC midH = displayArea.Range2().Center();
    GUIDrawLine(GUIDrawGCGrey(),Index2dC(displayArea.Range1().Min(),midH),Index2dC(displayArea.Range1().Max(),midH));
#endif
    return true;
  }
  
   RealT EventTimeLineBodyC::GetMarkerRight(){return markerRight;}
    RealT EventTimeLineBodyC::GetMarkerLeft(){return markerLeft;}
    RealT EventTimeLineBodyC::GetMarkerTime(){return atMarker;}
    
    bool EventTimeLineBodyC::AddEvent(){
      if(markerLeft < markerRight)
        AddEvent(RealRangeC(markerLeft,markerRight));
      else
        AddEvent(RealRangeC(markerRight,markerLeft));
        return true;
    }
    
    bool EventTimeLineBodyC::AddEvent(RealRangeC data){
      events+=Tuple3C<IntT,RealRangeC,StringC>(0,data,"");
      return true;
    }
    
    bool EventTimeLineBodyC::DeleteEvent(){
      if(markerLeft < markerRight)
        for(DLIterC<Tuple3C<IntT,RealRangeC,StringC> > it(events);it;it++)
          if(it.Data().Data2().Min() > markerLeft && it.Data().Data2().Min() < markerRight)
            it.Del();
      else
        for(DLIterC<Tuple3C<IntT,RealRangeC,StringC> > it(events);it;it++)
          if(it.Data().Data2().Min()  > markerRight && it.Data().Data2().Min() < markerLeft)
            it.Del();
      return true;
    }
   
    TranscriptionBaseListC &EventTimeLineBodyC::GetEvents(){return events;}
    
    bool EventTimeLineBodyC::SetEventVal(RealT time){
        for(DLIterC<Tuple3C<IntT,RealRangeC,StringC> > it(events);it;it++)
          if(it.Data().Data2().Contains(time)){
            it.Data().Data1() = (it.Data().Data1()+1) % 5;
	  GUIDraw();
	  }
      return true;
    }
    

  
}
