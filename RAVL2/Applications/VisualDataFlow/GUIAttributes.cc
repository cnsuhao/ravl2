///////////////////////////////////////////////////
//! rcsid="$Id: GUIAttributes.cc 3340 2003-08-25 21:55:35Z craftit $"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="25/8/2003"

#include "Ravl/DF/GUIAttributes.hh"
#include "Ravl/GUI/AttributeEditor.hh"
#include "Ravl/GUI/Label.hh"
#include "Ravl/GUI/Frame.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {
  
  //: Default constructor.
  
  GUIAttributesBodyC::GUIAttributesBodyC(const DFSystemC &nsys)
    : notebook(GTK_POS_TOP)
  { AttachSystem(const_cast<DFSystemC &>(nsys)); }
  
  //: Attach to a system.
  
  bool GUIAttributesBodyC::AttachSystem(DFSystemC &nsys) {
    if(system == nsys)
      return true; // Already attached.
    
    if(system.IsValid()) {
      // Disconnect the old system. 
      sysConnectSet.DisconnectAll(); 
      // Make independant list of objects to remove.
      DListC<DFObjectC> objects;
      for(HashIterC<DFObjectC,AttributeEditorC> it(obj2editor);it;it++)
	objects.InsLast(it.Key());
      // Remove all pages.
      for(DLIterC<DFObjectC> it(objects);it;it++)
	DelPage(*it);
    }
    
    system = nsys;
    sigObjChange.Invalidate();
    sigObjChange = Signal2C<DFObjectUpdateT,DFObjectC>(DFOU_ADDED);
    
    if(!system.IsValid())
      return false;
    
    sysConnectSet += ConnectRef(sigObjChange,*this,&GUIAttributesBodyC::ObjectUpdate);
    sysConnectSet += Connect(system.SigChange(),sigObjChange);
    
    BuildAll();
    
    return true;
  }
  
  //: Build interface for current system.
  
  bool GUIAttributesBodyC::BuildAll() {
    for(DLIterC<DFObjectC> it(system.Objects());it;it++)
      AddPage(*it);
    return true;
  }
  
  //: Create the widget.
  
  bool GUIAttributesBodyC::Create() {
    Add(FrameC(notebook,"Attributes"));
    LBoxBodyC::Create();
    return true;
  }
  
  //: Handle object updates.
  
  bool GUIAttributesBodyC::ObjectUpdate(DFObjectUpdateT &type,DFObjectC &obj) {
    switch(type) {
    case DFOU_ADDED:   AddPage(obj); break;
    case DFOU_DELETED: DelPage(obj); break;
    case DFOU_CHANGED: UpdatePage(obj); break;
    default:
      cerr << "GUIViewBodyC::ObjectUpdate(), WARNING: Unexpected update type. \n";
    }
    return true;
  }
  
  //: Add a page for an object.
  
  bool GUIAttributesBodyC::AddPage(DFObjectC &obj) {
    ONDEBUG(cerr << "GUIAttributesBodyC::AddPage(), Called for " << obj.Name() << "\n");
    AttributeCtrlC attrCtrl = obj.AttributeCtrl();
    if(!attrCtrl.IsValid())
      return true; // No attribute control for object.
    AttributeEditorC editor(attrCtrl);
    notebook.AppendPage(editor,LabelC(obj.Name()));
    obj2editor[obj] = editor;
    return true;
  }
  
  //: Add a page for an object.
  
  bool GUIAttributesBodyC::DelPage(DFObjectC &obj) {
    ONDEBUG(cerr << "GUIAttributesBodyC::DelPage(), Called for " << obj.Name() << "\n");
    AttributeEditorC editor;
    if(!obj2editor.Lookup(obj,editor))
      return true;
    notebook.RemovePage(editor);
    obj2editor.Del(obj);
    return true;
  }
  
  //: Add a page for an object.
  
  bool GUIAttributesBodyC::UpdatePage(DFObjectC &obj) {
    ONDEBUG(cerr << "GUIAttributesBodyC::UpdatePage(), Called for " << obj.Name() << "\n");
    return true;
  }

}
