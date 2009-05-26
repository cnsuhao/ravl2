// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_VIDEOSERVER_HEADER
#define RAVL_VIDEOSERVER_HEADER 1
//! rcsid="$Id$"

#include "Ravl/OS/NetPortManager.hh"
#include "Ravl/Threads/Mutex.hh"
#include "Ravl/HashTree.hh"
#include "Ravl/DataServer/DataServerVFSNode.hh"

namespace RavlN {

  class DataServerC;
  
  //! userlevel=Develop
  //: Data server body class.
  
  class DataServerBodyC
    : public NetPortManagerBodyC
  {
  public:
    DataServerBodyC(const StringC &name);
    //: Constructor.
    
    bool Open(const StringC &addr);
    //: Open server connection.
    
    bool ReadConfigFile(const StringC &filename);
    //: Read a new config file.
    // Build Virtual File System appropriatly.
    
  protected:
    bool HandleRequestIPort(StringC name,StringC dataType,NetISPortServerBaseC &port);
    //: Handle a request for an input port.
    
    bool HandleRequestOPort(StringC name,StringC dataType,NetOSPortServerBaseC &port);
    //: Handle a request for an output port.
    
    bool FindVFSNode(const StringC &vfilename,HashTreeNodeC<StringC,DataServerVFSNodeC> &vfsn,DListC<StringC> &remainingPath);
    //: Find a virtual file system node.
    // This breaks the filename into strings seperated by '/', it follows the path as far as possible
    // throught the virtual filesystem. If any strings remain in the path they are stored in 'remainingPath'.
    //!param:vfilename - Full virtual filename.
    //!param:vfsn - Virtual file system node.
    //!param:remainingPath - Remainder of path after last node has been found.
    // Returns true if node found successfully, false if the path corresponds to no known entry in the filesystem.
    
    MutexC access;    
    HashTreeC<StringC,DataServerVFSNodeC> vfs; // Virtual file system.
    
    bool verbose;
    friend class DataServerC;
  };
  
  //! userlevel=Normal
  //: Data server class.
  //!cwiz:author
  
  class DataServerC
    : public NetPortManagerC
  {
  public:
    DataServerC(const StringC & name) 
      : NetPortManagerC(*new DataServerBodyC(name))
    {}
    //: Constructor. 
    //!cwiz:author
    
    bool Open(const StringC & addr) 
    { return Body().Open(addr); }
    //: Open server connection. 
    //!cwiz:author
    
    bool ReadConfigFile(const StringC &filename)
    { return Body().ReadConfigFile(filename); }
    //: Read a new config file.
    // Build Virtual File System appropriatly.
    
  protected:
    DataServerC(DataServerBodyC &bod)
     : NetPortManagerC(bod)
    {}
    //: Body constructor. 
    
    DataServerBodyC& Body()
    { return static_cast<DataServerBodyC &>(NetPortManagerC::Body()); }
    //: Body Access. 
    
    const DataServerBodyC& Body() const
    { return static_cast<const DataServerBodyC &>(NetPortManagerC::Body()); }
    //: Body Access. 
    
    friend class DataServerBodyC;
  };
}


#endif
