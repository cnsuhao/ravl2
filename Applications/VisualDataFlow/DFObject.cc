// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"

#include "Ravl/DF/DFObject.hh"
#include "Ravl/DF/GUIView.hh"
#include <gtk/gtk.h>

namespace RavlDFN {
  
  //: Attachment point.
  
  DFAttachBodyC::DFAttachBodyC(const DFObjectC &nobj,const Index2dC &noffset,DFAttachPlacementT nplacement)
    : object(nobj),
      offset(noffset),
      placement(nplacement)
  {}
  
  //: Attachment point.
  
  DFAttachBodyC::DFAttachBodyC(const DFObjectC &nobj,DFAttachPlacementT nplacement) 
    : object(nobj),
      offset(0,0),
      placement(nplacement)
  {}
  
  ////////////////////////////////////////////////////////////////////////
  
  //: Default constructor.
  
  DFObjectBodyC::DFObjectBodyC()
    : renderSize(10,10),
      packingSize(10,10)
  {}
  
  //: Create a named object.
  
  DFObjectBodyC::DFObjectBodyC(const StringC &nname)
    : name(nname),
      renderSize(10,10),
      packingSize(10,10)
  {}
  
  //: Initalise with info from a factory.
  // This is used to setup icons, and default settings..
  
  bool DFObjectBodyC::Init(FactoryC &factory) {
    cerr << "DFObjectBodyC::Init(), Called \n";
    return true;
  }
  
  //: Render object to view.
  
  bool DFObjectBodyC::Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode) {
    int x = at[0].V();
    int y = at[1].V();
    GdkGC *bggc;
    switch(mode) {
    case DFRM_NORMAL: bggc = view.DrawGCWhite(); break;
    case DFRM_SELECTED: bggc = view.DrawGCGrey(); break;
    case DFRM_SHADED: bggc = view.DrawGCGrey(); break;
    default:
      bggc = view.DrawGCGrey(); break;
    }
    gdk_draw_rectangle(view.DrawWindow(),
		       bggc,1,
		       x,y,
		       10,10);
    gdk_draw_rectangle(view.DrawWindow(),
		       view.DrawGCBlack(),0,
		       x,y,
		       10,10);
    
    PackingSize(Index2dC(10,10));
    return false;
  }
  
  //: Attempt to link to another object.
  
  DFObjectC DFObjectBodyC::LinkTo(const DFObjectC &,bool autoConvert) {
    return DFObjectC(); // Don't know how to link.
  }
  
  //: Get attachment point.
  
  Index2dC DFObjectBodyC::AttachPoint() const 
  { return Index2dC(0,0); }
  
  //: Get list of attachment points.
  
  DListC<DFAttachC> DFObjectBodyC::Parts() const {
    return DListC<DFAttachC>();
  }

  
}
