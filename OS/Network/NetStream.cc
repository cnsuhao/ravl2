// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlNet
//! file="Ravl/OS/Network/NetStream.cc"

#ifdef __sol2__
#define __EXTENSIONS__ 1
#endif

#ifdef __sgi__
#undef _POSIX_C_SOURCE
#include <standards.h>
#endif

extern "C" {
#include <unistd.h>
#include <sys/types.h>
#ifdef __sgi__
#include <bstring.h>
#endif
#include <sys/time.h>
#include <sys/select.h>
#include <string.h>
};

#include "Ravl/OS/NetStream.hh"

namespace RavlN {
  
  ////////// Output //////////////////////////////////
  
  //: Open net connection for output.
  
  NetOStreamC::NetOStreamC(const StringC &filename,bool buffered,bool server) 
    : sock(filename,server)
  {
    if(!sock.IsOpen())
      return ;
    if(server) {
      sock = sock.Listen();
      if(!sock.IsValid())
	return ;
    }
    (*this).OStreamC::operator=(OStreamC(sock.Fd(),buffered));
    sock.SetDontClose(true);
  }
  
  //: Use a socket to build new handle.
  
  NetOStreamC::NetOStreamC(const SocketC &nsock,bool buffered)
    : OStreamC(nsock.Fd(),buffered),
      sock(nsock)
  {
    sock.SetDontClose(true);
  }
  
  ////////// Input //////////////////////////////////
  
  //: Open net connection for input
  
  NetIStreamC::NetIStreamC(const StringC &filename,bool buffered,bool server) 
    : sock(filename,server)
  {
    if(!sock.IsOpen()) 
      return ; // Failed.
    
    if(server) { 
      sock = sock.Listen();
      if(!sock.IsValid())
	return ;
    }
    (*this).IStreamC::operator=(IStreamC(sock.Fd(),buffered));
    sock.SetDontClose(true);
  }
  
  //: Use a socket to build new handle.
  
  NetIStreamC::NetIStreamC(const SocketC &nsock,bool buffered) 
    : IStreamC(nsock.Fd(),buffered),
      sock(nsock)
  { sock.SetDontClose(true); }
  
  //: Wait for data to arrive.
  // Returns true if data is available, on a timeout or other interupt
  // false is returned.
  
  bool NetIStreamC::WaitForData(RealT timeout) {
    if(!sock.IsOpen())
      return false;
    fd_set readSet;
    int fd = sock.Fd();
    FD_ZERO(&readSet);
    FD_SET(fd,&readSet);
    int reterr;
    if(timeout >= 0) {
      struct timeval timelimit;
      timelimit.tv_sec = (long) timeout;
      timelimit.tv_usec = (long) ((RealT) (timeout - (RealT) timelimit.tv_sec) * 1000000);
      reterr = select(fd+1,&readSet,0,0,&timelimit);
    } else
      reterr = select(fd+1,&readSet,0,0,0); // Infinite timeout.
    if(reterr==0)
      return false;
    return FD_ISSET(fd,&readSet);
  }

}
