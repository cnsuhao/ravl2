#ifndef RAVLGUILIST_HEADER
#define RAVLGUILIST_HEADER 1
//////////////////////////////////////////////////
//! file="Ravl/GUI/GTK/List.hh"
//! lib=GUI
//! author="Charles Galambos"
//! rcsid="$Id$"
//! date="02/07/99"
//! example=exList.cc
//! docentry="Ravl.GUI.Control"

#include "Ravl/GUI/GTKTypes.hh"
#include "Ravl/GUI/CWidget.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal2.hh"
#include "Ravl/String.hh"

namespace RavlGUIN {

  class ListC;
  
  // GtkSelectionMode:
  //  GTK_SELECTION_SINGLE
  //  GTK_SELECTION_BROWSE
  //  GTK_SELECTION_MULTIPLE
  //  GTK_SELECTION_EXTENDED
  
  //! userlevel=Develop
  //: List body.
  
  class ListBodyC 
    : public WidgetBodyC
  {
  public:
    ListBodyC(const DListC<StringC> &choices,GtkSelectionMode selMode = GTK_SELECTION_SINGLE);
    //: Constructor from a list of strings.
    
    ListBodyC(const DListC<WidgetC> &lst,GtkSelectionMode selMode = GTK_SELECTION_SINGLE);
    //: Constructor from a list of strings.
    
    ListBodyC(GtkSelectionMode selMode = GTK_SELECTION_SINGLE);
    //: Constructor from a list of strings.
    
    virtual bool Create();
    //: Create the widget.
    
    DListC<StringC> Selected() const;
    //: Get current selection
    // Should only be called by the GUI thread !
    
    bool GUIAdd(WidgetC &widge);
    //: Add new widget to list.
    
    bool GUIDelS(StringC &text);
    //: Del string from list.
  
    bool GUIDel(WidgetC &widge);
    //: Del widget from list.
    
    void Add(const StringC &text);
    //: Add new string to list.
    
    void Add(WidgetC &widge);
    //: Add new widget to list.
    
    void Del(const StringC &text);
    //: Del string from list.
  
    void Del(WidgetC &widge);
    //: Del widget from list.
    
    
  protected:
    virtual void Destroy();
    //: Undo all refrences.
    
    DListC<WidgetC> children;
    GtkSelectionMode selMode;
    friend class ListC;
  };
  
  //! userlevel=Normal
  //: List handle.
  
  class ListC
    : public WidgetC
  {
  public:
    ListC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ListC(DListC<StringC> lst,GtkSelectionMode selMode = GTK_SELECTION_SINGLE)
      : WidgetC(*new ListBodyC(lst,selMode))
      {}
    //: Create a List box.
    
    ListC(const DListC<WidgetC> &lst,GtkSelectionMode selMode = GTK_SELECTION_SINGLE)
      : WidgetC(*new ListBodyC(lst,selMode))
    {}
    //: Constructor from a list of strings.
  
    ListC(GtkSelectionMode selMode)
      : WidgetC(*new ListBodyC(selMode))
    {}
  //: Create an empty List box.
  
  protected:
    ListC(ListBodyC &bod)
      : WidgetC(bod)
      {}
    //: Body constructor.
    
    ListBodyC &Body()
      { return static_cast<ListBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const ListBodyC &Body() const
      { return static_cast<const ListBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    bool GUIAdd(WidgetC &text)
      { return Body().GUIAdd(text); }
    //: Add new string to window.
    // GUI Thread only.
    
    bool GUIDelS(StringC &text)
      { return Body().GUIDelS(text); }
    //: Add new string to window.
    // GUI Thread only.
    
    bool GUIDel(WidgetC &obj)
      { return Body().GUIDel(obj); }
    //: Add new string to window.
    // GUI Thread only.
    
  public:
    Signal0C &SigSelected()
      { return Body().Signal("list_activate"); }
    //: Short cut clicked signal.
    
    DListC<StringC> Selected() const 
      { return Body().Selected(); }
    //: Get currently selected string.
    // Should only be called by the GUI thread !
    
    void Add(const StringC &text)
      { Body().Add(text); }
    //: Add new string to window.
    // Thread safe.
    
    void Add(WidgetC &text)
      { Body().Add(text); }
    //: Add new string to window.
    // Thread safe.
    
    void Del(const StringC &text)
      { Body().Del(text); }
    //: Add new string to window.
    // Thread safe.
    
    void Del(WidgetC &obj)
      { Body().Del(obj); }
    //: Add new string to window.
    // Thread safe.
    
    friend class ListBodyC;
  };
  
  
  template<class DataT>
  ListC List(const DListC<StringC> &lst,void (*func)(ListC &, DataT &ref),const DataT &dat = DataT())
  { 
    ListC ret(lst);
    Connect(ret.SigSelected(),func,ret,dat);
    return ret;    
  }  

  template<class DataT>
  ListC List(const DListC<StringC> &lst,const DataT &dat,void (DataT::*func)(StringC &ref))
  { 
    ListC ret(lst);
    Connect(ret.SigSelected(),dat,func);
    return ret;    
  }  
}



#endif
