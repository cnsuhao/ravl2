// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_DFPUMP_HEADER
#define RAVLDF_DFPUMP_HEADER 1
///////////////////////////////////////////////////////////////////
//! rcsid="$Id: DFPump.hh 1533 2002-08-08 16:03:23Z craftit $"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/DFPump.hh"

#include "Ravl/DF/DFStreamOp.hh"
#include "Ravl/DP/MTIOConnect.hh"
#include "Ravl/GUI/Menu.hh"

namespace RavlDFN {
  using namespace RavlGUIN;
  
  //! userlevel=Develop
  //: Data object.
  
  class DFPumpBodyC
    : public DFStreamOpBodyC 
  {
  public:
    DFPumpBodyC(const StringC &nname,const DPIOConnectBaseC &ndata);
    //: Construct from name and data.
    
    virtual bool Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode);
    //: Render object to view.
    
    DPIOConnectBaseC &Connection()
    { return connect; }
    //: Connection.

    virtual DFMouseActionT MouseClick(GUIViewBodyC &view,const  MouseEventC &me);
    //: Process a mouse click.
    
    bool Run();
    //: Run pump.
    
    bool Stop();
    //: Stop pump.
    
    bool Step();
    //: Pump one item.
    
  protected:
    DPIOConnectBaseC connect;
    MenuC popUp;
  };
  
  //! userlevel=Normal
  //: Data object.
  
  class DFPumpC 
    : public DFStreamOpC
  {
  public:
    DFPumpC()
    {}
    //: Default constructor.
    
    DFPumpC(const StringC &name,const DPIOConnectBaseC &data)
      : DFStreamOpC(*new DFPumpBodyC(name,data))
    {}
    //: Constructor.
    
  protected:
    DFPumpC(DFPumpBodyC &bod)
      : DFStreamOpC(bod)
    {}
    //: Body constructor.
    
    DFPumpBodyC &Body()
    { return static_cast<DFPumpBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
    const DFPumpBodyC &Body() const
    { return static_cast<const DFPumpBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
  public:
    DPIOConnectBaseC &Connection()
    { return Body().Connection(); }
    //: Connection.
    
    bool Run()
    { return Body().Run(); }
    //: Run pump.
    
    bool Stop()
    { return Body().Stop(); }
    //: Stop pump.
    
    bool Step()
    { return Body().Step(); }
    //: Stop pump.
    
  };
  
  
}

#endif
