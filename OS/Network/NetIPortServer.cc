// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlNet
//! file="Ravl/OS/Network/NetIPortServer.cc"

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
  { ONDEBUG(cerr << "NetISPortServerBaseBodyC::NetISPortServerBaseBodyC(), Called. Name=" << portName << " \n"); }
  
  //: Destructor.
  
  NetISPortServerBaseBodyC::~NetISPortServerBaseBodyC() 
  { cerr << "NetISPortServerBaseBodyC::~NetISPortServerBaseBodyC(), Called. Name=" << portName << " \n";  }
  
  //: Get the port type.
  
  StringC NetISPortServerBaseBodyC::PortType() 
  { return TypeName(typeid(void)); }
  
  bool NetISPortServerBaseBodyC::Connect(NetEndPointC &nep) {
    ONDEBUG(cerr << "NetISPortServerBaseBodyC::Connect(), Called \n");
    if(ep.IsValid())
      return false; // Already connected!
    RavlAssert(nep.IsValid());
    ep = nep;
    if(!Init()) {
      cerr << "NetISPortServerBaseBodyC::Connect(), Failed. \n";
      return false;
    }
    return true;
  }
  
  //: Disonnect to an end point.
  
  bool NetISPortServerBaseBodyC::Disconnect() {
    cerr << "NetISPortServerBaseBodyC::Disconnect(), Called. \n";
    ep.Invalidate();
    return true;
  }
  
  //: Initalise stream.
  
  bool NetISPortServerBaseBodyC::Init() {
    ONDEBUG(cerr << "NetISPortServerBaseBodyC::Init(), Called. \n");
    ep.RegisterR(2,"ReqState",*this,&NetISPortServerBaseBodyC::ReqStats);
    return true;
  }
  
  //: Request stream stats.
  
  bool NetISPortServerBaseBodyC::ReqStats() {
    ONDEBUG(cerr << "NetISPortServerBaseBodyC::ReqStats(), Called. \n");
    UIntT at = 0;
    UIntT start = 0;
    UIntT size = ((UIntT) -1);
    if(seekCtrl.IsValid()) {
      at = seekCtrl.Tell();
      start = seekCtrl.Start();
      size = seekCtrl.Size();
    }
    ep.Send(3,at,start,size);
    ONDEBUG(cerr << "NetISPortServerBaseBodyC::ReqStats(), Sent: At=" << at << " Start=" << start << " Size=" << size << "\n");
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
