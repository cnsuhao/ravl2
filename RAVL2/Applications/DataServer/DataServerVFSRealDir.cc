// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/DataServer/DataServerVFSRealDir.hh"
#include "Ravl/OS/NetPortManager.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/DP/CacheIStream.hh"

namespace RavlN {
  
  
  //: Constructor.
  
  DataServerVFSRealDirBodyC::DataServerVFSRealDirBodyC(const StringC &vname,const StringC &nRealDirname,bool canWrite)
    : DataServerVFSNodeBodyC(vname,canWrite,true),
      realDirname(nRealDirname)
  {
    cerr << "DataServerVFSRealDirBodyC::DataServerVFSRealDirBodyC, Called VName=" << vname << " \n";
  }
  
  //: Destructor.
  
  DataServerVFSRealDirBodyC::~DataServerVFSRealDirBodyC() {
    // Empty out handles with a lock. This will give any stray threads a chance to exit,
    // though there should be none running in the instance by the time this gets called.
    MutexLockC lock(access);
    name2file.Empty();
  }
  
  //: Configure node with given setup.
  
  bool DataServerVFSRealDirBodyC::Configure(const ConfigFileC &config) {
    
    // Lock server while we're setting up.
    // No other threads should be running here, but better safe than sorry.
    MutexLockC lock(access);
    
    // Configure basic attributes.
    DataServerVFSNodeBodyC::Configure(config);
    
    // Setup filename 
    realDirname = config["Filename"];
    
    return true;
  }
  
  //: Open VFS file.
  
  bool DataServerVFSRealDirBodyC::OpenVFSFile(DListC<StringC> &remainingPath,DataServerVFSRealFileC &rfile,bool forWrite) {
    StringC vfile = StringListC(remainingPath).Cat("/");
    if(vfile.IsEmpty()) {
      cerr << "DataServerVFSRealDirBodyC::OpenVFSFile, No filename remaining. VDir=" << name << "\n";
      return false;
    }
    FilenameC absFile = realDirname + "/" + vfile;
    MutexLockC lock(access);
    if(!name2file.Lookup(vfile,rfile)) {
      if(!absFile.Exists() && !forWrite) {
        cerr << "DataServerVFSRealDirBodyC::OpenIPort, Failed to open file '" << absFile << "' \n";
        return false;
      }
      rfile = DataServerVFSRealFileC(vfile,absFile,canWrite);
      name2file[vfile] = rfile;
    }
    lock.Unlock();
    return true;
  }
  
  //: Open input port.
  
  bool DataServerVFSRealDirBodyC::OpenIPort(DListC<StringC> &remainingPath,const StringC &dataType,NetISPortServerBaseC &port) {
    DataServerVFSRealFileC rfile;
    if(!OpenVFSFile(remainingPath,rfile,false))
      return false;
    DListC<StringC> emptyList;
    return rfile.OpenIPort(emptyList,dataType,port);  
  }
  
  //: Open output port.
  
  bool DataServerVFSRealDirBodyC::OpenOPort(DListC<StringC> &remainingPath,const StringC &dataType,NetOSPortServerBaseC &port) {
    // Check we can write to dir.
    if(!CanWrite())
      return false;
    
    // Setup output port.
    DataServerVFSRealFileC rfile;
    if(!OpenVFSFile(remainingPath,rfile,true))
      return false;
    DListC<StringC> emptyList;
    return rfile.OpenOPort(emptyList,dataType,port);  
  }
  

}
