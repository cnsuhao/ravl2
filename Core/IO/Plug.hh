#ifndef RAVL_PLUG_HEADER
#define RAVL_PLUG_HEADER 1
////////////////////////////////////////////////////
//! docentry="Ravl.Core.Data Processing" 
//! rcsid="$Id$"
//! file="Ravl/Core/IO/Plug.hh"
//! lib=RavlIO
//! author="Charles Galambos"
//! date="8/6/2002"
//! userlevel=Normal

#include "Ravl/DP/Port.hh"

namespace RavlN {

  //! userlevel=Develop
  //: Input plug base.
  
  class DPIPlugBaseBodyC 
    : public RCBodyVC
  {
  public:
    DPIPlugBaseBodyC()
      : hold(true)
    {}
    //: Default constructor.
    
    DPIPlugBaseBodyC(const DPEntityC &nhold)
      : hold(nhold)
    {}
    //: Constructor.
    
    virtual bool SetPort(const DPIPortBaseC &port);
    //: set port.
    
  protected:
    DPEntityC hold; // Make sure object is not deleted.
  };
  
  //! userlevel=Normal
  //: Input plug base.
  
  class DPIPlugBaseC 
    : public RCHandleC<DPIPlugBaseBodyC>
  {
  public:
    DPIPlugBaseC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DPIPlugBaseC(DPIPlugBaseBodyC &bod)
      : RCHandleC<DPIPlugBaseBodyC>(bod)
    {}
    //: Body constructor.
    
    DPIPlugBaseBodyC &Body()
    { return RCHandleC<DPIPlugBaseBodyC>::Body(); }
    //: Access body.
    
    const DPIPlugBaseBodyC &Body() const
    { return RCHandleC<DPIPlugBaseBodyC>::Body(); }
    //: Access body.
    
  public:
    bool SetPort(const DPIPortBaseC &port)
    { return Body().SetPort(port); }
    //: Set port.
    
  };
  
  ///////////////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: Input plug base.
  
  class DPOPlugBaseBodyC 
    : public RCBodyVC
  {
  public:
    DPOPlugBaseBodyC()
      : hold(true)
    {}
    //: Default constructor.
    
    DPOPlugBaseBodyC(const DPEntityC &nhold)
      : hold(nhold)
    {}
    //: Constructor.
    
    virtual bool SetPort(const DPOPortBaseC &port);
    //: set port.
    
  protected:
    DPEntityC hold; // Make sure object is not deleted.
  };
  
  //! userlevel=Normal
  //: Input plug base.
  
  class DPOPlugBaseC 
    : public RCHandleC<DPOPlugBaseBodyC>
  {
  public:
    DPOPlugBaseC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    DPOPlugBaseC(DPOPlugBaseBodyC &bod)
      : RCHandleC<DPOPlugBaseBodyC>(bod)
    {}
    //: Body constructor.
    
    DPOPlugBaseBodyC &Body()
    { return RCHandleC<DPOPlugBaseBodyC>::Body(); }
    //: Access body.
    
    const DPOPlugBaseBodyC &Body() const
    { return RCHandleC<DPOPlugBaseBodyC>::Body(); }
    //: Access body.
    
  public:
    bool SetPort(const DPOPortBaseC &port)
    { return Body().SetPort(port); }
    //: Set port.
    
  };

  
  ////////////////////////////////////
  //! userlevel=Normal
  //: Plug.
  // Used for setting up inputs.
  
  template<class DataT>
  class DPIPlugBodyC 
    : public DPIPlugBaseBodyC
  {
  public:
    explicit DPIPlugBodyC(DPIPortC<DataT> &nport,const DPEntityC &nhold)
      : DPIPlugBaseBodyC(nhold),
	port(nport)
    {}
    //: Constructor.
    
    inline const DPPlugC<DataT> &operator= (DPIPortC<DataT> &othport)
    { port = othport; return *this; }
    //: Assignment.
    
    DPIPortC<DataT> &Port()
    { return port; }
    //: Access port.
    
    virtual bool SetPort(const DPIPortBaseC &port) { 
      port = DPIPortC<DataT>(port);
      return port.IsValid();
    }
    //: set port.
    
  private:
    DPIPortC<DataT> &port;
  };
  
  ////////////////////////////////////
  //! userlevel=Normal
  //: Plug.
  // Used for setting up inputs.
  
  template<class DataT>
  class DPIPlugC 
    : public DPIPlugBaseC
  {
  public:
    explicit DPIPlugC(DPIPortC<DataT> &nport,const DPEntityC &nhold = DPEntityC(true))
      : DPIPlugBaseC(*new DPIPlugBodyC<DataT>(nport,nhold))
    {}
    //: Constructor.
    
  protected:
    DPIPlugBodyC<DataT> &Body()
    { return static_cast<DPIPlugBodyC<DataT> &>(DPIPlugBaseC::Body()); }
    //: Access body.
    
    const DPIPlugBodyC<DataT> &Body() const
    { return static_cast<const DPIPlugBodyC<DataT> &>(DPIPlugBaseC::Body()); }
    //: Access body.
  public:
    
    DPIPortC<DataT> &Port()
    { return Body().Port(); }
    //: Access handle to port.
    
  };
  
  /////////////////////////////
  //: Use a plug
  
  template<class DataT>
  void operator>> (DPIPortC<DataT> &source,DPIPlugC<DataT> &input)  { 
    input = source; 
  }
  
  
  //////////////////////////////////////////////////////////////////////////
  //! userlevel=Normal
  //: Plug.
  // Used for setting up inputs.
  
  template<class DataT>
  class DPOPlugBodyC 
    : public DPOPlugBaseBodyC
  {
  public:
    explicit DPOPlugBodyC(DPIPortC<DataT> &nport,const DPEntityC &nhold)
      : DPOPlugBaseBodyC(nhold),
	port(nport)
    {}
    //: Constructor.

    DPOPortC<DataT> &Port()
    { return port; }
    //: Access handle to port.
    
    virtual bool SetPort(const DPOPortBaseC &port) { 
      port = DPOPortC<DataT>(port);
      return port.IsValid();
    }
    //: set port.
    
  private:
    DPOPortC<DataT> &port;
  };
  
  ////////////////////////////////////
  //! userlevel=Normal
  //: Plug.
  // Used for setting up inputs.
  
  template<class DataT>
  class DPOPlugC 
    : public DPOPlugBaseC
  {
  public:
    explicit DPOPlugC(DPIPortC<DataT> &nport,const DPEntityC &nhold = DPEntityC(true))
      : DPOPlugBaseC(*new DPOPlugBodyC<DataT>(nport,nhold))
    {}
    //: Constructor.
    
  protected:
    DPOPlugBodyC<DataT> &Body()
    { return static_cast<DPOPlugBodyC<DataT> &>(DPOPlugBaseC::Body()); }
    //: Access body.
    
    const DPOPlugBodyC<DataT> &Body() const
    { return static_cast<const DPOPlugBodyC<DataT> &>(DPOPlugBaseC::Body()); }
    //: Access body.
    
  public:
    DPOPortC<DataT> &Port()
    { return Body().Port(); }
    //: Access handle to port.
    
  };
  
  /////////////////////////////
  //: Use a plug
  
  template<class DataT>
  void operator>> (DPOPortC<DataT> &source,DPOPlugC<DataT> &output)  { 
    output = source; 
  }

}

#endif
