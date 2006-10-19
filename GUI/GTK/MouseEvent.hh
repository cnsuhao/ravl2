// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_MOUSEEVENT_HEADER
#define RAVLGUI_MOUSEEVENT_HEADER 1
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/MouseEvent.hh"
//! lib=RavlGUI
//! author="Charles Galambos"
//! docentry="Ravl.API.GUI.Internal"
//! date="08/04/1999"

#include "Ravl/Types.hh"
#include "Ravl/Index2d.hh"

// Namespace fix for Visual C++
#if RAVL_COMPILER_VISUALCPP6
#ifndef RavlGUIN
#define RavlGUIN RavlN
#endif
#endif

typedef struct _GdkEventMotion	    GdkEventMotion;
typedef struct _GdkEventButton	    GdkEventButton;

namespace RavlGUIN {
  
  using namespace RavlN;
  
  //! userlevel=Normal
  //: Mouse event information.
  
  class MouseEventC {
  public:
    MouseEventC(IntT col = 0,IntT row = 0,IntT state = 0,IntT changed = 0);
    //: Constructor.
    
    MouseEventC(GdkEventButton &ev);
    //: Constructor.
    
    MouseEventC(GdkEventMotion &ev);
    //: Constructor.
    
    RealT X() const { return x; }
    //: Get "x" component of position in GTK coord system.
    // Obsolete! Use Col()
    
    RealT Y() const { return y; }
    //: Get "y" component of position in GTK coord system.
    // Obsolete! Use Row()
    
    RealT Row() const { return y; }
    //: Get row number of position.
    
    RealT Col() const { return x; }
    //: Get column number of position.
    
    Index2dC Position() const { return Index2dC(x,y); }
    //: Get position in GTK co-ordinates (col, row).
    // This method is deprecated, use At() instead.
    
    Index2dC At() const { return Index2dC(y,x); }
    //: Get position.
    // Position of mouse click in RAVL co-ordinates (row, col).
    
    bool IsPressed(IntT buttonNo = 0) const;
    //: Test if a button is pessed.
    
    bool HasChanged(IntT buttonNo = 0) const;
    //: Has button changed state ?
    
    IntT MaxButtons() const { return 5; }
    //: Maximum buttons available.
    
    bool IsShift() const;
    //: Is shift down ?
    
    bool IsCntrl() const;
    //: Is control down ?
    
  protected:
    RealT x,y;   // Current position.
    IntT state;  // Current state.
    IntT change; // Change flags.
    UIntT time;  // Time of event.
  };
  
  ostream &operator<<(ostream &,const MouseEventC &me);
  //: Print description of mouse event to stream.
  
  /////// CListEventC ////////////////////////////////////////////////
  
  class CListEventC {
  public:
    CListEventC(IntT nrowId,IntT nrow,IntT ncol,GdkEventButton *mevent)
      : rowId(nrowId),
      row(nrow),
      col(ncol),
      event(*mevent)
      {}
    //: Constructor.
    
    CListEventC(IntT nrowId,IntT nrow,IntT ncol)
      : rowId(nrowId),
      row(nrow),
      col(ncol)
      {}
    //: Constructor.
    
    CListEventC()
      {}
    //: Default constructor.
    
    IntT &RowID()
      { return rowId; }
    //: Access row id.
    
    IntT RowID() const
      { return rowId; }
    //: Access row id.

    MouseEventC &MouseEvent()
      { return event; }
    //: Access mouse event.

    const MouseEventC &MouseEvent() const
      { return event; }
    //: Access mouse event.
    
    IntT rowId;
    IntT row;
    IntT col;
    MouseEventC event;
  };
  
}

#endif
