// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI
//! author="Charles Galambos"

#include "Ravl/GUI/TreeView.hh"

#if RAVL_USE_GTK2

#include  <gtk/gtk.h>

namespace RavlGUIN {

  //: Constructor.
  
  TreeViewBodyC::TreeViewBodyC(const TreeModelC &tm) 
    : treeModel(tm)
  {}
  
  //: Create widget.
  
  bool TreeViewBodyC::Create() {
    if(widget != 0)
      return true; // Already constructed.
    RavlAssert(treeModel.IsValid());
    treeModel.Create();
    
    widget = gtk_tree_view_new_with_model(treeModel.TreeModel());
    
    UIntT i = 0;
    for(i = 0;i < treeModel.Cols();i++) {
      GtkCellRenderer *renderer = 0;
      GtkTreeViewColumn *column = 0;
      IntT col_offset = 0;

      AttributeTypeC colType = treeModel.ColumnType(i);
	
      /* column for holiday names */
      switch(colType.ValueType()) {
      case AVT_Bool: 
	renderer = gtk_cell_renderer_toggle_new (); 
	col_offset = gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (widget),
								  -1, colType.Name(),renderer, 
								  "active",i,NULL);
	break;
      case AVT_String: 
	renderer = gtk_cell_renderer_text_new (); 
	col_offset = gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (widget),
								  -1, colType.Name(),renderer, 
								  "text",i,NULL);
	break;
      case AVT_Int: {
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (widget),
						     -1, colType.Name(), renderer,
						     "text", i,
						     NULL);
#if 0
	g_signal_connect (renderer, "edited",
			  G_CALLBACK (cell_edited), model);
	g_object_set_data (G_OBJECT (renderer), "column", (gint *)COLUMN_NUMBER);
#endif
      } break;
      case AVT_ByteRGBImage:
	cerr << "Setting up pixbuf renderer. \n";
	renderer = gtk_cell_renderer_pixbuf_new ();
	col_offset = gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (widget),
								  -1, colType.Name(),renderer, 
								  "pixbuf",i,NULL);
	break;
      case AVT_Real:
      case AVT_Enum:    
      case AVT_Abstract:
      case AVT_None:
      case AVT_Invalid:
	break;
      }
      
      g_object_set (G_OBJECT (renderer), "xalign", 0.0, NULL);
      column = gtk_tree_view_get_column (GTK_TREE_VIEW (widget), col_offset - 1);
      gtk_tree_view_column_set_clickable (GTK_TREE_VIEW_COLUMN (column), TRUE);
  
    }
    ConnectSignals();
    return true;
  }
}

#endif
