#ifndef RAVLGUILBOX_HEADER
#define RAVLGUILBOX_HEADER 1
////////////////////////////////////////////
//! file="Ravl/GUI/GTK/LBox.hh"
//! lib=GUI
//! author="Charles Galambos"
//! date="23/03/99"
//! docentry="Ravl.GUI.Layout"
//! rcsid="$Id$"

#include "Ravl/GUI/CWidget.hh"

namespace RavlGUIN {
  
  //! userlevel=Develop
  //: Layout box
  
  class LBoxBodyC 
    : public ContainerWidgetBodyC 
  {
  public:
    LBoxBodyC()
      : vert(true),
	boarder(0),
	homogeneous(false),
	spacing(0)
	{}
    //: Default constructor.
    
    LBoxBodyC(const DListC<WidgetC> &widges,bool nvert = false,IntT nboarder = 0,bool nhomogeneous = false,IntT nspacing = 0)
      : ContainerWidgetBodyC(widges),
	vert(nvert),
	boarder(nboarder),
	homogeneous(nhomogeneous),
	spacing(nspacing)
	{}
    //: Constructor
    
    LBoxBodyC(const WidgetC &widges,bool nvert = false,IntT nboarder = 0,bool nhomogeneous = false,IntT nspacing = 0)
      : ContainerWidgetBodyC(),
	vert(nvert),
	boarder(nboarder),
	homogeneous(nhomogeneous),
	spacing(nspacing)
	{ children.InsLast(widges); }
    //: Constructor
    
    LBoxBodyC(bool nvert,IntT nboarder = 0,bool nhomogeneous = false,IntT nspacing = 0)
      : ContainerWidgetBodyC(),
	vert(nvert),
	boarder(nboarder),
	homogeneous(nhomogeneous),
	spacing(nspacing)
	{}
    //: Constructor
    
    virtual bool Create();
    //: Create the widget.
    
  protected:
    virtual void Destroy()
	{ ContainerWidgetBodyC::Destroy(); }
    //: Undo all refrences.
    
    bool vert; // Vertical layout ?
    IntT boarder;
    bool homogeneous;
    IntT spacing;
  };
  
  //! userlevel=Normal
  //: Layout box


  class LBoxC 
    : public ContainerWidgetC 
  {
  public:
    LBoxC();
    //: Default constructor
    
    LBoxC(const DListC<WidgetC> &widges,bool vert = false,IntT nboarder = 0,bool nhomogeneous = false,IntT nspacing = 0)
      : ContainerWidgetC(*new LBoxBodyC(widges,vert,nboarder,nhomogeneous,nspacing))
	{}
    //: Constructor
    
    LBoxC(const WidgetC &widges,bool vert = false,IntT nboarder = 0,bool nhomogeneous = false,IntT nspacing = 0)
      : ContainerWidgetC(*new LBoxBodyC(widges,vert,nboarder,nhomogeneous,nspacing))
	{}
    //:  Constructor
    
    LBoxC(bool vert,IntT nboarder = 0,bool nhomogeneous = false,IntT nspacing = 0)
      : ContainerWidgetC(*new LBoxBodyC(vert,nboarder,nhomogeneous,nspacing))
	{}
    //:  Constructor
  };
  
  inline 
  LBoxC VBox(const DListC<WidgetC> &widges,int boarder = 0,bool nhomogeneous = false,IntT nspacing = 0)
  { return LBoxC(widges,true,boarder,nhomogeneous,nspacing); }
  //: Layout widgets in a vertical box.
  // Helper function calls: LBoxC(widges,true,boarder,nhomogeneous,nspacing)

  inline 
  LBoxC VBox(const WidgetC &widge,int boarder = 0,bool nhomogeneous = false,IntT nspacing = 0)
  { 
    DListC<WidgetC> widges;
    widges.InsLast(widge);
    return LBoxC(widges,true,boarder,nhomogeneous,nspacing); }
  //: Layout widgets in a vertical box.
  // Helper function calls: LBoxC(widges,true,boarder,nhomogeneous,nspacing)
  
  inline 
  LBoxC HBox(const DListC<WidgetC> &widges,int boarder = 0,bool nhomogeneous = false,IntT nspacing = 0)
  { return LBoxC(widges,false,boarder,nhomogeneous,nspacing); }
  //: Layout horzontal in a vertical box.
  // Helper function calls: LBoxC(widges,false,boarder,nhomogeneous,nspacing)

  inline
  LBoxC HBox(const WidgetC &widge,int boarder = 0,bool nhomogeneous = false,IntT nspacing = 0)
  { 
    DListC<WidgetC> widges;
    widges.InsLast(widge);
    return LBoxC(widges,false,boarder,nhomogeneous,nspacing); 
  }
  //: Layout horzontal in a vertical box.
  // Helper function calls: LBoxC(widges,false,boarder,nhomogeneous,nspacing)

  inline 
  LBoxC Box(const WidgetC &widge,int boarder = 0,bool nhomogeneous = false,IntT nspacing = 0)
  { return LBoxC(widge,false,boarder,nhomogeneous,nspacing); }
  //: Put a boarder around a widget.
  // Helper function calls: LBoxC(widge,false,boarder,nhomogeneous,nspacing)
  
  inline 
  LBoxC Box(const DListC<WidgetC> &widges,int boarder = 0,bool nhomogeneous = false,IntT nspacing = 0)
  { return LBoxC(widges,false,boarder,nhomogeneous,nspacing); }
  //: Put a boarder around a list of widgets.
  // Helper function calls: LBoxC(widges,false,boarder,nhomogeneous,nspacing)
}

#endif
