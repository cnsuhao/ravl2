
#include "Ravl/Image/GLIPProgram.hh"
#include <Cg/cgGL.h>

namespace RavlN { namespace ImageN {

  //: Construct program from file.
  
  GLIPProgramC::GLIPProgramC(const GLIPContextC &context,GLIPProfileTypeT progType) 
    : m_context(&context),
      m_program(0),
      m_programType(progType)
  {}

  //: Construct program from file.
  
  GLIPProgramC::GLIPProgramC(const GLIPContextC &context,GLIPProfileTypeT progType,const StringC &filename)
    : m_context(&context),
      m_program(0),
      m_programType(progType)
  {
    LoadFile(filename);
    Bind();
  }
  
  //: Destructor.
  
  GLIPProgramC::~GLIPProgramC()
  {
    if(m_program != 0)
      cgDestroyProgram(m_program);
  }
  
  //: Enable profile associated with the program.
  
  bool GLIPProgramC::Enable() {
    // Enable the profile.
    CGprofile profile = m_context->FPProfile();
    switch(m_programType) {
    case GLIPPROG_FRAGMENT: profile = m_context->FPProfile(); break;
    case GLIPPROG_VERTEX: profile = m_context->VPProfile(); break;
    }
    cgGLEnableProfile(profile);
    return m_context->CheckCgError();
  }
  
  //: Disable profile associated with the program.
  
  bool GLIPProgramC::Disable() {
    // Enable the profile.
    CGprofile profile = m_context->FPProfile();
    switch(m_programType) {
    case GLIPPROG_FRAGMENT: profile = m_context->FPProfile(); break;
    case GLIPPROG_VERTEX: profile = m_context->VPProfile(); break;
    }
    cgGLDisableProfile(profile);    
    return m_context->CheckCgError();
  }
  
  //: Bind program into current state.
  // NOTE: There can be only 1 vertex program and 1 shader program loaded at a time.
  
  bool GLIPProgramC::Bind() {
    
    // Need to load the program ?
    if(!cgGLIsProgramLoaded(m_program)) {
      cgGLLoadProgram(m_program);
      if(!m_context->CheckCgError())
        return false; // Failed to load program.
    }
    
    // Bind the program.
    cgGLBindProgram(m_program);
    
    return m_context->CheckCgError();
  }
  
  
  //: Load program from file.
  
  bool GLIPProgramC::LoadFile(const StringC &filename) {
    
    CGprofile profile = m_context->FPProfile();
    switch(m_programType) {
    case GLIPPROG_FRAGMENT: profile = m_context->FPProfile(); cerr << "Loading frag prog '" << filename << "' \n"; break;
    case GLIPPROG_VERTEX: profile = m_context->VPProfile(); cerr << "Loading vert prog '" << filename << "' \n"; break;
    }
    cerr << "Program profile = " << profile << " Program='" << filename << "'\n";
    m_program =  cgCreateProgramFromFile(m_context->CgContext(), 
                                         CG_SOURCE,
                                         filename.chars(),
                                         profile,
                                         "main",
                                         0);
    
    return m_context->CheckCgError();
  }
  
}}
