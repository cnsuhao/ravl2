// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlNet

#include "Ravl/OS/NetIPortServer.hh"
#include "Ravl/OS/NetPortManager.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  NetISPortServerBaseBodyC::NetISPortServerBaseBodyC(const DPSeekCtrlC &nSeekCtrl,const StringC &nPortName)
    : portName(nPortName),
      seekCtrl(nSeekCtrl),
      at(0)
  {}
  
  //: Get the port type.
  
  StringC NetISPortServerBaseBodyC::PortType() 
  { return TypeName(typeid(void)); }
  
  bool NetISPortServerBaseBodyC::Connect(NetEndPointC &nep) {
    ONDEBUG(cerr << "NetISPortServerBaseBodyC::Connect(), Called \n");
    RavlAssert(nep.IsValid());
    ep = nep;
    if(!Init()) {
      cerr << "NetISPortServerBaseBodyC::Connect(), Failed. \n";
      return false;
    }
    return true;
  }

  
  //: Initalise stream.
  
  bool NetISPortServerBaseBodyC::Init() {
    ONDEBUG(cerr << "NetISPortServerBaseBodyC::Init(), Called. \n");
    ep.RegisterR(2,"ReqState",*this,&NetISPortServerBaseBodyC::ReqStats);
    ep.Ready();
    ep.WaitSetupComplete(); 
    return true;
  }
  
  //: Request stream stats.
  
  bool NetISPortServerBaseBodyC::ReqStats() {
    ONDEBUG(cerr << "NetISPortServerBaseBodyC::ReqStats(), Called. \n");
    UIntT at = seekCtrl.Tell();
    UIntT start = seekCtrl.Start();
    UIntT size = seekCtrl.Size();
    ep.Send(3,at,start,size);
    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Export ISPort.
  
  bool NetExportBase(const StringC &name,NetISPortServerBaseC &isp) {
    GlobalNetPortManager().Register(name,isp);    
    return true;
  }

}
