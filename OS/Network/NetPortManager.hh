// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_NETPORTMANAGER_HEADER
#define RAVL_NETPORTMANAGER_HEADER 1
////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlNet

#include "Ravl/String.hh"
#include "Ravl/OS/Socket.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/Hash.hh"
#include "Ravl/OS/NetIPortServer.hh"
#include "Ravl/Threads/RWLock.hh"

namespace RavlN {
  
  class NetPortManagerC;
  
  //! userlevel=Develop
  //: Net port manager.
  
  class NetPortManagerBodyC 
    : public RCBodyC
  {
  public:
    NetPortManagerBodyC(const StringC &name);
    //: Constructor.
    
    NetISPortServerBaseC Lookup(const StringC &name);
    //: Search for port in table.

    bool Register(const StringC &name,NetISPortServerBaseC &ips);
    //: Register new port.

    bool Unregister(const StringC &name);
    //: Unregister port.
    
    bool Open(const StringC &addr);
    //: Open manager at address.
    
  protected:
    bool Run();
    //: Run port manager.
    
    StringC name;
    
    // Table of iports.
    HashC<StringC,NetISPortServerBaseC> iports;
    RWLockC access;
    
    bool managerOpen;
    SocketC sktserv;
    
    friend class NetPortManagerC;
  };

  //! userlevel=Advanced
  //: Net port manager.
  
  class NetPortManagerC 
    : public RCHandleC<NetPortManagerBodyC>
  {
  public:
    NetPortManagerC(const StringC &name)
      : RCHandleC<NetPortManagerBodyC>(*new NetPortManagerBodyC(name))
    {}
    //: Constructor.
    
    NetPortManagerC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

  protected:
    NetPortManagerC(NetPortManagerBodyC &bod)
      : RCHandleC<NetPortManagerBodyC>(bod)
    {}
    //: Body constructor.
    
    NetPortManagerBodyC &Body()
    { return RCHandleC<NetPortManagerBodyC>::Body(); }
    //: Access body.

    const NetPortManagerBodyC &Body() const
    { return RCHandleC<NetPortManagerBodyC>::Body(); }
    //: Access body.

    bool Run()
    { return Body().Run(); }
    //: Run manager thread.
  public:
    
    NetISPortServerBaseC Lookup(const StringC &name)
    { return Body().Lookup(name); }
    //: Search for port in table.
    
    bool Register(const StringC &name,NetISPortServerBaseC &ips)
    { return Body().Register(name,ips); }
    //: Register port.
    
    bool Unregister(const StringC &name)
    { return Body().Unregister(name); }
    //: Unregister port.
    
    bool Open(const StringC &addr)
    { return Body().Open(addr); }
    //: Open manager at address.
    
    friend class NetPortManagerBodyC;
  };
  
  NetPortManagerC &GlobalNetPortManager();
  //: Access global net port manager.

  bool NetPortOpen(const StringC &addr);
  //: Open net port manager.
}

#endif
