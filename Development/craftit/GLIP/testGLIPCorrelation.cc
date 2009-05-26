
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glext.h>
#include <Cg/cgGL.h>
#include <GL/glut.h>

#include "Ravl/Image/GLIPContext.hh"
#include "Ravl/Image/GLIPProgram.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Option.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/IO.hh"


using namespace RavlN::ImageN;
using namespace RavlImageN;

GLIPProgramC::RefT progVert;
GLIPProgramC::RefT progFrag;

GLuint sceneTexId;
GLuint patchTexId;

void DrawDisplay(void) {
  cerr << "DrawDisplay, Called. \n";
  progVert->Enable();
  progFrag->Enable();
  
  glClear(GL_COLOR_BUFFER_BIT);  
  //glBindTexture(GL_TEXTURE_2D,sceneTexId);
  
  CGparameter patchTP = cgGetNamedParameter(progFrag->CgProgram(), "patchTexture");
  cgGLSetTextureParameter(patchTP,patchTexId);
  cgGLEnableTextureParameter(patchTP);
  CGparameter sceneTP = cgGetNamedParameter(progFrag->CgProgram(), "sceneTexture");
  cgGLSetTextureParameter(sceneTP,sceneTexId);
  cgGLEnableTextureParameter(sceneTP);
  
  //  cgGLSetParameter2f(cgGetNamedParameter(progFrag->CgProgram(), "patchInc"),1.0/128.0,1.0/128.0);
  cgGLSetParameter2f(cgGetNamedParameter(progFrag->CgProgram(), "patchInc"),0.023,0.023);
  
  glColor3f(0.0,1.0,0.0);
#if 0
#if 0
  glPointSize(1.0);
  glBegin(GL_POINTS);  
  glTexCoord2f(0.0,0.0);  glVertex3f(0.25,0.25,0.0);
  glTexCoord2f(1.0,0.0);  glVertex3f(0.75,0.25,0.0);
  glTexCoord2f(1.0,1.0);  glVertex3f(0.75,0.75,0.0);
  glTexCoord2f(0.0,1.0);  glVertex3f(0.25,0.75,0.0);
  glEnd();
#else
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,0.0);  glVertex3f(0.25,0.25,0.0);
  glTexCoord2f(1.0,0.0);  glVertex3f(0.75,0.25,0.0);
  glTexCoord2f(1.0,1.0);  glVertex3f(0.75,0.75,0.0);
  glTexCoord2f(0.0,1.0);  glVertex3f(0.25,0.75,0.0);
  glEnd();
#endif
#else
  glActiveTexture(GL_TEXTURE0);
  glEnable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE1);
  glEnable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE1);
  glEnable(GL_TEXTURE_2D);
  
  glBegin(GL_POLYGON);
  glMultiTexCoord3f(GL_TEXTURE0,1,0,-0.2);
  glMultiTexCoord3f(GL_TEXTURE1,0,1,-0.2);
  glMultiTexCoord3f(GL_TEXTURE2,0,0,1);
  glVertex3f(0.25,0.25,0.0);
  
  glMultiTexCoord3f(GL_TEXTURE0,1,0,-0.2);
  glMultiTexCoord3f(GL_TEXTURE1,0,1,0.2);
  glMultiTexCoord3f(GL_TEXTURE2,0,0,1);
  glVertex3f(0.75,0.25,0.0);

  glMultiTexCoord3f(GL_TEXTURE0,1,0,0.2);
  glMultiTexCoord3f(GL_TEXTURE1,0,1,0.2);
  glMultiTexCoord3f(GL_TEXTURE2,0,0,1);
  glVertex3f(0.75,0.75,0.0);
  
  glMultiTexCoord3f(GL_TEXTURE0,1,0,0.2);
  glMultiTexCoord3f(GL_TEXTURE1,0,1,-0.2);
  glMultiTexCoord3f(GL_TEXTURE2,0,0,1);
  glVertex3f(0.25,0.75,0.0);
  
  glEnd();
  
#if 0
  glBegin(GL_POINTS);
  glMultiTexCoord3f(GL_TEXTURE0,1,0,0);
  glMultiTexCoord3f(GL_TEXTURE1,0,1,0);
  glMultiTexCoord3f(GL_TEXTURE2,0,0,1);
  glVertex3f(0.25,0.25,0.0);
  glEnd();
#endif
#endif

  progFrag->Disable();
  progVert->Disable();

  cgGLDisableTextureParameter(patchTP);
  cgGLDisableTextureParameter(sceneTP);
  
  glFlush();
}

int main(int nargs,char **argv) {
  GLIPContextC::RefT ctxt = new GLIPContextC(&nargs,argv);
  OptionC opts(nargs,argv);
  opts.Check();
  
  cgGLSetManageTextureParameters(ctxt->CgContext(),true);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glClearColor(0.0,0.0,0.0,0.0);
  glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
  
  glEnable(GL_TEXTURE_2D);
  
  ImageC<ByteRGBValueC> img;
  if(!Load("monkey.ppm",img)) {
    cerr << "Failed to find the monkey. \n";
    return 1;
  }
  
  sceneTexId= GLIPCreateTexture(img,GL_NEAREST);
  patchTexId= GLIPCreateTexture(img,GL_NEAREST);
  
  
#if 1
  progVert = new GLIPProgramC(*ctxt,GLIPPROG_VERTEX);
  if(!progVert->LoadFile("vertex.cg")) {
    cerr << "Failed to load vertex program. \n";
    return 1;
  }
  if(!progVert->Bind()) {
    cerr << "Failed to bind vertex program. \n";
    return 1;    
  }
#endif
#if 1
  progFrag = new GLIPProgramC(*ctxt,GLIPPROG_FRAGMENT);

  //StringC fragProg = "frag.cg";
  StringC fragProg = "correlation.cg";
  
  if(!progFrag->LoadFile(fragProg)) {
    cerr << "Failed to load fragment program. \n";
    return 1;
  }
  
  if(!progFrag->Bind()) {
    cerr << "Failed to bind fragment program. \n";
    return 1;    
  }
#endif

  
#if 0
  CGparameter param = cgGetNamedParameter(progFrag->CgProgram(), "monkeyMagic");
  if(param == 0) {
    cerr << "Failed to find parameter. \n";
    return 1;
  }
  cgGLSetTextureParameter(param,patchTexId);
#endif
  
#if 0
  for(int i = 0;i < 10;i++)
    DrawDisplay();
#else
  glutDisplayFunc(&DrawDisplay);
  glutMainLoop();
#endif
  
  return 0;
}

