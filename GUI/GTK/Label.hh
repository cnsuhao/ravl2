// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_LABEL_HEADER
#define RAVLGUI_LABEL_HEADER 1
////////////////////////////////////////////
//! file="Ravl/GUI/GTK/Label.hh"
//! lib=RavlGUI
//! author="Charles Galambos"
//! date="23/03/1999"
//! docentry="Ravl.GUI.Layout"
//! rcsid="$Id$"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/String.hh"

namespace RavlGUIN {

  class LabelC;
  
  //! userlevel=Develop
  //: Label body
  
  class LabelBodyC 
    : public WidgetBodyC
  {
  public:
    LabelBodyC(const StringC &ntext)
      : text(ntext.Copy())
    {}
    //: Constructor.
    
    virtual StringC Name() const;
    //: Get name of widget.
    // Defaults to WidgetName(), but may be differnt
    // for Lables etc.
    
    virtual bool Create();
    //: Create the widget.
    
    StringC &Label() { return text; }
    //: Access string.
    
    const StringC &Label() const { return text; }
    //: Access string.
    
    bool Label(const StringC &text);
    //: Update the text in the label.
    
  protected:
    bool GUISetLabel(StringC &txt);
    //: Set label.
    
    StringC text;
    
    friend class LabelC;
  };
  
  
  //! userlevel=Normal
  //: Label 
  // This displays some text.
  
  class LabelC 
    : public WidgetC
  {
  public:
    LabelC(const StringC &text)
      : WidgetC(*new LabelBodyC(text))
    {}
    //: Constructor
    
    LabelC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    LabelC(LabelBodyC &bod)
      : WidgetC(bod)
    {}
    //: Body constructor.
    
    LabelBodyC &Body()
    { return static_cast<LabelBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const LabelBodyC &Body() const
    { return static_cast<const LabelBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    bool GUISetLabel(StringC &txt)
    { return Body().GUISetLabel(txt); }
    //: Set label.
    
  public:
    StringC &Label() 
    { return Body().Label(); }
    //: Access string.
    
    const StringC &Label() const 
    { return Body().Label(); }
    //: Access string.
    
    bool Label(const StringC &text)
    { return Body().Label(text); }
    //: Update the text in the label.
    
    friend class LabelBodyC;
  };
  
  
  inline LabelC Label(const char *label,const char *tooltip = 0) { 
    LabelC ret = LabelC(label);
    if(tooltip != 0)
      ret.SetToolTip(tooltip);
    return ret;
  }
  //: Create a text label.
  // With an optional tooltip. (Doesn't work at the moment...)
  
}

#endif
