#ifndef RAVLGUISCROLLEDAREA_HEADER
#define RAVLGUISCROLLEDAREA_HEADER 1
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=GUI
//! author="Charles Galambos"
//! file="Ravl/GUI/GTK/ScrolledArea.hh"
//! date="03/04/99"
//! docentry="Ravl.GUI.Layout"

#include "Ravl/GUI/OneChild.hh"

namespace RavlGUIN {

  //! userlevel=Develop
  //: ScrolledArea body.
  
  class ScrolledAreaBodyC 
    : public OneChildBodyC
  {
  public:
    ScrolledAreaBodyC(const WidgetC &achild,IntT isx = -1,IntT isy = -1,bool vauto = true,bool hauto = true);
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
  protected:
    IntT isx,isy; // Inital area size.
    bool vauto,hauto; // Automatic scrollbars ?
  };
  
  //! userlevel=Normal
  //: ScrolledArea handle.
  
  class ScrolledAreaC
    : public OneChildC
  {
  public:
    ScrolledAreaC(const WidgetC &achild,IntT isx = -1,IntT isy = -1,bool vauto = true,bool hauto = true)
      : OneChildC(*new ScrolledAreaBodyC(achild,isx,isy,vauto,hauto))
      {}
    //: Create a scrolled area.
    // isx,isy set the inital size of the area.
  };

}
#endif
