// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPFIXEDBUFFER_HEADER
#define RAVL_DPFIXEDBUFFER_HEADER 1
////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlDPMT
//! docentry="Data Processing"
//! file="Ravl/StdType/MTDataProc/FixedBuffer.hh"
//! author="Charles Galambos"
//! date="04/03/99"

#include "Ravl/DP/Port.hh"
#include "Ravl/Threads/MessageQueue.hh"

namespace RavlN {
  
  //////////////////////////////
  //! userlevel=Develop
  //: MT safe queue body
  
  template<class DataT>
  class DPFixedBufferBodyC 
    : public DPIOPortBodyC<DataT,DataT>
  {
  public:
    DPFixedBufferBodyC(IntT maxsize = 10) 
      : queue(maxsize)
    {}
    //: Default constructor.
    
    virtual bool Put(const DataT &dat) 
    { queue.Put(dat); return true; }
    //: Put data.
    
    virtual IntT PutArray(const SArray1dC<DataT> &dat) {
      for(SArray1dIterC<DataT> it(dat);it;it++)
	queue.Put(*it);
      return dat.Size();
    }
    //: Put an array of data.
    
    virtual DataT Get() 
    { return queue.Get(); }
    //: Get next piece of data.
    // May block if not ready, or it will return a constructed
    // with the default constructor.
    
    virtual bool Get(DataT &d) { 
      d = queue.Get(); 
      return true;
    }
    //: Get next piece of data.
    // May block if not ready, or it will return a constructed
    // with the default constructor.
    
    virtual IntT GetArray(SArray1dC<DataT> &dat) {
      for(SArray1dIterC<DataT> it(dat);it;it++)
	*it = queue.Get();
      return dat.Size();
    }
    //: Get an array of data.
    
  private:
    MessageQueueC<DataT> queue;
  };
  
  //////////////////////////////////
  //! userlevel=Normal
  //: MT safe queue handle.
  
  
  template<class DataT>
  class DPFixedBufferC 
    : public DPIOPortC<DataT,DataT> 
  {
  public:
    DPFixedBufferC(IntT maxsize = 10)
      : DPEntityC(*new DPFixedBufferBodyC<DataT>(maxsize))
    {}
    //: Constructor.
    
  };
  
}
#endif
