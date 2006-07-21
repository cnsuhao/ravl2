// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/ListStore.cc"

#include "Ravl/GUI/ListStore.hh"


#include "Ravl/SArray1dIter2.hh"
#include <gtk/gtk.h>

namespace RavlGUIN {
  
  extern GType Ravl2GTKType(AttributeValueTypeT vtype);
  
  //: Constructor.
  
  ListStoreBodyC::ListStoreBodyC()
  {}
  
  //: Create the widget.
  
  bool ListStoreBodyC::Create() {
    if(model != 0)
      return true;
    
    SArray1dC<GType> types(colTypes.Size());
    for(SArray1dIter2C<GType,AttributeTypeC> it(types,colTypes);it;it++)
      it.Data1() = Ravl2GTKType(it.Data2().ValueType());
    model = GTK_TREE_MODEL(gtk_list_store_newv(colTypes.Size(),&(types[0])));
    
    return true;
  }

}

