// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"

#include "Ravl/DF/GUIEditor.hh"
#include "Ravl/GUI/Menu.hh"
#include "Ravl/GUI/MenuCheck.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/PackInfo.hh"
#include "Ravl/GUI/ScrolledArea.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/GUI/Paned.hh"
#include "Ravl/DF/DFPort.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/IO.hh"

#include <gtk/gtk.h>

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {
  using namespace RavlGUIN;
  
  //: Constructor.
  
  DFEditorBodyC::DFEditorBodyC(const StringC &nname)
    : WindowBodyC(200,200,nname),
      system(nname),
      sigObjChange(DFOU_ADDED)
  { 
    ONDEBUG(cerr << "DFEditorBodyC::DFEditorBodyC(const StringC &), Called. \n");
    Init(); 
  }

  //: Destructor.
  
  DFEditorBodyC::~DFEditorBodyC() {
    //ONDEBUG(cerr << "DFEditorBodyC::~DFEditorBodyC(), Called. \n");
  }
  
  //: Init window.
  
  void DFEditorBodyC::Init() {
    FactorySetC factories("factory.cfg");
    factoryGUI = GUIFactoryC(factories);
    
    viewGUI = GUIViewC(system,factories);
    
    StringC fn(""); // Convert to a real filename.
    fileSelInput = FileSelectorC("Create input",fn);
    connectSet += Connect(fileSelInput.Selected(),*this,&DFEditorBodyC::OpenInput,fn);
    fileSelOutput = FileSelectorC("Create output",fn); 
    connectSet += Connect(fileSelOutput.Selected(),*this,&DFEditorBodyC::OpenOutput,fn);
    
    MenuBarC menu(MenuC("File",
			MenuItemR("quit",*this,&DFEditorBodyC::Quit)
			) +
		  MenuC("Insert",
			MenuItemShow("Output port",fileSelInput) +
			MenuItemShow("Input port" ,fileSelOutput)
			) +
		  MenuC("Options",
			MenuCheckItemR("Auto Convert",viewGUI.AutoConvert(),viewGUI,&GUIViewC::SetAutoConvert)
			)
		  );
    
    
    Add(VBox(PackInfoC(menu,false,true) + 
	     PanedC(ScrolledAreaC(factoryGUI,100,0),ScrolledAreaC(viewGUI))));
    
    connectSet += ConnectRef(sigObjChange,*this,&DFEditorBodyC::ObjectUpdate);
    connectSet += Connect(system.SigChange(),sigObjChange);
    
    
    //FactoryInit();
  }
  
  
  //: Handle object updates.
  
  bool DFEditorBodyC::ObjectUpdate(DFObjectUpdateT &type,DFObjectC &obj) {
    ONDEBUG(cerr << "DFEditorBodyC::ObjectUpdate(). \n");
    switch(type)
      {
      case DFOU_ADDED:
	break;
      case DFOU_DELETED:
	break;
      case DFOU_CHANGED:
	break;
      default:
	cerr << "DFEditorBodyC::ObjectUpdate(), WARNING: Unexpected update type. \n";
      }
    return true;
  }
  
  //: Create a new input port.
  
  bool DFEditorBodyC::OpenInput(StringC &filename) {
    ONDEBUG(cerr << "DFEditorBodyC::OpenInput() '" << filename << "'\n");
    DPIPortBaseC ip;
    DPSeekCtrlC sc;
    if(!OpenISequenceBase(ip,sc,filename,"",typeid(void))) {
      cerr << "DFObjectFromFile(), Failed to open '" << filename << "' \n";
      return false;
    }
    ip.SetAttr("id",filename);
    DFIPortC dfi(ip,filename);
    system.AddObject(dfi);
    return true;
  }
  
  //: Create a new input port.
  
  bool DFEditorBodyC::OpenOutput(StringC &filename) {
    ONDEBUG(cerr << "DFEditorBodyC::OpenOutput() '" << filename << "'\n");
    DPOPortBaseC ip;
    DPSeekCtrlC sc;
    if(!OpenOSequenceBase(ip,sc,filename,"",typeid(void))) {
      cerr << "DFObjectFromFile(), Failed to open '" << filename << "'\n";
      return false;
    }
    ip.SetAttr("id",filename);
    DFOPortC dfo(ip,filename);
    system.AddObject(dfo);
    return true;
  }

  //: Open a generic object.
  
  bool DFEditorBodyC::OpenGeneric(StringC &filename) {
    ONDEBUG(cerr << "DFEditorBodyC::OpenGeneric() '" << filename << "'\n");
    
    return true;
  }
  
  //: Quit from the editor.
  
  bool DFEditorBodyC::Quit() {
    //ONDEBUG(cerr << "DFEditorBodyC::Quit() \n");
    Close();
    return true;
  }
  
  //: Undo all references.
  
  void DFEditorBodyC::Destroy() {
    ONDEBUG(cerr << "DFEditorBodyC::Destroy(), Called. \n");
    
    // Clean up connections.
    connectSet.DisconnectAll();
    sigObjChange.DisconnectAll();
    
    // Invalidate handles.
    system.Invalidate();
    viewGUI.Invalidate();
    factoryGUI.Invalidate();
    
    // Do normal window cleanup.
    WindowBodyC::Destroy();
  }  
  
}
