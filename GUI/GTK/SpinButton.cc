//////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/GUI/SpinButton.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>

#define DPDEBUG 0

#if DPDEBUG 
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  extern "C" {
    void spinbutton_value_changed( GtkAdjustment *adj,SpinButtonBodyC *data )
    { data->SigChanged()(adj->value); }
  }
  
  SpinButtonBodyC::SpinButtonBodyC(IntT ndigits,
				   RealT nclimbRate,
				   RealT nvalue,
				   RealT nlower,RealT nupper,RealT nstep_increment)
    :  digits(ndigits),
       climbRate(nclimbRate),
       value(nvalue),
       lower(nlower),  
       upper(nupper),  
       step_increment(nstep_increment),
       adj(0),
       sigChanged(true)
  {}
  
  
  //: Create widget.
  
  bool SpinButtonBodyC::Create() {
    // Setup adjustment.
    
    adj = gtk_adjustment_new (value, 
			      lower, 
			      upper + step_increment, 
			      step_increment,
			      1,
			      1);
    
    widget = gtk_spin_button_new(GTK_ADJUSTMENT (adj),
				 climbRate,
				 digits);
    
    gtk_signal_connect (GTK_OBJECT (adj), "value_changed",
			GTK_SIGNAL_FUNC (spinbutton_value_changed), this);
    
    ConnectSignals();
    return true;
  }
  
  //: Undo all refrences.
  
  void SpinButtonBodyC::Destroy() {
    sigChanged.DisconnectAll();
    WidgetBodyC::Destroy();
  }
  
  
  //: Set value 
  // Thread safe.
  
  void SpinButtonBodyC::SetValue(RealT val) {
    Manager.Queue(Trigger(SpinButtonC(*this),&SpinButtonC::GUISetValue,val));
  }
  
  //: Set value 
  // GUI thread only.
  
  bool SpinButtonBodyC::GUISetValue(RealT val) {
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),val);
    //GTK_ADJUSTMENT (adj)->value = val;
    //gtk_signal_emit_by_name (GTK_OBJECT (adj), "changed");  
    return true;
  }
}
  
