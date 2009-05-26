
#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GL/gl.h>
#include <GL/glext.h>
#include <Cg/cgGL.h>
#include <GL/glut.h>

#include "Ravl/Image/GLIPContext.hh"
#include <GL/glut.h>
#include <Cg/cgGL.h>
#include <GL/glx.h>

namespace RavlN { namespace ImageN {
  
  //: Create a connection to a X server.
  
  GLIPContextC::GLIPContextC(const StringC &displayName)
    : m_displayName(displayName),
      m_display(0),
      m_cgContext(0),
      m_defaultContextId(0)
  {
    Open(displayName);
  }

  //: Create a connection based on program arguments.
  
  GLIPContextC::GLIPContextC(int *pargc,char **argv) 
    : m_cgContext(0),
      m_defaultContextId(0)
  { 
#if 1
    glutInit(pargc,argv);
    Init();
#else
    //Open(":0.0");
#endif
  }
  
  //: Open a connection
  
  bool GLIPContextC::Open(const StringC &name) {
    
    Init();
    return true;
  }
  
  //: Destructor
  
  GLIPContextC::~GLIPContextC()
  {
    for(HashIterC<int,GLXContext> it(m_visualId2context);it;it++)
      glXDestroyContext(m_display,it.Data());
    
    if(m_cgContext != 0)
      cgDestroyContext(m_cgContext);
  }
  
  //: Check for a CG error.
  // Will print message to cerr and return false if one is detected.
  
  bool GLIPContextC::CheckCgError() {
    CGerror err = cgGetError();
    
    if (err == CG_NO_ERROR)
      return true;
    cerr  << cgGetErrorString(err) << "\n";
    return false;
  }
  
  
  static void myCcgErrorCallback(void) {
    CGerror err = cgGetError();
    if (err == CG_NO_ERROR)
      return ;
    cerr << cgGetErrorString(err) << "\n";
  }
  
  //: Initialise the context.
  
  void GLIPContextC::Init() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //glutInitWindowSize(512,512);
    glutInitWindowSize(64,64);
#if 1
    glutCreateWindow("Test");
#endif
    m_display = glXGetCurrentDisplay();
    m_glxContext = glXGetCurrentContext();
    
    cgSetErrorCallback(&myCcgErrorCallback);
    
    // Setup vertex profile
    
    if (cgGLIsProfileSupported(CG_PROFILE_VP40)) {
      cerr << "CG_PROFILE_VP40, Supported. " << CG_PROFILE_VP40 << " \n";
      m_cgVPProfile = CG_PROFILE_VP40;
    } else if (cgGLIsProfileSupported(CG_PROFILE_ARBVP1))
      m_cgVPProfile = CG_PROFILE_ARBVP1;
    else if (cgGLIsProfileSupported(CG_PROFILE_VP30))
      m_cgVPProfile = CG_PROFILE_VP30;
    else {
      cerr << "GLIPContextC::Init, No vertex profile found. \n";
      //throw ExceptionOperationFailedC("Can't find suitable vertex profile. ");
    }
    
    
    // Setup fragment profile
    
    if (cgGLIsProfileSupported(CG_PROFILE_FP40)) {
      cerr << "CG_PROFILE_FP40, Supported. " << CG_PROFILE_FP40 << " \n";
      m_cgFPProfile = CG_PROFILE_FP40;
    } else if (cgGLIsProfileSupported(CG_PROFILE_ARBFP1))
      m_cgFPProfile = CG_PROFILE_ARBFP1;
    else if (cgGLIsProfileSupported(CG_PROFILE_FP30))
      m_cgFPProfile = CG_PROFILE_FP30;
    else {
      cerr << "GLIPContextC::Init, No fragment profile found. \n";
      //throw ExceptionOperationFailedC("Can't find suitable fragment profile. ");
    }
    
    m_cgContext = cgCreateContext();
    CheckCgError(); // If failure then throw ex

    m_defaultContextId = glXGetCurrentDrawable();
  }
  
  //: Is this a valid context ?

  bool GLIPContextC::IsOpen() const {
    
    return true;
  }
  
  //: Make this context current for this thread.

  bool GLIPContextC::MakeCurrent() {
    return false;
  }
  
  
  //! Make default context.
  
  void GLIPContextC::MakeDefaultDrawableCurrent() {
    if(m_defaultContextId == 0) {
      cerr << "GLIPContextC::MakeDefaultDrawableCurrent, WARNING: No default drawable defined. \n";
      return ;
    }
    glXMakeCurrent(m_display,m_defaultContextId,m_glxContext);
  }
  
  //! Obtain a context matching the given config.
  
  GLXContext GLIPContextC::GetGLXContext(const GLXFBConfig &config) {
    int fbid;
    
    // Get the id of the requested config.
    glXGetFBConfigAttrib(m_display,config, GLX_FBCONFIG_ID, &fbid);
    
    // Have we created it already ?
    GLXContext ret = 0;
    if(!m_visualId2context.Lookup(fbid,ret)) {
      ret = glXCreateNewContext(m_display,config,GLX_RGBA_TYPE,m_glxContext,true);
      if(ret == 0) {
        cerr << "GLIPContextC::GetGLXContext, Failed. \n";
        return 0;
      }
      m_visualId2context[fbid] = ret;
    }
    
    return ret;
  }

  
  // ---------------------------------------------------------------------------------------------------
  
  //! Create a OpenGL texture from an image.
  // interpolationType=GL_LINEAR,GL_NEAREST...
  
  GLuint GLIPCreateTexture(ImageC<ByteRGBValueC> &rgbImage,GLint interpolationType) {
    GLuint ret;
    glGenTextures(1,&ret);
    glBindTexture(GL_TEXTURE_2D,ret);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,rgbImage.Cols(),rgbImage.Rows(),0,GL_RGB,GL_UNSIGNED_BYTE,&(rgbImage[rgbImage.Frame().Origin()]));
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,interpolationType);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,interpolationType);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    return ret;
  }

  
}}
