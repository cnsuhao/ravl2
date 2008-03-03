
#include "Ravl/GUI/GLContext.hh"

//#include "Ravl/StdError.hh"
#ifndef VISUAL_CPP
#include "Ravl/GUI/gdkgl.h"
#include "Ravl/GUI/gtkglarea.h"
#endif
#include "Ravl/GUI/Manager.hh"
#include "Ravl/FMatrix.hh"

#include <gtk/gtk.h>

#ifdef VISUAL_CPP
#include <GL/glu.h>
#include <gtk/gtkgl.h>
#include <gdk/gdkgl.h>
#else
#include <GL/glx.h>
#endif

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {

  //: Constructor.
  
  GLContextBodyC::GLContextBodyC(GtkWidget *widget) 
    : m_widget(widget)
  {
    if(m_widget != 0)
      g_object_ref(m_widget);
  }
  
  //: Destructor.
  
  GLContextBodyC::~GLContextBodyC() {
    if(m_widget != 0)
      g_object_unref(m_widget);
  }
  
  //: Do we have a valid context.
  
  bool GLContextBodyC::IsReady() const {
    return (m_widget != 0);
  }
  
  //: Switch to GL context.
  
  bool GLContextBodyC::Begin() {
    if(m_widget == 0) {
      ONDEBUG(cerr << "GLContextBodyC::Begin(), ERROR: Called with invalid widget. \n");
      return false;
    }
#ifdef VISUAL_CPP
    GdkGLContext *glcontext = gtk_widget_get_gl_context (m_widget);
    GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (m_widget);
    if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
      return FALSE;
#else
    if (!gtk_gl_area_make_current(GTK_GL_AREA(m_widget))) {
      ONDEBUG(cerr << "WARNING: Canvas3DBodyC::BeginGL(), Failed. \n");
      return false;
    }
#endif
    return true;
  }
  
  //: Flag that we're finished with the context.
  
  void GLContextBodyC::End() {
#ifdef VISUAL_CPP
    GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);
    gdk_gl_drawable_gl_end (gldrawable);
#endif
    return ;
  }

  //: Thread safe freeing of textures.
  
  bool GLContextBodyC::FreeTextures(const RavlN::SArray1dC<GLuint> &textureIds) {
    if(!Manager.IsGUIThread()) {
      Manager.Queue(Trigger(GLContextC(*this),&GLContextC::GUIFreeTextures,textureIds));
    } else {
      return GUIFreeTextures(textureIds); 
    }
    return true;
  }
  
  //: Thread 
  
  bool GLContextBodyC::GUIFreeTextures(RavlN::SArray1dC<GLuint> textureIds) {
    //std::cerr << "Freeing " << textureIds.Size() << " textures\n";
    glDeleteTextures(textureIds.Size(), &(textureIds[0]));
    return true;
  }

  
}
