/////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/GUI/Window.hh"
#include "amma/GUI/Manager.hh"
#include "amma/GUI/LBox.hh"
#include "amma/GUI/Graph1d.hh"
#include "amma/Random.hh"
#include "amma/Arr1Iter.hh"
#include "amma/Date.hh"

#include "amma/Option.hh"

int main(int nargs,char *args[]) 
{
  GUIManager.Init(nargs,args);
  OptionC opts(nargs,args);
  opts.Check();
    
  GUIWindowC win(300,300,"exGraph1d.cc");
  GUIGraph1dC graph(Point2dC(0,0),Point2dC(10,10),Vector2dC(1,1));
  win.Add(graph);
  
  win.Show();
  GUIManager.Execute();
  
  DateC::Sleep(0.1);
  while(1) {
    DateC::Sleep(1);
    Array1dC<RealT> values(50);
    for(Array1dIterC<RealT> it(values);it.IsElm();it.Next()) 
      it.Data() = Random1() * 5;
    graph.Plot(values,1,0,0);
  }
  
  GUIManager.Wait();
  cerr << "Finished... \n";
}
