// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_DFLINK_HEADER
#define RAVLDF_DFLINK_HEADER 1
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/DFLink.hh"

#include "Ravl/DF/DFObject.hh"

namespace RavlDFN {
  
  //! userlevel=Develop
  //: Link between processing elements.
  
  class DFLinkBodyC
    : public DFObjectBodyC
  {
  public:
    DFLinkBodyC(const DFObjectC &src,const DFObjectC &dst);
    //: Create link.
    
    ~DFLinkBodyC();
    //: Destructor.
    
    DFLinkBodyC(XMLIStreamC &is,DFSystemC &context);
    //: Read from istream.
    
    virtual bool Save(XMLOStreamC &strm,bool inCharge = true) const;
    //: Save ostream.
    
    const DFObjectC &Source() const
    { return src; }
    //: Source of link.
    
    const DFObjectC &Destination() const
    { return dst; }
    //: Destination of link.
    
    virtual bool Render(GUIViewBodyC &view,const Index2dC &at);
    //: Render object to view.
    
    bool Connect();
    //: Connect link.
    
    bool Disconnect();
    //: Disconnect link.
    
    bool IsConnected() const
    { return connected; }
    //: Is this link in place ?
    
  protected:
    DFObjectC src;
    DFObjectC dst;
    bool connected;
  };
  
  //! userlevel=Develop
  //: Link between processing elements.
  
  class DFLinkC
    : public DFObjectC 
  {
  public:
    DFLinkC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DFLinkC(const DFObjectC &src,const DFObjectC &dst)
      : DFObjectC(*new DFLinkBodyC(src,dst))
    {}
    //: Create a link between two objects.
    
    DFLinkC(const DFObjectC &obj)
      : DFObjectC(dynamic_cast<const DFLinkBodyC *>(BodyPtr(obj)))
    {}
    //: Create from base class.
    // If object types don't match an invalid handle will be created.
    
  protected:
    DFLinkC(DFLinkBodyC &bod)
      : DFObjectC(bod)
    {}
    //: Body constructor.
    
    DFLinkC(const DFLinkBodyC *bod)
      : DFObjectC(bod)
    {}
    //: Body constructor.
    
    DFLinkBodyC &Body()
    { return static_cast<DFLinkBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
    const DFLinkBodyC &Body() const
    { return static_cast<const DFLinkBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
  public:
    
    const DFObjectC &Source() const
    { return Body().Source(); }
    //: Source of link.
    
    const DFObjectC &Destination() const
    { return Body().Destination(); }
    //: Destination of link.

    bool Connect()
    { return Body().Connect(); }
    //: Connect link.
    
    bool Disconnect()
    { return Body().Disconnect(); }
    //: Disconnect link.
    
    bool IsConnected() const
    { return Body().IsConnected(); }
    //: Is this link in place ?

  };
}


#endif
