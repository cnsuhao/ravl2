// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLNETSERVER_HEADER
#define RAVLNETSERVER_HEADER 1
//////////////////////////////////////////////////////////////////
//! docentry="Basic Types.Network"
//! rcsid="$Id$"
//! example=exEndPoint.cc
//! file="Ravl/OS/Network/NetEndPoint.hh"
//! lib=RavlNet
//! userlevel=Normal
//! docentry="Ravl.OS.Network"
//! author="Charles Galambos"
//! date="13/12/2000"

#include "Ravl/OS/Packet.hh"
#include "Ravl/OS/Socket.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/Calls.hh"
#include "Ravl/Threads/MessageQueue.hh"
#include "Ravl/Threads/ThreadEvent.hh"
#include "Ravl/OS/NetMessage.hh"
#include "Ravl/OS/NetMsgCall.hh"
#include "Ravl/CallMethodRefs.hh"
#include "Ravl/CallMethods.hh"
#include "Ravl/Threads/Thread.hh"

namespace RavlN {

  class NetEndPointC;
  
  //! userlevel=Develop
  //: An end point for a network packet base protocol.
  
  class NetEndPointBodyC 
    : public RCBodyVC
  {
  public:
    NetEndPointBodyC(SocketC &skt,bool nautoInit = true);
    //: Constructor.
    // If auto init is set to false, you must call the Ready() function
    // when your ready to start processing network messages. If autoinit
    // is true messages will start being processed as soon as the connection
    // is established.
    
    NetEndPointBodyC(const StringC &skt,bool nautoInit = true);
    //: Constructor.
    // If auto init is set to false, you must call the Ready() function
    // when your ready to start processing network messages. If autoinit
    // is true messages will start being processed as soon as the connection
    // is established.
    
    NetEndPointBodyC();
    //: Default constructor.
    
    ~NetEndPointBodyC();
    //: Destructor.
    
    bool IsOpen() const { 
      if(!skt.IsValid())
	return false;
      return skt.IsOpen(); 
    }
    //: Is Connections open ?
    
    bool Init(SocketC &skt);
    //: Setup a connection.
    // This should only be used if net end point 
    // has been created by the default constructor.
    
    bool WaitSetupComplete();
    //: Wait for setup to complete.
    
    bool Close();
    //: Close connection.

    inline SocketC Socket(void) 
    { return skt ; }
    //: Access the socket 

    inline StringC ConnectedHost(void) 
    { return skt.ConnectedHost() ; }
    //: Access the name of the connected Host 

    inline IntT ConnectedPort(void) 
    { return skt.ConnectedPort() ; } 
    //: Access the name of the connected Port 
    
    const StringC &RemoteUser() const
    { return remoteUser; }
    //: Access name of remote user.
    
    void Transmit(const NetPacketC &pkt)
      { transmitQ.Put(pkt); }
    //: Queue a packet for transmition.
    
    bool MsgInit(StringC &user);
    //: Init message.

    bool Ready();
    //: Initalise link.

    void SndInit(StringC &user);
    //: Send init message.
    
    bool Send(UIntT id);
    //: Send a 0 paramiter message.
    
    template<class Data1T>
    bool Send(UIntT id,const Data1T &dat1) {
      BufOStreamC os;
      BinOStreamC bos(os);
      bos << id << dat1;
      Transmit(NetPacketC(os.Data()));
      return true;
    }
    //: Send a 1 paramiter message.
    
    template<class Data1T,class Data2T>
    bool Send(UIntT id,const Data1T &dat1,const Data2T &dat2) {
      BufOStreamC os;
      BinOStreamC bos(os);
      bos << id << dat1 << dat2;
      Transmit(NetPacketC(os.Data()));
      return true;
    }
    //: Send a 2 paramiter message.

    template<class Data1T,class Data2T,class Data3T>
    bool Send(UIntT id,const Data1T &dat1,const Data2T &dat2,const Data3T &dat3) {
      BufOStreamC os;
      BinOStreamC bos(os);
      bos << id << dat1 << dat2  << dat3;
      Transmit(NetPacketC(os.Data()));
      return true;
    }
    //: Send a 3 paramiter message.
    
    bool Register(const NetMsgRegisterC &nmsg);
    //: Register new message handler.
    
    NetMsgRegisterC Find(UIntT id) const;
    //: Search for message decode/encode of type 'id'.

    template<class ObjT>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)()) {
      return Register(NetMsgCall0C(mid,msgName,CallMethod0C<ObjT &,bool>(obj,func))); 
    }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.
    
    template<class ObjT,class DataT>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(DataT)) {
      return Register(NetMsgCall1C<DataT>(mid,msgName,CallMethod1C<ObjT &,DataT,bool>(obj,func))); 
    }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.

    template<class ObjT,class Data1T,class Data2T>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(Data1T,Data2T)) {
      return Register(NetMsgCall2C<Data1T,Data2T>(mid,msgName,CallMethod2C<ObjT &,Data1T,Data2T,bool>(obj,func))); 
    }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.
    
    template<class ObjT,class Data1T,class Data2T,class Data3T>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(Data1T,Data2T,Data3T)) {
      return Register(NetMsgCall3C<Data1T,Data2T,Data3T>(mid,msgName,CallMethod3C<ObjT &,Data1T,Data2T,Data3T,bool>(obj,func))); 
    }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.

    template<class ObjT>
    bool Register(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)()) {
      return Register(NetMsgCall0C(mid,msgName,CallMethod0C<ObjT,bool>(obj,func))); 
    }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.
    
    template<class ObjT,class DataT>
    bool Register(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(DataT)) {
      return Register(NetMsgCall1C<DataT>(mid,msgName,CallMethod1C<ObjT,DataT,bool>(obj,func))); 
    }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.

    template<class ObjT,class Data1T,class Data2T>
    bool Register(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(Data1T,Data2T)) {
      return Register(NetMsgCall2C<Data1T,Data2T>(mid,msgName,CallMethod2C<ObjT,Data1T,Data2T,bool>(obj,func))); 
    }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.

    template<class ObjT,class Data1T,class Data2T,class Data3T>
    bool Register(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(Data1T,Data2T,Data3T)) {
      return Register(NetMsgCall3C<Data1T,Data2T,Data3T>(mid,msgName,CallMethod3C<ObjT,Data1T,Data2T,Data3T,bool>(obj,func))); 
    }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.
    
  protected:
    
    bool RunTransmit();
    //: Handle packet transmition.
    
    bool RunReceive();
    //: Handle packet reception.
    
    bool RunDecode();
    //: Decodes incoming packets.
    
    bool ReadData(int nfd,char *buff,UIntT size);
    //: Read some bytes from a stream.
    
    SocketC skt;
    MessageQueueC<NetPacketC> transmitQ; // Transmition Q.
    MessageQueueC<NetPacketC> receiveQ; // Recieve Q.
    volatile bool shutdown;   // Shutdown system ?
    ThreadEventC setupComplete;
    StringC remoteUser;
    HashC<UIntT,NetMsgRegisterC> msgReg;  // Local register of decoding routines.
    friend class NetEndPointC;
    bool autoInit;
  };
  
  //! userlevel=Normal
  //:  An end point for a network packet base protocol.
  
  class NetEndPointC 
    : public RCHandleC<NetEndPointBodyC>
  {
  public:
    NetEndPointC()
      {}
    //: Default constructor.
    // Creates an invalid handle.

    NetEndPointC(SocketC &skt,bool autoInit = true)
      : RCHandleC<NetEndPointBodyC>(*new NetEndPointBodyC(skt,autoInit))
    {}
    //: Constructor.
    // If auto init is set to false, you must call the Ready() function
    // when your ready to start processing network messages. If autoinit
    // is true messages will start being processed as soon as the connection
    // is established.
    
    NetEndPointC(const StringC &addr,bool autoInit = true)
      : RCHandleC<NetEndPointBodyC>(*new NetEndPointBodyC(addr,autoInit))
    {}
    //: Constructor.
    // This connects to the given address. <p>
    // If auto init is set to false, you must call the Ready() function
    // when your ready to start processing network messages. If autoinit
    // is true messages will start being processed as soon as the connection
    // is established.
    
    explicit NetEndPointC(bool)
      : RCHandleC<NetEndPointBodyC>(*new NetEndPointBodyC())
    {}
    //: Create an uninitalised end point.
    
  protected:
    NetEndPointC(NetEndPointBodyC &bod)
      : RCHandleC<NetEndPointBodyC>(bod)
      {}
    //: Body constructor.
    
    NetEndPointBodyC &Body() 
      { return RCHandleC<NetEndPointBodyC>::Body(); }
    //: Access body.

    const NetEndPointBodyC &Body() const
      { return RCHandleC<NetEndPointBodyC>::Body(); }
    //: Access body.

    bool RunTransmit()
      { return Body().RunTransmit(); }
    //: Handle packet transmition.
    
    bool RunReceive()
      { return Body().RunReceive(); }
    //: Handle packet reception.
    
    bool RunDecode()
      { return Body().RunDecode(); }
    //: Decodes incoming packets.
    
  public:    
    bool IsOpen() const
    { return Body().IsOpen(); }
    //: Is Connections open ?
    
    inline SocketC Socket (void) 
    { return Body().Socket() ; } 
    //: Access the socket 

    inline StringC ConnectedHost (void) 
    { return Body().ConnectedHost() ; } 
    //: Access the connected host 

    inline IntT ConnectedPort (void) 
    { return Body().ConnectedPort() ; } 
    //: Access the connected port

    const StringC &RemoteUser() const
    { return Body().RemoteUser(); }
    //: Access name of remote user.
    
    bool Init(SocketC &skt)
    { return Body().Init(skt); }
    //: Setup a connection.
    // This should only be used if net end point 
    // has been created by the default constructor.
    
    bool Ready()
    { return Body().Ready(); }
    //: Call when your ready to recieved data from the network..
    
    bool WaitSetupComplete()
    { return Body().WaitSetupComplete(); }
    //: Wait for setup to complete.
    
    bool Close()
    { return Body().Close(); }
    //: Close connection.
    
    void Transmit(const NetPacketC &pkt)
      { Body().Transmit(pkt); }
    //: Queue a packet for transmition.
    
    bool MsgInit(StringC &user)
      { return  Body().MsgInit(user); }
    //: Init message.

    bool Register(const NetMsgRegisterC &nmsg)
      { return Body().Register(nmsg); }
    //: Register new message handler.
    
    bool Send(UIntT id)
    { return Body().Send(id); }
    //: Send a 0 paramiter message.
    
    template<class Data1T>
    bool Send(UIntT id,const Data1T &dat1)
      { return Body().Send(id,dat1); }
    //: Send a 1 paramiter message.
    
    template<class Data1T,class Data2T>
    bool Send(UIntT id,const Data1T &dat1,const Data2T &dat2)
      { return Body().Send(id,dat1,dat2); }
    //: Send a 2 paramiter message.

    template<class Data1T,class Data2T,class Data3T>
    bool Send(UIntT id,const Data1T &dat1,const Data2T &dat2,const Data3T &dat3)
      { return Body().Send(id,dat1,dat2,dat3); }
    //: Send a 3 paramiter message.
    
    template<class ObjT>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)())
      { return Body().RegisterR(mid,msgName,obj,func); }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.
    
    template<class ObjT,class DataT>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(DataT ))
      { return Body().RegisterR(mid,msgName,obj,func); }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.

    template<class ObjT,class Data1T,class Data2T>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(Data1T ,Data2T ))
      { return Body().RegisterR(mid,msgName,obj,func); }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.

    template<class ObjT,class Data1T,class Data2T,class Data3T>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(Data1T ,Data2T ,Data3T ))
      { return Body().RegisterR(mid,msgName,obj,func); }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.
    
    template<class ObjT>
    bool Register(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)())
      { return Body().Register(mid,msgName,obj,func); }
    //: Register new message handler.
    // Hold a handle to the object called.
    
    template<class ObjT,class DataT>
    bool Register(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(DataT ))
      { return Body().Register(mid,msgName,obj,func); }
    //: Register new message handler.
    // Hold a handle to the object called.
    
    template<class ObjT,class Data1T,class Data2T>
    bool Register(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(Data1T,Data2T))
      { return Body().Register(mid,msgName,obj,func); }
    //: Register new message handler.
    // Hold a handle to the object called.

    template<class ObjT,class Data1T,class Data2T,class Data3T>
    bool Register(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(Data1T,Data2T,Data3T))
      { return Body().Register(mid,msgName,obj,func); }
    //: Register new message handler.
    // Hold a handle to the object called.
    
    friend class NetEndPointBodyC;
  };
  
  
}

#endif
