// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlNet
//! file="Ravl/OS/Network/testNetPort.cc"
//! docentry="Ravl.OS.Network.NetPort"
//! userlevel=Normal
//! author="Charles Galambos"

#include "Ravl/OS/NetIPort.hh"
#include "Ravl/OS/NetIPortServer.hh"
#include "Ravl/OS/NetOPort.hh"
#include "Ravl/OS/NetOPortServer.hh"
#include "Ravl/DP/ContainerIO.hh"
#include "Ravl/DP/Compose.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/OS/NetPortManager.hh"

using namespace RavlN;

int testNetIPort();
int testNetOPort();

StringC server;

int main() {
  int ln;
  
  cerr << "testNetPort(), Start port server. \n";
  
  server = StringC("localhost:4046");
  
  if(!NetPortOpen(server)) {
    cerr << "Failed to open netPortManager. \n";
    return __LINE__;
  }
  if((ln = testNetIPort()) != 0) {
    cerr << "Test failed on line :" << ln << "\n";
    return 1;
  }
  if((ln = testNetOPort()) != 0) {
    cerr << "Test failed on line :" << ln << "\n";
    return 1;
  }
  
  cout << "Test passed ok. \n";
  return 0;
}

int testNetIPort() {
  cerr << "testNetPort(), Test started. \n";

  // ********************** SERVER SIDE ************************************
  // Setup some data.
  DListC<IntT> lst;
  lst.InsLast(1);
  lst.InsLast(2);
  lst.InsLast(3);
  
  // Setup server IPort.
  cerr << "testNetPort(), Setup server IPort. \n";
  DPIPortC<IntT> op = DPIContainer(lst);

  // Export the stream 'op' as test1
  if(!NetExport("test1",op)) {
    cerr << "Failed to export 'test1' \n";
    return __LINE__;
  }
  
  // ********************** CLIENT SIDE ******************************
  
  cerr << "testNetPort(), Setup  NetIPort. \n";

  // Make a connection to the server.
  NetISPortC<IntT>  isp (server,"test1");
  
  // Should check it succeeded here.
  
  DListC<IntT> lst2;
  
  // Transfer data from server to lst2
  
  cerr << "testNetPort(), Transfer data. \n";
  
  isp >> DPOContainer(lst2);
  
  // ********************** CHECK IT WORKED ************************
  
  cerr << "testNetPort(), Check data. Elements=" << lst2.Size() << "\n";
  // Check the results.
  if(lst2.Size() != lst.Size()) return __LINE__;
  if(lst2.First() != lst.First()) return __LINE__;
  if(lst2.Last() != lst.Last()) return __LINE__;
  return 0;
}




int testNetOPort() {
  cerr << "testNetPort(), Test started. \n";

  // ********************** SERVER SIDE ************************************
  // Setup some data.
  DListC<IntT> lst;
  
  // Setup server IPort.
  cerr << "testNetPort(), Setup server OPort. \n";
  DPOPortC<IntT> op = DPOContainer(lst);
  
  // Export the stream 'op' as test2
  if(!NetExport("test2",op)) {
    cerr << "Failed to export 'test2' \n";
    return __LINE__;
  }
  
  // ********************** CLIENT SIDE ******************************
  
  cerr << "testNetPort(), Setup  NetOPort. \n";

  // Make a connection to the server.
  NetOSPortC<IntT>  osp (server,"test2");
  
  // Should check it succeeded here.
  
  DListC<IntT> lst2;
  lst2.InsLast(1);
  lst2.InsLast(2);
  lst2.InsLast(3);
  
  // Transfer data from server to lst2
  
  cerr << "testNetPort(), Transfer data. \n";
  
  DPIContainer(lst2) >> osp;
  Sleep(1); // Wait for data to be sent.
  
  // ********************** CHECK IT WORKED ************************
  
  cerr << "testNetPort(), Check data. Elements=" << lst.Size() << "\n";
  // Check the results.
  if(lst2.Size() != lst.Size()) return __LINE__;
  if(lst2.First() != lst.First()) return __LINE__;
  if(lst2.Last() != lst.Last()) return __LINE__;
  return 0;
}
