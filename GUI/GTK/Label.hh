#ifndef RAVLGUILABEL_HEADER
#define RAVLGUILABEL_HEADER 1
////////////////////////////////////////////
//! file="Ravl/GUI/GTK/Label.hh"
//! lib=GUI
//! author="Charles Galambos"
//! date="23/03/99"
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
      : text(ntext)
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
    // Creayes an invalid handle.
    
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
