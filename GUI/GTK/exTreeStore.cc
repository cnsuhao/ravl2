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

using namespace RavlGUIN;

#endif

TreeStoreC treeStore;


bool EditCallback(TreeModelIterC &at,StringC &str2) {
  cerr << "Edit callback. " << str2 << "\n";
  treeStore.SetValue(at,1,str2);
  return true;
}

bool ToggleCallback(TreeModelIterC &at) {
  cerr << "Toggle callback. \n";
  bool val;
  treeStore.GetValue(at,3,val);
  val = !val;
  treeStore.SetValue(at,3,val);
  return true;
}

int main(int nargs,char **argv) {
#if RAVL_USE_GTK2
  Manager.Init(nargs,argv);
  OptionC opts(nargs,argv);
  opts.Check();
  
  WindowC win(100,100,"Hello");
  

  //: Create tree store.
  
  SArray1dC<AttributeTypeC> types(5);
  //types[0] = AttributeTypeNumC<IntT>("ANumber","...");
  types[0] = AttributeTypeStringC("Another","...");
  types[1] = AttributeTypeStringC("AString","...");
  types[2] = AttributeTypeMiscC("AImage","...",AVT_ByteRGBImage);
  types[3] = AttributeTypeBoolC("ABool","...");
  types[4] = AttributeTypeStringC("Colour","...");
  treeStore = TreeStoreC(types);
  
  //: Put some data into the tree store.
  
  TreeModelIterC iter;
  treeStore.AppendRow(iter);
  //treeStore.SetValue(iter,0,true);
  treeStore.SetValue(iter,0,StringC("meep"));
  treeStore.SetValue(iter,1,StringC("hello"));
  PixbufC map(xpmData_OpenFile);
  treeStore.SetValue(iter,2, map);
  treeStore.SetValue(iter,3,true);
  treeStore.SetValue(iter,4,StringC("red"));
  
  TreeModelIterC iter2;
  treeStore.AppendRow(iter2,iter);
  treeStore.SetValue(iter2,0,StringC("igloo"));
  treeStore.SetValue(iter2,1,StringC("child"));
  treeStore.SetValue(iter2,2, map);
  treeStore.SetValue(iter2,3,false);
  treeStore.SetValue(iter2,4,StringC("green"));
  
  //: View a tree store.
  
  DListC<StringC> cols;
  cols.InsLast("Another");
  cols.InsLast("AString");
  cols.InsLast("AImage");
  cols.InsLast("ABool");
  
  TreeViewC treeView(treeStore,cols);
  treeView.SetAttribute(1,"foreground","Colour");
  treeView.SetAttribute(1,"editable","1",false);
  treeView.SetAttribute(3,"activatable","1",false);
  Connect(treeView.ChangedSignal(1),&EditCallback);
  Connect(treeView.ChangedSignal(3),&ToggleCallback);
  
  win.Add(treeView);
  win.Create();
  
  
  
  win.Show();
  Manager.Start();
#endif  
  return 0;
}
