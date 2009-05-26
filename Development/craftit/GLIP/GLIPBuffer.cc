
#include "Ravl/Image/GLIPBuffer.hh"
#include <GL/glx.h>

namespace RavlN { namespace ImageN {
  using namespace RavlImageN;
  
  //! Create a new processing buffer.
  // @param bitDepth  number of bits we want.
  // @param components Number of components in the buffer, 1 to 4
  // @param isFloat Do we want to store floating point numbers ?
  
  GLIPBufferC::GLIPBufferC(GLIPContextC &context,
                           UIntT rows,UIntT cols,
                           UIntT bitSize,
                           UIntT components,
                           bool isFloat,
                           UIntT depthBits
                           ) 
    : m_bufferId(0),
      m_glxContext(0),
      m_rows(rows),
      m_cols(cols)
  {
    
    m_display = context.XDisplay();
    
    int elements;
    int al[64];
    int n = 0;
    al[n++] = GLX_DOUBLEBUFFER;         al[n++] = false;
    al[n++] = GLX_DRAWABLE_TYPE;        al[n++] = GLX_PBUFFER_BIT;
    al[n++] = GLX_STENCIL_SIZE;         al[n++] = 0;
    
    if(isFloat) {
#ifdef GLX_FLOAT_COMPONENTS_NV
      al[n++] = GLX_FLOAT_COMPONENTS_NV;  al[n++] = true;
#else
      cerr << "WARNING: Don't know how to flag float components. \n";
      RavlAssert(0);
      // Any alternatives ?
#endif
    } else {
      al[n++] = GLX_RENDER_TYPE;          al[n++] = GLX_RGBA_BIT;
    }
    
    // We always have at least 1 channel.
    al[n++] = GLX_RED_SIZE;    al[n++] = bitSize; 
    al[n++] = GLX_GREEN_SIZE;  al[n++] = components > 1 ? bitSize : 0;
    al[n++] = GLX_BLUE_SIZE;   al[n++] = components > 2 ? bitSize : 0;
    al[n++] = GLX_ALPHA_SIZE;  al[n++] = components > 3 ? bitSize : 0;
    al[n++] = GLX_DEPTH_SIZE;  al[n++] = depthBits;
    al[n++] = None;
    
    GLXFBConfig *configs = glXChooseFBConfig(m_display, 0,al, &elements);
    if(configs == 0 || elements == 0) {
      cerr << "GLIPBufferC::GLIPBufferC, BitSize=" << bitSize << " Components=" << components << " Float=" << isFloat << "\n";
      cerr << "GLIPBufferC::GLIPBufferC, No suitable buffer type. Elements=" << elements << " \n";
      throw ExceptionOperationFailedC("Failed to create pbuffer.");
    }

#if 0
    // Dump some info about our choice of buffers.
    cerr << "GLIPBufferC::GLIPBufferC, BitSize=" << bitSize << " Components=" << components << " Float=" << isFloat << "\n";
    cerr << "Configs:\n";
    for(int i = 0;i < elements;i++) {
      IntT fbid=-1,redSize=-1,greenSize=-1,blueSize=-1,alphaSize=-1,depthSize=-1;
      glXGetFBConfigAttrib(m_display,configs[i], GLX_FBCONFIG_ID, &fbid);
      glXGetFBConfigAttrib(m_display,configs[i], GLX_RED_SIZE, &redSize);
      glXGetFBConfigAttrib(m_display,configs[i], GLX_GREEN_SIZE, &greenSize);
      glXGetFBConfigAttrib(m_display,configs[i], GLX_BLUE_SIZE, &blueSize);
      glXGetFBConfigAttrib(m_display,configs[i], GLX_ALPHA_SIZE, &alphaSize);
      glXGetFBConfigAttrib(m_display,configs[i], GLX_DEPTH_SIZE, &depthSize);
      
      cerr << "Visual " <<  (UIntT) fbid << " : " << redSize << " " << greenSize << " " << blueSize << " " << alphaSize << " " << depthSize <<"\n";
    }
#endif
    
    n = 0;
    al[n++] = GLX_PBUFFER_WIDTH;      al[n++] = cols;
    al[n++] = GLX_PBUFFER_HEIGHT;     al[n++] = rows;
    al[n++] = GLX_PRESERVED_CONTENTS; al[n++] = 1;
    al[n++] = None;
    m_glxContext = context.GetGLXContext(*configs);
    if(m_glxContext == 0) {
      cerr << "GLIPBufferC::GLIPBufferC, Failed to create approriate context. \n";
      throw ExceptionOperationFailedC("Failed to create pbuffer.");       
    }

    m_bufferId = glXCreatePbuffer(m_display, *configs,al);
    if(m_bufferId == 0) {
      cerr << "GLIPBufferC::GLIPBufferC, Failed to create pbuffer. \n";
      throw ExceptionOperationFailedC("Failed to create pbuffer.");      
    }
    
    XFree(configs); 
  }
  
  
  //! Destructor
  
  GLIPBufferC::~GLIPBufferC() {
    if(m_bufferId > 0) {
      Display *display = glXGetCurrentDisplay();
      glXDestroyPbuffer(display, m_bufferId);
    }
  }
  
  //! Make this the current drawing target.
  
  void GLIPBufferC::MakeCurrent() {
    
    glXMakeCurrent(m_display,m_bufferId,m_glxContext);
  }


}}

