#ifndef OMNI_IMAGE_GLIPBUFFER_HEADER
#define OMNI_IMAGE_GLIPBUFFER__HEADER 1

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/GLIPContext.hh"

namespace RavlN { namespace ImageN {
  using namespace RavlImageN;
  
  class GLIPBufferC
    : public RCBodyC
  {
  public:
    //! Default constructor, creates an invalid buffer.
    GLIPBufferC()
      : m_bufferId(0)
    {}
    
    //! Create a new processing buffer.
    // @param bitDepth  number of bits we want.
    // @param components Number of components in the buffer, 1 to 4
    // @param isFloat Do we want to store floating point numbers ?
    
    GLIPBufferC(GLIPContextC &context,
                UIntT rows,UIntT cols,
                UIntT bitSize,
                UIntT components,
                bool isFloat = false,
                UIntT depthBits = 0
                );
    
    //! Destructor
    virtual ~GLIPBufferC();
    
    //! Make this the current drawing target.
    void MakeCurrent();

    //! Number of rows.
    UIntT Rows() const
    { return m_rows; }
    
    //! Number of cols.
    UIntT Cols() const
    { return m_cols; }
    
    //! Reference to GLIP buffer.
    typedef SmartPtrC<GLIPBufferC> RefT;
    
  protected:
    typedef unsigned long XID ;
    
    XID m_bufferId;
    GLXContext m_glxContext;
    Display *m_display;
    UIntT m_rows; // Number of rows.
    UIntT m_cols; // Number of cols.
  };
  
}}

#endif
