// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI
//! author="Charles Galambos"
//! date="23/9/2003"

#include "Ravl/GUI/TreeView.hh"

#if RAVL_USE_GTK2

#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Pixmap.hh"
#include "Ravl/Threads/Signal2.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/HashIter.hh"

#include  <gtk/gtk.h>


namespace RavlGUIN {

  //:---------------------------------------------------------------------------------
  
  //: Default constructor.
  
  TreeViewColumnC::TreeViewColumnC()
    : renderer(0),
      column(0),
      treeViewBody(0)
  {}
  
  //:---------------------------------------------------------------------------------

  static void tree_view_toggle_cb(GtkCellRendererToggle *cellrenderertoggle,gchar *arg1,gpointer treeCol) {
    //cerr << "tree_view_toggle(), Called. \n";
    Signal1C<TreeModelIterC> sig = ((TreeViewColumnC *) treeCol)->SignalChanged();
    RavlAssert(sig.IsValid());
    RavlAssert(((TreeViewColumnC *) treeCol)->TreeBody() != 0);
    TreeModelIterC iter = ((TreeViewColumnC *) treeCol)->TreeBody()->Path2Iter(arg1);
    sig(iter);
  }
  
  static void tree_view_edit_cb(GtkCellRendererToggle *cellrenderertoggle,gchar *arg1,gchar *arg2,gpointer treeCol) {
    //cerr << "tree_view_edit(), Called. \n";
    Signal2C<TreeModelIterC,StringC> sig = ((TreeViewColumnC *) treeCol)->SignalChanged();
    RavlAssert(sig.IsValid());
    RavlAssert(((TreeViewColumnC *) treeCol)->TreeBody() != 0);
    TreeModelIterC iter = ((TreeViewColumnC *) treeCol)->TreeBody()->Path2Iter(arg1);
    sig(iter,StringC(arg2));
  }
  
  static void tree_selection_changed_cb (GtkTreeSelection *selection, gpointer obj) {
    TreeViewBodyC *bod = (TreeViewBodyC *) obj;
    GtkTreeModel *model;
    TreeModelIterC rowIter;
    DListC<TreeModelIterC> ret;
    if (gtk_tree_selection_get_selected (selection, &model, rowIter.TreeIter()))
      ret.InsLast(rowIter);
    bod->SelectionChanged()(ret);
  }

  static const StringC attrText("text");
  static const StringC attrPixbuf("pixbuf");
  static const StringC attrActive("active");
  
  
  //: Constructor.
  
  TreeViewBodyC::TreeViewBodyC(const TreeModelC &tm,const DListC<StringC> &ndisplayColumns) 
    : treeModel(tm),
      selection(0),
      selectionChanged(DListC<TreeModelIterC>())
  {
    UIntT nCols = ndisplayColumns.Size();
    DListC<StringC> dispList = ndisplayColumns;
    if(nCols == 0) {
      dispList = DListC<StringC>(); // Don't modify the input list.
      nCols = treeModel.Cols();
      for(UIntT i = 0;i < nCols;i++)
	dispList.InsLast(treeModel.ColumnType(i).Name());
    }
    //cerr << "TreeViewBodyC::TreeViewBodyC(), Called. " << nCols << "\n";
    displayColumns = SArray1dC<TreeViewColumnC>(dispList.Size());
    SArray1dIterC<TreeViewColumnC> ait(displayColumns);
    for(DLIterC<StringC> it(dispList);it;it++,ait++) {
      UIntT sourceCol = treeModel.ColNumber(*it);
      if(sourceCol == ((UIntT) -1)) {
	cerr << "Unknown column '" << *it << "'\n";
	continue;
      }
      
      AttributeTypeC colType = treeModel.ColumnType(sourceCol);
      StringC renderType;
      ait->Name(*it);
      switch(colType.ValueType()) {
      case AVT_Bool: 
	renderType ="bool";
	ait->Attributes()[attrActive] = Tuple2C<StringC,bool>(*it,true);
	break;
      case AVT_ByteRGBImage: 
	renderType ="pixbuf";
	ait->Attributes()[attrPixbuf] = Tuple2C<StringC,bool>(*it,true);
	break;
      case AVT_String:  
      case AVT_Int: 
      case AVT_Real:
      case AVT_Enum: 
	renderType ="text";
	ait->Attributes()[attrText] = Tuple2C<StringC,bool>(*it,true);
	break;
      case AVT_Abstract:
      case AVT_None:
      case AVT_Invalid:
	break;
      }
      ait->RenderType(renderType);
      //cerr << "Setting '" << ait->Name() << "' to render type '" << ait->RenderType() << "'\n";
    }
  }
  
  //: Constructor.
  
  TreeViewBodyC::TreeViewBodyC(const TreeModelC &tm,const SArray1dC<TreeViewColumnC> &displayColumns) 
    : treeModel(tm),
      selection(0),
      selectionChanged(DListC<TreeModelIterC>()),
      displayColumns(displayColumns)
  {}
  
  //: Default constructor.
  
  TreeViewBodyC::TreeViewBodyC()
    : selection(0),
      selectionChanged(DListC<TreeModelIterC>())
  {}

  //: Set an attribute for a column
  
  bool TreeViewBodyC::SetAttribute(UIntT colNum,const StringC &key,const StringC &value,bool proxy) {
    displayColumns[colNum].Attributes()[key] = Tuple2C<StringC,bool>(value,proxy);
    return true;
  }
  
  //: Create widget.
  
  bool TreeViewBodyC::Create() {
    if(widget != 0)
      return true; // Already constructed.
    RavlAssert(treeModel.IsValid());
    treeModel.Create();
    
    widget = gtk_tree_view_new_with_model(treeModel.TreeModel());

    // Build view 
    
    UIntT cols = displayColumns.Size();
    if(cols == 0) 
      displayColumns = SArray1dC<TreeViewColumnC>(treeModel.Cols());
    //cerr << "Cols=" << cols << " treeModel.Cols()= " << treeModel.Cols() << "\n";
    
    UIntT i = 0;
    for(SArray1dIterC<TreeViewColumnC> it(displayColumns);it;it++,i++) {
      GtkCellRenderer *renderer = 0;
      GtkTreeViewColumn *column = 0;
      IntT col_offset = 0;
      
      if(it->RenderType() == "bool") {
	renderer = gtk_cell_renderer_toggle_new (); 
	// sourceCol = treeModel.ColNumber(it->Attributes()["active"]);
	col_offset = gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (widget),
								  -1, it->Name(),renderer,NULL);
	if(it->SignalChanged().IsValid()) {
	  g_signal_connect (G_OBJECT (renderer), "toggled",
			    G_CALLBACK (tree_view_toggle_cb),
			    &(*it));
	  it->TreeBody(this);
	}
      } else if( it->RenderType() == "text") {
	renderer = gtk_cell_renderer_text_new ();
	// sourceCol = treeModel.ColNumber(it->Attributes()["text"]); 
	col_offset = gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (widget),
								  -1, it->Name(),renderer,NULL); 
	
	if(it->SignalChanged().IsValid()) {
	  g_signal_connect (G_OBJECT (renderer), "edited",
			    G_CALLBACK (tree_view_edit_cb),
			    &(*it));
	  it->TreeBody(this);
	}
      } else if( it->RenderType() == "pixbuf") {
	renderer = gtk_cell_renderer_pixbuf_new ();
	col_offset = gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (widget),
								  -1, it->Name(),renderer,NULL);
      } else {
	cerr << "Unknown rendered type '" << it->RenderType() << "'\n";
	RavlAssert(0);
      }
      
      column = gtk_tree_view_get_column (GTK_TREE_VIEW (widget), col_offset - 1);
      
      // Setup attributes.
      for(HashIterC<StringC,Tuple2C<StringC,bool> > ait(it->Attributes());ait;ait++) {
	Tuple2C<StringC,bool> &at = ait.Data();
	if(at.Data2()) { // Proxy ?
	  UIntT sourceCol = treeModel.ColNumber(ait.Data().Data1());
	  if(sourceCol == ((UIntT) -1))
	    cerr << "Failed to find column '" << ait.Data() << "' \n";
	  gtk_tree_view_column_add_attribute(column,renderer,ait.Key(),sourceCol);
	} else {
	  //cerr << "Setting attribute '" << ait.Key() << "' to '" << at.Data1() << "'\n";
	  if(ait.Key() == "editable" || ait.Key() == "activatable") {
	    gboolean val = (at.Data1() == "1") ? 1 : 0;
	    g_object_set(G_OBJECT (renderer), ait.Key(),val,0);
	  }
	  // Enable sorting
	  else if (ait.Key() == "sortable") {
	    gtk_tree_view_column_set_sort_column_id(GTK_TREE_VIEW_COLUMN (column), col_offset-1);
	  }
	  // Enable column reordering
	  else if (ait.Key() == "reorderable") {
	    gtk_tree_view_column_set_reorderable(GTK_TREE_VIEW_COLUMN (column), true);
	  }	  
	  // Enable column resizing
	  else if (ait.Key() == "resizable") {
	    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN (column), true);
	  }	  
	}
      }
      
      //g_object_set (G_OBJECT (renderer), "xalign", 0.0, NULL);
      //gtk_tree_view_column_set_clickable (GTK_TREE_VIEW_COLUMN (column), TRUE);

  
    }
    
    // Setup selection
    
    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (widget));
    gtk_tree_selection_set_mode (selection, GTK_SELECTION_BROWSE);
    g_signal_connect (G_OBJECT (selection), "changed",
		      G_CALLBACK (tree_selection_changed_cb),
		      this);
    
    // Finalise widget
    
    ConnectSignals();
    return true;
  }

  //: Access changed signal for a column
  
  Signal0C &TreeViewBodyC::ChangedSignal(UIntT colNum) {
    TreeViewColumnC &col = displayColumns[colNum];
    Signal0C &sig = col.SignalChanged();
    if(!sig.IsValid()) {
      if(col.RenderType() == "bool") {	
	sig = Signal1C<TreeModelIterC>(TreeModelIterC());
      } else if(col.RenderType() == "text") {
	sig = Signal2C<TreeModelIterC,StringC>(TreeModelIterC(),StringC(""));
      }
    }
    return sig;
  }

  //: Get list of selected rows.
  
  DListC<TreeModelIterC> TreeViewBodyC::GUISelected() {
    DListC<TreeModelIterC> ret;
    if(selection == 0)
      return ret; // Not created yet!.
    GtkTreeModel *model;
    TreeModelIterC rowIter;
    if (gtk_tree_selection_get_selected (selection, &model, rowIter.TreeIter()))
      ret.InsLast(rowIter);
    return ret;
  }


  //: Sort treeview by column colNum.
  
  void TreeViewBodyC::Sort(UIntT colNum, bool bAscending) {
    Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUISort,colNum,bAscending));
  }

  //: Sort treeview by column colNum.
  // GUI thread only
  
  bool TreeViewBodyC::GUISort(UIntT colNum, bool bAscending) {
    // Check validity of widget
    if(widget == 0)
      Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUISort,colNum,bAscending));
    // Set sorting
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(treeModel.TreeModel()), colNum,
					 bAscending ? GTK_SORT_ASCENDING : GTK_SORT_DESCENDING);

    return true;
  }



}


#endif
