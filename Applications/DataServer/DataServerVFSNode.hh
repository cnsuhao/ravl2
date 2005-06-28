// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DATASERVERVFSNODE_HEADER
#define RAVL_DATASERVERVFSNODE_HEADER 1
//! rcsid="$Id$"

#include "Ravl/String.hh"
#include "Ravl/RCHandleV.hh"
#include "Ravl/DList.hh"
#include "Ravl/Text/ConfigFile.hh"

namespace RavlN {
  
  class NetOSPortServerBaseC;
  class NetISPortServerBaseC;
  
  //! userlevel=Develop
  //: Virtual File System node for DataServerC.
  
  class DataServerVFSNodeBodyC 
    : public RCBodyVC
  {
  public:
    DataServerVFSNodeBodyC(const StringC &nname,bool ncanWrite,bool isDir);
    //: Constructor.
    
    virtual bool Configure(const ConfigFileC &config);
    //: Configure node with given setup.
    
    const StringC &Name() const
    { return name; }
    //: Get name of node.
    
    virtual bool CanWrite() const
    { return canWrite; }
    //: Can write.
    
    virtual void SetWrite(bool v)
    { canWrite = v; }
    //: Set writable flag.
    
    virtual bool IsDirectory() const
    { return isDirectory; }
    //: Is this a directory ?
    
    virtual bool OpenIPort(DListC<StringC> &remainingPath,const StringC &dataType,NetISPortServerBaseC &port);
    //: Open input port.
    
    virtual bool OpenOPort(DListC<StringC> &remainingPath,const StringC &dataType,NetOSPortServerBaseC &port);
    //: Open output port.
    
  protected:
    StringC name;
    bool isDirectory; // Is this a directory.
    bool canWrite;    // Write permission enabled ?
    bool verbose;
  };
  
  //! userlevel=Normal
  //: Virtual File System node for DataServerC. 
  //!cwiz:author
  
  class DataServerVFSNodeC
    : public RCHandleC<DataServerVFSNodeBodyC>
  {
  public:
    DataServerVFSNodeC(const StringC & nname,bool ncanWrite,bool isDir) 
      : RCHandleC<DataServerVFSNodeBodyC>(*new DataServerVFSNodeBodyC(nname,ncanWrite,isDir))
    {}
    //: Constructor. 
    //!cwiz:author
    
    DataServerVFSNodeC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    bool Configure(const ConfigFileC &config)
    { return Body().Configure(config); }
    //: Configure node with given setup.
    
    const StringC & Name() const
    { return Body().Name(); }
    //: Get name of node. 
    //!cwiz:author
    
    bool CanWrite() const
    { return Body().CanWrite(); }
    //: Can write. 
    //!cwiz:author
    
    void SetWrite(bool v) 
    { Body().SetWrite(v); }
    //: Set writable flag. 
    //!cwiz:author
    
    bool IsDirectory() const
    { return Body().IsDirectory(); }
    //: Is this a directory ? 
    //!cwiz:author

    bool OpenIPort(DListC<StringC> &remainingPath,const StringC &dataType,NetISPortServerBaseC &port)
    { return Body().OpenIPort(remainingPath,dataType,port); }
    //: Open input port.
    
    bool OpenOPort(DListC<StringC> &remainingPath,const StringC &dataType,NetOSPortServerBaseC &port)
    { return Body().OpenOPort(remainingPath,dataType,port); }
    //: Open output port.
    
  protected:
    DataServerVFSNodeC(DataServerVFSNodeBodyC &bod)
     : RCHandleC<DataServerVFSNodeBodyC>(bod)
    {}
    //: Body constructor. 
    
    DataServerVFSNodeBodyC& Body()
    { return static_cast<DataServerVFSNodeBodyC &>(RCHandleC<DataServerVFSNodeBodyC>::Body()); }
    //: Body Access. 
    
    const DataServerVFSNodeBodyC& Body() const
    { return static_cast<const DataServerVFSNodeBodyC &>(RCHandleC<DataServerVFSNodeBodyC>::Body()); }
    //: Body Access. 
    
  };
  

}

#endif
