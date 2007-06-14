// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/ListStore.cc"

#include "Ravl/GUI/ListStore.hh"
#include "Ravl/GUI/Manager.hh"

#include "Ravl/SArray1dIter2.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {
  
  extern GType Ravl2GTKType(AttributeValueTypeT vtype);
  

  //: Constructor.
  
  ListStoreBodyC::ListStoreBodyC()
  {}
  
  //: List store.
  
  ListStoreBodyC::ListStoreBodyC(const SArray1dC<AttributeTypeC> &nColTypes) 
    : TreeModelBodyC(nColTypes)
  { Create(); }
  
  //: Create the widget.
  
  bool ListStoreBodyC::Create() {
    if(model != 0)
      return true;
    
    SArray1dC<GType> types(colTypes.Size());
    for(SArray1dIter2C<GType,AttributeTypeC> it(types,colTypes);it;it++)
      it.Data1() = Ravl2GTKType(it.Data2().ValueType());
    model = GTK_TREE_MODEL(gtk_list_store_newv(colTypes.Size(),&(types[0])));
    
    return TreeModelBodyC::Create();
  }

  //: Append a row.
  
  bool ListStoreBodyC::AppendRow(TreeModelIterC &rowHandle) {
    RavlAssert(model != 0);
    
    gtk_list_store_append(GTK_LIST_STORE(model),rowHandle.TreeIter());
    
    return true;
  }
  
  //: Set int value.
  
  bool ListStoreBodyC::GUISetValue(TreeModelIterC &rowIter,IntT col, IntT value) {
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    if(!rowIter.IsElm())
      return false;
    gtk_list_store_set(GTK_LIST_STORE(model),rowIter.TreeIter(),col,value,-1);
    return true;
  }
  //: Set bool value.
  
  bool ListStoreBodyC::GUISetValue(TreeModelIterC &rowIter,IntT col, bool value) {
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    if(!rowIter.IsElm())
      return false;
    gtk_list_store_set(GTK_LIST_STORE(model),rowIter.TreeIter(),col,value,-1);
    return true;
  }
  
  //: Set bool value.
  
  bool ListStoreBodyC::GUISetValue(TreeModelIterC &rowIter,IntT col, const StringC &value) {
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    if(!rowIter.IsElm())
      return false;
    gtk_list_store_set(GTK_LIST_STORE(model),rowIter.TreeIter(),col,const_cast<char *>(value.chars()),-1);
    return true;    
  }

  //: Set bool value.
  
  bool ListStoreBodyC::GUISetValue(TreeModelIterC &rowIter,IntT col, const PixbufC &value) {
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    if(!rowIter.IsElm())
      return false;
    gtk_list_store_set(GTK_LIST_STORE(model),rowIter.TreeIter(),col,value.Pixbuf(),-1);
    return true;
  }

  //: Clear store of all values.
  
  void ListStoreBodyC::GUIEmpty() {
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    gtk_list_store_clear(GTK_LIST_STORE(model));
  }


}

