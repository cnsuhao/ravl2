// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_WIDGETSTYLE_HEADER
#define RAVLGUI_WIDGETSTYLE_HEADER 1
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/WidgetStyle.hh"
//! lib=RavlGUI
//! author="James Smith"
//! date="28/10/2002"
//! userlevel=Normal
//! docentry="Ravl.GUI.Styles"
//! example="exStyle.cc"

#include "Ravl/GUI/GTKTypes.hh"
#include "Ravl/GUI/Pixmap.hh"
#include "Ravl/GUI/Widget.hh"

#include <gtk/gtkenums.h>
#include <gtk/gtk.h>

// Namespace fix for Visual C++
#ifdef VISUAL_CPP
#ifndef RavlGUIN
#define RavlGUIN RavlN
#endif
#endif

namespace RavlGUIN {

  using namespace RavlImageN;

  enum WidgetColourTypeT {
    WIDGET_COLOUR_FG,
    WIDGET_COLOUR_BG,
    WIDGET_COLOUR_LIGHT,
    WIDGET_COLOUR_DARK,
    WIDGET_COLOUR_MID,
    WIDGET_COLOUR_TEXT,
    WIDGET_COLOUR_BASE,
    WIDGET_COLOUR_BLACK,
    WIDGET_COLOUR_WHITE
  };
  
  //! userlevel=Develop
  //: Widget style

  class WidgetStyleBodyC
    : public RCBodyVC 
  {
  public:
    WidgetStyleBodyC();
    //: Default constructor.
    
    virtual ~WidgetStyleBodyC();
    //: Destructor.
    
    GtkStyle *Style() { return style; }
    //: Access gtk style.
    
    void LoadDefault();
    //: Loads the default style

    void SetBackground(const PixmapC& pixmap);
    //: Set the background of the widget

    void SetBackground(const PixmapC& pixmap, GtkStateType& state);
    //: Set the background of the widget
    // Values for state are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKSTATETYPE">here</A>.
    
    void SetColour(WidgetColourTypeT& type, ByteRGBValueC& col);
    //: Set a colour for the widget
    
    void SetColour(WidgetColourTypeT& type, ByteRGBValueC& col, GtkStateType& state);
    //: Set a colour for the widget
    // Values for state are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKSTATETYPE">here</A>.

  protected:

    bool GUILoadDefault();
    //: Loads the default style

    bool GUISetBackground(PixmapC& pixmap, GtkStateType state);
    // Sets the background to a pixmap
    // Values for state are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKSTATETYPE">here</A>.

    bool GUISetBackground(PixmapC& pixmap);
    //: Sets the background of the widget

    GdkColor GUIRGB2Colour(ByteRGBValueC& rgb);
    // Loads a colour from a ByteRGBValueC

    bool GUISetColour(WidgetColourTypeT type, GdkColor color, GtkStateType state);
    // Sets a colour 
    // Values for state are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKSTATETYPE">here</A>.

    bool GUISetColour(WidgetColourTypeT& type, ByteRGBValueC& col);
    //: Set a colour for the widget
    
    bool GUISetColour(WidgetColourTypeT& type, ByteRGBValueC& col, GtkStateType& state);
    //: Set a colour for the widget
    // Values for state are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKSTATETYPE">here</A>.

    GtkStyle *style;
    //: The GTK style itself
    
    friend class WidgetStyleC;

  };
  
  //! userlevel=Normal
  //: Widget style
  
  class WidgetStyleC
    : public RCHandleC<WidgetStyleBodyC>
  {
    
  public:
    WidgetStyleC()
      : RCHandleC<WidgetStyleBodyC>(*new WidgetStyleBodyC())
    {}
    //: Constructor.
    // Creates default style
    
  protected:
    
    WidgetStyleC(WidgetStyleBodyC &bod) 
      : RCHandleC<WidgetStyleBodyC>(bod)
    {}
    //: Body Constructor.
    
    WidgetStyleBodyC &Body() 
    { return RCHandleC<WidgetStyleBodyC>::Body(); }
    //: Access body.
    
    const WidgetStyleBodyC &Body() const
    { return RCHandleC<WidgetStyleBodyC>::Body(); }
    //: Access body.  
  
  public:

    GtkStyle *Style() 
    { return Body().Style(); }
    //: Access gtk style.
    
    void LoadDefault() 
    { Body().LoadDefault(); }
    //: Loads the default style

    void SetBackground(const PixmapC& pixmap)
    { Body().SetBackground(pixmap); }
    //: Set the background of the widget

    void SetBackground(const PixmapC& pixmap, GtkStateType& state)
    { Body().SetBackground(pixmap,state); }
    //: Set the background of the widget
    // Values for state are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKSTATETYPE">here</A>.
    
    void SetColour(WidgetColourTypeT& type, ByteRGBValueC& col)
    { Body().SetColour(type,col); }
    //: Set a colour for the widget
    
    void SetColour(WidgetColourTypeT& type, ByteRGBValueC& col, GtkStateType& state)
    { Body().SetColour(type,col,state); }
    //: Set a colour for the widget
    // Values for state are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKSTATETYPE">here</A>.

  protected:

    bool GUILoadDefault()
    { return Body().GUILoadDefault(); }
    //: Loads the default style

    bool GUISetBackground(PixmapC& pixmap)
    { return Body().GUISetBackground(pixmap); }
    //: Sets the background of the widget

    bool GUISetBackground(PixmapC& pixmap, GtkStateType& state) 
    { return Body().GUISetBackground(pixmap,state); }
    //: Sets the background of the widget
    // Values for state are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKSTATETYPE">here</A>.

    bool GUISetColour(WidgetColourTypeT& type, ByteRGBValueC& col)
    { return Body().GUISetColour(type,col); }
    //: Set a colour for the widget
    
    bool GUISetColour(WidgetColourTypeT& type, ByteRGBValueC& col, GtkStateType& state)
    { return Body().GUISetColour(type,col,state); }
    //: Set a colour for the widget
    // Values for state are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKSTATETYPE">here</A>.

    friend class WidgetStyleBodyC;

  };

}
#endif
