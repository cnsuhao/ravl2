// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_GUIFACTORY_HEADER
#define RAVL_GUIFACTORY_HEADER 1
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"
//! docentry="Ravl.Applications.VDF"
//! date="2/8/2002"
//! file="Ravl/Applications/VisualDataFlow/GUIFactory.hh"

#include "Ravl/GUI/Tree.hh"
#include "Ravl/DF/FactorySet.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/DragAndDrop.hh"
#include "Ravl/GUI/MouseEvent.hh"

namespace RavlDFN {
  using namespace RavlGUIN;
  
  //! userlevel=Develop
  //: Factory GUI.
  
  class GUIFactoryBodyC 
    : public LBoxBodyC
  {
  public:
    GUIFactoryBodyC(const FactorySetC &nFactories);
    //: Default constructor.
    
    virtual bool Create();
    //: Create the widget.
    
    bool DNDFactoryDataGet(DNDDataInfoC &info,StringC &id);
    //: Drag and drop data get.
    
    bool AddFactory(const FactoryC &factory);
    //: Add factory to display.
    
  protected:
    //HashC<UIntT, FactoryC> id2factory;
    
    FactorySetC factories;
    
    TreeC tree;
    
    HashC<StringC,TreeItemC> name2treeitem;
    HashC<StringC,TreeC> name2tree;
  };
  
  //! userlevel=Normal
  //: Factory GUI.
  
  class GUIFactoryC 
    : public LBoxC
  {
  public:
    GUIFactoryC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    GUIFactoryC(const FactorySetC &dffs)
      : LBoxC(*new GUIFactoryBodyC(dffs))
    {}
    //: Create factory widget from a factory set.
    
  protected:
    GUIFactoryBodyC &Body()
    { return static_cast<GUIFactoryBodyC &>(WidgetC::Body()); }
    //: Access body.

    const GUIFactoryBodyC &Body() const
    { return static_cast<const GUIFactoryBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
    
  };
  
}

#endif
