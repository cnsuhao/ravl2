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
//! file="Ravl/OS/Network/NetPortManager.cc"

#include "Ravl/OS/Date.hh"
#include "Ravl/OS/NetPortManager.hh"
#include "Ravl/OS/NetPortClient.hh"
#include "Ravl/Threads/LaunchThread.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  NetPortManagerBodyC::NetPortManagerBodyC(const StringC &nname)
    : name(nname),
      managerOpen(false),
      ready(0)
  {}
  
  //: Open manager at address.
  
  bool NetPortManagerBodyC::Open(const StringC &addr) {
    ONDEBUG(cerr << "NetPortManagerBodyC::Open(), Called for " << addr << " \n");
    
    RWLockHoldC hold(access,false);
    if(managerOpen) {
      cerr << "NetPortManagerBodyC::Open(), Attempt to re-open port manager at '" << addr << "'\n";
      return false; 
    }
    
    sktserv = SocketC(addr,true);
    if(!sktserv.IsOpen()) {
      cerr << "NetPortManagerBodyC::Run(), Failed to open server socket. '" << addr << "' \n";
      return false;
    }
    
    managerOpen = true;
    NetPortManagerC manager(*this);
    LaunchThread(manager,&NetPortManagerC::Run);
    ready.Wait();
    Sleep(0.1);
    return true;
  }
  
  
  //: Run port manager.
  
  bool NetPortManagerBodyC::Run() {
    ONDEBUG(cerr << "NetPortManagerBodyC::Run(), Called. \n");
    RavlAssert(sktserv.IsOpen());
    NetPortManagerC manager(*this);
    ready.Post();
    while(1) {
      SocketC skt = sktserv.Listen();
      // When a socket connects, make and end point and send a 'hello' message.
      NetPortClientC cl(skt,manager);
      // Register client somewhere ?
    }
    return true;
  }
  
  //: Search for port in table.
  
  bool NetPortManagerBodyC::Lookup(const StringC &name,NetISPortServerBaseC &isport) {
    ONDEBUG(cerr << "NetPortManagerBodyC::Lookup(),  Called. Port='" << name << "' \n");
    NetISPortServerBaseC ret; 
    RWLockHoldC hold(access,RWLOCK_READONLY);
    return iports.Lookup(name,isport);
  }

  bool NetPortManagerBodyC::Lookup(const StringC &name,NetOSPortServerBaseC &osport) {
    ONDEBUG(cerr << "NetPortManagerBodyC::Lookup(),  Called. Port='" << name << "' \n");
    NetISPortServerBaseC ret; 
    RWLockHoldC hold(access,RWLOCK_READONLY);
    return oports.Lookup(name,osport);
  }
  
  //: Register new port.
  
  bool NetPortManagerBodyC::Register(const StringC &name,NetISPortServerBaseC &ips) {
    ONDEBUG(cerr << "NetPortManagerBodyC::Register(),  Called. Port='" << name << "' \n");
    RWLockHoldC hold(access,RWLOCK_WRITE);
    if(iports.IsElm(name)) 
      return false; // Already registered.
    iports[name] = ips;
    return true;
  }

  bool NetPortManagerBodyC::Register(const StringC &name,NetOSPortServerBaseC &ops) {
    ONDEBUG(cerr << "NetPortManagerBodyC::Register(),  Called. Port='" << name << "' \n");
    RWLockHoldC hold(access,RWLOCK_WRITE);
    if(oports.IsElm(name)) 
      return false; // Already registered.
    oports[name] = ops;
    return true;
  }
  
  //: Unregister port.
  
  bool NetPortManagerBodyC::Unregister(const StringC &name) {
    ONDEBUG(cerr << "NetPortManagerBodyC::Unregister(), Called. Name='" << name << "'\n");
    RWLockHoldC hold(access,RWLOCK_WRITE);
    return iports.Del(name);
  }
  
  //: Called when a connection is established.
  
  bool NetPortManagerBodyC::RegisterConnection(NetISPortServerBaseC &isport) {
    return true;
  }

  //: Called when a connection is established.
  
  bool NetPortManagerBodyC::RegisterConnection(NetOSPortServerBaseC &osport) {
    return true;
  }
  
  
  //: Access global net port manager.

  NetPortManagerC &GlobalNetPortManager() {
    static NetPortManagerC npm("global");
    return npm;
  }
  
  //: Open net port manager.
  
  bool NetPortOpen(const StringC &addr) 
  { return GlobalNetPortManager().Open(addr); }

}
