// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_NETOPORT_HEADER
#define RAVL_NETOPORT_HEADER 1
////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Charles Galambos"
//! lib=RavlNet
//! docentry="Ravl.OS.Network.NetPort"
//! file="Ravl/OS/Network/NetOPort.hh"
//! example=exNetPort.cc

#include "Ravl/DP/SPort.hh"
#include "Ravl/OS/NetEndPoint.hh"
#include "Ravl/Threads/RWLock.hh"
#include "Ravl/OS/NetPort.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Base class for NetIPorts.
  
  class NetOSPortBaseC 
    : public NetPortBaseC 
  {
  public:
    NetOSPortBaseC(const StringC &server,const StringC &portName,const type_info &ndataType);
    //: Constructor.
    // The 'server' has the format  'host:port' where port may be a
    // host name or its ip (dotted numbers) address and port is the 
    // number of the port to use. <br>
    // 'portName' is the namer of the stream on the server.
    
    ~NetOSPortBaseC();
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
    
    
    StringC portName,dataType;
    
    UIntT start,size;    
    UIntT at; // Position in stream.
    bool gotEOS; // Got an End Of Stream.
    
    RWLockC rwlock;
    
    UIntT flag;
  };
  
  //! userlevel=Develop
  //: Input port body
  
  template<class DataT>
  class NetOSPortBodyC
    : public DPOSPortBodyC<DataT>,
      public NetOSPortBaseC
  {
  public:
    NetOSPortBodyC(const StringC &address,const StringC &portName)
      : NetOSPortBaseC(address,portName,typeid(DataT))
    { 
      this->MapBackChangedSignal("start");
      this->MapBackChangedSignal("size");
      Init(); 
    }
    //: Constructor.
    // The 'address' has the format  'host:port' where port may be a
    // host name or its ip (dotted numbers) address and port is the 
    // number of the port to use. <br>
    // 'portName' is the namer of the stream on the server.
    
    ~NetOSPortBodyC() { 
      if(ep.IsOpen() && !gotEOS) {
	ep.Send(NPMsg_Close);
	ep.WaitTransmitQClear();
      }
      ep.Close(); 
    }
    //: Destructor.
    
    virtual bool Seek(UIntT off) { 
      //cerr << "NetOSPortBodyC()::Seek() Off=" << off << " Start=" << start << " Size=" << size << "\n";
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
      //cerr << "NetOSPortBodyC()::DSeek() Off=" << off << " At=" << at <<" Start=" << start << " Size=" << size << "\n";
      Int64T newOff = (Int64T) at + off;
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
    
    virtual UIntT Tell() const 
    { return at; }
    //: Find current location in stream.
    // Defined as the index of the next object to be written or read.
    // May return ((UIntT) (-1)) if not implemented.
    
    virtual UIntT Size() const
    { return size; }
    //: Find the total size of the stream. (assuming it starts from 0)
    // May return ((UIntT) (-1)) if not implemented.
    
    virtual UIntT Start() const
    { return start; }
    //: Find the offset where the stream begins, normally zero.
    // Defaults to 0
    
    virtual void PutEOS() { 
      gotEOS = true; 
      ep.Send(NPMsg_Close);
      ep.WaitTransmitQClear();
    }
    //: Put End Of Stream marker.
    
    virtual bool IsPutReady() const 
    { return !gotEOS && ep.IsValid(); }
    //: Is port ready for data ?
    
    virtual bool Put(const DataT &data) { 
      if(gotEOS || !ep.IsValid())
	return false;
      ep.Send(NPMsg_Data,at,data);
      at++;
      if(at > size)
	size = at;
      return true; 
    }
    //: Put data.
    // This function MUST be provided by client class.
    
    virtual AttributeCtrlC ParentCtrl() const
    { return netAttr; }
    //: Get Parent attribute control.
    
  };

  //! userlevel=Normal
  //: Input port.
  
  template<class DataT>
  class NetOSPortC
    : public DPOSPortC<DataT>
  {
  public:
    NetOSPortC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    NetOSPortC(const StringC &server,const StringC &portName)
      : DPEntityC(*new NetOSPortBodyC<DataT>(server,portName))
    {}
    //: Constructor.
    // The 'address' has the format  'host:port' where port may be a
    // host name or its ip (dotted numbers) address and port is the 
    // number of the port to use. <br>
    // 'portName' is the namer of the stream on the server.
    
  protected:
    NetOSPortC(NetOSPortBodyC<DataT> &bod)
      : DPEntityC(bod)
    {}
    //: Body constructor.
    
    NetOSPortBodyC<DataT> &Body()
    { return dynamic_cast<NetOSPortBodyC<DataT> &>(DPEntityC::Body()); }
    //: Access body.
    
    const NetOSPortBodyC<DataT> &Body() const 
    { return dynamic_cast<const NetOSPortBodyC<DataT> &>(DPEntityC::Body()); }
    //: Access body.
    
  public:
    NetEndPointC &NetEndPoint()
    { return Body().NetEndPoint(); }
    //: Access net end point.
    
  };


  
}


#endif
