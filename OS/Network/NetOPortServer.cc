// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlNet
//! file="Ravl/OS/Network/NetOPortServer.cc"

#include "Ravl/OS/NetOPortServer.hh"
#include "Ravl/OS/NetPortManager.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  NetOSPortServerBaseBodyC::NetOSPortServerBaseBodyC(const DPSeekCtrlC &nSeekCtrl,const StringC &nPortName)
    : portName(nPortName),
      seekCtrl(nSeekCtrl),
      at(0)
  { ONDEBUG(cerr << "NetOSPortServerBaseBodyC::NetOSPortServerBaseBodyC(), Called. Name=" << portName << " \n"); }
  
  //: Destructor.
  
  NetOSPortServerBaseBodyC::~NetOSPortServerBaseBodyC() 
  { cerr << "NetOSPortServerBaseBodyC::~NetOSPortServerBaseBodyC(), Called. Name=" << portName << " \n";  }
  
  //: Get the port type.
  
  StringC NetOSPortServerBaseBodyC::PortType() 
  { return TypeName(typeid(void)); }
  
  bool NetOSPortServerBaseBodyC::Connect(NetEndPointC &nep) {
    ONDEBUG(cerr << "NetOSPortServerBaseBodyC::Connect(), Called \n");
    if(ep.IsValid())
      return false; // Already connected!
    RavlAssert(nep.IsValid());
    ep = nep;
    if(!Init()) {
      cerr << "NetOSPortServerBaseBodyC::Connect(), Failed. \n";
      return false;
    }
    return true;
  }
  
  //: Disonnect to an end point.
  
  bool NetOSPortServerBaseBodyC::Disconnect() {
    cerr << "NetOSPortServerBaseBodyC::Disconnect(), Called. \n";
    ep.Invalidate();
    return true;
  }
  
  //: Initalise stream.
  
  bool NetOSPortServerBaseBodyC::Init() {
    ONDEBUG(cerr << "NetOSPortServerBaseBodyC::Init(), Called. \n");
    ep.RegisterR(2,"ReqState",*this,&NetOSPortServerBaseBodyC::ReqStats);
    return true;
  }
  
  //: Request stream stats.
  
  bool NetOSPortServerBaseBodyC::ReqStats() {
    ONDEBUG(cerr << "NetOSPortServerBaseBodyC::ReqStats(), Called. \n");
    UIntT at = 0;
    UIntT start = 0;
    UIntT size = ((UIntT) -1);
    if(seekCtrl.IsValid()) {
      at = seekCtrl.Tell();
      start = seekCtrl.Start();
      size = seekCtrl.Size();
    }
    ep.Send(3,at,start,size);
    ONDEBUG(cerr << "NetOSPortServerBaseBodyC::ReqStats(), Sent: At=" << at << " Start=" << start << " Size=" << size << "\n");
    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Export ISPort.
  
  bool NetExportBase(const StringC &name,NetOSPortServerBaseC &isp) {
    GlobalNetPortManager().Register(name,isp);
    return true;
  }

}
