// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! file="Ravl/Applications/VisualDataFlow/DFObject.cc"

#include "Ravl/DF/DFObject.hh"
#include "Ravl/DF/GUIView.hh"
#include "Ravl/BinStream.hh"
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
  
  //: Load from stream.
  
  DFAttachBodyC::DFAttachBodyC(BinIStreamC &strm) {
    int nplace;
    strm >> object >> offset >> nplace;
    placement = (DFAttachPlacementT) nplace;
  }
  
  //: Load from stream.
  
  DFAttachBodyC::DFAttachBodyC(istream &strm) {
    int nplace;
    strm >> object >> offset >> nplace;
    placement = (DFAttachPlacementT) nplace;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DFAttachBodyC::Save (ostream &out) const {
    out << object << ' ' << offset << ' ' << ((int) placement) << ' ' ;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DFAttachBodyC::Save (BinOStreamC &out) const {
    out << object << offset << ((int) placement);
    return true;
  }
  
  //: Write to an ostream.
  
  ostream &operator<<(ostream &strm,const DFAttachC &dfa) {
    RavlAssert(dfa.IsValid());
    dfa.Save(strm);
    return strm;
  }
  
  //: Read from an istream.
  
  istream &operator>>(istream &strm,DFAttachC &dfa) {
    dfa = DFAttachC(strm);
    return strm;
  }
  
  //: Write to an ostream.
  
  BinOStreamC &operator<<(BinOStreamC &strm,const DFAttachC &dfa) {
    RavlAssert(dfa.IsValid());
    dfa.Save(strm);
    return strm;
  }
  
  //: Read from an istream.
  
  BinIStreamC &operator>>(BinIStreamC &strm,DFAttachC &dfa) {
    dfa = DFAttachC(strm);
    return strm;
  }
  
  
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
  
  //: Load from stream.
  
  DFObjectBodyC::DFObjectBodyC(istream &strm) 
    : RCBodyVC(strm)
  {
    int version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("Unknown version number in DFObjectBodyC stream. ");
    strm >> name >> renderSize >> packingSize; 
  }
  
  //: Load from binary stream.
  
  DFObjectBodyC::DFObjectBodyC(BinIStreamC &strm) 
    : RCBodyVC(strm)
  {
    int version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("Unknown version number in DFObjectBodyC binary stream. ");
    strm >> name >> renderSize >> packingSize; 
  }

  //: Read from istream.
  
  DFObjectBodyC::DFObjectBodyC(XMLIStreamC &strm,DFSystemC &context) {
    strm >> XMLAttribute("name",name);
  }
  
  //: Save ostream.
  
  bool DFObjectBodyC::Save(XMLOStreamC &strm,bool inCharge) const {
    if(inCharge)
      strm << XMLStartTag("DFObject");
    strm << XMLAttribute("name",name);
    if(inCharge)
      strm << XMLEndTag;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DFObjectBodyC::Save (ostream &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    int version = 0;
    out << ' ' << version << ' ' << name << ' ' << renderSize << ' ' << packingSize << ' ';
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DFObjectBodyC::Save (BinOStreamC &out) const {
    if(!RCBodyVC::Save(out))
      return false;
    int version = 0;
    out << version << name << renderSize << packingSize;
    return true;
  }
  
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
  
  //: Process a mouse click.
  
  DFMouseActionT DFObjectBodyC::MouseClick(GUIViewBodyC &view,const  MouseEventC &me) {
    if(me.HasChanged(0)) 
      return DFMA_SELECTDRAG;
    return DFMA_NONE;
  }
  
  //: Attempt to link to another object.
  
  DFObjectC DFObjectBodyC::LinkTo(const DFObjectC &,DFSystemC &sys,bool autoConvert) {
    return DFObjectC(); // Don't know how to link.
  }
  
  //: Get attachment point.
  
  Index2dC DFObjectBodyC::AttachPoint() const 
  { return Index2dC(0,0); }
  
  //: Get list of attachment points.
  
  DListC<DFAttachC> DFObjectBodyC::Parts() const {
    return DListC<DFAttachC>();
  }
  
  //: Access attribute control for object if it exists.
  // Returns an invalid handle if none.
  
  AttributeCtrlC DFObjectBodyC::AttributeCtrl() {
    return AttributeCtrlC();
  }
  
  ////////////////////////////////////////////////////////////////////////////////
  
  //: Construct from a stream.
  
  DFObjectC::DFObjectC(istream &strm) 
    : RCHandleVC<DFObjectBodyC>(RAVL_VIRTUALCONSTRUCTOR(strm,DFObjectBodyC))
  {}
  
  //: Construct from a binary stream.
  
  DFObjectC::DFObjectC(BinIStreamC &strm) 
    : RCHandleVC<DFObjectBodyC>(RAVL_VIRTUALCONSTRUCTOR(strm,DFObjectBodyC))
  {}
  

  //: Write DFObjectC to stream.
  
  BinOStreamC &operator<<(BinOStreamC &strm,const DFObjectC &dfo) {
    RavlAssert(dfo.IsValid());
    dfo.Save(strm);
    return strm; 
  }
  
  //: Read DFObject from stream.
  
  BinIStreamC &operator>>(BinIStreamC &strm,DFObjectC &dfo) {
    dfo = DFObjectC(strm);
    return strm;
  }
  
  //: Write DFObjectC to stream.
  
  ostream &operator<<(ostream &strm,const DFObjectC &dfo) {
    RavlAssert(dfo.IsValid());
    dfo.Save(strm);
    return strm;
  }
  
  //: Read DFObject from stream.
  
  istream &operator>>(istream &strm,DFObjectC &dfo) {
    dfo = DFObjectC(strm);
    return strm;
  }

  
}
