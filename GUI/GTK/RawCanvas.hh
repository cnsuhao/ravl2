#ifndef RAVLGUIRAWCANVAS_HEADER 
#define RAVLGUIRAWCANVAS_HEADER  1
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/RawCanvas.hh"
//! lib=GUI
//! author="Charles Galambos"
//! date="23/09/99"
//! docentry="Ravl.GUI.Control"

#include "Ravl/GUI/Widget.hh"

namespace RavlGUIN {

  //! userlevel=Develop
  //: RawCanvas body.
  
  class RawCanvasBodyC
    : public WidgetBodyC 
  {
  public:
    RawCanvasBodyC(int nsx,int nsy)
      : sx(nsx),sy(nsy)
      {}
    //: Default constructor.
    
  protected:  
    virtual bool Create();
    //: Create the widget.
    
    virtual void Destroy()
      { WidgetBodyC::Destroy(); }
    //: Undo all refrences.
    // Placeholder only.
    
  private:
    int sx,sy;
  };
  
  //! userlevel=Normal
  //: RawCanvas handle.
  
  class RawCanvasC
    : public WidgetC 
  {
  public:
    RawCanvasC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    RawCanvasC(int sx,int sy)
      : WidgetC(*new RawCanvasBodyC(sx,sy))
      {}
    //: Constructor.  
    
  };
  
}

#endif
