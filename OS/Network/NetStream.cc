// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlOS
//! file="Ravl/OS/Network/NetStream.cc"

#include "Ravl/OS/NetStream.hh"

namespace RavlN {
  
  ////////// Output //////////////////////////////////
  
  //: Open net connection for output.
  
  ONetStreamC::ONetStreamC(const StringC &filename,bool buffered,bool server) 
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
  
  ONetStreamC::ONetStreamC(const SocketC &nsock,bool buffered)
    : OStreamC(nsock.Fd(),buffered),
      sock(nsock)
  {
    sock.SetDontClose(true);
  }
  
  ////////// Input //////////////////////////////////
  
  //: Open net connection for input
  
  INetStreamC::INetStreamC(const StringC &filename,bool buffered,bool server) 
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
  
  INetStreamC::INetStreamC(const SocketC &nsock,bool buffered) 
    : IStreamC(nsock.Fd(),buffered),
      sock(nsock)
  {
    sock.SetDontClose(true);
  }
  
}
