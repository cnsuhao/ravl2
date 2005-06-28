// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "Ravl/DataServer/DataServerVFSRealFile.hh"
#include "Ravl/OS/NetPortManager.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/DP/CacheIStream.hh"

namespace RavlN {
  
  
  //: Constructor.
  
  DataServerVFSRealFileBodyC::DataServerVFSRealFileBodyC(const StringC &vname,const StringC &nRealFilename,bool canWrite)
    : DataServerVFSNodeBodyC(vname,canWrite,false),
      cacheSize(0),
      realFilename(nRealFilename),
      canSeek(true)
  {
    cerr << "DataServerVFSRealFileBodyC::DataServerVFSRealFileBodyC, Called VName=" << vname << " \n";
  }
  
  //: Destructor.
  
  DataServerVFSRealFileBodyC::~DataServerVFSRealFileBodyC() {
    CloseFile();
  }
  
  //: Configure node with given setup.
  
  bool DataServerVFSRealFileBodyC::Configure(const ConfigFileC &config) {
    // Configure basic attributes.
    DataServerVFSNodeBodyC::Configure(config);
    
    // Setup filename 
    realFilename = config["Filename"];
    
    // Setup cache.
    StringC cacheSizeStr = config["CacheSize"];
    if(!cacheSizeStr.IsEmpty())
      cacheSize = cacheSizeStr.UIntValue();
    else
      cacheSize = 0;
    
    return true;
  }
  
  //: Open input port.
  
  bool DataServerVFSRealFileBodyC::OpenIPort(DListC<StringC> &remainingPath,const StringC &dataType,NetISPortServerBaseC &port) {
    
    // Check the path is empty.
    if(!remainingPath.IsEmpty())
      return false;
    
    // Make sure file is open for reading.
    if(!OpenFileRead())
      return false;
    if(!iTypeInfo.IsValid()) {
      RavlAssert(0); // This should never happen, catch it in test mode.
      return false;
    }
    
    // Create a new shared port.
    DPISPortC<RCWrapAbstractC> rawIp = ispShare.Port(); 
    
    // Creat a converter to an apropriate type.
    DPIPortBaseC realPort = iTypeInfo.CreateConvFromAbstract(rawIp);
    RavlAssert(realPort.IsValid());
    
    // Create a net port server.
    port = NetISPortServerBaseC(AttributeCtrlC(realPort),
                                realPort,
                                rawIp,
                                name);
    
    return true;  
  }
  
  //: Open output port.
  
  bool DataServerVFSRealFileBodyC::OpenOPort(DListC<StringC> &remainingPath,const StringC &dataType,NetOSPortServerBaseC &port) {
    
    // Check the path is empty.
    if(!remainingPath.IsEmpty())
      return false;
    
    // Make sure file is open for writing.
    if(!OpenFileWrite())
      return false;
    
    // Still don't know what to do...
    
    return false;
  }
  
  //: Open file and setup cache.
  
  bool DataServerVFSRealFileBodyC::OpenFileRead() {
    if(ispShare.IsValid())
      return true;
    
    if(!iTypeInfo.IsValid()) {
      iTypeInfo = TypeInfo(RTypeInfo(defaultDataType));
      if(!iTypeInfo.IsValid()) {
        cerr << "DataServerVFSRealFileBodyC::OpenFileRead, type '" << defaultDataType << "' unknown. \n";
        return false; 
      }
    }
    
    DPIPortBaseC ip;
    DPSeekCtrlC sc;
    
    if(!OpenISequenceBase(ip,sc,name,"",iTypeInfo.TypeInfo(),verbose)) {
      cerr << "DataServerBodyC::HandleRequestIPort, Failed to open stream '" << name << "' of type '" << iTypeInfo.Name() << "' \n";
      return false;
    }
    
    // Setup raw input sport.
    DPISPortAttachC<RCWrapAbstractC> isport(ip,sc);
    
    // Setup inline cache ?
    if(cacheSize > 0) 
      isport = CacheIStreamC<RCWrapAbstractC>(isport,cacheSize);
    
    // Setup port share.
    ispShare = DPISPortShareC<RCWrapAbstractC>(isport);
    
    return true;
  }

  //: Open file and setup cache.
  
  bool DataServerVFSRealFileBodyC::OpenFileWrite() {
    
    return false;
  }
  
  //: Close file and discard cache.
  
  bool DataServerVFSRealFileBodyC::CloseFile() {
    
    return false;
  }

}
