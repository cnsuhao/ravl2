
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glext.h>
#include <Cg/cgGL.h>
#include <GL/glut.h>

#include "Ravl/Image/GLIPContext.hh"
#include "Ravl/Image/GLIPProgram.hh"
#include "Ravl/Image/GLIPBuffer.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Option.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/IO.hh"


using namespace RavlN::ImageN;
using namespace RavlImageN;


GLuint sceneTexId;

void DrawDisplay(void) {
  cerr << "DrawDisplay, Called. \n";
  
  glClear(GL_COLOR_BUFFER_BIT);  
  glBindTexture(GL_TEXTURE_2D,sceneTexId);
  
  glColor3f(1.0,1.0,1.0);
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,0.0);  glVertex3f(0.25,0.25,0.0);
  glTexCoord2f(1.0,0.0);  glVertex3f(0.75,0.25,0.0);
  glTexCoord2f(1.0,1.0);  glVertex3f(0.75,0.75,0.0);
  glTexCoord2f(0.0,1.0);  glVertex3f(0.25,0.75,0.0);
  glEnd();
  
  glFlush();
}

int main(int nargs,char **argv) {
  GLIPContextC::RefT ctxt = new GLIPContextC(&nargs,argv);
  OptionC opts(nargs,argv);
  opts.Check();
  
  GLIPBufferC::RefT buf;
  try {
    buf = new GLIPBufferC(*ctxt,256,256,8,1,false);
    //buf = new GLIPBufferC(256,256,32,4,true);
    //buf = new GLIPBufferC(256,256,32,1,true);
  } catch(...) {
    cerr << "Failed to allocate Buffer. \n";
    return 1;
  }
  buf->MakeCurrent();
  
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
  
  glutDisplayFunc(&DrawDisplay);
  glutMainLoop();
  
  return 0;
}

