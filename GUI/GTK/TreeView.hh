// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_TREEVIEW_HEADER
#define RAVLGUI_TREEVIEW_HEADER 1
//! rcsid="$Id$"
//! docentry="Ravl.GUI.Control"
//! author="Charles Galambos"
//! example=exTreeStore.cc
//! lib=RavlGUI
//! date="23/9/2003"

#include "Ravl/config.h"

#if RAVL_USE_GTK2

#include "Ravl/GUI/Widget.hh"
#include "Ravl/GUI/TreeModel.hh"
#include "Ravl/Threads/Signal1.hh"

extern "C" {
  typedef struct _GtkTreeSelection      GtkTreeSelection;
}

namespace RavlGUIN {
  
  //! userlevel=Develop
  //: Tree view widget.
  // Available on GTK+-2.0 and above only.
  
  class TreeViewBodyC
    : public WidgetBodyC
  {
  public:
    TreeViewBodyC(const TreeModelC &tm,const DListC<StringC> &displayColumns);
    //: Constructor.
    
    TreeViewBodyC();
    //: Default constructor.
    
    virtual bool Create();
    //: Create widget.
    
    TreeModelC &TreeModel()
    { return treeModel; }
    //: Access tree model.
    
    DListC<TreeModelIterC> GUISelected();
    //: Get list of selected rows.
    
    Signal1C<DListC<TreeModelIterC> > &SelectionChanged()
    { return selectionChanged; }
    //: Access selection changed signal.
    
  protected:
    TreeModelC treeModel;
    GtkTreeSelection *selection;
    Signal1C<DListC<TreeModelIterC> > selectionChanged;
    DListC<StringC> displayColumns;
  };
  
  //! userlevel=Normal
  //: Tree view widget.
  // Available on GTK+-2.0 and above only.
  
  class TreeViewC
    : public WidgetC
  {
  public:
    TreeViewC()
    {}
    //: Default constructor.
    // Creates an invalid handle.

    TreeViewC(const TreeModelC &treeModel,const DListC<StringC> &displayColumns = DListC<StringC>())
      : WidgetC(*new TreeViewBodyC(treeModel,displayColumns))
    {}
    //: Constructor.
    // Creates an invalid handle.
    
  protected:
    TreeViewC(TreeViewBodyC &bod)
      : WidgetC(bod)
    {}
    //: Body constructor.
    
    TreeViewBodyC &Body()
    { return static_cast<TreeViewBodyC &>(WidgetC::Body()); }
    //: Access body.

    const TreeViewBodyC &Body() const
    { return static_cast<const TreeViewBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
    
    TreeModelC &TreeModel()
    { return Body().TreeModel(); }
    //: Access tree model.
    
    DListC<TreeModelIterC> GUISelected()
    { return Body().GUISelected(); }
    //: Get list of selected rows.
    
    Signal1C<DListC<TreeModelIterC> > &SelectionChanged()
    { return Body().SelectionChanged(); }
    //: Access selection changed signal.
    
  };
  
}

#endif
#endif
