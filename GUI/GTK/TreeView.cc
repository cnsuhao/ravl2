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
#include "Ravl/StringList.hh"

#include  <gtk/gtk.h>


namespace RavlGUIN {

  //:---------------------------------------------------------------------------------
  
  //: Default constructor.
  
  TreeViewColumnC::TreeViewColumnC()
    : renderers(1),
      column(0)
  {}
  
  //:---------------------------------------------------------------------------------

  static void tree_view_toggle_cb(GtkCellRendererToggle *cellrenderertoggle,gchar *arg1,gpointer treeCol) {
    //cerr << "tree_view_toggle(), Called. \n";
    Signal1C<TreeModelIterC> sig = ((TreeViewColumnRendererC *) treeCol)->SignalChanged();
    RavlAssert(sig.IsValid());
    RavlAssert(((TreeViewColumnRendererC *) treeCol)->TreeBody() != 0);
    TreeModelIterC iter = ((TreeViewColumnRendererC *) treeCol)->TreeBody()->Path2Iter(arg1);
    sig(iter);
  }
  
  static void tree_view_edit_cb(GtkCellRendererToggle *cellrenderertoggle,gchar *arg1,gchar *arg2,gpointer treeCol) {
    //cerr << "tree_view_edit(), Called. \n";
    Signal2C<TreeModelIterC,StringC> sig = ((TreeViewColumnRendererC *) treeCol)->SignalChanged();
    RavlAssert(sig.IsValid());
    RavlAssert(((TreeViewColumnRendererC *) treeCol)->TreeBody() != 0);
    TreeModelIterC iter = ((TreeViewColumnRendererC *) treeCol)->TreeBody()->Path2Iter(arg1);
    sig(iter,StringC(arg2));
  }
  
  static void tree_selection_changed_cb (GtkTreeSelection *selection, gpointer obj) {
    TreeViewBodyC *bod = (TreeViewBodyC *) obj;
    // Filter first selection event
    if (bod->FilterFirstSelections()) {
      bod->GUIDeselectAll();
      return;
    }
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
  
  TreeViewBodyC::TreeViewBodyC(const TreeModelC &tm,const DListC<StringC> &ndisplayColumns, GtkSelectionMode nselMode) 
    : treeModel(tm),
      selection(0),
      selectionChanged(DListC<TreeModelIterC>()),
      firstSelection(2),
      selMode(nselMode)
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
      StringListC subCols(*it,"|");
      UIntT noSubCols = subCols.Size();
      SArray1dC<TreeViewColumnRendererC> renderers(noSubCols);
      
      SArray1dIterC<TreeViewColumnRendererC> rit(renderers);
      
      for(DLIterC<StringC> sit(subCols);sit;sit++) {
	StringC name = *sit;
	//cerr << "Name=" << name << "\n";
	RavlAssert(!name.IsEmpty());
	char key = name[0];
	bool mainName = false;
	if(key == '@') {
	  name = name.after(0);
	  key = name[0];
	} else
	  mainName = true;
	
	if(key == '-' || key == '+') {
	  name = name.after(0);
	  rit->SetExpand(key == '+');
	}
	if(mainName)
	  ait->Name(name); // Set the name of the column
	
	UIntT sourceCol = treeModel.ColNumber(name);
	if(sourceCol == ((UIntT) -1)) {
	  cerr << "Unknown column '" << name << "'\n";
	  continue;
	}
	AttributeTypeC colType = treeModel.ColumnType(sourceCol);
	StringC renderType;
	switch(colType.ValueType()) {
	case AVT_Bool: 
	  renderType ="bool";
	  // Get value from 'active' from column '*it'
	  rit->Attributes()[attrActive] = Tuple2C<StringC,bool>(name,true);
	  break;
	case AVT_ByteRGBImage: 
	  renderType ="pixbuf";
	  // Get value from 'pixbuf' from column '*it'
	  rit->Attributes()[attrPixbuf] = Tuple2C<StringC,bool>(name,true);
	  break;
	case AVT_String:  
	case AVT_Int: 
	case AVT_Real:
	case AVT_Enum: 
	  renderType ="text";
	  // Get value from 'text' from column '*it'
	  rit->Attributes()[attrText] = Tuple2C<StringC,bool>(name,true);
	  break;
	case AVT_Abstract:
	case AVT_None:
	case AVT_Invalid:
	case AVT_Component:
	  break;
	}
	rit->SetRenderType(renderType);
	//cerr << "Setting '" << ait->Name() << "' to render type '" << ait->RenderType() << "'\n";

	rit++;
      }
      renderers = SArray1dC<TreeViewColumnRendererC>(renderers,rit.Index().V());
      ait->SetRenderers(renderers);
    }
  }
  
  //: Constructor.
  
  TreeViewBodyC::TreeViewBodyC(const TreeModelC &tm,const SArray1dC<TreeViewColumnC> &displayColumns, GtkSelectionMode nselMode) 
    : treeModel(tm),
      selection(0),
      selectionChanged(DListC<TreeModelIterC>()),
      displayColumns(displayColumns),
      firstSelection(2),
      selMode(nselMode)
  {}
  
  //: Default constructor.
  
  TreeViewBodyC::TreeViewBodyC()
    : selection(0),
      selectionChanged(DListC<TreeModelIterC>()),
      firstSelection(2)
  {}

  //: Set an attribute for a column
  
  bool TreeViewBodyC::SetAttribute(UIntT colNum,const StringC &key,const StringC &value,bool proxy) {
    displayColumns[colNum].Attributes()[key] = Tuple2C<StringC,bool>(value,proxy);
    return true;
  }
  
  //: Set an attribute for a column
  // Possible keys include: "editable", "sortable", "activateable", "foreground", "background", "reorderable", "resizable"
  
  bool TreeViewBodyC::SetAttribute(UIntT colNum,UIntT subCol,const StringC &key,const StringC &value,bool proxy) {
    displayColumns[colNum].Renderers()[subCol].Attributes()[key] = Tuple2C<StringC,bool>(value,proxy);
    return true;
  }

  //: Create with a widget supplied from elsewhere.
  
  bool TreeViewBodyC::Create(GtkWidget *nwidget) {
    widget = nwidget;
    
    // Setup tree model.
    
    RavlAssert(treeModel.IsValid());
    treeModel.Create();
    gtk_tree_view_set_model(GTK_TREE_VIEW (widget),treeModel.TreeModel());
    
    // Build view 
    
    UIntT cols = displayColumns.Size();
    if(cols == 0) 
      displayColumns = SArray1dC<TreeViewColumnC>(treeModel.Cols());
    //cerr << "Cols=" << cols << " treeModel.Cols()= " << treeModel.Cols() << "\n";
    
    UIntT i = 0;
    for(SArray1dIterC<TreeViewColumnC> it(displayColumns);it;it++,i++) {
      GtkCellRenderer *renderer = 0;
      IntT col_offset = 0;
      
      GtkTreeViewColumn *column = gtk_tree_view_column_new ();
      gtk_tree_view_column_set_title (column, it->Name());
      col_offset = gtk_tree_view_append_column (GTK_TREE_VIEW (widget),
						column);
      
      for(SArray1dIterC<TreeViewColumnRendererC> rit(it->Renderers());rit;rit++) {
	const StringC &renderType = rit->RenderType();
	
	if(renderType == "bool") { // Bool render
	  renderer = gtk_cell_renderer_toggle_new (); 
	  if(it->SignalChanged().IsValid()) {
	    g_signal_connect (G_OBJECT (renderer), "toggled",
			      G_CALLBACK (tree_view_toggle_cb),
			      &(*rit));
	    rit->TreeBody(this);
	  }
	  
	} else if( renderType == "text") {
	  renderer = gtk_cell_renderer_text_new ();
	  if(it->SignalChanged().IsValid()) {
	    g_signal_connect (G_OBJECT (renderer), "edited",
			      G_CALLBACK (tree_view_edit_cb),
			      &(*rit));
	    rit->TreeBody(this);
	  }
	  
	} else if( renderType == "pixbuf") {
	  renderer = gtk_cell_renderer_pixbuf_new ();
	  
	} else {
	  cerr << "Unknown rendered type '" << rit->RenderType() << "'\n";
	  RavlAssert(0);
	}
	
	gtk_tree_view_column_pack_start (column,
					 renderer,
					 rit->Expand());
	
	// Setup attributes.
	for(HashIterC<StringC,Tuple2C<StringC,bool> > ait(rit->Attributes());ait;ait++) {
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
      }
    }
    
    // Setup selection
    
    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (widget));
    gtk_tree_selection_set_mode (selection, selMode);
    g_signal_connect (G_OBJECT (selection), "changed",
		      G_CALLBACK (tree_selection_changed_cb),
		      this);
    
    // Finalise widget
    
    ConnectSignals();
    return true;
  }
  
  //: Create widget.
  
  bool TreeViewBodyC::Create() {
    if(widget != 0)
      return true; // Already constructed.
    return Create(gtk_tree_view_new());
  }
  
  //: Access changed signal for a column
  
  Signal0C &TreeViewBodyC::ChangedSignal(UIntT colNum,UIntT subColNo) {
    TreeViewColumnC &col = displayColumns[colNum];
    TreeViewColumnRendererC &colRender = col.Renderers()[subColNo];
    Signal0C &sig = colRender.SignalChanged();
    if(!sig.IsValid()) {
      if(colRender.RenderType() == "bool") {	
	sig = Signal1C<TreeModelIterC>(TreeModelIterC());
      } else if(colRender.RenderType() == "text") {
	sig = Signal2C<TreeModelIterC,StringC>(TreeModelIterC(),StringC(""));
      }
    }
    return sig;
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

  //: Expand to the specified path
  
  void TreeViewBodyC::Expand(TreeModelPathC path) {
    Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUIExpand,path));  
  }

  //: Expand to the specified row iterator

  void TreeViewBodyC::Expand(TreeModelIterC iter) {
    // Create path
    TreeModelPathC path(iter);
    // Expand to path    
    Expand(path);
  }


  //: Expand to the specified path
  // GUI thread only

  bool TreeViewBodyC::GUIExpand(TreeModelPathC path) {
    // Check validity of widget
    if(widget == 0)
      Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUIExpand,path));
    // Expand    
    gtk_tree_view_expand_to_path(GTK_TREE_VIEW(widget),path.TreePath());
    return true;
  }
  
  //: Is the specified path expanded?
  // GUI thread only
  
  bool TreeViewBodyC::GUIExpanded(TreeModelPathC path) {    
    // Check validity of widget
    if(widget == 0)
      return false;
    // Check status
    return gtk_tree_view_row_expanded(GTK_TREE_VIEW(widget),path.TreePath()) != 0;
  }
  
  //: Is the specified iterator expanded?
  // GUI thread only
  
  bool TreeViewBodyC::GUIExpanded(TreeModelIterC iter) {
    // Convert to path
    TreeModelPathC path(iter);
    // Check status
    return GUIExpanded(path);
  }

  //: Expand the entire tree
  
  void TreeViewBodyC::ExpandAll() {
    Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUIExpandAll));
  }
  
  //: Expand the entire tree
  // GUI thread only
  
  bool TreeViewBodyC::GUIExpandAll() {
    // Check validity of widget
    if(widget == 0)
      Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUIExpandAll));
    // Expand all
    gtk_tree_view_expand_all(GTK_TREE_VIEW(widget));
    return true;
  }
  
  //: Collapse the entire tree
  
  void TreeViewBodyC::CollapseAll() {
    Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUICollapseAll));
  }
  
  //: Collapse the entire tree
  // GUI thread only
  
  bool TreeViewBodyC::GUICollapseAll() {
    // Check validity of widget
    if(widget == 0)
      Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUICollapseAll));
    // Collapse all
    gtk_tree_view_collapse_all(GTK_TREE_VIEW(widget));
    return true;
  }

  //: Select the specified path
  
  void TreeViewBodyC::Select(TreeModelPathC path) {
    Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUISelectPath,path));  
  }

  //: Select the specified row iterator

  void TreeViewBodyC::Select(TreeModelIterC iter) {
    Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUISelectIter,iter));  
  }

  //: Select the specified path
  // GUI thread only

  bool TreeViewBodyC::GUISelectPath(TreeModelPathC path) {
    if (selection == 0)
      return false;
    gtk_tree_selection_unselect_path(selection,path.TreePath());
    return true;
  }
  
  //: Select the specified row iterator
  // GUI thread only
  
  bool TreeViewBodyC::GUISelectIter(TreeModelIterC iter) {
    if (selection == 0)
      return false;
    gtk_tree_selection_select_iter(selection,iter.TreeIter());
    return true;
  }

  //: Is the specified path selected?
  // GUI thread only
  
  bool TreeViewBodyC::GUISelectedPath(TreeModelPathC path) {
    if (selection == 0)
      return false;
    return gtk_tree_selection_path_is_selected(selection,path.TreePath()) != 0;
  }

  //: Is the specified row iterator selected?
  // GUI thread only
  
  bool TreeViewBodyC::GUISelectedIter(TreeModelIterC iter) {
    if (selection == 0)
      return false;
    return gtk_tree_selection_iter_is_selected(selection,iter.TreeIter()) != 0;
  }

  //: Get list of selected rows.
  
  DListC<TreeModelIterC> TreeViewBodyC::GUISelected() {
    DListC<TreeModelIterC> ret;
    if(selection == 0)
      return ret; // Not created yet!.

    // Get selection
    GtkTreeModel* model;
    GList* list = gtk_tree_selection_get_selected_rows(selection,&model);    
    GList* ptr = list;

    // Extract iterators
    while (ptr) {
      GtkTreePath* path(static_cast<GtkTreePath*>(ptr->data));
      TreeModelIterC iter(model,path,true);
      ret.InsLast(iter);
      gtk_tree_path_free(path);
      ptr = ptr->next;
    }

    // Free list
    g_list_free (list);

    // Done
    return ret;
  }

  //: Deselect the specified path
  void TreeViewBodyC::Deselect(TreeModelPathC path)  {
    Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUIDeselectPath,path));  
  }
  
  //: Deselect the specified row iterator
  
  void TreeViewBodyC::Deselect(TreeModelIterC iter) {
    Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUIDeselectIter,iter));
  }
  
  //: Deselect the specified path
  // GUI thread only
  
  bool TreeViewBodyC::GUIDeselectPath(TreeModelPathC path) {
    if (selection == 0)
      return false;
    gtk_tree_selection_unselect_path(selection,path.TreePath());
    return true;
  }

  //: Deselect the specified row iterator
  // GUI thread only
  
  bool TreeViewBodyC::GUIDeselectIter(TreeModelIterC iter) {
    if (selection == 0)
      return false;
    gtk_tree_selection_unselect_iter(selection,iter.TreeIter());
    return true;
  }

  //: Select all rows
  
  void TreeViewBodyC::SelectAll() {
    Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUISelectAll));
  }

  //: Select all rows
  // GUI thread only

  bool TreeViewBodyC::GUISelectAll() {
    if (selection == 0)
      return false;
    gtk_tree_selection_select_all(selection);
    return true;
  }
    
  //: Deselect all rows

  void TreeViewBodyC::DeselectAll() {
    Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUIDeselectAll));
  }
    
  //: Deselect all rows
  // GUI thread only

  bool TreeViewBodyC::GUIDeselectAll() {
    if (selection == 0)
      return false;
    gtk_tree_selection_unselect_all(selection);
    return true;
  }

  //: Select the rows between the two paths
  
  void TreeViewBodyC::SelectRange(TreeModelPathC from, TreeModelPathC to) {
    Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUISelectRange,from,to));
  }

  //: Select the rows between the two paths
  // GUI thread only
  
  bool TreeViewBodyC::GUISelectRange(TreeModelPathC from, TreeModelPathC to) {
    if (selection == 0)
      return false;
    gtk_tree_selection_select_range(selection,from.TreePath(),to.TreePath());
    return true;
  }

  //: Deselect the rows between the two paths
  
  void TreeViewBodyC::DeselectRange(TreeModelPathC from, TreeModelPathC to) {
    Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUIDeselectRange,from,to));
  }

  //: Deselect the rows between the two paths
  // GUI thread only
  
  bool TreeViewBodyC::GUIDeselectRange(TreeModelPathC from, TreeModelPathC to) {
    if (selection == 0)
      return false;
    gtk_tree_selection_unselect_range(selection,from.TreePath(),to.TreePath());
    return true;
  }

  //: Scroll the treeview to the specified path

  void TreeViewBodyC::ScrollTo(TreeModelPathC path) {
    Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUIScrollTo,path));  
  }

  //: Scroll the treeview to the specified row iterator
  
  void TreeViewBodyC::ScrollTo(TreeModelIterC iter) {
    // Create path
    TreeModelPathC path(iter);
    // Expand to path    
    ScrollTo(path);
  }

  //: Scroll the treeview to the specified path
  // GUI thread only
  
  bool TreeViewBodyC::GUIScrollTo(TreeModelPathC path) {
    // Check validity of widget
    if(widget == 0)
      Manager.Queue(Trigger(TreeViewC(*this),&TreeViewC::GUIScrollTo,path));
    // Expand
    gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(widget), path.TreePath(), NULL, true, 0, 0);
    return true;
  }

}


#endif
