// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlDPDisplay
//! file="Ravl/GUI/DPDisplay/DPDisplayView.cc"

#include "Ravl/GUI/DPDisplayView.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/PackInfo.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  //: Default constructor.
  
  DPDisplayViewBodyC::DPDisplayViewBodyC(const IndexRange2dC &size) 
    : TableBodyC(3,4),
      winSize(size),
      refreshQueued(false),
      vRuler(true),
      hRuler(false),
      offset(0,0),
      lastMousePos(-1000,-1000)
  {}
  
  //: Create the widget.
  
  bool DPDisplayViewBodyC::Create() {
    ONDEBUG(cerr << "DPDisplayViewBodyC::Create(), Called \n");
    
    int rows = winSize.RCol().V();
    int cols = winSize.BRow().V();
    // Limit maximum inital size.
    if(rows > 700)
      rows = 700;
    if(rows < 30)
      rows = 30;
    if(cols > 800)
      cols = 800;
    if(cols < 30)
       cols = 30;
    canvas = RawCanvasC(rows,cols);
    xpos=LabelC("0");
    ypos=LabelC("0");
    info=LabelC("-");
    //xpos = TextEntryC("",3,false);
    //ypos = TextEntryC("",3,false);
    //info = TextEntryC("",-1,false);
    
    DPDisplayViewC thisH(*this);
    
    vSlider = SliderVR(1.0,0.0,100.0,1.0,*this,&DPDisplayViewBodyC::CallbackYOffset);
    hSlider = SliderHR(1.0,0.0,100.0,1.0,*this,&DPDisplayViewBodyC::CallbackXOffset);
    vSlider.SetDrawValue(false);
    hSlider.SetDrawValue(false);
    
    vRuler.AttachTo(canvas);
    hRuler.AttachTo(canvas);
    
    TableBodyC::AddObject(vRuler,0,1,1,2,GTK_FILL,(GtkAttachOptions) (GTK_EXPAND|GTK_SHRINK|GTK_FILL));
    TableBodyC::AddObject(hRuler,1,2,0,1,(GtkAttachOptions) (GTK_EXPAND|GTK_SHRINK|GTK_FILL),GTK_FILL);
    TableBodyC::AddObject(vSlider,2,3,1,2,GTK_FILL,(GtkAttachOptions) (GTK_EXPAND|GTK_SHRINK|GTK_FILL));
    TableBodyC::AddObject(hSlider,1,2,2,3,(GtkAttachOptions) (GTK_EXPAND|GTK_SHRINK|GTK_FILL),GTK_FILL);
    TableBodyC::AddObject(HBox(PackInfoC(Label(" Row="),false,false) + PackInfoC(xpos,false,false) +
			       PackInfoC(Label(" Col="),false,false) + PackInfoC(ypos,false,false) + 
			       PackInfoC(Label("  Value="),false,false) + PackInfoC(info,true,false)),
			  0,3,3,4,
			  (GtkAttachOptions)(GTK_FILL),
			  (GtkAttachOptions)(GTK_FILL));
    
    TableBodyC::AddObject(canvas,1,2,1,2,
			  (GtkAttachOptions)(GTK_FILL|GTK_SHRINK),
			  (GtkAttachOptions)(GTK_FILL|GTK_SHRINK)
			  );
    ConnectRef(canvas.Signal("expose_event"),*this,&DPDisplayViewBodyC::CallbackExpose);
    ConnectRef(canvas.Signal("configure_event"),*this,&DPDisplayViewBodyC::CallbackConfigure,(GdkEvent *) 0);    
    ConnectRef(canvas.Signal("motion_notify_event"),*this,&DPDisplayViewBodyC::CallbackMouseMotion);    
    
    if(!TableBodyC::Create())
      return false;
    
    return true;
  }
  
  //: Add object to the display list.

  bool DPDisplayViewBodyC::AddObject(const DPDisplayObjC &obj) {
    ONDEBUG(cerr << "DPDisplayViewBodyC::AddObject(), Called \n");
    RWLockHoldC hold(lockDisplayList,RWLOCK_WRITE);
    if(displayList.IsEmpty())
      displaySize = obj.Frame();
    else
      displaySize.Involve(obj.Frame());
    displayList.InsLast(obj);
    Refresh();
    return true;
  }
  
  //: Clear the display list.
  
  bool DPDisplayViewBodyC::Clear() {
    ONDEBUG(cerr << "DPDisplayViewBodyC::Clear(), Called \n");
    RWLockHoldC hold(lockDisplayList,RWLOCK_WRITE);
    displayList.Empty(); 
    return true;
  }
  
  //: Refresh the display.
  
  bool DPDisplayViewBodyC::Refresh() {
    ONDEBUG(cerr << "DPDisplayViewBodyC::Refresh(), Called \n");
    if(refreshQueued)
      return true;
    refreshQueued = true;
    Manager.Queue(Trigger(DPDisplayViewC(*this),&DPDisplayViewC::GUIRefresh));
    return true;
  }
  
  //: Refresh the display.
  
  bool DPDisplayViewBodyC::GUIRefresh() {
    ONDEBUG(cerr << "DPDisplayViewBodyC::GUIRefresh(), Called \n");
    if(!canvas.IsValid() || canvas.Widget() == 0) {
      refreshQueued = false;
      return false;
    }
    RWLockHoldC hold(lockDisplayList,RWLOCK_READONLY);
    refreshQueued = false;
    for(DLIterC<DPDisplayObjC> it(displayList);it;it++)
      it->Draw(*this);
    hold.Unlock();
    UpdateSlider();
    UpdateInfo(lastMousePos);
    return true;
  }

  //: Update ruler info.
  
  bool DPDisplayViewBodyC::UpdateRuler() {
    ONDEBUG(cerr << "DPDisplayViewBodyC::UpdateRuler(), Called. \n");
    Index2dC canSize = canvas.Size();
    vRuler.SetRange(offset[0],offset[0] + canSize[0]);
    hRuler.SetRange(offset[1],offset[1] + canSize[1]);
    return true;
  }
  
  //: Update sliders info.
  
  bool DPDisplayViewBodyC::UpdateSlider() {
    RWLockHoldC hold(lockDisplayList,RWLOCK_READONLY); // To protect access to displaySize.
    Index2dC canSize = canvas.Size();
    int vdiff = displaySize.Range1().Max().V() - canSize[0].V();
    int hdiff = displaySize.Range2().Max().V() - canSize[1].V();
    ONDEBUG(cerr << "DPDisplayViewBodyC::UpdateSlider(), Called. canSize=" << canSize <<" DisplaySize=" << displaySize.Rows() << " " << displaySize.Cols()<< " \n");
    if(vdiff < 0)
      vdiff = 0;
    if(hdiff < 0)
      hdiff = 0;
    if(vdiff == 0 && displaySize.Range1().Min() >= 0) 
      vSlider.Hide();
    else vSlider.Show();      
    vSlider.UpdateRange(displaySize.Range1().Min().V(),vdiff);
    if(hdiff == 0 && displaySize.Range2().Min() >= 0)
      hSlider.Hide();
    else hSlider.Show();      
    hSlider.UpdateRange(displaySize.Range2().Min().V(),hdiff);
    return true;
  }

  //: Query position,
  
  bool DPDisplayViewBodyC::Query(Vector2dC pos,StringC &info) { 
    //ONDEBUG(cerr <<"DPDisplayViewBodyC::Query(), Position=" << pos << "\n");
    RWLockHoldC hold(lockDisplayList,RWLOCK_READONLY); // To protect access to displaySize.
    for(DLIterC<DPDisplayObjC> it(displayList);it;it++) {
      if(it->Query(pos,info)) {
	//ONDEBUG(cerr <<"DPDisplayViewBodyC::Query(), Position=" << pos << " Result=" << info <<"\n");
	return true;
      }
    }
    //ONDEBUG(cerr <<"DPDisplayViewBodyC::Query(), Position=" << pos << " No result.\n");
    return false;
  }
  
  //: Handle an expose event.
  
  bool DPDisplayViewBodyC::CallbackExpose(GdkEvent *&event) {
    ONDEBUG(cerr << "DPDisplayViewBodyC::Expose(), Called \n");
    RWLockHoldC hold(lockDisplayList,RWLOCK_READONLY);
    for(DLIterC<DPDisplayObjC> it(displayList);it;it++)
      it->Draw(*this);
    return true;
  }

  //: Handle configure callback.
  
  bool DPDisplayViewBodyC::CallbackConfigure(GdkEvent *&event) {
    ONDEBUG(cerr << "DPDisplayViewBodyC::CallbackConfigure(), Called. \n");
    UpdateRuler();
    UpdateSlider();
    return true;
  }
  
  //: Set X offset.
  
  bool DPDisplayViewBodyC::CallbackXOffset(RealT &val) {
    ONDEBUG(cerr << "DPDisplayViewBodyC::CallbackXOffset(), Called. Value=" << val << "\n");
    offset[1]=val;
    UpdateRuler();
    Refresh();
    return true;
  }
  
  //: Set Y offset.
  
  bool DPDisplayViewBodyC::CallbackYOffset(RealT &val) {
    ONDEBUG(cerr << "DPDisplayViewBodyC::CallbackYOffset(), Called. Value=" << val << "\n");
    offset[0]=val;
    UpdateRuler();
    Refresh();
    return true;
  }

  //: Call back for mouse movements in the window.
  
  bool DPDisplayViewBodyC::CallbackMouseMotion(MouseEventC &mouseEvent) {
    Vector2dC pos(mouseEvent.X(),mouseEvent.Y());
    //ONDEBUG(cerr << "DPDisplayViewBodyC::CallbackMouseMotion(), Called. Posision=" << pos <<"\n");
    UpdateInfo(pos);
    lastMousePos = pos;
    return true;
  }
  
  //: Update info for mouse position.
  
  bool DPDisplayViewBodyC::UpdateInfo(const Vector2dC &at) {
    if(at[0] < 0 || at[1] < 0)
      return false;
    Vector2dC pos = at+ offset;
    StringC rowps((int) pos[0]);
    StringC colps((int) pos[1]);
    xpos.Label(colps);
    ypos.Label(rowps);
    StringC infos("-");
    Query(pos,infos);
    info.Label(infos);
    return true;
  }


}
