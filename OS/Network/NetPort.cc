// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlNet

#include "Ravl/OS/NetPort.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  NetPortBaseC::NetPortBaseC(const StringC &server)
    : ep(server,false),
      netAttr(0)
  {}

  //: Destructor.
  
  NetPortBaseC::~NetPortBaseC()
  {}

  //: Wait for connection complete.
  
  bool NetPortBaseC::WaitForConnect(RealT timeOut) {
    ONDEBUG(cerr << "NetPortBaseC::WaitForConnect(). Called. \n");
    if(!streamReady.Wait(timeOut)) {
      cerr << "NetPortBaseC::WaitForConnect(), Connection failed to complete. \n";
      return false;
    }
    ONDEBUG(cerr << "NetPortBaseC::WaitForConnect(). Done. \n");
    return true;
  }
  
  //: Handle incoming StreamReady message.
  
  bool NetPortBaseC::MsgStreamReady() {
    ONDEBUG(cerr << "NetPortBaseC::MsgStreamReady(). Called. \n");
    streamReady.Post();
    return true;
  }
  
  //: Initialise link.
  
  bool NetPortBaseC::Init() {
    ONDEBUG(cerr << "NetPortBaseC::Init(). Called. \n");
    ep.RegisterR(NPMsg_StreamReady,"StreamInfo",*this,&NetPortBaseC::MsgStreamReady);
    //: Handle incoming StreamReady message.
    
    return true;
  }

  //: Setup net end point.
  
  bool NetPortBaseC::Connect(NetEndPointC &nep) {
    ep = nep;
    netAttr.Connect(nep);
    NetPortBaseC::Init();
    return true;
  }

}
