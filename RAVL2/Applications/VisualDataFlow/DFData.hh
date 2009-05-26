// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_DFDATA_HEADER
#define RAVLDF_DFDATA_HEADER 1
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/DFData.hh"

#include "Ravl/DF/DFObject.hh"
#include "Ravl/RCWrap.hh"

namespace RavlDFN {
  
  //! userlevel=Develop
  //: Data object.
  
  class DFDataBodyC
    : public DFObjectBodyC 
  {
  public:
    DFDataBodyC(const StringC &nname,const RCWrapAbstractC &ndata);
    //: Construct from name and data.
    
    DFDataBodyC(istream &strm);
    //: Load from stream.
    
    DFDataBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode);
    //: Render object to view.
    
    RCWrapAbstractC &Data()
    { return data; }
    //: Access data.
    
  protected:
    RCWrapAbstractC data;
  };
  
  //! userlevel=Normal
  //: Data object.
  
  class DFDataC 
    : public DFObjectC
  {
  public:
    DFDataC()
    {}
    //: Default constructor.
    
    DFDataC(const StringC &name,const RCWrapAbstractC &data)
      : DFObjectC(*new DFDataBodyC(name,data))
    {}
    //: Constructor.

  protected:
    DFDataC(DFDataBodyC &bod)
      : DFObjectC(bod)
    {}
    //: Body constructor.
    
    DFDataBodyC &Body()
    { return static_cast<DFDataBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
    const DFDataBodyC &Body() const
    { return static_cast<const DFDataBodyC &>(DFObjectC::Body()); }
    //: Access body.
    
  public:
    
    RCWrapAbstractC &Data()
    { return Body().Data(); }
    //: Access data.
    
  };
}


#endif
