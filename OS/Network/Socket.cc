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
#if !RAVL_USE_WINSOCK

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
#include "Ravl/SArray1d.hh"

#if RAVL_HAVE_NETDB_H
#include <netdb.h>
#endif
#include <sys/types.h>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#if RAVL_HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif

#include <string.h>

#include <stdlib.h>
#include <errno.h>
#if RAVL_HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <sys/uio.h>
#include <fcntl.h>

#include <poll.h>

#include "Ravl/OS/SysLog.hh"
#include "Ravl/OS/Date.hh"

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
      dontClose(false),
      writeTimeout(60)
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
      dontClose(false),
      writeTimeout(180)
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
      dontClose(false),
      writeTimeout(180)
  {
    //SetNonBlocking(true);
  }

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
#if RAVL_OS_LINUX || RAVL_OS_LINUX64
    return SOL_TCP;
#elif RAVL_OS_MACOSX
    return getprotobyname("tcp")->p_proto;
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

  //: Cork stream.
  // This is used to indicate that there is going to
  // be several write operations immediatly following each
  // other and stops the transmition of fragmented packets.
  // If your not expecting to do any more writes immediatly
  // you must call 'Uncork()'.
  // Returns true if Corking is supported by stream.

  bool SocketBodyC::Cork(bool enable) {
    // Enable delays.
    int n;
    if(enable)
      n = 1;
    else
      n = 0;
    static int tcpprotocolno = GetTCPProtocolNumber();
#ifdef TCP_CORK
    // Linux specific call.
    if(setsockopt(fd,tcpprotocolno,TCP_CORK,&n,sizeof(int)) != 0) {
      cerr << "SocketBodyC::Cork(), Failed. errno=" << errno <<"\n";
    }
#else
    if(setsockopt(fd,tcpprotocolno,TCP_NODELAY,&n,sizeof(int)) != 0) {
      cerr << "SocketBodyC::Cork(), Failed. errno=" << errno <<"\n";
    }
#endif
    return true;
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
    ent.h_addrtype = 0;
    while(1) {
      ONDEBUG(cerr << " Looking for '" << name << "'\n");
      opErrno = 0;
#if RAVL_OS_LINUX || RAVL_OS_LINUX64
      if(gethostbyname_r(name,&ent,hostentData,buffSize,&result, &opErrno) == 0 && result != 0)
	break;
#elif RAVL_OS_OSF
      if((gethostbyname_r(name,&ent,(struct hostent_data *) hostentData)) != 0) {
        result = &ent;
        break;
      }
      opErrno = h_errno;
#elif RAVL_OS_MACOSX
	  if((result = gethostbyname(name)) != 0)
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
        SysLog(SYSLOG_WARNING) << "Can't understand hostname '" << name  << "', Malformed address?";
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
        SysLog(SYSLOG_WARNING) << "Can't find host '" << name << "' .";
        delete [] hostentData;
        throw ExceptionNetC("Can't find host name.\n");
      }
      SysLog(SYSLOG_WARNING) << "Can't find host '" << name  << "' for some reason. Errno:" << opErrno << " '"
#if RAVL_HAVE_HSTRERROR
        << hstrerror(opErrno) << "'";
#else
        << strerror(opErrno) << "'";
#endif
      delete [] hostentData;
      throw ExceptionNetC("Can't find host name for some reason.");
    }

    RavlAssert(result != 0);
    //  char *addr = inet_ntoa(*((struct in_addr *)(result->h_addr_list[0])));
    //sin.sin_addr.s_addr = inet_addr(addr);

#if DODEBUG
    cerr << "Offical hostname: '" << result->h_name << "' h_length: '" << result->h_length << "' \n";
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
    ent.h_name = 0;

    int error = 0;
    while(1) {
#if RAVL_OS_LINUX || RAVL_OS_LINUX64
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
#elif RAVL_OS_MACOSX
      {
      	struct hostent *pHostent = gethostbyaddr((const char *) &((sockaddr_in &)sin).sin_addr,sinLen,AF_INET);
      	if (pHostent == 0)
      	  break;
      }
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
    if(!GetHostByName(name,sin)) {
      cerr << "Failed to lookup hostname '" << name << "'\n";
      return -1;
    }
    if((fd = OpenSocket(sin,portNo)) < 0)
      return -1;
    sin.sin_port = htons(portNo);
    int retryLimit = 10;
    while(connect(fd, (sockaddr*)&sin, sizeof(sin)) < 0) {
      // Sometimes its worth trying a again a few times.
      if((errno == EAGAIN || errno == EINTR || errno==ETIMEDOUT) && retryLimit-- > 0) {
        ONDEBUG(cerr << "Connect failed, EAGAIN. errno=" << errno << " \n");
        Sleep(0.1);
        continue;
      }
      Close();
#if DODEBUG
      if(errno == EADDRINUSE) {
        SysLog(SYSLOG_DEBUG) << "Address in use. " << fd ;
        return -1;
      }
      if(errno == ECONNREFUSED) {
        SysLog(SYSLOG_DEBUG) << "Connection refused. " << fd;
        return -1;
      }
      SysLog(SYSLOG_DEBUG) << "Connect failed. " << fd;
#endif
      return -1;
    }

    ONDEBUG(SysLog(SYSLOG_DEBUG) << "SocketBodyC::OpenClient(), Connected to '" << name  << "'");
    if(addr != 0)
      delete [] (char *) addr;
    addr = (struct sockaddr *) new char [sizeof(struct sockaddr)];
    memcpy((char *) addr,(sockaddr*)&sin,sizeof(struct sockaddr));
    //SetNonBlocking(true);
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
      sin.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    if((fd = OpenSocket(sin,portNo)) < 0)
      return -1;
    sin.sin_port = htons(portNo);
    ONDEBUG(cerr  << "Binding name. \n");
    if(bind(fd,(struct sockaddr*)&sin, sizeof(sockaddr)) < 0) {
      cerr << "Bind failed. errno=" << errno << "\n";
      cerr << "Error:" << strerror(errno) << endl;
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
      socklen_t addrBuffSize = sizeof(sockaddr) + 256;
      struct sockaddr *cn_addr = (struct sockaddr *) new char [addrBuffSize];
      do {
	int nfd = accept(fd,cn_addr, &addrBuffSize);
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
    if(getpeername(fd,name,&namelen) != 0)
    {
      delete [] name;
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
    ONDEBUG(cerr << "SocketBodyC::SetNonBlocking(), Block=" << block << "\n");
    long flags = fcntl(fd,F_GETFL);
    if(flags < 0) {
      cerr << "SocketBodyC::SetNonBlocking(), WARNING: Get flags failed. errno=" << errno << " fd=" << fd << "\n";
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


  //: Wait for read to be ready.
  // Returns false on error.

  bool SocketBodyC::WaitForRead() {
#if !RAVL_OS_MACOSX
    fd_set rfds;
    struct timeval tv;
    FD_ZERO(&rfds);

    while(fd >= 0) {
      int checkFd = fd;
      if(checkFd < 0)
        break;
      FD_SET(checkFd,&rfds);
      tv.tv_sec = 5;
      tv.tv_usec = 0;
      int rn = select(checkFd+1,&rfds,0,0,&tv);
      if(rn == 0) {
	//SysLog(SYSLOG_DEBUG) << "SocketBodyC::WaitForRead(), Timeout retry! " << errno;
	continue; // Timeout, check if sockets been closed.
      }
      if(rn > 0) return fd >= 0; // Some data's ready!
      if(!CheckErrors("SocketBodyC::WaitForRead()"))
	break;
      //SysLog(SYSLOG_DEBUG) << "SocketBodyC::WaitForRead(), Temp error, retry! " << errno;
      // Temporary error, retry.
    }
#else
    struct pollfd ufds[2];
    ufds[0].fd = fd;
    ufds[0].events = POLLIN | POLLERR |  POLLHUP | POLLNVAL;
    while(fd >= 0) {
      ufds[0].revents = 0;
      int rn = poll(ufds,1,5000);
      SysLog(SYSLOG_DEBUG) << "SocketBodyC::WaitForRead(), Poll=" << rn << " Errno= " << errno << " Events=" << ufds[0].revents;
      if(rn == 0) continue; // Timeout.
      if(rn < 0) { // Error.
	if(!CheckErrors("SocketBodyC::WaitForRead()"))
	  break;
      }
      if(ufds[0].revents & POLLIN) // Data ready ?
	return true;
      if(ufds[0].revents & POLLERR) { // Error ?
	SysLog(SYSLOG_DEBUG) << "SocketBodyC::WaitForRead(), Error on stream " << errno;
	return false;
      }

      if(ufds[0].revents & POLLHUP) { // Hangup ?
	SysLog(SYSLOG_DEBUG) << "SocketBodyC::WaitForRead(), Hangup on stream " << errno;
	return false;
      }
      if(ufds[0].revents & POLLNVAL) { // Invalid fd ?
	SysLog(SYSLOG_DEBUG) << "SocketBodyC::WaitForRead(), Invalid fd for stream " << errno;
	return false;
      }
      SysLog(SYSLOG_DEBUG) << "SocketBodyC::WaitForRead(), Unexpected condition " << ufds[0].revents;
    }
#endif
    return false;
  }

  //: Wait for write to be ready.
  // Returns false on error.

  bool SocketBodyC::WaitForWrite() {
#if !RAVL_OS_MACOSX
    struct timeval timeout;
    fd_set wfds;
    FD_ZERO(&wfds);
    DateC startTime(true);
    while(fd >= 0) {
      RealT timeToGo = (RealT) writeTimeout - (DateC(true) - startTime).Double(); // Compute time remaining.
      if(timeToGo <= 0) {
	SysLog(SYSLOG_WARNING) << "SocketBodyC::WaitForWrite(), Timeout writting to socket. : " << errno;
	break;
      }
      int checkFd = fd; // Read it from the class, it might be set to -1 at any time.
      if(checkFd < 0)
        break;
      FD_SET(checkFd,&wfds);
      timeout.tv_sec = Round(timeToGo);
      timeout.tv_usec = 0;
      int rn = select(checkFd+1,0,&wfds,0,&timeout);
      if(rn == 0) continue; // Go check if timeout has expired.
      if(rn > 0) return fd >= 0; // Ready to write.
      if(!CheckErrors("SocketBodyC::WaitForWrite()"))
	break;
      // Retry.
    }
#endif
    return false;
  }

  //: Check for recoverable errors.

  bool SocketBodyC::CheckErrors(const char *opName) {
    if(errno == EINTR || errno == EAGAIN)
      return true; // Temporary error, try again.
#if RAVL_OS_LINUX
    char buff[256];
    SysLog(SYSLOG_WARNING) << opName << " Error :" << errno << " '" << strerror_r(errno,buff,256) << "' ";
#else
    SysLog(SYSLOG_WARNING) << opName << " Error :" << errno;
#endif
    return false;
  }

  //: Read some bytes from a stream.

  IntT SocketBodyC::Read(char *buff,UIntT size) {
    //ONDEBUG(cerr << "SocketBodyC::Read(), Buff=" << ((void *) buff) << " Size=" << size << "\n");
    UIntT at = 0;
    while(at < size && fd >= 0) {
      if(!WaitForRead())
	break;
      int n = read(fd,&(buff[at]),size - at);
      if(n == 0) { // Linux indicates a close by returning 0 bytes read.  Is this portable ??
	ONDEBUG(SysLog(SYSLOG_INFO) << "SocketBodyC::Read(). Socket closed ? fd=" << fd);
	break;
      }
      if(n < 0) {
	if(!CheckErrors("SocketBodyC::Read()"))
	  break;
	SysLog(SYSLOG_DEBUG) << "SocketBodyC::Read(), Temp error, retry! " << errno;
	// Temporary error, retry
	n = 0;
      }
      at += n;
    }
    return at;
  }

  //: Read some bytes from a stream.

  IntT SocketBodyC::ReadV(char **buffer,IntT *len,int n) {
    if(n == 0) return 0;
    struct iovec vecBuf[101];
    struct iovec *vecp = vecBuf;
    IntT at = 0,total = 0;
    SArray1dC<iovec> vecArray;
    if(n > 100) {
      vecArray = SArray1dC<iovec>(n);
      vecp = &(vecArray[0]);
    }
    for(int i = 0;i < n;i++) {
      vecp[i].iov_base = (char *) buffer[i];
      vecp[i].iov_len = len[i];
      total += len[i];
    }

    while(fd >= 0) {
      if(!WaitForRead())
	return 0;
      at = readv(fd,vecp,n);
      if(at == 0) {
	SysLog(SYSLOG_INFO) << "SocketBodyC::ReadV(). Socket closed. fd=" << fd;
	break;
      }
      if(at > 0)
	break;
      if(!CheckErrors("SocketBodyC::ReadV()"))
	return 0;
      // Temporary failure, try again.
    }
    if(at == total)
      return at; // All done ?

    ONDEBUG(SysLog(SYSLOG_WARNING) << "SocketBodyC::ReadV(), Socket read interupted, at=" << at << " Blocks=" << n << " attempting to recover. \n");

    // Read in 1 lump failed, break it up.
    int b = 0,xat = 0;
    do {
      for(;b < n;b++) {
	ONDEBUG(cerr << "len[" << b << "]=" << len[b] << " xat=" << xat << "\n");
	xat += len[b];
	if(at <= xat) //In this block ?
	  break;
      }
      if(at < xat){
	IntT toGo = xat - at;
	IntT done = len[b] - toGo;
	ONDEBUG(cerr << "Reading " << toGo << " bytes to complete the block " << b << " xat=" << xat << " done=" << done << " toGo=" << toGo << "\n");
	IntT x = Read(&(buffer[b][done]),toGo);
	if(x < 0)
	  return at;
	at += x;
	if(x < toGo)
	  return at; // Some serious error must have occured to stop 'Read'
      }
      ONDEBUG(cerr << "Reading vector b=" << b << " n=" << n << " \n");
      RavlAssert(xat == at);
      b++;
      int blocksToGo = n - b;
      if(blocksToGo == 0)
	break; // We're done!

      if(!WaitForRead())
	return at;

      int x = readv(fd,&(vecp[b]),blocksToGo);
      if(x == 0) {
	SysLog(SYSLOG_INFO) << "SocketBodyC::ReadV(). Socket closed. fd=" << fd;
	break;
      }
      if(x < 0) {
	if(!CheckErrors("SocketBodyC::ReadV()"))
	  return at;
	// Temporary error. Retry.
	x = 0;
      }
      at += x;
    } while(at < total) ;
    return at;
  }

  //: Write multiple buffers

  IntT SocketBodyC::WriteV(const char **buffer,IntT *len,int n) {
    if(n == 0) return 0;
    struct iovec vecBuf[101];
    struct iovec *vecp = vecBuf;
    SArray1dC<iovec> vecArray;
    IntT at = 0,total = 0;
    if(n > 100) {
      vecArray = SArray1dC<iovec>(n);
      vecp = &(vecArray[0]);
    }
    for(int i = 0;i < n;i++) {
      vecp[i].iov_base = (char *) buffer[i];
      vecp[i].iov_len = len[i];
      total += len[i];
    }

    while(fd >= 0) {
      if(!WaitForWrite())
	return at;

      //cerr << "writev(" << fd << "," << (void *) vecp << "," << n << ");\n";
      if((at = writev(fd,vecp,n)) > 0)
	break;
      if(!CheckErrors("SocketBodyC::WriteV()"))
	return 0;
      // Temporary failure, try again.
    }

    if(at == total || fd < 0)
      return at; // All done ?

    ONDEBUG(SysLog(SYSLOG_WARNING) << "SocketBodyC::WriteV(), Socket write interupted, attempting to recover. (Relatively untested code.) ");

    // Write in 1 lump failed, break it up.
    int b = 0,xat = 0;
    do {
      for(;b < n;b++) {
	xat += len[b];
	if(at <= xat) //In this block ?
	  break;
      }
      if(at < xat){
	IntT toGo = xat - at;
	IntT done = len[b] - toGo;
	ONDEBUG(cerr << "Reading " << toGo << " bytes to complete the block " << b << " xat=" << xat << " done=" << done << " toGo=" << toGo << "\n");
	IntT x = Write(&(buffer[b][done]),toGo);
	if(x <= 0) return at;
	at += x;
	if(x < toGo) return at; // Some serious error must have occured to stop 'Write'
      }
      RavlAssert(xat == at);
      b++;
      int blocksToGo = n - b;
      if(blocksToGo == 0)
	break; // We're done!

      if(!WaitForWrite())
	return at;
      int x = writev(fd,&(vecp[b]),blocksToGo);
      if(x < 0) {
	if(!CheckErrors("SocketBodyC::WriteV()"))
	  return at;
	x = 0;
      }
      at += x;
    } while(at < total) ;
    return at;
  }

  //: Write some bytes to a stream.

  IntT SocketBodyC::Write(const char *buff,UIntT size) {
    UIntT at = 0;
    while(at < size && fd >= 0) {
      if(!WaitForWrite())
	return at;
      int n = write(fd,&(buff[at]),size - at);
      if(n < 0) {
	if(!CheckErrors("SocketBodyC::Write()"))
	  return at;
	n = 0;
      }
      at += n;
    }
    return at;
  }

}
#endif
