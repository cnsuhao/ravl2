/////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/Notebook.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/LBox.hh"

using namespace RavlGUIN;

bool buttonA(IntT &v)
{
  cerr << "ButtonA:" << v << "\n";
  return true;
}

bool buttonB(IntT &v)
{
  cerr << "ButtonB:" << v << "\n";
  return true;
}


int main(int nargs,char *args[]) 
{
  Manager.Init(nargs,args);
  
  WindowC win(100,100,"Hello");
  
  NotebookC nb(GTK_POS_TOP);
  nb.Add(
	    VBox(Button("A Button 1",&buttonA,1) + Button("A Button 3",&buttonA,3)) + 
	    VBox(Button("A Button 2",&buttonB,2) + Button("A Button 4",&buttonB,4))
	    );
  win.Add(nb);
  win.Show();
  
  Manager.Start();
  
}
