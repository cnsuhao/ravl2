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

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  NetISPortBaseC::NetISPortBaseC(const StringC &server,const StringC &nPortName,const type_info &ndataType) 
    : ep(server,false),
      portName(nPortName),
      dataType(TypeName(ndataType)),
      at(0),
      recieved(0),
      flag(0)
  {}
  
  //: Destructor.
  
  NetISPortBaseC::~NetISPortBaseC() { 
    ep.Close(); // Make sure NetEndPointC is closed before we complete close.
  }
  
  bool NetISPortBaseC::Init() {
    ONDEBUG(cerr << "NetISPortBaseC::Init(), Called for '" << portName << "'\n");
    if(!ep.IsOpen()) {
      cerr << "NetISPortBaseC::Init(), WARNING: No connection. \n";
      gotEOS = true;
      return false;
    }
    ep.RegisterR(3,"SendState",*this,&NetISPortBaseC::RecvState);
    ep.RegisterR(6,"ReqFailed",*this,&NetISPortBaseC::ReqFailed);
    ep.Ready();
    ep.WaitSetupComplete();
    ep.Send(10,portName,dataType);  // Request connection.
    ep.Send(2); // Request info about the stream.
    return true;
  }
  
  //: Handle incoming state info.
  
  bool NetISPortBaseC::RecvState(UIntT &nat,UIntT &nstart,UIntT &nsize) {
    ONDEBUG(cerr << "NetISPortBaseC::RecvState(), At=" << at << " Start=" << nstart << " Size=" << nsize << "\n");
    at = nat;
    start = nstart;
    size = nsize;
    return true;
  }

  //: Handle request failed.
  
  bool NetISPortBaseC::ReqFailed(IntT &nflag) {
    ONDEBUG(cerr << "NetISPortBaseC::ReqFailed(), Flag=" << flag << "\n");
    if(nflag == 1)
      gotEOS = true;
    flag = nflag;
    recieved.Post();
    return true;
  }

}
