// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI3D

#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/View3D.hh"
#include "Ravl/GUI/Util.hh"
#include "Ravl/GUI/Menu.hh"
#include "Ravl/GUI/MenuCheck.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/StdMath.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/AxisAngle.hh"
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <GL/glu.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
static RavlN::StringC GLGetString(GLenum Name)
{
  char *ptr = (char *)glGetString(Name);
  RavlN::StringC res = ptr != NULL ? ptr : "NULL";
  return res;
}
#else
#define ONDEBUG(x)
#endif


namespace RavlGUIN {

  //: Default constructor.
  View3DBodyC::View3DBodyC(int sx,int sy,bool enableLighting,bool enableTexture)
    : Canvas3DBodyC(sx,sy),
      sceneComplete(false),
      initDone(false),
      m_sceneExtent(1),
      m_viewPoint(0, 0, 10),
      m_sceneCenter(0, 0, 0),
      m_bTextureStatus(enableTexture),
      m_bLightingStatus(enableLighting),
      m_bFront(true),
      m_bBack(false)
  {
    ONDEBUG(cerr << "View3DBodyC::View3DBodyC(), Called. \n");
  }

  bool View3DBodyC::GUIInitGL()
  {
    ONDEBUG(cerr << "View3DBodyC::InitGL(), Called. \n");
    // Set up culling
    GUISetCullMode();
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    // Init shade model
    glShadeModel(GL_SMOOTH);
    Canvas3DRenderMode mode = C3D_SMOOTH;
    SetRenderMode(mode);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    ONDEBUG(cerr << "OpenGL vendor    :" << GLGetString(GL_VENDOR) << endl);
    ONDEBUG(cerr << "OpenGL renderer  :" << GLGetString(GL_RENDERER) << endl);
    ONDEBUG(cerr << "OpenGL version   :" << GLGetString(GL_VERSION) << endl);
    ONDEBUG(cerr << "OpenGL extensions:" << GLGetString(GL_EXTENSIONS) << endl);

    // Let everyone know we're ready to go.
    initDone = true;
    return true;
  }

  //: Setup widget.
  bool View3DBodyC::Create(GtkWidget *Parent)
  {
    ONDEBUG(cerr << "View3DBodyC::Create(), Called. \n");

    ConnectRef(Signal("button_press_event"),   *this, &View3DBodyC::MousePress);
    ConnectRef(Signal("button_release_event"), *this, &View3DBodyC::MouseRelease);
    ConnectRef(Signal("motion_notify_event"),  *this, &View3DBodyC::MouseMove);
    ConnectRef(Signal("scroll_event"),         *this, &View3DBodyC::MouseWheel);
    ConnectRef(Signal("expose_event"),         *this, &View3DBodyC::Refresh);

    if(!Canvas3DBodyC::Create(Parent))
    {
      // Get this sorted out early.
      cerr << "View3DBodyC::Create(), ERROR: Canvas3DBodyC create failed. \n";
      return false;
    }

    ONDEBUG(cerr << "View3DBodyC::Create(), Setting up canvas intialization. \n");

    // Setup render options
    m_oRenderOpts[0] = MenuCheckItemC("Points", false);
    m_oRenderOpts[1] = MenuCheckItemC("Wire",   false);
    m_oRenderOpts[2] = MenuCheckItemC("Flat",   false);
    m_oRenderOpts[3] = MenuCheckItemC("Smooth", true);
    for(int i=0; i<4; i++) {
      ConnectRef(m_oRenderOpts[i].SigSelected(), *this, &View3DBodyC::SelectRenderMode, i);
    }

    MenuC renderMenu("Render",
                     m_oRenderOpts[0] +
                     m_oRenderOpts[1] +
                     m_oRenderOpts[2] +
                     m_oRenderOpts[3] +
                     MenuItemSeparator() +
                     MenuCheckItem("Texturing", m_bTextureStatus,  Canvas3DC(*this), &Canvas3DC::SetTextureMode) +
                     MenuCheckItem("Lighting",  m_bLightingStatus, Canvas3DC(*this), &Canvas3DC::SetLightingMode)
                    );

    MenuC facesMenu("Faces",
                    MenuCheckItemR("Front", m_bFront, *this, &View3DBodyC::GUIFrontFaces) +
                    MenuCheckItemR("Back",  m_bBack,  *this, &View3DBodyC::GUIBackFaces)
                   );

    backMenu = MenuC("back",
                     MenuItemR("Center",           *this, &View3DBodyC::GUICenter) +
                     MenuItemR("Fit",              *this, &View3DBodyC::GUIFit) +
                     MenuItemR("Upright",          *this, &View3DBodyC::GUIResetRotation) +
                     //MenuCheckItemR("Auto Center", *this, &View3DBodyC::GUIAutoCenter) +
                     //MenuCheckItemR("Auto Fit",    *this, &View3DBodyC::GUIAutoFit) +
                     MenuItemSeparator() +
                     renderMenu +
                     facesMenu
                    );

    ONDEBUG(cerr << "View3DBodyC::Create(), Doing setup. \n");

    SetTextureMode(m_bTextureStatus);
    SetLightingMode(m_bLightingStatus);

    // Put Initialise OpenGL into queue
    Manager.Queue(Trigger(View3DC(*this), &View3DC::GUIInitGL));

    // Setup lights and cameras (it is ok to delayed render here)
    //Put(DLight3DC(RealRGBValueC(1, 1, 1), Point3dC(0, 0, 10)));
    Manager.Queue(Trigger(View3DC(*this), &View3DC::GUIAdjustView));

    ONDEBUG(cerr << "View3DBodyC::Create(), Done. \n");
    return true;
  }

  //: ADD object into the view.
  bool View3DBodyC::GUIAdd(const DObject3DC &r, IntT id)
  {
    ONDEBUG(cerr << "View3DBodyC::GUIAdd(), Called. \n");
    {
      RWLockHoldC lockHold(viewLock, RWLOCK_WRITE);
      if(sceneComplete || !scene.IsValid()) {
        scene = DObjectSet3DC(true);
        sceneComplete = false;
      }
      if(r.IsValid())
        scene += r;
    }

    ONDEBUG(cerr << "View3DBodyC::GUIAdd(), Done. \n");
    return true;
  }

  //: ADD object into the view.
  bool View3DBodyC::Add(const DObject3DC &r, IntT id)
  {
    ONDEBUG(cerr << "View3DBodyC::Add(), Called. \n");
    {
      RWLockHoldC lockHold(viewLock, RWLOCK_WRITE);
      if(sceneComplete || !scene.IsValid()) {
        scene = DObjectSet3DC(true);
        sceneComplete = false;
      }
      if(r.IsValid())
        scene += r;
    }

    ONDEBUG(cerr << "View3DBodyC::Add(), Done. \n");
    return true;
  }

  //: Make the scene complete.
  // If more objects are Add()ed after this, a new scene will be started
  void View3DBodyC::GUISceneComplete()
  {
    sceneComplete = true;
    CalcViewParams(true);
    GUIBeginGL();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    m_viewPoint = Vector3dC(0., 0., 5. * m_sceneExtent);
    GUIAdjustView();
    GUIRefresh();
  }

  //: adjust view point
  bool View3DBodyC::GUIAdjustView()
  {
    ONDEBUG(cerr << "View3DBodyC::AdjustView(), Called. \n");

    //lock scene
    RWLockHoldC lockHold(viewLock, RWLOCK_READONLY);

    if(!scene.IsValid())
      return false;

    Vector3dC lookAt(0., 0., 0.);
    RealT dist = lookAt.EuclidDistance(m_viewPoint);
    //cerr << "viewObj:" << lookAt << "  dist:" << dist << endl;
    if(dist <= 0)
      dist = 0.01;
    //if(dist <= m_sceneExtent)
    //  cerr << "View point could be inside scene\n";

    GUIBeginGL();
    //get viewport parameters
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    //cerr << "View port:" << viewport[0] << "  " << viewport[1] << "  " << viewport[2] << "  " << viewport[3] << "  " << endl;

    GLdouble fNear = dist - m_sceneExtent;
    GLdouble fFar = dist + m_sceneExtent;
    if(fNear < 0.1)
      fNear = 0.1;
    GLdouble extent = m_sceneExtent * fNear / dist;

    GLdouble extHor, extVer;
    if(viewport[2] < viewport[3])
    {
      extHor = extent;
      extVer = extent * viewport[3] / viewport[2];
    }
    else
    {
      extHor = extent * viewport[2] / viewport[3];
      extVer = extent;
    }

    //setup light
    Canvas3DC me(*this);
    DLight3DC(RealRGBValueC(1., 1., 1.), m_viewPoint).GUIRender(me);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //cerr << "ext:" << extHor << "   " << extVer << endl;
    //cerr << "depth:" << fNear << "   " << fFar << endl;
    glFrustum(-extHor, extHor, -extVer, extVer, fNear, fFar);

    //setup view point
    gluLookAt(m_viewPoint.X(),   m_viewPoint.Y(),   m_viewPoint.Z(),
              lookAt.X(),        lookAt.Y(),        lookAt.Z(),
              0.,                1.,                0.);
    //FMatrixC<4, 4> projectionMat;
    //glGetDoublev(GL_PROJECTION_MATRIX, &(projectionMat[0][0]));
    //cerr << "pMat:\n" << projectionMat << endl;


    return true;
  }

  //: Fit object to view
  bool View3DBodyC::GUIFit()
  {
    ONDEBUG(cerr << "View3DBodyC::GUIFit(), Called. \n");
    CalcViewParams(true);
    GUIAdjustView();
    GUIRefresh();
    return true;
  }

  //: Center output.
  bool View3DBodyC::GUICenter() {
    ONDEBUG(cerr << "View3DBodyC::GUICenter(), Called. \n");
    GUIAdjustView();
    GUIRefresh();
    return true;
  }

  //: Center output.
  bool View3DBodyC::GUIResetRotation() {
    ONDEBUG(cerr << "View3DBodyC::GUIResetRotation(), Called. \n");
    if(GUIBeginGL())
    {
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
    }
    GUIEndGL();
    GUIRefresh();
    return true;
  }

  //: Handle button press.
  bool View3DBodyC::MousePress(MouseEventC &me)
  {
    ONDEBUG(cerr << "View3DBodyC::MousePress(), Called. '" << me.HasChanged(0) << " " << me.HasChanged(1) << " " << me.HasChanged(2) <<"' \n");
    ONDEBUG(cerr << "View3DBodyC::MousePress(),         '" << me.IsPressed(0) << " " << me.IsPressed(1) << " " << me.IsPressed(2) <<"' \n");
    //save reference position
    m_lastMousePos = me.At();

    if(me.HasChanged(2))
    {
      ONDEBUG(cerr << "Show menu. \n");
      backMenu.Popup();
    }

    return true;
  }

  //: Handle button release.
  bool View3DBodyC::MouseRelease(MouseEventC &me)
  {
    ONDEBUG(cerr << "View3DBodyC::MouseRelease(), Called.\n");
    return true;
  }

  //: Handle mouse move.
  bool View3DBodyC::MouseMove(MouseEventC &me) {
    //ONDEBUG(cerr << "View3DBodyC::MouseMove(), Called. '" << me.HasChanged(0) << " " << me.HasChanged(1) << " " << me.HasChanged(2) <<"' \n");
    //ONDEBUG(cerr << "View3DBodyC::MouseMove(),         '" << me.IsPressed(0) << " " << me.IsPressed(1) << " " << me.IsPressed(2) <<"' \n");
    //cerr << "View3DBodyC::MouseMove(), Called. \n";

    // Calculate change
    Index2dC change = me.At() - m_lastMousePos;
    //cerr << "change:" << change << endl;

    // Store new position
    m_lastMousePos = me.At();

    // Rotate when button 0 pressed
    if(me.IsPressed(0))
    {
      //cerr << "rotation\n";

      if(change.Row() == 0 && change.Col() == 0)
        return true;

      GUIBeginGL();

      //get viewport parameters
      GLint viewport[4];
      glGetIntegerv(GL_VIEWPORT,viewport);

      //get current modelview matrix
      glMatrixMode(GL_MODELVIEW);
      FMatrixC<4, 4> modelviewMat;
      glGetDoublev(GL_MODELVIEW_MATRIX, &(modelviewMat[0][0]));

      //calculate rotation parameters
      FVectorC<4> a;
      a[0] = change.Row();
      a[1] = change.Col();
      a[2] = 0.;
      a[3] = 0.;
      RealT angle = a.Magnitude() / (double)(viewport[2] + 1) * 180.0;
      //cerr << "angle:" << angle << endl;

      FVectorC<4> b = modelviewMat * a;

      //issue rotation
      glRotatef(angle, b[0], b[1], b[2]);

      // posponded update display
      //Put(DTransform3DC(change.Row(), Vector3dC(1, 0, 0)));
      //Put(DTransform3DC(change.Col(), Vector3dC(0, 1, 0)));
      Refresh();
    }

    // Translate when button 1 pressed
    else if (me.IsPressed(1)) {
      cerr << "translation\n";

      // Calculate individual translations
      // X & Y in GTK coords; hence also Y is inverted
      //m_fXTranslation += (RealT)change.Col() / 100.0;
      //m_fYTranslation -= (RealT)change.Row() / 100.0;

      // Update display
      Refresh();
    }
    return true;
  }

  //: Handle mouse wheel.
  bool View3DBodyC::MouseWheel(GdkEvent *event)
  {
    ONDEBUG(cerr << "View3DBodyC::MouseWheel, Called.\n");
    GdkEventScroll &scrollEvent = (GdkEventScroll &) *event;
    bool shiftKey = (scrollEvent.state & GDK_SHIFT_MASK) != 0;
    //bool ctrlKey  = (scrollEvent.state & GDK_CONTROL_MASK) != 0;
    //cerr << "shift:" << shiftKey << "   ctrl:" << ctrlKey << endl;

    switch(scrollEvent.direction)
    {
    case GDK_SCROLL_UP:
    case GDK_SCROLL_LEFT:
      //cerr << "up\n";
      if(!shiftKey)
        m_sceneExtent *= 1.2; //change zoom
      else
        m_viewPoint = m_viewPoint / 1.2;
      GUIAdjustView();
      GUIRefresh();
      break;
    case GDK_SCROLL_DOWN:
    case GDK_SCROLL_RIGHT:
      //cerr << "down\n";
      if(!shiftKey)
        m_sceneExtent /= 1.2; //change zoom
      else
        m_viewPoint = m_viewPoint * 1.2;
      GUIAdjustView();
      GUIRefresh();
      break;
    }
    //cout << "vp:" << m_viewPoint << endl;

    return true;
  }

  //: Handle configure event
  bool View3DBodyC::CBConfigureEvent(GdkEvent *event)
  {
    if(GUIBeginGL())
    {
      ONDEBUG(cerr << "Reshape. " << widget->allocation.width << " " << widget->allocation.height << "\n");
      glViewport(0, 0, widget->allocation.width, widget->allocation.height);

      //CalcViewParams(m_bAutoFit);
      GUIAdjustView();
      //FMatrixC<4, 4> projectionMat;
      //glGetDoublev(GL_PROJECTION_MATRIX, &(projectionMat[0][0]));
      //cerr << "pMat:\n" << projectionMat << endl;
    }
    GUIEndGL();
    return true;
  }

  //: Refresh display.
  bool View3DBodyC::GUIRefresh()
  {
    if(!initDone)
    {
      ONDEBUG(cerr << "View3DBodyC::GUIRefresh(), Called. Returning" << initDone << "\n");
      return false;
    }

    ONDEBUG(cerr << "View3DBodyC::GUIRefresh(), Called. " << ((void *) widget) << "\n");

    GUIClearBuffers();
    // Render scene
    {
      RWLockHoldC lockHold(viewLock, RWLOCK_READONLY);
      if(scene.IsValid())
      {
        //shift origin to scene centre
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated(-m_sceneCenter.X(), -m_sceneCenter.Y(), -m_sceneCenter.Z());

        Canvas3DC my(*this);
        scene.GUIRender(my);
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
      }
    }

    // show scene
    GUISwapBuffers();

    // Finished
    return true;
  }

  //: Refresh display. (Thread safe postponded refresh)
  bool View3DBodyC::Refresh()
  {
    View3DC my(*this);
    Manager.Queue(Trigger(my, &View3DC::GUIRefresh));
    return true;
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

  void View3DBodyC::GUISetCullMode()
  {
    ONDEBUG(cerr << "View3DBodyC::SetCullMode(), Called. \n");

    GUIBeginGL();
    if(m_bFront) {
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
    //cerr << "Culling:" << (glIsEnabled(GL_CULL_FACE) == GL_TRUE ? "enabled" : "disabled") << endl;
    //GLint cullMode;
    //glGetIntegerv(GL_CULL_FACE_MODE, &cullMode);
    //cerr << "mode:" << cullMode << endl;
  }

  void View3DBodyC::CalcViewParams(bool AutoExtent)
  {
    if(AutoExtent)
      m_sceneExtent = scene.GUIExtent() * 1.1;
    m_sceneCenter = scene.GUICenter();
    //cerr << "scene extent:" << m_sceneExtent << endl;
  }
}
