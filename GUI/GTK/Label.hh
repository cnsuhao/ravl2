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
//! docentry="Ravl.API.GUI.Layout"
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
    LabelBodyC(const StringC &ntext);
    //: Constructor.
    
    virtual ~LabelBodyC() { }
    //: Have virtual methods - need virtual destructor

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
    
    bool Justify(GtkJustification& justify);
    //: Set justification mode
    // Values for justify are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKJUSTIFICATION">here</A>.

    bool Wrap(const bool& wrap);
    //: Set line wrap mode

    bool Label(const StringC &text);
    //: Update the text in the label.
    
    bool GUISetLabel(const StringC &txt);
    //: Set label.

  protected:

    bool GUIJustify(GtkJustification& justify);
    //: Set justification mode
    // Values for justify are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKJUSTIFICATION">here</A>.

    bool GUIWrap(const bool& wrap);
    //: Set line wrap mode
        
    StringC text;
    
    bool lineWrap;
    IntT justification;
    
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
    
    LabelC(const char *text)
      : WidgetC(*new LabelBodyC(text))
    {}
    //: Constructor
    
    LabelC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    LabelC(const WidgetC &base)
      : WidgetC(dynamic_cast<const LabelBodyC *>(BodyPtr(base)))
    {}
    //: Base class constructor.
    // If types don't match an invalid handle will be created.
    
  protected:
    LabelC(LabelBodyC &bod)
      : WidgetC(bod)
    {}
    //: Body constructor.
    
    LabelC(const LabelBodyC *bod)
      : WidgetC(bod)
    {}
    //: Body constructor.
    
    LabelBodyC &Body()
    { return static_cast<LabelBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const LabelBodyC &Body() const
    { return static_cast<const LabelBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    bool GUIJustify(GtkJustification& justify)
    { return Body().GUIJustify(justify); }
    //: Set justification mode
    // Values for justify are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKJUSTIFICATION">here</A>.

    bool GUIWrap(const bool& wrap)
    { return Body().GUIWrap(wrap); }
    //: Set line wrap mode

  public:
    bool GUISetLabel(const StringC &txt)
    { return Body().GUISetLabel(txt); }
    //: Set label.
    
    StringC &Label() 
    { return Body().Label(); }
    //: Access string.
    
    const StringC &Label() const 
    { return Body().Label(); }
    //: Access string.
    
    bool Label(const StringC &text)
    { return Body().Label(text); }
    //: Update the text in the label.
    
    bool Justify(GtkJustification& justify)
    { return Body().Justify(justify); }    
    //: Set justification mode
    // Values for justify are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKJUSTIFICATION">here</A>.

    bool Wrap(const bool& wrap)
    { return Body().Wrap(wrap); }    
    //: Set line wrap mode

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
