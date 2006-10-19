// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI3D

#include "Ravl/GUI/View3D.hh"
#include "Ravl/GUI/Util.hh"
#include "Ravl/GUI/Menu.hh"
#include "Ravl/GUI/MenuCheck.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/StdMath.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/AxisAngle.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {

  //: Default constructor.
  
  View3DBodyC::View3DBodyC(int sx,int sy,bool enableLighting,bool enableTexture)
    : Canvas3DBodyC(sx,sy),
      sceneComplete(false),
      viewObject(0,0,0),
      viewPoint(0,0,3),
      useRotate(true),
      viewRotate(0,0,0),
      fov(90),
      enablerefresh(false),
      initDone(false),
      m_bAutoCenter(false),
      m_bAutoFit(false),
      m_bTextureStatus(enableTexture),
      m_bLightingStatus(enableLighting),
      m_pixButton0Pos(0,0),
      m_pixButton1Pos(0,0),
      m_fXRotation(0),
      m_fYRotation(0),
      m_fXTranslation(0),
      m_fYTranslation(0),
      m_fZoom(0),
      m_bFront(true),
      m_bBack(false)
  {
    ONDEBUG(cerr << "View3DBodyC::View3DBodyC(), Called. \n");
  }
  
  //: Fit and centre output if appropriate
  void View3DBodyC::DoAuto() {
    if(m_bAutoCenter) Center();
    if(m_bAutoFit)    Fit();
  }
  
  //: Fit object to view
  bool View3DBodyC::Fit() {
    ONDEBUG(cerr << "View3DBodyC::Fit(), Called. \n");
    if (!scene.IsValid()) return false;
    RealT dist = viewObject.EuclidDistance(viewPoint);
    RealT extent = scene.Extent() * 1.3;
    if(dist <= 0)
      dist = 0.01;
    fov = ATan(extent/dist) * (180 / RavlConstN::pi);
    ONDEBUG(cerr << "Set fov to " << fov << "\n");
    Put(DViewPoint3DC(fov,viewPoint,viewObject));
    Refresh();
    return true;
  }
  
  //: Center output.
  bool View3DBodyC::Center() {
    ONDEBUG(cerr << "View3DBodyC::Center(), Called. \n");
    if (!scene.IsValid()) return false;
    viewObject = scene.Center();
    Put(DViewPoint3DC(fov,viewPoint,viewObject));
    ResetCamera();
    Refresh();
    return true;
  }
  
  //: Auto fit output.
  bool View3DBodyC::AutoFit(bool &val) {
    m_bAutoFit = val;
    if(m_bAutoFit) Fit();
    return true;
  }
  
  //: Auto center output.
  bool View3DBodyC::AutoCenter(bool &val) {
    m_bAutoCenter = val;
    if(m_bAutoCenter) Center();
    return false;
  }
  
  //: Handle button press.
  bool View3DBodyC::MousePress(MouseEventC &me) {
    ONDEBUG(cerr << "View3DBodyC::MousePress(), Called. '" << me.HasChanged(0) << " " << me.HasChanged(1) << " " << me.HasChanged(2) <<"' \n");
    if(me.HasChanged(0)) 
      m_pixButton0Pos = me.At();
    else if(me.HasChanged(1)) 
      m_pixButton1Pos = me.At();
    else if(me.HasChanged(2)) {
      ONDEBUG(cerr << "Show menu. \n");
      backMenu.Popup(); 
    }  else if(me.HasChanged(3)) {
      // Zoom in
      //ChangeFOV(-3);
    } else if(me.HasChanged(4)) {
      // Zoom out
      //ChangeFOV(3);
    }
    
    return true;
  }
  
  //: Handle button release.
  bool View3DBodyC::MouseRelease(MouseEventC &me) {
    ONDEBUG(cerr << "View3DBodyC::MouseRelease(), Called. '" << me.HasChanged(0) << " " << me.HasChanged(1) << " " << me.HasChanged(2) <<"' \n");
    return true;
  }
  
  //: Handle mouse move.
  bool View3DBodyC::MouseMove(MouseEventC &me) {
    //ONDEBUG(cerr << "View3DBodyC::MouseMove(), Called. '" << me.HasChanged(0) << " " << me.HasChanged(1) << " " << me.HasChanged(2) <<"' \n");
    //ONDEBUG(cerr << "View3DBodyC::MouseMove(),         '" << me.IsPressed(0) << " " << me.IsPressed(1) << " " << me.IsPressed(2) <<"' \n");
    //cerr << "View3DBodyC::MouseMove(), Called. \n";
    
  // X rotation limit values
    const RealT upper_limit = 90;
    const RealT lower_limit = -90;
    
    // Zoom in and out if buttons 0 and 1 are pressed
    if (me.IsPressed(0) && me.IsPressed(1)) {
      // Calculate change
      Index2dC change = me.At() -  m_pixButton0Pos; 
      
      // Calculate individual rotations
      m_fZoom += change.Col();
      
      // Store new position
      m_pixButton0Pos = m_pixButton1Pos = me.At();
      
      // Update display
      Refresh();
    }
    
    // Rotate when button 0 pressed
    else if(me.IsPressed(0)) {
      // Calculate change
      Index2dC change = me.At() -  m_pixButton0Pos; 
      
      // Calculate individual rotations
      m_fXRotation += change.Row();
      m_fYRotation += change.Col();
      
      // Limit X rotation
      if (m_fXRotation > upper_limit) m_fXRotation = upper_limit;
      else if (m_fXRotation < lower_limit) m_fXRotation = lower_limit;
      
      // Store new position
      m_pixButton0Pos = me.At();
      
      // Update display
      Refresh();
    }
    
    // Translate when button 1 pressed
    else if (me.IsPressed(1)) {
      // Calculate change
      Index2dC change = me.At() -  m_pixButton1Pos; 
      
      // Calculate individual translations
      // X & Y in GTK coords; hence also Y is inverted
      m_fXTranslation += (RealT)change.Col() / 100.0;
      m_fYTranslation -= (RealT)change.Row() / 100.0;
      
      // Store new position
      m_pixButton1Pos = me.At();
      
      // Update display
      Refresh();
    }
    return true;
  }
  
  //: Setup widget.
  bool View3DBodyC::Create() {
    ONDEBUG(cerr << "View3DBodyC::Create(), Called. \n");
    
    ConnectRef(Signal("button_press_event"),*this,&View3DBodyC::MousePress);
    ConnectRef(Signal("button_release_event"),*this,&View3DBodyC::MouseRelease);
    ConnectRef(Signal("motion_notify_event"),*this,&View3DBodyC::MouseMove);
    ConnectRef(Signal("expose_event"),*this,&View3DBodyC::Refresh);
    
    if(!Canvas3DBodyC::Create()) {
      // Get this sorted out early.
      cerr << "View3DBodyC::Create(), ERROR: Canvas3DBodyC create failed. \n";
      return false;
    }
    
    ONDEBUG(cerr << "View3DBodyC::Create(), Setting up canvas intialization. \n");
    
    // Setup render options
    m_oRenderOpts[0] = MenuCheckItemC("Points",false);
    m_oRenderOpts[1] = MenuCheckItemC("Wire",false);
    m_oRenderOpts[2] = MenuCheckItemC("Flat",false);
    m_oRenderOpts[3] = MenuCheckItemC("Smooth",true);
    for (int i=0; i<4; i++) {
      ConnectRef(m_oRenderOpts[i].SigSelected(),*this,&View3DBodyC::SelectRenderMode,i);
    }
    
    MenuC renderMenu("Render",
		     m_oRenderOpts[0] +
		     m_oRenderOpts[1] +
		     m_oRenderOpts[2] +
		     m_oRenderOpts[3] +
		     MenuItemSeparator() +
		     MenuCheckItem("Texturing",m_bTextureStatus,Canvas3DC(*this),&Canvas3DC::SetTextureMode) +
		     MenuCheckItem("Lighting",m_bLightingStatus,Canvas3DC(*this),&Canvas3DC::SetLightingMode)
		     );
    
    MenuC facesMenu("Faces",
		    MenuCheckItemR("Front",m_bFront,*this,&View3DBodyC::FrontFaces) +
		    MenuCheckItemR("Back",m_bBack,*this,&View3DBodyC::BackFaces)
		    );
    
    backMenu = MenuC("back",
		     MenuItemR("Center",*this,&View3DBodyC::Center) +
		     MenuItemR("Fit",*this,&View3DBodyC::Fit) +
		     MenuCheckItemR("Auto Center",*this,&View3DBodyC::AutoCenter) +
		     MenuCheckItemR("Auto Fit",*this,&View3DBodyC::AutoFit) +
		     MenuItemSeparator() +
		     renderMenu +
		     facesMenu
		     );
    
    
    ONDEBUG(cerr << "View3DBodyC::Create(), Doing setup. \n");
    
    // Initialise OpenGL
    Put(DOpenGLC(Trigger(View3DC(*this),&View3DC::InitGL)));
    
    // Setup lights and cameras
    Put(DLight3DC(RealRGBValueC(1,1,1),Point3dC(0,0,10)));
    Put(DViewPoint3DC(90,viewPoint));
    
    SetTextureMode(m_bTextureStatus);
    SetLightingMode(m_bLightingStatus);
    
    ONDEBUG(cerr << "View3DBodyC::Create(), Done. \n");
    return true;
  }
  
  //: Put render instructon into pipe.
  
  bool View3DBodyC::Add(const DObject3DC &r, IntT id) {
    ONDEBUG(cerr << "View3DBodyC::Add(), Called. \n");
    if(sceneComplete || !scene.IsValid()) {
      scene = DObjectSet3DC(true);
      sceneComplete = false;
    }
    if(r.IsValid())
      scene += r;
    // Do auto-fit and auto-centre
    enablerefresh = false;
    DoAuto();
    enablerefresh = true;
    // Refresh display
    Refresh();
    ONDEBUG(cerr << "View3DBodyC::Add(), Done. \n");
    return true;
  }
  
  //: Refresh display.
  bool View3DBodyC::Refresh() {
    if(!(initDone && enablerefresh))
      return false;

    ONDEBUG(cerr << "View3DBodyC::Refresh(), Called. " << ((void *) widget) << "\n");
    
    // Init new frame
    Put(DOpenGLC(Trigger(View3DC(*this),&View3DC::NewFrame)));
    Put(DOpenGLC(Trigger(View3DC(*this),&View3DC::SetCamera)));
    
    // Render scene
    if(scene.IsValid()) Put(scene);
    SwapBuffers();

    // Finished
    return true;
  }
  
  //: Reset the camera position
  void View3DBodyC::ResetCamera() {
    m_fXRotation = 0;
    m_fYRotation = 0;
    m_fXTranslation = 0;
    m_fYTranslation = 0;
    m_fZoom = 0;
    return;
  }
  
  bool View3DBodyC::SelectRenderMode(int& iOption) {
    bool bVal = m_oRenderOpts[iOption].IsActive();
    if (bVal) {
      for (int i=0; i<4; i++) {
	if (i!=iOption) {
	  m_oRenderOpts[i].SetActive(false);
	}
      }
      Canvas3DRenderMode mode;
      switch (iOption) {
      case 0:
	mode = C3D_POINT;
	break;
      case 1:
	mode = C3D_WIRE;
	break;
      case 2:
	mode = C3D_FLAT;
	break;
      case 3:
      default:
	mode = C3D_SMOOTH;
	break;
      }	
      SetRenderMode(mode);
    }
    else {
      int iNumTrue = 0;
      for (int i=0; i<4; i++) {
	if (i!=iOption && m_oRenderOpts[i].IsActive()) iNumTrue++;
      }
      if (iNumTrue == 0) {
	m_oRenderOpts[iOption].SetActive(true);
      }
    }
    return true;
  }
  
  bool View3DBodyC::InitGL() {
    ONDEBUG(cerr << "View3DBodyC::InitGL(), Called. \n");
    // Set up culling
    SetCullMode();
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    // Init shade model
    glShadeModel(GL_SMOOTH);
    Canvas3DRenderMode mode = C3D_SMOOTH;
    SetRenderMode(mode);
    // Let everyone know we're ready to go.
    initDone = true;
    return true;
  }
  
  void View3DBodyC::SetCullMode() {
    ONDEBUG(cerr << "View3DBodyC::SetCullMode(), Called. \n");
    
    if (m_bFront) {
      if (m_bBack) {
	glDisable(GL_CULL_FACE);
      }
      else {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
      }
    }
    else {
      if (m_bBack) {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);      
      }
      else {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT_AND_BACK);
      }    
    }
  }
  
  bool View3DBodyC::NewFrame() {
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset matrix
    glLoadIdentity();
    // Done
    return true;
  }
  
  bool View3DBodyC::SetCamera() {
    // Rotate scene
    glRotated(m_fXRotation,1,0,0);
    glRotated(m_fYRotation,0,1,0);
    
    // Translate scene
    //Vector3dC vecTranslation(m_fXTranslation,0,0);
    //vecTranslation = AxisAngleC(0,m_fYRotation,0).Matrix() * vecTranslation;
    //glTranslated(vecTranslation.X(),m_fYTranslation,vecTranslation.Z());
    //glTranslated(m_fXTranslation,m_fYTranslation,0);  
    
    // Done
    return true;
  }

}
