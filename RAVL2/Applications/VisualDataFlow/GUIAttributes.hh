#ifndef RAVLDF_GUIATTRIBUTES_HEADER
#define RAVLDF_GUIATTRIBUTES_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id: GUIAttributes.hh 3340 2003-08-25 21:55:35Z craftit $"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="25/8/2003"

#include "Ravl/DF/DFSystem.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/Notebook.hh"
#include "Ravl/Hash.hh"
#include "Ravl/GUI/AttributeEditor.hh"
#include "Ravl/Threads/SignalConnectionSet.hh"

namespace RavlDFN {
  using namespace RavlGUIN;
  
  //! userlevel=Develop
  //: Attributes.
  
  class GUIAttributesBodyC
    : public LBoxBodyC
  {
  public:
    GUIAttributesBodyC(const DFSystemC &nsys);
    //: Default constructor.
    
    virtual bool Create();
    //: Create the widget.
    
    bool AttachSystem(DFSystemC &sys);
    //: Attach to a system.
    
    bool ObjectUpdate(DFObjectUpdateT &type,DFObjectC &obj);
    //: Handle object updates.
    
    bool AddPage(DFObjectC &obj);
    //: Add a page for an object.
    
    bool DelPage(DFObjectC &obj);
    //: Add a page for an object.
    
    bool UpdatePage(DFObjectC &obj);
    //: Add a page for an object.
    
    bool BuildAll();
    //: Build interface for current system.
  protected:
    HashC<DFObjectC,AttributeEditorC> obj2editor;
    Signal2C<DFObjectUpdateT,DFObjectC> sigObjChange;
    DFSystemC system;
    NotebookC notebook;
    SignalConnectionSetC sysConnectSet;
  };

  //! userlevel=Normal
  //: Attributes.
  
  class GUIAttributesC
    : public LBoxC
  {
  public:
    GUIAttributesC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    GUIAttributesC(const DFSystemC &nsys)
      : LBoxC(*new GUIAttributesBodyC(nsys))
    {}
    //: Constructor.
    
  protected:    
    GUIAttributesC(GUIAttributesBodyC &bod)
      :  LBoxC(bod)
    {}
    //: Body constructor.
    
    GUIAttributesBodyC &Body()
    { return static_cast<GUIAttributesBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const GUIAttributesBodyC &Body() const
    { return static_cast<const GUIAttributesBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
    bool ObjectUpdate(DFObjectUpdateT &type,DFObjectC &obj)
    { return Body().ObjectUpdate(type,obj); }
    //: Handle object updates.
    
  };
  
  
}

#endif
