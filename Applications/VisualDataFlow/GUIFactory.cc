// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: GUIFactory.cc 1533 2002-08-08 16:03:23Z craftit $"
//! lib=RavlVDF
//! author="Charles Galambos"
//! file="Ravl/Applications/VisualDataFlow/GUIFactory.cc"

#include "Ravl/DF/GUIFactory.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/Threads/Signal2.hh"
#include <gtk/gtk.h>

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {
  
  //: Default constructor.
  
  GUIFactoryBodyC::GUIFactoryBodyC(const FactorySetC &nFactories)
    : factories(nFactories),
      tree(true)
  {
    Add(tree);
  }
  
  //: Create the widget.
  
  bool GUIFactoryBodyC::Create() {
    
    // Add factories to tree.
    for(DLIterC<FactoryC> it(factories.List());it;it++)
      AddFactory(*it);
    
    if(!LBoxBodyC::Create())
      return false;
    return true;
  }
  
  //: Drag and drop data get.
  
  bool GUIFactoryBodyC::DNDFactoryDataGet(DNDDataInfoC &info,StringC &id) {
    ONDEBUG(cerr << "GUIFactoryBodyC::DNDFactoryDataGet(), Called. ID=" << id << " \n");
    info.PutString(2,id);
    return true;
  }
  
  //: Add factory to display.
  
  bool GUIFactoryBodyC::AddFactory(const FactoryC &factory) {
    //ONDEBUG(cerr << "GUIFactoryBodyC::AddFactory(), Adding '" << factory.Name() << "'\n");
    StringC entryname;
    StringC lastname;
    TreeC lastTree = tree;
    for(DLIterC<StringC> it(factory.Section());it;it++) {
      if(!lastname.IsEmpty()) {
	entryname = lastname.Copy();
	entryname += '.';
      }
      entryname += *it;
      //ONDEBUG(cerr << "GUIFactoryBodyC::AddFactory(), Adding entry '" << entryname << "'\n");
      if(it.IsLast()) {
	TreeItemC treeItem(*it);
	
	// Setup drag and drop.
	DNDDataInfoC tmp;
	ConnectRef(treeItem.Signal("drag_data_get"),*this,&GUIFactoryBodyC::DNDFactoryDataGet,tmp,factory.Name());
	SArray1dC<GtkTargetEntry> te(2);
	te[0].target = "text/uri-list";
	te[0].flags = 0;
	te[0].info = 1;
	te[1].target = "application/ravl-type";
	te[1].flags = 0;
	te[1].info = 2;
	treeItem.GUIDNDSource(GDK_BUTTON1_MASK,
			      te,
			      GDK_ACTION_MOVE | GDK_ACTION_COPY);
	
	// Add to table...
	name2treeitem[entryname] = treeItem;
	lastTree.AddChild(treeItem);
	break;
      }
      if(!name2tree.Lookup(entryname,lastTree)) {
	TreeC branch(true);
	name2tree[entryname] = branch;
	lastTree.AddChild(TreeItemC(*it,branch));
	lastTree = branch;
      }
      lastname = entryname;
    }
    
    return true;
  }

}
