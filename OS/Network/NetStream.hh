// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_NETSTREAM_HEADER
#define RAVL_NETSTREAM_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlNet
//! author="Charles Galambos"
//! docentry="Ravl.OS.Network"
//! file="Ravl/OS/Network/NetStream.hh"
//! date="15/02/2000"

#include "Ravl/Stream.hh"
#include "Ravl/OS/Socket.hh"

namespace RavlN {
  ////////////////////////////
  //! userlevel=Normal
  //: Output stream to memory.
  // Wraps the standard library ostrstream class.
  
  class NetOStreamC 
    : public OStreamC
  {
  public:
    NetOStreamC()
      {}
    //: Default constructor.
    
    NetOStreamC(const StringC &filename,bool buffered=true,bool server = false);
    //: Open net connection for output.
    
    NetOStreamC(const SocketC &nsock,bool buffered=true);
    //: Use a socket to build new handle.
    
    SocketC &Socket() 
      { return sock; }
    //: Access socket.
    
  protected:
    SocketC sock;
  };
  
  ////////////////////////////
  //! userlevel=Normal
  //: Input stream from memory.
  // Wraps the standard library istrstream class.
  
  class NetIStreamC 
    : public IStreamC
  {
  public:
    NetIStreamC()
      {}
    //: Default constructor
    
    NetIStreamC(const StringC &filename,bool buffered=true,bool server = false);
    //: Open net connection for input
    
    NetIStreamC(const SocketC &nsock,bool buffered=true);
    //: Use a socket to build new handle.
    
    bool WaitForData(RealT timeout = -1);
    //: Wait for data to arrive.
    // Returns true if data is available, on a timeout or other interupt
    // false is returned.
    
    SocketC &Socket() 
      { return sock; }
    //: Access socket.
    
  protected:
    SocketC sock;
  };
  
}


#endif
