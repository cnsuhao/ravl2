// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Control"
//! lib=RavlGUI
//! date="23/9/2003"

#include "Ravl/GUI/TreeModel.hh"

#if RAVL_USE_GTK2

#include <gtk/gtk.h>

namespace RavlGUIN {
  
  GType Ravl2GTKType(AttributeValueTypeT vtype) {
    switch(vtype) {
    case AVT_Bool:     return G_TYPE_BOOLEAN;
    case AVT_Int:      return G_TYPE_INT;
    case AVT_Real:     return G_TYPE_FLOAT;
    case AVT_String:   return G_TYPE_STRING;
    case AVT_Enum:     return G_TYPE_ENUM;
    case AVT_Abstract: return G_TYPE_NONE;
    case AVT_ByteRGBImage: return GDK_TYPE_PIXBUF;
    case AVT_None:     return G_TYPE_NONE;
    case AVT_Invalid:  return G_TYPE_INVALID;
    }
    return G_TYPE_INVALID;
  }
  
  //:----------------------------------------------------------------------------
  
  //: Constructor.
  
  TreeModelRowBodyC::TreeModelRowBodyC() 
    : treeIter(new GtkTreeIter)
  {}
    
  //: Destructor.
  
  TreeModelRowBodyC::~TreeModelRowBodyC() 
  { delete treeIter; }


  //:----------------------------------------------------------------------------
    
  //: Constructor.
  
  TreeModelBodyC::TreeModelBodyC()
    : model(0)
  {}
  
  //: Constructor from a list of types.
  
  TreeModelBodyC::TreeModelBodyC(const SArray1dC<AttributeTypeC> &ncolTypes)
    : model(0),
      colTypes(ncolTypes)
  {}
  

  //: Destructor.
  
  TreeModelBodyC::~TreeModelBodyC()
  {}
  

  //: Append a row.
  
  bool TreeModelBodyC::AppendRow(TreeModelRowC &rowHandle) {
    RavlAssert(0);
    return false;
  }

  //: Delete a row.
  
  bool TreeModelBodyC::DeleteRow(TreeModelRowC &rowHandle) {
    RavlAssert(0);
    return false;    
  }

  //: Look up column number of named column.
  
  UIntT TreeModelBodyC::ColNumber(const StringC &name) const {
    
    for(SArray1dIterC<AttributeTypeC> it(colTypes);it;it++)
      if(it->Name() == name)
	return it.Index().V();
    return ((UIntT) -1);
  }
  
  //: Create the widget.
  
  bool TreeModelBodyC::Create() {
    return true;
  }
  
  //: Set int value.
  
  bool TreeModelBodyC::GetValue(TreeModelRowC &rowIter,IntT col, IntT &value) {
    gtk_tree_model_get(model,rowIter.TreeIter(),col,&value,-1);
    return true;
  }
  
  //: Set bool value. 
  
  bool TreeModelBodyC::GetValue(TreeModelRowC &rowIter,IntT col, bool &value) {
    int tmp;
    gtk_tree_model_get(model,rowIter.TreeIter(),col,&tmp,-1);
    value = tmp != 0;
    return true;
  }
  
  //: Set bool value.
  
  bool TreeModelBodyC::GetValue(TreeModelRowC &rowIter,IntT col, StringC &value) {
    guchar *text;
    gtk_tree_model_get(model,rowIter.TreeIter(),col,&text,-1);
    value = StringC((char *) text);
    g_free(text);
    return true;
  }
  
  //: Set bool value.
  
  bool TreeModelBodyC::GetValue(TreeModelRowC &rowIter,IntT col, PixbufC &value) {
    RavlAssertMsg(0,"TreeModelBodyC::GetValue(), Not implemented.");
    return true;
  }

}

#endif
