// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_BUTTON_HEADER
#define RAVLGUI_BUTTON_HEADER 1
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/Button.hh"
//! lib=RavlGUI
//! author="Charles Galambos"
//! example=exButton.cc
//! date="23/03/1999"
//! docentry="Ravl.GUI.Control"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/GUI/GTKTypes.hh"
#include "Ravl/GUI/Pixmap.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal2.hh"

namespace RavlGUIN {
  
  class ButtonC;
  
  //! userlevel=Develop
  //: Button body.
  
  class ButtonBodyC 
    : public WidgetBodyC
  {
  public:
    ButtonBodyC(const char *label = 0,const char *tooltip = 0);
    //: Constructor.
    
    ButtonBodyC(const char *nlabel,const PixmapC &pixm);
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
    bool GUISetLabel(StringC &text);
    //: Set toggle label.
    // GUI thread only.
    
    void SetLabel(StringC &text);
    //: Set toggle label.
    
  protected:
    virtual GtkWidget *BuildWidget(const char *lab = 0);
    //: Create the actual widget.
    // This allows different types of buttons to
    // be created easily.
    
    bool state;
    PixmapC pix;
    StringC label;    // length() = 0 == none
    friend class ButtonC;
  };
  
  //! userlevel=Normal
  //: Button handle.
  
  class ButtonC
    : public WidgetC
  {
  public:
    ButtonC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ButtonC(const char *label,const char *tooltip = 0);
    //: Create a button.
    
    ButtonC(const PixmapC &pixm,const char *label = 0)
      : WidgetC(*new ButtonBodyC(label,pixm))
    {}
    //: Create a button.
    // If label is set to 0 none will be used.
  
    ButtonC(ButtonBodyC &bod)
      : WidgetC(bod)
      {}
    //: Body constructor.
    
  protected:
    
    ButtonBodyC &Body()
    { return static_cast<ButtonBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const ButtonBodyC &Body() const
    { return static_cast<const ButtonBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
    Signal0C &SigClicked() 
    { return Body().Signal("clicked"); }
    //: Short cut clicked signal.
    
    bool GUISetLabel(StringC &text)
    { return Body().GUISetLabel(text); }
    //: Set toggle label.
    // GUI thread only.
    
    void SetLabel(StringC &text)
    { Body().SetLabel(text); }
    //: Set toggle label.
    
    friend class ButtonBodyC;
  };
  
  inline 
  ButtonC Button(const char *label,const char *tooltip = 0) {
    ButtonC ret;
    if(tooltip != 0)
      ret = ButtonC(label,tooltip);
    else
      ret = ButtonC(label);
    return ret;        
  }
  //: Create a button with no function attached.
  // here just for consistancy.

  template<class DataT>
  ButtonC Button(const char *label,bool (*func)(DataT &dat),const DataT &dat)
  { 
    ButtonC ret = ButtonC(label);
    Connect(ret.Signal("clicked"),func,dat);
    return ret;    
  }
  
  template<class Data1T,class Data2T>
  ButtonC Button(const char *label,bool (*func)(Data1T &,Data2T &),const Data1T &dat1,const Data2T &dat2)
  { 
    ButtonC ret = ButtonC(label);
    Connect(ret.Signal("clicked"),func,dat1,dat2);
    return ret;    
  }
  
  template<class ObjT,class DataT>
  ButtonC Button(const char *label,const ObjT &obj,bool (ObjT::*func)(DataT &dat),const DataT &dat)
  { 
    ButtonC ret = ButtonC(label);
    Connect(ret.Signal("clicked"),obj,func,dat);
    return ret;    
  }

  template<class ObjT,class DataT>
  ButtonC ButtonR(const char *label,ObjT &obj,bool (ObjT::*func)(DataT &dat),const DataT &dat )
  { 
    ButtonC ret = ButtonC(label);
    ConnectRef(ret.Signal("clicked"),obj,func,dat);
    return ret;    
  }
  //: Create button that calls a function.
  // This does NOT make a reference to obj.
  
  template<class ObjT,class DataT>
  ButtonC Button(const char *label,const char *tooltip,const ObjT &obj,bool (ObjT::*func)(DataT &dat),const DataT &dat)
  { 
    ButtonC ret = ButtonC(label,tooltip);
    Connect(ret.Signal("clicked"),obj,func,dat);
    return ret;    
  }

  template<class ObjT>
  ButtonC Button(const char *label,const ObjT &obj,bool (ObjT::*func)())
  { 
    ButtonC ret = ButtonC(label);
    Connect(ret.Signal("clicked"),obj,func);
    return ret;    
  }
  //: Create button that calls a function.

  template<class ObjT>
  ButtonC ButtonR(const char *label,ObjT &obj,bool (ObjT::*func)())
  { 
    ButtonC ret = ButtonC(label);
    ConnectRef(ret.Signal("clicked"),obj,func);
    return ret;    
  }
  //: Create button that calls a function.
  // This does NOT make a reference to obj.
  
  template<class ObjT>
  ButtonC Button(const char *label,const char *tooltip,const ObjT &obj,bool (ObjT::*func)())
  { 
    ButtonC ret = ButtonC(label,tooltip);
    Connect(ret.Signal("clicked"),obj,func);
    return ret;    
  }

  template<class ObjT>
  ButtonC ButtonR(const char *label,const char *tooltip,ObjT &obj,bool (ObjT::*func)())
  { 
    ButtonC ret = ButtonC(label,tooltip);
    ConnectRef(ret.Signal("clicked"),obj,func);
    return ret;    
  }

  template<class ObjT>
  ButtonC Button(const PixmapC &pix,const ObjT &obj,bool (ObjT::*func)())
  {
    ButtonC ret = ButtonC(pix,0);
    Connect(ret.Signal("clicked"),obj,func);
    return ret;    
  }
  
}

#undef VCPPARGFIX

#endif
