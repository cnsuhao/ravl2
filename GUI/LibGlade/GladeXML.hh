// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_GLADEXML_HEADER
#define RAVLGUI_GLADEXML_HEADER 1
//! rcsid="$Id$"
//! docentry="Ravl.API.Graphics.GTK.LibGlade"
//! lib=RavlLibGlade
//! file="Ravl/GUI/LibGlade/GladeXML.hh"

#include "Ravl/RefCounter.hh"
#include "Ravl/GUI/Widget.hh"
#include "Ravl/String.hh"

extern "C" {
  typedef struct _GladeXML GladeXML;
}

namespace RavlGUIN {
  using namespace RavlN;
  
  //! userlevel=Develop
  //: Glade XML file
  
  class GladeXMLBodyC
    : public RCBodyC
  {
  public:
    GladeXMLBodyC();
    //: Default constructor.
    
    GladeXMLBodyC(const StringC &filename);
    //: Create whole interface from a file.
    
    GladeXMLBodyC(const StringC &filename,const StringC &rootWidgetName);
    //: Create part of interface from a file.
    
    GladeXML *XML();
    //: Access xml info for whole interface.
    
    GtkWidget *Widget(const StringC &widgetName);
    //: Find named widget.
    
    const StringC &Filename() const
    { return filename; }
    //: Access filename.
    
    const StringC &RootWidgetName() const
    { return rootWidgetName; }
    //: Get name of root widget.
    
  protected:
    bool Create();
    //: Create interface.
    
    GladeXML *xml;
    StringC filename;
    StringC rootWidgetName;
  };
  
  //! userlevel=Normal
  //: Glade XML file
  
  class GladeXMLC
    : public RCHandleC<GladeXMLBodyC>
  {
  public:
    GladeXMLC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    GladeXMLC(const StringC &filename)
      : RCHandleC<GladeXMLBodyC>(*new GladeXMLBodyC(filename))
    {}
    //: Create whole interface from a file.
    
    GladeXMLC(const StringC &filename,const StringC &rootWidgetName)
      : RCHandleC<GladeXMLBodyC>(*new GladeXMLBodyC(filename,rootWidgetName))
    {}
    //: Create part of interface from a file.
    
  protected:
    GladeXMLBodyC &Body()
    { return RCHandleC<GladeXMLBodyC>::Body(); }
    //: Access body.
    
    const GladeXMLBodyC &Body() const
    { return RCHandleC<GladeXMLBodyC>::Body(); }
    //: Access body.
    
  public:
    GladeXML *XML()
    { return Body().XML(); }
    //: Access xml info for whole interface.
    
    GtkWidget *Widget(const StringC &widgetName)
    { return Body().Widget(widgetName); }
    //: Find named widget.
    
    const StringC &Filename() const
    { return Body().Filename(); }
    //: Access filename.
    
    const StringC &RootWidgetName() const
    { return Body().RootWidgetName(); }
    //: Get name of root widget.
    
  };
}

#endif
