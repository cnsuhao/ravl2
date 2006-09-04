// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlNet
//! file="Ravl/OS/Network/NetIPort.cc"

#include "Ravl/OS/NetIPort.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/OS/SysLog.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  NetISPortBaseC::NetISPortBaseC(const StringC &server,const StringC &nPortName,const type_info &ndataType) 
    : NetPortBaseC(server),
      portName(nPortName),
      dataType(TypeName(ndataType)),
      start(0),
      size((UIntT) -1),
      at(0),
      gotEOS(false),
      recieved(0),
      flag(0)
  {}
  
  //: Destructor.
  
  NetISPortBaseC::~NetISPortBaseC() { 
    ONDEBUG(cerr << "NetISPortBaseC::~NetISPortBaseC(), Called. \n");
  }
  
  bool NetISPortBaseC::Init() {
    ONDEBUG(cerr << "NetISPortBaseC::Init(), Called for '" << portName << "'\n");
    if(!ep.IsOpen()) {
      cerr << "NetISPortBaseC::Init(), WARNING: No connection. \n";
      gotEOS = true;
      return false;
    }
    if(!NetPortBaseC::Connect(ep))
      return false;
    
    ep.LocalInfo().ProtocolName("IPortClient");
    ep.LocalInfo().ProtocolVersion("1.0");    
    ep.RegisterR(NPMsg_StreamInfo,"StreamInfo",*this,&NetISPortBaseC::RecvState);
    ep.RegisterR(NPMsg_ReqFailed,"ReqFailed",*this,&NetISPortBaseC::ReqFailed);
    ep.Ready();
    if(!ep.WaitSetupComplete()) {
      cerr << "NetIPort(), ERROR: Failed to complete connection. \n";
      ep.Close();
      return false;
    }
    
    if(ep.PeerInfo().ProtocolName() != "PortServer") {
      SysLog(SYSLOG_ERR) << "Unexpected connection protocol '" << ep.PeerInfo().ProtocolName() << "'";
      ep.Close();
      return false;
    }
    
    if(ep.PeerInfo().ProtocolVersion() != ep.LocalInfo().ProtocolVersion()) {
      SysLog(SYSLOG_ERR) << "Unexpected protocol version '" << ep.PeerInfo().ProtocolVersion() << "'  (Local version "  << ep.LocalInfo().ProtocolVersion() << ") ";
      ep.Close();
      return false;
    }
    
    ep.Send(NPMsg_ReqConnection,portName,dataType,true);  // Request connection.
    if(!WaitForConnect())
      return false;
    netAttr.UpdateAttributeTypes(); 
    ep.Send(NPMsg_ReqInfo); // Request info about the stream.
    return true;
  }
  
  //: Wait for stream info to arrive.
  
  bool NetISPortBaseC::WaitForInfo() const {
    do {
      if(!ep.IsValid()) return false;
      if(!ep.IsOpen()) return false;
    } while(!gotStreamInfo.Wait(2));
    return true;
  }
  
  //: Handle incoming state info.
  
  bool NetISPortBaseC::RecvState(Int64T &nat,Int64T &nstart,Int64T &nsize) {
    ONDEBUG(cerr << "NetISPortBaseC::RecvState(), At=" << at << " Start=" << nstart << " Size=" << nsize << "\n");
    RWLockHoldC hold(rwlock,RWLOCK_WRITE);
    at = nat;
    start = nstart;
    size = nsize;
    gotStreamInfo.Post();
    return true;
  }
  
  //: Handle request failed.
  
  bool NetISPortBaseC::ReqFailed(IntT &nflag) {
    ONDEBUG(cerr << "NetISPortBaseC::ReqFailed(), Flag=" << flag << "\n");
    if(nflag == 1) gotEOS = true;
    flag = nflag;
    recieved.Post();
    return true;
  }

}
