///////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Tree.hh"
#include "Ravl/GUI/Label.hh"
#include "Ravl/GUI/ScrolledArea.hh"

using namespace RavlGUIN;

int main(int nargs,char *args[]) 
{
  Manager.Init(nargs,args);
  
  WindowC win(100,100,"Hello");
  
  TreeC aTree(true);
  TreeItemC ti1("TreeItem1");
  TreeItemC ti2("TreeItem2");
  aTree.GUIAddChild(ti1);
  aTree.GUIAddChild(ti2);
  
  TreeC st2(true);
  
  TreeItemC ti5("TreeItem5");
  TreeItemC ti6("TreeItem6");
  st2.GUIAddChild(ti5);
  st2.GUIAddChild(ti6);
  
  TreeItemC ti3("TreeItem3");
  TreeItemC ti4("TreeItem4");
  TreeC st1(true);
  st1.GUIAddChild(ti3);
  st1.GUIAddChild(ti4);
  TreeItemC tst2(st2);
  st1.GUIAddChild(tst2);
  
  TreeItemC x("Hello",st1);
  aTree.GUIAddChild(x);
  
  aTree.DelChild(ti1);
  
  win.Add(ScrolledAreaC(aTree,100,100));  
  win.Show();
  
  Manager.Start();
  
  return 0;
}


