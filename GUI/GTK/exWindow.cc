// This file is part of OmniSoft, Pattern recognition software 
// Copyright (C) 2002, Omniperception Ltd.
// file-header-ends-here
//! rcsid="$Id$"
//! lib=omnilogin

#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Window.hh"
#include "Ravl/DP/FileFormatIO.hh"

using namespace RavlN;
using namespace RavlGUIN;
using namespace RavlImageN;

int main(int nargs,char *args[]) {

  // Initialise GUI manager
  Manager.Init(nargs,args);

  // Load an image to use as background
  ImageC<ByteRGBValueC> img;
  Load("/usr/share/doorman/misc/monkey.png",img);

  // Create main window
  WindowC win(100,100,"exWindow");
  win.Show();
  // Set background
  win.SetBackground(img);

  // Start GUI
  Manager.Execute();

  // Done
  Manager.Wait();
  return 0;
}
