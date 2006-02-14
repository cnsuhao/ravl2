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
#include "Ravl/GUI/DPDisplayImage.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  //: Default constructor.
  
  DPDisplayViewBodyC::DPDisplayViewBodyC(const IndexRange2dC &size) 
    : TableBodyC(3,5),
      winSize(size),
      refreshQueued(false),
      vRuler(true),
      hRuler(false),
      offset(size.Range1().Min(),size.Range2().Min()),
      lastMousePos(-1000,-1000),
      backMenu("BackMenu")
  {}
  
  //: Create the widget.
  
  bool DPDisplayViewBodyC::Create() {
    ONDEBUG(cerr << "DPDisplayViewBodyC::Create(), Called \n");
    
    backMenu.GUIAdd(MenuItemR("Save",*this, &DPDisplayViewBodyC::CallbackStartSave));
    menuBar.GUIAdd(MenuItemR("Save",*this, &DPDisplayViewBodyC::CallbackStartSave));
    
    fileSelector = FileSelectorC("@X Save");
    ConnectRef(fileSelector.Selected(),*this,&DPDisplayViewBodyC::CallbackSave);
    
    int rows = winSize.Cols();
    int cols = winSize.Rows();
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
    colPos=LabelC("0");
    rowPos=LabelC("0");
    info=LabelC("-");
    //xpos = TextEntryC("",3,false);
    //ypos = TextEntryC("",3,false);
    //info = TextEntryC("",-1,false);
    
    DPDisplayViewC thisH(*this);
    
    int r1min = winSize.Range1().Min().V();
    int r2min = winSize.Range2().Min().V();
    int r1max = winSize.Range1().Max().V();
    int r2max = winSize.Range2().Max().V();
    
    vSlider = SliderVR(r1min,r1min,r1max,1.0,*this,&DPDisplayViewBodyC::CallbackYOffset);
    hSlider = SliderHR(r2min,r2min,r2max,1.0,*this,&DPDisplayViewBodyC::CallbackXOffset);
    vSlider.SetDrawValue(false);
    hSlider.SetDrawValue(false);
    
    vRuler.GUIAttachTo(canvas);
    hRuler.GUIAttachTo(canvas);

    TableBodyC::GUIAddObject(menuBar,0,3,0,1,(GtkAttachOptions)(GTK_EXPAND|GTK_FILL|GTK_SHRINK),(GtkAttachOptions) (GTK_SHRINK|GTK_FILL));    
    TableBodyC::GUIAddObject(vRuler,0,1,2,3,GTK_FILL,(GtkAttachOptions) (GTK_EXPAND|GTK_SHRINK|GTK_FILL));
    TableBodyC::GUIAddObject(hRuler,1,2,1,2,(GtkAttachOptions) (GTK_EXPAND|GTK_SHRINK|GTK_FILL),GTK_FILL);
    TableBodyC::GUIAddObject(vSlider,2,3,2,3,GTK_FILL,(GtkAttachOptions) (GTK_EXPAND|GTK_SHRINK|GTK_FILL));
    TableBodyC::GUIAddObject(hSlider,1,2,3,4,(GtkAttachOptions) (GTK_EXPAND|GTK_SHRINK|GTK_FILL),GTK_FILL);
    TableBodyC::GUIAddObject(HBox(PackInfoC(Label(" Row="),false,false) + PackInfoC(rowPos,false,false) +
			       PackInfoC(Label(" Col="),false,false) + PackInfoC(colPos,false,false) + 
			       PackInfoC(Label("  Value="),false,false) + PackInfoC(info,true,false)),
			  0,3,4,5,
			  (GtkAttachOptions)(GTK_FILL),
			  (GtkAttachOptions)(GTK_FILL));
    
    TableBodyC::GUIAddObject(canvas,1,2,2,3,
			  (GtkAttachOptions)(GTK_FILL|GTK_SHRINK),
			  (GtkAttachOptions)(GTK_FILL|GTK_SHRINK)
			  );
    ConnectRef(canvas.Signal("expose_event"),*this,&DPDisplayViewBodyC::CallbackExpose);
    ConnectRef(canvas.Signal("configure_event"),*this,&DPDisplayViewBodyC::CallbackConfigure,(GdkEvent *) 0);    
    ConnectRef(canvas.Signal("motion_notify_event"),*this,&DPDisplayViewBodyC::CallbackMouseMotion);    
    ConnectRef(canvas.Signal("button_press_event"),*this,&DPDisplayViewBodyC::CallbackMousePress); 
    
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
    hold.Unlock();
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
  
  bool DPDisplayViewBodyC::GUIUpdateRuler() {
    ONDEBUG(cerr << "DPDisplayViewBodyC::UpdateRuler(), Called. \n");
    Index2dC canSize = canvas.Size();
    RealT val1 = offset[0] + canSize[0];
    vRuler.GUISetRange(offset[0],val1);
    RealT val2 = offset[0] + canSize[0];
    hRuler.GUISetRange(offset[1],val2);    
    return true;
  }
  
  //: Update ruler info.
  
  bool DPDisplayViewBodyC::UpdateRuler() {
    Manager.QueueOnGUI(Trigger(DPDisplayViewC(*this),&DPDisplayViewC::GUIUpdateRuler));    
    return true;
  }

  bool DPDisplayViewBodyC::UpdateSlider() {
    Manager.QueueOnGUI(Trigger(DPDisplayViewC(*this),&DPDisplayViewC::GUIUpdateSlider));        
    return true;
  }
  
  //: Update sliders info.
  
  bool DPDisplayViewBodyC::GUIUpdateSlider() {
    RWLockHoldC hold(lockDisplayList,RWLOCK_READONLY); // To protect access to displaySize.
    Index2dC canSize = canvas.Size();
    int vdiff = displaySize.Range1().Max().V() - canSize[0].V();
    int hdiff = displaySize.Range2().Max().V() - canSize[1].V();
    ONDEBUG(cerr << "DPDisplayViewBodyC::UpdateSlider(), Called. canSize=" << canSize <<" DisplaySize=" << displaySize.Rows() << " " << displaySize.Cols()<< " \n");
    if(vdiff < 0)
      vdiff = 0;
    if(hdiff < 0)
      hdiff = 0;
    vSlider.GUIUpdateRange(displaySize.Range1().Min().V(),vdiff);
    if(vdiff == 0 && displaySize.Range1().Min() >= 0) 
      vSlider.GUIHide();
    else vSlider.GUIShow();      
    hSlider.GUIUpdateRange(displaySize.Range2().Min().V(),hdiff);
    if(hdiff == 0 && displaySize.Range2().Min() >= 0)
      hSlider.GUIHide();
    else hSlider.GUIShow();      
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
    GUIUpdateRuler();
    GUIUpdateSlider();
    return true;
  }
  
  //: Set X offset.
  
  bool DPDisplayViewBodyC::CallbackXOffset(RealT &val) {
    ONDEBUG(cerr << "DPDisplayViewBodyC::CallbackXOffset(), Called. Value=" << val << "\n");
    offset[1]=val;
    GUIUpdateRuler();
    GUIRefresh();
    return true;
  }
  
  //: Set Y offset.
  
  bool DPDisplayViewBodyC::CallbackYOffset(RealT &val) {
    ONDEBUG(cerr << "DPDisplayViewBodyC::CallbackYOffset(), Called. Value=" << val << "\n");
    offset[0]=val;
    GUIUpdateRuler();
    GUIRefresh();
    return true;
  }

  //: Call back for mouse movements in the window.
  
  bool DPDisplayViewBodyC::CallbackMouseMotion(MouseEventC &mouseEvent) {
    Index2dC idx ( mouseEvent.At() ) ;  // gets the position of the mose event in RAVL co-ordinates not GTK
    Vector2dC pos ( idx[0] , idx[1]  ) ; 
    UpdateInfo(pos);
    lastMousePos = pos;
    return true;
  }
  
  //: Call back for mouse press events.
  
  bool DPDisplayViewBodyC::CallbackMousePress(MouseEventC &mouseEvent) {
    ONDEBUG(cerr << "DPDisplayViewBodyC::CallbackMousePress(), Called. \n");
    if(mouseEvent.HasChanged(2))
      backMenu.Popup();
    return true;
  }
  
  //: Update info for mouse position.
  
  bool DPDisplayViewBodyC::UpdateInfo(const Vector2dC &at) {
    if(at[0] < 0 || at[1] < 0)
      return false;
    Vector2dC pos = at+ offset; // ravl co-ords
    StringC rowps((int) pos[0]);
    rowPos.Label(rowps);
    StringC colps((int) pos[1]);
    colPos.Label(colps);
    StringC infos("-");
    Query(pos,infos);
    info.Label(infos);
    return true;
  }

  //: Start image save.
  
  bool DPDisplayViewBodyC::CallbackStartSave() {
    ONDEBUG(cerr << "DPDisplayViewBodyC::CallbackStartSave(), Called. \n");
    fileSelector.Show();
    return true;
  }

  //: Save image to a file.
  
  bool DPDisplayViewBodyC::CallbackSave(StringC &str) {
    ONDEBUG(cerr << "DPDisplayViewBodyC::CallbackSave(), Called. File='" << str << "' \n");
    for(DLIterC<DPDisplayObjC> it(displayList);it;it++) {
      if(it->Save(str))
	break;
    }
    return true;
  }

}
