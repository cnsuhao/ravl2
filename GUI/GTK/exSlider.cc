/////////////////////////////////////////////////////////
//! rcsid=$Id$"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Slider.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/SpinButton.hh"

using namespace RavlGUIN;

bool sliderFunc(RealT &v,IntT &)
{
  cerr << "Slider:" << v << "\n";
  return true;
}

int main(int nargs,char *args[]) 
{
  Manager.Init(nargs,args);
  
  WindowC win(100,100,"Hello");
  
  win.Add(VBox(
	       SliderH(1.0,0.0,10.0,0.1,sliderFunc) +
	       SliderV(1.0,0.0,10.0,0.1,sliderFunc) +
	       SpinButtonC(4,1,1,0,2,1)
	       ));
  win.Show();
  
  Manager.Start();
  
}
