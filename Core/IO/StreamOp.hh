// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDPSTREAMOP_HEADER
#define RAVLDPSTREAMOP_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Data Processing" 
//! file="Ravl/Core/IO/StreamOp.hh"
//! lib=RavlIO
//! author="Charles Galambos"
//! date="09/07/98"
//! userlevel=Default

#include "Ravl/DP/Port.hh"

namespace RavlN {
  ////////////////////////////////////////
  //! userlevel=Develop
  //: Stream operation base class.
  
  template<class InT,class OutT>
  class DPIStreamOpBodyC 
    : public DPIPortBodyC<OutT>
  {
  public:
    DPIStreamOpBodyC()
      {}
    //: Default constructor.
    
    DPIStreamOpBodyC(const DPIPortC<InT> &nin)
      : input(nin)
      {}
    //: Constructor.
    
    virtual bool IsGetReady() const  {
      if(!input.IsValid())
	return false;
      return input.IsGetReady(); 
    }
    //: Is some data ready ?
    // true = yes.
    
    virtual bool IsGetEOS() const {
      if(!input.IsValid())
	return true;
      return input.IsGetEOS(); 
    }
    //: Has the End Of Stream been reached ?
    // true = yes.
    
    virtual DPPortC ConnectedTo() const
    { return input; }
    //: What does this connect to ?
    
  protected:
    DPIPortC<InT> input; // Where to get data from.
    
  public:
    inline DPIPortC<InT> &Input() { return input; }
    // Access input port.
  }; 
  
  ///////////////////////////////////
  //! userlevel=Normal
  //: Stream operation handle class.
  
  template<class InT,class OutT>
  class DPIStreamOpC : public DPIPortC<OutT> {
  public:
    DPIStreamOpC() 
      : DPEntityC(true)
      {}
    //: Default Constructor.
    
    DPIStreamOpC(const DPIStreamOpC<IntT,OutT> &oth) 
      : DPEntityC(oth),
      DPIPortC<OutT>(oth)
      {}
    //: Copy Constructor.
    
  protected:
    DPIStreamOpC(const DPIStreamOpBodyC<InT,OutT> &bod)
      : DPEntityC((DPIPortBodyC<OutT> &) bod)
      {}
    //: Body constructor.
    
  public:  
    inline DPIPortC<InT> &Input() 
      { return dynamic_cast<DPIStreamOpBodyC<InT,OutT> & >(DPEntityC::Body()).Input(); }
    // Access input port.
    
  };
  
  ////////////////////////////////////////
  //! userlevel=Develop
  //: Stream operation base class.
  
  template<class InT,class OutT>
  class DPOStreamOpBodyC 
    : public DPOPortBodyC<InT>
  {
  public:
    DPOStreamOpBodyC()
      {}
    //: Default constructor.
    
    DPOStreamOpBodyC(const DPOPortC<OutT> &nout)
      : output(nout)
      {}
    //: Constructor.
    
    virtual bool IsPutReady() const {
      RavlAssert(output.IsValid());
      return output.IsPutReady(); 
    }
    //: Is some data ready ?
    // true = yes.
    
    virtual void PutEOS() {
      if(output.IsValid())
	output.PutEOS();
    }
    //: Put End Of Stream marker.
    
    virtual DPPortC ConnectedTo() const
    { return output; }
    //: What does this connect to ?
    
  protected:
    DPOPortC<OutT> output; // Where to put data to.
    
  public:
    inline DPOPortC<OutT> &Output() { return output; }
    // Access output port.
  }; 
  
  ///////////////////////////////////
  //! userlevel=Normal
  //: Stream operation handle class.
  
  template<class InT,class OutT>
  class DPOStreamOpC 
    : public DPOPortC<InT> 
  {
  public:
    DPOStreamOpC() 
      : DPEntityC(true)
      {}
    //: Default Constructor.
    
    DPOStreamOpC(const DPOStreamOpC<InT,OutT> &oth) 
      : DPEntityC(oth),
      DPOPortC<InT>(oth)
      {}
    //: Copy Constructor.
    
  protected:
    DPOStreamOpC(const DPOStreamOpBodyC<InT,OutT> &bod)
      : DPEntityC((DPOPortBodyC<InT> &) bod)
      {}
    //: Body constructor.
    
    inline DPOPortC<OutT> &Output() 
      { return dynamic_cast<DPOStreamOpBodyC<InT,OutT> & >(DPEntityC::Body()).Output(); }
    // Access input port.
    
  };
  
  template<class InT,class OutT>
  DPIPortC<OutT> operator>>(const DPIPortC<InT> &in,DPIStreamOpC<InT,OutT> dat) {
    dat.Input() = in;
    return dat;
  }

}
#endif
