// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: exTreeStore.cc 5839 2006-08-23 09:40:49Z robowaz $"
//! author="Charles Galambos"
//! docentry="Ravl.API.GUI.Control"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/exTreeStore.cc"

//: Example of TreeStoreC
// Available on GTK+-2.0 and above only.

#include "Ravl/config.h"


#include "Ravl/GUI/TreeStore.hh"
#include "Ravl/GUI/ListStore.hh"
#include "Ravl/GUI/IconView.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/Option.hh"
#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/Pixmap.hh"
#include "Ravl/DP/AttributeValueTypes.hh"
#include <gtk/gtk.h>

using namespace RavlGUIN;


ListStoreC listStore;

bool SelectCallback() {
  cerr << "Selection changed. \n";
  return true;
}


int main(int nargs,char **argv) {
  Manager.Init(nargs,argv);
  OptionC opts(nargs,argv);
  opts.Check();
  
  WindowC win(100,100,"Hello");
  
  //: Create tree store.
  
  SArray1dC<AttributeTypeC> types(3);
  types[0] = AttributeTypeStringC("Text","...");
  types[1] = AttributeTypeMiscC("Icon","...",AVT_ByteRGBImage);
  types[2] = AttributeTypeBoolC("ABool","...");   
  listStore = ListStoreC(types);
  
  //: Put some data into the tree store.
  
  TreeModelIterC iter;
  listStore.AppendRow(iter);
  listStore.GUISetValue(iter,0,"hello");
  PixbufC map(xpmData_OpenFile);
  listStore.GUISetValue(iter,1, map);
  listStore.GUISetValue(iter,2,true);
  
  // Add another line to the tree store.
  TreeModelIterC iter1;
  listStore.AppendRow(iter1);
  listStore.GUISetValue(iter1,0,"ping");
  listStore.GUISetValue(iter1,1, map);
  listStore.GUISetValue(iter1,2,false);
  
  // Add another line to the tree store.
  TreeModelIterC iter2;
  listStore.AppendRow(iter2);
  listStore.GUISetValue(iter2,0,"child");
  listStore.GUISetValue(iter2,1, map); //GTK_STOCK_ADD
  listStore.GUISetValue(iter2,2,false);
  
  // Add another line to the tree store.
  TreeModelIterC iter3;
  listStore.AppendRow(iter3);
  listStore.GUISetValue(iter3,0,"Wobble");
  listStore.GUISetValue(iter3,1, map);
  listStore.GUISetValue(iter3,2,false);
  
  
  // Create a new tree view displaying the columns
  IconViewC iconView(listStore,0,1,40);
  
  
  // Connect the changed signal for column 1 to 'EditCallback'
  Connect(iconView.Signal("selection_changed"),&SelectCallback);
  
  // Setup the widgets, and off we go!
  win.Add(iconView);
  
  win.GUIShow();

  Manager.Start();
  return 0;
}
