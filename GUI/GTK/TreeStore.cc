// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI
//! date="23/9/2003"
//! author="Charles Galambos"
//! file="Ravl/GUI/GTK/TreeStore.cc"

#include "Ravl/GUI/TreeStore.hh"
#include "Ravl/GUI/Pixmap.hh"
#include "Ravl/GUI/ReadBack.hh"

#if RAVL_USE_GTK2

#include "Ravl/SArray1dIter2.hh"
#include  <gtk/gtk.h>

namespace RavlGUIN {

  extern GType Ravl2GTKType(AttributeValueTypeT vtype);
  
  //: Constructor.
  
  TreeStoreBodyC::TreeStoreBodyC(const SArray1dC<AttributeTypeC> &nColTypes) 
    : TreeModelBodyC(nColTypes)
  { Create(); }
  
  //: Destructor.
  
  TreeStoreBodyC::~TreeStoreBodyC()
  {}
  
  //: Delete a row.
  // After return, the iterator will point to the next row at the same level,
  // or will be invalidated if such a row does not exist.
  
  bool TreeStoreBodyC::GUIDeleteRow(TreeModelIterC &rowHandle) {
    if (!gtk_tree_store_remove (GTK_TREE_STORE(model),rowHandle.TreeIter()))
      rowHandle.Invalidate();
    return true;
  }
  
  //: Set int value.
  
  bool TreeStoreBodyC::GUISetValue(TreeModelIterC &rowIter,IntT col, IntT value) {
    gtk_tree_store_set(GTK_TREE_STORE(model),rowIter.TreeIter(),col,value,-1);
    return true;
  }
  
  //: Set bool value.
  
  bool TreeStoreBodyC::GUISetValue(TreeModelIterC &rowIter,IntT col, bool value) {
    gtk_tree_store_set(GTK_TREE_STORE(model),rowIter.TreeIter(),col,value,-1);
    return true;
  }
  
  //: Set bool value.
  
  bool TreeStoreBodyC::GUISetValue(TreeModelIterC &rowIter,IntT col, const StringC &value) {
    gtk_tree_store_set(GTK_TREE_STORE(model),rowIter.TreeIter(),col,const_cast<char *>(value.chars()),-1);
    return true;    
  }

  //: Set bool value.
  
  bool TreeStoreBodyC::GUISetValue(TreeModelIterC &rowIter,IntT col, const PixbufC &value) {
    gtk_tree_store_set(GTK_TREE_STORE(model),rowIter.TreeIter(),col,value.Pixbuf(),-1);
    return true;
  }
  
  
  //: Append a row.
  
  bool TreeStoreBodyC::AppendRow(TreeModelIterC &rowIter,TreeModelIterC &parentIter) {
    ReadBackLockC lock;
    // Append row
    gtk_tree_store_append (GTK_TREE_STORE(model), rowIter.TreeIter(),parentIter.TreeIter());
    // Set tree model in iterator
    rowIter.Model(model);
    return true;
  }
  
  //: Append a row.

  bool TreeStoreBodyC::AppendRow(TreeModelIterC &rowIter) {
    ReadBackLockC lock;
    // Append row
    gtk_tree_store_append (GTK_TREE_STORE(model), rowIter.TreeIter(),0);
    // Set tree model in iterator
    rowIter.Model(model);
    return true;
  }
  
  //: Clear store of all values.
  
  void TreeStoreBodyC::GUIEmpty() {
    gtk_tree_store_clear(GTK_TREE_STORE(model));
  }
  
  //: Create the widget.
  
  bool TreeStoreBodyC::Create() {
    if(model != 0)
      return true;
    ReadBackLockC lock;    
    SArray1dC<GType> types(colTypes.Size());
    for(SArray1dIter2C<GType,AttributeTypeC> it(types,colTypes);it;it++)
      it.Data1() = Ravl2GTKType(it.Data2().ValueType());
    model = GTK_TREE_MODEL(gtk_tree_store_newv(colTypes.Size(),&(types[0])));
    lock.Unlock();
    return TreeModelBodyC::Create();
  }

}
#endif
