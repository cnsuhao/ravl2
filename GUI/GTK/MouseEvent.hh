#ifndef RAVLGUIMOUSEEVENT_HEADER
#define RAVLGUIMOUSEEVENT_HEADER 1
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/MouseEvent.hh"
//! lib=GUI
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Internal"
//! date="08/04/99"

#include "Ravl/Types.hh"
#include "Ravl/Index2d.hh"

typedef struct _GdkEventMotion	    GdkEventMotion;
typedef struct _GdkEventButton	    GdkEventButton;

namespace RavlGUIN {
  
  using namespace RavlN;
  
  //! userlevel=Normal
  //: Mouse event information.
  
  class MouseEventC {
  public:
    MouseEventC(IntT x = 0,IntT y = 0,IntT state = 0);
    //: Constructor.
    
    MouseEventC(GdkEventButton &ev);
    //: Constructor.
    
    MouseEventC(GdkEventMotion &ev);
    //: Constructor.
    
    RealT X() const { return x; }
    //: Get X component of position.
    
    RealT Y() const { return y; }
    //: Get Y component of position.
    
    Index2dC Position() const { return Index2dC(x,y); }
    //: Get position.
    
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
    
    IntT rowId;
    IntT row;
    IntT col;
    MouseEventC event;
  };
  
}

#endif
