// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPMTIOCONNECT_HEADER
#define RAVL_DPMTIOCONNECT_HEADER 1
/////////////////////////////////////////////////////
//! lib=RavlDPMT
//! file="Ravl/OS/DataProc/MTIOConnect.hh"
//! author="Charles Galambos"
//! date="02/10/1998"
//! docentry="Ravl.Core.Data Processing"
//! rcsid="$Id$"

#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/Threads/Semaphore.hh"
#include "Ravl/Threads/ThreadEvent.hh"
#include "Ravl/DP/Port.hh"
#include "Ravl/DList.hh"
#include "Ravl/DP/IOJoin.hh"
#include "Ravl/DP/Event.hh"
#include "Ravl/DP/Pipes.hh"
#include "Ravl/DP/StreamOp.hh"

namespace RavlN {

  template<class DataT> class DPMTIOConnectC;
  
  //////////////////////////
  //! userlevel=Develop
  //: Connect some IOPorts body.
  
  class DPMTIOConnectBaseBodyC 
    : public DPStreamOpBodyC
  {
  public:
    inline DPMTIOConnectBaseBodyC(bool nuseIsGetReady = true,UIntT nblockSize = 1)
      : useIsGetReady(nuseIsGetReady),
	terminate(false),
	blockSize(nblockSize)
    {}
    //: Default Constructor.
    
    virtual StringC OpName() const
    { return StringC("pump"); }
    //: Op type name.
    
    bool Disconnect();
    //: Stop connection.
    // Returns false if connection is already terminated.
    
    inline bool IsDisconnected() const
    { return terminate; }
    //: Test if connection is terminated.
    
    inline bool Wait() ;
    //: Wait for connection to finish.
    
    DPEventC EventComplete();
    //: Generate an event handle 
    // It indicates the completion of processing.
    
  protected:
    bool useIsGetReady;
    bool terminate;
    UIntT blockSize;
    ThreadEventC done;
  };
  
  //////////////////////////
  //! userlevel=Develop
  //: Connect some IOPorts body.
  
  template<class DataT>
  class DPMTIOConnectBodyC 
    : public DPMTIOConnectBaseBodyC
  {
  public:
    DPMTIOConnectBodyC(const DPIPortC<DataT> &nfrom,const DPOPortC<DataT> &nto,bool nuseIsGetReady = true,UIntT nblockSize = 1)
      : DPMTIOConnectBaseBodyC(nuseIsGetReady,nblockSize),
	from(nfrom),
	to(nto)
    { LaunchThread(DPMTIOConnectC<DataT>(*this),&DPMTIOConnectC<DataT>::Start); }
    //: Constructor.
    
#if RAVL_CHECK
    ~DPMTIOConnectBodyC() 
    { cerr << "~DPMTIOConnectBodyC(), Called. Type:" << typeid(*this).name() << "\n"; }
    //: Destructor.
#endif
    
    bool Start();
    //: Do some async stuff.
    
    virtual DListC<DPIPlugBaseC> IPlugs() const {
      DListC<DPIPlugBaseC> ret;
      ret.InsLast(DPIPlugC<DataT>(from,DPEntityC(const_cast<DPMTIOConnectBodyC<DataT> &>(*this))));
      return ret;
    }
    //: Input plugs.
    
    virtual DListC<DPOPlugBaseC> OPlugs() const {
      DListC<DPOPlugBaseC> ret;
      ret.InsLast(DPOPlugC<DataT>(to,DPEntityC(const_cast<DPMTIOConnectBodyC<DataT> &>(*this))));
      return ret;
    }
    //: Output plugs

  private:
    DPIPortC<DataT> from;
    DPOPortC<DataT> to;
    
    friend class DPMTIOConnectC<DataT>;
  };
  
  ////////////////////////////////
  //! userlevel=Normal
  //: Connect some IOPorts.
  
  class DPMTIOConnectBaseC 
    : public DPStreamOpC
  {
  public:
    inline DPMTIOConnectBaseC(DPMTIOConnectBaseBodyC &bod)
      : DPEntityC(bod)
    {}
    //: Constructor.
    
    DPMTIOConnectBaseC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    
  protected:
    inline DPMTIOConnectBaseBodyC &Body() 
    { return dynamic_cast<DPMTIOConnectBaseBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
    inline const DPMTIOConnectBaseBodyC &Body() const
    { return dynamic_cast<const DPMTIOConnectBaseBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
  public:
    bool Disconnect();
    //: Stop connection.
    
    inline bool IsDisconnected() const
    { return Body().IsDisconnected(); }
    //: Test if connection is terminated.
    
    inline bool Wait()
    { return Body().Wait(); }
    //: Wait for connection to finish.
    
    inline DPEventC EventComplete()
    { return Body().EventComplete(); }
    //: Generate an event handle 
    // It indicates the completion of processing.
    
  };
  

  ////////////////////////////////
  //! userlevel=Normal
  //: Connect some IOPorts.
  
  template<class DataT>
  class DPMTIOConnectC
    : public DPMTIOConnectBaseC
  {
  public:
    DPMTIOConnectC(const DPIPortC<DataT> &from,const DPOPortC<DataT> &to,bool nuseIsGetReady = true,bool deleteable = true,UIntT blockSize = 1)
      : DPEntityC(*new DPMTIOConnectBodyC<DataT>(from,to,nuseIsGetReady,blockSize))
    {}
    //: Constructor.
    
  protected: 
    DPMTIOConnectC(DPMTIOConnectBodyC<DataT> &oth)
      : DPEntityC(oth)
    {}
    //: Body Constructor.
    
    inline DPMTIOConnectBodyC<DataT> &Body() 
    { return dynamic_cast<DPMTIOConnectBodyC<DataT> &>(DPEntityC::Body()); }
    //: Access body.
    
    inline const DPMTIOConnectBodyC<DataT> &Body() const
    { return dynamic_cast<const DPMTIOConnectBodyC<DataT> &>(DPEntityC::Body()); }
    //: Access body.
    
  public:  
    bool Start()
    { return Body().Start(); }
    //: Do some async stuff.
    
    friend class DPMTIOConnectBodyC<DataT>;
  };

  //////////////////////////////
  
  template<class DataT>
  DPMTIOConnectC<DataT> DPMTIOConnect(const DPIPortC<DataT> &from,const DPOPortC<DataT> &to)
  { return DPMTIOConnectC<DataT>(from,to); }
  
  /////////////////////////////////////////
  
  inline bool DPMTIOConnectBaseBodyC::Wait() {
    if(IsDisconnected())
      return true;
    done.Wait();
    return true;
  }
  
  ////////////////////////////////////////
  
  template<class DataT>
  bool DPMTIOConnectBodyC<DataT>::Start() {
    //  cerr << "DPMTIOConnectBodyC<DataT>::Start(void) Called " << useIsGetReady << " \n";
    try {
      if(useIsGetReady) {
	if(blockSize > 1) {
	  while(!terminate) {
	    DataT buff;
	    if(!from.Get(buff))
	      break;
	    if(!to.Put(buff)) {
#if RAVL_CHECK
	      if(to.IsPutReady()) {
		cerr << "DPMTIOConnectBodyC<DataT>::Start(), IsPutReady test failed. \n";
		cerr << "  Type:" << typeid(*this).name() << endl;
		RavlAssert(0);
	      }
#endif
	      break;
	    }
	  }
	} else {
	  // Use block processing.
	  SArray1dC<DataT> buf(blockSize);
	  while(!terminate) {
	    int got = from.GetArray(buf);
	    if(got == 0)
	      break;
	    if(to.PutArray(buf) != got) {
#if RAVL_CHECK
	      if(to.IsPutReady()) {
		cerr << "DPMTIOConnectBodyC<DataT>::Start(), Failed to put all data. \n";
		cerr << "  Type:" << typeid(*this).name() << endl;
		RavlAssert(0);
	      }
#endif
	      break;
	    }
	  }
	}
      } else {
	if(blockSize > 1) {
	  while(!terminate) {
	    if(!to.Put(from.Get()))
	      break;
	  }
	} else {
	  // Use block processing.
	  SArray1dC<DataT> buf(blockSize);
	  int puts;
	  while(!terminate) {
	    IntT got = from.GetArray(buf);
	    if(got < 0)
	      continue;
	    if(got < (IntT) blockSize) {
	      SArray1dC<DataT> tb(buf,got);
	      puts = to.PutArray(tb);
	    } else
	      puts = to.PutArray(buf);
	    if(puts != got) {
	      cerr << "DPMTIOConnectBodyC<DataT>::Start(), PutArray failed to output all data. \n";
	      break;
	    }
	  }
	}
      }
    } catch(...) {
      cerr << "An exception occured in: " << typeid(*this).name() << endl;
      cerr << "Halting thread. \n" << flush;
    }
    //cerr << "DPMTIOConnectBodyC<DataT>::Start(), Completed. Get:" << from.IsGetReady() << " Put:" << to.IsPutReady() << " Term:" << terminate << endl ;
    to.PutEOS(); // Put a termination marker.
    terminate = true;
    done.Post(); // Post event to all waiting funcs.
    return true;
  }

  //! userlevel=Normal
  //: Multi-threaded composition operators.
  
  template<class DataT>
  inline DPEventC operator>>= (const DPIPortC<DataT> &in,const DPOPortC<DataT> &out)
  { return DPMTIOConnectC<DataT>(in,out,true).EventComplete(); }
  //: Pump data from an input into an output.
  
  template<class DataT,class OutT>
  inline DPIPortC<OutT> operator>>= (const DPIPortC<DataT> &in,const DPIOPortC<OutT,DataT> &out)
  { return DPIPipeC<OutT>(out,DPMTIOConnectC<DataT>(in,out,true)); }
  //: Pump data from an input into an output.
  
  template<class InT,class DataT>
  inline DPOPortC<InT> operator>>= (const DPIOPortC<DataT,InT> &in,const DPOPortC<DataT> &out) 
  { return DPOPipeC<InT>(in,DPMTIOConnectC<DataT>(in,out,true)); }
  //: Pump data from an input into an output.
  
  template<class InT,class DataT,class OutT>
  inline DPIOPortC<InT,OutT> operator>>= (const DPIOPortC<DataT,OutT> &in,const DPIOPortC<InT,DataT> &out) 
  { return DPIOPortJoin(out,in,DPMTIOConnectC<DataT>(in,out,true)); }
  //: Pump data from an input into an output.
  
}

#endif
