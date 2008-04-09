// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_GLADEWINDOW_HEADER
#define RAVLGUI_GLADEWINDOW_HEADER 1
//! docentry="Ravl.API.Graphics.GTK.LibGlade"
//! rcsid="$Id$"
//! lib=RavlLibGlade
//! file="Ravl/GUI/LibGlade/GladeWindow.hh"

#include "Ravl/GUI/GladeWidget.hh"

namespace RavlGUIN {

  //! userlevel=Develop
  //: Glade widget
  
  class GladeWindowBodyC
    : public GladeWidgetBodyC
  {
  public:
    GladeWindowBodyC(const GladeXMLC &gladeXml,const StringC &widgetName,bool customWidget = true);
    //: Constructor
    
    GladeWindowBodyC(const StringC &widgetName,bool customWidget = true);
    //: Constructor
    // NOTE: If using this constructor a Glade XML object must be set with SetXML()
    
    bool Raise();
    //: Raise window to top
    
    bool GUIRaise();
    //: Raise window to top
    
    bool SetTitle(const StringC &title);
    //: Set the window title
    
    bool GUISetTitle(const StringC &title);
    //: Set the window title
  };
  
  //! userlevel=Normal
  //: Glade widget
  
  class GladeWindowC
    : public GladeWidgetC
  {
  public:
    GladeWindowC()
    {}
    //: Default constructor
    // Creates an invalid handle.
    
    GladeWindowC(const GladeXMLC &gladeXml,const StringC &widgetName,bool customWidget = true)
      : GladeWidgetC(*new GladeWindowBodyC(gladeXml,widgetName,customWidget))
    {}
    //: Constructor
    
    GladeWindowC(const StringC &widgetName,bool customWidget = true)
      : GladeWidgetC(*new GladeWindowBodyC(widgetName,customWidget))
    {}
    //: Constructor
    // NOTE: If using this constructor a Glade XML object must be set with SetXML()
    
  protected:
    GladeWindowC(GladeWindowBodyC &body)
      : GladeWidgetC(body)
    {}
    //: Body constructor
    
    GladeWindowBodyC &Body()
    { return static_cast<GladeWindowBodyC &>(WidgetC::Body()); }
    //: Access widget body.
    
    const GladeWindowBodyC &Body() const
    { return static_cast<const GladeWindowBodyC &>(WidgetC::Body()); }
    //: Access widget body.
    
  public:
    bool Raise()
    { return Body().Raise(); }
    //: Raise window to top
    
    bool GUIRaise()
    { return Body().GUIRaise(); }
    //: Raise window to top
    
    bool SetTitle(const StringC &title)
    { return Body().SetTitle(title); }
    //: Set the window title
    
    bool GUISetTitle(const StringC &title)
    { return Body().GUISetTitle(title); }
    //: Set the window title

    friend class GladeWindowBodyC;
  };

}


#endif
