// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DFOBJECT_HEADER
#define RAVL_DFOBJECT_HEADER 1
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/DFObject.hh"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/IndexRange2d.hh"
#include "Ravl/String.hh"
#include "Ravl/DList.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/Stream.hh"
#include "Ravl/XMLStream.hh"
#include "Ravl/DP/AttributeCtrl.hh"

namespace RavlDFN {
  using namespace RavlN;
  using namespace RavlGUIN;
  
  enum DFRenderModeT { DFRM_NORMAL,DFRM_SELECTED,DFRM_SHADED };
  //: Render modes.
  
  enum DFAttachPlacementT { ATTACH_TOP,ATTACH_BOTTOM,ATTACH_LEFT,ATTACH_RIGHT, ATTACH_FLOAT };
  
  enum DFMouseActionT { DFMA_NONE,DFMA_SELECTDRAG,DFMA_LINK };
  
  class GUIViewBodyC;
  class DFAttachC;
  class DFObjectC;
  class FactoryC;
  class DFSystemC;
  
  //! userlevel=Develop
  //: Abstract handle for data flow object.

  class DFObjectBodyC
    : public RCBodyVC
  {
  public:
    DFObjectBodyC();
    //: Default constructor.

    DFObjectBodyC(const StringC &nname);
    //: Create named object.
    
    DFObjectBodyC(istream &strm);
    //: Load from stream.
    
    DFObjectBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    DFObjectBodyC(XMLIStreamC &is,DFSystemC &context);
    //: Read from istream.
    
    virtual bool Save(XMLOStreamC &strm,bool inCharge = true) const;
    //: Save ostream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    bool Init(FactoryC &factory);
    //: Initalise with info from a factory.
    // This is used to setup icons, and default settings..
    
    virtual bool Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode);
    //: Render object to view.
    
    virtual DFMouseActionT MouseClick(GUIViewBodyC &view,const  MouseEventC &me);
    //: Process a mouse click.
    
    const StringC &Name() const
    { return name; }
    //: Access name of object.
    
    const IndexRange2dC &RenderSize() const
    { return renderSize; }
    //: Get the total size of the object.
    // This may be larger than the packing size.
    
    const IndexRange2dC &PackingSize() const
    { return packingSize; }
    //: This is the size to use for packing the widget.
    
    const IndexRange2dC &InvolveRenderSize(const IndexRange2dC &rect)
    { renderSize.Involve(rect); return renderSize; }
    //: Involve in the render rectangle.
    // NB. This is reset by the render method.
    
    virtual DListC<DFAttachC> Parts() const;
    //: Get list of attachment points.
    
    virtual DFObjectC LinkTo(const DFObjectC &obj,DFSystemC &system,bool autoConvert = false);
    //: Attempt to link to another object.
    
    virtual Index2dC AttachPoint() const;
    //: Get attachment point.
    
    virtual AttributeCtrlC AttributeCtrl();
    //: Access attribute control for object if it exists.
    // Returns an invalid handle if none.
  protected:
    const IndexRange2dC &RenderSize(const IndexRange2dC &size)
    { return renderSize = size; }
    //: Set the render size.
    
    const IndexRange2dC &RenderSize(const Index2dC &size)
    { return renderSize = IndexRange2dC(Index2dC(0,0),size); }
    //: Set the render size.
    
    const IndexRange2dC &PackingSize(const IndexRange2dC &size) { 
      renderSize.Involve(size); // Make sure its at least the packing size.
      return packingSize = size;
    }
    //: Set the packing size.
    
    const IndexRange2dC &PackingSize(const Index2dC &size) 
    { return PackingSize(IndexRange2dC(Index2dC(0,0),size)); }
    //: Set the packing size.
    
    StringC name;
    IndexRange2dC renderSize;
    IndexRange2dC packingSize;
  };

  //! userlevel=Normal
  //: Abstract handle for data flow object.
  
  class DFObjectC
    : public RCHandleVC<DFObjectBodyC>
  {
  public:
    DFObjectC()
    {}
    //: Default constructor
    // Creates an invalid handle.
    
    DFObjectC(istream &strm);
    //: Construct from a stream.
    
    DFObjectC(BinIStreamC &strm);    
    //: Construct from a binary stream.
    
  protected:
    DFObjectC(DFObjectBodyC &bod)
      : RCHandleVC<DFObjectBodyC>(bod)
    {}
    //: Body constructor.
    
    DFObjectC(const DFObjectBodyC *bod)
      : RCHandleVC<DFObjectBodyC>(bod)
    {}
    //: Body constructor.
    
    DFObjectBodyC &Body()
    { return RCHandleVC<DFObjectBodyC>::Body(); }
    //: Access body.

    const DFObjectBodyC &Body() const
    { return RCHandleVC<DFObjectBodyC>::Body(); }
    //: Access body.
    
  public:
    bool Save(XMLOStreamC &strm,bool inCharge = true) const
    { return Body().Save(strm,inCharge); }
    //: Save ostream.
    
    bool Save(BinOStreamC &strm) const
    { return Body().Save(strm); }
    //: Save ostream.
    
    bool Save(ostream &strm) const
    { return Body().Save(strm); }
    //: Save ostream.
    
    bool Init(FactoryC &factory)
    { return Body().Init(factory); }
    //: Initalise with info from a factory.
    // This is used to setup icons, and default settings..
    
    bool Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode)
    { return Body().Render(view,at,mode); }
    //: Render object to view.
    
    DFMouseActionT MouseClick(GUIViewBodyC &view,const  MouseEventC &me)
    { return Body().MouseClick(view,me); }
    //: Process a mouse click.
    
    const StringC &Name() const
    { return Body().Name(); }
    //: Access name of object.
    
    const IndexRange2dC &RenderSize() const
    { return Body().RenderSize(); }
    //: Get the size of this object.
    
    const IndexRange2dC &PackingSize() const
    { return Body().PackingSize(); }
    //: This is the size to use for packing the widget.

    const IndexRange2dC &InvolveRenderSize(const IndexRange2dC &rect)
    { return Body().InvolveRenderSize(rect); }
    //: Involve in the render rectangle.
    // NB. This is reset by the render method.
    
    inline DListC<DFAttachC> Parts() const;
    //: Get list of attachment points.
    
    DFObjectC LinkTo(const DFObjectC &obj,DFSystemC &system,bool autoConvert = false) 
    { return Body().LinkTo(obj,system,autoConvert); }
    //: Attempt to link to another object.
    
    Index2dC AttachPoint() const
    { return Body().AttachPoint(); }
    //: Get attachment point.
    
    bool operator==(const DFObjectC &obj) const
    { return &Body() == &obj.Body(); }
    //: Compair handles.
    
    bool operator!=(const DFObjectC &obj) const
    { return &Body() != &obj.Body(); }
    //: Compair handles.
    
    AttributeCtrlC AttributeCtrl()
    { return Body().AttributeCtrl(); }
    //: Access attribute control for object if it exists.
    // Returns an invalid handle if none.
    
  };
  
  BinOStreamC &operator<<(BinOStreamC &strm,const DFObjectC &dfo);
  //: Write DFObjectC to stream.
  
  BinIStreamC &operator>>(BinIStreamC &strm,DFObjectC &dfo);
  //: Read DFObject from stream.

  ostream &operator<<(ostream &strm,const DFObjectC &dfo);
  //: Write DFObjectC to stream.
  
  istream &operator>>(istream &strm,DFObjectC &dfo);
  //: Read DFObject from stream.
  
  ///////////////////////////////////////////////////////////////////////

  //! userlevel=Normal
  //: Attachment point descriptor.
  
  class DFAttachBodyC
    : public RCBodyC
  {
  public:
    DFAttachBodyC(const DFObjectC &obj,const Index2dC &offset,DFAttachPlacementT placement);
    //: Attachment point.
    
    DFAttachBodyC(const DFObjectC &obj,DFAttachPlacementT placement);
    //: Attachment point.
    
    DFAttachBodyC(BinIStreamC &strm);
    //: Load from stream.
    
    DFAttachBodyC(istream &strm);
    //: Load from stream.
    
    bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    const DFObjectC &Object() const
    { return object; }
    //: Attached object.
    
    DFObjectC &Object()
    { return object; }
    //: Attached object.
    
    const Index2dC &Offset() const
    { return offset; }
    //: Offset of attachment point.

    Index2dC &Offset()
    { return offset; }
    //: Offset of attachment point.
    
    DFAttachPlacementT Placement() const
    { return placement; }
    //: Get placement.
    
  protected:
    DFObjectC object;
    Index2dC offset;
    DFAttachPlacementT placement;
  };
  
  //! userlevel=Normal
  //: Attachment point descriptor.
  
  class DFAttachC
    : public RCHandleC<DFAttachBodyC>
  {
  public:
    DFAttachC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    DFAttachC(const DFObjectC &object,const Index2dC &offset,DFAttachPlacementT placement = ATTACH_FLOAT)
      : RCHandleC<DFAttachBodyC>(*new DFAttachBodyC(object,offset,placement))
    {}
    //: Attachment point.
    
    DFAttachC(const DFObjectC &object,DFAttachPlacementT placement = ATTACH_FLOAT)
      : RCHandleC<DFAttachBodyC>(*new DFAttachBodyC(object,placement))
    {}
    //: Attachment point.
    
    DFAttachC(BinIStreamC &strm)
      : RCHandleC<DFAttachBodyC>(*new DFAttachBodyC(strm))
    {}
    //: Load from stream.
    
    DFAttachC(istream &strm)
      : RCHandleC<DFAttachBodyC>(*new DFAttachBodyC(strm))
    {}
    //: Load from stream.
    
  protected:
    DFAttachBodyC &Body()
    { return RCHandleC<DFAttachBodyC>::Body(); }
    //: Access body.
    
    const DFAttachBodyC &Body() const
    { return RCHandleC<DFAttachBodyC>::Body(); }
    //: Access body.
    
  public:
    bool Save (ostream &out) const
    { return Body().Save(out); }
    //: Writes object to stream, can be loaded using constructor
    
    bool Save (BinOStreamC &out) const
    { return Body().Save(out); }
    //: Writes object to stream, can be loaded using constructor
    
    const Index2dC &Offset() const
    { return Body().Offset(); }
    //: Offset of attachment point.
    
    Index2dC &Offset()
    { return Body().Offset(); }
    //: Offset of attachment point.

    const DFObjectC &Object() const
    { return Body().Object(); }
    //: Attached object.
    
    DFObjectC &Object()
    { return Body().Object(); }
    //: Attached object.
    
    DFAttachPlacementT Placement() const
    { return Body().Placement(); }
    //: Get placement.
    
  };
  
  ostream &operator<<(ostream &strm,const DFAttachC &dfa);
  //: Write to an ostream.
  
  istream &operator>>(istream &strm,DFAttachC &dfa);
  //: Read from an istream.
  
  BinOStreamC &operator<<(BinOStreamC &strm,const DFAttachC &dfa);
  //: Write to an ostream.
  
  BinIStreamC &operator>>(BinIStreamC &strm,DFAttachC &dfa);
  //: Read from an istream.
  
  ////////////////////////////////////////////////////
  
  inline DListC<DFAttachC> DFObjectC::Parts() const
  { return Body().Parts(); }
  //: Get list of attachment points.
  
}


#endif
