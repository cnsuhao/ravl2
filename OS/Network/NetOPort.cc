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
//! file="Ravl/OS/Network/NetOPort.cc"

#include "Ravl/OS/NetOPort.hh"
#include "Ravl/TypeName.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  NetOSPortBaseC::NetOSPortBaseC(const StringC &server,const StringC &nPortName,const type_info &ndataType) 
    : ep(server,false),
      portName(nPortName),
      dataType(TypeName(ndataType)),
      start(0),
      size((UIntT) -1),
      at(0),
      gotEOS(false),
      flag(0)
  {}
  
  //: Destructor.
  
  NetOSPortBaseC::~NetOSPortBaseC() { 
    ONDEBUG(cerr << "NetOSPortBaseC::~NetOSPortBaseC(), Called. \n");
  }
  
  bool NetOSPortBaseC::Init() {
    ONDEBUG(cerr << "NetOSPortBaseC::Init(), Called for '" << portName << "'\n");
    if(!ep.IsOpen()) {
      cerr << "NetOSPortBaseC::Init(), WARNING: No connection. \n";
      gotEOS = true;
      return false;
    }
    ep.RegisterR(NPMsg_StreamInfo,"StreamInfo",*this,&NetOSPortBaseC::RecvState);
    ep.RegisterR(NPMsg_ReqFailed,"ReqFailed",*this,&NetOSPortBaseC::ReqFailed);
    ep.Ready();
    ep.WaitSetupComplete();
    ep.Send(NPMsg_ReqConnection,portName,dataType,false);  // Request connection.
    ep.Send(NPMsg_ReqInfo); // Request info about the stream.
    return true;
  }
  
  //: Handle incoming state info.
  
  bool NetOSPortBaseC::RecvState(UIntT &nat,UIntT &nstart,UIntT &nsize) {
    ONDEBUG(cerr << "NetOSPortBaseC::RecvState(), At=" << at << " Start=" << nstart << " Size=" << nsize << "\n");
    RWLockHoldC hold(rwlock,RWLOCK_WRITE);
    at = nat;
    start = nstart;
    size = nsize;
    return true;
  }
  
  //: Handle request failed.
  
  bool NetOSPortBaseC::ReqFailed(IntT &nflag) {
    ONDEBUG(cerr << "NetOSPortBaseC::ReqFailed(), Flag=" << flag << "\n");
    if(nflag == 1) gotEOS = true;
    flag = nflag;
    return true;
  }

}
