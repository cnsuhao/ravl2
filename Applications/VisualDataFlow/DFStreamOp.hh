// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_DFSTREAMOP_HEADER
#define RAVLDF_DFSTREAMOP_HEADER 1
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"

#include "Ravl/DF/DFObject.hh"
#include "Ravl/RCWrap.hh"
#include "Ravl/DP/StreamOp.hh"

namespace RavlDFN {
  
  //! userlevel=Develop
  //: Data object.
  
  class DFStreamOpBodyC
    : public DFObjectBodyC 
  {
  public:
    DFStreamOpBodyC(const StringC &nname,const DPStreamOpC &sop);
    //: Construct from name and data.
    
    bool Init(const DPStreamOpC &sop);
    //: Setup stream operator.
    
    virtual bool Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode);
    //: Render object to view.
    
    virtual DListC<DFAttachC> Parts() const;
    //: Get list of attachment points.
    
  protected:
    bool packStacked;
    DPStreamOpC streamOp;
    
    DListC<DFAttachC> parts;
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
    
  };
}


#endif
