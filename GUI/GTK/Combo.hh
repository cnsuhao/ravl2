#ifndef RAVLGUICOMBO_HEADER
#define RAVLGUICOMBO_HEADER 1
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/Combo.hh"
//! lib=GUI
//! docentry="Ravl.GUI.Control"
//! author="Charles Galambos"
//! date="25/06/99"

#include "Ravl/GUI/GTKTypes.hh"
#include "Ravl/GUI/Widget.hh"
#include "Ravl/GUI/Pixmap.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal2.hh"
#include "Ravl/String.hh"

namespace RavlGUIN {

  class ComboC;
  
  //! userlevel=Develop
  //: Combo body.
  
  class ComboBodyC 
    : public WidgetBodyC
  {
  public:
    ComboBodyC(const DListC<StringC> &choices,bool editable = true);
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
    StringC Selected() const;
    //: Get currently selected string.
    // Should only be called by the GUI thread !
    
  protected:
    DListC<StringC> choices;
    bool editable;
    friend class ComboC;
  };
  
  //! userlevel=Normal
  //: Combo handle.
  
  class ComboC
    : public WidgetC
  {
  public:
    ComboC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ComboC(const DListC<StringC> &lst,bool editable = true)
      : WidgetC(*new ComboBodyC(lst,editable))
      {}
    //: Create a Combo box.
    
    
  protected:
    ComboC(ComboBodyC &bod)
      : WidgetC(bod)
      {}
    //: Body constructor.
    
    ComboBodyC &Body()
      { return static_cast<ComboBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const ComboBodyC &Body() const
      { return static_cast<const ComboBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
    Signal0C &SigSelected()
      { return Body().Signal("combo_activate"); }
    //: Short cut clicked signal.
    
    StringC Selected() const 
      { return Body().Selected(); }
    //: Get currently selected string.
    // Should only be called by the GUI thread !
    
    friend class ComboBodyC;
  };
  
  template<class DataT>
  ComboC Combo(const DListC<StringC> &lst,void (*func)(ComboC &, DataT &ref),const DataT &dat = DataT(),bool editable = true)
  { 
    ComboC ret(lst,editable);
    Connect(ret.SigSelected(),func,ret,dat);
    return ret;    
  }  
  //: Contruct a combo box, call back to function.
  
  template<class DataT>
  ComboC Combo(const DListC<StringC> &lst,const DataT &dat,void (DataT::*func)(StringC &ref),bool editable = true)
  { 
    ComboC ret(lst,editable);
    Connect(ret.SigSelected(),dat,func);
    return ret;    
  }  
  //: Contruct a combo box, call back to method in class.

  template<class DataT>
  ComboC Combo(const DListC<StringC> &lst,const char *tooltip,const DataT &dat,void (DataT::*func)(StringC &ref),bool editable = true)
  {
    ComboC ret(lst,editable);
    Connect(ret.SigSelected(),dat,func);
    ret.SetToolTip(tooltip);
    return ret;    
  }  
  //: Contruct a combo box, call back to method in class.
  // With tooltip.

  template<class DataT>
  ComboC ComboR(const DListC<StringC> &lst,DataT &dat,void (DataT::*func)(StringC &ref),bool editable = true)
  { 
    ComboC ret(lst,editable);
    ConnectRef(ret.SigSelected(),dat,func);
    return ret;    
  }  
  //: Contruct a combo box, call back to method in refrenced class.

  template<class DataT>
  ComboC ComboR(const DListC<StringC> &lst,char *tooltip,const DataT &dat,void (DataT::*func)(StringC &ref),bool editable = true)
  {
    ComboC ret(lst,editable);
    ConnectRef(ret.SigSelected(),dat,func);
    ret.SetToolTip(tooltip);
    return ret;    
  }  
  //: Contruct a combo box, call back to method in refrenced class.
  // With tooltip.
  
}



#endif
