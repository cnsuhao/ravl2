#ifndef RAVLGLIP_CONTEXT_HEADER
#define RAVLGLIP_CONTEXT_HEADER 1

#include "Ravl/String.hh"
#include "Ravl/RCBodyV.hh"
#include "Ravl/SmartPtr.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Hash.hh"
#include "Ravl/HashIter.hh"
#include <Cg/cg.h>
#include <GL/gl.h>

extern "C" {
  typedef struct __GLXcontextRec *GLXContext;
  typedef struct _CGcontext *CGcontext;
  typedef struct __GLXFBConfigRec *GLXFBConfig;
  typedef struct _XDisplay Display;
}

namespace RavlN { namespace ImageN {
  using namespace RavlImageN;
  
  //! userlevel=Develop
  //: GLIP Processing context.
  
  class GLIPContextC 
    : public RCBodyVC 
  {
  public:
    GLIPContextC(const StringC &displayName);
    //: Create a connection to a X server.
    
    GLIPContextC(int *pargc,char **argv);
    //: Create a connection based on program arguments.
    
    ~GLIPContextC();
    //: Destructor

    bool IsOpen() const;
    //: Is this a valid context ?
    
    bool MakeCurrent();
    //: Make this context current for this thread.
    
    const StringC &DisplayName() const
    { return m_displayName; }
    //: Access display name
    
    CGcontext CgContext()
    { return m_cgContext; }
    //: Access CG context.
    
    bool CheckCgError();
    //: Check for a CG error.
    // Will print message to cerr and return false if one is detected.
    
    //! Best fragment shader profile
    CGprofile FPProfile() const
    { return m_cgFPProfile; }
    
    //! Best vertex program profile
    CGprofile VPProfile() const
    { return  m_cgVPProfile; } 
    
    //! Make default context.
    void MakeDefaultDrawableCurrent();
    
    //! Obtain a context matching the given config.
    GLXContext GetGLXContext(const GLXFBConfig &config);
    
    //! Get current X display
    Display *XDisplay()
    { return m_display; }
    
    //! Handle to context.
    typedef SmartPtrC<GLIPContextC> RefT;
  protected:
    bool Open(const StringC &name);
    //: Open a connection
    
    void Init();
    //: Initialise the context.
    
    StringC m_displayName; // Display name
    Display *m_display;
    GLXContext m_glxContext; 
    CGcontext m_cgContext; // Current CG context.
    CGprofile m_cgFPProfile; // Best fragment shader profile
    CGprofile m_cgVPProfile; // Best vertex program profile
    
    long int m_defaultContextId; // Default context
    
    HashC<int,GLXContext> m_visualId2context;
  };
  
  //! Create a OpenGL texture from an image.
  // interpolationType=GL_LINEAR,GL_NEAREST...
  GLuint GLIPCreateTexture(ImageC<ByteRGBValueC> &rgbImage,GLint interpolationType); 
  
  
}}

#endif
