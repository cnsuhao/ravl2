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

#include "Ravl/GUI/Pixmap.hh"

#include  <gtk/gtk.h>


namespace RavlGUIN {
  
  static void tree_selection_changed_cb (GtkTreeSelection *selection, gpointer obj) {
    TreeViewBodyC *bod = (TreeViewBodyC *) obj;
    GtkTreeModel *model;
    TreeModelRowC rowIter;
    DListC<TreeModelRowC> ret;
    if (gtk_tree_selection_get_selected (selection, &model, rowIter.TreeIter()))
      ret.InsLast(rowIter);
    bod->SelectionChanged()(ret);
  }
  
  //: Constructor.
  
  TreeViewBodyC::TreeViewBodyC(const TreeModelC &tm,const DListC<StringC> &ndisplayColumns) 
    : treeModel(tm),
      selection(0),
      selectionChanged(DListC<TreeModelRowC>()),
      displayColumns(ndisplayColumns)
  {}
  
  //: Create widget.
  
  bool TreeViewBodyC::Create() {
    if(widget != 0)
      return true; // Already constructed.
    RavlAssert(treeModel.IsValid());
    treeModel.Create();
    
    widget = gtk_tree_view_new_with_model(treeModel.TreeModel());

    // Build view 
    
    UIntT cols = displayColumns.Size();
    UIntT i = 0;
    DLIterC<StringC> it(displayColumns);
    if(cols == 0) 
      cols = treeModel.Cols();
    //cerr << "Cols=" << cols << " treeModel.Cols()= " << treeModel.Cols() << "\n";
    for(i = 0;i < cols;i++) {
      GtkCellRenderer *renderer = 0;
      GtkTreeViewColumn *column = 0;
      IntT col_offset = 0;
      UIntT sourceCol = i;
      if(it.IsElm()) {
	sourceCol = treeModel.ColNumber(*it);
	//	cerr << "SourceCol=" << sourceCol << "\n";
	if(sourceCol == ((UIntT) -1)) {
	  cerr << "WARNING: Unknown source column '" << *it << "' \n";
	  continue;
	}
	it++;
      }
      
      AttributeTypeC colType = treeModel.ColumnType(i);
	
      /* column for holiday names */
      switch(colType.ValueType()) {
      case AVT_Bool: 
	renderer = gtk_cell_renderer_toggle_new (); 
	col_offset = gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (widget),
								  -1, colType.Name(),renderer, 
								  "active",sourceCol,NULL);
	break;
      case AVT_String: 
	renderer = gtk_cell_renderer_text_new (); 
	col_offset = gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (widget),
								  -1, colType.Name(),renderer, 
								  "text",sourceCol,NULL);
	break;
      case AVT_Int: {
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (widget),
						     -1, colType.Name(), renderer,
						     "text", sourceCol,
						     NULL);
#if 0
	g_signal_connect (renderer, "edited",
			  G_CALLBACK (cell_edited), model);
	g_object_set_data (G_OBJECT (renderer), "column", (gint *)COLUMN_NUMBER);
#endif
      } break;
      case AVT_ByteRGBImage: {
	//cerr << "Setting up pixbuf renderer. " << i << "\n";
	renderer = gtk_cell_renderer_pixbuf_new ();
	col_offset = gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (widget),
								  -1, colType.Name(),renderer, 
								  "pixbuf",sourceCol,NULL);
      } break;
      case AVT_Real:
      case AVT_Enum:    
      case AVT_Abstract:
      case AVT_None:
      case AVT_Invalid:
	break;
      }
      
      //g_object_set (G_OBJECT (renderer), "xalign", 0.0, NULL);
      column = gtk_tree_view_get_column (GTK_TREE_VIEW (widget), col_offset - 1);
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

  //: Get list of selected rows.
  
  DListC<TreeModelRowC> TreeViewBodyC::GUISelected() {
    DListC<TreeModelRowC> ret;
    if(selection == 0)
      return ret; // Not created yet!.
    GtkTreeModel *model;
    TreeModelRowC rowIter;
    if (gtk_tree_selection_get_selected (selection, &model, rowIter.TreeIter()))
      ret.InsLast(rowIter);
    return ret;
  }

}

#endif
