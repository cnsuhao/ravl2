// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/exMenu.cc"
//! userlevel=Normal
//! docentry="Ravl.API.Graphics.GTK.Control"
//! author="Charles Galambos"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/RawCanvas.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Menu.hh"
#include "Ravl/GUI/MenuCheck.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/Label.hh"
#include "Ravl/GUI/FileSelector.hh"
#include "Ravl/GUI/StatusBar.hh"

using namespace RavlGUIN;

bool gui_quit() 
{
  Manager.Quit(); // Initate shutdown.
  return true;
}

int main(int nargs,char *args[]) 
{
  Manager.Init(nargs,args);
  
  WindowC win(100,100,"Hello");
  
  FileSelectorC fs;
  
  MenuC test("back",
		MenuItemC("Not Implemented") +
		MenuItem("Quit",gui_quit) 
		);
  StatusBarC sb("Hello");
  RealT d = 2;
  MenuBarC menuBar(MenuC("File",
			 MenuItem("Not Implemented 1",sb,&StatusBarC::PushTimedF,d,StringC("Not Implemented.")) +
			 MenuItem("Not Implemented 2",sb,&StatusBarC::PushF,StringC("Not Implemented.2")) +
			 MenuItemSeparator() +
			 MenuItemShow("Open",fs) +
			 MenuItem("Quit",gui_quit) +
			 MenuCheckItemC("xx")
			 ));
  
  win.Add(VBox(menuBar + 
	       RawCanvasC(100,100) +       // Make a canvas
	       sb
	       ));
  win.Show();
  sb.Next("Ready.");
  //sb.PushTimed(3,"Setup complete.");
  
  Manager.Start();
  cerr << "Finished. \n";
}
