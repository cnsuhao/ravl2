// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_TREEMODEL_HEADER
#define RAVLGUI_TREEMODEL_HEADER 1
//! author="Charles Galambos"
//! rcsid="$Id$"
//! docentry="Ravl.GUI.Control"
//! lib=RavlGUI
//! example=exTreeStore.cc

#include "Ravl/config.h"

#if RAVL_USE_GTK2

#include "Ravl/GUI/Widget.hh"
#include "Ravl/DP/AttributeType.hh"

extern "C" {
  typedef struct _GtkTreeModel        GtkTreeModel; 
  typedef struct _GtkTreeIter         GtkTreeIter;
}

namespace RavlGUIN {
  
  //! userlevel=Develop
  //: Handle to row in tree model.
  // Available on GTK+-2.0 and above only.
  
  class TreeModelRowBodyC 
    : public RCBodyC
  {
  public:
    TreeModelRowBodyC();
    //: Constructor.
    
    ~TreeModelRowBodyC();
    //: Destructor.
    
    GtkTreeIter *TreeIter()
    { return treeIter; }
    //: Access tree store.
    
  protected:
    GtkTreeIter *treeIter;
  };
  
  //! userlevel=Normal
  //: Handle to row in tree model.
  // Available on GTK+-2.0 and above only.
  
  class TreeModelRowC 
    : public RCHandleC<TreeModelRowBodyC>
  {
  public:
    TreeModelRowC()
      : RCHandleC<TreeModelRowBodyC>(*new TreeModelRowBodyC())
    {}
    //: Default constructor.
    
    GtkTreeIter *TreeIter()
    { return Body().TreeIter(); }
    //: Access tree store.
    
  };

  //! userlevel=Develop
  //: List store body.
  // Available on GTK+-2.0 and above only.
  
  class TreeModelBodyC
    : public RCBodyVC
  {
  public:
    TreeModelBodyC();
    //: Constructor.
    
    TreeModelBodyC(const SArray1dC<AttributeTypeC> &ncolTypes);
    //: Constructor.
    
    ~TreeModelBodyC();
    //: Destructor.
    
    virtual bool Create();
    //: Create the widget.
    
    GtkTreeModel *TreeModel()
    { return model; }
    //: Access tree model.
    
    AttributeValueTypeT ColumnValueType(UIntT col) const
    { return colTypes[col].ValueType(); }
    //: Get the type of a given column.
    
    AttributeTypeC ColumnType(UIntT col) const
    { return colTypes[col] ; }
    //: Access column type info.
    
    UIntT Cols() const
    { return colTypes.Size(); }
    //: Access the number of columns .
    
    virtual bool AppendRow(TreeModelRowC &rowHandle);
    //: Append a row.
    
  protected:
    GtkTreeModel        *model;
    SArray1dC<AttributeTypeC> colTypes;
    
  };
  
  //! userlevel=Normal
  //: List Store
  // Available on GTK+-2.0 and above only.
  
  class TreeModelC
    : public RCHandleC<TreeModelBodyC>
  {
  public:
    TreeModelC()
    {}
    //: Default constructor
    // Creates an invalid handle.
    
  protected:
    TreeModelC(TreeModelBodyC &bod)
      : RCHandleC<TreeModelBodyC>(bod)
    {}
    //: Body constructor.
    
    TreeModelBodyC &Body()
    { return RCHandleC<TreeModelBodyC>::Body(); }
    //: Access body.
    
    const TreeModelBodyC &Body() const
    { return RCHandleC<TreeModelBodyC>::Body(); }
    //: Access body.
    
  public:
    bool Create()
    { return Body().Create(); }
    //: Create the model
    
    GtkTreeModel *TreeModel()
    { return Body().TreeModel(); }
    //: Access tree model.
    
    AttributeValueTypeT ColumnValueType(UIntT col) const
    { return Body().ColumnValueType(col); }
    //: Get the type of a given column.
    
    AttributeTypeC ColumnType(UIntT col) const
    { return Body().ColumnType(col) ; }
    //: Access column type info.
    
    UIntT Cols() const
    { return Body().Cols(); }
    //: Access the number of columns .
    
    bool AppendRow(TreeModelRowC &rowHandle)
    { return Body().AppendRow(rowHandle); }
    //: Append a row.
    
    
  };
  
}

#endif
#endif
