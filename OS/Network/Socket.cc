// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlNet
//! file="Ravl/OS/Network/Socket.cc"


#ifdef __sol2__
#define __EXTENSIONS__ 1
#include <string.h>
#include <netdir.h>
#endif

#ifdef __linux__
#define _REENTRANT 1
#define _BSD_SOURCE 1
#define _XOPEN_SOURCE_EXTENDED 1
#endif

#include "Ravl/OS/Socket.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/OS/SktError.hh"
#include "Ravl/MTLocks.hh"
#if RAVL_HAVE_NETDB_H
#include <netdb.h>
#endif
#include <sys/types.h>
#if RAVL_USE_WINSOCK
#include <winsock.h>
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#if RAVL_HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#endif

#include <string.h>

#include <stdlib.h>
#include <errno.h>
#if RAVL_HAVE_UNISTD_H
#include <unistd.h>
#endif

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Open socket.
  
  SocketBodyC::SocketBodyC(StringC name,bool nserver) 
    : fd(-1),
      server(nserver),
      addr(0),
      dontClose(false)
  {
    int at = name.index(':');
    if(at < 0) {
      cerr << "SocketBodyC::SocketBodyC(), No port no in '" << name << "' \n";
      return ;
    }
    StringC host = name.before(at);
    StringC pn(name.after(at));
    int portno = atoi(pn);
    ONDEBUG(cerr << "Opening connection '" << host << "' port " << portno << " \n");
    if(server)
      OpenServer(host,portno);
    else
      OpenClient(host,portno);  
  }
  
  //: Open socket.
  
  SocketBodyC::SocketBodyC(StringC name,UIntT portno,bool nserver) 
    : fd(-1),
      server(nserver),
      addr(0),
      dontClose(false)
  {
    ONDEBUG(cerr << "Opening connection '" << name << "' port " << portno << "\n");
    if(server)
      OpenServer(name,portno);
    else
      OpenClient(name,portno);
  }
  
  
  //: Open socket.
  
  SocketBodyC::SocketBodyC(struct sockaddr *naddr,int nfd,bool nserver)
    : fd(nfd),
      server(nserver),
      addr(naddr),
      dontClose(false)
  {}
  
  //: Open socket.
  
  SocketBodyC::~SocketBodyC()  {
    Close(); // Tidy up.
  }
  
  //: Close the socket.
  
  void SocketBodyC::Close() {
    if(!dontClose) {
      if(fd >= 0)
	close(fd);
    }
    fd = -1;
    if(addr != 0)
      delete [] (char *) addr;
    addr = 0;
  }
  
  //: Attempt to get info about named host.
  // returns true on success.
  
  bool SocketBodyC::GetHostByName(const char *name,struct sockaddr_in &sin) {
    int opErrno = 0;
    int buffSize = 1024;
    char *hostentData = new char [buffSize];  
    struct hostent ent;
    struct hostent *result = 0;
    while(1) {
      ONDEBUG(cerr << " Looking for '" << name << "'\n");
#ifdef __linux__
      opErrno = 0;
      gethostbyname_r(name,&ent,hostentData,buffSize,&result, &opErrno);
      //cerr << " Result:" << ((void *) result) << " " << opErrno << "\n";
      if(opErrno == 0 && result != 0)
	break;
      
#else
      if((result = gethostbyname_r(name,&ent,hostentData,buffSize,&opErrno)) != 0)
	break;
#endif
      if(opErrno == ERANGE) {
	delete [] hostentData;
	buffSize *= 2;
	if(buffSize > 100000) {
	  delete [] hostentData;
	  throw ExceptionNetC("GetHostByName(),ERROR: Buffer requested too large. Failing.\n");
	}
	hostentData = new char [buffSize];
	continue;
      }
      if(opErrno < 0) {
	cerr << "Can't understand hostname '" << name  << "', Malformed address ? \n";
	delete hostentData;
	throw ExceptionNetC("Failed to unstanderstand find host name.\n");
      }
#if 0
      if(opErrno == TRY_AGAIN) {
	ONDEBUG(cerr << "Failed to get hostname, retrying. \n");
	DateC::Sleep(0.5);  // Thread safe sleep.
	continue;
      }
#endif      
      if(opErrno == HOST_NOT_FOUND) {
	cerr << "Can't find host '" << name  << "' .\n";
	delete hostentData;
	throw ExceptionNetC("Can't find host name.\n");
      }
      cerr << "Can't find host '" << name  << "' for some reason. Errno:" << opErrno << " '"
#ifndef __sol2__
	   << hstrerror(opErrno) << "'\n";
#else
      << strerror(opErrno) << "'\n";
#endif
      delete hostentData;
      throw ExceptionNetC("Can't find host name for some reason.");
    }
    
    RavlAssert(result != 0);
    //  char *addr = inet_ntoa(*((struct in_addr *)(result->h_addr_list[0])));
    //sin.sin_addr.s_addr = inet_addr(addr);
    
#if DODEBUG
    cerr << "Offical hostname: '" << result->h_name << "' \n";
    cerr << "h_length: '" << result->h_length << "' \n";
    //cerr << "h_addr_list: '" << result->h_addr_list[0] << "' \n";
#endif
    sin.sin_addr.s_addr = ((struct in_addr *)result->h_addr_list[0])->s_addr;
    sin.sin_family = ent.h_addrtype;
  
    ONDEBUG(cerr << "Got host data..  Addr:'" << inet_ntoa(sin.sin_addr) << "'\n");
    
    delete hostentData;
    return true;
  }


  //: Attempt to find hostname by the address.
  // returns true on success and assignes the hostname to name.
  
  bool SocketBodyC::GetHostByAddr(struct sockaddr &sin,int sinLen,StringC &name) {
#if defined(__linux__) && 0
    char hostname[1024];
    if(getnameinfo(&sin,sinLen,hostname,1024,0,0,0) != 0) {
      // Failed to get the name, at least put the address in dot notation.
      inet_nsap_ntoa (sinLen,(const unsigned char *)((void *)&sin),hostname);
    }
    name = StringC(hostname);
#else
    int buffSize = 1024;
    char *hostentData = new char [buffSize];
    struct hostent ent;
    int error = 0;
    while(1) {
#if defined(__linux__)
      struct hostent *result = 0;
      int retcode;
      // Hack to detect the difference between red-hat 6.x  and 7.x boxes.
#if (_XOPEN_SOURCE - 0) <= 500
      // For red-hat 6.2
      if((retcode = gethostbyaddr_r((char *) &(((sockaddr_in &)sin).sin_addr),sinLen,AF_INET,&ent,hostentData,buffSize,&result,&error)) != 0)
	break;
#else
      // For red-hat 7.2
      if((retcode = gethostbyaddr_r(&(((sockaddr_in &)sin).sin_addr),sinLen,AF_INET,&ent,hostentData,buffSize,&result,&error)) != 0)
	break;
#endif
#else
      gethostbyaddr_r((const char *) &((sockaddr_in &)sin).sin_addr,sinLen,AF_INET,&ent,hostentData,buffSize,&error);
#endif
      if(error == 0)
	break;
      if(error == ERANGE) { // Buffer not big enough.
	delete [] hostentData;
	buffSize *= 2;
	if(buffSize > 100000) {
	  delete [] hostentData;
	  throw ExceptionNetC("GetHostByName(),ERROR: Buffer requested too large. Failing.\n");
	}
	hostentData = new char [buffSize];
	continue;
      }
      cerr << "WARNING: Error while attempting to find hostname. errno=" << error << "\n";
      break; // Unknown error.
    }
    if(error == 0) { // If we got the name ok.
      name = StringC(ent.h_name);
      delete hostentData;
      return true;
    }
    delete hostentData;
    MTWriteLockC hold; // this call isn't MT safe. 
    name = inet_ntoa(((sockaddr_in &)sin).sin_addr); // Convert to a dot notation string.
#endif
    return true;
  }
  
  
  //: Open a socket to the given address / port no.
  
  int SocketBodyC::OpenSocket(struct sockaddr_in &sin,IntT portNo)  {
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
      cerr << "Failed to create socket. " << errno << "\n";
      return -1;
    }  
    return sock;
  }
  
  
  int SocketBodyC::OpenClient(const char *name,IntT portNo) {
    struct sockaddr_in sin = {PF_INET};
    if(!GetHostByName(name,sin))
      return -1;    
    if((fd = OpenSocket(sin,portNo)) < 0)
      return -1;
    sin.sin_port = htons(portNo);
    if(connect(fd, (sockaddr*)&sin, sizeof(sin)) < 0) {
      cerr << "Failed to connect socket " << errno << ":";
      Close();
      if(errno == EADDRINUSE) {
	cerr << "Address in use.\n";
	return -1;
      }
      if(errno == ECONNREFUSED) {
	cerr << "Connection refused. \n";
	return -1;
      }
      cerr << " \n";
      return -1;
    }
    if(addr != 0)
      delete [] (char *) addr;
    addr = (struct sockaddr *) new char [sizeof(struct sockaddr)];
    memcpy((char *) addr,(sockaddr*)&sin,sizeof(struct sockaddr));
    return fd;
  }
  
  
  //: Open a server socket.
  // Its then ready for listening.
  
  int SocketBodyC::OpenServer(const char *name,IntT portNo) {
    struct sockaddr_in sin = {PF_INET};
    if(!GetHostByName(name,sin))
      return -1;    
    if((fd = OpenSocket(sin,portNo)) < 0)
      return -1;
    sin.sin_port = htons(portNo);
    ONDEBUG(cerr  << "Binding name. \n");
    if(bind(fd,(struct sockaddr*)&sin, sizeof(sockaddr)) < 0) {
      cerr << "Bind failed. " << errno << "\n";
      Close();
      return -1;
    }
    return fd;
  }
  
  //: Listen for a connection from a client.
  // Can only be used on server sockets.
  
  SocketC SocketBodyC::Listen(bool block,int backLog) {
    RavlAssert(server); // Must be a server socket.
    if(fd < 0)
      return SocketC(); // Not open!
    do {
      ONDEBUG(cerr  << "Listening. \n");
      if(listen(fd, backLog) < 0) {
	cerr << "Listen failed." << errno << " \n";
	return SocketC(); // Failed.
      }
      ONDEBUG(cerr  << "Accepting. \n");
      int addrBuffSize = sizeof(sockaddr) + 256;
      struct sockaddr *cn_addr = (struct sockaddr *) new char [addrBuffSize];
#ifdef __sgi__
      int nfd = accept(fd,cn_addr, &addrBuffSize);
#else
      int nfd = accept(fd,cn_addr,(socklen_t *) &addrBuffSize);
#endif
      ONDEBUG(cerr  << "Got connection. \n");
      if(nfd >= 0) 
	return SocketC(cn_addr,nfd);
      delete [] (char *) cn_addr;  
    } while(block);
    return SocketC();
  }
  
  //: Get host name 
  
  StringC SocketBodyC::ConnectedHost() { 
    StringC ret("-failed-");
    if(fd == 0)
      return ret;
#ifdef __sgi__
    int namelen = sizeof(sockaddr) + 256;
#else
    socklen_t namelen = sizeof(sockaddr) + 256;
#endif
    struct sockaddr *name = (struct sockaddr *) new char[namelen];
    if(getpeername(fd,name,&namelen) != 0) {
      cerr << "SocketBodyC::ConnectedHost(), gerpeername failed. Error=" << errno << "\n";
      return StringC("unknown");
    }
    GetHostByAddr(*name,namelen,ret);
    ONDEBUG(cerr << "Hostname=" << ret << "\n");
    delete [] (char*) name;
    return ret;
  }
  
  //: Get other port number.
  
  IntT SocketBodyC::ConnectedPort() { 
    if(addr == 0)
      return 0;
    return 0;
  }
}
