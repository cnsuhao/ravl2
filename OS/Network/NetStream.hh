// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLNETSTREAM_HEADER
#define RAVLNETSTREAM_HEADER 1
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
  
  class ONetStreamC 
    : public OStreamC
  {
  public:
    ONetStreamC()
      {}
    //: Default constructor.
    
    ONetStreamC(const StringC &filename,bool buffered=true,bool server = false);
    //: Open net connection for output.
    
    ONetStreamC(const SocketC &nsock,bool buffered=true);
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
  
  class INetStreamC 
    : public IStreamC
  {
  public:
    INetStreamC()
      {}
    //: Default constructor
    
    INetStreamC(const StringC &filename,bool buffered=true,bool server = false);
    //: Open net connection for input
    
    INetStreamC(const SocketC &nsock,bool buffered=true);
    //: Use a socket to build new handle.
    
    SocketC &Socket() 
      { return sock; }
    //: Access socket.
    
  protected:
    SocketC sock;
  };
  
}


#endif
