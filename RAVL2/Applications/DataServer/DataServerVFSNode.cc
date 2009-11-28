// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/DataServer/DataServerVFSNode.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Constructor.
  
  DataServerVFSNodeBodyC::DataServerVFSNodeBodyC(const StringC &nname,const StringC& npath,bool ncanWrite,bool isDir)
    : name(nname),
      path(npath),
      isDirectory(isDir),
      canWrite(ncanWrite),
      verbose(false)
  {
    ONDEBUG(cerr << "DataServerVFSNodeBodyC::DataServerVFSNodeBodyC, Called name=" << name << " path=" << path << " isDir=" << isDir <<"\n");
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



  const StringC DataServerVFSNodeBodyC::AbsoluteName()
  {
    StringC absoluteName = path;
    if (!absoluteName.IsEmpty())
      absoluteName += "/";
    absoluteName += name;
    return absoluteName;
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



  bool DataServerVFSNodeBodyC::Delete()
  {
    DListC<StringC> emptyPath;
    return Delete(emptyPath);
  }



  bool DataServerVFSNodeBodyC::Delete(const DListC<StringC>& remainingPath)
  {
    cerr << "DataServerVFSNodeBodyC::Delete not supported on '" << name << "' for '" << StringListC(remainingPath).Cat("/") << "'" << endl;
    return false;
  }
  


  bool DataServerVFSNodeBodyC::QueryNodeSpace(const StringC& remainingPath, Int64T& total, Int64T& used, Int64T& available)
  {
    cerr << "DataServerVFSNodeBodyC::QueryNodeSpace not supported on '" << name << "' for '" << StringListC(remainingPath).Cat("/") << "'" << endl;
    return false;
  }

}
