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

#include "Ravl/config.h"
#if RAVL_OS_SOLARIS
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
#include <netinet/tcp.h>
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

#include <sys/uio.h>
#include <fcntl.h>

#include "Ravl/OS/SysLog.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

#if !RAVL_HAVE_SOCKLEN_T
#define socklen_t int
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
    ONDEBUG(cerr << "SocketBodyC::Close() dontclose=" << dontClose << " fd=" << fd << "\n");
    if(!dontClose) {
      if(fd >= 0)
	close(fd);
    }
    fd = -1;
    if(addr != 0)
      delete [] (char *) addr;
    addr = 0;
  }
  
  int GetTCPProtocolNumber() {
#if RAVL_OS_LINUX
    return SOL_TCP;
#else
    struct protoent entry;
    char buffer[1024];
    if(getprotobyname_r("tcp",&entry,buffer,1024) != 0) {
      cerr << "WARNING: Failed to get tcp protocol number. Guessing a value of 6. \n";
      return 6;
    }
    return entry.p_proto;
#endif
  }
  
  //: Send data as soon as possible. 
  
  void SocketBodyC::SetNoDelay() {
    // Disable delays.
    int n = 1;
    static int tcpprotocolno = GetTCPProtocolNumber();
    if(setsockopt(fd,tcpprotocolno,TCP_NODELAY,&n,sizeof(int)) != 0) {
      cerr << "SocketBodyC::SetNoDelay(), Failed. errno=" << errno <<"\n";
    }
  }
  
  //: Attempt to get info about named host.
  // returns true on success.
  
  bool SocketBodyC::GetHostByName(const char *name,struct sockaddr_in &sin) {
    int opErrno = 0;
    int buffSize = 1024;
    char *hostentData = new char [buffSize];  
    struct hostent ent;
    struct hostent *result = 0;
    if(*name == 0)
      name = "localhost";
    while(1) {
      ONDEBUG(cerr << " Looking for '" << name << "'\n");
      opErrno = 0;
#if RAVL_OS_LINUX
      if(gethostbyname_r(name,&ent,hostentData,buffSize,&result, &opErrno) == 0 && result != 0)
	break;
#elif RAVL_OS_OSF
      if((gethostbyname_r(name,&ent,(struct hostent_data *) hostentData)) != 0) {
	result = &ent;
	break;
      }
      opErrno = h_errno;
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
	delete [] hostentData;
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
	delete [] hostentData;
	throw ExceptionNetC("Can't find host name.\n");
      }
      cerr << "Can't find host '" << name  << "' for some reason. Errno:" << opErrno << " '"
#if RAVL_HAVE_HSTRERROR
	   << hstrerror(opErrno) << "'\n";
#else
      << strerror(opErrno) << "'\n";
#endif
      delete [] hostentData;
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
    
    delete [] hostentData;
    return true;
  }


  //: Attempt to find hostname by the address.
  // returns true on success and assignes the hostname to name.
  
  bool SocketBodyC::GetHostByAddr(struct sockaddr &sin,int sinLen,StringC &name) {
#if  0
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
#if RAVL_OS_LINUX
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
#elif RAVL_OS_OSF
      if(gethostbyaddr_r((const char *) &((sockaddr_in &)sin).sin_addr,sinLen,AF_INET,&ent,(struct hostent_data *)hostentData) == 0)
	break;
      error = h_errno;
#elif RAVL_OS_IRIX 
      ulong tmp_addr = ((sockaddr_in &)sin).sin_addr.s_addr ; 
      gethostbyaddr_r ((const char *) & tmp_addr, sizeof(tmp_addr), AF_INET, &ent, hostentData, buffSize, &error) ; 
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
      cerr << "WARNING: Error while attempting to find hostname from ip address. errno=" << error << "\n";
      break; // Unknown error.
    }
    if(error == 0) { // If we got the name ok.
      name = StringC(ent.h_name);
      delete [] hostentData;
      return true;
    }
    delete [] hostentData;
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
#if DODEBUG
      cerr << "Failed to connect socket " << errno << ":";
      if(errno == EADDRINUSE) {
	cerr << "Address in use.\n";
	return -1;
      }
      if(errno == ECONNREFUSED) {
	cerr << "Connection refused. \n";
	return -1;
      }
      cerr << " \n";
#endif
      Close();
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
    if(*name != 0) {
      if(!GetHostByName(name,sin))
	return -1;
    } else {
      cerr << "sin_addr=" << sizeof(sin.sin_addr) <<  " ANY=" << sizeof(INADDR_ANY) << "\n";
      static in_addr_t anyAddress = INADDR_ANY;
      //sin.sin_addr = anyAddress;
      memcpy(&sin.sin_addr,&anyAddress,sizeof(INADDR_ANY));
    }
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
      do {
	int nfd = accept(fd,cn_addr,(socklen_t *) &addrBuffSize);
	ONDEBUG(cerr  << "Got connection. \n");
	if(nfd >= 0)
	  return SocketC(cn_addr,nfd); // Socket accepted ok.
	// Recoverable error ?
      } while(errno == EAGAIN || errno == EINTR) ;
      cerr << "ERROR: Failed to accept connection. errno=" << errno << "\n"; ;
      delete [] (char *) cn_addr;  
    } while(block);
    return SocketC();
  }
  
  //: Get host name 
  
  StringC SocketBodyC::ConnectedHost() { 
    StringC ret("-failed-");
    if(fd == 0)
      return ret;
    socklen_t namelen = sizeof(sockaddr) + 256;
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
    struct sockaddr_in name;
    socklen_t namelen = sizeof(name); 
    getpeername( fd, (sockaddr*) &name, &namelen );
    IntT ret = ntohs( name.sin_port );
    return ret;
  }

  //: Enable non-blocking use of read and write.
  // true= read and write's won't do blocking waits.
  
  bool SocketBodyC::SetNonBlocking(bool block) {
    long flags = fcntl(fd,F_GETFL);
    if(flags < 0) {
      cerr << "SocketBodyC::SetNonBlocking(), WARNING: Get flags failed. \n";
      return false;
    }
    long newFlags;
    if(block) 
      newFlags = flags | O_NONBLOCK;
    else
      newFlags = flags & ~O_NONBLOCK;
    flags = fcntl(fd,F_SETFL,newFlags);
    if(flags < 0) {
      cerr << "SocketBodyC::SetNonBlocking(), WARNING: Set flags failed. \n";
      return false;
    }
    return false;
  }
  
  //: Read some bytes from a stream.
  
  IntT SocketBodyC::Read(char *buff,UIntT size) {
    UIntT at = 0;
    fd_set rfds;
    FD_ZERO(&rfds);
    struct timeval tv;
    while(at < size && fd >= 0) {
#if 1
      //ONDEBUG(SysLog(SYSLOG_DEBUG) << "SocketBodyC::Read(), Waiting for select. ");
      FD_SET(fd,&rfds);
      tv.tv_sec = 5;
      tv.tv_usec = 0;
      if(select(fd+1,&rfds,0,0,&tv) == 0) {
	//ONDEBUG(SysLog(SYSLOG_DEBUG) << "SocketBodyC::Read(), Select timeout. ");
	continue;
      }
      //ONDEBUG(SysLog(SYSLOG_DEBUG) << "SocketBodyC::Read(), Waiting for read. Read=" << (int) FD_ISSET(nfd, &rfds) << " Except=" << (int) FD_ISSET(nfd, &efds) << "\n");
#endif
      if(fd < 0)
	break;
      int n = read(fd,&(buff[at]),size - at);
      if(n == 0) { // Linux indicates a close by returning 0 bytes read.  Is this portable ??
	ONDEBUG(SysLog(SYSLOG_DEBUG) << "Socket close. ");
	return at;
      }
      if(n < 0) {
	ONDEBUG(SysLog(SYSLOG_DEBUG) << "SocketBodyC::Read(), Error on read. ");
	if(errno == EINTR || errno == EAGAIN)
	  continue;
#if RAVL_OS_LINUX
	char buff[256];
	SysLog(SYSLOG_WARNING) << "SocketBodyC::Read(), Error reading from socket :" << errno << " '" << strerror_r(errno,buff,256) << "'";
#else
	SysLog(SYSLOG_WARNING) << "SocketBodyC::Read(), Error reading from socket :" << errno;
#endif
	return false;
      }
      at += n;
    }
    return at;
  }

  //: Read some bytes from a stream.
  
  IntT SocketBodyC::ReadV(char **buffer,IntT *len,int n) {
    if(n == 0) return 0;
    struct iovec vecBuf[100];
    struct iovec *vecp = vecBuf;
    IntT at = 0,total = 0;
    if(n > 100) {
      vecp = (struct iovec *) malloc(n * sizeof(iovec));
      if(vecp == 0) {
	SysLog(SYSLOG_WARNING) << "SocketBodyC::ReadV(), Out of memory ";
	return 0;
      }
    }
    for(int i = 0;i < n;i++) {
      vecp[i].iov_base = (char *) buffer[i];
      vecp[i].iov_len = len[i];
      total += len[i];
    }
    
    fd_set wfds;
    FD_ZERO(&wfds);
    
    do {
      FD_SET(fd,&wfds);
      if(select(fd+1,&wfds,0,0,0) == 0)
	continue;
      at = readv(fd,vecp,n);
      if(at > 0)
	break;
      if(errno != EINTR && errno != EAGAIN) {
#if RAVL_OS_LINUX
	char buff[256];
	SysLog(SYSLOG_WARNING) << "SocketBodyC::ReadV(), Error reading from socket :" << errno << " '" << strerror_r(errno,buff,256) << "' ";
#else
	SysLog(SYSLOG_WARNING) << "SocketBodyC::ReadV(), Error reading from socket :" << errno;
#endif
	if(n > 100) free(vecp);
	return false;
      }
      // Temporary failure, try again.
    } while(fd >= 0);
    if(at == total) return at; // All done ?
    
    SysLog(SYSLOG_WARNING) << "SocketBodyC::ReadV(), Socket read interupted, attempting to recover. (Relatively untested code.) \n";
    
    // Read in 1 lump failed, break it up.
    int b = 0,xat = 0;
    do {
      for(b = 0;b < n;b++) {
	xat += len[b];
	if(at < xat) //In this block ?
	  break;
      }
      if(xat < at){
	IntT done = len[b] - (at - xat);
	IntT x = Read(&(buffer[b][done]),len[b] - done);
	if(x < 0) { 
	  if(n > 100) free(vecp);
	  return at;
	}
	at += x;
	if(x < (len[b] - done)) {
	  if(n > 100) free(vecp);
	  return at; // Some serious error must have occured to stop 'Read'
	}
      }
      RavlAssert(xat == at);
      b++;
      int x = readv(fd,&(vecp[b]),n - b);
      if(x < 0) {
	if(errno != EINTR && errno != EAGAIN) {
#if RAVL_OS_LINUX
	  char buff[256];
	  SysLog(SYSLOG_WARNING) << "SocketBodyC::ReadV(), Error writing to socket :" << errno << " '" << strerror_r(errno,buff,256) << "' ";
#else
	  SysLog(SYSLOG_WARNING) << "SocketBodyC::ReadV(), Error writing to socket :" << errno;
#endif
	  if(n > 100) free(vecp);
	  return at;
	}
	x = 0;
      }
      at += x;
    } while(at < total) ;
    if(n > 100) free(vecp);
    return at;
  }

  //: Write multiple buffers
  
  IntT SocketBodyC::WriteV(const char **buffer,IntT *len,int n) {
    if(n == 0) return 0;
    struct timeval timeout;
    struct iovec vecBuf[100];
    struct iovec *vecp = vecBuf;
    int rn;
    IntT at = 0,total = 0;
    if(n > 100) {
      vecp = (struct iovec *) malloc(n * sizeof(iovec));
      if(vecp == 0) {
	SysLog(SYSLOG_WARNING) << "SocketBodyC::WriteV(), Out of memory ";
	return 0;
      }
    }
    for(int i = 0;i < n;i++) {
      vecp[i].iov_base = (char *) buffer[i];
      vecp[i].iov_len = len[i];
      total += len[i];
    }
    
    fd_set wfds;
    FD_ZERO(&wfds);
    
    do {
      FD_SET(fd,&wfds);
      timeout.tv_sec = 60; // Time-out of a minute...
      timeout.tv_usec = 0;
      if((rn = select(fd+1,0,&wfds,0,&timeout)) == 0) {
	SysLog(SYSLOG_WARNING) << "SocketBodyC::Write(), Timeout writting to socket. :" << errno;
	return at;
      }
      if(rn < 0) {
	if(errno == EINTR || errno == EAGAIN)
	  continue;
#if RAVL_OS_LINUX
	char buff[256];
	SysLog(SYSLOG_WARNING) << "SocketBodyC::Write(), Error writing to socket :" << errno << " '" << strerror_r(errno,buff,256) << "' ";
#else
	SysLog(SYSLOG_WARNING) << "SocketBodyC::Write(), Error writing to socket :" << errno;
#endif
	return at;
      }
      //cerr << "writev(" << fd << "," << (void *) vecp << "," << n << ");\n";
      if((at = writev(fd,vecp,n)) > 0)
	break;
      if(errno != EINTR && errno != EAGAIN) {
#if RAVL_OS_LINUX
	char buff[256];
	SysLog(SYSLOG_WARNING) << "SocketBodyC::WriteV(), Error writing to socket :" << errno << " '" << strerror_r(errno,buff,256) << "' ";
#else
	SysLog(SYSLOG_WARNING) << "SocketBodyC::WriteV(), Error writing to socket :" << errno;
#endif
	if(n > 100) free(vecp);
	return false;
      }
      // Temporary failure, try again.
    } while(fd >= 0);
    if(at == total) return at; // All done ?
    
    SysLog(SYSLOG_WARNING) << "SocketBodyC::WriteV(), Socket write interupted, attempting to recover. (Relatively untested code.) \n";
    
    // Write in 1 lump failed, break it up.
    int b = 0,xat = 0;
    do {
      for(b = 0;b < n;b++) {
	xat += len[b];
	if(at < xat) //In this block ?
	  break;
      }
      if(xat < at){
	IntT done = len[b] - (at - xat);
	IntT x = Write(&(buffer[b][done]),len[b] - done);
	if(x < 0) { 
	  if(n > 100) free(vecp);
	  return at;
	}
	at += x;
	if(x < (len[b] - done)) {
	  if(n > 100) free(vecp);
	  return at; // Some serious error must have occured to stop 'Write'
	}
      }
      RavlAssert(xat == at);
      b++;
      timeout.tv_sec = 60; // Time-out of a minute...
      timeout.tv_usec = 0;
      
      int x = writev(fd,&(vecp[b]),n - b);
      if(x < 0) {
	if(errno != EINTR && errno != EAGAIN) {
#if RAVL_OS_LINUX
	  char buff[256];
	  SysLog(SYSLOG_WARNING) << "SocketBodyC::WriteV(), Error writing to socket :" << errno << " '" << strerror_r(errno,buff,256) << "' ";
#else
	  SysLog(SYSLOG_WARNING) << "SocketBodyC::WriteV(), Error writing to socket :" << errno;
#endif
	  if(n > 100) free(vecp);
	  return at;
	}
	x = 0;
      }
      at += x;
    } while(at < total) ;
    if(n > 100) free(vecp);
    return at;
  }
    
  //: Write some bytes to a stream.
  
  IntT SocketBodyC::Write(const char *buff,UIntT size) {
    UIntT at = 0;
    int rn;
    fd_set wfds;
    FD_ZERO(&wfds);
    struct timeval timeout;
    
    while(at < size && fd >= 0) {
      FD_SET(fd,&wfds);
      timeout.tv_sec = 60; // Time-out of a minute...
      timeout.tv_usec = 0;
      if((rn = select(fd+1,0,&wfds,0,&timeout)) == 0) {
	SysLog(SYSLOG_WARNING) << "SocketBodyC::Write(), Timeout writting to socket. :" << errno;
	return at;
      }
      if(rn < 0) {
	if(errno == EINTR || errno == EAGAIN)
	  continue;
#if RAVL_OS_LINUX
	char buff[256];
	SysLog(SYSLOG_WARNING) << "SocketBodyC::Write(), Error writing to socket :" << errno << " '" << strerror_r(errno,buff,256) << "' ";
#else
	SysLog(SYSLOG_WARNING) << "SocketBodyC::Write(), Error writing to socket :" << errno;
#endif
	return at;
      }
      FD_SET(fd,&wfds);
      timeout.tv_sec = 60; // Time-out of a minute...
      timeout.tv_usec = 0;
      if((rn = select(fd+1,0,&wfds,0,&timeout)) == 0) {
	SysLog(SYSLOG_WARNING) << "SocketBodyC::Write(), Timeout writting to socket. :" << errno;
	return at;
      }
      if(rn < 0) {
	if(errno == EINTR || errno == EAGAIN)
	  continue;
#if RAVL_OS_LINUX
	char buff[256];
	SysLog(SYSLOG_WARNING) << "SocketBodyC::Write(), Error writing to socket :" << errno << " '" << strerror_r(errno,buff,256) << "' ";
#else
	SysLog(SYSLOG_WARNING) << "SocketBodyC::Write(), Error writing to socket :" << errno;
#endif
	return at;
      }
      int n = write(fd,&(buff[at]),size - at);
      if(n < 0) {
	ONDEBUG(SysLog(SYSLOG_DEBUG) << "SocketBodyC::RunReceive(), Error on read. ");
	if(errno == EINTR || errno == EAGAIN)
	  continue;
#if RAVL_OS_LINUX
	char buff[256];
	SysLog(SYSLOG_WARNING) << "SocketBodyC::Write(), Error writing to socket :" << errno << " '" << strerror_r(errno,buff,256) << "' ";
#else
	SysLog(SYSLOG_WARNING) << "SocketBodyC::Write(), Error writing to socket :" << errno;
#endif
	return at;
      }
      at += n;
    }    
    return at;
  }

}
