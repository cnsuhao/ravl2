/////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/RawCanvas.hh"
#include "Ravl/GUI/Cursor.hh"

using namespace RavlGUIN;

int main(int nargs,char *args[]) 
{
  Manager.Init(nargs,args);
  
  WindowC win(100,100,"Hello");
  CursorC curs("GDK_HAND1");
  RawCanvasC canvas(100,100);
  win.Add(canvas);
  win.SetCursor(curs);
  win.Show();
  Manager.Start();
  
  return 0;
}
