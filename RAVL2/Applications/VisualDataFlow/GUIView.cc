// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! file="Ravl/Applications/VisualDataFlow/GUIView.cc"

#include "Ravl/DF/GUIView.hh"
#include "Ravl/DF/DFLink.hh"
#include "Ravl/DF/DFPort.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Threads/Signal1.hh"
#include <gtk/gtk.h>

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {
  using namespace RavlGUIN;
  
  //: Construct with a size.
  
  GUIViewBodyC::GUIViewBodyC(const DFSystemC &nsys,
			     const FactorySetC &nfactories,
			     int nsx,int nsy)
    : RawCanvasBodyC(nsx,nsy),
      viewState(VS_READY),
      autoConvert(true),
      factories(nfactories)
  {
    EnableURLMapper(); // This widget relies on URL mapping being enabled.
    AttachSystem(const_cast<DFSystemC &>(nsys));
  }
  
  //: Destructor.
  
  GUIViewBodyC::~GUIViewBodyC() {
    //ONDEBUG(cerr << "GUIViewBodyC::~GUIViewBodyC(), Called \n");
  }
  
  //:  Attach system to this view.
  
  bool GUIViewBodyC::AttachSystem(DFSystemC &nsys) {
    if(system == nsys)
      return true; // Already attached.
    if(system.IsValid()) {
      // Disconnect the old system.
      elements.Empty();
      hold.Invalidate();
      obj2elem.Empty();
      sysConnectSet.DisconnectAll();
    }
    
    system = nsys;
      
    // Clear out connections to old system.
    sigObjChange.Invalidate();
    sigObjChange = Signal2C<DFObjectUpdateT,DFObjectC>(DFOU_ADDED);
    
    if(!system.IsValid())
      return false;
    
    // Attach new system.
    sysConnectSet += ConnectRef(sigObjChange,*this,&GUIViewBodyC::ObjectUpdate);
    sysConnectSet += Connect(system.SigChange(),sigObjChange);
    
    BuildAll();
    return true;
  }
  
  //: build view of the complete system.
  
  void GUIViewBodyC::BuildAll() {
    if(!system.IsValid())
      return ;
    DListC<DFObjectC> objs=system.Objects();
    int x = 10;
    for(DLIterC<DFObjectC> it(objs);it;it++,x += 20) {
      Index2dC at(10,x);
      AddObject(*it,at);
    }
    if(widget != 0)
      Render();
  }
  
  //: Handle object updates.
  
  bool GUIViewBodyC::ObjectUpdate(DFObjectUpdateT &type,DFObjectC &obj) {
    ONDEBUG(cerr << "GUIViewBodyC::ObjectUpdate(). \n");
    switch(type) {
    case DFOU_ADDED: {
      Index2dC at(0,0);
      if(viewState == VS_LINK) {
	if(hold.IsValid()) {
	  Index2dC att = hold.AttachPoint();
	  at = Index2dC((mouseAt[0] + att[0])/2,(mouseAt[1] + att[1])/2);
	} else
	  at = mouseAt;
      }
      AddObject(obj,at); 
      break;
    }
    case DFOU_DELETED: DelObject(obj); break;
    case DFOU_CHANGED: Render(obj); break;
    default:
      cerr << "GUIViewBodyC::ObjectUpdate(), WARNING: Unexpected update type. \n";
    }
    return true;
  }
  
  //: Add object to view.
  // Returns true if its a new object.

  ViewElementC GUIViewBodyC::AddObject(const DFObjectC &obj,const Index2dC &at) {
    ViewElementC ret;
    if(!obj.IsValid())
      return ret;
    ONDEBUG(cerr << "GUIViewBodyC::AddObject(), " << ((void *) this) << " Object '" << obj.Name() << "' at=" << at << "\n");
    if(obj2elem.Lookup(obj,ret) && ret.IsValid()) {
      ONDEBUG(cerr << " Object already present. \n");
      return ret;
    }
    DFLinkC lnk(obj);
    if(lnk.IsValid()) {
      ViewElementC os = AddObject(lnk.Source(),at);
      ViewElementC od = AddObject(lnk.Destination(),at);
      ret = ViewLinkC(os,od,obj);
    } else {
      ret = ViewElementC(obj,at);
    }
    elements.InsLast(ret);
    RavlAssert(ret.IsValid());
    obj2elem[obj] = ret;
    for(DLIterC<DFAttachC> it(obj.Parts());it;it++) {
      ViewElementC elem = AddObject(it->Object(),at);
      RavlAssert(elem.IsValid());
      elem.Component(true);
      ret.AddPart(elem);
    }
    Render(ret.Frame());
    return ret;
  }
  
  //: Remove object from view,
  
  bool GUIViewBodyC::DelObject(const DFObjectC &obj) {
    ONDEBUG(cerr << "GUIViewBodyC::DelObject(), Called. \n");
    ViewElementC ve;
    if(!obj2elem.Lookup(obj,ve))
      return true; // Done already.
    IndexRange2dC rect(ve.Frame());
    // Remove all its children.
    for(DLIterC<DFAttachC> it(obj.Parts());it;it++)
      DelObject(it->Object());
    ve.Disconnect();
    elements.Del(ve);
    obj2elem.Del(obj);
    Render(rect);
    return true;
  }
  
  //: Access drawing context.
  
  GdkGC *GUIViewBodyC::DrawGC() {
    RavlAssert(Widget() != 0);
    return Widget()->style->base_gc[0];
    //widget->style->font
  }
  
  //: Get black drawing context.
  
  GdkGC *GUIViewBodyC::DrawGCBlack() {
    RavlAssert(Widget() != 0);
    return Widget()->style->black_gc;
  }
  
  //: Get white drawing context.
  
  GdkGC *GUIViewBodyC::DrawGCWhite() {
    RavlAssert(Widget() != 0);
    return Widget()->style->white_gc;
  }
  
  //: Get grey drawing context.
  
  GdkGC *GUIViewBodyC::DrawGCGrey() {
    RavlAssert(Widget() != 0);
    return Widget()->style->mid_gc[0];
  }
  
  //: Font to use.
  
  GdkFont *GUIViewBodyC::DrawFont() {
    RavlAssert(Widget() != 0);
    GdkFont *cfont = gtk_style_get_font(widget->style);
    return cfont;
  }
  
  //: Get get draw area.
  
  GdkWindow *GUIViewBodyC::DrawWindow() {
    RavlAssert(Widget() != 0);
    return Widget()->window;    
  }
  
  //: Draw a line.
  
  void GUIViewBodyC::DrawLine(GdkGC *gc,Index2dC p1,Index2dC p2) {
    gdk_draw_line(DrawWindow(),gc,p1[0].V(),p1[1].V(),p2[0].V(),p2[1].V());
  }
  
  //: Draw a rectangle.
  
  void GUIViewBodyC::DrawRectangle(GdkGC *gc,const IndexRange2dC &rect,bool fill) {
    gdk_draw_rectangle(DrawWindow(),
		       gc,fill,
		       rect.TRow().V(),rect.LCol().V(),
		       rect.Rows(),rect.Cols());
  }
  
  //: Draw a rectangle.
  
  void GUIViewBodyC::DrawRectangle(GdkGC *gc,Index2dC topLeft,Index2dC bottomRight,bool fill) {
    Index2dC size = (bottomRight - topLeft) - Index2dC(1,1);
    gdk_draw_rectangle(DrawWindow(),
		       gc,fill,
		       topLeft[0].V(),topLeft[1].V(),
		       size[0].V(),size[1].V()
		       );
  }
  
  //: Draw text.
  
  void GUIViewBodyC::DrawText(GdkGC *gc,GdkFont *font,Index2dC at,const StringC &txt) {
    gdk_draw_text(DrawWindow(),
		  font,gc,
		  at[0].V(),at[1].V(),
		  txt.chars(),txt.Size());
  }
  
  //: Draw a circle.
  
  void GUIViewBodyC::DrawCircle(GdkGC *gc,Index2dC cent,UIntT size,bool fill) {
    gdk_draw_arc(DrawWindow(),gc,(int) fill ,
		 cent[0].V() - size,cent[1].V() - size,
		 size*2,size*2,
		 0,64* 360);
  }
  
  //: Find the size of the font.
  
  Index2dC GUIViewBodyC::TextSize(GdkFont *font,const StringC &txt) {  
    IntT width = gdk_text_width(font,txt.chars(),txt.Size());
    return Index2dC(width,10);
  }
  
  //: Get background for given draw mode.
  
  GdkGC *GUIViewBodyC::DrawModeBG(DFRenderModeT mode) {
    GdkGC *bggc;
    switch(mode) {
    case DFRM_NORMAL: bggc = DrawGCWhite(); break;
    case DFRM_SELECTED: bggc = DrawGCGrey(); break;
    case DFRM_SHADED: bggc = DrawGCGrey(); break;
    default:
      bggc = DrawGCGrey(); break;
    }
    return bggc;
  }
  
  //: Get forground for given draw mode.
  
  GdkGC *GUIViewBodyC::DrawModeFG(DFRenderModeT mode) {
    return DrawGCBlack();
  }
  
  //: Render a particular view element..
  
  bool GUIViewBodyC::Render(ViewElementC &rve) {
    rve.Render(*this);
    for(DLIterC<DFAttachC> pit(rve.Object().Parts());pit;pit++) {
      ViewElementC ve = obj2elem[pit->Object()];
      if(!ve.IsValid())
	continue;
      //cerr << "Rendering " << rve.Object().Name() << " part " << pit->Object().Name() << " at=" << (rve.At() + pit->Offset()) << "\n";
      ve.Move(rve.At() + pit->Offset());
      ve.Render(*this);
    }
    return true;
  }
  
  //: Render entire view.
  
  void GUIViewBodyC::Render() {
    // Draw filled rectangle, for background.
    if(widget == 0)
      return ; // Nowhere to render to yet.
    for(DLIterC<ViewElementC> it(elements);it;it++) {
      //ONDEBUG(cerr << "GUIViewBodyC::Render(), Obj=" << it->Object().Name() << " At=" << it->AttachPoint() << "\n");
      Render(*it);
    }
  }

  //: Update an area of the view.
  
  void GUIViewBodyC::Render(const IndexRange2dC &area) {
    if(widget == 0)
      return ; // Nowhere to render to yet.
    gdk_draw_rectangle(widget->window,
		       widget->style->white_gc,1,
		       area.LCol().V(),area.TRow().V(),
		       area.Range2().Size(),area.Range1().Size());
    
    for(DLIterC<ViewElementC> it(elements);it;it++) {
      //ONDEBUG(cerr << "GUIViewBodyC::Render(const IndexRange2dC &), Obj=" << it->Object().Name() << " At=" << it->AttachPoint() << " Intersect=" << it->Intersects(area) << "\n");
      if(it->Intersects(area))
	Render(*it);
    }
  }
  
  //: Update rendering of an object.
  
  bool GUIViewBodyC::Render(const DFObjectC &obj) {
    if(widget == 0)
      return true; // Nowhere to render to yet.
    ViewElementC ve;
    if(!obj2elem.Lookup(obj,ve)) {
      ONDEBUG(cerr << "GUIViewBodyC::Render(const DFObjectC &), WARNING: Can't find ViewElement for object. \n");
      return false;
    }
    Render(ve.Frame());
    return true;
  }
  
  //: Find the view element containing 'at'.
  // Will return an invalid handle if none where found.
  
  ViewElementC GUIViewBodyC::FindElement(const Index2dC &at) {
    for(DLIterC<ViewElementC> it(elements);it;it++) {
      if(it->Contains(at)) {
	//cerr << "Got object " << it->Object().Name() << "\n";
	for(DLIterC<DFAttachC> pit(it->Object().Parts());pit;pit++) {
	  ViewElementC ve = obj2elem[pit->Object()];
	  if(!ve.IsValid())
	    continue;
	  if(ve.Contains(at))
	    return ve;
	}
	return *it;
      }
    }
    return ViewElementC();
  }
  
  //: Create the widget.
  
  bool GUIViewBodyC::Create() {
    
    connectSet += ConnectRef(Signal("expose_event"),*this,&GUIViewBodyC::EventExpose);
    connectSet += ConnectRef(Signal("configure_event"),*this,&GUIViewBodyC::EventConfigure);
    connectSet += ConnectRef(Signal("button_press_event"),*this,&GUIViewBodyC::EventMousePress);
    connectSet += ConnectRef(Signal("button_release_event"),*this,&GUIViewBodyC::EventMouseRelease);
    connectSet += ConnectRef(Signal("motion_notify_event"),*this,&GUIViewBodyC::EventMouseMove);

    connectSet += ConnectRef(Signal("key_press_event"),*this,&GUIViewBodyC::EventKeyPress);
    connectSet += ConnectRef(Signal("key_release_event"),*this,&GUIViewBodyC::EventKeyRelease);
    
    // Drag and drop...
#if 0
    GUIDNDSource(GDK_BUTTON1_MASK | GDK_BUTTON2_MASK,
		 CommonTargetEntries(),
		 GDK_ACTION_MOVE | GDK_ACTION_COPY);
#endif
    
    GUIDNDTarget(GTK_DEST_DEFAULT_MOTION | GTK_DEST_DEFAULT_HIGHLIGHT | GTK_DEST_DEFAULT_DROP ,
		 CommonTargetEntries(),
		 GDK_ACTION_MOVE | GDK_ACTION_COPY);
    
    connectSet += ConnectRef(Signal("drag_data_received"),*this,&GUIViewBodyC::DNDDataRecieved);
    //ConnectRef(Signal("drag_motion"),*this,&GUIViewBodyC::DNDMotion);
    connectSet += ConnectRef(Signal("drag_drop"),*this,&GUIViewBodyC::DNDDrop);
    
    if(!RawCanvasBodyC::Create())
      return false;
    
    return true;
  }
  
  //: Mouse move.
  
  bool GUIViewBodyC::EventMouseMove(MouseEventC &me) {
    //ONDEBUG(cerr << "GUIViewBodyC::EventMouseMove(MouseEventC &) Called. \n");
    mouseAt = me.At();
    switch(viewState) {
    case VS_DRAG:
      if(hold.IsValid() && !hold.Component()) { // Can't drag components...
	IndexRange2dC old = hold.Frame();
	hold.Move(me.At() - holdOffset);
	hold.Selected(true); // If its being dragged, its selected.
	if(old.IsOverlapping(hold.Frame())) {
	  old.Involve(hold.Frame());
	  Render(old);
	} else {
	  Render(old);
	  Render(hold.Frame());
	}
	break;
      }
      viewState = VS_READY;
    case VS_READY:
      break;
    case VS_LINK:
      {
	Index2dC from = hold.AttachPoint();
	Index2dC to = me.At();
	IndexRange2dC area(from,0);
	area.Involve(holdOffset);
	area.Dilate();
	Render(area);
	gdk_draw_line(DrawWindow(),DrawGCBlack(),from[0].V(),from[1].V(),to[0].V(),to[1].V());
	holdOffset = to;
      } break;
    }
    return true;
  }
  
  //: Attempt to create a link between elm1 and elm2.
  
  bool GUIViewBodyC::CreateLink(const ViewElementC &elm1,const ViewElementC &elm2) {
    ONDEBUG(cerr << "GUIViewBodyC::CreateLink(ViewElementC &,ViewElementC &), Called. \n");
    if(!system.IsValid())
      return true;
    DFObjectC obj1 = elm1.Object();
    DFObjectC obj2 = elm2.Object(); 
    if(!obj1.IsValid() || !obj2.IsValid())
      return false;
    DFObjectC newun = obj1.LinkTo(obj2,system,autoConvert);
    if(!newun.IsValid())
      return false;
    system.AddObject(newun);
    return true;
  }
  
  //: Load an object and put it at location 'at'.
  
  bool GUIViewBodyC::LoadObject(const StringC &fn,Index2dC at) {
    ONDEBUG(cerr << "GUIViewBodyC::LoadObject() Called. " << fn << " At=" << at << "\n");
    if(!system.IsValid())
      return false;
    DFObjectC nObj = system.LoadObject(fn);
    if(!nObj.IsValid())
      return false;
    return true;
  }
  
  //: Clear the selection.
  
  bool GUIViewBodyC::ClearSelection() {
    IndexRange2dC rect;
    bool changed = false;
    for(DLIterC<ViewElementC> it(elements);it;it++) {
      if(it->Selected()) {
	if(!changed) {
	  rect = it->Frame();
	  changed = true;
	} else
	  rect.Involve(it->Frame());
	it->Selected(false);
      }
    }
    if(changed)
      Render(rect);
    return true;
  }
  
  //: Delete the selected objects.
  
  bool GUIViewBodyC::DeleteSelection() {
    IndexRange2dC rect;
    bool changed = false;
    DListC<ViewElementC> toGo;
    // Make a list of objects to delete.
    for(DLIterC<ViewElementC> it(elements);it;it++) {
      if(it->Selected() && !it->Component()) { // Can't delete components with selection.
	if(!changed) {
	  rect = it->Frame();
	  changed = true;
	} else
	  rect.Involve(it->Frame());
	toGo.InsLast(*it);
	DListC<ViewElementC> parts = it->AllParts();
	toGo.MoveLast(parts);
      }
    }
    // Remove the objects.
    while(!toGo.IsEmpty()) {
      DFObjectC obj = toGo.First().Object();
      if(obj.IsValid()) {
	cerr << "Deleteing " << toGo.First().Name() << "\n";
	system.DelObject(obj);
      }
      toGo.DelFirst();
    }
    //// 
    //if(changed)
    //  Render(rect);
    return true;
  }
  
  //: Mouse press.
  
  bool GUIViewBodyC::EventMousePress(MouseEventC &me) {
    //ONDEBUG(cerr << "GUIViewBodyC::EventMousePress(MouseEventC &) Called. " << me.HasChanged(0) << " " << me.HasChanged(2) << " At=" << me.Position() << "\n");
    ViewElementC el = FindElement(me.At());
    DFMouseActionT ma = DFMA_NONE;
    if(!el.IsValid()) {
      if(me.HasChanged(0)) {
	ClearSelection();
	return true;
      }
      if(me.HasChanged(2))
	ma = DFMA_LINK;
    } else
      ma = el.MouseClick(*this,me);
    if(me.HasChanged(0))
      GUIGrabFocus(); // Grab the keyboard focus.
    switch(ma) 
      {
      case DFMA_SELECTDRAG: {
	if(!el.IsValid()) {
	  ClearSelection();
	  return true;
	}
	el.Selected(!el.Selected());
	ONDEBUG(cerr << "GUIViewBodyC::EventMousePress(), Got object. Selected:" << el.Selected() << "\n");
	hold = el;
	holdOffset = me.At() - el.At();
	viewState = VS_DRAG;
	Render(hold.Frame());
	return true;
      }
      case DFMA_LINK:  {
	switch(viewState)
	  {
	  case VS_READY: {
	    if(!el.IsValid())
	      return true;
	    // Clicked on a port ?
	    DFPortC port(el.Object());
	    if(port.IsValid()) {
	      ONDEBUG(cerr << "Got a port. \n";);
	      hold = el;
	      viewState = VS_LINK;
	    }
	  } break;
	  case VS_LINK: {
	    holdOffset = me.At();
	    bool clear = true;
	    if(el.IsValid()) {
	      if(CreateLink(hold,el)) {
		clear = false;
		Render(el.Frame());
	      }
	    }
	    if(clear) {
	      // Clear old line.
	      Index2dC from = hold.At();
	      IndexRange2dC area(from,0);
	      area.Involve(holdOffset);
	      area.Dilate();
	      Render(area);
	    }
	    viewState = VS_READY;
	  } break;
	  case VS_DRAG:
	    break;
	  };
      }
      case DFMA_NONE:
	break;
      }
    return true;
  }
  
  //: Mouse release.
  
  bool GUIViewBodyC::EventMouseRelease(MouseEventC &me) {
    ONDEBUG(cerr << "GUIViewBodyC::EventMouseRelease(MouseEventC &) Called. \n");
    if(me.HasChanged(0)) {
      if(viewState == VS_DRAG) {
	viewState = VS_READY;
	hold.Invalidate();
      }
    }
    return true;
  }
  
  //: Configure. 

  bool GUIViewBodyC::EventConfigure(GdkEvent* &event) {
    //ONDEBUG(cerr << "GUIViewBodyC::EventConfigure(GdkEvent* &event) Called. \n");
    return true;
  }
  
  //: Expose of area.
  
  bool GUIViewBodyC::EventExpose(GdkEvent* &event) {
    //ONDEBUG(cerr << "GUIViewBodyC::EventExpose(GdkEvent* &event) Called. \n");
    GdkEventExpose &expose = *((GdkEventExpose *)event);
    GtkWidget *widget = Widget();
    
    // Draw filled rectangle, for background.
    gdk_draw_rectangle(widget->window,
		       widget->style->white_gc,1,
		       expose.area.x,expose.area.y,
		       expose.area.width + expose.area.x,
		       expose.area.height + expose.area.y);
    
    IndexRange2dC area(expose.area.y,expose.area.height + expose.area.y,
		       expose.area.x,expose.area.width + expose.area.x
		       );
    Render(area);
    return true;
  }
  
  //: Handle key press events.
  
  bool GUIViewBodyC::EventKeyPress(GdkEventKey *&key) {
    ONDEBUG(cerr << "GUIViewBodyC::EventKeyPress(), Called. \n");
    //if(key->string[0] == 0
    switch(key->string[0]) {
    case 0x7f: // Backspace.
    case 0x08: // Delete
      DeleteSelection();
      break;
    }
    //cerr << "String= " << hex << (int) key->string[0] << " \n";
    return true;
  }
  
  //: Handle key release events.
  
  bool GUIViewBodyC::EventKeyRelease(GdkEventKey *&key) {
    ONDEBUG(cerr << "GUIViewBodyC::EventKeyRelease(), Called. \n");
    //cerr << "String='" << key->string << "'\n";
    return true;
  }
    

  //: Handle drag and drop motion.
  
  bool GUIViewBodyC::DNDMotion(GdkDragContext * &dc,PositionTimeC &pt) {
    ONDEBUG(cerr << "GUIViewBodyC::DNDMotion(), Called \n");
    return true;
  }
  
  //: Drop.
  
  bool GUIViewBodyC::DNDDrop(GdkDragContext * &dc,PositionTimeC &pt) {
    ONDEBUG(cerr << "GUIViewBodyC::DNDDrop(), Called \n");    
    return TRUE;
  }
  
  //: Drag and drop begin.
  
  bool GUIViewBodyC::DNDBegin(GdkDragContext * &dc) {
    ONDEBUG(cerr << "GUIViewBodyC::DNDBegin(), Called \n");
    return true;
  }
  
  //: Drag and drop end.
  
  bool GUIViewBodyC::DNDEnd(GdkDragContext * &dc) {
    ONDEBUG(cerr << "GUIViewBodyC::DNDEnd(), Called \n");
    return true;
  }
  
  //: Drag and drop data recieved
  
  bool GUIViewBodyC::DNDDataRecieved(DNDDataInfoC &info) {
    ONDEBUG(cerr << "GUIViewBodyC::DNDDataRecieved(), Called \n");
    ONDEBUG(cerr << "Data length=" << info.Data()->length << " Format=" << info.Data()->format << " Data=" << (char *) info.Data()->data << " type=" << info.Data()->type << "\n");
    FactoryC fact;
    switch(info.Info()) {
    case 0: /* URL */
      ONDEBUG(cerr << "GUIViewBodyC::DNDDataRecieved(), Got URL. \n");
      if(info.IsString())
	LoadObject(info.String().TopAndTail(),info.At());
      break;
    case 1: /* Object. */
      {
	ONDEBUG(cerr << "GUIViewBodyC::DNDDataRecieved(), Got tag '" << info.String() << "'. \n");
	if(!factories.LookupFactory(info.String(),fact)) {
	  cerr << "GUIViewBodyC::DNDDataRecieved(), ERROR: Unrecognised factory. '" << info.String() << "' \n";
	  break;
	}
	if(!fact.IsValid()) {
	  cerr << "GUIViewBodyC::DNDDataRecieved(), ERROR: No factory. \n";
	  break;
	}
	DFObjectC obj = fact.Create();
	if(!obj.IsValid()) {
	  cerr << "GUIViewBodyC::DNDDataRecieved(), ERROR: Failed to create object. \n";
	  break;
	}
	cerr << "Create '" << info.String() << "'\n";
	AddObject(obj,info.At());
	system.AddObject(obj);
	info.Finish(true,false);
	return true;
      }
    default:
      cerr << "GUIViewBodyC::DNDDataRecieved(), Unexpected drop type. \n";
      break;
    }
    info.Finish(false,false);
    return true;
  }
  
  //: Undo all references.
  
  void GUIViewBodyC::Destroy() {
    //ONDEBUG(cerr << "GUIViewBodyC::Destroy(), Called. \n");
    // Disconnect all signals.
    connectSet.DisconnectAll();
    sysConnectSet.DisconnectAll();
    sigObjChange.DisconnectAll();
    elements.Empty();
    system.Invalidate();
    hold.Invalidate();
    
    // Destory canvas normaly.
    RawCanvasBodyC::Destroy();
  }
  
  
}
