// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_DFEDITOR_HEADER
#define RAVLDF_DFEDITOR_HEADER 1
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/GUIEditor.hh"

#include "Ravl/DF/DFSystem.hh"
#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/CList.hh"
#include "Ravl/DF/GUIView.hh"
#include "Ravl/DF/GUIFactory.hh"
#include "Ravl/Threads/SignalConnectionSet.hh"
#include "Ravl/GUI/FileSelector.hh"

namespace RavlDFN {
  using namespace RavlGUIN;
  
  //! userlevel=Develop
  //: Data flow editor.
  
  class DFEditorBodyC 
    : public WindowBodyC
  {
  public:
    DFEditorBodyC(const StringC &nname);
    //: Constructor.
    
    ~DFEditorBodyC();
    //: Destructor.
    
  protected:
    void Init();
    //: Initalise window.
    // Creates widges etc.
    
    bool DeleteSelection();
    //: Delete selected objects.
    
    bool OpenInput(StringC &filename);
    //: Open an input.
    
    bool OpenOutput(StringC &filename);
    //: Open an output.
    
    bool OpenGeneric(StringC &filename);
    //: Open a generic object.
    
    bool Quit();
    //: Quit from the editor.
    
    virtual void Destroy();
    //: Undo all references.
    
    DFSystemC system;
    
    GUIViewC viewGUI;        // View widget.
    GUIFactoryC factoryGUI; // Factory widget.
    
    bool ObjectUpdate(DFObjectUpdateT &type,DFObjectC &obj);
    //: Handle object updates.
    
    Signal2C<DFObjectUpdateT,DFObjectC> sigObjChange;
    
    SignalConnectionSetC connectSet;
    
    FileSelectorC fileSelInput;
    FileSelectorC fileSelOutput;
  };
  
  //! userlevel=Normal
  //: Data flow editor.
  
  class DFEditorC 
    : public WindowC
  {
  public:
    DFEditorC()
    {}
    //: Constructor.
    
    DFEditorC(const StringC &nname)
      : WindowC(*new DFEditorBodyC(nname))
    {}
    //: Constructor.
    
  protected:
    DFEditorBodyC &Body()
    { return static_cast<DFEditorBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const DFEditorBodyC &Body() const
    { return static_cast<const DFEditorBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
  };
}


#endif
