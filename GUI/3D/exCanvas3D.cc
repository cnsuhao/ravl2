//////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/Canvas.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Slider.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/Canvas3D.hh"
#include "Ravl/GUI/DViewPoint3D.hh"
#include "Ravl/GUI/DCube3D.hh"
#include "Ravl/GUI/DLight3D.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/Option.hh"
#include "Ravl/GUI/Bitmap.hh"
#include "Ravl/Vector3d.hh"
#include <gtk/gtk.h>
#include <gdk/gdk.h>

using namespace RavlN;
using namespace RavlGUIN;


bool DrawFunc()
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
  return true;
}

bool pressFunc(MouseEventC &me) {
  cerr << "Press " << me.X() << " " << me.Y() << "\n";
  return true;
}

bool releaseFunc(MouseEventC &me) {
  cerr << "Release " << me.X() << " " << me.Y() << "\n";
  return true;
}

bool moveFunc(MouseEventC &me) {
  cerr << "Move " << me.X() << " " << me.Y() << "\n";
  return true;
}


int main(int nargs,char *args[]) 
{
  Manager.Init(nargs,args);
  
  OptionC opts(nargs,args); // Make sure help option is detected.
  bool doMotion = opts.Boolean("m",false,"Detect motion events.");
  opts.Check();
  
  WindowC win(100,100,"Hello");
  Canvas3DC area(400,400);
  
  Connect(area.Signal("button_press_event"),&pressFunc);
  Connect(area.Signal("button_release_event"),&releaseFunc);
  if(doMotion)
    Connect(area.Signal("motion_notify_event"),&moveFunc);
  
  win.Add(area);
  cerr << "Starting gui. \n";
  Manager.Execute();
  win.Show();
  
  area.Light(RealRGBValueC(0.8,0.8,0.8),Point3dC(3,3,10));
  area.ViewPoint(90,Point3dC(0,0,3)); // Setup view point.
  
  DCube3DC object(Vector3dC(1,1,1),RealRGBValueC(0,1,0));
  //object.EnableDisplayList();
  
  for(RealT i = 0;i < 1000;i++) {
    // Draw rotated cube
    area.Transform(i * 5,  // Angle.
		   Vector3dC(0,1,0), // Axis of rotation
		   object); // Object to draw.
    area.SwapBuffers();
  }
  cerr << "Execute done, waiting... \n";
  Manager.Wait();
}
