/////////////////////////////////////
//! rcsid="$Id$

#include "Ravl/GUI/MouseEvent.hh"
#include <gtk/gtk.h>

#define RAVLDODEBUG 1

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {

  //: Constructor.
  
  MouseEventC::MouseEventC(IntT nx,IntT ny,IntT nstate) 
    : x(nx),
      y(ny),
      state(nstate),
      change(0)
  {}
  
  //: Constructor.
  
  MouseEventC::MouseEventC(GdkEventButton &ev)
    : x(ev.x),
      y(ev.y),
      state(ev.state),
      change(0),
      time(ev.time)
    
  {
    change = 1 << (ev.button - 1);
    //ONDEBUG(cerr << "Button: " << ev.button << "\n");
  }
  
  //: Constructor.
  
  MouseEventC::MouseEventC(GdkEventMotion &event)
    : x(event.x),
      y(event.y),
      state(event.state),
      change(0),
      time(event.time)
  {
    if (event.is_hint) {
      IntT ix,iy;
      gdk_window_get_pointer (event.window, &ix, &iy,(GdkModifierType *) &state);
      x = ix;
      y = iy;
    } else {
      x = event.x;
      y = event.y;
      state = event.state;
    }
  }
  
  //: Test if a button is pessed.
  
  bool MouseEventC::IsPressed(IntT buttonNo) const {
    if(buttonNo < 0 || buttonNo >= MaxButtons())
      return false;
    return (state & (1 << (8 + buttonNo))) != 0;
  }
  
  //: Has button changed state ?
  
  bool MouseEventC::HasChanged(IntT buttonNo) const {
    if(buttonNo < 0 || buttonNo >= MaxButtons())
      return false;
    return (change & (1 << buttonNo)) != 0; 
  }
  
  
  //: Is shift down ?
  
  bool MouseEventC::IsShift() const { 
    return (state & GDK_SHIFT_MASK) != 0; 
  }
  
  //: Is control down ?
  
  bool MouseEventC::IsCntrl() const { 
    return (state & GDK_CONTROL_MASK) != 0; 
  }
  
  ostream &operator<<(ostream &s,const MouseEventC &me) {
    //s << " x:" << me.X() << " y:" << me.Y();
    return s;
  }
}
