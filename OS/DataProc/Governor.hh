// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPGOVERNOR_HEADER
#define RAVL_DPGOVERNOR_HEADER
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Data Processing.Extras"
//! author="Charles Galambos"
//! date="12/10/98"
//! lib=RavlDPMT
//! file="Ravl/OS/DataProc/Governor.hh"

#include "Ravl/DP/StreamOp.hh"
#include "Ravl/OS/Date.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Governor base body.
  
  class DPGovernorBaseBodyC 
    : virtual public DPEntityBodyC
  {
  public:
    DPGovernorBaseBodyC(double ndelay)
      : delay(ndelay),
	frameCnt(0)
    {}
    //: Constructor
    
    DPGovernorBaseBodyC(const DPGovernorBaseBodyC &oth) 
      : delay(oth.delay),
	frameCnt(0)
    {}
    //: Copy Constructor
    
    UIntT FrameCount() const { return frameCnt; }
    //: Access frame count.
    
    RealT Delay() const { return delay; }
    //: Access frame count.
    
    RealT &Delay() { return delay; }
    //: Access frame count.
    
  protected:
    void WaitForTimeup();
    //: Wait for timeup.
    
    void Dummy(void);
    //: Dummy func.
    
    DateC next;
    RealT delay;
    UIntT frameCnt; // Frame count,can be used to measure frame rate.
  };
  
  ////////////////////////////////////
  //! userlevel=Normal
  //: Governor base Handle.
  // Stream independant control of frame rate.
  
  class DPGovernorBaseC 
    : virtual public DPEntityC
  {
  public:
    DPGovernorBaseC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    
    DPGovernorBaseC(DPGovernorBaseBodyC &bod)
      : DPEntityC(bod)
    {}
    //: Body Constructor
    
    DPGovernorBaseC(const DPGovernorBaseC &bod)
      : DPEntityC(bod)
    {}
    //: Copy Constructor
    
  protected:
    DPGovernorBaseBodyC &Body() 
    { return dynamic_cast<DPGovernorBaseBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
    const DPGovernorBaseBodyC &Body() const 
    { return dynamic_cast<const DPGovernorBaseBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
  public:
    UIntT FrameCount() const 
    { return Body().FrameCount(); }
    //: Access frame count.
    
    RealT Delay() const 
    { return Body().Delay(); }
    //: Access delay
    
    RealT &Delay()
    { return Body().Delay(); }
    //: Access delay
    
  };
  
  ///////////////////////////
  //! userlevel=Develop
  //: Governor body.
  
  template<class DataT>
  class DPGovernorBodyC 
    : public DPIStreamOpBodyC<DataT,DataT>,
      public DPGovernorBaseBodyC 
  {
  public:
    DPGovernorBodyC(double ndelay)
      : DPGovernorBaseBodyC(ndelay)
    {}
    //: Constructor
    
    DPGovernorBodyC(const DPGovernorBodyC<DataT> &oth) 
      : DPIStreamOpBodyC<DataT,DataT>(oth),
	DPGovernorBaseBodyC(oth)
    {}
    //: Copy Constructor
    
    virtual DataT Get() { 
      DataT ret = input.Get(); 
      WaitForTimeup();
      return ret;
    }
    //: Process next piece of data.
    
    virtual bool Get(DataT &outbuff) { 
      bool ret = input.Get(outbuff);
      WaitForTimeup();
      return ret;
    }
    //: Process some data.  
    
    virtual bool IsGetReady() const {
      RavlAssert(input.IsValid());
      return input.IsGetReady(); 
    }
    
    virtual bool IsGetEOS() const { 
      RavlAssert(input.IsValid());
      return input.IsGetEOS(); 
    }
    //: Has the End Of Stream been reached ?
    // true = yes.
    
    virtual RCBodyVC &Copy() const 
    { return *new DPGovernorBodyC(*this); }
    //: Creat a copy of this object.
    
  };
  
  ////////////////////////////////////
  //! userlevel=Normal
  //: Governor Handle.
  // This class limits the minimum time between
  // get operations.  This is used for things 
  // like control  the frame rate of a video 
  // sequence.
  
  template<class DataT>
  class DPGovernorC 
    : public DPIStreamOpC<DataT,DataT>,
      public DPGovernorBaseC 
  {
  public:
    DPGovernorC(double ndelay)
      : DPEntityC(*new DPGovernorBodyC<DataT>(ndelay))
    {}
    //: Constructor  
  };
  
}

#endif
