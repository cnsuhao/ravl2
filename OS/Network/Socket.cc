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

static const float g_defaultTimeout = 180;

namespace RavlN {

  //: Open socket.

  SocketBodyC::SocketBodyC(StringC name,bool nserver)
    : UnixStreamIOC(-1,g_defaultTimeout,g_defaultTimeout,false),
      server(nserver),
      addr(0)
  {
    int at = name.index(':');
    if(at < 0) {
      SysLog(SYSLOG_ERR) << "SocketBodyC::SocketBodyC(), No port no in '" << name << "' ";
      return ;
    }
    StringC host = name.before(at);
    StringC pn(name.after(at));
    int portno = atoi(pn);
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "Opening connection '" << host << "' port " << portno << " ");
    if(server)
      OpenServer(host,portno);
    else
      OpenClient(host,portno);
  }

  //: Open socket.

  SocketBodyC::SocketBodyC(StringC name,UIntT portno,bool nserver)
    : UnixStreamIOC(-1,g_defaultTimeout,g_defaultTimeout),
      server(nserver),
      addr(0)
  {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "Opening connection '" << name << "' port " << portno << " ");
    if(server)
      OpenServer(name,portno);
    else
      OpenClient(name,portno);
  }


  //: Open socket.

  SocketBodyC::SocketBodyC(struct sockaddr *naddr,int nfd,bool nserver)
    : UnixStreamIOC(nfd,g_defaultTimeout,g_defaultTimeout),
      server(nserver),
      addr(naddr)
  {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "SocketBodyC::SocketBodyC(), fd = " << m_fd );
  }

  //: Open socket.

  SocketBodyC::~SocketBodyC()  {
    Close(); // Tidy up.
  }

  //: Close the socket.

  void SocketBodyC::Close() {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "SocketBodyC::Close() dontclose=" << m_dontClose << " fd=" << m_fd << " ");
    UnixStreamIOC::Close();
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
      SysLog(SYSLOG_WARN) << "WARNING: Failed to get tcp protocol number. Guessing a value of 6. \n";
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
    if(setsockopt(m_fd,tcpprotocolno,TCP_CORK,&n,sizeof(int)) != 0) {
      SysLog(SYSLOG_WARNING) << "SocketBodyC::Cork(), Failed. errno=" << errno <<"\n";
    }
#else
    if(setsockopt(m_fd,tcpprotocolno,TCP_NODELAY,&n,sizeof(int)) != 0) {
      SysLog(SYSLOG_WARNING) << "SocketBodyC::Cork(), Failed. errno=" << errno <<"\n";
    }
#endif
    return true;
  }

  //: Send data as soon as possible.

  void SocketBodyC::SetNoDelay() {
    // Disable delays.
    int n = 1;
    static int tcpprotocolno = GetTCPProtocolNumber();
    if(setsockopt(m_fd,tcpprotocolno,TCP_NODELAY,&n,sizeof(int)) != 0) {
      SysLog(SYSLOG_WARNING) << "SocketBodyC::SetNoDelay(), Failed. errno=" << errno <<" '" << strerror(errno) << "' on fd= " << m_fd << "\n";
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
      ONDEBUG(SysLog(SYSLOG_DEBUG) << " Looking for '" << name << "'\n");
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
        ONDEBUG(SysLog(SYSLOG_DEBUG) << "Failed to get hostname, retrying. \n");
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
    SysLog(SYSLOG_DEBUG) << "Offical hostname: '" << result->h_name << "' h_length: '" << result->h_length << "' ";
    //SysLog(SYSLOG_DEBUG) << "h_addr_list: '" << result->h_addr_list[0] << "' ";
#endif
    sin.sin_addr.s_addr = ((struct in_addr *)result->h_addr_list[0])->s_addr;
    sin.sin_family = ent.h_addrtype;

    ONDEBUG(SysLog(SYSLOG_DEBUG) << "Got host data..  Addr:'" << inet_ntoa(sin.sin_addr) << "' ");

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
	  throw ExceptionNetC("GetHostByName(),ERROR: Buffer requested too large. Failing. ");
	}
	hostentData = new char [buffSize];
	continue;
      }
      SysLog(SYSLOG_ERR) << "WARNING: Error while attempting to find hostname from ip address. errno=" << error << " ";
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
      SysLog(SYSLOG_ERR) << "Failed to create socket. " << errno << " ";
      return -1;
    }
    return sock;
  }


  int SocketBodyC::OpenClient(const char *name,IntT portNo) {
    struct sockaddr_in sin = {PF_INET};
    if(!GetHostByName(name,sin)) {
      SysLog(SYSLOG_ERR) << "Failed to lookup hostname '" << name << "' ";
      return -1;
    }
    if((m_fd = OpenSocket(sin,portNo)) < 0)
      return -1;
    sin.sin_port = htons(portNo);
    int retryLimit = 10;
    while(connect(m_fd, (sockaddr*)&sin, sizeof(sin)) < 0) {
      // Sometimes its worth trying a again a few times.
      if((errno == EAGAIN || errno == EINTR || errno==ETIMEDOUT) && retryLimit-- > 0) {
        ONDEBUG(SysLog(SYSLOG_DEBUG) << "Connect failed, EAGAIN. errno=" << errno << " ");
        Sleep(0.1);
        continue;
      }
      Close();
#if DODEBUG
      if(errno == EADDRINUSE) {
        SysLog(SYSLOG_DEBUG) << "Address in use. " << m_fd ;
        return -1;
      }
      if(errno == ECONNREFUSED) {
        SysLog(SYSLOG_DEBUG) << "Connection refused. " << m_fd;
        return -1;
      }
      SysLog(SYSLOG_DEBUG) << "Connect failed. " << m_fd;
#endif
      return -1;
    }

    ONDEBUG(SysLog(SYSLOG_DEBUG) << "SocketBodyC::OpenClient(), Connected to '" << name  << "' ");
    if(addr != 0)
      delete [] (char *) addr;
    addr = (struct sockaddr *) new char [sizeof(struct sockaddr)];
    memcpy((char *) addr,(sockaddr*)&sin,sizeof(struct sockaddr));
    //SetNonBlocking(true);
    return m_fd;
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
    if((m_fd = OpenSocket(sin,portNo)) < 0)
      return -1;
    sin.sin_port = htons(portNo);
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "Binding name. ");
    if(bind(m_fd,(struct sockaddr*)&sin, sizeof(sockaddr)) < 0) {
      SysLog(SYSLOG_DEBUG) << "Bind failed. errno=" << errno << " ";
      SysLog(SYSLOG_DEBUG) << "Error:" << strerror(errno);
      Close();
      return -1;
    }
    return m_fd;
  }

  //: Listen for a connection from a client.
  // Can only be used on server sockets.

  SocketC SocketBodyC::Listen(bool block,int backLog) {
    RavlAssert(server); // Must be a server socket.
    if(m_fd < 0)
      return SocketC(); // Not open!
    do {
      ONDEBUG(SysLog(SYSLOG_DEBUG) << "Listening. ");
      if(listen(m_fd, backLog) < 0) {
	SysLog(SYSLOG_ERR) << "Listen failed." << errno << " ";
	return SocketC(); // Failed.
      }
      ONDEBUG(SysLog(SYSLOG_DEBUG) << "Accepting. ");
      socklen_t addrBuffSize = sizeof(sockaddr) + 256;//FIXME why 256? need to use sockaddr_in instead
      struct sockaddr *cn_addr = (struct sockaddr *) new char [addrBuffSize];
      do {
	int nfd = accept(m_fd,cn_addr, &addrBuffSize);
	ONDEBUG(SysLog(SYSLOG_DEBUG) << "Got connection. Server fd=" << m_fd << "  Client fd=" << nfd);
	if(nfd >= 0)
	  return SocketC(cn_addr,nfd); // Socket accepted ok.
	// Recoverable error ?
      } while(errno == EAGAIN || errno == EINTR) ;
      SysLog(SYSLOG_ERR) << "ERROR: Failed to accept connection. errno=" << errno << " "; ;
      delete [] (char *) cn_addr;
    } while(block);
    return SocketC();
  }

  //: Get host name

  StringC SocketBodyC::ConnectedHost() {
    StringC ret("-failed-");
    if(m_fd == 0)
      return ret;
    socklen_t namelen = sizeof(sockaddr) + 256;
    struct sockaddr *name = (struct sockaddr *) new char[namelen];
    if(getpeername(m_fd,name,&namelen) != 0)
    {
      delete [] name;
      SysLog(SYSLOG_ERR) << "SocketBodyC::ConnectedHost(), gerpeername failed. Error=" << errno << " ";
      return StringC("unknown");
    }
    GetHostByAddr(*name,namelen,ret);
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "Hostname=" << ret << " ");
    delete [] (char*) name;
    return ret;
  }

  //: Get other port number.

  IntT SocketBodyC::ConnectedPort() {
    if(addr == 0)
      return 0;
    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);
    getpeername(m_fd, (sockaddr*) &name, &namelen );
    IntT ret = ntohs( name.sin_port );
    return ret;
  }


}
#endif
