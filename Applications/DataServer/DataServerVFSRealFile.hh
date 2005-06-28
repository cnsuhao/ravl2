// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DATASERVERVFSREALFILE_HEADER
#define RAVL_DATASERVERVFSREALFILE_HEADER 1
//! rcsid="$Id$"

#include "Ravl/DataServer/DataServerVFSNode.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/DP/TypeInfo.hh"
#include "Ravl/DP/SPortShare.hh"
#include "Ravl/RCWrap.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Handle file's or directories in a real filesystem.
  
  class DataServerVFSRealFileBodyC
    : public DataServerVFSNodeBodyC
  {
  public:
    DataServerVFSRealFileBodyC(const StringC &vname,const StringC &nRealFilename,bool canWrite);
    //: Constructor.
    
    ~DataServerVFSRealFileBodyC();
    //: Destructor.
    
    virtual bool Configure(const ConfigFileC &config);
    //: Configure node with given setup.

    const FilenameC &RealFilename() const
    { return realFilename; }
    //: Real filename.
    
    void SetDefaultType(const StringC &typeName)
    { defaultDataType = typeName; }
    //: Set default type name.
    
    void SetCacheSize(UIntT size)
    { cacheSize = size; }
    //: Set cache size in number of items to cache.
    
    bool CanSeek() const
    { return canSeek; }
    //: Is stream seekable ?
    
    virtual bool OpenIPort(DListC<StringC> &remainingPath,const StringC &dataType,NetISPortServerBaseC &port);
    //: Open input port.
    
    virtual bool OpenOPort(DListC<StringC> &remainingPath,const StringC &dataType,NetOSPortServerBaseC &port);
    //: Open output port.
    
  protected:
    bool OpenFileRead();
    //: Open file and setup cache for reading.
    
    bool OpenFileWrite();
    //: Open file and setup cache for writing.
    
    bool CloseFile();
    //: Close file and discard cache.
    
    StringC defaultDataType;

    DPTypeInfoC iTypeInfo; // Type infor for input stream.
    DPISPortShareC<RCWrapAbstractC> ispShare; // Share for input port.
    
    UIntT cacheSize; // Size of cache to use.
    
    FilenameC realFilename;
    bool canSeek;
  };
  
  //! userlevel=Normal
  //: Handle file's or directories in a real filesystem. 
  //!cwiz:author
  
  class DataServerVFSRealFileC
    : public DataServerVFSNodeC
  {
  public:
    DataServerVFSRealFileC(const StringC & vname,const StringC & nRealFilename,bool canWrite = false) 
      : DataServerVFSNodeC(*new DataServerVFSRealFileBodyC(vname,nRealFilename,canWrite))
    {}
    //: Constructor. 
    //!cwiz:author
    
    const FilenameC & RealFilename() const
    { return Body().RealFilename(); }
    //: Real filename. 
    //!cwiz:author
    
    void SetDefaultType(const StringC &typeName)
    { return Body().SetDefaultType(typeName); }
    //: Set default type to be used on node.
    
  protected:
    DataServerVFSRealFileC(DataServerVFSRealFileBodyC &bod)
     : DataServerVFSNodeC(bod)
    {}
    //: Body constructor. 
    
    DataServerVFSRealFileBodyC& Body()
    { return static_cast<DataServerVFSRealFileBodyC &>(DataServerVFSNodeC::Body()); }
    //: Body Access. 
    
    const DataServerVFSRealFileBodyC& Body() const
    { return static_cast<const DataServerVFSRealFileBodyC &>(DataServerVFSNodeC::Body()); }
    //: Body Access. 
    
  };
}


#endif
