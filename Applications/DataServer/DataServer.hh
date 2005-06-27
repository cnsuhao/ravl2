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
    
  protected:
    bool HandleRequestIPort(StringC name,StringC dataType,NetISPortServerBaseC &port);
    //: Handle a request for an input port.
    
    bool HandleRequestOPort(StringC name,StringC dataType,NetOSPortServerBaseC &port);
    //: Handle a request for an output port.
    
    
    MutexC access;
    
    HashC<Tuple2C<StringC,StringC>,DPIPortBaseC> iStreamCache; // Input stream cache.
    HashC<Tuple2C<StringC,StringC>,DPOPortBaseC> oStreamCache; // Output stream cache.

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
