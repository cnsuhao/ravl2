/////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/RadioButton.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/Option.hh"

using namespace RavlGUIN;

bool buttonA(bool &v)
{
  cerr << "ButtonA:" << v << "\n";
  return true;
}

bool buttonB(bool &v)
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
  DListC<StringC> sel;
  sel.InsFirst("Hello1");
  sel.InsFirst("Hello2");
  sel.InsFirst("Hello3");
  //MenuBarC menuBar;
  //menuBar +
  RadioButtonGroupT buttonGrp;
  
  win.Add(
	  HBox(
	       RadioButton("A Button 1",buttonGrp,buttonA) + 
	       RadioButton("A Button 2",buttonGrp,buttonB) +
	       RadioButton("A Button 3",buttonGrp) + 
	       RadioButton("A Button 4",buttonGrp) 
	       ) 
	  );
  win.Show();
  
  Manager.Start();
  cerr << "Finished... \n";
}
