// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI
//! author="Charles Galambos"
//! docentry="Ravl.Graphics.GTK.Control"

#include "Ravl/GUI/Menu.hh"
#include "Ravl/GUI/ColourSelector.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/TextBox.hh"

using namespace RavlN;
using namespace RavlGUIN;

//: Callback, Open a file.

bool ShowColour(UInt16RGBValueC &colour,ColourSelectorC &fs,TextBoxC &textBox) {
  StringC col = StringC(colour.Red()) + " " + StringC(colour.Green()) + " " + StringC(colour.Blue()) + "\n";
  textBox.Insert(col);  // Display colour in textbox.
  return true;
}

//: Callback, Quit the application.

bool gui_quit()  {
  Manager.Quit(); // Initate shutdown.
  return true;
}


int main(int nargs,char **argv) {
  Manager.Init(nargs,argv);
  
  // Create a textbox to show files user has requested.
  
  TextBoxC textBox("",true);
  
  // Create a fileselector 
  
  ColourSelectorC fs = ColourSelector("Load Image",UInt16RGBValueC(255,0,0),&ShowColour,textBox);
  
  // Create a menubar
  
  MenuBarC menuBar(MenuC("File",
			 MenuItem("Quit",gui_quit)  +
			 MenuItemShow("Open",fs)     // Show fileselector.
			 ));
  
  // Create a window with a menu bar and textbox
  
  WindowC win(100,100,"ColourSelectorC example");
  win.Add(VBox(menuBar + 
	       textBox));
  win.Show();
  
  // Start the GUI.
  
  Manager.Start();
  
}
