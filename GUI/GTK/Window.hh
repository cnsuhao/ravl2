// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_WINDOW_HEADER
#define RAVLGUI_WINDOW_HEADER 1
/////////////////////////////////////////////////
//! file="Ravl/GUI/GTK/Window.hh"
//! lib=RavlGUI
//! author="Charles Galambos"
//! date="23/03/1999"
//! rcsid="$Id$"
//! docentry="Ravl.GUI.Layout"

#include "Ravl/GUI/OneChild.hh"
#include "Ravl/GUI/Cursor.hh"

#include <gtk/gtkenums.h>

namespace RavlGUIN {
  
  class CursorC;
  class WindowC;
  
  //! userlevel=Develop
  //: Window body.
  
  class WindowBodyC 
    : public OneChildBodyC
  {
  public:
    WindowBodyC(int sx = 1,int sy = 1,const char *title = 0,GtkWindowType winType = GTK_WINDOW_TOPLEVEL,int nboarder = 0,bool rootWin = true);
    //: Constructor.
    // Values for winType are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKWINDOWTYPE">here</A>.
    
    ~WindowBodyC();
    //: Destructor.
    
    virtual bool Create();
    //: Create the widget.
    
    virtual bool Close();
    //: Close window.
    // Thread safe.
    // If you override this, you MUST call WindowBodyC::Close() at the end of your Close() function
    
    void SetCursor(CursorC &cur);
    //: Set cursor.
    
    void SetTitle(const StringC &str);
    //: Set the title of the window.
  
    void SetPositioning(GtkWindowPosition& pos);
    //: Influences positioning of the window.
    // Values for pos are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKWINDOWPOSITION">here</A>.

  protected:
    virtual void Destroy();
    //: Undo all references.
    // Used to avoid problems with circluar references.
    // This should undo all references to RAVL and GUI
    // objects which are not in the destroy tree. 
    // The function is called by the root window in its
    // destructor.
    
    bool GUISetPositioning(GtkWindowPosition& pos);
    //: Influences positioning of the window.
    // Values for pos are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKWINDOWPOSITION">here</A>.

    bool GUISetTitle(StringC &str);
    //: Set the title of the window.
    
    bool GUICloseDown();
    //: Close down window.
    
    bool GUIUpdateCursor(CursorC &newCursor);
    //: Update cursor.
  
    int sx,sy;
    int boarder;
    StringC title;
    bool rootWin;
    bool closeDown; // Indicates close down is in progress or pending.
    CursorC cursor; // Invalid == default.
    bool cursorChange;
    GtkWindowType winType;
    
    friend class WindowC;
  };
  
  //! userlevel=Normal
  //: Window handle.
  // Note: A window can only have ONE child widget, if you want more than
  // one thing in the window you have to add a layout widget first,
  // and add things to that.
  
  class WindowC 
    : public OneChildC
  {
  public:
    WindowC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    WindowC(int sx,int sy = 1,const char *ntitle = 0,GtkWindowType winType = GTK_WINDOW_TOPLEVEL,int nboarder = 0,bool rootWin = true);
    //: Constructor.
    // Values for winType are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKWINDOWTYPE">here</A>.
    
  protected:
    WindowC(WindowBodyC &bod)
      : OneChildC(bod)
      {}
    //: Body constructor.
    
    WindowBodyC &Body() 
      { return static_cast<WindowBodyC  &>(WidgetC::Body()); }
    //: Access body.
    
    const WindowBodyC  &Body() const
      { return static_cast<const WindowBodyC  &>(WidgetC::Body()); }
    //: Access body.
    
    bool GUISetTitle(StringC &str)
      { return Body().GUISetTitle(str); }
    //: Set the title of the window.
    // GUI thread only.
    
    bool GUICloseDown()
      { return Body().GUICloseDown(); }
    //: Close down window.
    
    bool GUIUpdateCursor(CursorC &newCursor)
      { return Body().GUIUpdateCursor(newCursor); }
    //: Update cursor.
    
    bool GUISetPositioning(GtkWindowPosition& pos)
    { return Body().GUISetPositioning(pos); }
    //: Influences positioning of the window.
    // Values for pos are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKWINDOWPOSITION">here</A>.

  public:
    void Destroy() { 
      WidgetC::Destroy(); 
      Invalidate();
    }
    //: Destroy this window.
    
    void SetTitle(const StringC &str)
    { Body().SetTitle(str); }
    //: Set the title of the window.
    
    void SetPositioning(GtkWindowPosition& pos)
    { Body().SetPositioning(pos); }
    //: Influences positioning of the window.
    // Values for pos are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKWINDOWPOSITION">here</A>.

    bool Close()
    { return Body().Close(); }
    //: Close window.
    // Thread safe.
    
    void SetCursor(CursorC &cur)
    { Body().SetCursor(cur); }
    //: Set cursor.
    
    friend class WindowBodyC;
  };

}

#endif
