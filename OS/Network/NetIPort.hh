// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_NETIPORT_HEADER
#define RAVL_NETIPORT_HEADER 1
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlNet
//! docentry="Ravl.OS.Network.NetPort"
//! file="Ravl/OS/Network/NetIPort.hh"
//! example=exNetPort.cc

#include "Ravl/DP/SPort.hh"
#include "Ravl/OS/NetEndPoint.hh"
#include "Ravl/OS/NetPort.hh"
#include "Ravl/Threads/RWLock.hh"
#include "Ravl/Threads/Semaphore.hh"
#include "Ravl/Threads/ThreadEvent.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Base class for NetIPorts.
  
  class NetISPortBaseC 
  {
  public:
    NetISPortBaseC(const StringC &server,const StringC &portName,const type_info &ndataType);
    //: Constructor.
    // The 'server' has the format  'host:port' where port may be a
    // host name or its ip (dotted numbers) address and port is the 
    // number of the port to use. <br>
    // 'portName' is the namer of the stream on the server.
    
    ~NetISPortBaseC();
    //: Destructor.
    
    NetEndPointC &NetEndPoint()
    { return ep; }
    //: Access net end point.
    
  protected:
    bool Init();
    //: Initalise link.
    
    bool RecvState(UIntT &at,UIntT &start,UIntT &end);
    //: Handle incoming state info.
    
    bool ReqFailed(IntT &flag);
    //: Handle request failed.
    
    bool WaitForInfo() const;
    //: Wait for stream info to arrive.
    
    NetEndPointC ep;
    
    StringC portName,dataType;
    
    UIntT start,size;    
    UIntT at; // Position in stream.
    bool gotEOS; // Got an End Of Stream.
    RWLockC rwlock;
    SemaphoreC recieved; // Posted when new data arrives.
    UIntT flag;
    mutable ThreadEventC gotStreamInfo; // Have we recieved stream info yet.
  };
  
  //! userlevel=Develop
  //: Input port body
  
  template<class DataT>
  class NetISPortBodyC
    : public DPISPortBodyC<DataT>,
      public NetISPortBaseC
  {
  public:
    NetISPortBodyC(const StringC &address,const StringC &portName)
      : NetISPortBaseC(address,portName,typeid(DataT))
    { Init(); }
    //: Constructor.
    // The 'address' has the format  'host:port' where port may be a
    // host name or its ip (dotted numbers) address and port is the 
    // number of the port to use. <br>
    // 'portName' is the namer of the stream on the server.
    
    ~NetISPortBodyC() { 
      if(ep.IsOpen()) {
	ep.Send(NPMsg_Close);
	ep.WaitTransmitQClear();
      }
      ep.Close(); 
    }
    //: Destructor.
    
    virtual bool Seek(UIntT off) { 
      //cerr << "NetISPortBodyC()::Seek() Off=" << off << " Start=" << start << " Size=" << size << "\n";
      WaitForInfo();
      if(off >= size || off < start)
	return false;
      gotEOS = false; // Reset end of stream flag.
      at = off; 
      return true;
    }
    //: Seek to location in stream.
    // Returns false, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual bool DSeek(IntT off) {
      //cerr << "NetISPortBodyC()::DSeek() Off=" << off << " At=" << at <<" Start=" << start << " Size=" << size << "\n";
      Int64T newOff = (Int64T) at + off;
      WaitForInfo();
      if(off < 0) {
	if((UIntT) (-off) > at)
	  return false; // Seek to before beginning on file.
	if(newOff < start)
	  return false;
      } else {
	if(newOff >= (Int64T) size)
	  return false;	
      }
      gotEOS = false; // Reset end of stream flag.
      at += off;
      return true;
    }
    //: Delta Seek, goto location relative to the current one.
    // The default behavour of this functions is :
    // Do some error checking then:
    //   Seek((UIntT)((IntT) Tell() + off));
    // if an error occurered (DSeek returned False) then stream
    // position will not be changed.
    
    virtual UIntT Tell() const { 
      WaitForInfo();
      return at; 
    }
    //: Find current location in stream.
    // Defined as the index of the next object to be written or read.
    // May return ((UIntT) (-1)) if not implemented.
    
    virtual UIntT Size() const { 
      WaitForInfo();
      return size; 
    }
    //: Find the total size of the stream. (assuming it starts from 0)
    // May return ((UIntT) (-1)) if not implemented.
    
    virtual UIntT Start() const { 
      WaitForInfo();
      return start; 
    }
    //: Find the offset where the stream begins, normally zero.
    // Defaults to 0
    
    virtual bool IsGetReady() const
    { return !gotEOS && ep.IsValid(); } 
    //: Is some data ready ?
    // true = yes.
    
    virtual bool IsGetEOS() const
    { return gotEOS; }
    //: Has the End Of Stream been reached ?
    // true = yes.
    
    virtual DataT Get();
    //: Get next piece of data.
    
    virtual bool Get(DataT &buf);
    //: Get next piece of data.
    
  protected:
    bool Init();
    //: Initalise link.
    
    bool RecvData(UIntT &pos,DataT &dat);
    //: Recieve data.
    
    DataT data; 
  };

  //! userlevel=Normal
  //: Input port.
  
  template<class DataT>
  class NetISPortC
    : public DPISPortC<DataT>
  {
  public:
    NetISPortC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    NetISPortC(const StringC &server,const StringC &portName)
      : DPEntityC(*new NetISPortBodyC<DataT>(server,portName))
    {}
    //: Constructor.
    // The 'address' has the format  'host:port' where port may be a
    // host name or its ip (dotted numbers) address and port is the 
    // number of the port to use. <br>
    // 'portName' is the namer of the stream on the server.
    
  protected:
    NetISPortC(NetISPortBodyC<DataT> &bod)
      : DPEntityC(bod)
    {}
    //: Body constructor.
    
    NetISPortBodyC<DataT> &Body()
    { return dynamic_cast<NetISPortBodyC<DataT> &>(DPEntityC::Body()); }
    //: Access body.
    
    const NetISPortBodyC<DataT> &Body() const 
    { return dynamic_cast<const NetISPortBodyC<DataT> &>(DPEntityC::Body()); }
    //: Access body.
    
  public:
    NetEndPointC &NetEndPoint()
    { return Body().NetEndPoint(); }
    //: Access net end point.
    
  };


  /////////////////////////////////////////////////////////////////////////////////////

  template<class DataT>
  bool NetISPortBodyC<DataT>::Init() {
    ep.RegisterR(NPMsg_Data,"SendData",*this,&NetISPortBodyC<DataT>::RecvData);
    return NetISPortBaseC::Init();
  }
  
  template<class DataT>
  bool NetISPortBodyC<DataT>::RecvData(UIntT &pos,DataT &dat) {
    //cerr << "NetISPortBodyC<DataT>::RecvData(), Called for Pos=" << pos << "\n";
    RWLockHoldC hold(rwlock,RWLOCK_WRITE);
    data = dat;
    flag = 0;
    at = pos;
    hold.Unlock();
    recieved.Post();
    //cerr << "NetISPortBodyC<DataT>::RecvData(), Done for Pos=" << pos << "\n";
    return true;
  }

  //: Get next piece of data.
  
  template<class DataT>
  bool NetISPortBodyC<DataT>::Get(DataT &buf) {
    //cerr << "NetISPortBodyC<DataT>::Get(DataT &), Called for Pos=" << at << "\n";
    if(gotEOS)
      return false;
    ep.Send(NPMsg_ReqData,at);
    recieved.Wait();
    // 'at' is updated by the RecvData method. 
    RWLockHoldC hold(rwlock,RWLOCK_READONLY);
    if(flag != 0) return false;
    buf = data;
    //cerr << "NetISPortBodyC<DataT>::Get(DataT &), Done for Pos=" << at << "\n";
    return true;
  }
  
  template<class DataT>
  DataT NetISPortBodyC<DataT>::Get() {
    DataT tmp;
    if(!Get(tmp))
      throw DataNotReadyC("Get failed. ");
    return tmp;
  }
  
}


#endif
