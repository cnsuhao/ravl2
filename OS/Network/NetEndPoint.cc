// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlNet
//! file="Ravl/OS/Network/NetEndPoint.cc"

#include "Ravl/config.h"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/OS/NetEndPoint.hh"
#include "Ravl/OS/NetStream.hh"
#include "Ravl/OS/NetMsgCall.hh"
#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/OS/SysLog.hh"
#include "Ravl/OS/Date.hh"

//#include "Ravl/BinStream.hh"
//#include "Ravl/BinString.hh"

#include <stdlib.h>
#include <unistd.h>
#include <sys/uio.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  NetEndPointBodyC::NetEndPointBodyC(const StringC &addr,bool nautoInit) 
    : skt(addr,false),
      transmitQ(15),
      receiveQ(5),
      shutdown(false),
      autoInit(nautoInit),
      useBigEndianBinStream(RAVL_BINSTREAM_ENDIAN_BIG)
  {
    localInfo.appName = SysLogApplicationName();
    Init(skt); 
  }
  
  //:  Constructor.
  
  NetEndPointBodyC::NetEndPointBodyC(SocketC &nskt,bool nautoInit)
    : skt(nskt),
      transmitQ(15),
      receiveQ(5),
      shutdown(false),
      autoInit(nautoInit),
      useBigEndianBinStream(RAVL_BINSTREAM_ENDIAN_BIG)
  {
    localInfo.appName = SysLogApplicationName();
    Init(nskt); 
  }
  
  //: Constructor.
  
  NetEndPointBodyC::NetEndPointBodyC(SocketC &socket,const StringC &protocolName,const StringC &protocolVersion,bool nautoInit)
    : skt(socket),
      transmitQ(15),
      receiveQ(5),
      shutdown(false),
      autoInit(nautoInit),
      localInfo(protocolName,protocolVersion),
      useBigEndianBinStream(RAVL_BINSTREAM_ENDIAN_BIG)
  { 
    localInfo.appName = SysLogApplicationName();
    Init(skt); 
  }
  
  //: Constructor.
  
  NetEndPointBodyC::NetEndPointBodyC(const StringC &address,const StringC &protocolName,const StringC &protocolVersion,bool nautoInit) 
    : skt(address),
      transmitQ(15),
      receiveQ(5),
      shutdown(false),
      autoInit(nautoInit),
      localInfo(protocolName,protocolVersion),
      useBigEndianBinStream(RAVL_BINSTREAM_ENDIAN_BIG)
  { 
    localInfo.appName = SysLogApplicationName();
    Init(skt); 
  }
  
  //: Default constructor.
  
  NetEndPointBodyC::NetEndPointBodyC() 
    : transmitQ(15),
      receiveQ(5),
      shutdown(false),
      useBigEndianBinStream(RAVL_BINSTREAM_ENDIAN_BIG)
  {}
  
  //: Destructor.
  
  NetEndPointBodyC::~NetEndPointBodyC() {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::~NetEndPointBodyC(), Called. " << (void *) this);
    setupComplete.Post(); // Make sure nothings waiting for setup to complete.
  }
  
  //: Setup and startup the aproprate threads.
  
  //  NetMsgRegisterItemC<NetMsgCall1C<NetEndPointC,StringC,&NetEndPointC::MsgInit> > netMsgReg(1,"NetEndPointC.MsgInit");
  
  //: Register new message handler.
  
  bool NetEndPointBodyC::Register(const NetMsgRegisterC &nmsg) {
    MutexLockC lock(accessMsgReg);
#if RAVL_CHECK
    if(msgReg.IsElm(nmsg.Id())) {
      NetMsgRegisterC oldMsg;
      msgReg.Lookup(nmsg.Id(),oldMsg);
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::Register(), WARNING: Overriding handling of message id:" << nmsg.Id() << " Name=" << nmsg.Name() << " Old name=" << oldMsg.Name();
    }
#endif
    msgReg[nmsg.Id()] = nmsg;
    return true;
  }
  
  //: Search for message decode/encode of type 'id'.
  
  NetMsgRegisterC NetEndPointBodyC::Find(UIntT msgTypeID) const {
    // Check local decode table.
    MutexLockC lock(accessMsgReg);
    NetMsgRegisterC *msg = const_cast<NetMsgRegisterC *>(msgReg.Lookup(msgTypeID));
    if(msg != 0) 
      return *msg;
    // Check global decode table.
    msg = NetMsgRegisterC::MsgTypes().Lookup(msgTypeID);
    if(msg != 0) 
      return *msg;
    return NetMsgRegisterC();
  }
  
  //: Send init message.
  
  void NetEndPointBodyC::SndInit(StringC &user) {
    const char *hostType = getenv("HOSTTYPE");
    if(hostType == 0)
      hostType = "*unknown*";
    localInfo.hostType = StringC(hostType);
    
    Send(1,user,localInfo);
  }
  
  bool NetEndPointBodyC::Init(SocketC &nskt) {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::Init(), Called. " << (void *) this);
    skt = nskt;
    if(!skt.IsOpen()) {
      ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::Init(), Socket not opened. ");
      return false;
    }
    skt.SetNonBlocking(true); // Make socket non-blocking.
    
    RegisterR(1,StringC("Init"),*this,&NetEndPointBodyC::MsgInit);
    
    if(autoInit) {
      const char *un = getenv("USER"); // This isn't really secure!!
      if(un == 0)
	un = "*unknown*";
      StringC auser(un);
      SndInit(auser);
    }
    
    //Transmit(initMsg);
    
    NetEndPointC me(*this);
    LaunchThread(me,&NetEndPointC::RunReceive);
    LaunchThread(me,&NetEndPointC::RunTransmit);
    LaunchThread(me,&NetEndPointC::RunDecode);
    return true;
  }
  
  //: Initalise link.
  
  bool NetEndPointBodyC::Ready() {
    if(autoInit)
      return true;
    autoInit = true;
    
    const char *un = getenv("USER"); // This isn't really secure!!
    if(un == 0)
      un = "*unknown*";
    StringC auser(un);
    
    SndInit(auser);
    
    return true;
  }
  
  //: Wait for setup to complete.
  
  bool NetEndPointBodyC::WaitSetupComplete(RealT timeOut) {
    if(!setupComplete.Wait(timeOut)) {
      if(!IsOpen()) {
	
	return false;
      }
    }
    return true;
  }
  
  //: Wait for the transmit queue to clear.
  
  bool NetEndPointBodyC::WaitTransmitQClear() {
    transmitQ.Put(NetPacketC()); // Put an empty packet to ensure all is sent before we return.
    while(IsOpen() && !transmitQ.IsEmpty())
      Sleep(0.1);
    return true;
  }

  //: Send a 0 paramiter message.
  
  bool NetEndPointBodyC::Send(UIntT id) {
    BufOStreamC os;
    BinOStreamC bos(os);
    bos.UseBigEndian(useBigEndianBinStream);
    bos << id ;
    Transmit(NetPacketC(os.Data()));
    return true;
  }
  
  
  //: Close connection.
  
  bool NetEndPointBodyC::Close() {
    ONDEBUG(SysLog(SYSLOG_ERR) << "NetEndPointBodyC::Close(), Called shutdown=" << shutdown << " RefCount=" << References());
    if(!shutdown) {
      MutexLockC lock(accessMsgReg);
      shutdown = true;
      msgReg.Empty(); 
      skt.Close();
      receiveQ.Put(NetPacketC()); // Put an empty packet to indicate shutdown.
      transmitQ.Put(NetPacketC()); // Put an empty packet to indicate shutdown.
    }
    return true;
  }
  
  static const StringC streamHeaderBigEndian ="\n<ABPS>\n";
  static const StringC streamHeaderLittleEndian ="\n<RBPS>\n";
  
  //: Handle packet transmition.
  
  bool NetEndPointBodyC::RunTransmit() {
    skt.SetNoDelay(); // Send packets asap.
    int wfd = skt.Fd();
    if(wfd < 0) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: No connection. ";
      return false;       
    }
#if RAVL_BINSTREAM_ENDIAN_LITTLE
    StringC streamHeader = streamHeaderLittleEndian;
#else
    StringC streamHeader = streamHeaderBigEndian;
#endif
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunTransmit(), Sending header '" << streamHeader << "' ");
    
    // Write stream header.
    if(!WriteData(wfd,streamHeader,streamHeader.Size())) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: Failed to write header. ";
      return false;
    }
    // Wait still we got a stream header from peer 
    if(!gotStreamType.Wait(30)) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: Timeout waiting for stream header. ";
      Close();
      return false;
    }
    
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunTransmit() Stream mode:" << streamType );
    
#if RAVL_BINSTREAM_ENDIAN_LITTLE
    // Check peer protocol.
    if(streamType == "<ABPS>") { // Client using an old big endian protocol ?
#if RAVL_ENDIAN_COMPATILIBITY
      // We're in compatiblity mode, send old header.
      // If so, write <ABPS> header.
      useBigEndianBinStream = true;
      if(!WriteData(wfd,streamHeaderBigEndian,streamHeader.Size())) {
	SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: Failed to write header. ";
	return false;
      }
#else
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: Incompatible protocol. ";
      Close();
      return false;
#endif
    }
#else
    if(streamType == "<RBPS>") { // Client using an old big endian protocol ?
#if RAVL_ENDIAN_COMPATILIBITY
      // We're in compatiblity mode, send old header.
      // If so, write <ABPS> header.
      useBigEndianBinStream = false;
      if(!WriteData(wfd,streamHeaderBigEndian,streamHeader.Size())) {
	SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: Failed to write header. ";    
	return false;
      }
#else
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: Incompatible protocol. ";
      Close();
      return false;
#endif
    }
#endif
    
    ONDEBUG(SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), Starting transmit loop. ");
    try {
      while(!shutdown) {
	NetPacketC pkt;
	if(!transmitQ.Get(pkt,1.5))
	  continue;
	if(shutdown)
	  break;
	if(!pkt.IsValid())
	  continue;
	//ONDEBUG(cerr << "  Transmit packet:\n");
	//ONDEBUG(pkt.Dump(cerr));
	UIntT size = pkt.Size();

#if RAVL_LITTLEENDIAN
	if(useBigEndianBinStream)
	  size = bswap_32(size);
#else
	if(!useBigEndianBinStream)
	  size = bswap_32(size);	
#endif
	// Write length of packet.
	if(!WriteData(wfd,
		      (char *)&size,sizeof(size),  // First buffer: Size
		      &(pkt.Data()[0]),pkt.Size()) // Second buffer: Data.
	   )
	  break;	
	ONDEBUG(SysLog(SYSLOG_DEBUG) << "  Sent packet. ");
      }
    } catch(ExceptionC &e) {
      SysLog(SYSLOG_WARNING) << "RAVL Exception :'" << e.what() << "' ";
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::RunTransmit(), Exception caught, terminating link. ";
    } catch(exception &e) {
      SysLog(SYSLOG_WARNING) << "C++ Exception :'" << e.what() << "'";
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::RunTransmit(), Exception caught, terminating link. ";
    } catch(...) {
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::RunTransmit(), Exception caught, terminating link. ";
    }
    //if(!nos)
    // cerr << "NetEndPointBodyC::RunTransmit(), Connection broken ";    
    Close();
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunTransmit(), Terminated. "); 
    return true;
  }
  
  //: Read some bytes from a stream.
  
  bool NetEndPointBodyC::ReadData(int nfd,char *buff,UIntT size) {
    UIntT at = 0;
    fd_set rfds;
    fd_set efds;
    FD_ZERO(&rfds);
    struct timeval tv;
    while(at < size && !shutdown) {
#if 1
      //ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::ReadData(), Waiting for select. ");
      FD_SET(nfd,&rfds);
      tv.tv_sec = 5;
      tv.tv_usec = 0;
      if(select(nfd+1,&rfds,0,0,&tv) == 0) {
	//ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::ReadData(), Select timeout. ");
	continue;
      }
      //ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::ReadData(), Waiting for read. Read=" << (int) FD_ISSET(nfd, &rfds) << " Except=" << (int) FD_ISSET(nfd, &efds) << "\n");
#endif
      
      int n = read(nfd,&(buff[at]),size - at);
      if(n == 0) { // Linux indicates a close by returning 0 bytes read.  Is this portable ??
	ONDEBUG(SysLog(SYSLOG_DEBUG) << "Socket close. ");
	return false;
      }
      if(n < 0) {
	ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::ReadData(), Error on read. ");
	if(errno == EINTR || errno == EAGAIN)
	  continue;
#if RAVL_OS_LINUX
	char buff[256];
	SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::ReadData(), Error reading from socket :" << errno << " '" << strerror_r(errno,buff,256) << "'";
#else
	SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::ReadData(), Error reading from socket :" << errno;
#endif
	return false;
      }
      at += n;
    }
    return !shutdown;
  }
  
  //: Write 2 buffers to file descriptor.
  
  bool NetEndPointBodyC::WriteData(int nfd,
				   const char *buff1,UIntT size1,
				   const char *buff2,UIntT size2) {
    
    struct iovec vec[2];
    vec[0].iov_base = (void*) buff1;
    vec[0].iov_len = size1;
    vec[1].iov_base = (void*) buff2;
    vec[1].iov_len = size2;
    UIntT at = 0;
    UIntT total = size1 + size2;

    fd_set wfds;
    FD_ZERO(&wfds);
    
    do {
#if 1
      FD_SET(nfd,&wfds);
      if(select(nfd+1,0,&wfds,0,0) == 0)
	continue;
#endif
      at = writev(nfd,vec,2);
      if(at > 0)
	break;
      if(errno != EINTR && errno != EAGAIN) {
#if RAVL_OS_LINUX
	char buff[256];
	SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::WriteData(),(2) Error writing to socket :" << errno << " '" << strerror_r(errno,buff,256) << "' ";
#else
	SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::WriteData(),(2) Error writing to socket :" << errno;
#endif
	return false;
      }
      // Temporary failure, try again.
    } while(true);
    
    if(at == total)
      return true; // Everything done ok.
    // Write of all data failed, try and sort things out.
    // Does this ever really happen ??
    SysLog(SYSLOG_WARNING) << "WARNING: Partial data write in NetEndPointBodyC::WriteData(). ";
    if(at < size1) { // Written all of first packet ?
      if(!WriteData(nfd,&(buff1[at]),size1-at))
	return false;
      at = size1;
    }
    // Write second vector.
    at -= size1;
    return WriteData(nfd,&(buff2[at]),size2-at);
  }
  
  //: Write some bytes to a stream.
  
  bool NetEndPointBodyC::WriteData(int nfd,const char *buff,UIntT size) {
    UIntT at = 0;
    while(at < size && !shutdown) {
      int n = write(nfd,&(buff[at]),size - at);
      if(n < 0) {
	ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunReceive(), Error on read. ");
	if(errno == EINTR || errno == EAGAIN)
	  continue;
#if RAVL_OS_LINUX
	char buff[256];
	SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::WriteData(),(2) Error writing to socket :" << errno << " '" << strerror_r(errno,buff,256) << "' ";
#else
	SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::WriteData(),(2) Error writing to socket :" << errno;
#endif
	return false;
      }
      at += n;
    }    
    return !shutdown;
  }
  
  //: Handle packet reception.
  
  bool NetEndPointBodyC::RunReceive() {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunReceive(), Started. ");
    
    int rfd = skt.Fd();
    if(rfd < 0) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunReceive(), ERROR: No connection. ";
      return false;       
    }
    StringC recvStreamType;
    {
      // Look for ABPS
      const char *str = "<ABPS>\n";
      char buff;
      int state = 0;
      streamType = "<ABPS>";
      do {
	ONDEBUG(SysLog(SYSLOG_DEBUG) << "State=" << state;)
	if(!ReadData(rfd,&buff,1))
	  break;
	if(str[state] != buff) {
	  if(state != 1 || buff != 'R') {
	    if(str[0] == buff)
	      state = 1;
	    else 
	      state = 0;
	    continue;
	  } else {
	    if(buff == 'R' && state == 1)
	      streamType = "<RBPS>";
	  }
	}
	state++;
      } while(str[state] != 0) ;
    }
    gotStreamType.Post();
    
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunReceive(), Connection type confirmed. '" << streamType << "' ");
    
    try {
      while(!shutdown) {
	UIntT size;
	if(!ReadData(rfd,(char *) &size,sizeof(UIntT))) {
	  if(!shutdown)
	    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunRecieve(), Read size failed. Assuming connection broken. ");
	  break;
	}
	if(size == 0)
	  continue;
#if RAVL_LITTLEENDIAN
	//SysLog(SYSLOG_DEBUG) << "Little endian. \n";
	if(useBigEndianBinStream)
	  size = bswap_32(size);
#else
	if(!useBigEndianBinStream)
	  size = bswap_32(size);
#endif
	ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunRecieve(), Read " << size << " bytes. UseBigEndian:" << useBigEndianBinStream << " BigEdian:" << RAVL_ENDIAN_BIG << " "); 
	SArray1dC<char> data(size);
	if(!ReadData(rfd,(char *) &(data[0]),size)) {
	  ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunRecieve(), Read data failed. Assuming connection broken. "); 
	  break;
	}
	NetPacketC pkt(data);
	receiveQ.Put(pkt);
      }
    } catch(ExceptionC &e) {
      SysLog(SYSLOG_ERR) << "RAVL Exception :'" << e.what() << "' ";
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunRecieve(), Exception caught, terminating link. ";
    }
#if 0
    catch(exception &e) {
      SysLog(SYSLOG_ERR) << "C++ Exception :'" << e.what() << "'";
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunRecieve(), Exception caught, terminating link. ";
    } catch(...) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunRecieve(), Exception caught, terminating link. ";
    }
#endif
 
#if 0
    if(!nis)
      SysLog(SYSLOG_INFO) << "NetEndPointBodyC::RunReceive(), Connection broken ";
#endif
    MutexLockC lock(accessMsgReg);
    if(connectionBroken.IsValid()) { // Got a callback ?
      TriggerC call = connectionBroken; // Make copy of trigger in case its overwritten.
      connectionBroken.Invalidate(); // Not needed after this.
      lock.Unlock();
      call.Invoke();
      //      MutexLockC lock(accessMsgReg);
    } else
      lock.Unlock();
    Close();
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunRecieve(), Terminated "); 
    return true;
  }
  
  
  //: Decodes incoming packets.
  
  bool NetEndPointBodyC::RunDecode() {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunDecode(), Startup. "); 
    NetPacketC pkt;
    NetEndPointC me(*this);
    try {
      while(!shutdown) {
	NetPacketC pkt;
	if(!receiveQ.Get(pkt,1.5))
	  continue;
	if(shutdown)
	  break;
	if(!pkt.IsValid()) 
	  continue;
	//ONDEBUG(cerr << "Recieved packet:");
	//ONDEBUG(pkt.Dump(cerr));
	// Decode....
	BinIStreamC is(pkt.DecodeStream());
	is.UseBigEndian(useBigEndianBinStream);
	UIntT msgTypeID = 0;
	is >> msgTypeID;
	ONDEBUG(SysLog(SYSLOG_DEBUG) << "Incoming packet type id:" << msgTypeID );
	// Check local decode table.
	NetMsgRegisterC msg = Find(msgTypeID);
	if(!msg.IsValid()) {
	  SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunDecode(), ERROR: Don't know how to decode message type " << msgTypeID;
	  continue;
	}  
	ONDEBUG(SysLog(SYSLOG_DEBUG) << "Decoding incoming packet. Type: '" << msg.Name() << "'"); 
	msg.Decode(me,is); 

#if RAVL_COMPILER_MIPSPRO // ignore Tell() = -1 on MIPS 
  	if(  ((UIntT) is.Tell() != pkt.Size()) && (is.Tell() != -1) )  
	  { SysLog(SYSLOG_ERR) << "WARNING: Not all of packet processed Stream:" << is.Tell() << " Packet size:" << pkt.Size(); }
#else
	if((UIntT) is.Tell() != pkt.Size()) 
	  { SysLog(SYSLOG_ERR) << "WARNING: Not all of packet processed Stream:" << is.Tell() << " Packet size:" << pkt.Size(); }
#endif 
      }
    } catch(ExceptionOperationFailedC &ex) {
      // protocol error...
      Close();
    } catch(ExceptionC &e) {
      SysLog(SYSLOG_WARNING) << "RAVL Exception :'" << e.what() << "'";
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::RunDecode(), Exception caught, terminating link. ";
    } 
#if 0
    catch(exception &e) {
      SysLog(SYSLOG_WARNING) << "C++ Exception :'" << e.what() << "'";
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::RunDecode(), Exception caught, terminating link. ";
    } catch(...) {
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::RunDecode(), Exception caught, terminating link. ";
    }
#endif
    transmitQ.Put(NetPacketC()); // Put an empty packet to indicate shutdown.
    // Can't to much about recieve...
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunDecode(), Terminated. "); 
    return true;
  }
    
    
  //: Init message.
  
  bool NetEndPointBodyC::MsgInit(StringC &user,NetClientInfoC &nPeerInfo) {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::MsgInit(), Called. User:" << user);
    remoteUser = user;
    peerInfo = nPeerInfo;
    if(peerInfo.ProtocolName() != localInfo.ProtocolName()) {
      SysLog(SYSLOG_ERR) << "ERROR: Protocol mismatch Local='" << localInfo.ProtocolName() << "' Remote='" << peerInfo.ProtocolName() << "'";
      throw ExceptionOperationFailedC("Failed to connect, protocol error. ");
    }
    setupComplete.Post();
    return true;
  }
  
  //: Set new trigger to be called if connection broken.
  
  void NetEndPointBodyC::ConnectionBroken(const TriggerC &trigger) {
    MutexLockC lock(accessMsgReg);
    connectionBroken = trigger;
  }
  
  //:------------------------------------------------------------------------------

  //: Constructor.
  
  NetClientInfoC::NetClientInfoC(const StringC &nprotocolName,
				 const StringC &nprotocolVersion,
				 const StringC &nappName,
				 const StringC &nappVersion,
				 const StringC &nhostType
				 )
    : protocol(nprotocolName),
      protocolVersion(nprotocolVersion),
      appName(nappName),
      appVersion(nappVersion),
      hostType(nhostType)
  {}
  
  //: Default Constructor.
  
  NetClientInfoC::NetClientInfoC()
    : protocol("User Protocol"),
      protocolVersion("0.0"),
      appName("Default"),
      appVersion("0.0"),
      hostType("unknown")
  {}
  
  BinOStreamC &operator<<(BinOStreamC &strm,const NetClientInfoC &info) {
    IntT version = 0;
    strm << version;
    strm << info.protocol << info.protocolVersion;
    strm << info.appName << info.appVersion;
    return strm;
  }
  //: Write info to a stream.
  
  BinIStreamC &operator>>(BinIStreamC &strm,NetClientInfoC &info) {
    IntT version = 0;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("Unexpected version number in NetClientInfoC io. ");
    strm >> info.protocol >> info.protocolVersion;
    strm >> info.appName >> info.appVersion;
    return strm;
  }
  //: Read info from a stream.
  
}
