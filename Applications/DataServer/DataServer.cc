// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/DataServer/DataServer.hh"
#include "Ravl/CallMethods.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/StringList.hh"
#include "Ravl/BlkQueue.hh"
#include "Ravl/Tuple2.hh"

#include "Ravl/DataServer/DataServerVFSRealFile.hh"
#include "Ravl/DataServer/DataServerVFSRealDir.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Constructor.
  
  DataServerBodyC::DataServerBodyC(const StringC &name)
    : NetPortManagerBodyC(name,true),
      vfs(true),
      verbose(false)
  {
    // Setup root VFS node.
    vfs.Data() = DataServerVFSNodeC("root",false,true);
  }
  
  //: Open server connection.
  
  bool DataServerBodyC::Open(const StringC &addr) {
    StringC empty;
    
    RegisterIPortRequestManager(TriggerR(*this,&DataServerBodyC::HandleRequestIPort,empty,empty,NetISPortServerBaseC()));
    RegisterOPortRequestManager(TriggerR(*this,&DataServerBodyC::HandleRequestOPort,empty,empty,NetOSPortServerBaseC()));
    
    return NetPortManagerBodyC::Open(addr);
  }
  
  //: Read a new config file.
  // Build Virtual File System appropriatly.
  
  bool DataServerBodyC::ReadConfigFile(const StringC &filename) {
    ConfigFileC cfg(filename);
    
    //: Configure the root node.
      
    BlkQueueC<Tuple2C<ConfigFileC,HashTreeC<StringC,DataServerVFSNodeC> > > toDo;
    ConfigFileC rootSection = cfg.Section("VFS");
    RavlAssert(vfs.IsValid());
    if(rootSection.IsValid())
      toDo.InsLast(Tuple2C<ConfigFileC,HashTreeC<StringC,DataServerVFSNodeC> >(rootSection,vfs));
    
    while(!toDo.IsEmpty()) {
      // Get next thing.
      Tuple2C<ConfigFileC,HashTreeC<StringC,DataServerVFSNodeC> > at = toDo.GetFirst();
      
      // Configure it.
      RavlAssert(at.Data2().Data().IsValid());
      at.Data2().Data().Configure(at.Data1());
      
      // Any children ?
      
      DListC<StringC> children = at.Data1().ListSections();
      if(!at.Data2().Data().IsDirectory() && !children.IsEmpty()) {
        cerr << "DataServerBodyC::ReadConfigFile, WARNING: SubSection's in non directory object '" << at.Data1().Name() << "' \n";
        continue;
      }
      
      for(DLIterC<StringC> it(children);it;it++) {
        ConfigFileC subSection = at.Data1().Section(*it);
        
        // What kind of node is wanted ?
        StringC nodeType = subSection["NodeType"];
        DataServerVFSNodeC node;
        if(nodeType == "" || nodeType == "VDir") { // Virtual directory ?
          node = DataServerVFSNodeC(subSection.Name(),false,true);
        } else if(nodeType == "RealFile") {        // Real file ?
          node = DataServerVFSRealFileC(*it,subSection.Name());
        } else if(nodeType == "RealDir") {
          node = DataServerVFSRealDirC(*it,subSection.Name());
        } else { // Something strange.
          cerr << "DataServerBodyC::ReadConfigFile, WARNING: Unknown node type '" << nodeType << "' in file '" << filename << "'\n";
          continue;
        }
        
        // Add new node into tree.
        RavlAssert(node.IsValid());
        if(!at.Data2().Add(*it,node)) {
          cerr << "DataServerBodyC::ReadConfigFile, WARNING: Duplicate node entry '" << *it << "' in file '" << filename << "'\n";
          continue;
        }
        
        // Retrieve new node entry.
        HashTreeC<StringC,DataServerVFSNodeC>  entry;
        at.Data2().Child(*it,entry);
        RavlAssert(entry.IsValid());
        
        // Put it on the todo list.
        toDo.InsLast(Tuple2C<ConfigFileC,HashTreeC<StringC,DataServerVFSNodeC> >(subSection,entry));
      }
    }

    StringC hostAddr = cfg["Host"];
    if(hostAddr.IsEmpty()) {
      cerr << "DataServerBodyC::ReadConfigFile, Not host address given. ";
      return false;
    }
    
    return Open(hostAddr);
  }
  
  //: Find a virtual file system node.
  // Returns true if node found successfully.
  
  bool DataServerBodyC::FindVFSNode(const StringC &vfilename,HashTreeNodeC<StringC,DataServerVFSNodeC> &vfsn,DListC<StringC> &remainingPath) {
    StringListC path(vfilename,"/");
    HashTreeNodeC<StringC,DataServerVFSNodeC> at = vfs;
    DLIterC<StringC> it(path);
    for(;it && !at.IsLeaf();it++) {
      // Is this a node in the tree with children ?
      HashTreeC<StringC,DataServerVFSNodeC> ht(at);
      RavlAssert(ht.IsValid()); // No children.
      if(!ht.Child(*it,at))
        break; // Child not found.
    }
    
    // There can only be a remainer in the path if the last node in the tree is not a directory.
    if(!at.Data().IsDirectory() && it)
      return false;
    
    // Retrieve node of interest.
    vfsn = at;
    
    // Sort out any unused path items.
    if(it)
      remainingPath = it.InclusiveTail();
    else
      remainingPath.Empty();
    ONDEBUG(cerr << "DataServerBodyC::FindVFSNode, '" << vfilename << "' -> '" << vfsn.Data().Name() << "' PathSize=" << remainingPath.Size() << "\n");
    return true;
  }
  

  //: Handle a request for an input port.
  
  bool DataServerBodyC::HandleRequestIPort(StringC name,StringC dataType,NetISPortServerBaseC &port) {
    ONDEBUG(cerr << "DataServerBodyC::HandleRequestIPort, Name=" << name << " Type=" << dataType << "\n");
    
    HashTreeNodeC<StringC,DataServerVFSNodeC> vfsn;
    DListC<StringC> remainingPath;
    if(!FindVFSNode(name,vfsn,remainingPath)) {
      cerr << "DataServerBodyC::HandleRequestIPort, Failed to find VFSNode for '" << name << "'\n";
      return false;
    }
    RavlAssert(vfsn.IsValid());
    if(!vfsn.Data().OpenIPort(remainingPath,dataType,port)) {
      cerr << "DataServerBodyC::HandleRequestIPort, Failed to open file '" << name << "'\n";
      return false;
    }
    return true;
  }
  
  //: Handle a request for an output port.
  
  bool DataServerBodyC::HandleRequestOPort(StringC name,StringC dataType,NetOSPortServerBaseC &port) {
    ONDEBUG(cerr << "DataServerBodyC::HandleRequestOPort, Name=" << name << " Type=" << dataType << "\n");
    
    HashTreeNodeC<StringC,DataServerVFSNodeC> vfsn;
    DListC<StringC> remainingPath;
    if(!FindVFSNode(name,vfsn,remainingPath)) 
      return false;
    RavlAssert(vfsn.IsValid());
    return vfsn.Data().OpenOPort(remainingPath,dataType,port);
  }
  
}
