#ifndef RAVLDF_DFPUMP_HEADER
#define RAVLDF_DFPUMP_HEADER 1
///////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"

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
