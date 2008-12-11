// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_GUIEVENTTIMELINE_HEADER
#define RAVL_GUIEVENTTIMELINE_HEADER 1
//! author="Charles Galambos"
//! rcsid="$Id$"
//! docentry="Ravl.API.Graphics.GTK.Util"

#include "Ravl/GUI/RawCanvas.hh"
#include "Ravl/RealRange1d.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/Tuple2.hh"

namespace RavlGUIN {
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
    
    EventTimeLineBodyC(const RealRangeC &rng,const DListC<Tuple2C<IntT,RealRangeC> > &events);
    //: Constructor.
    //!param: rng - Range of times to display.
    //!param: events - List of events.

    EventTimeLineBodyC(IntT srow,IntT scol,const RealRangeC &rng,const DListC<Tuple2C<IntT,RealRangeC> > &events);
    //: Constructor.
    //!param: rng - Range of times to display.
    //!param: events - List of events.

    EventTimeLineBodyC(const RealRangeC &rng,bool useMarker = true);
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
    
    bool SetEvents(DListC<Tuple2C<IntT,RealRangeC> > &events);
    //: Set event list.
    // The event list must be sorted.
    
    bool GUISetEvents(DListC<Tuple2C<IntT,RealRangeC> > &events);
    //: Set event list.
    // The event list must be sorted.
    
    bool SetDisplaySpan(RealT &size);
    //: Set the length of time to display.
    
    bool GUISetDisplaySpan(RealT &size);
    //: Set the length of time to display.
    
    bool GUISetUseMarker(bool marker);
    //: Set use marker.
  protected:
    virtual bool Create();
    //: Create the widget.
    
    virtual bool Create(GtkWidget *_widget);
    //: Create the widget.
    
    virtual bool CommonCreate(GtkWidget *_widget = 0);
    //: Create the widget.
    
    bool EventConfigure(GdkEvent* &event);
    //: Configure.
    
    bool EventExpose(GdkEvent* &event);
    //: Expose of area.
    
    bool EventMousePress(MouseEventC &mousePress);
    //: Event mouse press.
    
    bool GUIDraw();
    //: Draw widget on screen.
    
    IndexRange2dC displayArea; // Area to use for displaying images.
    
    RealRangeC displayRange; // Range of times to display.
    DListC<Tuple2C<IntT,RealRangeC> > events;
    
    Signal1C<RealT> timeSelected; // Frame selected signal
    
    RealT atMarker; // Marker for where you are in the sequence.
    
    
    UIntT updateId;
    
    GdkGC *markerGc;
    
    bool m_useMarker;
    
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

    EventTimeLineC(const RealRangeC &rng,const DListC<Tuple2C<IntT,RealRangeC> > &events) 
      : RawCanvasC(*new EventTimeLineBodyC(rng,events))
    {}
    //: Constructor.
    //!param: rng - Range of times to display.
    //!param: events - List of events.
    
    EventTimeLineC(const RealRangeC &rng,bool useMarker = true) 
      : RawCanvasC(*new EventTimeLineBodyC(rng,useMarker))
    {}
    //: Constructor.
    //!param: rng - Range of times to display.
    //!param: events - List of events.
    
    EventTimeLineC(IntT srow,IntT scol,const RealRangeC &rng ,const DListC<Tuple2C<IntT,RealRangeC> > &events) 
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
    
    bool SetEvents(DListC<Tuple2C<IntT,RealRangeC> > &events)
    { return Body().SetEvents(events); }
    //: Set event list.
    // The event list must be sorted.
    
    bool GUISetEvents(DListC<Tuple2C<IntT,RealRangeC> > &events)
    { return Body().GUISetEvents(events); }
    //: Set event list.
    // The event list must be sorted.
    
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
    
    Signal1C<RealT> &SigTimeSelected()
    { return Body().SigTimeSelected(); }
    //: Frame selected signal
    
    bool GUISetUseMarker(bool marker)
    { return Body().GUISetUseMarker(marker); }
    //: Set use marker.
    
    friend class EventTimeLineBodyC;
  };
  
  
}



#endif
