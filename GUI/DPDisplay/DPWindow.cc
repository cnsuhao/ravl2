// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlDPDisplay
//! file="Ravl/GUI/DPDisplay/DPWindow.cc"

#include "Ravl/GUI/DPWindow.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/Threads/Signal1.hh"
#include <stdlib.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  static bool noWaitForGUIExit = false;
  
  void DisableWaitForGUIExit() {
    noWaitForGUIExit = true;
  }
  
}

extern "C" {
  void waitForGUIExit() {
    using namespace RavlGUIN;
    if(noWaitForGUIExit)
      return ;
    if(!Manager.IsManagerStarted())
      return ;
    cerr << "Program exited, waiting for GUI to be shutdown. \n";
    Manager.Wait();
  }

}

namespace RavlGUIN {
  
  MutexC DPWindowBodyC::setupMutex; // Make sure window is only setup at once.
  
  DPWindowBodyC::DPWindowBodyC(const StringC &nname,const IndexRange2dC &nWinSize)
    : name(nname),
      winSize(nWinSize)
  {}
  
  //: Construct widgets.
  
  void DPWindowBodyC::Init(const IndexRange2dC &size) {
    ONDEBUG(cerr << "DPWindowBodyC::Init(), Called. Size=" << winSize << " \n");
    MutexLockC hold(setupMutex);
    if(view.IsValid()) // Check for race in setup.
      return ;
    winSize = size;
    // Ensure the manager is started.
    if(!Manager.IsManagerStarted()) {
      Manager.Execute();      
      Manager.WaitForStartup();
      atexit(waitForGUIExit);
    }
    
    // Create a window and display it.
    win = WindowC(winSize.Cols()+10,winSize.Rows()+10,name);
    DPDisplayViewC nview(winSize);
    win.Add(nview);
    win.Show();
    
    // Don't setup view until we're ready to start processing data.
    view = nview;
  }
  
  //: Add object to the display list.
  
  bool DPWindowBodyC::AddObject(const DPDisplayObjC &obj) { 
    ONDEBUG(cerr << "DPWindowBodyC::AddObject(), Called \n");
    if(!view.IsValid())
      Init(obj.Frame());
    view.AddObject(obj);
    view.Refresh();
    return true;
  }
  
  //: This clears the display list then adds 'obj'.
  
  bool DPWindowBodyC::ReplaceObject(const DPDisplayObjC &obj) {
    ONDEBUG(cerr << "DPWindowBodyC::ReplaceObject(), Called \n");
    if(!view.IsValid()) 
      Init(obj.Frame());
    view.Clear();
    view.AddObject(obj);
    view.Refresh();
    return true;
  }
  
  //: Clear the display list.
  
  bool DPWindowBodyC::Clear() {  
    ONDEBUG(cerr << "DPWindowBodyC::Clear(), Called \n");
    if(!view.IsValid())
      return true;
    return view.Clear();
  }
  
  //: Refresh the display.
  
  bool DPWindowBodyC::Refresh() {
    ONDEBUG(cerr << "DPWindowBodyC::Refresh(), Called \n");
    if(!view.IsValid())
      return true;
    return view.Refresh();
  }

}
