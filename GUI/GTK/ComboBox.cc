// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/GUI/ComboBox.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {

  //: Constructor
  
  ComboBoxBodyC::ComboBoxBodyC()
  {}
  
  //: Constructor
  
  ComboBoxBodyC::ComboBoxBodyC(TreeModelC &treeModel)
    : m_treeModel(treeModel)
  {}
  
  //: Access model iterator for the current selection.
  
  TreeModelIterC ComboBoxBodyC::GUISelection() {
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");    
    TreeModelIterC iter(m_treeModel);
    if(!gtk_combo_box_get_active_iter (GTK_COMBO_BOX(widget),iter.TreeIter())) {
      // If nothing is selected invalidate the iterator.
      iter.Invalidate();
    }
    return iter;
  }
  
  //: Set the current selection
  
  bool ComboBoxBodyC::GUISetSelection(TreeModelIterC &selection) {
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");    
    RavlAssert(selection.IsValid());
    gtk_combo_box_set_active_iter (GTK_COMBO_BOX(widget),selection.TreeIter());
    return true;
  }
  
  //: Get index of active selection.
  
  IntT ComboBoxBodyC::GUIGetSelectionIndex() { 
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");    
    return gtk_combo_box_get_active (GTK_COMBO_BOX(widget)); 
  }
  
  //: Get index of active selection.
  
  bool ComboBoxBodyC::GUISetSelectionIndex(IntT selectionIndex) {
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");    
    gtk_combo_box_set_active (GTK_COMBO_BOX(widget),selectionIndex);
    return true;
  }
  
  //: Create the widget.
  
  bool ComboBoxBodyC::Create() {
    return CommonCreate(0);
  }
  
  //: Create with a widget supplied from elsewhere.
  
  bool ComboBoxBodyC::Create(GtkWidget *widget) {
    return CommonCreate(widget);
  }
  
  //: Create with a widget possibly supplied from elsewhere.
  
  bool ComboBoxBodyC::CommonCreate(GtkWidget *nwidget) {
    if(nwidget == 0) {
      if(m_treeModel.IsValid()) {
        widget = gtk_combo_box_new_with_model (m_treeModel.TreeModel());
      } else {
        widget = gtk_combo_box_new();
        if(m_treeModel.IsValid()) {
          gtk_combo_box_set_model (GTK_COMBO_BOX(widget),m_treeModel.TreeModel());
        }
      }
    } else {
      widget = nwidget;
      if(m_treeModel.IsValid()) {
        gtk_combo_box_set_model (GTK_COMBO_BOX(widget),m_treeModel.TreeModel());
      }
    }
    
    ConnectSignals();
    return true;
  }

}
