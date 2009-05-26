// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/DataServer/DataServerVFSNode.hh"

namespace RavlN {

  //: Constructor.
  
  DataServerVFSNodeBodyC::DataServerVFSNodeBodyC(const StringC &nname,bool ncanWrite,bool isDir)
    : name(nname),
      isDirectory(isDir),
      canWrite(ncanWrite),
      verbose(false)
  {
    cerr << "DataServerVFSNodeBodyC::DataServerVFSNodeBodyC, Called VName=" << nname << " Dir=" << isDir <<"\n";
  }
  
  //: Configure node with given setup.
  
  bool DataServerVFSNodeBodyC::Configure(const ConfigFileC &config) {
    
    // Sort out write flag.
    StringC canWriteStr = config["CanWrite"];
    if(canWriteStr.IsEmpty() || canWriteStr == "1") canWrite = true;
    else canWrite = false;
    
    // Setup verbose flag.
    StringC verboseStr = config["Verbose"];
    if(verboseStr.IsEmpty() || verboseStr == "1") verbose = true;
    else verbose = false;
    
    return true;
  }

  //: Open input port.
  
  bool DataServerVFSNodeBodyC::OpenIPort(DListC<StringC> &remainingPath,const StringC &dataType,NetISPortServerBaseC &port) {
    cerr << "DataServerVFSNodeBodyC::OpenIPort, Not supported on '" << name << "' \n";
    return false;
  }
    
  //: Open output port.
  
  bool DataServerVFSNodeBodyC::OpenOPort(DListC<StringC> &remainingPath,const StringC &dataType,NetOSPortServerBaseC &port) {
    cerr << "DataServerVFSNodeBodyC::OpenIPort, Not supported on '" << name << "' \n";
    return false;
  }

  
}
