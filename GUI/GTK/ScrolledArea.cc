/////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/ScrolledArea.hh"
#include <gtk/gtk.h>

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x) 
#endif

namespace RavlGUIN {

  /////////////////////////////////
  //: Constructor.
  
  ScrolledAreaBodyC::ScrolledAreaBodyC(const WidgetC &achild,IntT sx,IntT sy,bool nVauto,bool nHauto)
    : OneChildBodyC(achild),
      isx(sx),isy(sy),
      vauto(nVauto),
      hauto(nHauto)
  {}
  
  //////////////////////////////////
  //: Create the widget.
  
  bool ScrolledAreaBodyC::Create() {
    if(widget != 0)
      return true; // Done already!
    widget = gtk_scrolled_window_new(0,0);
    GtkPolicyType      hscrollbar_policy,vscrollbar_policy ;
    if(child.IsValid()) {
      child.GUIShow();
      gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW(widget),
					     child.Widget());
    }
    if(vauto)
      vscrollbar_policy = GTK_POLICY_AUTOMATIC;
    else
      vscrollbar_policy = GTK_POLICY_ALWAYS;
    if(hauto)
      hscrollbar_policy = GTK_POLICY_AUTOMATIC;
    else
      hscrollbar_policy = GTK_POLICY_ALWAYS;
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (widget),hscrollbar_policy,vscrollbar_policy );
    if(isx >= 0) {
      if(isy < 0)
	isy = isx;
      GUISetUSize(isx,isy);
    }
    ConnectSignals();
    return true;
  }
  
}
