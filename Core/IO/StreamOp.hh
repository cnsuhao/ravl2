// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPSTREAMOP_HEADER
#define RAVL_DPSTREAMOP_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Data Processing.Internal" 
//! file="Ravl/Core/IO/StreamOp.hh"
//! lib=RavlIO
//! author="Charles Galambos"
//! date="09/07/1998"
//! userlevel=Default

#include "Ravl/DP/Port.hh"
#include "Ravl/DP/Plug.hh"
#include "Ravl/DList.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Abstract stream operation.
  
  class DPStreamOpBodyC
    : virtual public DPEntityBodyC 
  {
  public:
    DPStreamOpBodyC()
    {}
    //: Default constructor.
    
    virtual DListC<DPIPlugBaseC> IPlugs() const;
    //: Input plugs.
    
    virtual DListC<DPOPlugBaseC> OPlugs() const;
    //: Output plugs
    
    virtual DListC<DPIPortBaseC> IPorts() const;
    //: Input ports.
    
    virtual DListC<DPOPortBaseC> OPorts() const;
    //: Output ports
    
  };

  //! userlevel=Normal
  //: Abstract stream operation.
  
  class DPStreamOpC
    : virtual public DPEntityC 
  {
  public:
    DPStreamOpC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DPStreamOpC(DPEntityC &ent)
      : DPEntityC(ent)
    {
      if(dynamic_cast<DPStreamOpBodyC *>(&DPEntityC::Body()) == 0)
	Invalidate();
    }
    //: Base class constructor.
    // If object is not a DPStreamOpC then an invalid handle will
    // be created.
    
  protected:
    DPStreamOpC(DPStreamOpBodyC &bod)
      : DPEntityC(bod)
    {}
    //: Body constructor.
    
    DPStreamOpBodyC &Body()
    { return dynamic_cast<DPStreamOpBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
    const DPStreamOpBodyC &Body() const
    { return dynamic_cast<const DPStreamOpBodyC &>(DPEntityC::Body()); }
    //: Access body.
    
  public:
    
    DListC<DPIPlugBaseC> IPlugs() const
    { return Body().IPlugs(); }
    //: Input plugs.
    
    DListC<DPOPlugBaseC> OPlugs() const
    { return Body().OPlugs(); }
    //: Output plugs
    
    DListC<DPIPortBaseC> IPorts() const
    { return Body().IPorts(); }
    //: Input ports.
    
    DListC<DPOPortBaseC> OPorts() const
    { return Body().OPorts(); }
    //: Output ports
    
  };

  
  ////////////////////////////////////////
  //! userlevel=Develop
  //: Stream operation base class.
  
  template<class InT,class OutT>
  class DPIStreamOpBodyC 
    : public DPIPortBodyC<OutT>,
      public DPStreamOpBodyC
  {
  public:
    DPIStreamOpBodyC()
    {}
    //: Default constructor.
    
    DPIStreamOpBodyC(const DPIPortC<InT> &nin)
      : input(nin)
    {}
    //: Constructor.
    
    virtual bool IsGetReady() const {
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
    
    virtual DListC<DPIPortBaseC> IPorts() const {
      DListC<DPIPortBaseC> lst = DPStreamOpBodyC::IPorts();
      lst.InsLast(DPIPortBaseC((DPIPortBaseBodyC &)*this));
      return lst;
    }
    //: Input ports.

    virtual DListC<DPIPlugBaseC> IPlugs() const {
      DListC<DPIPlugBaseC> lst = DPStreamOpBodyC::IPlugs();
      lst.InsLast(DPIPlugC<InT>(input,DPEntityC((DPEntityBodyC &)*this)));
      return lst;
    }
    //: Input plugs.
    
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
  class DPIStreamOpC 
    : public DPIPortC<OutT>,
      public DPStreamOpC
  {
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
    : public DPOPortBodyC<InT>,
      public DPStreamOpBodyC
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

    virtual DListC<DPOPortBaseC> OPorts() const {
      DListC<DPOPortBaseC> lst = DPStreamOpBodyC::OPorts();
      lst.InsLast(DPOPortBaseC(const_cast<DPOStreamOpBodyC<InT,OutT> &>(*this)));
      return lst;
    }
    //: Output ports.
    
    virtual DListC<DPOPlugBaseC> OPlugs() const {
      DListC<DPOPlugBaseC> lst = DPStreamOpBodyC::OPlugs();
      lst.InsLast(DPOPlugC<OutT>(output,DPEntityC((DPEntityBodyC &)*this)));
      return lst;
    }
    //: Output plugs.
    
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
    : public DPOPortC<InT>,
      public DPStreamOpC
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
