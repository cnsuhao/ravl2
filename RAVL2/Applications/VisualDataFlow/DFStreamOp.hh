// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_DFSTREAMOP_HEADER
#define RAVLDF_DFSTREAMOP_HEADER 1
//! rcsid="$Id: DFStreamOp.hh 3349 2003-08-26 21:13:51Z craftit $"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/DFStreamOp.hh"

#include "Ravl/DF/DFObject.hh"
#include "Ravl/RCWrap.hh"
#include "Ravl/DP/StreamOp.hh"
#include "Ravl/Hash.hh"
#include "Ravl/DF/DFPort.hh"

namespace RavlDFN {
  
  //! userlevel=Develop
  //: Data object.
  
  class DFStreamOpBodyC
    : public DFObjectBodyC 
  {
  public:
    DFStreamOpBodyC(const StringC &nname,const DPStreamOpC &sop);
    //: Construct from name and data.
    
    DFStreamOpBodyC(istream &strm);
    //: Load from stream.
    
    DFStreamOpBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save(XMLOStreamC &strm,bool inCharge) const;
    //: Save ostream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    bool Init(const DPStreamOpC &sop);
    //: Setup stream operator.
    
    virtual bool Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode);
    //: Render object to view.
    
    virtual DListC<DFAttachC> Parts() const;
    //: Get list of attachment points.
    
    DFIPortC IPort(const DPIPortBaseC &ip) const;
    //: Find DFIPort corresponding to 'ip'.
    // Returns an invalid handle if not found.
    
    DFOPortC OPort(const DPOPortBaseC &ip) const;
    //: Find DFIPort corresponding to 'ip'.
    // Returns an invalid handle if not found.
    
    DFIPlugC IPlug(const DPIPlugBaseC &ip) const;
    //: Find DFIPort corresponding to 'ip'.
    // Returns an invalid handle if not found.
    
    DFOPlugC OPlug(const DPOPlugBaseC &ip) const;
    //: Find DFIPort corresponding to 'ip'.
    // Returns an invalid handle if not found.
    
    virtual AttributeCtrlC AttributeCtrl();
    //: Access attribute control for object if it exists.
    // Returns an invalid handle if none.
    
  protected:
    bool packStacked;
    DPStreamOpC streamOp;
    
    DListC<DFAttachC> parts;
    
    HashC<DPIPortBaseC,DFIPortC> iports;
    HashC<DPOPortBaseC,DFOPortC> oports;
    HashC<DPIPlugBaseC,DFIPlugC> iplugs;
    HashC<DPOPlugBaseC,DFOPlugC> oplugs;
  };
  
  //! userlevel=Normal
  //: Data object.
  
  class DFStreamOpC 
    : public DFObjectC
  {
  public:
    DFStreamOpC()
    {}
    //: Default constructor.
    
    DFStreamOpC(const StringC &name,const DPStreamOpC &sop)
      : DFObjectC(*new DFStreamOpBodyC(name,sop))
    {}
    //: Constructor.
    
  protected:
    DFStreamOpC(DFStreamOpBodyC &bod)
      : DFObjectC(bod)
    {}
    //: Body constructor.
    
    DFStreamOpBodyC &Body()
    { return static_cast<DFStreamOpBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
    const DFStreamOpBodyC &Body() const
    { return static_cast<const DFStreamOpBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
  public:
    DFIPortC IPort(const DPIPortBaseC &ip) const
    { return Body().IPort(ip); }
    //: Find DFIPort corresponding to 'ip'.
    // Returns an invalid handle if not found.
    
    DFOPortC OPort(const DPOPortBaseC &ip) const
    { return Body().OPort(ip); }
    //: Find DFIPort corresponding to 'ip'.
    // Returns an invalid handle if not found.
    
    DFIPlugC IPlug(const DPIPlugBaseC &ip) const
    { return Body().IPlug(ip); }
    //: Find DFIPort corresponding to 'ip'.
    // Returns an invalid handle if not found.
    
    DFOPlugC OPlug(const DPOPlugBaseC &ip) const
    { return Body().OPlug(ip); }
    //: Find DFIPort corresponding to 'ip'.
    // Returns an invalid handle if not found.
    
  };
}


#endif
