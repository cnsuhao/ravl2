// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_NETENDPOINT_HEADER
#define RAVL_NETENDPOINT_HEADER 1
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
#include "Ravl/DP/ByteStream.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/Calls.hh"
#include "Ravl/Threads/MessageQueue.hh"
#include "Ravl/Threads/ThreadEvent.hh"
#include "Ravl/Threads/Mutex.hh"
#include "Ravl/OS/NetMessage.hh"
#include "Ravl/OS/NetMsgCall.hh"
#include "Ravl/CallMethodRefs.hh"
#include "Ravl/CallMethods.hh"
#include "Ravl/Threads/Thread.hh"

namespace RavlN {
  class SocketC;
  class NetEndPointC;
  
  struct NetClientInfoC {
    NetClientInfoC();
    //: Default Constructor.
    
    NetClientInfoC(const StringC &protocolName,
		   const StringC &protocolVersion = StringC("0.0"),
		   const StringC &appName = StringC("default"),
		   const StringC &appName = StringC("0.0"),
		   const StringC &hostType = StringC("unknown")
		   );
    //: Constructor.

    void ProtocolName(StringC &str)
    { protocol = str; }
    //: Set Name of protocol being used.
    
    void ProtocolVersion(StringC & str)
    { protocol = str; }
    //: Set Version of protocol being used.
    
    void AppName(StringC &str)
    { appName = str; }
    //: Set Name of application
    
    void AppVersion(StringC &str)
    { appVersion = str; }
    //: Set Version of application
    
    void HostType(StringC &str)
    { hostType = str; }
    //: Set type of host.
    
    const StringC &ProtocolName() const
    { return protocol; }
    //: Name of protocol being used.
    
    const StringC &ProtocolVersion() const
    { return protocol; }
    //: Version of protocol being used.
    
    const StringC &AppName() const
    { return appName; }
    //: Name of application
    
    const StringC &AppVersion() const
    { return appVersion; }
    //: Version of application
    
    const StringC &HostType() const
    { return hostType; }
    //: Access type of host.

    StringC protocol;    // Name of protocol being used.
    StringC protocolVersion; // Version of protocol.
    StringC appName;     // Name of application.
    StringC appVersion;  // Version of application.
    StringC hostType;
  };
  
  BinOStreamC &operator<<(BinOStreamC &strm,const NetClientInfoC &info);
  //: Write info to a stream.
  
  BinIStreamC &operator>>(BinIStreamC &strm,NetClientInfoC &info);
  //: Read info from a stream.
  
  //! userlevel=Develop
  //: An end point for a network packet base protocol.
  
  class NetEndPointBodyC 
    : public RCBodyVC
  {
  public:
    NetEndPointBodyC(SocketC &socket,bool autoInit = true);
    //: Constructor.
    //!param: socket - connext to existing socket
    //!param: autoInit - If false, you must call the Ready() function when you are ready to start processing network messages. If true, messages will start being processed as soon as the connection is established.

    
    NetEndPointBodyC(const StringC &address,bool autoInit = true);
    //: Constructor.
    //!param: address -  has the format  `host:port' where `host' may be a host name or its IP address (e.g. 122.277.96.255) and `port' is the number of the port to use.
    //!param: autoInit - If false, you must call the Ready() function when you are ready to start processing network messages. If true, messages will start being processed as soon as the connection is established.

    NetEndPointBodyC(SocketC &socket,const StringC &protocolName,const StringC &protocolVersion,bool autoInit = true);
    //: Constructor.
    //!param: socket - connext to existing socket
    //!param: protocolName - Name of communication protocol being used.
    //!param: protocolVersion - Version of communication protocol being used.
    //!param: autoInit - If false, you must call the Ready() function when you are ready to start processing network messages. If true, messages will start being processed as soon as the connection is established.
    
    NetEndPointBodyC(const StringC &address,const StringC &protocolName,const StringC &protocolVersion,bool autoInit = true);
    //: Constructor.
    //!param: address -  has the format  `host:port' where `host' may be a host name or its IP address (e.g. 122.277.96.255) and `port' is the number of the port to use.
    //!param: protocolName - Name of communication protocol being used.
    //!param: protocolVersion - Version of communication protocol being used.
    //!param: autoInit - If false, you must call the Ready() function when you are ready to start processing network messages. If true, messages will start being processed as soon as the connection is established.
    
    NetEndPointBodyC(const DPIByteStreamC &istrm,const DPOByteStreamC &ostrm,const StringC &protocolName,const StringC &protocolVersion,bool autoInit = true);
    //: Constructor.
    //!param: istrm - Input comunications stream
    //!param: ostrm - Output comunications stream
    //!param: protocolName - Name of communication protocol being used.
    //!param: protocolVersion - Version of communication protocol being used.
    //!param: autoInit - If false, you must call the Ready() function when you are ready to start processing network messages. If true, messages will start being processed as soon as the connection is established.
    
    NetEndPointBodyC();
    //: Default constructor.
    
    ~NetEndPointBodyC();
    //: Destructor.
    
    bool IsOpen() const { 
      if(!istrm.IsValid() || !ostrm.IsValid())
	return false;
      return !shutdown && !istrm.IsGetEOS() && ostrm.IsPutReady(); 
    }
    //: Is Connections open ?
    
    bool Init(SocketC &skt);
    //: Setup a connection.
    // This should only be used if net end point 
    // has been created by the default constructor.
    
    bool WaitSetupComplete(RealT timeOut = 10);
    //: Wait for setup to complete.
    
    bool WaitTransmitQClear();
    //: Wait for the transmit queue to clear.
    
    bool Close();
    //: Close connection.

#if 0
    inline SocketC &Socket(void) 
    { return skt ; }
    //: Access the socket 
#endif
    
    StringC ConnectedHost();
    //: Access the name of the connected Host 
    
    IntT ConnectedPort();
    //: Access the name of the connected Port 
    
    const StringC &RemoteUser() const
    { return remoteUser; }
    //: Access name of remote user.
    
    bool Transmit(const NetPacketC &pkt) { 
      if(shutdown) return false; // Don't Q new stuff if we're shutting down.
      transmitQ.Put(pkt);
      return true;
    }
    //: Queue a packet for transmition.
    
    bool MsgInit(StringC &user,NetClientInfoC &info);
    //: Init message.

    bool Ready();
    //: Initalise link.

    void SndInit(StringC &user);
    //: Send init message.
    
    bool Send(UIntT id);
    //: Send a 0 parameter message.
    
    template<class Data1T>
    bool Send(UIntT id,const Data1T &dat1) {
      BufOStreamC os;
      BinOStreamC bos(os);
      bos.UseBigEndian(useBigEndianBinStream);
      bos << id << dat1;
      return Transmit(NetPacketC(os.Data()));
    }
    //: Send a 1 parameter message.
    
    template<class Data1T,class Data2T>
    bool Send(UIntT id,const Data1T &dat1,const Data2T &dat2) {
      BufOStreamC os;
      BinOStreamC bos(os);
      bos.UseBigEndian(useBigEndianBinStream);
      bos << id << dat1 << dat2;
      return Transmit(NetPacketC(os.Data()));
    }
    //: Send a 2 parameter message.

    template<class Data1T,class Data2T,class Data3T>
    bool Send(UIntT id,const Data1T &dat1,const Data2T &dat2,const Data3T &dat3) {
      BufOStreamC os;
      BinOStreamC bos(os);
      bos.UseBigEndian(useBigEndianBinStream);
      bos << id << dat1 << dat2  << dat3;
      return Transmit(NetPacketC(os.Data()));
    }
    //: Send a 3 parameter message.
    
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
    
    TriggerC &ConnectionBroken()
    { return connectionBroken; }
    //: Access trigger called if connection broken.
    
    void ConnectionBroken(const TriggerC &);
    //: Set new trigger to be called if connection broken.
    
    const StringC &ProtocolName() const
    { return localInfo.protocol; }
    //: Name of local protocol being used.
    
    const StringC &ProtocolVersion() const
    { return localInfo.protocolVersion; }
    //: Version of local protocol.
    
    const StringC &AppName() const
    { return localInfo.appName; }
    //: Name of local application.
    
    const StringC &AppVersion() const
    { return localInfo.appVersion; }
    //: Version of local application.
    
    NetClientInfoC &LocalInfo()
    { return localInfo; }
    // Info for this application.
    
    NetClientInfoC &PeerInfo()
    { return peerInfo; }
    // Info for remote application.
    
  protected:
    
    bool RunTransmit();
    //: Handle packet transmition.
    
    bool RunReceive();
    //: Handle packet reception.
    
    bool RunDecode();
    //: Decodes incoming packets.
    
    
    void CloseTransmit();
    //: Close down for transmit thread.
    
    void CloseDecode();
    //: Close down for decode thread.
    
    DPIByteStreamC istrm; // Input channel 
    DPOByteStreamC ostrm; // Output channel
    
    MessageQueueC<NetPacketC> transmitQ; // Transmition Q.
    MessageQueueC<NetPacketC> receiveQ; // Recieve Q.
    volatile bool shutdown;   // Shutdown system ?
    ThreadEventC setupComplete;
    ThreadEventC gotStreamType;
    StringC streamType;
    StringC remoteUser;
    MutexC accessMsgReg;
    HashC<UIntT,NetMsgRegisterC> msgReg;  // Local register of decoding routines.
    friend class NetEndPointC;
    bool autoInit;
    TriggerC connectionBroken; // Trigger called if connection broken.
    
    NetClientInfoC localInfo; // Info for this application.
    NetClientInfoC peerInfo;  // Info for remote application.
    bool useBigEndianBinStream;
  };
  
  //! userlevel=Normal
  //:  An end point for a network packet base protocol.

  // <p>This class provides a peer to peer communication mechanism for
  // operation over a network.  The user can register functions to be
  // called when messages (identified by an ID number) are sent over
  // the connection. Sending and receiving are handled asynchronously:
  // one thread handles sending messages from the transmit queue,
  // whilst the other handles decoding of messages and dispatching
  // them to the receiver functions.</p> 

  // <p>Note: There is only 1 receiver thread, if you wish to process
  // other incoming messages whilst handling a long request you should
  // use LaunchThread() to create a separate thread for handling
  // it.</p> 

  // <p>Note: The processing threads hold a reference to this class and
  // it will not be destroyed until the connection is closed down,
  // either with the 'Close()' method or by losing the connection.</p>
  
  class NetEndPointC 
    : public RCHandleC<NetEndPointBodyC>
  {
  public:
    NetEndPointC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    NetEndPointC(SocketC &socket,bool autoInit = true)
      : RCHandleC<NetEndPointBodyC>(*new NetEndPointBodyC(socket,autoInit))
    {}
    //: Constructor.  
    //!param: socket - connext to existing socket
    //!param: autoInit - If false, you must call the Ready() function when you are ready to start processing network messages. If true, messages will start being processed as soon as the connection is established.
    
    NetEndPointC(const StringC &address,bool autoInit = true)
      : RCHandleC<NetEndPointBodyC>(*new NetEndPointBodyC(address,autoInit))
    {}
    //: Constructor.
    // This connects to the given port address. <p>
    //!param: address -  has the format  `host:port' where `host' may be a host name or its IP address (e.g. 122.277.96.255) and `port' is the number of the port to use.
    //!param: autoInit - If false, you must call the Ready() function when you are ready to start processing network messages. If true, messages will start being processed as soon as the connection is established.
    
    NetEndPointC(const DPIByteStreamC &istrm,const DPOByteStreamC &ostrm,const StringC &protocolName,const StringC &protocolVersion,bool autoInit = true)
      : RCHandleC<NetEndPointBodyC>(*new NetEndPointBodyC(istrm,ostrm,protocolName,protocolVersion,autoInit))
    {}
    //: Constructor.
    //!param: istrm - Input comunications stream
    //!param: ostrm - Output comunications stream
    //!param: protocolName - Name of communication protocol being used.
    //!param: protocolVersion - Version of communication protocol being used.
    //!param: autoInit - If false, you must call the Ready() function when you are ready to start processing network messages. If true, messages will start being processed as soon as the connection is established.
    
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
    
#if 0
    inline SocketC Socket (void) 
    { return Body().Socket() ; } 
    //: Access the socket 
#endif

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
    
    bool WaitSetupComplete(RealT timeOut = 10)
    { return Body().WaitSetupComplete(timeOut); }
    //: Wait for setup to complete.
    // May fail if peer drops connection for some resson.
    
    bool WaitTransmitQClear()
    { return Body().WaitTransmitQClear(); }
    //: Wait for the transmit queue to clear.
    // Will return immediatly if the NetEndPoint is closed.
    
    bool Close()
    { return Body().Close(); }
    //: Close connection.
    
    bool Transmit(const NetPacketC &pkt)
    { return Body().Transmit(pkt); }
    //: Queue a packet for transmition.
    
    bool MsgInit(StringC &user,NetClientInfoC &info)
    { return  Body().MsgInit(user,info); }
    //: Init message.

    bool Register(const NetMsgRegisterC &nmsg)
    { return Body().Register(nmsg); }
    //: Register new message handler.
    
    bool Send(UIntT id)
    { return Body().Send(id); }
    //: Send a 0 parameter message.
    
    template<class Data1T>
    bool Send(UIntT id,const Data1T &dat1)
    { return Body().Send(id,dat1); }
    //: Send a 1 parameter message.
    
    template<class Data1T,class Data2T>
    bool Send(UIntT id,const Data1T &dat1,const Data2T &dat2)
    { return Body().Send(id,dat1,dat2); }
    //: Send a 2 parameter message.

    template<class Data1T,class Data2T,class Data3T>
    bool Send(UIntT id,const Data1T &dat1,const Data2T &dat2,const Data3T &dat3)
    { return Body().Send(id,dat1,dat2,dat3); }
    //: Send a 3 parameter message.
    
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
    
    TriggerC &ConnectionBroken()
    { return Body().ConnectionBroken(); }
    //: Access trigger called if connection broken.
    
    void ConnectionBroken(const TriggerC &trigger)
    { Body().ConnectionBroken(trigger); }
    //: Set new trigger to be called if connection broken.

    const StringC &ProtocolName() const
    { return Body().ProtocolName(); }
    //: Name of protocol being used.
    
    const StringC &ProtocolVersion() const
    { return Body().ProtocolVersion(); }
    //: Version of protocol.
    
    const StringC &AppName() const
    { return Body().AppName(); }
    //: Name of application.
    
    const StringC &AppVersion() const
    { return Body().AppVersion(); }
    //: Version of application.
    
    NetClientInfoC &LocalInfo()
    { return Body().LocalInfo(); }
    // Info for this application.
    
    NetClientInfoC &PeerInfo()
    { return Body().PeerInfo(); }
    // Info for remote application.
    
    friend class NetEndPointBodyC;
  };
  
  
}

#endif
