// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Control"
//! lib=RavlGUI

//: Example of TreeStoreC
// Available on GTK+-2.0 and above only.

#include "Ravl/config.h"

#if RAVL_USE_GTK2

#include "Ravl/GUI/TreeStore.hh"
#include "Ravl/GUI/TreeView.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/Option.hh"
#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/Pixmap.hh"
#include "Ravl/DP/AttributeValueTypes.hh"
#include <gtk/gtk.h>

#endif


using namespace RavlGUIN;


int main(int nargs,char **argv) {
#if RAVL_USE_GTK2
  Manager.Init(nargs,argv);
  OptionC opts(nargs,argv);
  opts.Check();
  
  SArray1dC<AttributeTypeC> types(3);
  //types[0] = AttributeTypeNumC<IntT>("ANumber","...");
  //types[0] = AttributeTypeBoolC("ABool","...");
  types[0] = AttributeTypeStringC("Another","...");
  types[1] = AttributeTypeStringC("AString","...");
  types[2] = AttributeTypeMiscC("AImage","...",AVT_ByteRGBImage);
  
  TreeModelRowC iter;
  TreeStoreC treeStore(types);
  treeStore.AppendRow(iter);
  //treeStore.SetValue(iter,0,true);
  treeStore.SetValue(iter,0,StringC("meep"));
  treeStore.SetValue(iter,1,StringC("hello"));
  PixmapC map((char **) xpmData_OpenFile);
  treeStore.SetValue(iter,2, map);
  
  TreeModelRowC iter2;
  treeStore.AppendRow(iter2,iter);
  treeStore.SetValue(iter2,0,StringC("igloo"));
  treeStore.SetValue(iter2,1,StringC("child"));
  treeStore.SetValue(iter2,2, map);
  
  TreeViewC treeView(treeStore);
  
  WindowC win(100,100,"Hello");
  win.Add(treeView);
  win.Show();
  Manager.Start();
#endif  
  return 0;
}
