// This file is part of OmniSoft, Pattern recognition software 
// Copyright (C) 2002, Omniperception Ltd.
// file-header-ends-here
//! rcsid="$Id$"
//! lib=omnilogin

#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Pixmap.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/GUI/WidgetStyle.hh"
#include "Ravl/Option.hh"

using namespace RavlN;
using namespace RavlGUIN;
using namespace RavlImageN;

int main(int nargs,char *args[]) {

  OptionC opts(nargs,args);
  StringC file = opts.String("i",PROJECT_OUT "/share/RAVL/pixmaps/monkey.ppm","input filename");
  opts.Check();

  // Initialise GUI manager
  Manager.Init(nargs,args);

  // Load an image to use as background
  ImageC<ByteRGBValueC> img;
  if (!Load(file,img)) {
    return 1;
  }  

  // Create main window
  WindowC win(256,256,"exStyle");
  win.Show();
  
  // Create style
  WidgetStyleC style;
  // Create pixmap
  PixmapC pixmap(win,img);
  // Set background
  style.SetBackground(pixmap);

  // Set style
  win.SetStyle(style);

  // Start GUI
  Manager.Execute();

  // Done
  Manager.Wait();
  return 0;
}
