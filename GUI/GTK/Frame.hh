// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUIFRAME_HEADER
#define RAVLGUIFRAME_HEADER 1
//////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/Frame.hh"
//! lib=RavlGUI
//! author="Charles Galambos"
//! date="17/06/99"
//! docentry="Ravl.GUI.Layout"

#include "Ravl/GUI/OneChild.hh"
#include "Ravl/String.hh"

namespace RavlGUIN {
  
  class FrameC;
  
  //! userlevel=Develop
  //: Put a frame around some other widgets.
  
  class FrameBodyC
    : public OneChildBodyC
  {
  public:
    FrameBodyC();
    //: Default constructor.
    
    FrameBodyC(const WidgetC &widge,int nboarder,const StringC &ntitle = "");
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
    void SetShadowType(GtkShadowType shadow);
    //: Set frame type.
    
    void SetLabel(StringC &name);
    //: Set label

    bool GUISetLabel(StringC &name);
    //: Set label
    // Call with GUI thread only!
    
  protected:
    bool GUISetShadow(GtkShadowType &nshadow);
    //: Setup shadow.
    
    StringC title;
    int boarder;
    GtkShadowType shadow;
    GtkResizeMode resizeMode;
    
    friend class FrameC;
  };
  
  //! userlevel=Normal
  //: Put a frame around some other widgets.
  
  class FrameC
    : public OneChildC
  {
  public:
    FrameC()
      {}
    //: Default constructor.

    FrameC(const WidgetC &widge,const StringC &title,int boarder = 2)
      : OneChildC(*new FrameBodyC(widge,boarder,title))
      {}
    //: Constructor.
    
    FrameC(const WidgetC &widge,int boarder)
      : OneChildC(*new FrameBodyC(widge,boarder))
      {}
    //: Constructor.
    
  protected:
    FrameC(FrameBodyC &body)
      : OneChildC(body)
      {}
    //: Body constructor.
    
    FrameBodyC &Body() 
      { return static_cast<FrameBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    bool GUISetShadow(GtkShadowType &shadow)
      { return Body().GUISetShadow(shadow); }
    //: Setup shadow.
    
    
  public:
    FrameC(WidgetC &widge)
      : OneChildC(widge)
      {
	if(dynamic_cast<FrameBodyC *>(&WidgetC::Body()) == 0)
	  Invalidate();
      }
    //: Base constructor.

    bool GUISetLabel(StringC &name)
      { return Body().GUISetLabel(name); }
    //: Set label
    // Call with GUI thread only!
    
    void SetShadowType(GtkShadowType shadow)
      { Body().SetShadowType(shadow); }
    //: Set frame type.
    
    void SetLabel(StringC &name)
      { Body().SetLabel(name); }
    //: Set label
    
    friend class FrameBodyC;
  };

}
#endif
