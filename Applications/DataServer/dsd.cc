// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/DataServer/DataServer.hh"
#include "Ravl/Option.hh"

using namespace RavlN;

int main(int nargs,char **vargs) {
  OptionC opts(nargs,vargs);
  StringC serverName = opts.String("n","DataServer","Name of data server. ");
  StringC serverAddr = opts.String("a","localhost:4554","Address to connect to ");
  opts.Check();

  cerr << "Starting server. \n";
  DataServerC dataServer(serverName);
  
  if(!dataServer.Open(serverAddr)) {
    cerr << "Failed to start server. \n";
    return 1;
  }
  
  cerr << "Server started ok. \n";
  
  dataServer.WaitForTerminate();
  
  cerr << "Server exiting. \n";
  
  return 0;
}
