
//////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/View3D.hh"
#include "Ravl/Option.hh"
#include "Ravl/Vector3d.hh"

#include <GL/gl.h>

using namespace RavlN;
using namespace RavlGUIN;

void DrawFunc()
{
  Vector3dC diag(1,1,1);
  Vector3dC d1 = diag/2;
  Vector3dC d2 = -diag/2;

  glBegin(GL_QUAD_STRIP);
  {
    glNormal3d(1,0,0);
	       
    glVertex3d(d1.X(),d1.Y(),d1.Y());
    glVertex3d(d1.X(),d2.Y(),d1.Y());
    
    glVertex3d(d1.X(),d1.Y(),d2.Y());
    glVertex3d(d1.X(),d2.Y(),d2.Y());
  }
  glEnd();

  glBegin(GL_QUAD_STRIP);
  {
    glNormal3d(-1,0,0);
    
    glVertex3d(d2.X(),d1.Y(),d1.Y());
    glVertex3d(d2.X(),d2.Y(),d1.Y());
    
    glVertex3d(d2.X(),d1.Y(),d2.Y());
    glVertex3d(d2.X(),d2.Y(),d2.Y());
  }
  glEnd();  
}

int main(int nargs,char *args[]) 
{
  OptionC opts(nargs,args); // Make sure help option is detected.
  opts.Check();
  
  Manager.Init(nargs,args);
  
  WindowC win(100,100,"Hello");  
  View3DC view(400,400);  
  win.Add(view);
  win.Show();

  cerr << "Starting gui. \n";
  Manager.Execute();

  view.Put(DOpenGLC(Trigger(DrawFunc)));
  
  Manager.Wait();

}
