// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DATASERVERVFSREALDIR_HEADER
#define RAVL_DATASERVERVFSREALDIR_HEADER 1
//! rcsid="$Id$"

#include "Ravl/DataServer/DataServerVFSNode.hh"
#include "Ravl/DataServer/DataServerVFSRealFile.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/DP/TypeInfo.hh"
#include "Ravl/DP/SPortShare.hh"
#include "Ravl/RCWrap.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Handle file's or directories in a real filesystem.
  
  class DataServerVFSRealDirBodyC
    : public DataServerVFSNodeBodyC
  {
  public:
    DataServerVFSRealDirBodyC(const StringC &vname,const StringC &nRealDirname,bool canWrite);
    //: Constructor.
    
    ~DataServerVFSRealDirBodyC();
    //: Destructor.
    
    virtual bool Configure(const ConfigFileC &config);
    //: Configure node with given setup.
    
    const FilenameC &RealDirname() const
    { return realDirname; }
    //: Real filename.
    
    virtual bool OpenIPort(DListC<StringC> &remainingPath,const StringC &dataType,NetISPortServerBaseC &port);
    //: Open input port.
    
    virtual bool OpenOPort(DListC<StringC> &remainingPath,const StringC &dataType,NetOSPortServerBaseC &port);
    //: Open output port.
    
  protected:
    bool OpenVFSFile(DListC<StringC> &remainingPath,DataServerVFSRealFileC &rfile,bool forWrite = false);
    //: Open VFS file.
    
    MutexC access; // Access control for object.
    HashC<StringC,DataServerVFSRealFileC> name2file;
    
    FilenameC realDirname;
  };
  
  //! userlevel=Normal
  //: Handle file's or directories in a real filesystem. 
  //!cwiz:author
  
  class DataServerVFSRealDirC
    : public DataServerVFSNodeC
  {
  public:
    DataServerVFSRealDirC(const StringC & vname,const StringC & nRealDirname,bool canWrite = false) 
      : DataServerVFSNodeC(*new DataServerVFSRealDirBodyC(vname,nRealDirname,canWrite))
    {}
    //: Constructor. 
    //!cwiz:author
    
    const FilenameC & RealDirname() const
    { return Body().RealDirname(); }
    //: Real filename. 
    //!cwiz:author
    
  protected:
    DataServerVFSRealDirC(DataServerVFSRealDirBodyC &bod)
     : DataServerVFSNodeC(bod)
    {}
    //: Body constructor. 
    
    DataServerVFSRealDirBodyC& Body()
    { return static_cast<DataServerVFSRealDirBodyC &>(DataServerVFSNodeC::Body()); }
    //: Body Access. 
    
    const DataServerVFSRealDirBodyC& Body() const
    { return static_cast<const DataServerVFSRealDirBodyC &>(DataServerVFSNodeC::Body()); }
    //: Body Access. 
    
  };
}


#endif
