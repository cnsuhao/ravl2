// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_GUIEVENTTIMELINE_HEADER
#define RAVL_GUIEVENTTIMELINE_HEADER 1
//! author="Charles Galambos"
//! rcsid="$Id: EventTimeLine.hh 5371 2006-02-28 08:18:33Z craftit $"
//! docentry="Ravl.API.GUI.Util"

#include "Ravl/GUI/RawCanvas.hh"
#include "Ravl/RealRange1d.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/Threads/Signal3.hh"
#include "Ravl/Threads/Signal.hh"
#include "Jack/Transcription.hh"

namespace RavlGUIN {
  using namespace RavlAudioN;
  using namespace RavlGUIN;
  using namespace RavlImageN;
  class EventTimeLineC;
  
  //! userlevel=Develop
  //: Event time line.
  // Display a set of events as black marks on a white backgrouond. A red marker indicates current position.
  
  class EventTimeLineBodyC 
    : public RawCanvasBodyC 
  {
  public:
    EventTimeLineBodyC();
    //: Default constructor.
    
    EventTimeLineBodyC(const RealRangeC &rng,const TranscriptionBaseListC &events);
    //: Constructor.
    //!param: rng - Range of times to display.
    //!param: events - List of events.

    EventTimeLineBodyC(IntT srow,IntT scol,const RealRangeC &rng,const TranscriptionBaseListC &events);
    //: Constructor.
    //!param: rng - Range of times to display.
    //!param: events - List of events.

    EventTimeLineBodyC(const RealRangeC &rng);
    //: Constructor.
    //!param: rng - Range of times to display.
    //!param: events - List of events.

    EventTimeLineBodyC(IntT srow,IntT scol,const RealRangeC &rng);
    //: Constructor.
    //!param: rng - Range of times to display.
    //!param: events - List of events.
    
    ~EventTimeLineBodyC();
    //: Destructor.
    
    bool SetDisplayRange(RealRangeC &rng);
    //: Set range of times to display
    
    bool GUISetDisplayRange(RealRangeC &rng);
    //: Set range of times to display
    
    Signal3C<RealT,RealT,RealT> &SigTimeSelected1()
    { return timeSelected1; }
    //: Get marker position signal
    
    Signal1C<RealT> &SigTimeSelected()
    { return timeSelected; }
    //: Frame selected signal
    
    bool Goto(RealT &time);
    //: Centre on a specific time.
    
    bool GUIGoto(RealT &time);
    //: Centre on a specific time.
    
    bool SetMarker(RealT time);
    //: Set marker position.
    
    bool GUISetMarker(RealT time);
    //: Set marker position.
    
    bool SetEvents(TranscriptionBaseListC &events);
    //: Set event list.
    
    bool GUISetEvents(TranscriptionBaseListC &events);
    //: Set event list.
    
    bool SetDisplaySpan(RealT &size);
    //: Set the length of time to display.
    
    bool GUISetDisplaySpan(RealT &size);
    //: Set the length of time to display.
    
    StringC &Label(){return label;}
    //: Access timeline a label
    
    RealT GetMarkerRight();
    //: Get right marker
    
    RealT GetMarkerLeft();
    //: Get left marker
    
    RealT GetMarkerTime();
    //: Get time selected
    
    bool AddEvent();
    //: Add Event between left and right markers
    
    bool AddEvent(RealRangeC data);
    //: Add Event with range data
    
    bool DeleteEvent();
    //: Delete Event whose position starts between left and right markers
    // may want to change
    
    bool SetEventVal(RealT time);
    //: Change value of events at time. Cycles through 0 to 5
    // may want to change
    
    bool SetMarkers(RealT time, RealT left,RealT right);
    //: Set marker positions
    
    TranscriptionBaseListC &GetEvents();
    //: Get Event List
    
  protected:
    virtual bool Create();
    //: Create the widget.
    
    bool EventConfigure(GdkEvent* &event);
    //: Configure.
    
    bool EventExpose(GdkEvent* &event);
    //: Expose of area.
    
    bool EventMousePress(MouseEventC &mousePress);
    //: Event mouse press.
    //  Middle mouse button selects time, left positions left marker, right right marker
    // Left plus shift adds label
    // Middle plus ctrl deletes label whose range lies between l+r markers
    // Middle plus shift changes label value
    
    bool GUIDraw();
    //: Draw widget on screen.
    
    IndexRange2dC displayArea; // Area to use for displaying images.
    
    RealRangeC displayRange; // Range of times to display.
    TranscriptionBaseListC events; // list of events
    
    Signal3C<RealT,RealT,RealT> timeSelected1; // Frame selected signal
    Signal1C<RealT> timeSelected; // Frame selected signal
    
    RealT atMarker; // Marker for where you are in the sequence.
    RealT markerLeft; // Left marker
    RealT markerRight; // Right marker

    UIntT updateId;
    
    GdkGC *markerGc;
    GdkGC *markerGcL;
    GdkGC *markerGcR;
    GdkGC *text;
    
    StringC label; //label
    
    
    friend class EventTimeLineC;
  };
  
  //! userlevel=Normal
  //: Event time line.
  // Display a set of events as black marks on a white backgrouond. A red marker indicates current position.
  
  class EventTimeLineC 
    : public RawCanvasC 
  {
  public:
    EventTimeLineC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    EventTimeLineC(const RealRangeC &rng,const TranscriptionBaseListC &events) 
      : RawCanvasC(*new EventTimeLineBodyC(rng,events))
    {}
    //: Constructor.
    //!param: rng - Range of times to display.
    //!param: events - List of events.

    EventTimeLineC(const RealRangeC &rng) 
      : RawCanvasC(*new EventTimeLineBodyC(rng))
    {}
    //: Constructor.
    //!param: rng - Range of times to display.
    //!param: events - List of events.
    
    EventTimeLineC(IntT srow,IntT scol,const RealRangeC &rng ,const TranscriptionBaseListC &events) 
      : RawCanvasC(*new EventTimeLineBodyC(srow,scol,rng,events))
    {}
    //: Constructor.
    //!param: rng - Range of times to display.
    //!param: events - List of events.
    
    EventTimeLineC(IntT srow,IntT scol,const RealRangeC &rng) 
      : RawCanvasC(*new EventTimeLineBodyC(srow,scol,rng))
    {}
    //: Constructor.
    //!param: rng - Range of times to display.
    //!param: events - List of events.
    
    
  protected:
    EventTimeLineC(EventTimeLineBodyC &bod)
      : RawCanvasC(bod)
    {}
    
    EventTimeLineBodyC& Body()
    { return static_cast<EventTimeLineBodyC&>(WidgetC::Body()); }
    //: Access body.

    const EventTimeLineBodyC& Body() const
    { return static_cast<const EventTimeLineBodyC&>(WidgetC::Body()); }
    //: Access body.
    
  public:
    bool Goto(RealT &time)
    { return Body().Goto(time); }
    //: Centre on a specific time.
    
    bool GUIGoto(RealT &time)
    { return Body().GUIGoto(time); }
    //: Centre on a specific time.
    
    bool SetMarker(RealT time)
    { return Body().SetMarker(time); }
    //: Set marker position.
    
    bool GUISetMarker(RealT time)
    { return Body().GUISetMarker(time); }
    //: Set marker position.
    
    bool SetEvents(TranscriptionBaseListC &events)
    { return Body().SetEvents(events); }
    //: Set event list.
    
    bool GUISetEvents(TranscriptionBaseListC &events)
    { return Body().GUISetEvents(events); }
    //: Set event list.
    
    bool SetDisplayRange(RealRangeC &rng)
    { return Body().SetDisplayRange(rng); }
    //: Set range of times to display
    
    bool GUISetDisplayRange(RealRangeC &rng)
    { return Body().GUISetDisplayRange(rng); }
    //: Set range of times to display
    
    bool SetDisplaySpan(RealT &size)
    { return Body().SetDisplaySpan(size); }
    //: Set the length of time to display.
    
    bool GUISetDisplaySpan(RealT &size)
    { return Body().GUISetDisplaySpan(size); }
    //: Set the length of time to display.
    
    StringC & Label() 
    { return Body().Label(); }
    //: Access label
    
    Signal1C<RealT> &SigTimeSelected1()
    { return Body().SigTimeSelected1(); }
    //: Frame selected signal
    
    Signal1C<RealT> &SigTimeSelected()
    { return Body().SigTimeSelected(); }
    //: Frame selected signal
    
    RealT GetMarkerRight(){return Body().GetMarkerRight();}
    //: Get marker right
    
    RealT GetMarkerLeft(){return Body().GetMarkerLeft();}
    //: Get marker left
    
    RealT GetMarkerTime(){return Body().GetMarkerTime();}
    //: Get marker time
    
    bool AddEvent() 
    { return Body().AddEvent(); }
    //: Add Event between left and right markers
    
    bool AddEvent(RealRangeC data) 
    { return Body().AddEvent(data); }
    //: Add Event with range data
    
    bool DeleteEvent() 
    { return Body().DeleteEvent(); }
    //: Delete Event whose position starts between left and right markers
    // may want to change
    
    bool SetEventVal(RealT time) 
    { return Body().SetEventVal(time); }
    //: Delete Event whose position starts between left and right markers
    // may want to change
    
    bool SetMarkers(RealT time,RealT left, RealT right){return Body().SetMarkers(time,left,right);}
    //: Set markers in position
    
    TranscriptionBaseListC &GetEvents() 
    { return Body().GetEvents(); }
    //: Access event lis
    
    friend class EventTimeLineBodyC;
  };
  
  
}



#endif
