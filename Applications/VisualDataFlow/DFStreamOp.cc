// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! file="Ravl/Applications/VisualDataFlow/DFStreamOp.cc"

#include "Ravl/DF/DFStreamOp.hh"
#include "Ravl/DF/GUIView.hh"
#include "Ravl/DF/DFPort.hh"
#include "Ravl/BinStream.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {
  
  DFStreamOpBodyC::DFStreamOpBodyC(const StringC &nname,const DPStreamOpC &sop)
    : DFObjectBodyC(nname),
      packStacked(true)
  { Init(sop); }
  
  //: Load from stream.
  
  DFStreamOpBodyC::DFStreamOpBodyC(istream &strm) 
    : DFObjectBodyC(strm)
  {
    int version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("Unknown version number in DFStreamOpBodyC stream. ");
    strm >> packStacked >> streamOp;
  }
  
  //: Load from binary stream.
  
  DFStreamOpBodyC::DFStreamOpBodyC(BinIStreamC &strm)
    : DFObjectBodyC(strm)
  {
    int version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("Unknown version number in DFStreamOpBodyC binary stream. ");
    strm >> packStacked >> streamOp;    
  }
  
  //: Save ostream.
  
  bool DFStreamOpBodyC::Save(XMLOStreamC &strm,bool inCharge) const {
    if(inCharge)
      strm << XMLStartTag("DFStreamOp");
    if(!DFObjectBodyC::Save(strm,false))
      return false;
    strm << XMLAttribute("stacked",packStacked);
    if(inCharge)
      strm << XMLEndTag;
    return true;
  }

  //: Writes object to stream, can be loaded using constructor
  
  bool DFStreamOpBodyC::Save (ostream &strm) const {
    if(!DFObjectBodyC::Save(strm))
      return false;
    int version = 0;
    strm << ' ' << version << ' ' << packStacked << ' ' << streamOp;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DFStreamOpBodyC::Save (BinOStreamC &strm) const {
    if(!DFObjectBodyC::Save(strm))
      return false;
    int version = 0;
    strm << version << packStacked << streamOp;
    return true;
  }
  
  //: Setup stream operator.
  
  bool DFStreamOpBodyC::Init(const DPStreamOpC &sop) {
    streamOp = sop;
    if(!streamOp.IsValid())
      return false;
    for(DLIterC<DPIPlugBaseC> it(sop.IPlugs());it;it++) {
      DFIPlugC cobj(*it,"Unknown");
      parts.InsLast(DFAttachC(cobj,ATTACH_RIGHT));
      iplugs[*it] = cobj;
    }
    for(DLIterC<DPIPortBaseC> it(sop.IPorts());it;it++) {
      DFIPortC cobj(*it,"Unknown");
      parts.InsLast(DFAttachC(cobj,ATTACH_LEFT));
      iports[*it] = cobj;
    }
    for(DLIterC<DPOPlugBaseC> it(sop.OPlugs());it;it++) {
      DFOPlugC cobj(*it,"Unknown");
      parts.InsLast(DFAttachC(cobj,ATTACH_RIGHT));
      oplugs[*it] = cobj;
    }
    for(DLIterC<DPOPortBaseC> it(sop.OPorts());it;it++) {
      DFOPortC cobj(*it,"Unknown");
      parts.InsLast(DFAttachC(cobj,ATTACH_LEFT));
      oports[*it] = cobj;
    }
    
    return true;
  }

  //: Render object to view.
  
  bool DFStreamOpBodyC::Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode) {
    ONDEBUG(cerr << "DFStreamOpBodyC::Render(), Called. At=" << at << " Mode=" << (int)mode << "\n");
    
    Index2dC textSize = view.TextSize(view.DrawFont(),name);
    Index2dC size = textSize + Index2dC(3,8);
    GdkGC *fggc = view.DrawModeFG(mode);
    
    // Work out size.
    int maxWidthl = 0;
    int maxWidthr = 0;
    
    for(DLIterC<DFAttachC> it(parts);it;it++) {
      Index2dC osize = it->Object().PackingSize().Size();
      switch(it->Placement()) {
      case ATTACH_LEFT:
	if(maxWidthl < osize.Row().V())
	  maxWidthl = osize.Row().V();
	break;
      case ATTACH_RIGHT:
	if(maxWidthr < osize.Row().V())
	  maxWidthr = osize.Row().V();
	break;
      default:
      case ATTACH_TOP:
      case ATTACH_BOTTOM:
      case ATTACH_FLOAT:
	break;
      }
    }
    IntT width;
    if(!packStacked)
      width = (maxWidthl + maxWidthr);
    else
      width = Max(maxWidthl,maxWidthr);
    
    if(size.Row() < width)
      size.Row() = width;
    //cerr << "Width = " << width << "\n";
    IndexRange2dC rect(Index2dC(0,0),size);
    IndexRange2dC nrenderSize = rect;
    
    // Render components.
    
    IntT leftSide = size.Col().V();
    IntT rightSide = size.Col().V();
    //ONDEBUG(cerr << "Row=" << size.Row() << " Col=" << size.Col().V() << "\n");
    for(DLIterC<DFAttachC> it(parts);it;it++) {
      Index2dC osize = it->Object().PackingSize().Size();
      Index2dC off;
      switch(it->Placement()) {
      case ATTACH_LEFT:
	off = Index2dC((size.Row().V() - osize.Row().V())+3,leftSide);
	leftSide += osize.Col().V() + 1;
	break;
      case ATTACH_RIGHT:
	if(packStacked) {
	  // Put them above each other.
	  off = Index2dC(2,leftSide);
	  leftSide += osize.Col().V() + 1;
	} else {
	  off = Index2dC(2,rightSide);
	  rightSide += osize.Col().V() + 1;
	}
	break;
      default:
      case ATTACH_TOP:
      case ATTACH_BOTTOM:
      case ATTACH_FLOAT: off = it->Offset(); break;
      }
      //it->Object().Render(view,at + off,mode);
      rect.Involve(it->Object().PackingSize() + off);
      nrenderSize.Involve(it->Object().RenderSize() + off);
      it->Offset() = off;
    }
    rect.BRow()++;
    rect.RCol()++;    
    nrenderSize.Involve(rect);
    IndexRange2dC drawRect = rect + at;
    view.DrawRectangle(view.DrawModeBG(mode),drawRect,true);
    view.DrawRectangle(fggc,drawRect,false);
    view.DrawText(fggc,view.DrawFont(),at + Index2dC(5,textSize[1]+5),name);
    PackingSize(rect);
    RenderSize(nrenderSize.Expand(1));
    
    //cerr << "PackingSize:" << rect << " RenderSize:" << nrenderSize << "\n";
    //view.DrawRectangle(view.DrawGCGrey(),renderSize + at,false);
    return true;
  }
  
  //: Get list of attachment points.
  
  DListC<DFAttachC> DFStreamOpBodyC::Parts() const {
    return parts;
  }
  
  //: Find DFIPort corresponding to 'ip'.
  
  DFIPortC DFStreamOpBodyC::IPort(const DPIPortBaseC &ip) const {
    DFIPortC ret;
    iports.Lookup(ip,ret);
    return ret;
  }
  
  //: Find DFIPort corresponding to 'ip'.
  
  DFOPortC DFStreamOpBodyC::OPort(const DPOPortBaseC &ip) const {
    DFOPortC ret;
    oports.Lookup(ip,ret);
    return ret;
  }
  
  //: Find DFIPort corresponding to 'ip'.
  
  DFIPlugC DFStreamOpBodyC::IPlug(const DPIPlugBaseC &ip) const {
    DFIPlugC ret;
    iplugs.Lookup(ip,ret);
    return ret;
  }
  
  //: Find DFIPort corresponding to 'ip'.
  
  DFOPlugC DFStreamOpBodyC::OPlug(const DPOPlugBaseC &ip) const {
    DFOPlugC ret;
    oplugs.Lookup(ip,ret);
    return ret;
  }
  
  //: Access attribute control for object if it exists.
  // Returns an invalid handle if none.
  
  AttributeCtrlC DFStreamOpBodyC::AttributeCtrl() {
    return AttributeCtrlC((DPEntityC &)streamOp); 
  }
  
}
