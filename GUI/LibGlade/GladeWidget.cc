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
#include <gtk/gtk.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  //: Constructor
  
  GladeWidgetBodyC::GladeWidgetBodyC(const GladeXMLC &gladeXml,const StringC &widgetName,bool aCustomWidget) 
    : xml(gladeXml),
      name(widgetName),
      customWidget(aCustomWidget)
  {
    if(customWidget)
      xml = GladeXMLC(gladeXml.Filename(),name);
  }
  
  //: Constructor
  
  GladeWidgetBodyC::GladeWidgetBodyC(const StringC &widgetName,bool aCustomWidget) 
    : name(widgetName),
      customWidget(aCustomWidget)
  {
  }
  
  
  
  bool GladeWidgetBodyC::SetXML(const GladeXMLC &gladeXml)
  {
    if (xml.IsValid())
    {
      ONDEBUG(cerr << "GladeWidgetBodyC::SetXML already set" << endl;)
      return true;
    }
    
    if(customWidget)
      xml = GladeXMLC(gladeXml.Filename(),name);
    else
      xml = gladeXml;
    
    return true;
  }

  //: Create the widget.
  
  bool GladeWidgetBodyC::Create() {
    ONDEBUG(cerr << "GladeWidgetBodyC::Create(), Called. Name=" << name << "\n");

    if (!xml.IsValid())
    {
      cerr << "GladeWidgetBodyC::Create called with no XML set" << endl;
      return false;
    }

    if(widget != 0)
      return true;
    widget = xml.Widget(name);
    if(widget == 0) {
      cerr << "ERROR: Failed to find widget '" << name << "' in '" << xml.Filename() << "'\n";
      RavlAssert(0);
      return false;
    }
    ONDEBUG(cerr << " Setting up children. \n");
    for(HashIterC<StringC,WidgetC> it(children);it;it++) {
      GtkWidget *childWidget = xml.Widget(it.Key());
      if(childWidget == 0) {
	cerr << "WARNING: Can't find child widget '" << it.Key() << "'\n";
	continue;
      }
      if(!it.Data().IsValid()) {
        cerr << "ERROR: Invalid widget wrapper provided for " << it.Key() << "\n";
        continue;
      }
      it.Data().Create(childWidget);
    }
    ONDEBUG(cerr << " Connecting signals \n");
    ConnectSignals();
    ONDEBUG(cerr << "GladeWidgetBodyC::Create(), Done. Name=" << name << "\n");
    return true;
  }
  
  //: Create with a widget supplied from elsewhere.
  
  bool GladeWidgetBodyC::Create(GtkWidget *newWidget) {
    ONDEBUG(cerr << "GladeWidgetBodyC::Create(GtkWidget *), Called. Name=" << name << " \n");

    if (!xml.IsValid())
    {
      cerr << "GladeWidgetBodyC::Create called with no XML set" << endl;
      return false;
    }

    if(widget != 0)
      return true;
    widget = newWidget;
    if(customWidget) {
      if(!GTK_IS_CONTAINER(widget)) {
	cerr << "ERROR: Custom widget for " << name << " isn't a container. (Try putting an event box here.) \n";
	RavlAssert(0);
	return false;
      }
      ONDEBUG(cerr << "Adding custom child widget '" << name << "' into parent. \n");  
      GtkWidget *childWidget = xml.Widget(name);
      gtk_widget_show (childWidget);
      gtk_container_add(GTK_CONTAINER(widget),childWidget);
    }
    for(HashIterC<StringC,WidgetC> it(children);it;it++) {
      GtkWidget *childWidget = xml.Widget(it.Key());
      if(childWidget == 0) {
	cerr << "WARNING: Can't find widget for '" << it.Key() << "'\n";
	continue;
      }
      it->Create(childWidget);
    }
    ConnectSignals();    
    ONDEBUG(cerr << "GladeWidgetBodyC::Create(GtkWidget *), Done. Name=" << name << "\n");
    return true;
  }

  //: Add named widget.
  
  bool GladeWidgetBodyC::AddObject(const StringC &name,const WidgetC &widget) {
    children[name] = widget;
    return true;
  }

}
