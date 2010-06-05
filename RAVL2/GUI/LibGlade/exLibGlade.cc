// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd. 
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: exLibGlade.cc 6701 2008-04-09 16:07:40Z ees1wc $"
//! lib=RavlLibGlade
//! file="Ravl/GUI/LibGlade/exLibGlade.cc"
//! docentry="Ravl.API.Graphics.GTK.LibGlade"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/Menu.hh"
#include "Ravl/Option.hh"

#include "Ravl/GUI/GladeWidget.hh"

using namespace RavlGUIN;

bool OnPress1() {
  cerr << "Pressed 1. \n";
  return true;
}

bool OnPress2() {
  cerr << "Pressed 2. \n";
  return true;
}

bool OnQuit() 
{
  Manager.Quit(); // Initate shutdown.
  return true;
}

int main(int nargs,char **argv) {
  Manager.Init(nargs,argv);
  OptionC opts(nargs,argv);
  StringC xmlfile = opts.String("f",PROJECT_OUT "/share/RAVL/Glade/exlibglade.glade","Interface description file. ");
  opts.Check();
  
  cerr << "Create widgets. \n";

  GladeXMLC  glade(xmlfile);
  GladeWidgetC mainWindow(glade,"window1");

  GladeWidgetC SubWidget(glade,"AWidget");
  
  mainWindow.AddObject("button1",Button("Test",&OnPress1));
  mainWindow.AddObject("button2",Button("Test",&OnPress2));
  mainWindow.AddObject("quit1",MenuItem("Quit",&OnQuit));
  mainWindow.AddObject("SubWidget",SubWidget);
  
  cerr << "Show widgets. \n";
  
  mainWindow.Show();
  
  cerr << "Start GUI. \n";
  
  Manager.Start();

  cerr << "Done. \n";
  
  return 0;
}
