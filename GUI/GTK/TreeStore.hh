// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_TREESTORE_HEADER
#define RAVLGUI_TREESTORE_HEADER 1
//! author="Charles Galambos"
//! rcsid="$Id$"
//! docentry="Ravl.GUI.Control"
//! lib=RavlGUI
//! example=exTreeStore.cc
//! date="23/9/2003"

#include "Ravl/config.h"

#if RAVL_USE_GTK2

#include "Ravl/GUI/TreeModel.hh"

extern "C" {
  typedef struct _GtkTreeStore       GtkTreeStore;
}

namespace RavlGUIN {
  class PixmapC;
  
  //! userlevel=Develop
  //: List store body.
  // Available on GTK+-2.0 and above only.
  
  class TreeStoreBodyC
    : public TreeModelBodyC
  {
  public:
    TreeStoreBodyC(const SArray1dC<AttributeTypeC> &nColTypes);
    //: Constructor.
    
    ~TreeStoreBodyC();
    //: Destructor.
    
    virtual bool Create();
    //: Create the widget.
    
    bool AppendRow(TreeModelIterC &rowIter,TreeModelIterC &parentIter);
    //: Append a row.
    
    virtual bool AppendRow(TreeModelIterC &rowHandle);
    //: Append a row.
    
    virtual bool DeleteRow(TreeModelIterC &rowHandle);
    //: Delete a row.
    
    bool SetValue(TreeModelIterC &rowIter,IntT col, IntT value);
    //: Set int value.
    
    bool SetValue(TreeModelIterC &rowIter,IntT col, bool value);
    //: Set bool value.
    
    bool SetValue(TreeModelIterC &rowIter,IntT col, const StringC &value);
    //: Set bool value.
    
    bool SetValue(TreeModelIterC &rowIter,IntT col, const PixbufC &value);
    //: Set bool value.
    
  protected:
  };
  
  //! userlevel=Normal
  //: List Store
  // Available on GTK+-2.0 and above only.
  
  class TreeStoreC
    : public TreeModelC
  {
  public:
    TreeStoreC()
    {}
    //: Default constructor
    // Creates an invalid handle.

    TreeStoreC(const SArray1dC<AttributeTypeC> &nColTypes)
      : TreeModelC(*new TreeStoreBodyC(nColTypes))
    {}
    //: Constructor.
    
  protected:
    TreeStoreC(TreeStoreBodyC &bod)
      : TreeModelC(bod)
    {}
    //: Body constructor.
    
    TreeStoreBodyC &Body()
    { return static_cast<TreeStoreBodyC &>(TreeModelC::Body()); }
    //: Access body.
    
    const TreeStoreBodyC &Body() const
    { return static_cast<const TreeStoreBodyC &>(TreeModelC::Body()); }
    //: Access body.
    
  public:
    bool AppendRow(TreeModelIterC &rowHandle,TreeModelIterC &parentHandle)
    { return Body().AppendRow(rowHandle,parentHandle); }
    //: Append a row.
    
    bool AppendRow(TreeModelIterC &rowHandle)
    { return Body().AppendRow(rowHandle); }
    //: Append a row.
    
    bool SetValue(TreeModelIterC &rowIter,IntT col, IntT value) 
    { return Body().SetValue(rowIter,col,value); }
    //: Set int value.
    
    bool SetValue(TreeModelIterC &rowIter,IntT col, bool value)
    { return Body().SetValue(rowIter,col,value); }
    //: Set bool value.
    
    bool SetValue(TreeModelIterC &rowIter,IntT col, const StringC &value)
    { return Body().SetValue(rowIter,col,value); }
    //: Set bool value.
    
    bool SetValue(TreeModelIterC &rowIter,IntT col, const PixbufC &value)
    { return Body().SetValue(rowIter,col,value); }
    //: Set bool value.
        
  };
  
}
#endif

#endif
