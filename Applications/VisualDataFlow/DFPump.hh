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

namespace RavlDFN {
  
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
    
  protected:
    DPIOConnectBaseC connect;
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
    
  };
  
  
}

#endif
