// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_NETIPORTSERVER_HEADER
#define RAVL_NETIPORTSERVER_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlNet
//! docentry="Ravl.OS.Network.NetPort"
//! example=exNetPort.cc
//! file="Ravl/OS/Network/NetIPortServer.hh"

#include "Ravl/OS/NetPort.hh"
#include "Ravl/OS/NetEndPoint.hh"
#include "Ravl/DP/SPort.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/DP/SPortAttach.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Base class for NetIPorts.
  
  class NetISPortServerBaseBodyC 
    : public RCBodyVC
  {
  public:
    NetISPortServerBaseBodyC(const DPSeekCtrlC &seekCtrl,const StringC &portName);
    //: Default constructor.
    
    ~NetISPortServerBaseBodyC();
    //: Destructor.
    
    const StringC &Name() const
    { return portName; }
    //: Access port name.
    
    virtual StringC PortType();
    //: Get the port type.
    
    bool Connect(NetEndPointC &ep);
    //: Connect to an end point.
    // Returns false if port is already in use..
    
    bool Disconnect();
    //: Disonnect to an end point.
    
    NetEndPointC &NetEndPoint()
    { return ep; }
    //: Access net end point.

  protected:
    virtual bool Init();
    //: Initalise stream.
    
    bool ReqStats();
    //: Request information on the stream.. 
    
    StringC portName;
    NetEndPointC ep;
    DPSeekCtrlC seekCtrl;
    UIntT at;
  };
  
  //! userlevel=Develop
  //: Input port body
  
  template<class DataT>
  class NetISPortServerBodyC
    : public NetISPortServerBaseBodyC
  {
  public:
    NetISPortServerBodyC(const DPISPortC<DataT> &niport,const StringC &portName)
      : NetISPortServerBaseBodyC(niport,portName),
	iport(niport)
    {}
    //: Constructor.
    
    ~NetISPortServerBodyC() 
    {}
    //: Destructor
    
    virtual StringC PortType()
    { return TypeName(typeid(DataT)); }
    //: Get the port type.
    
    bool ReqData(UIntT &pos);
    //: Request information on the stream.. 
    
  protected:
    bool Init();
    //: Initalise link.
        
    DPISPortC<DataT> iport;
  };
  
  //! userlevel=Advanced
  //: Input port server base.

  class NetISPortServerBaseC
    : public RCHandleC<NetISPortServerBaseBodyC>
  {
  public:
    NetISPortServerBaseC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

  protected:
    NetISPortServerBaseC(NetISPortServerBaseBodyC &bod)
      : RCHandleC<NetISPortServerBaseBodyC>(bod)
    {}
    //: Body constructor.
    
    NetISPortServerBaseBodyC &Body()
    { return RCHandleC<NetISPortServerBaseBodyC>::Body(); }
    //: Access body.
    
    const NetISPortServerBaseBodyC &Body() const
    { return RCHandleC<NetISPortServerBaseBodyC>::Body(); }
    //: Access body.
    
  public:
    const StringC &Name() const
    { return Body().Name(); }
    //: Access port name.
    
    bool Connect(NetEndPointC &ep)
    { return Body().Connect(ep); }
    //: Connect to an end point.
    // Returns false if port is already in use..
    
    bool Disconnect()
    { return Body().Disconnect(); }
    //: Disonnect to an end point.
    
    StringC PortType()
    { return Body().PortType(); }
    //: Get the port type.
    
    NetEndPointC &NetEndPoint()
    { return Body().NetEndPoint(); }
    //: Access net end point.

  };
  
  //! userlevel=Advanced
  //: Input port.
  // This class manages the information needed to serve a particular port.
  
  template<class DataT>
  class NetISPortServerC
    : public NetISPortServerBaseC
  {
  public:
    NetISPortServerC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    NetISPortServerC(const DPISPortC<DataT> &iport,const StringC &portName)
      : NetISPortServerBaseC(*new NetISPortServerBodyC<DataT>(iport,portName))
    {}
    //: Constructor.
    
  protected:
    NetISPortServerC(NetISPortServerBodyC<DataT> &bod)
      : NetISPortServerBaseC(bod)
    {}
    //: Body constructor.

    NetISPortServerBodyC<DataT> &Body()
    { return static_cast<NetISPortServerBodyC<DataT> &>(NetISPortServerBaseC::Body()); }
    //: Access body.
    
    const NetISPortServerBodyC<DataT> &Body() const
    { return static_cast<const NetISPortServerBodyC<DataT> &>(NetISPortServerBaseC::Body()); }
    //: Access body.
    
    bool ReqData(UIntT &pos)
    { return Body().ReqData(pos); }
    //: Request information on the stream.. 
    
    friend class NetISPortServerBodyC<DataT>;
  };

  ///////////////////////////////////////////////////

  bool NetExportBase(const StringC &name,NetISPortServerBaseC &isp);
  //! userlevel=Develop
  //: Export  port.
  
  template<class DataT>
  bool NetExport(const StringC &portName,DPISPortC<DataT> &port) {
    NetISPortServerC<DataT> ips(port,portName);
    return NetExportBase(portName,ips);
  }
  //! userlevel=Normal 
  //: Export an SPort with a given portName.
  
  template<class DataT>
  bool NetExport(const StringC &portName,DPIPortC<DataT> &port) {
    NetISPortServerC<DataT> ips(SPort(port),portName);
    return NetExportBase(portName,ips);
  }
  //! userlevel=Normal 
  //: Export an SPort with a given portName.
  
  ///////////////////////////////////////////////////
  
  template<class DataT>  
  bool NetISPortServerBodyC<DataT>::Init() {
    NetISPortServerC<DataT> me(*this);
    ep.Register(NPMsg_ReqData,"ReqData",me,&NetISPortServerC<DataT>::ReqData);
    return NetISPortServerBaseBodyC::Init();
  }
  
  template<class DataT>
  bool NetISPortServerBodyC<DataT>::ReqData(UIntT &pos) {
    if(!iport.IsValid()) {
      ep.Send(NPMsg_ReqFailed,1); // Report end of stream.
      return true;
    }
    //cerr << "NetISPortServerBodyC<DataT>::ReqData(), Pos=" << pos << " at=" << at << " Tell=" << iport.Tell() <<"\n";
    if(at != pos && pos != (UIntT)(-1)) {
      iport.Seek(pos);
      at = pos;
    }
    DataT dat;
    if(iport.Get(dat)) {
      at++;
      ep.Send(NPMsg_Data,at,dat);
    } else { // Failed to get data.
      if(iport.IsGetEOS())
	ep.Send(NPMsg_ReqFailed,1); // End of stream.
      else
	ep.Send(NPMsg_ReqFailed,2); // Just get failed.
    }
    return true;
  }
  

}


#endif
