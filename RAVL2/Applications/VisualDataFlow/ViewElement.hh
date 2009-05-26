// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDF_VIEWELEMENT_HEADER
#define RAVLDF_VIEWELEMENT_HEADER 1
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/ViewElement.hh"

#include "Ravl/RCHandleV.hh"
#include "Ravl/IndexRange2d.hh"
#include "Ravl/DF/DFObject.hh"

namespace RavlDFN {

  class ViewElementC;
  
  //! userlevel=Normal
  //: Element in a view.
  
  class ViewElementBodyC
    : public RCBodyVC
  {
  public:
    ViewElementBodyC();
    //: Default constructor.

    ViewElementBodyC(const DFObjectC &nobj,const Index2dC &nat);
    //: Constructor view for object.
    
    virtual bool Render(GUIViewBodyC &view);
    //: Render object in view.
    
    virtual DFMouseActionT MouseClick(GUIViewBodyC &view,const  MouseEventC &me);
    //: Mouse click.
    
    const Index2dC &At() const
    { return at; }
    //: Get location of object.
    
    bool Contains(const Index2dC &pos) const;
    //: Test if this view element contains 'pos'.
    
    bool Intersects(const IndexRange2dC &area) const;
    //: Test if rectangle overlaps this widget.
    
    void Move(const Index2dC &at);
    //: Move object to new position.
    
    virtual IndexRange2dC Frame() const;
    //: Bounding box for area we're rendering into.
    
    bool Selected() const
    { return selected; }
    //: Get selected status.
    
    bool Selected(bool state)
    { return selected = state; }
    //: Change selected status.
    
    const DFObjectC &Object() const
    { return object; }
    //: Access object.
    
    bool Component(bool ncomponent)
    { return component = ncomponent; }
    //: Set component flag
    
    bool Component()
    { return component; }
    //: Get component flag
    
    DListC<ViewElementC> &Parts()
    { return parts; }
    //: Access list of parts.
    
    bool AddPart(const ViewElementC &part);
    //: Add part.
    
    bool DelPart(const ViewElementC &part);
    //: Remove part.
    
    virtual bool Disconnect();
    //: Disconnect all refrences.
    
    Index2dC AttachPoint() const
    { return at + object.AttachPoint(); }
    //: Get attachment point.
    
    DListC<ViewElementC> AllParts() const;
    //: Make a list of all parts in the view element.
    // The returned list is generated recursively,
    // and so may be modified without any side effects.
    
    StringC Name() const { 
      RavlAssert(object.IsValid());
      return object.Name(); 
    }
    //: Get name of view element.
    
  protected:
    DFObjectC object; // Object we're attached to.
    Index2dC at; // Position of object.
    bool component; // A component of a larger part ?
    bool selected; // Is the object selected ?    
    DListC<ViewElementC> parts;
  };
  
  //! userlevel=Normal
  //: Element in a view.
  
  class ViewElementC
    : public RCHandleC<ViewElementBodyC>
  {
  public:
    ViewElementC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    ViewElementC(const DFObjectC &obj,const Index2dC &at = Index2dC(0,0))
      : RCHandleC<ViewElementBodyC>(*new ViewElementBodyC(obj,at))
    {}
    //: Create a new element for object 'obj'.
    
  protected:
    ViewElementC(ViewElementBodyC &bod)
      : RCHandleC<ViewElementBodyC>(bod)
    {}
    //: Body constructor.
    
    ViewElementBodyC &Body()
    { return RCHandleC<ViewElementBodyC>::Body(); }
    //: Access body.
    
    const ViewElementBodyC &Body() const
    { return RCHandleC<ViewElementBodyC>::Body(); }
    //: Access body.
    
  public:
    
    bool Render(GUIViewBodyC &view)
    { return Body().Render(view); }
    //: Render object in view.
    
    DFMouseActionT MouseClick(GUIViewBodyC &view,const  MouseEventC &me)
    { return Body().MouseClick(view,me); }
    //: Mouse click.
    
    const Index2dC &At() const
    { return Body().At(); }
    //: Get location of object.
    
    IndexRange2dC Frame() const
    { return Body().Frame(); }
    //: Bounding box for area we're rendering into.
    
    bool Contains(const Index2dC &pos) const
    { return Body().Contains(pos); }
    //: Test if this view element contains 'pos'.
    
    bool Intersects(const IndexRange2dC &area) const
    { return Body().Intersects(area); }
    //: Test if rectangle overlaps this widget.
    
    void Move(const Index2dC &at)
    { Body().Move(at); }
    //: Move object to new position.
    
    bool Selected() const
    { return Body().Selected(); }
    //: Get selected status.
    
    bool Selected(bool state)
    { return Body().Selected(state); }
    //: Change selected status.
    
    const DFObjectC &Object() const
    { return Body().Object(); }
    //: Access object.
    
    bool Component(bool ncomponent)
    { return Body().Component(ncomponent); }
    //: Set component flag
    
    bool Component()
    { return Body().Component(); }
    //: Get component flag
    
    DListC<ViewElementC> &Parts()
    { return Body().Parts(); }
    //: Access list of parts.
    
    bool AddPart(const ViewElementC &part)
    { return Body().AddPart(part); }
    //: Add part.
    
    bool DelPart(const ViewElementC &part)
    { return Body().DelPart(part); }
    //: Remove part.
    
    bool Disconnect()
    { return Body().Disconnect(); }
    //: Disconnect all refrences.
    
    Index2dC AttachPoint() const
    { return Body().AttachPoint(); }
    //: Get attachment point.
    
    DListC<ViewElementC> AllParts() const
    { return Body().AllParts(); }
    //: Make a list of all parts in the view element.
    // The returned list is generated recursively,
    // and so may be modified without any side effects.
    
    StringC Name() const 
    { return Body().Name(); }
    //: Get name of view element.
    
    friend class ViewElementBodyC;
  };

  //////////////////////////////////////////////////////////
  
  //! userlevel=Develop
  //: View of link between objects.
  
  class ViewLinkBodyC
    : public ViewElementBodyC
  {
  public:
    ViewLinkBodyC(const ViewElementC &source,
		    const ViewElementC &dest,
		    const DFObjectC &obj
		    );
    //: Constructor
    
    const ViewElementC &Source() const
    { return src; }
    //: Source of link.
    
    const ViewElementC &Destination() const
    { return dst; }
    //: Destination of link.
    
    virtual bool Render(GUIViewBodyC &view);
    //: Render object in view.
    
    virtual IndexRange2dC Frame() const;
    //: Bounding box for area we're rendering into.
    
    virtual bool Disconnect();
    //: Disconnect all refrences.
    
  protected:
    ViewElementC src;
    ViewElementC dst;
  };
  
  //! userlevel=Normal
  //: View of link between objects.

  class ViewLinkC
    : public ViewElementC
  {
  public:
    ViewLinkC(const ViewElementC &source,const ViewElementC &dest,const DFObjectC &obj)
      : ViewElementC(*new ViewLinkBodyC(source,dest,obj))
    {}
    //: Constructor
    
  protected:
    ViewLinkC(ViewLinkBodyC &bod)
      : ViewElementC(bod)
    {}
    //: Body constructor.
    
    ViewLinkBodyC &Body()
    { return static_cast<ViewLinkBodyC &>(ViewElementC::Body()); }
    //: Access body.
    
    const ViewLinkBodyC &Body() const
    { return static_cast<const ViewLinkBodyC &>(ViewElementC::Body()); }
    //: Access body.
    
  public:
    const ViewElementC &Source() const
    { return Body().Source(); }
    //: Source of link.
    
    const ViewElementC &Destination() const
    { return Body().Destination(); }
    //: Destination of link.
    
    friend class ViewLinkBodyC;
  };
}

#endif
