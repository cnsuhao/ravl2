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

#include <gtk/gtk.h>
#include <GL/gl.h>
#include <GL/glx.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  //: Initalise GL info
  
  bool Canvas3DBodyC::InitGL() { 
    ONDEBUG(cerr << "Canvas3DBodyC::InitGL(), GL Avaliable ? \n");
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
    ONDEBUG(cerr << "Canvas3DBodyC::InitGL(), Found " << ret << " \n");
    return ret;
  }
  
  //: Don't do this.
  
  Canvas3DBodyC::Canvas3DBodyC(const Canvas3DBodyC &) {
    RavlAssert(0);
  }
  
  //: Create a 3D canvas
  
  Canvas3DBodyC::Canvas3DBodyC(int x,int y,int *nglattrlist,bool autoConfigure)
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

  //: Create the widget.
  
  bool Canvas3DBodyC::Create() {
    if(!InitGL())
#if 0
      throw ExceptionC("OpenGL not supported on display. \n"); 
#else
    cerr << "WARNING: OpenGL not supported on this X server. \n";
#endif
    ONDEBUG(cerr << "Canvas3DBodyC::Create(), Setting up canvas. \n");
    
    gint attrlist[] = {
      GDK_GL_RGBA,
      GDK_GL_DOUBLEBUFFER,
      GDK_GL_DEPTH_SIZE, 16,
      GDK_GL_NONE
    };
    if(glattrlist == 0)
      glattrlist = attrlist; // Use default.
    
    widget = gtk_gl_area_new(glattrlist);
    if(widget == 0) {
      cerr << "Canvas3DBodyC::Create() ERROR: Widget create failed. \n";
      return false;
    }
    ONDEBUG(cerr << "Canvas3DBodyC::Create(), Setting draw area size to " << sx << " " << sy <<". \n");
    gtk_drawing_area_size (GTK_DRAWING_AREA (widget), sx, sy); 
    
    // When window is resized viewport needs to be resized also. 
    if(m_autoConfigure)
      ConnectRef(Signal("configure_event"),*this,&Canvas3DBodyC::CBConfigureEvent);
    
    gtk_quit_add_destroy(1, GTK_OBJECT(widget));
    
    ONDEBUG(cerr << "Canvas3DBodyC::Create(), Connect Signals. \n");
    
    ConnectSignals();

    ONDEBUG(cerr << "Canvas3DBodyC::Create(), Complete. \n");
    return true;
  }

  //: Create with a widget supplied from elsewhere.
  
  bool Canvas3DBodyC::Create(GtkWidget *owidget) {
    // The widget supplied is unlikely to be the correct type,
    // so we assume its a container into which we'll create
    // the graphics context.
    
    // Initalise opengl
    if(!InitGL())
      throw ExceptionC("OpenGL not supported on display. \n"); 
    ONDEBUG(cerr << "Canvas3DBodyC::Create(GtkWidget *), Setting up canvas. \n");
    
    gint attrlist[] = {
      GDK_GL_RGBA,
      GDK_GL_DOUBLEBUFFER,
      GDK_GL_DEPTH_SIZE, 16,
      GDK_GL_NONE
    };
    if(glattrlist == 0)
      glattrlist = attrlist; // Use default.
    
    widget = gtk_gl_area_new(glattrlist);
    if(widget == 0) {
      cerr << "Canvas3DBodyC::Create(GtkWidget *) ERROR: Widget create failed. \n";
      return false;
    }
    
    // Add in child widget...
    gtk_container_add (GTK_CONTAINER (owidget), widget);
    //gtk_widget_show (widget);
    

    // Setup drawing area.
    ONDEBUG(cerr << "Canvas3DBodyC::Create(GtkWidget *), Setting draw area size to " << sx << " " << sy <<". \n");
    
    
    // When window is resized viewport needs to be resized also.
    if(m_autoConfigure)
      ConnectRef(Signal("configure_event"),*this,&Canvas3DBodyC::CBConfigureEvent);
    
    gtk_quit_add_destroy(1, GTK_OBJECT(widget));
    
    ONDEBUG(cerr << "Canvas3DBodyC::Create(GtkWidget *), Connect Signals. \n");
    
    ConnectSignals();

    ONDEBUG(cerr << "Canvas3DBodyC::Create(GtkWidget *), Complete. \n");
    return true;
    
  }
  
  //: swap buffers.
  
  bool Canvas3DBodyC::SwapBuffers() {
    gtk_gl_area_swapbuffers(GTK_GL_AREA(widget));
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();
    return true;
  }
  
  //: clear buffers 
  bool Canvas3DBodyC::ClearBuffers() {
    
    GLenum whichBuffers(GL_COLOR_BUFFER_BIT) ;
    if ( glIsEnabled (GL_DEPTH_TEST) ) whichBuffers |= (GL_DEPTH_BUFFER_BIT) ;
    glClear( whichBuffers ) ; 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    return true;
  }

  //: Process OpenGL requests.
  
  bool Canvas3DBodyC::ProcessReq(DObject3DC &obj) {
    ONDEBUG(cerr << "Canvas3DBodyC::ProcessReq(), Called. \n");
    if(!BeginGL()) {
      cerr << "Canvas3DBodyC::ProcessReq(), Failed to BeginGL(). \n";
      return false;
    }
    Canvas3DC c(*this);
    if(!obj.IsValid())
     cerr << "Canvas3DBodyC::ProcessReq(), Given invalid object. \n";
    else
      obj.RenderDL(c);
    EndGL();  
    return true;
  }
  
  //: Handle configure event

  bool Canvas3DBodyC::CBConfigureEvent(GdkEvent *event) {
    if (gtk_gl_area_make_current(GTK_GL_AREA(widget))) {
      ONDEBUG(cerr << "Reshape. " << widget->allocation.width << " " << widget->allocation.height << "\n");
      glViewport(0,0, widget->allocation.width, widget->allocation.height);
    }   
    return true;
  }

  //: Put render instructon into pipe.
  bool Canvas3DBodyC::Put(const DObject3DC &obj) {
    Manager.Queue(Trigger(Canvas3DC(*this),&Canvas3DC::ProcessReq,obj)); 
    return true;
  }
  
  //: Enable or disable lighting
  //: Put End Of Stream marker.
  bool Canvas3DBodyC::SetLightingMode(bool& bLighting) {
    m_bLighting = bLighting; 
    Canvas3DC me(*this);
    Put(DOpenGLC(CallMethod0C<Canvas3DC,bool>(me,&Canvas3DC::DoLighting)));
    return true;
  }
  
  
  //: Call before using any GL commands.
  
  bool Canvas3DBodyC::BeginGL() {
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
  
  //: Call aftern finished with GL
  
  bool Canvas3DBodyC::EndGL() {
    //glFinish();
    //cerr << "WARNING: Canvas3DBodyC::BeginGL(), Failed. \n";
    return true;
  }
}


