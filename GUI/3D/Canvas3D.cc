// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI3D

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

  /* When glarea widget size changes, viewport size is set to match the new size */
  static gint reshape(GtkWidget *widget, GdkEventConfigure *event) {
    /* OpenGL functions can be called only if make_current returns true */
    if (gtk_gl_area_make_current(GTK_GL_AREA(widget))) {
      //cerr << "Reshape. " << widget->allocation.width << " " << widget->allocation.height << "\n";
      glViewport(0,0, widget->allocation.width, widget->allocation.height);
    }
    return true;
  }
  
  //: Initalise GL info
  
  bool Canvas3DBodyC::InitGL() { 
    ONDEBUG(cerr << "Canvas3DBodyC::InitGL(), GL Avaliable ? \n");
    bool ret = gdk_gl_query(); 
    if(!ret) {
#if defined(__sgi__)
      cerr << "No native OpenGL not supported on this display. \n";
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
  
  Canvas3DBodyC::Canvas3DBodyC(int x,int y,int *nglattrlist)
    : glattrlist(nglattrlist),
      sx(x),
      sy(y),
      m_eRenderMode(C3D_SMOOTH),
      m_bTexture(false),
      m_bLighting(true)
  { 
    ONDEBUG(cerr << "Canvas3DBodyC::Canvas3DBodyC(), Called.\n");
    if(!InitGL())
#if 0
    throw ExceptionC("OpenGL not supported on display. \n"); 
#else
    cerr << "WARNING: OpenGL not supported on this X server. \n";
#endif
  }

  //: Create the widget.
  
  bool Canvas3DBodyC::Create() {
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
    gtk_drawing_area_size (GTK_DRAWING_AREA (widget), sx, sy); 
    /* When window is resized viewport needs to be resized also. */
    gtk_signal_connect(GTK_OBJECT(widget), "configure_event",
		       GTK_SIGNAL_FUNC(reshape), NULL);
    gtk_quit_add_destroy(1, GTK_OBJECT(widget));
    
    ConnectSignals();
    
    return true;
  }
  
  //: swap buffers.
  
  bool Canvas3DBodyC::SwapBuffers() {
    gtk_gl_area_swapbuffers(GTK_GL_AREA(widget));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
  
  //: Put render instructon into pipe.
  bool Canvas3DBodyC::Put(const DObject3DC &obj) {
    Manager.Queue(Trigger(Canvas3DC(*this),&Canvas3DC::ProcessReq,obj)); 
    return true;
  }
  
  //: Enable or disable lighting
  //: Put End Of Stream marker.
  void Canvas3DBodyC::SetLightingMode(bool& bLighting) {
    m_bLighting = bLighting; 
    Put(DOpenGLC(CallMethod0C<Canvas3DC>(Canvas3DC(*this),&Canvas3DC::DoLighting)));
  }
  
  
  //: Call before using any GL commands.
  
  bool Canvas3DBodyC::BeginGL() {
    if(widget == 0) {
      cerr << "Canvas3DBodyC::BeginGL(), ERROR: Called with invalid widget. \n";
      return false;
    }
    if (!gtk_gl_area_make_current(GTK_GL_AREA(widget))) {
      cerr << "WARNING: Canvas3DBodyC::BeginGL(), Failed. \n";
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


