#ifndef RAVLGUI_SEPARATOR_HEADER
#define RAVLGUI_SEPARATOR_HEADER 1
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/Separator.hh"
//! lib=GUI
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Layout"

#include "Ravl/GUI/Widget.hh"

namespace RavlGUIN {

  //! userlevel=Develop
  //: Vertical or horizontal separator.
  
  class SeparatorBodyC
    : public WidgetBodyC
  {
  public:
    SeparatorBodyC(bool nvert)
      : vert(nvert)
      {}
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
  protected:
    bool vert;
  };
  
  //! userlevel=Normal
  //: Vertical or horizontal separator.
  
  class SeparatorC
    : public WidgetC
  {
  public:
    SeparatorC()
    {}
    //: Default constructor.
    
    SeparatorC(bool nvert)
      : WidgetC(*new SeparatorBodyC(nvert))
      {}
    //: Construct a separator.
    
  };

  inline 
  SeparatorC Separator(bool vert) { 
    return SeparatorC(vert);
  }
  //: Create a separator.

  inline 
  SeparatorC VSeparator() { 
    return SeparatorC(true);
  }
  //: Create a vertical separator.

  inline 
  SeparatorC HSeparator() { 
    return SeparatorC(false);
  }
  //: Create a horizontal separator.
  
}



#endif
