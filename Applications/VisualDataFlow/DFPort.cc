// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! file="Ravl/Applications/VisualDataFlow/DFPort.cc"

#include "Ravl/DF/DFPort.hh"
#include "Ravl/DF/GUIView.hh"
#include "Ravl/DF/DFLink.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/DP/TypeConverter.hh"
#include "Ravl/DP/StreamProcess.hh"
#include "Ravl/DF/DFStreamOp.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {
  
  //: Constructor.
  
  DFPortBodyC::DFPortBodyC(const StringC &nname,DFAttachPlacementT attach)
    : DFObjectBodyC(nname),
      attachAt(attach),
      attachScale(10)
  {}
  
  //: Load from stream.
  
  DFPortBodyC::DFPortBodyC(istream &strm)
    : DFObjectBodyC(strm)
  {}
  
  //: Load from binary stream.
  
  DFPortBodyC::DFPortBodyC(BinIStreamC &strm)
    : DFObjectBodyC(strm)
  {}
  
  //: Read from XMLStream.
  
  DFPortBodyC::DFPortBodyC(XMLIStreamC &strm,DFSystemC &context)
    : DFObjectBodyC(strm,context)
  {
  }
  
  //: Save ostream.
  
  bool DFPortBodyC::Save(XMLOStreamC &strm,bool inCharge) const {
    if(inCharge)
      strm << XMLStartTag("DFPort");
    if(!DFObjectBodyC::Save(strm,false))
      return false;
    if(inCharge)
      strm << XMLEndTag;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DFPortBodyC::Save (ostream &out) const {
    if(!DFObjectBodyC::Save(out))
      return false;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DFPortBodyC::Save (BinOStreamC &out) const {
    if(!DFObjectBodyC::Save(out))
      return false;
    return true;
  }
  
  //: Access the port.
  
  DPPortC DFPortBodyC::Port() { 
    RavlAssert(0);
    return DPPortC(); 
  }
  
  //: Get attachment point.
  
  Index2dC DFPortBodyC::AttachPoint() const {
    const Index2dC &rs = baseSize;
    //: Get the size of this object.
    switch(AttachPlacement()) {
    case ATTACH_TOP:    return Index2dC(rs[0]/2,0);
    case ATTACH_BOTTOM: return Index2dC(rs[0]/2,rs[1]);
    case ATTACH_RIGHT:  return Index2dC(0,rs[1]/2);
    case ATTACH_LEFT:   return Index2dC(rs[0],rs[1]/2);
    case ATTACH_FLOAT:
    default:
      break;
    }
    return Index2dC(0,0);
  }

  //: Get a point inside of the area of 'pos' by distance 'dist'.
  // dist may be negative.
  
  Index2dC DFPortBodyC::Inside(const Index2dC &pos,IntT dist) {
    switch(AttachPlacement()) {
    case ATTACH_TOP:    return pos + Index2dC(0,dist);
    case ATTACH_BOTTOM: return pos + Index2dC(0,-dist);
    case ATTACH_RIGHT:  return pos + Index2dC(dist,0);
    case ATTACH_LEFT:   return pos + Index2dC(-dist,0);
    case ATTACH_FLOAT:
    default: break;
    }
    return Index2dC(0,0);    
  }
  
  //: Get a point to the left of 'pos' by distance 'dist'.
  // dist may be negative.
  
  Index2dC DFPortBodyC::Left(const Index2dC &pos,IntT dist) {
    switch(AttachPlacement()) {
    case ATTACH_TOP:    return pos + Index2dC(-dist,0);
    case ATTACH_BOTTOM: return pos + Index2dC(dist,0);
    case ATTACH_RIGHT:  return pos + Index2dC(0,-dist);
    case ATTACH_LEFT:   return pos + Index2dC(0,dist);
    case ATTACH_FLOAT:
    default: break;
    }
    return Index2dC(0,0);    
  }
  
  //: Render object to view.
  
  bool DFPortBodyC::Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode) {
    StringC tname = TypeName(PortType());
    StringC pname = PortName();
    Index2dC tsize = view.TextSize(view.DrawFont(),tname);
    Index2dC psize = view.TextSize(view.DrawFont(),pname);
    
    GdkGC *fggc = view.DrawModeFG(mode);
    GdkGC *bggc = view.DrawModeBG(mode);
    IndexRange2dC rect(at,at + 
		       Index2dC(Max(tsize[0],psize[0]),tsize[1] + psize[1] + 1) + 
		       Index2dC(attachScale*2 + 2,attachScale + 2));
    
    view.DrawRectangle(bggc,rect,true);
    view.DrawRectangle(fggc,rect,false);
    view.DrawText(fggc,view.DrawFont(),at + Index2dC(attachScale + 1,attachScale/2 + tsize[1] + 1),pname);
    view.DrawText(fggc,view.DrawFont(),at + Index2dC(attachScale + 1,attachScale/2 + tsize[1] + psize[1] + 2),tname);
    baseSize = rect.Size();
    PackingSize(baseSize);
    return true;
  }
  
  //: Process a mouse click.
  
  DFMouseActionT DFPortBodyC::MouseClick(GUIViewBodyC &view,const  MouseEventC &me) {
    if(me.HasChanged(0)) 
      return DFMA_SELECTDRAG;
    if(me.HasChanged(2)) 
      return DFMA_LINK;
    return DFMA_NONE;
  }
  
  //: Connect this port to another.
  
  bool DFPortBodyC::Connect(DFPortC &port) {
    RavlAssertMsg(0,"DFPortBodyC::Connect(), Abstract method called. ");
    return false;
  }
  
  //: Disconnect.
  
  bool DFPortBodyC::Disconnect(DFPortC &port) {
    RavlAssertMsg(0,"DFPortBodyC::Disconnect(), Abstract method called. ");
    return false;
  }
  
  //: Get type of port.
  
  const type_info &DFPortBodyC::PortType() const {
    // Default return voide.
    return typeid(void);
  }

  //: Get the port name.
  
  StringC DFPortBodyC::PortName() const {
    static StringC unknown("Unknown");
    return unknown;
  }

  //: Access attribute control for object if it exists.
  // Returns an invalid handle if none.
  
  AttributeCtrlC DFPortBodyC::AttributeCtrl() {
    return Port();
  }
  
  // IPort /////////////////////////////////////////////////////////////////////////////////////////////
  
  //: Constructor.
  DFIPortBodyC::DFIPortBodyC(const StringC &nname)
    : DFPortBodyC(nname,ATTACH_LEFT)
  {}
  
  //: Construct from a port and a name
  
  DFIPortBodyC::DFIPortBodyC(const DPIPortBaseC &port,const StringC &nname)
    : DFPortBodyC(nname,ATTACH_LEFT),
      iport(port)
  {}
  
  //: Render object to view.
  
  bool DFIPortBodyC::Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode) {
    if(!DFPortBodyC::Render(view,at,mode))
      return false;
    
    GdkGC *fggc = view.DrawModeFG(mode);
    GdkGC *bggc = view.DrawModeBG(mode);
    Index2dC ap = at + AttachPoint();
    view.DrawCircle(bggc,ap,attachScale/2,true);
    view.DrawCircle(fggc,ap,attachScale/2,false);
    Index2dC pnt = Inside(ap,-attachScale);
    view.DrawLine(fggc,Left(ap,attachScale),pnt);
    view.DrawLine(fggc,Left(ap,-attachScale),pnt);
    
    // Setup render size.
    renderSize = PackingSize();
    renderSize.Involve(Inside(AttachPoint(),-attachScale));
    
    return true;
  }
  
  //: Access the port.
  
  DPPortC DFIPortBodyC::Port()
  { return iport; }
  
  //: Attempt to link to another object.
  
  DFObjectC DFIPortBodyC::LinkTo(const DFObjectC &obj,DFSystemC &system,bool autoConvert) {
    ONDEBUG(cerr << "DFIPortBodyC::LinkTo(), Called \n");
    DFIPlugC objp(obj);
    if(!objp.IsValid()) {
      // Can only link to an IPlug.
      ONDEBUG(cerr << "DFIPortBodyC::LinkTo(), Object is not an IPlug. \n");
      return DFObjectC();
    }
    return objp.LinkTo(DFIPortC(*this),system,autoConvert);
  }
  
  //: Connect this port to another.
  
  bool DFIPortBodyC::Connect(DFPortC &port) {
    DFIPlugC dfiplug(port);
    if(!dfiplug.IsValid())
      return false;
    if(!iport.IsValid())
      return false;
    if(!dfiplug.IPlug().IsValid())
      return false;
    if(dfiplug.IPlug().InputType() != iport.InputType()) {
      cerr << "DFOPlugBodyC::Connect(), Type mismatch. \n";
      return false;
    }
    dfiplug.IPlug().ConnectPort(iport);
    return true;
  }
  
  //: Disconnect.
  
  bool DFIPortBodyC::Disconnect(DFPortC &port) {
    return true;
  }
  
  const type_info &DFIPortBodyC::PortType() const {
    return iport.InputType(); 
  }

  //: Get the port name.
  
  StringC DFIPortBodyC::PortName() const {
    return const_cast<DPIPortBaseC &>(iport).GetAttr("id");
  }
  
  // OPort ////////////////////////////////////////////////////////////////////////////////
  
  //: Constructor.
  
  DFOPortBodyC::DFOPortBodyC(const StringC &nname)
    : DFPortBodyC(nname,ATTACH_RIGHT)
  {}
  
  //: Construct from a port and a name
  
  DFOPortBodyC::DFOPortBodyC(const DPOPortBaseC &port,const StringC &nname)
    : DFPortBodyC(nname,ATTACH_RIGHT),
      oport(port)
  {}
  
  //: Render object to view.
  
  bool DFOPortBodyC::Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode) {
    if(!DFPortBodyC::Render(view,at,mode))
      return false;
    
    GdkGC *fggc = view.DrawModeFG(mode);
    GdkGC *bggc = view.DrawModeBG(mode);
    Index2dC ap = at + AttachPoint();
    view.DrawCircle(bggc,ap,attachScale/2,true);
    view.DrawCircle(fggc,ap,attachScale/2,false);
    Index2dC pnt = Inside(ap,attachScale);
    view.DrawLine(fggc,Left(ap,attachScale),pnt);
    view.DrawLine(fggc,Left(ap,-attachScale),pnt);
    
    // Setup render size.
    renderSize = PackingSize();
    renderSize.Involve(Inside(AttachPoint(),-attachScale/2));
    
    return true;
  }
  
  //: Access the port.
  
  DPPortC DFOPortBodyC::Port()
  { return oport; }
  
  //: Attempt to link to another object.
  
  DFObjectC DFOPortBodyC::LinkTo(const DFObjectC &obj,DFSystemC &system,bool autoConvert) {
    ONDEBUG(cerr << "DFOPortBodyC::LinkTo(), Called \n");
    DFOPlugC objp(obj);
    if(!objp.IsValid()) {
      // Can only link to an IPlug.
      ONDEBUG(cerr << "DFOPortBodyC::LinkTo(), Object is not an OPlug. \n");
      return DFObjectC();
    }
    return objp.LinkTo(DFOPortC(*this),system,autoConvert);
  }

  //: Connect this port to another.
  
  bool DFOPortBodyC::Connect(DFPortC &port) {
    DFOPlugC dfoplug(port);
    if(!dfoplug.IsValid())
      return false;
    if(!oport.IsValid())
      return false;
    if(!dfoplug.OPlug().IsValid())
      return false;
    if(dfoplug.OPlug().OutputType() != oport.OutputType()) {
      cerr << "DFOPortBodyC::Connect(), Type mismatch. \n";
      return false;
    }
    dfoplug.OPlug().ConnectPort(oport);
    return true;
  }
  
  //: Disconnect.
  
  bool DFOPortBodyC::Disconnect(DFPortC &port) {
    DFOPlugC dfoplug(port);
    if(!dfoplug.IsValid())
      return false;
    DPOPortBaseC op;
    if(!dfoplug.OPlug().IsValid())
      return false;
    dfoplug.OPlug().ConnectPort(op); // Set to null port.
    return true;
  }
  
  const type_info &DFOPortBodyC::PortType() const {
    return oport.OutputType(); 
  }
  
  //: Get the port name.
  
  StringC DFOPortBodyC::PortName() const {
    return const_cast<DPOPortBaseC &>(oport).GetAttr("id");
  }

  // IPlug ///////////////////////////////////////////////////////////////////////////////////
  
  //: Constructor.
  
  DFIPlugBodyC::DFIPlugBodyC(const StringC &nname)
    : DFPortBodyC(nname,ATTACH_RIGHT)
  {}
  
  //: Construct from a port and a name
  
  DFIPlugBodyC::DFIPlugBodyC(const DPIPlugBaseC &port,const StringC &nname)
    : DFPortBodyC(nname,ATTACH_RIGHT),
      iplug(port)
  {}
  
  //: Render object to view.
  
  bool DFIPlugBodyC::Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode) {
    if(!DFPortBodyC::Render(view,at,mode))
      return false;
    GdkGC *fggc = view.DrawModeFG(mode);
    //GdkGC *bggc = view.DrawModeBG(mode);
    
    Index2dC ap = at + AttachPoint();
    view.DrawCircle(fggc,ap,attachScale/2,true);
    Index2dC pnt = Inside(ap,attachScale);
    view.DrawLine(fggc,Left(ap,attachScale),pnt);
    view.DrawLine(fggc,Left(ap,-attachScale),pnt);
    
    // Setup render size.
    renderSize = PackingSize();
    renderSize.Involve(Inside(AttachPoint(),-attachScale/2));
    
    return true;
  }

  //: Attempt to link to another object.
  
  DFObjectC DFIPlugBodyC::LinkTo(const DFObjectC &obj,DFSystemC &system,bool autoConvert) {
    ONDEBUG(cerr << "DFIPlugBodyC::LinkTo(), Called \n");
    DFIPortC objp(obj);
    if(!objp.IsValid()) {
      // Can only link to an IPlug.
      ONDEBUG(cerr << "DFIPlugBodyC::LinkTo(), Object is not an IPort. \n");
      return DFObjectC();
    }
    if(PortType() == objp.PortType()) // Check if types match.
      return DFLinkC(obj,DFIPlugC(*this));
    
    if(!autoConvert) {
      ONDEBUG(cerr << "DFIPlugBodyC::LinkTo(), Can't link " << TypeName(objp.PortType()) <<" and " << TypeName(PortType()) << " \n");
      return DFObjectC();
    }
    
    // Find conversion path.
    DListC<DPConverterBaseC> conv = SystemTypeConverter().FindConversion(objp.PortType(),PortType());
    if(conv.IsEmpty())
      return DFObjectC();
    
    // Build converter.
    DLIterC<DPConverterBaseC> it(conv);
    DPIPortBaseC at;
    at = it->CreateIStream(at);
    DPStreamOpC first(at);
    RavlAssert(first.IsValid());
    for(it++;it;it++)
      at = it->CreateIStream(at);
    DPStreamProcessC streamProc("Converter");

    //: Build DFStreamOpC.
    DListC<DPIPlugBaseC> iplugs = first.IPlugs();
    RavlAssert(iplugs.Size() == 1);
    streamProc.IPlug("In",iplugs.First());
    streamProc.IPort("Out",at);
    DFStreamOpC so("Converter",streamProc);
    system.AddObject(so);
    
    // Put links in.
    DFLinkC l1(so.IPort(at),DFIPlugC(*this));
    system.AddObject(l1);
    DFLinkC l2(objp,so.IPlug(iplugs.First()));
    system.AddObject(l2);
    return so;
  }
  
  //: Connect this port to another.
  
  bool DFIPlugBodyC::Connect(DFPortC &port) {
    DFIPortC op(port);
    if(!op.IsValid())
      return false;
    if(!iplug.IsValid())
      return false;
    if(!op.IPort().IsValid())
      return false;
    if(iplug.InputType() != op.IPort().InputType()) {
      cerr << "DFIPlugBodyC::Connect(), Type mismatch. \n";
      return false;
    }
    iplug.ConnectPort(op.IPort());
    return true;
  }
  
  //: Disconnect.
  
  bool DFIPlugBodyC::Disconnect(DFPortC &port) {
    DPIPortBaseC ip;
    if(!iplug.IsValid())
      return false;
    iplug.ConnectPort(ip);
    return true;
  }

  const type_info &DFIPlugBodyC::PortType() const {
    return iplug.InputType(); 
  }

  StringC DFIPlugBodyC::PortName() const {
    return iplug.PlugId();
  }
  
  // OPlug ///////////////////////////////////////////////////////////////////
  
  //: Constructor.
  
  DFOPlugBodyC::DFOPlugBodyC(const StringC &nname)
    : DFPortBodyC(nname,ATTACH_LEFT)
  {}
  
  //: Construct from a port and a name
  
  DFOPlugBodyC::DFOPlugBodyC(const DPOPlugBaseC &port,const StringC &nname)
    : DFPortBodyC(nname,ATTACH_LEFT),
      oplug(port)
  {}
  
  //: Attempt to link to another object.
  
  DFObjectC DFOPlugBodyC::LinkTo(const DFObjectC &obj,DFSystemC &system,bool autoConvert) {
    ONDEBUG(cerr << "DFOPlugBodyC::LinkTo(), Called \n");
    DFOPortC objp(obj);
    if(!objp.IsValid()) {
      // Can only link to an IPlug.
      ONDEBUG(cerr << "DFOPlugBodyC::LinkTo(), Object is not an OPort. \n");
      return DFObjectC();
    }
    if(PortType() == objp.PortType()) // Linking the same type ?
      return DFLinkC(DFOPlugC(*this),obj);    
    if(!autoConvert) {
      ONDEBUG(cerr << "DFIPlugBodyC::LinkTo(), Can't link " << TypeName(PortType()) <<" and " << TypeName(objp.PortType()) << " \n");
      return DFObjectC();
    }
    // Find conversion path.
    DListC<DPConverterBaseC> conv = SystemTypeConverter().FindConversion(PortType(),objp.PortType());
    if(conv.IsEmpty())
      return DFObjectC();

    // Build converter.
    DLIterC<DPConverterBaseC> it(conv);
    DPOPortBaseC at;
    at = it->CreateOStream(at);
    DPStreamOpC first(at);
    RavlAssert(first.IsValid());
    for(it++;it;it++)
      at = it->CreateOStream(at);
    DPStreamProcessC streamProc("Converter");

    //: Build DFStreamOpC.
    DListC<DPOPlugBaseC> oplugs = first.OPlugs();
    RavlAssert(oplugs.Size() == 1);
    streamProc.OPlug("Out",oplugs.First());
    streamProc.OPort("In",at);
    DFStreamOpC so("Converter",streamProc);
    system.AddObject(so);
    
    // Put links in.
    DFLinkC l1(DFOPlugC(*this),so.OPort(at));
    system.AddObject(l1);
    DFLinkC l2(so.OPlug(oplugs.First()),objp);
    system.AddObject(l2);
    return so;
  }
  
  //: Render object to view.
  
  bool DFOPlugBodyC::Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode) {
    if(!DFPortBodyC::Render(view,at,mode))
      return false;    
    GdkGC *fggc = view.DrawModeFG(mode);
    //GdkGC *bggc = view.DrawModeBG(mode);
    Index2dC ap = at + AttachPoint();
    view.DrawCircle(fggc,ap,attachScale/2,true);
    Index2dC pnt = Inside(ap,-attachScale);
    view.DrawLine(fggc,Left(ap,attachScale),pnt);
    view.DrawLine(fggc,Left(ap,-attachScale),pnt);
    
    // Setup render size.
    renderSize = PackingSize();
    renderSize.Involve(Inside(AttachPoint(),-attachScale));
    return true;
  }

  //: Connect this port to another.
  
  bool DFOPlugBodyC::Connect(DFPortC &port) {
    DFOPortC op(port);
    if(!op.IsValid())
      return false;
    if(!oplug.IsValid())
      return false;
    if(!op.OPort().IsValid())
      return false;
    if(oplug.OutputType() != op.OPort().OutputType()) {
      cerr << "DFOPlugBodyC::Connect(), Type mismatch. \n";
      return false;
    }
    oplug.ConnectPort(op.OPort());
    return true;
  }
  
  //: Disconnect.
  
  bool DFOPlugBodyC::Disconnect(DFPortC &port) {
    DPOPortBaseC ip;
    if(!oplug.IsValid())
      return false;
    oplug.ConnectPort(ip);
    return true;
  }
  
  const type_info &DFOPlugBodyC::PortType() const {
    return oplug.OutputType(); 
  }

  StringC DFOPlugBodyC::PortName() const {
    return oplug.PlugId();
  }
  
}
