// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! file="Ravl/Applications/VisualDataFlow/DFPump.cc"

#include "Ravl/DF/DFPump.hh"
#include "Ravl/DF/GUIView.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {
  using namespace RavlGUIN;
  
  DFPumpBodyC::DFPumpBodyC(const StringC &nname,const DPIOConnectBaseC &ndata)
    : DFStreamOpBodyC(nname,ndata),
      connect(ndata)
  {}
  
  //: Render object to view.
  
  bool DFPumpBodyC::Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode) {
    return DFStreamOpBodyC::Render(view,at,mode);
  }
  
  //: Process a mouse click.
  
  DFMouseActionT DFPumpBodyC::MouseClick(GUIViewBodyC &view,const  MouseEventC &me) {
    ONDEBUG(cerr << "DFPumpBodyC::MouseClick(), Called. \n");
    if(me.HasChanged(0)) 
      return DFMA_SELECTDRAG;
    if(!popUp.IsValid()) {
      popUp = MenuC("Pump Options",
		    MenuItemR("Step",*this,&DFPumpBodyC::Step) +
		    MenuItemR("Run",*this,&DFPumpBodyC::Run) +
		    MenuItemR("Stop",*this,&DFPumpBodyC::Stop)
		  );
      popUp.Show();
    }
    popUp.Popup();
    return DFMA_NONE;
  }
    
  //: Run pump.
  
  bool DFPumpBodyC::Run() {
    ONDEBUG(cerr << "DFPumpBodyC::Run(), Called. \n");
    if(!connect.IsValid()) {
      cerr << "DFPumpBodyC::Run(), ERROR: No connection. \n";
      return false;
    }
    return connect.Run();
  }
  
  //: Stop pump.
  
  bool DFPumpBodyC::Stop() {
    ONDEBUG(cerr << "DFPumpBodyC::Stop(), Called. \n");
    if(!connect.IsValid()) {
      cerr << "DFPumpBodyC::Stop(), ERROR: No connection. \n";
      return false;
    }
    connect.Stop();
    return true;
  }
  
  //: Pump one item.
  bool DFPumpBodyC::Step() {
    ONDEBUG(cerr << "DFPumpBodyC::Step(), Called. \n");
    if(!connect.IsValid()) {
      cerr << "DFPumpBodyC::Step(), ERROR: No connection. \n";
      return false;
    }
    return connect.Step();
  }
  

}
