// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUICURSOR_HEADER
#define RAVLGUICURSOR_HEADER
////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/Cursor.hh"
//! lib=RavlGUI
//! docentry="Ravl.GUI.Layout"
//! author="Charles Galambos"
//! date="17/06/99"
//! example=exCursor.cc

#include "Ravl/GUI/GTKTypes.hh"
#include "Ravl/RefCounter.hh"

namespace RavlGUIN {
  
  using namespace RavlN;
  
  //! userlevel=Develop
  //: Cursor body
  
  class CursorBodyC
    : public RCBodyC
  {
  public:  
    CursorBodyC(const char *name = "GDK_ARROW");
    //: Constructor.
    
    ~CursorBodyC();
    //: Destructor.
    
    void SetWindow(GdkWindow *win);
    //: Set cursor in window to this one.
    
    bool operator ==(const CursorBodyC &oth) const
    { return cursor == oth.cursor; }
    //: Compair cursors.
  protected:
    GdkCursor *Cursor();
    //: Get the cursor.
    
    GdkCursor *cursor;
    const char *cname;
  };
  
  //! userlevel=Normal
  //: Cursor handle
  // This changes the pointer used in a window.
  // List of options can be seen in Cursor.cc, will add
  // it to documentation soon.
  
  class CursorC
    : public RCHandleC<CursorBodyC>
  {
  public:
    CursorC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
  
    CursorC(const char *name)
      : RCHandleC<CursorBodyC>(*new CursorBodyC(name))
    {}
    //: Create named cursor.
  
    void SetWindow(GdkWindow *win)
      { Body().SetWindow(win); }
    //: Set cursor in window to this one.
    
  };
}

#endif
