// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/List.hh"

using namespace RavlGUIN;

int main(int nargs,char *args[]) 
{
  Manager.Init(nargs,args);
  
  WindowC win(100,100,"Hello");
  using namespace RavlGUIN;
  DListC<StringC> sel;
  sel.InsFirst("Hello1");
  sel.InsFirst("Hello2");
  sel.InsFirst("Hello3");
  sel.InsFirst("A longer message");
  //MenuBarC menuBar;
  //menuBar +
  ListC aList(sel);
  aList.Add(StringC("Hi!!!"));
  win.Add(aList);
  
  win.Show();
  
  aList.Add(StringC("Hi2"));
  Manager.Start();
  
}
