/////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/List.hh"

using namespace RavlGUIN;

int main(int nargs,char *args[]) 
{
  Manager.Init(nargs,args);
  
  WindowC win(100,100,"Hello");
  using namespace RavlGUIN;
  DListC<StringC> sel;
  sel.InsFirst("Hello1");
  sel.InsFirst("Hello2");
  sel.InsFirst("Hello3");
  sel.InsFirst("A longer message");
  //MenuBarC menuBar;
  //menuBar +
  ListC aList(sel);
  aList.Add(StringC("Hi!!!"));
  win.Add(aList);
  
  win.Show();
  
  aList.Add(StringC("Hi2"));
  Manager.Start();
  
}
