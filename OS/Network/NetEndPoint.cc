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
      autoInit(nautoInit)
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
      autoInit(nautoInit)
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
      localInfo(protocolName,protocolVersion)
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
      localInfo(protocolName,protocolVersion)
  { 
    localInfo.appName = SysLogApplicationName();
    Init(skt); 
  }
  
  //: Default constructor.
  
  NetEndPointBodyC::NetEndPointBodyC() 
    : transmitQ(15),
      receiveQ(5),
      shutdown(false)
  {}
  
  //: Destructor.
  
  NetEndPointBodyC::~NetEndPointBodyC() {
    //cerr << "NetEndPointBodyC::~NetEndPointBodyC(), Called. \n";
    setupComplete.Post(); // Make sure nothings waiting for setup to complete.
  }
  
  //: Setup and startup the aproprate threads.
  
  //  NetMsgRegisterItemC<NetMsgCall1C<NetEndPointC,StringC,&NetEndPointC::MsgInit> > netMsgReg(1,"NetEndPointC.MsgInit");
  
  //: Register new message handler.
  
  bool NetEndPointBodyC::Register(const NetMsgRegisterC &nmsg) {
    MutexLockC lock(accessMsgReg);
#if RAVL_CHECK
    if(msgReg.IsElm(nmsg.Id()))
      cerr << "NetEndPointBodyC::Register(), WARNING: Overriding handling of message id:" << nmsg.Id() << "\n";
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
    skt = nskt;
    if(!skt.IsOpen()) {
      ONDEBUG(cerr << "NetEndPointBodyC::Init(), Socket not opened. \n");
      return false;
    }
    
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
  
  bool NetEndPointBodyC::WaitSetupComplete() {
    setupComplete.Wait();
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
    bos << id ;
    Transmit(NetPacketC(os.Data()));
    return true;
  }
  
  
  //: Close connection.
  
  bool NetEndPointBodyC::Close() {
    if(!shutdown) {
      MutexLockC lock(accessMsgReg);
      msgReg.Empty(); 
      shutdown = true;
      skt.Close();
      receiveQ.Put(NetPacketC()); // Put an empty packet to indicate shutdown.
      transmitQ.Put(NetPacketC()); // Put an empty packet to indicate shutdown.
    }
    return true;
  }
  
  static const StringC streamHeader ="\n<ABPS>\n";
  
  //: Handle packet transmition.
  
  bool NetEndPointBodyC::RunTransmit() {
    skt.SetNoDelay(); // Send packets asap.
    int wfd = skt.Fd();
    if(wfd < 0) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: No connection. \n";    
      return false;       
    }
    if(!WriteData(wfd,streamHeader.chars(),streamHeader.Size())) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: Failed to write header. \n";    
      return false;
    }
    
    ONDEBUG(cerr << "NetEndPointBodyC::RunTransmit(), Starting transmit loop. \n");
    try {
      while(!shutdown) {
	NetPacketC pkt;
	if(!transmitQ.Get(pkt,1.5))
	  continue;
	if(shutdown)
	  break;
	if(!pkt.IsValid())
	  continue;
	ONDEBUG(cerr << "  Transmit packet:\n");
	ONDEBUG(pkt.Dump(cerr));
	UIntT size = pkt.Size();
#if RAVL_LITTLEENDIAN
	size = bswap_32(size);
#endif
	// Write length of packet.
	if(!WriteData(wfd,
		      (char *)&size,sizeof(size),  // First buffer: Size
		      &(pkt.Data()[0]),pkt.Size()) // Second buffer: Data.
	   )
	  break;	
	ONDEBUG(cerr << "  Sent packet. \n");
      }
    } catch(ExceptionC &e) {
      SysLog(SYSLOG_WARNING) << "RAVL Exception :'" << e.what() << "'\n";
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::RunTransmit(), Exception caught, terminating link. \n";
    } catch(exception &e) {
      SysLog(SYSLOG_WARNING) << "C++ Exception :'" << e.what() << "'\n";
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::RunTransmit(), Exception caught, terminating link. \n";
    } catch(...) {
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::RunTransmit(), Exception caught, terminating link. \n";
    }
    //if(!nos)
    // cerr << "NetEndPointBodyC::RunTransmit(), Connection broken \n";    
    Close();
    ONDEBUG(cerr << "NetEndPointBodyC::RunTransmit(), Terminated \n"); 
    return true;
  }
  
  //: Read some bytes from a stream.
  
  bool NetEndPointBodyC::ReadData(int nfd,char *buff,UIntT size) {
    UIntT at = 0;
    while(at < size && !shutdown) {
      int n = read(nfd,&(buff[at]),size - at);
      if(n == 0) { // Linux indicates a close by returning 0 bytes read.  Is this portable ??
	ONDEBUG(cerr << "Socket close. \n");
	return false;
      }
      if(n < 0) {
	ONDEBUG(cerr << "NetEndPointBodyC::ReadData(), Error on read. \n");
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
    do {
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
	ONDEBUG(cerr << "NetEndPointBodyC::RunReceive(), Error on read. \n");
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
    ONDEBUG(cerr << "NetEndPointBodyC::RunReceive(), Started. \n");
    
    int rfd = skt.Fd();
    if(rfd < 0) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunReceive(), ERROR: No connection. \n";    
      return false;       
    }
    {
      // Look for ABPS
      const char *str = "<ABPS>\n";
      char buff;
      int state = 0;
      do {
	ONDEBUG(cerr << "State=" << state << "\n";)
	if(!ReadData(rfd,&buff,1))
	  break;
	if(str[state] != buff) {
	  if(str[0] == buff)
	    state = 1;
	  else 
	    state = 0;
	  continue;
	} 
	state++;
      } while(str[state] != 0) ;
    }
    
    ONDEBUG(cerr << "NetEndPointBodyC::RunReceive(), Connection type confirmed. \n");
    
    try {
      while(!shutdown) {
	UIntT size;
	if(!ReadData(rfd,(char *) &size,sizeof(UIntT))) {
	  ONDEBUG(cerr << "NetEndPointBodyC::RunRecieve(), Read size failed. Assuming connection broken.\n");
	  break;
	}
	if(size == 0)
	  continue;
#if RAVL_LITTLEENDIAN
	size = bswap_32(size);
#endif
	ONDEBUG(cerr << "NetEndPointBodyC::RunRecieve(), Read " << size << " bytes. \n"); 
	SArray1dC<char> data(size);
	if(!ReadData(rfd,(char *) &(data[0]),size)) {
	  ONDEBUG(cerr << "NetEndPointBodyC::RunRecieve(), Read data failed. Assuming connection broken. \n"); 
	  break;
	}
	NetPacketC pkt(data);
	receiveQ.Put(pkt);
      }
    } catch(ExceptionC &e) {
      cerr << "RAVL Exception :'" << e.what() << "'\n";
      cerr << "NetEndPointBodyC::RunRecieve(), Exception caught, terminating link. \n";
    }
#if 0
    catch(exception &e) {
      cerr << "C++ Exception :'" << e.what() << "'\n";
      cerr << "NetEndPointBodyC::RunRecieve(), Exception caught, terminating link. \n";
    } catch(...) {
      cerr << "NetEndPointBodyC::RunRecieve(), Exception caught, terminating link. \n";
    }
#endif
 
#if 0
    if(!nis)
      cerr << "NetEndPointBodyC::RunReceive(), Connection broken \n";
#endif
    MutexLockC lock(accessMsgReg);
    if(connectionBroken.IsValid()) { // Got a callback ?
      TriggerC call = connectionBroken; // Make copy of trigger in case its overwritten.
      connectionBroken.Invalidate(); // Not needed after this.
      lock.Unlock();
      call.Invoke();
      MutexLockC lock(accessMsgReg);
    } else
      lock.Unlock();
    Close();
    ONDEBUG(cerr << "NetEndPointBodyC::RunRecieve(), Terminated \n"); 
    return true;
  }
  
  
  //: Decodes incoming packets.
  
  bool NetEndPointBodyC::RunDecode() {
    ONDEBUG(cerr << "NetEndPointBodyC::RunDecode(), Startup. \n"); 
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
	//ONDEBUG(cerr << "Recieved packet:\n");
	//ONDEBUG(pkt.Dump(cerr));
	// Decode....
	BinIStreamC is(pkt.DecodeStream());
	UIntT msgTypeID = 0;
	is >> msgTypeID;
	ONDEBUG(cerr << "Incoming packet type id:" << msgTypeID << "\n");
	// Check local decode table.
	NetMsgRegisterC msg = Find(msgTypeID);
	if(!msg.IsValid()) {
	  cerr << "NetEndPointBodyC::RunDecode(), WARNING: Don't know how to decode message type " << msgTypeID << " \n";
	  continue;
	}  
	ONDEBUG(cerr << "Decoding incoming packet. Type: '" << msg.Name() << "'\n"); 
	msg.Decode(me,is); 

#if RAVL_COMPILER_MIPSPRO // ignore Tell() = -1 on MIPS 
  	if(  ((UIntT) is.Tell() != pkt.Size()) && (is.Tell() != -1) )  
	  { cerr << "WARNING: Not all of packet processed Stream:" << is.Tell() << " Packet size:" << pkt.Size() <<"\n"; }
#else
	if((UIntT) is.Tell() != pkt.Size()) 
	  { cerr << "WARNING: Not all of packet processed Stream:" << is.Tell() << " Packet size:" << pkt.Size() <<"\n"; }
#endif 
      }
    } catch(ExceptionOperationFailedC &ex) {
      // protocol error...
      Close();
    } catch(ExceptionC &e) {
      SysLog(SYSLOG_WARNING) << "RAVL Exception :'" << e.what() << "'\n";
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::RunDecode(), Exception caught, terminating link. \n";
    } 
#if 0
    catch(exception &e) {
      SysLog(SYSLOG_WARNING) << "C++ Exception :'" << e.what() << "'\n";
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::RunDecode(), Exception caught, terminating link. \n";
    } catch(...) {
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::RunDecode(), Exception caught, terminating link. \n";
    }
#endif
    transmitQ.Put(NetPacketC()); // Put an empty packet to indicate shutdown.
    // Can't to much about recieve...
    ONDEBUG(cerr << "NetEndPointBodyC::RunDecode(), Terminated. \n"); 
    return true;
  }
    
    
  //: Init message.
  
  bool NetEndPointBodyC::MsgInit(StringC &user,NetClientInfoC &nPeerInfo) {
    ONDEBUG(cerr << "NetEndPointBodyC::MsgInit(), Called. User:" << user << "\n");
    remoteUser = user;
    peerInfo = nPeerInfo;
    if(peerInfo.ProtocolName() != localInfo.ProtocolName()) {
      cerr << "ERROR: Protocol mismatch Local='" << localInfo.ProtocolName() << "' Remote='" << peerInfo.ProtocolName() << "'\n";
      throw ExceptionOperationFailedC("Failed to connect, protocol error. \n");
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
