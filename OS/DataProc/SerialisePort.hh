// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SERIALISEPORT_HEADER
#define RAVL_SERIALISEPORT_HEADER
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlDPMT
//! date="2/5/2003"
//! docentry="Ravl.Core.Data Processing.Threads" 

#include "Ravl/DP/StreamOp.hh"
#include "Ravl/Threads/Mutex.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Serialise requests to port when used by more than one thread .
  
  template<typename DataT>
  class DPISerialisePortBodyC
    : public DPIStreamOpBodyC<DataT,DataT>
  {
  public:
    DPISerialisePortBodyC(const DPIPortC<DataT> &in)
      : DPIStreamOpBodyC<DataT,DataT>(in)
    {}
    //: Constructor.
    
    virtual bool IsGetReady() const {
      MutexLockC lock(access);
      return DPIStreamOpBodyC<DataT,DataT>::IsGetReady(); 
    }
    //: Is some data ready ?
    // true = yes.
    
    virtual bool IsGetEOS() const {
      MutexLockC lock(access);      
      return DPIStreamOpBodyC<DataT,DataT>::IsGetEOS(); 
    }
    //: Has the End Of Stream been reached ?
    // true = yes.
    
    virtual DataT Get()  {
      MutexLockC lock(access);
      return input.Get();
    }
    //: Get next piece of data.
    
    virtual bool Get(DataT &buff) { 
      MutexLockC lock(access);
      return input.Get(buff);
    }
    //: Try and get next piece of data.
    
    virtual IntT GetArray(SArray1dC<DataT> &data) {
      MutexLockC lock(access);
      return input.Get(data);
    }
    //: Get an array of data from stream.
    
    virtual bool Discard() { 
      MutexLockC lock(access);
      return input.Discard();
    }
    //: Discard the next input datum.
    
  protected:
    MutexC access;
  };
  
  
  //! userlevel=Normal
  //: Serialise requests to port when used by more than one thread .
  
  template<typename DataT>
  class DPISerialisePortC
    : public DPIStreamOpC<DataT,DataT>
  {
  public:
    DPISerialisePortC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DPISerialisePortC(const DPIPortC<DataT> &in)
      : DPIStreamOpC<DataT,DataT>(*new DPISerialisePortBodyC<DataT>(in))
    {}
    //: Construct from port.
    
  };

  
  //! userlevel=Develop
  //: Serialise requests to port when used by more than one thread .
  
  template<typename DataT>
  class DPOSerialisePortBodyC
    : public DPOStreamOpBodyC<DataT,DataT>
  {
  public:
    DPOSerialisePortBodyC(const DPOPortC<DataT> &out)
      : DPOStreamOpBodyC<DataT,DataT>(out)
    {}
    //: Constructor.
    
    virtual void PutEOS() {
      MutexLockC lock(access);
      output.PutEOS();
    }
    //: Put End Of Stream marker.
    
    virtual bool IsPutReady() const {
      MutexLockC lock(access);
      return output.IsPutReady();
    }
    //: Is port ready for data ?
    
    virtual bool Put(const DataT &data) { 
      MutexLockC lock(access);
      return output.Put(data);
    }
    //: Put data.
    // This function MUST be provided by client class.
    
    virtual IntT PutArray(const SArray1dC<DataT> &data) {
      MutexLockC lock(access);
      return output.PutArray(data);
    }
    //: Put an array of data to stream.
    
  protected:
    MutexC access;
  };
  
  
  //! userlevel=Normal
  //: Serialise requests to port when used by more than one thread .
  
  template<typename DataT>
  class DPOSerialisePortC
    : public DPOStreamOpC<DataT,DataT>
  {
  public:
    DPOSerialisePortC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DPOSerialisePortC(const DPOPortC<DataT> &out)
      : DPOStreamOpC<DataT,DataT>(*new DPOSerialisePortBodyC<DataT>(out))
    {}
    //: Construct from port.
    
  };

}

#endif
