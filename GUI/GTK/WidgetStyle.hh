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
#include "Ravl/Image/Image.hh"
#include "Ravl/GUI/Widget.hh"
#include "Ravl/Image/ByteRGBValue.hh"

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
  
  //! userlevel=Develop
  //: Widget style
  
  class WidgetStyleBodyC
    : public RCBodyVC 
  {
  public:
    WidgetStyleBodyC(WidgetC nwidge);
    //: Default constructor.
    
    virtual ~WidgetStyleBodyC();
    //: Destructor.
    
    GtkStyle *Style() { return style; }
    //: Access gtk style.
    
    void LoadDefault();
    //: Loads the default style

    void SetBackground(const ImageC<ByteRGBValueC>& im);
    //: Set the background of the widget

    void SetBackground(const ImageC<ByteRGBValueC>& im, GtkStateType& state);
    //: Set the background of the widget
    
  protected:

    GdkPixmap* GUIImage2Pixmap(ImageC<ByteRGBValueC>& im);
    // Loads a pixmap from an ImageC

    bool GUISetBackground(GdkPixmap* pixmap, GtkStateType state);
    // Sets the background to a pixmap

    bool GUILoadDefault();
    //: Loads the default style

    bool GUISetBackground(ImageC<ByteRGBValueC>& im);
    //: Sets the background of the widget

    bool GUISetBackground(ImageC<ByteRGBValueC>& im, GtkStateType& state);
    //: Sets the background of the widget

    GtkStyle *style;
    //: The GTK style itself
    
    WidgetC widge;
    //: Widget used to get display info

    friend class WidgetStyleC;

  };

  class WidgetStyleC
    : public RCHandleC<WidgetStyleBodyC>
  {
    
  public:
    WidgetStyleC()
    {}
    //: Default constructor.
    // Creates invalid handle

    WidgetStyleC(WidgetC nwidge)
      : RCHandleC<WidgetStyleBodyC>(*new WidgetStyleBodyC(nwidge))
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

    void SetBackground(const ImageC<ByteRGBValueC>& im)
    { Body().SetBackground(im); }
    //: Set the background of the widget

    void SetBackground(const ImageC<ByteRGBValueC>& im, GtkStateType& state)
    { Body().SetBackground(im,state); }
    //: Set the background of the widget
    
  protected:

    bool GUILoadDefault()
    { return Body().GUILoadDefault(); }
    //: Loads the default style

    bool GUISetBackground(ImageC<ByteRGBValueC>& im)
    { return Body().GUISetBackground(im); }
    //: Sets the background of the widget

    bool GUISetBackground(ImageC<ByteRGBValueC>& im, GtkStateType& state) 
    { return Body().GUISetBackground(im,state); }
    //: Sets the background of the widget

    friend class WidgetStyleBodyC;

  };

}
#endif
