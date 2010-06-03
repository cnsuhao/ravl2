// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_DFPORT_HEADER
#define RAVLDF_DFPORT_HEADER 1
//! rcsid="$Id: DFPort.hh 4679 2004-12-02 17:32:08Z craftit $"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/DFPort.hh"

#include "Ravl/DF/DFObject.hh"
#include "Ravl/DP/Port.hh"
#include "Ravl/DP/Plug.hh"

namespace RavlDFN {
  
  class DFPortC;
  
  //! userlevel=Develop
  //: Port base class
  
  class DFPortBodyC
    : public DFObjectBodyC
  {
  public:
    DFPortBodyC(const StringC &nname,DFAttachPlacementT attach = ATTACH_FLOAT);
    //: Constructor.

    DFPortBodyC(istream &strm);
    //: Load from stream.
    
    DFPortBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    DFPortBodyC(XMLIStreamC &is,DFSystemC &context);
    //: Read from istream.
    
    virtual bool Save(XMLOStreamC &strm,bool inCharge = true) const;
    //: Save ostream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode);
    //: Render object to view.
    
    virtual DFMouseActionT MouseClick(GUIViewBodyC &view,const  MouseEventC &me);
    //: Process a mouse click.

    virtual DPPortC Port();
    //: Access the port.
    
    virtual Index2dC AttachPoint() const;
    //: Get attachment point.
    
    virtual bool Connect(DFPortC &port);
    //: Connect this port to another.
    
    virtual bool Disconnect(DFPortC &port);
    //: Disconnect.
    
    virtual const type_info &PortType() const;
    //: Get type of port.
    
    virtual StringC PortName() const;
    //: Get the port name.

    virtual AttributeCtrlC AttributeCtrl();
    //: Access attribute control for object if it exists.
    // Returns an invalid handle if none.
    
  protected:
    void SetAttachPlacement(DFAttachPlacementT attach) {
      attachAt = attach;
    }
    //: Set attach placement.
    
    DFAttachPlacementT AttachPlacement() const
    { return attachAt; }
    //: Access attach placement.
    
    Index2dC Inside(const Index2dC &pos,IntT dist);
    //: Get a point inside of the area of 'pos' by distance 'dist'.
    // dist may be negative.
    
    Index2dC Left(const Index2dC &pos,IntT dist);
    //: Get a point to the left of 'pos' by distance 'dist'.
    // dist may be negative.
    
    DFAttachPlacementT attachAt;
    IntT attachScale;
    Index2dC baseSize; // Size of central text etc.
  };
  
  //! userlevel=Normal
  //: Port base class
  
  class DFPortC
    : public DFObjectC
  {
  public:
    DFPortC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DFPortC(const DFObjectC &obj)
      : DFObjectC(dynamic_cast<const DFObjectBodyC *>(BodyPtr(obj)))
    {}
    //: Base constructor.
    // If object is not a DFPortC an invalid handle is
    // created
    
  protected:
    DFPortC(DFPortBodyC &bod)
      : DFObjectC(bod)
    {}
    //: Body constructor.
    
    DFPortC(const DFPortBodyC *bod)
      : DFObjectC(bod)
    {}
    //: Body constructor.
    
    DFPortBodyC &Body()
    { return static_cast<DFPortBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
    const DFPortBodyC &Body() const
    { return static_cast<const DFPortBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
  public:
    bool Connect(DFPortC &port)
    { return Body().Connect(port); }
    //: Connect this port to another.
    
    bool Disconnect(DFPortC &port)
    { return Body().Disconnect(port); }
    //: Disconnect.
    
    const type_info &PortType() const
    { return Body().PortType(); }
    //: Get type of port.
    
    friend class DFPortBodyC;
  };
  
  ////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Port base class
  
  class DFIPortBodyC
    : public DFPortBodyC
  {
  public:
    explicit DFIPortBodyC(const StringC &nname);
    //: Constructor.
    
    DFIPortBodyC(const DPIPortBaseC &port,const StringC &nname);
    //: Construct from a port and a name
    
    virtual bool Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode);
    //: Render object to view.
    
    virtual DPPortC Port();
    //: Access the port.
    
    virtual DFObjectC LinkTo(const DFObjectC &obj,DFSystemC &system,bool autoConvert);
    //: Attempt to link to another object.

    virtual bool Connect(DFPortC &port);
    //: Connect this port to another.
    
    virtual bool Disconnect(DFPortC &port);
    //: Disconnect.
    
    DPIPortBaseC &IPort()
    { return iport; }
    //: Access iport.

    virtual const type_info &PortType() const;
    //: Get type of port.

    virtual StringC PortName() const;
    //: Get the port name.
    
  protected:
    DPIPortBaseC iport;
  };
  
  //! userlevel=Normal
  //: Port base class
  
  class DFIPortC
    : public DFPortC
  {
  public:
    DFIPortC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DFIPortC(const DPIPortBaseC &port,const StringC &nname)
      : DFPortC(*new DFIPortBodyC(port,nname))
    {}
    //: Constructor.
    
    DFIPortC(const StringC &nname)
      : DFPortC(*new DFIPortBodyC(nname))
    {}
    //: Constructor.
    
    DFIPortC(const DFObjectC &obj)
      : DFPortC(dynamic_cast<const DFIPortBodyC *>(BodyPtr(obj)))
    {}
    //: Base constructor.
    // If object is not a DFIPortC an invalid handle is
    // created
    
  protected:
    DFIPortC(DFIPortBodyC &bod)
      : DFPortC(bod)
    {}
    //: Body constructor.
    
    DFIPortBodyC &Body()
    { return static_cast<DFIPortBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
    const DFIPortBodyC &Body() const
    { return static_cast<const DFIPortBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
  public:
    DPIPortBaseC &IPort()
    { return Body().IPort(); }
    //: Access iport.
    
    friend class DFIPortBodyC;
  };
  
  
  ////////////////////////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Port base class
  
  class DFOPortBodyC
    : public DFPortBodyC
  {
  public:
    explicit DFOPortBodyC(const StringC &nname);
    //: Constructor.
    
    DFOPortBodyC(const DPOPortBaseC &port,const StringC &nname);
    //: Construct from a port and a name
    
    virtual bool Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode);
    //: Render object to view.
    
    virtual DPPortC Port();
    //: Access the port.
    
    virtual DFObjectC LinkTo(const DFObjectC &obj,DFSystemC &system,bool autoConvert);
    //: Attempt to link to another object.

    virtual bool Connect(DFPortC &port);
    //: Connect this port to another.
    
    virtual bool Disconnect(DFPortC &port);
    //: Disconnect.
    
    DPOPortBaseC &OPort()
    { return oport; }
    //: Access oport.

    virtual const type_info &PortType() const;
    //: Get type of port.

    virtual StringC PortName() const;
    //: Get the port name.
  protected:
    DPOPortBaseC oport;
  };
  
  //! userlevel=Normal
  //: Port base class
  
  class DFOPortC
    : public DFPortC
  {
  public:
    DFOPortC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DFOPortC(const DPOPortBaseC &port,const StringC &nname)
      : DFPortC(*new DFOPortBodyC(port,nname))
    {}
    //: Constructor.

    DFOPortC(const StringC &nname)
      : DFPortC(*new DFOPortBodyC(nname))
    {}
    //: Constructor.
    
    DFOPortC(const DFObjectC &obj)
      : DFPortC(dynamic_cast<const DFOPortBodyC *>(BodyPtr(obj)))
    {}
    //: Base constructor.
    // If object is not a DFIPortC an invalid handle is
    // created
    
  protected:
    DFOPortC(DFOPortBodyC &bod)
      : DFPortC(bod)
    {}
    //: Body constructor.
    
    DFOPortBodyC &Body()
    { return static_cast<DFOPortBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
    const DFOPortBodyC &Body() const
    { return static_cast<const DFOPortBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
  public:
    
    DPOPortBaseC &OPort()
    { return Body().OPort(); }
    //: Access oport.
    
    friend class DFOPortBodyC;
  };
  
  /////////////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Plug base class
  
  class DFIPlugBodyC
    : public DFPortBodyC
  {
  public:
    explicit DFIPlugBodyC(const StringC &nname);
    //: Constructor.
    
    DFIPlugBodyC(const DPIPlugBaseC &port,const StringC &nname);
    //: Construct from a port and a name
    
    virtual bool Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode);
    //: Render object to view.
    
    DPIPlugBaseC IPlug()
    { return iplug; }
    //: Access the port.
    
    virtual DFObjectC LinkTo(const DFObjectC &obj,DFSystemC &system,bool autoConvert);
    //: Attempt to link to another object.
    
    virtual bool Connect(DFPortC &port);
    //: Connect this port to another.
    
    virtual bool Disconnect(DFPortC &port);
    //: Disconnect.
    
    virtual const type_info &PortType() const;
    //: Get type of port.

    virtual StringC PortName() const;
    //: Get the port name.
    
  protected:
    DPIPlugBaseC iplug;
  };
  
  //! userlevel=Normal
  //: Plug base class
  
  class DFIPlugC
    : public DFPortC
  {
  public:
    DFIPlugC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DFIPlugC(const DPIPlugBaseC &port,const StringC &nname)
      : DFPortC(*new DFIPlugBodyC(port,nname))
    {}
    //: Constructor.
    
    DFIPlugC(const StringC &nname)
      : DFPortC(*new DFIPlugBodyC(nname))
    {}
    //: Constructor.
    
    DFIPlugC(const DFObjectC &obj)
      : DFPortC(dynamic_cast<const DFIPlugBodyC *>(BodyPtr(obj)))
    {}
    //: Base constructor.
    // If object is not a DFIPlugC an invalid handle is
    // created
    
  protected:
    DFIPlugC(DFIPlugBodyC &bod)
      : DFPortC(bod)
    {}
    //: Body constructor.
    
    DFIPlugBodyC &Body()
    { return static_cast<DFIPlugBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
    const DFIPlugBodyC &Body() const
    { return static_cast<const DFIPlugBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
  public:
    DPIPlugBaseC IPlug()
    { return Body().IPlug(); }
    //: Access the port.
    
    friend class DFIPlugBodyC;
  };


  ////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Plug base class
  
  class DFOPlugBodyC
    : public DFPortBodyC
  {
  public:
    explicit DFOPlugBodyC(const StringC &nname);
    //: Constructor.
    
    DFOPlugBodyC(const DPOPlugBaseC &port,const StringC &nname);
    //: Construct from a port and a name
    
    virtual bool Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode);
    //: Render object to view.
    
    DPOPlugBaseC OPlug()
    { return oplug; }
    //: Access the port.
    
    virtual DFObjectC LinkTo(const DFObjectC &obj,DFSystemC &system,bool autoConvert);
    //: Attempt to link to another object.
    
    virtual bool Connect(DFPortC &port);
    //: Connect this port to another.
    
    virtual bool Disconnect(DFPortC &port);
    //: Disconnect.
    
    virtual const type_info &PortType() const;
    //: Get type of port.

    virtual StringC PortName() const;
    //: Get the port name.
    
  protected:
    DPOPlugBaseC oplug;
  };
  
  //! userlevel=Normal
  //: Plug base class
  
  class DFOPlugC
    : public DFPortC
  {
  public:
    DFOPlugC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DFOPlugC(const DPOPlugBaseC &port,const StringC &nname)
      : DFPortC(*new DFOPlugBodyC(port,nname))
    {}
    //: Constructor.

    DFOPlugC(const StringC &nname)
      : DFPortC(*new DFOPlugBodyC(nname))
    {}
    //: Constructor.

    DFOPlugC(const DFObjectC &obj)
      : DFPortC(dynamic_cast<const DFOPlugBodyC *>(BodyPtr(obj)))
    {}
    //: Base constructor.
    // If object is not a DFOPlugC an invalid handle is
    // created
    
  protected:
    DFOPlugC(DFOPlugBodyC &bod)
      : DFPortC(bod)
    {}
    //: Body constructor.
    
    DFOPlugBodyC &Body()
    { return static_cast<DFOPlugBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
    const DFOPlugBodyC &Body() const
    { return static_cast<const DFOPlugBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
  public:
    DPOPlugBaseC OPlug()
    { return Body().OPlug(); }
    //: Access the port.
    
    friend class DFOPlugBodyC;
  };
  
}

#endif
