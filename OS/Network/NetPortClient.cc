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

#include "Ravl/OS/NetPortClient.hh"

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
  { Init(); }
  
  //: Initalise connection.
  
  bool NetPortClientBodyC::Init() {
    ONDEBUG(cerr << "NetPortClientBodyC::Init(), Called. \n");
    RegisterR(10,"ConnectTo",*this,&NetPortClientBodyC::MsgConnectTo);
    Ready();
    WaitSetupComplete();
    return true;
  }
  
  //: Handle connect to message.
  
  bool NetPortClientBodyC::MsgConnectTo(StringC &port,StringC &datatype) {
    ONDEBUG(cerr << "NetPortClientBodyC::MsgConnectTo(), Called. Port=" << port << " Type=" << datatype << "\n");
    NetISPortServerBaseC isport;
    isport = manager.Lookup(port);
    if(!isport.IsValid()) {
      cerr << "NetPortClientBodyC::MsgConnectTo(), Failed to find port. \n";
      // Send a failure message ?
      return true;
    }
    if(isport.PortType() != datatype) {
      cerr << "NetPortClientBodyC::MsgConnectTo(), Missmatch in data types. \n";      
      return true;
    }
    // Connect something ?
    NetPortClientC me(*this);
    isport.Connect(me);
    return true;
  }

}
