// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlNet
//! file="Ravl/OS/Network/NetPortClient.cc"

#include "Ravl/OS/NetPortClient.hh"
#include "Ravl/OS/SysLog.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Construct from open socket.
  
  NetPortClientBodyC::NetPortClientBodyC(SocketC &skt,NetPortManagerC &nManager) 
    : NetEndPointBodyC(skt,false),
      manager(nManager)
  {}
  
  //: Destructor.
  
  NetPortClientBodyC::~NetPortClientBodyC() {
    ONDEBUG(cerr << "NetPortClientBodyC::~NetPortClientBodyC() Called. \n");
    // Make sure connections closed before destructing.
    Close();
  }
  
  //: Initalise connection.
  
  bool NetPortClientBodyC::Init() {
    ONDEBUG(cerr << "NetPortClientBodyC::Init(), Called. \n");
    LocalInfo().ProtocolName("PortServer");
    LocalInfo().ProtocolVersion("1.1");
    RegisterR(NPMsg_ReqConnection,"ConnectTo",*this,&NetPortClientBodyC::MsgConnectTo);
    RegisterR(NPMsg_Close,"Close",*this,&NetPortClientBodyC::MsgClose);
    Ready();
    if(!WaitSetupComplete()) {
      cerr << "NetPortClientBodyC::NetPortClientBodyC(), Connection init failed. \n";
      Close();
      return false;
    }
    // Check protocol.
    
    if(PeerInfo().ProtocolName() !=  "IPortClient" && PeerInfo().ProtocolName() !=  "OPortClient") {
      SysLog(SYSLOG_ERR) << "Unexpected connection protocol '" << PeerInfo().ProtocolName() << "' Expected:'OPortClient' or 'IPortClient'";
      Close();
      return false;
    }
    
    if(PeerInfo().ProtocolVersion() != "1.1") {
      SysLog(SYSLOG_ERR) << "Unexpected protocol version '" << PeerInfo().ProtocolVersion() << "'  (Local version "  << LocalInfo().ProtocolVersion() << ") ";
      Close();
      return false;
    }
    
    return true;
  }
  
  //: Handle connect to message.
  
  bool NetPortClientBodyC::MsgConnectTo(StringC &port,StringC &datatype,bool nIsIPort) {
    ONDEBUG(cerr << "NetPortClientBodyC::MsgConnectTo(), Called. Port=" << port << " Type=" << datatype << " IsIPort=" << nIsIPort << "\n");
    isIPort = nIsIPort;
    if(isIPort) {
      // Deal with input port.
      NetISPortServerBaseC isport;      
      if(!manager.Lookup(port,datatype,isport)) {
	cerr << "NetPortClientBodyC::MsgConnectTo(), Failed to find port. \n";
	Send(NPMsg_ReqFailed,1); // End of stream.
	// Send a failure message ?
	return true;
      }
      if(isport.PortType() != datatype) {
	cerr << "NetPortClientBodyC::MsgConnectTo(), Missmatch in data types. \n";      
	Send(NPMsg_ReqFailed,1); // End of stream.
	return true;
      }
      // Connect something ?
      NetPortClientC me(*this);
      if(!isport.Connect(me)) {
	cerr << "NetPortClientBodyC::MsgConnectTo(), Failed, Already connected. \n";
	Send(NPMsg_ReqFailed,1); // End of stream.
	// Return a failed message ?
	return true;
      }
      connectionName = port;
      manager.RegisterConnection(isport);
    } else {
      // Deal with output port.
      
      NetOSPortServerBaseC osport;
      if(!manager.Lookup(port,datatype,osport)) {
	cerr << "NetPortClientBodyC::MsgConnectTo(), Failed to find port. \n";
	Send(NPMsg_ReqFailed,1); // End of stream.
	// Send a failure message ?
	return true;
      }
      if(osport.PortType() != datatype) {
	cerr << "NetPortClientBodyC::MsgConnectTo(), Missmatch in data types. \n";      
	Send(NPMsg_ReqFailed,1); // End of stream.
	return true;
      }
      // Connect something ?
      NetPortClientC me(*this);
      ONDEBUG(cerr << "NetPortClientBodyC::MsgConnectTo(), Connecting OPort '" << port << "'. \n");
      if(!osport.Connect(me)) {
	cerr << "NetPortClientBodyC::MsgConnectTo(), Failed, Already connected. \n";
	Send(NPMsg_ReqFailed,1); // End of stream.
	// Return a failed message ?
	return true;
      }
      connectionName = port;
      ONDEBUG(cerr << "NetPortClientBodyC::MsgConnectTo(), Registering. \n");
      manager.RegisterConnection(osport);
    }
    Send(NPMsg_StreamReady);
    ONDEBUG(cerr << "NetPortClientBodyC::MsgConnectTo(), Done. ");
    return true;
  }

  //: Handle close message.
  // Close down an established connection.
  
  bool NetPortClientBodyC::MsgClose() {
    ONDEBUG(cerr << "NetPortClientBodyC::MsgClose(), Called. connectionName='" << connectionName << "'\n");
    Close();
    if(connectionName.IsEmpty())
      return true;
    StringC empty;
    if(isIPort) {
      NetISPortServerBaseC isport;
      if(!manager.Lookup(connectionName,empty,isport,false))
        return true;
      ONDEBUG(cerr << "NetPortClientBodyC::MsgClose(), disconnecting ISPort\n");
      if(isport.IsValid())
        isport.Disconnect();
    } else {
      NetOSPortServerBaseC osport;
      if(!manager.Lookup(connectionName,empty,osport,false))
        return true;
      ONDEBUG(cerr << "NetPortClientBodyC::MsgClose(), disconnecting OSPort\n");
      if(osport.IsValid())
        osport.Disconnect();
    }
    return true;
  }
  
}
