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
#include "Ravl/OS/NetMsgCall.hh"
#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/OS/SysLog.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/OS/NetByteStream.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Constructor.
  
  NetEndPointBodyC::NetEndPointBodyC(const StringC &addr,bool nautoInit) 
    : transmitQ(15),
      receiveQ(5),
      shutdown(false),
      autoInit(nautoInit),
      useBigEndianBinStream(RAVL_BINSTREAM_ENDIAN_BIG)
  {
    SocketC skt(addr,false);
    localInfo.appName = SysLogApplicationName();
    Init(skt); 
  }
  
  //:  Constructor.
  
  NetEndPointBodyC::NetEndPointBodyC(SocketC &nskt,bool nautoInit)
    : transmitQ(15),
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
    : transmitQ(15),
      receiveQ(5),
      shutdown(false),
      autoInit(nautoInit),
      localInfo(protocolName,protocolVersion),
      useBigEndianBinStream(RAVL_BINSTREAM_ENDIAN_BIG)
  { 
    localInfo.appName = SysLogApplicationName();
    Init(socket); 
  }
  
  //: Constructor.
  
  NetEndPointBodyC::NetEndPointBodyC(const StringC &address,const StringC &protocolName,const StringC &protocolVersion,bool nautoInit) 
    : transmitQ(15),
      receiveQ(5),
      shutdown(false),
      autoInit(nautoInit),
      localInfo(protocolName,protocolVersion),
      useBigEndianBinStream(RAVL_BINSTREAM_ENDIAN_BIG)
  { 
    SocketC skt(address,false);
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
    if(!nskt.IsOpen()) {
      ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::Init(), Socket not opened. ");
      return false;
    }
    //nskt.SetNonBlocking(true);
    istrm = NetIByteStreamC(nskt);
    ostrm = NetOByteStreamC(nskt);
    
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
      ostrm.PutEOS();
      //istrm.PutEOS();
      receiveQ.Put(NetPacketC()); // Put an empty packet to indicate shutdown.
      transmitQ.Put(NetPacketC()); // Put an empty packet to indicate shutdown.
    }
    return true;
  }
  
  //: Access the name of the connected Host 
  
  StringC NetEndPointBodyC::ConnectedHost(void) { 
    StringC hostName("Uknown");
    istrm.GetAttr("ConnectedHost",hostName);
    return hostName;
  }
  
  //: Access the name of the connected Port 
  
  IntT NetEndPointBodyC::ConnectedPort(void) { 
    IntT portNo = -1;
    istrm.GetAttr("ConnectedPort",portNo);
    return portNo;
  } 
  
  static const StringC streamHeaderBigEndian ="\n<ABPS>\n";
  static const StringC streamHeaderLittleEndian ="\n<RBPS>\n";
  
  //: Handle packet transmition.
  
  bool NetEndPointBodyC::RunTransmit() {
    if(!ostrm.IsPutReady()) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: No connection. ";
      CloseTransmit();
      return false;       
    }
    //skt.SetNoDelay(); // Send packets asap.
#if RAVL_BINSTREAM_ENDIAN_LITTLE
    StringC streamHeader = streamHeaderLittleEndian;
#else
    StringC streamHeader = streamHeaderBigEndian;
#endif
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunTransmit(), Sending header '" << streamHeader << "' ");
    
    // Write stream header.
    if(ostrm.Write(streamHeader,streamHeader.Size()) != (IntT) streamHeader.Size()) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: Failed to write header. ";
      CloseTransmit();
      return false;
    }
    if(shutdown) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), Terminated. ";
      CloseTransmit();
      return false;
    }
    // Wait still we got a stream header from peer 
    if(!gotStreamType.Wait(45)) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: Timeout waiting for stream header. ";
      CloseTransmit();
      return false;
    }
    if(shutdown) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), Terminated. ";
      CloseTransmit();
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
      if(ostrm.Write(streamHeaderBigEndian,streamHeader.Size()) < streamHeader.Size()) {
	SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: Failed to write header. ";
	CloseTransmit();
	return false;
      }
#else
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: Incompatible protocol. ";
      CloseTransmit();
      return false;
#endif
    }
#else
    if(streamType == "<RBPS>") { // Client using an old big endian protocol ?
#if RAVL_ENDIAN_COMPATILIBITY
      // We're in compatiblity mode, send old header.
      // If so, write <ABPS> header.
      useBigEndianBinStream = false;
      if(ostrm.Write(streamHeaderBigEndian,streamHeader.Size()) < (IntT) streamHeader.Size()) {
	SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: Failed to write header. ";    
	CloseTransmit();
	return false;
      }
#else
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunTransmit(), ERROR: Incompatible protocol. ";
      CloseTransmit();
      return false;
#endif
    }
#endif
    const char *bufPtr[2];
    IntT bufLen[2];
    
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
	bufPtr[0] = (char *)&size;
	bufLen[0] = sizeof(size);
	bufPtr[1] = &(pkt.Data()[0]);
	bufLen[1] = pkt.Size();
	if(ostrm.WriteV(bufPtr,bufLen,2) != (IntT) (sizeof(size) + pkt.Size())) {
	  SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::WriteV() Failed.  ";
	  break;
	}
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
    
    CloseTransmit();
    
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunTransmit(), Terminated. "); 
    return true;
  }
  
  //: Close down for transmit thread.
  
  void NetEndPointBodyC::CloseTransmit() {
    // Close down.
    Close();
    
    // Drain transmit Q.
    NetPacketC pkt;
    while(transmitQ.TryGet(pkt)) ;
  }
  
  //: Handle packet reception.
  
  bool NetEndPointBodyC::RunReceive() {
    SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunReceive(), Started. ";
    if(!istrm.IsGetReady()) {
      SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunReceive(), ERROR: No connection. ";
      return false;       
    }
    StringC recvStreamType;
    bool errorInHeader = false;
    {
      // Look for ABPS
      const char *str = "<ABPS>\n";
      char buff;
      int state = 0;
      streamType = "<ABPS>";
      do {
	if(istrm.Read(&buff,1) != 1) {
	  SysLog(SYSLOG_ERR) << "NetEndPointBodyC::RunReceive(), Failed to read byte from input stream. " << errno << " ";
	  errorInHeader = true;
	  break;
	}
	//SysLog(SYSLOG_DEBUG) << "State=" << state << " char='" << buff << "' ";
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
    if(errorInHeader) {
      Close();
      SysLog(SYSLOG_WARNING) << "NetEndPointBodyC::RunRecieve(), Terminated while reading header"; 
      return true;
    }
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunReceive(), Connection type confirmed. '" << streamType << "' "); 
   
    try {
      while(!shutdown) {
	UIntT size;
	if(istrm.Read((char *) &size,sizeof(UIntT)) != (IntT) sizeof(UIntT)) {
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
	if(istrm.Read((char *) &(data[0]),size) != (IntT) size) {
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
    SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunRecieve(), Terminated ";
    return true;
  }
  
  
  //: Decodes incoming packets.
  
  bool NetEndPointBodyC::RunDecode() {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "NetEndPointBodyC::RunDecode(), Startup. "); 
    NetPacketC pkt;
    NetEndPointC me(*this);
    try {
      while(1) {
	NetPacketC pkt;
	if(!shutdown) {
	  if(!receiveQ.Get(pkt,1.5))
	    continue;
	} else {
	  // We're shutting down, try and finish processing any
	  // remaining packets, but exit when the Q is empty.
	  if(!receiveQ.TryGet(pkt))
	    break;
	}
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
    // Can't to much about recieve...
    // Drain the recieve Q. 
     
    while(receiveQ.TryGet(pkt)) ;
    // Put an empty packet to indicate shutdown. 
    transmitQ.Put(NetPacketC()); 
    
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
