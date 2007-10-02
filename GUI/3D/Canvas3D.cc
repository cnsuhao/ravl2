// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI3D
//! file="Ravl/GUI/3D/Canvas3D.cc"

#include "Ravl/GUI/Canvas3D.hh"
//#include "Ravl/StdError.hh"
#include "Ravl/GUI/gdkgl.h"
#include "Ravl/GUI/gtkglarea.h"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/FMatrix.hh"

#include <gtk/gtk.h>
#include <GL/gl.h>
#include <GL/glx.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

static gint defaultAttrlist[] = {
      GDK_GL_RGBA,
      GDK_GL_DOUBLEBUFFER,
      GDK_GL_DEPTH_SIZE, 16,
      GDK_GL_NONE
    };

namespace RavlGUIN
{
  //: Create a 3D canvas
  Canvas3DBodyC::Canvas3DBodyC(int x, int y, int *nglattrlist,
                               bool autoConfigure)
    : glattrlist(nglattrlist),
      sx(x),
      sy(y),
      m_eRenderMode(C3D_SMOOTH),
      m_bTexture(false),
      m_bLighting(true),
      m_autoConfigure(autoConfigure)
  {
    ONDEBUG(cerr << "Canvas3DBodyC::Canvas3DBodyC(), Called.\n");
  }

  //: Initalise GL info
  bool Canvas3DBodyC::GUIInitGL() {
    ONDEBUG(cerr << "Canvas3DBodyC::GUIInitGL(), GL Avaliable ? \n");
    bool ret = gdk_gl_query();
    if(!ret) {
#if defined(__sgi__)
      cerr << "No native OpenGL supported on this display. \n";
      cerr << "You could try: 'setenv LD_LIBRARY_PATH /opt/PDmesa/Mesa-3.1/lib' \n";
      cerr << "Then restarting your program. \n";
      RavlAssertMsg(0,"OpenGL not supported. ");
#else
      //cerr << "No native OpenGL not supported on this display. \n";
#endif
    }
    ONDEBUG(cerr << "Canvas3DBodyC::GUIInitGL(), Found " << ret << " \n");
    return ret;
  }

  //: Create with a widget supplied from elsewhere.
  bool Canvas3DBodyC::Create(GtkWidget *Parent)
  {
    // Initalise opengl
    if(!GUIInitGL())
#if 0
      throw ExceptionC("OpenGL not supported on display. \n");
#else
      cerr << "WARNING: OpenGL not supported on this X server. \n";
#endif
    ONDEBUG(cerr << "Canvas3DBodyC::Create(GtkWidget *), Setting up canvas. \n");

    if(glattrlist == 0)
      glattrlist = defaultAttrlist; // Use default.

    widget = gtk_gl_area_new(glattrlist);
    if(widget == 0) {
      cerr << "Canvas3DBodyC::Create(GtkWidget *) ERROR: Widget create failed. \n";
      return false;
    }

    if(Parent != NULL)
    {
      // The widget supplied is unlikely to be the correct type,
      // so we assume its a container into which we'll create
      // the graphics context.

      // Add in child widget...
      gtk_container_add (GTK_CONTAINER (Parent), widget);
      //gtk_widget_show (widget);
    }
    else
    {
      // Setup drawing area.
      ONDEBUG(cerr << "Canvas3DBodyC::Create(GtkWidget *), Setting draw area size to " << sx << " " << sy <<". \n");
      gtk_drawing_area_size (GTK_DRAWING_AREA (widget), sx, sy);
    }

    // When window is resized viewport needs to be resized also.
    if(m_autoConfigure)
      ConnectRef(Signal("configure_event"), *this,
                 &Canvas3DBodyC::CBConfigureEvent);

    gtk_quit_add_destroy(1, GTK_OBJECT(widget));

    ONDEBUG(cerr << "Canvas3DBodyC::Create(GtkWidget *), Connect Signals. \n");
    ConnectSignals();
    ONDEBUG(cerr << "Canvas3DBodyC::Create(GtkWidget *), Complete. \n");

    return true;
  }

  //: Call before using any GL commands.
  bool Canvas3DBodyC::GUIBeginGL()
  {
    if(widget == 0) {
      ONDEBUG(cerr << "Canvas3DBodyC::BeginGL(), ERROR: Called with invalid widget. \n");
      return false;
    }
    if (!gtk_gl_area_make_current(GTK_GL_AREA(widget))) {
      ONDEBUG(cerr << "WARNING: Canvas3DBodyC::BeginGL(), Failed. \n");
      return false;
    }
    return true;
  }

  //: Call after finished with GL
  bool Canvas3DBodyC::GUIEndGL()
  {
    //glFinish();
    //cerr << "WARNING: Canvas3DBodyC::BeginGL(), Failed. \n";
    return true;
  }

  //: swap buffers.
  bool Canvas3DBodyC::GUISwapBuffers()
  {
    gtk_gl_area_swapbuffers(GTK_GL_AREA(widget));
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();
    return true;
  }

  //: clear buffers (make sure you called GUIBeginGL before)
  bool Canvas3DBodyC::GUIClearBuffers()
  {
    GLenum whichBuffers(GL_COLOR_BUFFER_BIT);
    if(glIsEnabled(GL_DEPTH_TEST) )
      whichBuffers |= (GL_DEPTH_BUFFER_BIT);
    glClear(whichBuffers);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    return true;
  }

  //: Process OpenGL requests.
  bool Canvas3DBodyC::GUIProcessReq(DObject3DC &obj) {
    ONDEBUG(cerr << "Canvas3DBodyC::GUIProcessReq(), Called. \n");
    if(!GUIBeginGL()) {
      cerr << "Canvas3DBodyC::GUIProcessReq(), Failed to BeginGL(). \n";
      return false;
    }
    Canvas3DC c(*this);
    if(!obj.IsValid())
     cerr << "Canvas3DBodyC::GUIProcessReq(), Given invalid object. \n";
    else
      obj.GUIRenderDL(c);
    GUIEndGL();
    return true;
  }

  //: Put render instructon into pipe.
  bool Canvas3DBodyC::Put(const DObject3DC &obj) {
    Manager.Queue(Trigger(Canvas3DC(*this), &Canvas3DC::GUIProcessReq, obj));
    return true;
  }

  //: Handle configure event
  bool Canvas3DBodyC::CBConfigureEvent(GdkEvent *event) {
    if(GUIBeginGL())
    {
      ONDEBUG(cerr << "Reshape. " << widget->allocation.width << " " << widget->allocation.height << "\n");
      glViewport(0, 0, widget->allocation.width, widget->allocation.height);

      //FMatrixC<4, 4> projectionMat;
      //glGetDoublev(GL_PROJECTION_MATRIX, &(projectionMat[0][0]));
      //cerr << "pMat:\n" << projectionMat << endl;
    }
    GUIEndGL();
    return true;
  }

  //: Enable or disable lighting
  //: Put End Of Stream marker.
  bool Canvas3DBodyC::SetLightingMode(bool& bLighting) {
    m_bLighting = bLighting;
    Put(DOpenGLC(CallMethod0C<Canvas3DC, bool>(Canvas3DC(*this), &Canvas3DC::GUIDoLighting)));
    return true;
  }

} // end of namespace


