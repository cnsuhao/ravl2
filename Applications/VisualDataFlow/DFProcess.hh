// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_DFOBJECTPROCESS_HEADER
#define RAVLDF_DFOBJECTPROCESS_HEADER 1
//! rcsid="$Id: DFProcess.hh 3349 2003-08-26 21:13:51Z craftit $"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/DFProcess.hh"

#include "Ravl/DF/DFObject.hh"
#include "Ravl/RCWrap.hh"

namespace RavlDFN {
  
  //! userlevel=Develop
  //: Data object.
  
  class DFProcessBodyC
    : public DFObjectBodyC 
  {
  public:
    DFProcessBodyC(const StringC &nname);
    //: Construct from name and data.
    
    virtual bool Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode);
    //: Render object to view.
    
    virtual DListC<DFAttachC> Parts() const;
    //: Get list of attachment points.
    
#if 0
    virtual AttributeCtrlC AttributeCtrl();
    //: Access attribute control for object if it exists.
    // Returns an invalid handle if none.
#endif
    
  protected:
    DListC<DFAttachC> parts;
  };
  
  //! userlevel=Normal
  //: Data object.
  
  class DFProcessC 
    : public DFObjectC
  {
  public:
    DFProcessC()
    {}
    //: Default constructor.
    
    DFProcessC(const StringC &name)
      : DFObjectC(*new DFProcessBodyC(name))
    {}
    //: Constructor.
    
  protected:
    DFProcessC(DFProcessBodyC &bod)
      : DFObjectC(bod)
    {}
    //: Body constructor.
    
    DFProcessBodyC &Body()
    { return static_cast<DFProcessBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
    const DFProcessBodyC &Body() const
    { return static_cast<const DFProcessBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
  public:
    
  };
}

#endif
