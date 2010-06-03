// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: ViewElement.cc 6026 2007-01-24 12:10:20Z craftit $"
//! lib=RavlVDF
//! author="Charles Galambos"
//! file="Ravl/Applications/VisualDataFlow/ViewElement.cc"

#include "Ravl/DF/ViewElement.hh"
#include "Ravl/Stream.hh"
#include "Ravl/IndexRange2d.hh"
#include "Ravl/DF/GUIView.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {

  //: Default constructor.
  
  ViewElementBodyC::ViewElementBodyC()
    : at(0,0),
      component(false),
      selected(false)
  {}
  
  //: Constructor view for object.
  
  ViewElementBodyC::ViewElementBodyC(const DFObjectC &nobj,const Index2dC &nat)
    : object(nobj),
      at(nat),
      component(false),
      selected(false)
  {
    ONDEBUG(cerr << "ViewElementBodyC::ViewElementBodyC(), Object=" << nobj.Name() << " At=" << at << "\n");
  }
  
  //: Test if this view element contains 'pos'.
  
  bool ViewElementBodyC::Contains(const Index2dC &pos) const {
    ONDEBUG(cerr <<"ViewElementBodyC::Contains(" << pos << "), At=" << at << " Size=" << object.RenderSize() << "\n");
    Index2dC off = pos - at;
    return object.RenderSize().Contains(off);
  }
  
  //: Test if rectangle overlaps this widget.
  
  bool ViewElementBodyC::Intersects(const IndexRange2dC &area) const 
  { return Frame().IsOverlapping(area); }
  
  //: Move object to new position.
  
  void ViewElementBodyC::Move(const Index2dC &nat) {
    Index2dC diff = nat - at;
    at = nat;
    for(DLIterC<ViewElementC> it(parts);it;it++) {
      if(!it->Component())
	continue;
      it->Move(it->At() + diff);
    }
  }
  
  //: Bounding box for area we're rendering into.
  
  IndexRange2dC ViewElementBodyC::Frame() const {
    if(!object.IsValid())
      return IndexRange2dC(at[0],at[0],at[1],at[1]);
    // Might be worth caching the rectangle.
    IndexRange2dC ret = object.RenderSize() + at;
    //cerr << "ViewElementBodyC::Frame() Base=" << ret << "\n";
    for(DLIterC<ViewElementC> it(parts);it;it++) {
      //cerr << "ViewElementBodyC::Frame()   Part=" << it->Frame() << "\n";
      ret.Involve(it->Frame());
    }
    //cerr << "ViewElementBodyC::Frame() +Parts=" << ret << "\n";
    return ret;
  }
  
  bool ViewElementBodyC::Render(GUIViewBodyC &view) {
    if(!object.IsValid()) {
      cerr << "ViewElementBodyC::Render(), Asked to render invalid object. \n";
      return false;
    }
    //if(component)
    //  return true; // Don't render this object now.
    bool ret;
    if(selected)
      ret = object.Render(view,at,DFRM_SELECTED);
    else
      ret = object.Render(view,at,DFRM_NORMAL);
    for(DLIterC<ViewElementC> it(parts);it;it++) {
      //      if(!it->Component())
      ret &= it->Render(view);
    }
    return ret;
  }
  
  //: Mouse click.
  
  DFMouseActionT ViewElementBodyC::MouseClick(GUIViewBodyC &view,const MouseEventC &me) {
    if(!object.IsValid()) {
      cerr << "ViewElementBodyC::MouseClick(), ERROR: No object. \n";
      return DFMA_NONE;
    }
    MouseEventC nme(nme.Col() - at.Col(),nme.Row() - at.Row(),nme.RawState(),nme.RawChanged(),nme.Time());
    return object.MouseClick(view,nme);
  }

  //: Add part.
  
  bool ViewElementBodyC::AddPart(const ViewElementC &part) { 
    parts.InsFirst(part);
    return true;
  }
  
  //: Remove part.
  
  bool ViewElementBodyC::DelPart(const ViewElementC &part) {
    parts.Del(part);
    return true;
  }
  
  //: Disconnect all refrences.
  
  bool ViewElementBodyC::Disconnect() {
    object.Invalidate();
    parts.Empty();
    return true;
  }

  //: Make a list of all parts in the view element.
  
  DListC<ViewElementC> ViewElementBodyC::AllParts() const {
    DListC<ViewElementC> ret;
    for(DLIterC<ViewElementC> it(parts);it;it++) {
      ret.InsLast(*it);
      DListC<ViewElementC> parts = it->AllParts();
      ret.MoveLast(parts);
    }
    return ret;
  }
  
  ////////////////////////////////////////////////////////////////////////
  
  //: Constructor
  
  ViewLinkBodyC::ViewLinkBodyC(const ViewElementC &source,const ViewElementC &dest,const DFObjectC &obj)
    : ViewElementBodyC(obj,Index2dC(0,0)),
      src(source),
      dst(dest)
  {
    src.AddPart(ViewLinkC(*this));
    dst.AddPart(ViewLinkC(*this));
    ONDEBUG(cerr << "ViewLinkBodyC::ViewLinkBodyC(), Called. \n");
  }
  
  //: Render object in view.
  
  bool ViewLinkBodyC::Render(GUIViewBodyC &view) {
    //ONDEBUG(cerr << "ViewLinkBodyC::Render(GUIViewBodyC &), Called. \n");
    view.DrawLine(view.DrawGCBlack(),src.AttachPoint(),dst.AttachPoint());
    //cerr << "ViewLinkBodyC::Render(GUIViewBodyC &), Called. From:"  << src.AttachPoint() << " to " << dst.AttachPoint() << " \n";
    return true;
  }
  
  //: Bounding box for area we're rendering into.
  
  IndexRange2dC ViewLinkBodyC::Frame() const {
    //cerr << "ViewLinkBodyC::Frame(), Called \n";
    if(!src.IsValid() || !dst.IsValid())
      return IndexRange2dC();
    IndexRange2dC ret(src.AttachPoint(),0);
    ret.Involve(dst.AttachPoint());
    //cerr << "ViewLinkBodyC::Frame(), Rect=" << ret << "\n";
    return ret.Expand(1);
  }

  //: Disconnect all refrences.
  
  bool ViewLinkBodyC::Disconnect() {
    if(!ViewElementBodyC::Disconnect())
      return false;
    src.DelPart(ViewLinkC(*this));
    dst.DelPart(ViewLinkC(*this));
    src.Invalidate();
    dst.Invalidate();
    return true;
  }
  
}
