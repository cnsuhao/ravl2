#ifndef RAVLGUIPACKINFO_HEADER
#define RAVLGUIPACKINFO_HEADER 1
////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/PackInfo.hh"
//! lib=GUI
//! docentry="Ravl.GUI.Layout"
//! author="Charles Galambos"
//! date="23/09/99"

#include "Ravl/GUI/OneChild.hh"

namespace RavlGUIN {

  //: Packing info widget.
  //! userlevel=Develop
  
  class PackInfoBodyC
    : public OneChildBodyC
  {
  public:
    PackInfoBodyC()
      {}
    //: Default constructor.
    
    PackInfoBodyC(const WidgetC &widge,bool nexpand = true,bool nfill = true,IntT npadding = 0)
      : OneChildBodyC(widge),
      expand(nexpand),
      fill(nfill),
      padding(npadding)
      {}
    //: Constructor.
    
    bool &Expand()
      { return expand; }
    //: Access expand flag.
    
    bool &Fill()
      { return fill; }
    //: Access fill flag.
    
    IntT &Padding()
      { return padding; }
    //: Padding.
  
  protected:
    virtual bool Create();
    //: Create the widget.
    
    virtual void Destroy();
    //: Undo all refrences.
    
    bool expand;
    bool fill;
    IntT padding;
  };
  
  //! userlevel=Normal
  //: Packing info widget.
  // This is a dummy widget which holds packing infomation
  // for its child.
  
  class PackInfoC
    : public OneChildC
  {
  public:
    PackInfoC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
  
    PackInfoC(const WidgetC &widge,bool expand,bool fill = true,IntT padding = 0)
      : OneChildC(*new PackInfoBodyC(widge,expand,fill,padding))
      {}
    //: Constructor.
    
    PackInfoC(WidgetC &other);
    //: Construct packing info from other widget.
    
  protected:
    PackInfoC(PackInfoBodyC &bod)
      : OneChildC(bod)
      {}
    //: Body constructor.
    
    PackInfoBodyC &Body() 
      { return static_cast<PackInfoBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const PackInfoBodyC &Body() const
      { return static_cast<const PackInfoBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
    bool &Expand()
      { return Body().Expand(); }
    //: Access expand flag.
    
    bool &Fill()
      { return Body().Fill(); }
    //: Access fill flag.
    
    IntT &Padding()
      { return Body().Padding(); }
    //: Padding.
    
  };
}


#endif

