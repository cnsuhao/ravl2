// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlLibGlade

#include "Ravl/GUI/GladeWidget.hh"
#include "Ravl/HashIter.hh"

namespace RavlGUIN {
  
  //: Constructor
  
  GladeWidgetBodyC::GladeWidgetBodyC(const GladeXMLC &gladeXml,const StringC &widgetName) 
    : xml(gladeXml),
      name(widgetName)
  {}
  
  //: Create the widget.
  
  bool GladeWidgetBodyC::Create() {
    if(widget != 0)
      return true;
    widget = xml.Widget(name);
    for(HashIterC<StringC,WidgetC> it(children);it;it++) {
      GtkWidget *childWidget = xml.Widget(it.Key());
      if(childWidget == 0) {
	cerr << "WARNING: Can't find widget for '" << it.Key() << "'\n";
	continue;
      }
      it.Data().Create(childWidget);
    }
    ConnectSignals();
    return true;
  }
  
  //: Create with a widget supplied from elsewhere.
  
  bool GladeWidgetBodyC::Create(GtkWidget *newWidget) {
    if(widget != 0)
      return true;
    widget = newWidget;
    for(HashIterC<StringC,WidgetC> it(children);it;it++) {
      GtkWidget *childWidget = xml.Widget(it.Key());
      if(childWidget == 0) {
	cerr << "WARNING: Can't find widget for '" << it.Key() << "'\n";
	continue;
      }
      it->Create(childWidget);
    }
    ConnectSignals();    
    return true;
  }

  //: Add named widget.
  
  bool GladeWidgetBodyC::AddObject(const StringC &name,const WidgetC &widget) {
    children[name] = widget;
    return true;
  }

}
