// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_LISTSTORE_HEADER
#define RAVLGUI_LISTSTORE_HEADER 1
//! docentry="Ravl.GUI.Control"
//! author="Charles Galambos"
//! example=exTreeStore.cc
//! lib=RavlGUI
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/ListStore.hh"

#include "Ravl/config.h"

#if RAVL_USE_GTK2

#include "Ravl/GUI/TreeModel.hh"

namespace RavlGUIN {
  
  //! userlevel=Develop
  //: List store body.
  // Available on GTK+-2.0 and above only.
  
  class ListStoreBodyC
    : public TreeModelBodyC
  {
  public:
    ListStoreBodyC();
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
  protected:
    
  };
  
  //! userlevel=Normal
  //: List Store
  // Available on GTK+-2.0 and above only.
  
  class ListStoreC
    : public TreeModelC
  {
  public:
    ListStoreC()
    {}
    //: Default constructor
    // Creates an invalid handle.
    
  protected:
    ListStoreC(ListStoreBodyC &bod)
      : TreeModelC(bod)
    {}
    //: Body constructor.
    
    ListStoreBodyC &Body()
    { return static_cast<ListStoreBodyC &>(TreeModelC::Body()); }
    //: Access body.
    
    const ListStoreBodyC &Body() const
    { return static_cast<const ListStoreBodyC &>(TreeModelC::Body()); }
    //: Access body.
    
  public:
    
  };
  
}
#else 
#warning ListStoreC is NOT supported (requires gtk2 ) 
#endif
#endif
