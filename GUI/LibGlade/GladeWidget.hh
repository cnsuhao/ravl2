// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_GLADEWIDGET_HEADER
#define RAVLGUI_GLADEWIDGET_HEADER 1
//! rcsid="$Id$"
//! lib=RavlLibGlade

#include "Ravl/GUI/Widget.hh"
#include "Ravl/GUI/GladeXML.hh"

namespace RavlGUIN {

  //! userlevel=Develop
  //: Glade widget
  
  class GladeWidgetBodyC
    : public WidgetBodyC
  {
  public:
    GladeWidgetBodyC(const GladeXMLC &gladeXml,const StringC &widgetName,bool customWidget = true);
    //: Constructor
    
    virtual bool Create();
    //: Create the widget.
    
    virtual bool Create(GtkWidget *widget);
    //: Create with a widget supplied from elsewhere.
    
    bool AddObject(const StringC &name,const WidgetC &widget);
    //: Add named widget.
    
  protected:
    GladeXMLC xml;
    StringC name;
    HashC<StringC,WidgetC> children;
    bool customWidget;
  };
  
  //! userlevel=Normal
  //: Glade widget
  
  class GladeWidgetC
    : public WidgetC
  {
  public:
    GladeWidgetC(const GladeXMLC &gladeXml,const StringC &widgetName,bool customWidget = true)
      : WidgetC(*new GladeWidgetBodyC(gladeXml,widgetName,customWidget))
    {}
    //: Constructor
    
    GladeWidgetC()
    {}
    //: Default constructor
    // Creates an invalid handle.
    
  protected:
    GladeWidgetC(GladeWidgetBodyC &body)
      : WidgetC(body)
    {}
    //: Body constructor
    
    GladeWidgetBodyC &Body()
    { return static_cast<GladeWidgetBodyC &>(WidgetC::Body()); }
    //: Access widget body.
    
    const GladeWidgetBodyC &Body() const
    { return static_cast<const GladeWidgetBodyC &>(WidgetC::Body()); }
    //: Access widget body.
    
  public:
    bool AddObject(const StringC &name,const WidgetC &widget)
    { return Body().AddObject(name,widget); }
    //: Add named widget.
    
  };

}


#endif
