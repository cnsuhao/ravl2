// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLNETSOCKET_HEADER
#define RAVLNETSOCKET_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/OS/Network/Socket.hh"
//! lib=RavlOS
//! author="Charles Galambos"
//! example=exSocket.cc
//! date="15/02/2000"
//! docentry="Ravl.OS.Network"

#include "Ravl/String.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/OS/SktError.hh"

// Some forward declarations to avoid including extra header
// files.

struct sockaddr_in;
struct sockaddr;

namespace RavlN {

  class SocketC;

  //! userlevel=Develop
  //: Socket connection body class.
  // For dealing with stream sockets.
  
  class SocketBodyC 
    : public RCBodyC
  {
  public:
    SocketBodyC(StringC name,bool server = false);
    //: Open socket.
    
    SocketBodyC(StringC name,UIntT portno,bool server = false);
    //: Open socket.
    
    SocketBodyC(struct sockaddr *addr,int nfd,bool server = false);
    //: Open socket.
    
    ~SocketBodyC();
    //: Open socket.
    
    int Fd() const
      { return fd; }
    //: Access file descriptor.
    
    bool IsOpen() const
      { return fd >= 0; }
    //: Test if socket is open.
    
    SocketC Listen(bool block = true,int backLog = 1);
    //: Listen for a connection from a client.
    // Can only be used on server sockets.
    // If block is true, the call will not return until there
    // is a valid client.
    
    void Close();
    //: Close the socket.
    
    void SetDontClose(bool ndontClose)
      { dontClose = ndontClose; }
    //: Setup don't close flag.
    
    StringC ConnectedHost();
    //: Get host name 
    
    IntT ConnectedPort();
    //: Get other port number.
    
  protected:
    bool GetHostByName(const char *name,struct sockaddr_in &sin);
    //: Attempt to get info about named host.
    // returns true on success.
    
    int OpenSocket(struct sockaddr_in &sin,IntT sockNo);
    //: Open a socket to the given address / port no.
    
    int OpenClient(const char *name,IntT sockNo);
    //: Open a client socket.
    
    int OpenServer(const char *name,IntT sockNo);
    //: Open a server socket.
    // Its then ready for listening.
    
    int fd;
    bool server;
    struct sockaddr *addr; // Allocated as a char array.
    bool dontClose;
  };
  
  
  //! userlevel=Normal
  //: Socket connection handle.
  // For dealing with stream sockets.
  
  class SocketC 
    : public RCHandleC<SocketBodyC>
  {
  public:
    SocketC()
      {}
    //: Default constructor.
    // creates an invalid handle.
    
    SocketC(StringC name,bool server = false)
      : RCHandleC<SocketBodyC>(*new SocketBodyC(name,server))
      {}
    //: Open socket.
    
    SocketC(StringC name,UIntT portno,bool server = false)
      : RCHandleC<SocketBodyC>(*new SocketBodyC(name,portno,server))
      {}
    //: Open socket.
    
  protected:
    SocketC(struct sockaddr *addr,int nfd,bool server = false)
      : RCHandleC<SocketBodyC>(*new SocketBodyC(addr,nfd,server))
      {}
    //: Open socket.
    
    SocketBodyC &Body()
      { return RCHandleC<SocketBodyC>::Body(); }
    //: Access body.
    
    const SocketBodyC &Body() const
      { return RCHandleC<SocketBodyC>::Body(); }
    //: Access body.
    
  public:
    int Fd() const
      { return Body().Fd(); }
    //: Access file descriptor.
    
    bool IsOpen() const
      { return Body().IsOpen(); }
    //: Test if socket is open.
    
    inline SocketC Listen(bool block = true)
    { return Body().Listen(block); }
    //: Listen for a connection from a client.
    // Can only be used on server sockets.
    // If block is true, the call will not return until there
    // is a valid client.
  
    void Close()
      { Body().Close(); }
    //: Close the socket.
    
    void SetDontClose(bool ndontClose)
      { Body().SetDontClose(ndontClose); }
    //: Setup don't close flag.
    
    StringC ConnectedHost()
      { return Body().ConnectedHost(); }
    //: Get host name 
    
    IntT ConnectedPort()
      { return Body().ConnectedPort(); }
    //: Get other port number.
    
    friend class SocketBodyC;
  };
  
}
#endif
