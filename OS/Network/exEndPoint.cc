// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlOS
//! file="Ravl/OS/Network/exEndPoint.cc"

#include "Ravl/Option.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/OS/NetEndPoint.hh"
#include "Ravl/OS/Date.hh"
//#include "Ravl/BinString.hh"

using namespace RavlN;

class TestRecieveC {
 public:
  bool HandleMessage(StringC &msg) {
    cerr << "TestRecieveC::HandleMessage() : Got '" << msg << "' \n";
    return true;
  }
};


int exEndPoint(int nargs,char *args[]) 
{  
  // Do normal option processing ....
  
  OptionC opt(nargs,args);
  StringC addr = opt.String("a","localhost:4041","Address to connect to. ");
  bool serv = opt.Boolean("s",false,"Server. ");
  opt.Check();
  TestRecieveC atest; 
  if(serv) {
    // Start a socket server.
    SocketC sktserv(addr,true);
    if(!sktserv.IsOpen()) {
      cerr << "Failed to open server socket. \n";
      return 1;
    }
    while(1) {
      SocketC skt = sktserv.Listen();
      // When a socket connects, make and end point and send a 'hello' message.
      NetEndPointC ep(skt);
      ep.Register(2,"Test",atest,&TestRecieveC::HandleMessage);
      
      StringC msg("Hello from server.");
      ep.Send(2,msg);
    }
  }
  {
    NetEndPointC ep(addr);
    // Register reciever function for the hello message.
    ep.Register(2,"Test",atest,&TestRecieveC::HandleMessage);
    // Wait for hello messages.
    StringC msg("Hello from client.");
    ep.Send(2,msg);
    while(1)
      Sleep(10);
  }  
  return 0;
}

RAVL_ENTRY_POINT(exEndPoint);
