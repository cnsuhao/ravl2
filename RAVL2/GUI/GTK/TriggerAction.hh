#ifndef RAVLGUI_TRIGGERACTION_HEADER
#define RAVLGUI_TRIGGERACTION_HEADER 1
/////////////////////////////////////////////////
//! rcsid="$Id: Button.hh 7430 2009-12-15 14:10:13Z craftit $"
//! file="Ravl/GUI/GTK/Button.hh"
//! lib=RavlGUI
//! author="Charles Galambos"
//! example=exButton.cc
//! date="23/03/1999"
//! docentry="Ravl.API.Graphics.GTK.Control"

#include "Ravl/GUI/Button.hh"

namespace RavlGUIN {

  //! Trigger the showing of a widget
  class TriggerShowWidgetBodyC
   : public TriggerBodyC
  {
  public:
    TriggerShowWidgetBodyC(const XMLFactoryContextC &context);
    //: XML factory constructor

    virtual void Invoke();
    //: Trigger event.
  protected:
    WidgetC m_targetWidget;
  };

  //! Trigger the showing of a widget
  class TriggerShowWidgetC
   : public TriggerC
  {
  public:
     TriggerShowWidgetC()
     {}
     //: Default constructor

     TriggerShowWidgetC(const XMLFactoryContextC &context)
       : TriggerC(new TriggerShowWidgetBodyC(context))
     {}
     //: XML factory constructor
  };


  //! Trigger the showing of a widget
  class TriggerHideWidgetBodyC
    : public TriggerBodyC
  {
  public:
    TriggerHideWidgetBodyC(const XMLFactoryContextC &context);
    //: XML factory constructor

    virtual void Invoke();
    //: Trigger event.

  protected:
    WidgetC m_targetWidget;
  };

  //! Trigger the showing of a widget
  class TriggerHideWidgetC
  : public TriggerC
  {
  public:
    TriggerHideWidgetC()
    {}
    //: Default constructor

    TriggerHideWidgetC(const XMLFactoryContextC &context)
     : TriggerC(new TriggerHideWidgetBodyC(context))
    {}
    //: XML factory constructor
  };

}
#endif
