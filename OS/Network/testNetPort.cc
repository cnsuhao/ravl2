// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlNet

#include "Ravl/OS/NetIPort.hh"
#include "Ravl/OS/NetIPortServer.hh"
#include "Ravl/DP/ContainerIO.hh"
#include "Ravl/DP/Compose.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/OS/NetPortManager.hh"

using namespace RavlN;

int testNetPort();

int main() {
  int ln;

  if((ln = testNetPort()) != 0) {
    cerr << "Test failed on line :" << ln << "\n";
    return 1;
  }
  
  cout << "Test passed ok. \n";
  return 0;
}

int testNetPort() {
  cerr << "testNetPort(), Test started. \n";
  // Setup some data.
  DListC<IntT> lst;
  lst.InsLast(1);
  lst.InsLast(2);
  lst.InsLast(3);

  cerr << "testNetPort(), Start port sever.. \n";
  
  StringC server = "localhost:4045";  
  if(!NetPortOpen(server)) {
    cerr << "Failed to open netPortManager. \n";
    return __LINE__;
  }
  
  // Setup server IPort.
  cerr << "testNetPort(), Setup server IPort. \n";
  DPIPortC<IntT> op = DPIContainer(lst);
  
  
  if(!NetExport("test1",op)) {
    cerr << "Failed to export 'test1' \n";
    return __LINE__;
  }
  
  // Setup IPort.
  cerr << "testNetPort(), Setup  NetIPort. \n";
  
  NetISPortC<IntT>  isp (server,"test1");
  
  DListC<IntT> lst2;
  
  // Transfer data.
  cerr << "testNetPort(), Transfer data. \n";
  //Sleep(0.1);
  isp >> DPOContainer(lst2);
  
  cerr << "testNetPort(), Check data. Elements=" << lst2.Size() << "\n";
  // Check the results.
  if(lst2.Size() != lst.Size()) return __LINE__;
  if(lst2.First() != lst.First()) return __LINE__;
  if(lst2.Last() != lst.Last()) return __LINE__;
  return 0;
}
