

#include "Ravl/Image/Image.hh"
#include "Ravl/IO.hh"
#include "Ravl/GUI/Menu.hh"
#include "Ravl/GUI/Canvas.hh"
#include "Ravl/GUI/FileSelector.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/Window.hh"

using namespace RavlN;
using namespace RavlGUIN;

//: Callback, Load an image.

bool LoadImage(StringC &filename,FileSelectorC &fs,CanvasC &canvas) {
  
  // Load a colour image.
  
  ImageC<ByteRGBValueC> img;
  if(!Load(filename,img)) {
    cerr << "Failed to load image '" << filename << "\n";
    return true;
  }

  // Draw image onto the canvas.
  canvas.DrawImage(img);
  
  return true;
}

//: Callback, Quit the application.

bool gui_quit() 
{
  Manager.Quit(); // Initate shutdown.
  return true;
}


int main(int nargs,char **argv) {
  Manager.Init(nargs,argv);
  
  // Create a canvas to draw to.
  
  CanvasC canvas(200,200);

  // Create a fileselector 
  
  FileSelectorC fs = FileSelector("Load Image","img.ppm",&LoadImage,canvas);
  
  
  // Create a window with a menu bar.
  
  MenuBarC menuBar(MenuC("File",
			 MenuItem("Quit",gui_quit)  +
			 MenuItemShow("Open",fs)
			 ));
  
  WindowC win(100,100,"FileSelectorC example");
  win.Add(VBox(menuBar + 
	       canvas));
  win.Show();
  
  // Start the GUI.
  
  Manager.Start();
  
}
