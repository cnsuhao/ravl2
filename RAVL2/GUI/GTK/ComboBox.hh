// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_COMBOBOX_HEADER
#define RAVLGUI_COMBOBOX_HEADER
//! docentry="Ravl.API.Graphics.GTK.Control"
//! author="Charles Galambos"
//! date="21/04/2008"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/GUI/TreeStore.hh"

namespace RavlGUIN {
  
  //! userlevel=Develop
  //: Combo box body.
  
  class ComboBoxBodyC
    : public WidgetBodyC
  {
  public:
    ComboBoxBodyC();
    //: Constructor
    
    ComboBoxBodyC(TreeModelC &treeModel);
    //: Constructor
    
    TreeModelIterC GUISelection();
    //: Access model iterator for the current selection.
    
    bool GUISetSelection(TreeModelIterC &selection);
    //: Set the current selection
    
    IntT GUIGetSelectionIndex();
    //: Get index of active selection.
    // A value of -1 indicates no active selection.
    
    bool GUISetSelectionIndex(IntT selectionIndex);
    //: Get index of active selection.
    // A value of -1 indicates no active selection.
    
  protected:
    void SetTreeModel(TreeModelC &treeModel);
    //: Set the tree model to use.
    // This can only be changed before the box is 'Created'.
    
    virtual bool Create();
    //: Create the widget.
    
    virtual bool Create(GtkWidget *widget);
    //: Create with a widget supplied from elsewhere.
    
    virtual bool CommonCreate(GtkWidget *widget);
    //: Create with a widget possibly supplied from elsewhere.
    
    TreeModelC m_treeModel; //: Tree store for options.
  };
  

  //! userlevel=Normal
  //: Combo box.
  // <img src="../../../html/combo-box.png"><br>
  // Uses the <a href="RavlGUIN.TreeStoreC.html">TreeStoreC</a> tree model for entries
  
  class ComboBoxC
    : public WidgetC
  {
  public:
    ComboBoxC()
    {}
    //: Default constructor
    
    ComboBoxC(TreeStoreC &treeStore)
      : WidgetC(new ComboBoxBodyC(treeStore))
    {}
    //: Constructor
    
  protected:
    ComboBoxC(ComboBoxBodyC &body)
      : WidgetC(body)
    {}
    //: Body Constructor
    
    ComboBoxC(const ComboBoxBodyC *body)
      : WidgetC(body)
    {}
    //: Body Constructor
    
    ComboBoxBodyC &Body()
    { return dynamic_cast<ComboBoxBodyC &>(WidgetC::Body()); }
    //: Body access.
    
    const ComboBoxBodyC &Body() const
    { return dynamic_cast<const ComboBoxBodyC &>(WidgetC::Body()); }
    //: Body access.

  public:
    TreeModelIterC GUISelection()
    { return Body().GUISelection(); }
    //: Access model iterator for the current selection.
    
    bool GUISetSelection(TreeModelIterC &selection)
    { return Body().GUISetSelection(selection); }
    //: Set the current selection

    IntT GUIGetSelectionIndex()
    { return Body().GUIGetSelectionIndex(); }
    //: Get index of active selection.
    // A value of -1 indicates no active selection.
    
    bool GUISetSelectionIndex(IntT selectionIndex)
    { return Body().GUISetSelectionIndex(selectionIndex); }
    //: Get index of active selection.
    // A value of -1 indicates no active selection.
    
  };

}

#endif
