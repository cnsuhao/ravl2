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
#include "Ravl/DP/SerialisePort.hh"
#include "Ravl/DP/TypeConverter.hh"
#include "Ravl/DP/FileFormatDesc.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  
  //: Constructor.
  
  DataServerVFSRealFileBodyC::DataServerVFSRealFileBodyC(const StringC &vname,const StringC &nRealFilename,bool canWrite)
    : DataServerVFSNodeBodyC(vname,canWrite,false),
      cacheSize(0),
      realFilename(nRealFilename),
      canSeek(true),
      multiWrite(false)
  {
    ONDEBUG(cerr << "DataServerVFSRealFileBodyC::DataServerVFSRealFileBodyC, Called VName=" << vname << " \n");
  }
  
  //: Destructor.
  
  DataServerVFSRealFileBodyC::~DataServerVFSRealFileBodyC() {
    CloseIFile();
    CloseOFile();
  }
  
  //: Configure node with given setup.
  
  bool DataServerVFSRealFileBodyC::Configure(const ConfigFileC &config) {
    
    // Lock server while we're setting up.
    // No other threads should be running here, but better safe than sorry.
    MutexLockC lock(access);
    
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
    
    // Setup multiwrite.
    StringC multiWriteStr = config["MultiWrite"];
    if(multiWriteStr == "1")
      multiWrite = true;
    else
      multiWrite = false;
    
    return true;
  }
  
  //: Open input port.
  
  bool DataServerVFSRealFileBodyC::OpenIPort(DListC<StringC> &remainingPath,const StringC &dataType,NetISPortServerBaseC &port) {
    
    // Check the path is empty.
    
    if(!remainingPath.IsEmpty()) {
      cerr << "DataServerVFSRealFileBodyC::OpenIPort, ERROR: Path remaining after a valid filename. \n";
      return false;
    }
    
    // Make sure file is open for reading.
    // Lock access to port share while we creat a client
    MutexLockC lock(access);
    while(!ispShare.IsValid()) {
      // Unlock while we open.
      lock.Unlock();
      if(!OpenFileRead(dataType))
        return false;
      // Relock access.
      lock.Lock();
    }
    
    // Obtain client
    DPISPortC<RCWrapAbstractC> rawIp = ispShare.Port(); 
    
    // Unlock access.
    lock.Unlock();
    
    if(!iTypeInfo.IsValid()) {
      RavlAssert(0); // This should never happen, catch it in test mode.
      return false;
    }
    
    // Creat a converter to an apropriate type.
    DPIPortBaseC realPort = iTypeInfo.CreateConvFromAbstract(rawIp);
    RavlAssert(realPort.IsValid());

    // Need to do any type conversion ?
    
    if(dataType != TypeName(iTypeInfo.TypeInfo())) {
      ONDEBUG(cerr << "DataServerVFSRealFileBodyC::OpenIPort, Building type converter. \n");
      DListC<DPConverterBaseC> convSeq = SystemTypeConverter().FindConversion(realPort.InputType(),RTypeInfo(dataType));
      if(convSeq.IsEmpty()) {
        cerr << "DataServerVFSRealFileBodyC::OpenOPort, Failed to find type conversion. \n";
        return false;
      }
      realPort = FileFormatDescC(convSeq,true).BuildInputConv(realPort);
    }
    
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
    if(!remainingPath.IsEmpty()) {
      cerr << "DataServerVFSRealFileBodyC::OpenOPort, ERROR: Path remaining after a valid filename. \n";
      return false;
    }
    
    // Make sure file is open for writing.
    
    if(!OpenFileWrite(dataType))
      return false;
    
    MutexLockC lock(access);
    if(oport.References() > 1 && !multiWrite) {
      cerr << "DataServerVFSRealFileBodyC::OpenOPort, Port already open for writing. \n";
      return false;
    }
    
    // Still don't know what to do...
    DPOPortBaseC realPort = oTypeInfo.CreateConvFromAbstract(oport);

    // Need to do any type conversion ?
    
    if(dataType != TypeName(oTypeInfo.TypeInfo())) {
      ONDEBUG(cerr << "DataServerVFSRealFileBodyC::OpenOPort, Building type converter. \n");
      DListC<DPConverterBaseC> convSeq = SystemTypeConverter().FindConversion(RTypeInfo(dataType),realPort.OutputType());
      if(convSeq.IsEmpty()) {
        cerr << "DataServerVFSRealFileBodyC::OpenOPort, Failed to find type conversion. \n";
        return false;
      }
      realPort = FileFormatDescC(convSeq,false).BuildOutputConv(realPort);
    }
    
    // Setup client specific part of server to handle connection
    
    port = NetOSPortServerBaseC(AttributeCtrlC(realPort),
                                realPort,
                                DPSeekCtrlC(realPort),
                                name);
    
    DataServerVFSRealFileC me(*this);
    Connect(port.SigConnectionClosed(),me,&DataServerVFSRealFileC::DisconnectOPortClient);
    
    return true;
  }
  
  //: Open file and setup cache.
  
  bool DataServerVFSRealFileBodyC::OpenFileRead(const StringC &typePref) {
    MutexLockC lock(access);
    
    if(ispShare.IsValid()) {
      cerr << "DataServerVFSRealFileBodyC::OpenFileRead, File already open. \n";
      return true;
    }
    
    // Sort out default type.
    if(!iTypeInfo.IsValid()) {
      StringC useType;
      if(!defaultDataType.IsEmpty())
        useType = defaultDataType;
      else
        useType = typePref;
      iTypeInfo = TypeInfo(RTypeInfo(useType));
      if(!iTypeInfo.IsValid()) {
        cerr << "DataServerVFSRealFileBodyC::OpenFileRead, type '" << useType << "' unknown. \n";
        return false; 
      }
    }
    
    // Open native sequence.
    DPIPortBaseC ip;
    DPSeekCtrlC sc;
    if(!OpenISequenceBase(ip,sc,realFilename,"",iTypeInfo.TypeInfo(),verbose)) {
      cerr << "DataServerBodyC::HandleRequestIPort, Failed to open stream '" << name << "' of type '" << iTypeInfo.Name() << "' \n";
      return false;
    }
    
    // Convert into an abstact stream.
    DPIPortC<RCWrapAbstractC> aip = iTypeInfo.CreateConvToAbstract(ip);
    
    // Setup raw input sport.
    DPISPortAttachC<RCWrapAbstractC> isport(aip,sc);
    
    // Setup inline cache ?
    if(cacheSize > 0) 
      isport = CacheIStreamC<RCWrapAbstractC>(isport,cacheSize);
    
    // Setup port share.
    ispShare = DPISPortShareC<RCWrapAbstractC>(isport);
    
    // Set trigger to let us know when people stop using this file.
    ispShare.TriggerCountZero() = TriggerR(*this,&DataServerVFSRealFileBodyC::ZeroIPortClients);
    
    return true;
  }

  //: Open file and setup cache.
  
  bool DataServerVFSRealFileBodyC::OpenFileWrite(const StringC &typePref) {
    ONDEBUG(cerr << "DataServerVFSRealFileBodyC::OpenFileWrite, Called. \n");
    MutexLockC lock(access);
    // If file already open ?
    if(oport.IsValid())
      return true;

    // Sort out default type.
    if(!oTypeInfo.IsValid()) {
      StringC useType;
      if(!defaultDataType.IsEmpty())
        useType = defaultDataType;
      else
        useType = typePref;
      oTypeInfo = TypeInfo(RTypeInfo(useType));
      if(!oTypeInfo.IsValid()) {
        cerr << "DataServerVFSRealFileBodyC::OpenFileWrite, type '" << useType << "' unknown. \n";
        return false; 
      }
    }
    
    DPOPortBaseC op;
    DPSeekCtrlC sc;
    if(!OpenOSequenceBase(op,sc,realFilename,"",oTypeInfo.TypeInfo(),verbose)) {
      cerr << "DataServerVFSRealFileBodyC::OpenFileWrite, Failed to open stream '" << realFilename << "' of type '" << typePref << "' \n";
      return false;
    }
    RavlAssert(op.IsValid());
    DPOPortC<RCWrapAbstractC> aop = DPOSPortAttachC<RCWrapAbstractC>(oTypeInfo.CreateConvToAbstract(op),sc);
    
    if(multiWrite) // Do we need to seralise writes ?
      aop = DPOSerialisePortC<RCWrapAbstractC>(aop);
    
    oport = aop;
    return true;
  }
  
  //: Close file and discard cache.
  
  bool DataServerVFSRealFileBodyC::CloseIFile() {
    MutexLockC lock(access);
    ispShare.Invalidate();
    return true;
  }

  //: Close output file 
  
  bool DataServerVFSRealFileBodyC::CloseOFile() {
    MutexLockC lock(access);
    oport.Invalidate();
    return true;
  }
  
  //: Called if when output file client disconnect it.
  
  bool DataServerVFSRealFileBodyC::DisconnectOPortClient() {
    cerr << "DataServerVFSRealFileBodyC::DisconnectOPortClient(), Called. Ref=" << oport.References() << "\n";
    MutexLockC lock(access);
    if(oport.References() == 1) { // Are all clients gone ?
      cerr << "DataServerVFSRealFileBodyC::DisconnectOPortClient(), Dropping output port. \n";
      oport.Invalidate();
    }
    return true;
  }

  //: Called if when file stop's being used.
  
  bool DataServerVFSRealFileBodyC::ZeroIPortClients() {
    ONDEBUG(cerr << "DataServerVFSRealFileBodyC::ZeroIPortClients, Called \n");
    CloseIFile();
    return true;
  }

}
