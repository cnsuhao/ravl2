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
#include "Ravl/OS/NetMessage.hh"
#include "Ravl/OS/NetMsgCall.hh"
#include "Ravl/CallMethodRefs.hh"
#include "Ravl/CallMethods.hh"

namespace RavlN {

  class NetEndPointC;
  
  //! userlevel=Develop
  //: An end point for a network packet base protocol.
  
  class NetEndPointBodyC 
    : public RCBodyVC
  {
  public:
    NetEndPointBodyC(SocketC &skt);
    //: Constructor.
    
    NetEndPointBodyC(const StringC &skt,bool serv = false);
    //: Constructor.
    
    ~NetEndPointBodyC();
    //: Destructor.
    
    void Transmit(const NetPacketC &pkt)
      { transmitQ.Put(pkt); }
    //: Queue a packet for transmition.
    
    bool MsgInit(StringC &user);
    //: Init message.

    void SndInit(StringC &user);
    //: Send init message.

    template<class Data1T>
    bool Send(UIntT id,const Data1T &dat1) {
      OBufStreamC os;
      BinOStreamC bos(os);
      bos << id << dat1;
      Transmit(NetPacketC(os.Data()));
      return true;
    }
    //: Send a 1 paramiter message.
    
    template<class Data1T,class Data2T>
    bool Send(UIntT id,const Data1T &dat1,const Data2T &dat2) {
      OBufStreamC os;
      BinOStreamC bos(os);
      bos << id << dat1 << dat2;
      Transmit(NetPacketC(os.Data()));
      return true;
    }
    //: Send a 1 paramiter message.
    
    bool Register(const NetMsgRegisterC &nmsg);
    //: Register new message handler.
    
    NetMsgRegisterC Find(UIntT id) const;
    //: Search for message decode/encode of type 'id'.

    template<class ObjT>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)()) {
      return Register(NetMsgCall0C(mid,msgName,CallMethodRef0C<ObjT,bool>(obj,func))); 
    }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.
    
    template<class ObjT,class DataT>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(DataT &)) {
      return Register(NetMsgCall1C<DataT>(mid,msgName,CallMethodRef1C<ObjT,DataT,bool>(obj,func))); 
    }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.

    template<class ObjT,class Data1T,class Data2T>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(Data1T &,Data2T &)) {
      return Register(NetMsgCall2C<Data1T,Data2T>(mid,msgName,CallMethodRef2C<ObjT,Data1T,Data2T,bool>(obj,func))); 
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
    bool Register(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(DataT &)) {
      return Register(NetMsgCall1C<DataT>(mid,msgName,CallMethod1C<ObjT,DataT,bool>(obj,func))); 
    }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.

    template<class ObjT,class Data1T,class Data2T>
    bool Register(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(Data1T &,Data2T &)) {
      return Register(NetMsgCall2C<Data1T,Data2T>(mid,msgName,CallMethod2C<ObjT,Data1T,Data2T,bool>(obj,func))); 
    }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.
    
  protected:
    void Init();
    //: Setup and startup the aproprate threads.
    
    bool RunTransmit();
    //: Handle packet transmition.
    
    bool RunReceive();
    //: Handle packet reception.
    
    bool RunDecode();
    //: Decodes incoming packets.
    
    SocketC skt;
    MessageQueueC<NetPacketC> transmitQ; // Transmition Q.
    MessageQueueC<NetPacketC> receiveQ; // Recieve Q.
    volatile bool shutdown;   // Shutdown system ?
    StringC remoteUser;
    HashC<UIntT,NetMsgRegisterC> msgReg;  // Local register of decoding routines.
    //HashC<UIntT,CallFunc0C<bool> > msgSigHandle;   // Table of signals to send on a message
    friend class NetEndPointC;
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

    NetEndPointC(SocketC &skt)
      : RCHandleC<NetEndPointBodyC>(*new NetEndPointBodyC(skt))
      {}
    //: Constructor.
    
    NetEndPointC(const StringC &addr,bool serv = false)
      : RCHandleC<NetEndPointBodyC>(*new NetEndPointBodyC(addr,serv))
      {}
    //: Constructor.
    // This connects to the given address.
    
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
    void Transmit(const NetPacketC &pkt)
      { Body().Transmit(pkt); }
    //: Queue a packet for transmition.
    
    bool MsgInit(StringC &user)
      { return  Body().MsgInit(user); }
    //: Init message.

    bool Register(const NetMsgRegisterC &nmsg)
      { return Body().Register(nmsg); }
    //: Register new message handler.
    
    template<class Data1T>
    bool Send(UIntT id,const Data1T &dat1)
      { return Body().Send(id,dat1); }
    //: Send a 1 paramiter message.
    
    template<class Data1T,class Data2T>
    bool Send(UIntT id,const Data1T &dat1,const Data2T &dat2)
      { return Body().Send(id,dat1,dat2); }
    //: Send a 1 paramiter message.

    template<class ObjT>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)())
      { return Body().RegisterR(mid,msgName,obj,func); }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.
    
    template<class ObjT,class DataT>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(DataT &))
      { return Body().RegisterR(mid,msgName,obj,func); }
    //: Register new message handler.
    // NB. This does not make a handle to 'obj', it is the users responsibility to 
    // ensure it is not deleted.

    template<class ObjT,class Data1T,class Data2T>
    bool RegisterR(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(Data1T &,Data2T &))
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
    bool Register(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(DataT &))
      { return Body().Register(mid,msgName,obj,func); }
    //: Register new message handler.
    // Hold a handle to the object called.
    
    template<class ObjT,class Data1T,class Data2T>
    bool Register(UIntT mid,const StringC &msgName,ObjT &obj,bool (ObjT::*func)(Data1T &,Data2T &))
      { return Body().Register(mid,msgName,obj,func); }
    //: Register new message handler.
    // Hold a handle to the object called.
    
    friend class NetEndPointBodyC;
  };
  
  
}

#endif
