// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd. 
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLibGlade

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/LBox.hh"
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

int main(int nargs,char **argv) {
  Manager.Init(nargs,argv);
  OptionC opts(nargs,argv);
  StringC xmlfile = opts.String("f","project1.glade","Interface description file. ");
  opts.Check();
  
  GladeXMLC  glade(xmlfile);
  
  GladeWidgetC mainWindow(glade,"window1");
  
  mainWindow.AddObject("button1",Button("Test",&OnPress1));
  mainWindow.AddObject("button2",Button("Test",&OnPress2));
  
  mainWindow.Show();
  
  Manager.Start();

  
  return 0;
}
