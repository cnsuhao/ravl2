/////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Button.hh"
//#include "Ravl/GUI/ToggleButton.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/Option.hh"

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
  OptionC opts(nargs,args);
  opts.Check();
  
  WindowC win(100,100,"Hello");
  
  win.Add(VBox(Button("Button 1",buttonA,1) +
	       Button("Button 2",buttonB,2)
	       )
	  );
  win.Show();
  
  Manager.Start();
  cerr << "Finished... \n";
}
