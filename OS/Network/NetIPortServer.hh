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
    
    const StringC &Name() const
    { return portName; }
    //: Access port name.
    
    virtual StringC PortType();
    //: Get the port type.
    
    bool Connect(NetEndPointC &ep);
    //: Connect to an end point.
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
    
    virtual StringC PortType()
    { return TypeName(typeid(DataT)); }
    //: Get the port type.
    
  protected:
    bool Init();
    //: Initalise link.
    
    bool ReqData(UIntT &pos);
    //: Request information on the stream.. 
    
    DPISPortC<DataT> iport;
  };
  
  //! userlevel=Normal
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
    
    StringC PortType()
    { return Body().PortType(); }
    //: Get the port type.
  };
  
  //! userlevel=Normal
  //: Input port.
  
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
  };

  ///////////////////////////////////////////////////

  bool NetExportBase(const StringC &name,NetISPortServerBaseC &isp);
  //! userlevel=Develop
  //: Export ISPort.
		     
  template<class DataT>
  bool NetExport(const StringC &name,DPISPortC<DataT> &port) {
    NetISPortServerC<DataT> ips(port,name);
    return NetExportBase(name,ips);
  }
  //! userlevel=Normal 
  //: Export ISPort.

  template<class DataT>
  bool NetExport(const StringC &name,DPIPortC<DataT> &port) {
    DPISPortAttachC<DataT> sport(port);
    NetISPortServerC<DataT> ips(sport,name);
    return NetExportBase(name,ips);
  }
  //! userlevel=Normal 
  //: Export ISPort.
  
  ///////////////////////////////////////////////////
  
  template<class DataT>  
  bool NetISPortServerBodyC<DataT>::Init() {
    ep.RegisterR(4,"ReqData",*this,&NetISPortServerBodyC<DataT>::ReqData);
    return NetISPortServerBaseBodyC::Init();
  }
  
  template<class DataT>
  bool NetISPortServerBodyC<DataT>::ReqData(UIntT &pos) {
    if(at != pos && pos != (UIntT)(-1)) {
      iport.Seek(pos);
    }
    DataT dat;
    if(iport.Get(dat)) {
      ep.Send(5,iport.Tell(),dat);
    } else { // Failed to get data.
      if(iport.IsGetEOS())
	ep.Send(6,1); // End of stream.
      else
	ep.Send(6,2); // Just get failed.
    }
    return true;
  }
  

}


#endif
