// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPPLUG_HEADER
#define RAVL_DPPLUG_HEADER 1
////////////////////////////////////////////////////
//! docentry="Ravl.Core.Data Processing.Ports" 
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
  
  //! userlevel=Advanced
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
  
  //! userlevel=Advanced
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
  //! userlevel=Develop
  //: Plug.
  // Used for setting up inputs.
  
  template<class DataT>
  class DPIPlugBodyC 
    : public DPIPlugBaseBodyC
  {
  public:
    explicit DPIPlugBodyC(const DPIPortC<DataT> &nport,const DPEntityC &nhold)
      : DPIPlugBaseBodyC(nhold),
	port(const_cast<DPIPortC<DataT> &>(nport))
    {}
    //: Constructor.
    
    inline const DPPlugC<DataT> &operator= (DPIPortC<DataT> &othport)
    { port = othport; return *this; }
    //: Assignment.
    
    DPIPortC<DataT> &Port()
    { return port; }
    //: Access port.
    
    virtual bool SetPort(const DPIPortBaseC &nport) { 
      port = DPIPortC<DataT>(const_cast<DPIPortBaseC &>(nport));
      return port.IsValid();
    }
    //: set port.
    
  private:
    DPIPortC<DataT> &port;
  };
  
  ////////////////////////////////////
  //! userlevel=Advanced
  //: Plug.
  // Used for setting up inputs.
  
  template<class DataT>
  class DPIPlugC 
    : public DPIPlugBaseC
  {
  public:
    explicit DPIPlugC(const DPIPortC<DataT> &nport,const DPEntityC &nhold = DPEntityC(true))
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
  //! userlevel=Develop
  //: Plug.
  // Used for setting up inputs.
  
  template<class DataT>
  class DPOPlugBodyC 
    : public DPOPlugBaseBodyC
  {
  public:
    explicit DPOPlugBodyC(const DPOPortC<DataT> &nport,const DPEntityC &nhold)
      : DPOPlugBaseBodyC(nhold),
	port(const_cast<DPOPortC<DataT> &>(nport))
    {}
    //: Constructor.

    DPOPortC<DataT> &Port()
    { return port; }
    //: Access handle to port.
    
    virtual bool SetPort(const DPOPortBaseC &nport) { 
      port = DPOPortC<DataT>(const_cast<DPOPortBaseC &>(nport));
      return port.IsValid();
    }
    //: set port.
    
  private:
    DPOPortC<DataT> &port;
  };
  
  ////////////////////////////////////
  //! userlevel=Advanced
  //: Plug.
  // Used for setting up inputs.
  
  template<class DataT>
  class DPOPlugC 
    : public DPOPlugBaseC
  {
  public:
    explicit DPOPlugC(const DPOPortC<DataT> &nport,const DPEntityC &nhold = DPEntityC(true))
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
