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
//! date="23/9/2003"

#include "Ravl/GUI/TreeModel.hh"

#if RAVL_USE_GTK2

#include <gtk/gtk.h>
#include "Ravl/HashIter.hh"

namespace RavlGUIN {
  
  GType Ravl2GTKType(AttributeValueTypeT vtype) {
    switch(vtype) {
    case AVT_Bool:     return G_TYPE_BOOLEAN;
    case AVT_Int:      return G_TYPE_INT;
    case AVT_Real:     return G_TYPE_FLOAT;
    case AVT_String:   return G_TYPE_STRING;
    case AVT_Enum:     return G_TYPE_ENUM;
    case AVT_Abstract: return G_TYPE_NONE;
    case AVT_ByteRGBImage: return GDK_TYPE_PIXBUF;
    case AVT_None:     return G_TYPE_NONE;
    case AVT_Invalid:  return G_TYPE_INVALID;
    }
    return G_TYPE_INVALID;
  }
  
  //:----------------------------------------------------------------------------
  
  //: Constructor.
  
  TreeModelIterBodyC::TreeModelIterBodyC() 
    : model(0),
      treeIter(new GtkTreeIter),
      canfree(true)
  {}

  //: Constructor.
  
  TreeModelIterBodyC::TreeModelIterBodyC(GtkTreeIter *ntreeIter,bool nCanFree)
    : model(0),
      treeIter(ntreeIter),
      canfree(nCanFree)
  {}

  //: Construct from tree model.
  
  TreeModelIterBodyC::TreeModelIterBodyC(TreeModelC &ntreeModel) 
    : model(0),
      treeIter(new GtkTreeIter),
      canfree(true)
  {
    model = ntreeModel.Body().model;
    gtk_tree_model_get_iter_first (model,treeIter);
  }
  
  //: Destructor.
  
  TreeModelIterBodyC::~TreeModelIterBodyC() 
  { if(canfree && treeIter != 0) delete treeIter; }
  
  //: Goto next element at current level.
  // Returns true if succeeded.
  
  bool TreeModelIterBodyC::Next() {
    RavlAssert(model != 0);
    return gtk_tree_model_iter_next (model,treeIter);
  }

  //: Return iterator for first child.
  // Will return an invalid iterator if none.
  
  TreeModelIterC TreeModelIterBodyC::Children() {
    RavlAssert(model != 0);
    TreeModelIterC ret;
    if(!gtk_tree_model_iter_children (model,ret.TreeIter(),treeIter))
      ret.Invalidate();
    return ret;
  }
  
  //: Does current node have children ?
  
  bool TreeModelIterBodyC::HasChildren() {
    RavlAssert(model != 0);
    return gtk_tree_model_iter_has_child (model,treeIter);
  }
  
  //: Get iterator for parent.
  // Returns an invalid handle if none.
  
  TreeModelIterC TreeModelIterBodyC::Parent() {
    TreeModelIterC ret;
    if(!gtk_tree_model_iter_parent (model,ret.TreeIter(),treeIter))
      ret.Invalidate();
    return ret;
  }
  
  //: Create a copy of the iterator.
  
  TreeModelIterC TreeModelIterBodyC::Copy() {
    return TreeModelIterC(model,gtk_tree_iter_copy (treeIter),true);
  }

  
  //:----------------------------------------------------------------------------
  
  //: Constructor.
  
  TreeModelPathBodyC::TreeModelPathBodyC() 
    : treePath(0),
      canfree(true)
  { treePath = gtk_tree_path_new (); }
  
  //: Constructor.
  
  TreeModelPathBodyC::TreeModelPathBodyC(GtkTreePath *ntreePath,bool nCanFree)
    : treePath(ntreePath),
      canfree(nCanFree)
  {}
    
  //: Destructor.
  
  TreeModelPathBodyC::~TreeModelPathBodyC() { 
    if(canfree && treePath != 0) 
      gtk_tree_path_free (treePath);
  }

  //: Path as text.
  
  StringC TreeModelPathBodyC::Text() const {
    char *str = gtk_tree_path_to_string(treePath);
    StringC ret(str);
    g_free(str);
    return ret;
  }

  //:----------------------------------------------------------------------------
  
  //"row-changed"
  static void handle_row_changed(GtkTreeModel *treemodel,
				 GtkTreePath *arg1,
				 GtkTreeIter *arg2,
				 gpointer user_data) {
    TreeModelPathC path(arg1,false);
    TreeModelIterC row(arg2,false);
    (*((Signal2C<TreeModelPathC,TreeModelIterC> *) user_data))(path,row);
  }
  
  //"row-deleted"
  static void handle_row_deleted(GtkTreeModel *treemodel,
				 GtkTreePath *arg1,
				 gpointer user_data) {
    TreeModelPathC path(arg1,false);
    TreeModelIterC row;
    (*((Signal2C<TreeModelPathC,TreeModelIterC> *) user_data))(path,row);
  }
  
  //"row-has-child-toggled"
  static void handle_row_has_child_toggled(GtkTreeModel *treemodel,
					   GtkTreePath *arg1,
					   GtkTreeIter *arg2,
					   gpointer user_data) {
    TreeModelPathC path(arg1,false);
    TreeModelIterC row(arg2,false);
    (*((Signal2C<TreeModelPathC,TreeModelIterC> *) user_data))(path,row);
  }
  
  //"row-inserted"
  static void handle_row_inserted(GtkTreeModel *treemodel,
				  GtkTreePath *arg1,
				  GtkTreeIter *arg2,
				  gpointer user_data) {
    TreeModelPathC path(arg1,false);
    TreeModelIterC row(arg2,false);
    (*((Signal2C<TreeModelPathC,TreeModelIterC> *) user_data))(path,row);
  }
  
  //"rows-reordered"
  static void handle_rows_reordered(GtkTreeModel *treemodel,
				   GtkTreePath *arg1,
				   GtkTreeIter *arg2,
				   gpointer arg3,
				   gpointer user_data) {
    
    TreeModelPathC path(arg1,false);
    TreeModelIterC row(arg2,false);
    (*((Signal2C<TreeModelPathC,TreeModelIterC> *) user_data))(path,row);
  }
  
  
  //:----------------------------------------------------------------------------
    
  //: Constructor.
  
  TreeModelBodyC::TreeModelBodyC()
    : model(0)
  {}
  
  //: Constructor from a list of types.
  
  TreeModelBodyC::TreeModelBodyC(const SArray1dC<AttributeTypeC> &ncolTypes)
    : model(0),
      colTypes(ncolTypes)
  {}
  

  //: Destructor.
  
  TreeModelBodyC::~TreeModelBodyC()
  {}
  

  //: Append a row.
  
  bool TreeModelBodyC::AppendRow(TreeModelIterC &rowHandle) {
    RavlAssert(0);
    return false;
  }

  //: Delete a row.
  
  bool TreeModelBodyC::DeleteRow(TreeModelIterC &rowHandle) {
    RavlAssert(0);
    return false;    
  }

  //: Look up column number of named column.
  
  UIntT TreeModelBodyC::ColNumber(const StringC &name) const {
    
    for(SArray1dIterC<AttributeTypeC> it(colTypes);it;it++)
      if(it->Name() == name)
	return it.Index().V();
    return ((UIntT) -1);
  }

  //: Create the widget.
  
  bool TreeModelBodyC::Create() {
    // Connect signals...
    for(HashIterC<StringC,Signal2C<TreeModelPathC,TreeModelIterC> > it(signals);it;it++)
      ConnectUp(it.Key());
    return true;
  }
  
  //: Create a new signal.
  
  void TreeModelBodyC::ConnectUp(StringC name) {
    int id;
    //, "row-deleted","row-has-child-toggled","row-inserted","rows-reordered"
    Signal2C<TreeModelPathC,TreeModelIterC> &ret =  signals[name];   
    if(name == "row-changed") {
      id = g_signal_connect (model, name,G_CALLBACK (handle_row_changed),&ret);
      return;
    }
    if(name == "row-deleted") {
      id = g_signal_connect (model, name,G_CALLBACK (handle_row_deleted),&ret);
      return;
    }
    if(name == "row-has-child-toggled") {
      id = g_signal_connect (model, name,G_CALLBACK (handle_row_has_child_toggled),&ret);
      return;
    }
    if(name == "row-inserted") {
      id = g_signal_connect (model, name,G_CALLBACK (handle_row_inserted),&ret);
      return;
    }
    if(name == "rows-reordered") {
      id = g_signal_connect (model, name,G_CALLBACK (handle_rows_reordered),&ret);
      return;
    }
    RavlAssertMsg(0,"Unknown signal type. ");    
  }
  
  
  //: Set int value.
  
  bool TreeModelBodyC::GetValue(TreeModelIterC &rowIter,IntT col, IntT &value) {
    gtk_tree_model_get(model,rowIter.TreeIter(),col,&value,-1);
    return true;
  }
  
  //: Set bool value. 
  
  bool TreeModelBodyC::GetValue(TreeModelIterC &rowIter,IntT col, bool &value) {
    int tmp;
    gtk_tree_model_get(model,rowIter.TreeIter(),col,&tmp,-1);
    value = tmp != 0;
    return true;
  }
  
  //: Set bool value.
  
  bool TreeModelBodyC::GetValue(TreeModelIterC &rowIter,IntT col, StringC &value) {
    guchar *text;
    gtk_tree_model_get(model,rowIter.TreeIter(),col,&text,-1);
    value = StringC((char *) text);
    g_free(text);
    return true;
  }
  
  //: Set bool value.
  
  bool TreeModelBodyC::GetValue(TreeModelIterC &rowIter,IntT col, PixbufC &value) {
    RavlAssertMsg(0,"TreeModelBodyC::GetValue(), Not implemented.");
    return true;
  }


  //: Access tree signal.
  // Where name is one of "row-changed", "row-deleted","row-has-child-toggled","row-inserted","rows-reordered"
  
  Signal2C<TreeModelPathC,TreeModelIterC> &TreeModelBodyC::Signal(const char *nname) {
    Signal2C<TreeModelPathC,TreeModelIterC> *ret;
    StringC name(nname);
    if((ret = signals.Lookup(name)) != 0)
      return *ret;
    if(name == "row-changed" || name == "row-deleted"  || name == "row-has-child-toggled" || name == "row-inserted" || name == "rows-reordered") {
      TreeModelIterC tmp2;
      TreeModelPathC tmp1; 
      signals[name] = Signal2C<TreeModelPathC,TreeModelIterC>(tmp1,tmp2);
      ret = &signals[name];
    } else {
      cerr << "TreeModelBodyC::Signal(), WARNING: Unknown signal '" << nname << "'\n";
      RavlAssert(0);
    }
    if(model != 0)
      ConnectUp(name);
    return *ret;
  }

}

#endif
