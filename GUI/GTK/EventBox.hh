#ifndef RAVLGUIEVENTBOX_HEADER
#define RAVLGUIEVENTBOX_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/EventBox.hh"
//! lib=GUI
//! userlevel=Normal
//! docentry="Ravl.GUI.Control"
//! author="Charles Galambos"
//! date="17/06/99"

#include "Ravl/GUI/OneChild.hh"

namespace RavlGUIN {
  //: Event box widget.
  
  class EventBoxBodyC
    : public OneChildBodyC 
  {
  public:
    EventBoxBodyC()
      {}
    //: Default constructor.
    
    EventBoxBodyC(const WidgetC &widge)
      : OneChildBodyC(widge)
      {}
    //: Default constructor.
    
    virtual bool Create();
    //: Create the widget.
  };
  
  //: Event box.
  
  class EventBoxC
    : public OneChildC 
  {
  public:
    EventBoxC()
      {}
    //: Default constructor
    
    EventBoxC(const WidgetC &widge,bool)
      : OneChildC(*new EventBoxBodyC(widge))
      {}
    //: Constructor
  
  protected:
    EventBoxBodyC &Body() 
      { return static_cast<EventBoxBodyC &>(WidgetC::Body()); }
    //: Access body.
  
  public:
    EventBoxC(WidgetC &widge)
      : OneChildC(widge)
      {
	if(dynamic_cast<EventBoxBodyC *>(&WidgetC::Body()) == 0)
	  Invalidate();
      }
    //: Base constructor.
    
  };
}

#endif
