#ifndef RAVLGLIP_PROGRAM_HEADER
#define RAVLGLIP_PROGRAM_HEADER 1

#include "Ravl/Image/GLIPContext.hh"

namespace RavlN { namespace ImageN {
  using namespace RavlN;
  
  enum GLIPProfileTypeT 
    { GLIPPROG_FRAGMENT,
      GLIPPROG_VERTEX,
    };
  
  //: GLIP Program.

  class GLIPProgramC
    : public RCBodyVC
  {
  public:
    GLIPProgramC(const GLIPContextC &context,GLIPProfileTypeT progType);
    //: Construct program from file.
    
    GLIPProgramC(const GLIPContextC &context,GLIPProfileTypeT progType,const StringC &filename);
    //: Construct program from file.
    
    ~GLIPProgramC();
    //: Destructor.
    
    bool LoadFile(const StringC &filename);
    //: Load program from file.
    
    bool Bind();
    //: Bind program into current state.
    // NOTE: There can be only 1 vertex program and 1 shader program loaded at a time.
    
    bool Enable();
    //: Enable profile associated with the program.
    
    bool Disable();
    //: Disable profile associated with the program.

    CGprogram CgProgram() const
    { return m_program; }
    //: Access program handle.
    
    //! Reference to program.
    typedef SmartPtrC<GLIPProgramC> RefT;
  protected:
    
    GLIPContextC::RefT m_context;
    CGprogram m_program;
    GLIPProfileTypeT m_programType;
  };
  
  
}}




#endif
