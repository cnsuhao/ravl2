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

#include "Ravl/config.h"

#if RAVL_USE_GTK2

#include "Ravl/GUI/Widget.hh"
#include "Ravl/GUI/TreeModel.hh"

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
    TreeViewBodyC(const TreeModelC &tm);
    //: Constructor.
    
    virtual bool Create();
    //: Create widget.
    
    
  protected:
    TreeModelC treeModel;
    GtkTreeSelection *selection;
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

    TreeViewC(const TreeModelC &treeModel)
      : WidgetC(*new TreeViewBodyC(treeModel))
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
    
  };
  
}

#endif
#endif
