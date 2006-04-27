// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////
//! docentry="GUI"
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/Slider.cc"

#include "Ravl/GUI/Slider.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>

#define DPDEBUG 0

#if DPDEBUG 
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  void value_changed( GtkAdjustment *adj,SliderBodyC *data ) {
    data->SigChanged()(adj->value); 
  }
  
  int value_released(GtkWidget *widget,GdkEvent *event,SliderBodyC *data ) {
    data->SigReleased()(); 
    return 0;
  }
  
  //: Constructor.
  
  SliderBodyC::SliderBodyC(RealT nvalue, 
			   RealT nlower, 
			   RealT nupper, 
			   RealT nstep_increment,
			   RealT npage_increment,
			   RealT npage_size)
    : setConfig(false),
      value(nvalue),
      lower(nlower),
      upper(nupper), 
      step_increment(nstep_increment),
      page_increment(npage_increment),
      page_size(npage_size),
      digits(0),
      updateCont(true),
      vert(false),
      sReq(false),
      numPos(GTK_POS_TOP),
      drawValue(true),
      setValue(false),
      sigChanged(true),
      sigReleased(true)
  {
    ONDEBUG(cerr << "Horiz Constructor. \n");
  }
  
  SliderBodyC::SliderBodyC(bool nvert,RealT nvalue, RealT nlower, 
			       RealT nupper, RealT nstep_increment,
			   RealT npage_increment,RealT npage_size)
    
    : value(nvalue),
      lower(nlower),
      upper(nupper), 
      step_increment(nstep_increment),
      page_increment(npage_increment),
      page_size(npage_size),
      digits(0),
      updateCont(true),
      vert(nvert),
      sReq(false),
      numPos(GTK_POS_TOP),
      drawValue(true),
      setValue(false),
      sigChanged(true),
      sigReleased(true)
  {
    if(!vert)
      numPos = GTK_POS_TOP;
    else
      numPos = GTK_POS_LEFT;
  }
  //: Constructor.
  
  
  //: Create the widget.

  bool SliderBodyC::CommonCreate(GtkWidget *_widget)
  {
    if (_widget == NULL)
    {
      ONDEBUG(cerr << "Slider create: Low:" << lower << " High:" << upper << " Inc:" << step_increment << "\n");
      adj = gtk_adjustment_new(value, 
                               lower, 
                               upper + step_increment, 
                               step_increment,
                               page_increment,
                               page_size);
      if(vert) 
        widget = gtk_vscale_new(GTK_ADJUSTMENT (adj));
      else
        widget = gtk_hscale_new(GTK_ADJUSTMENT (adj));
      
      if(updateCont) {
        gtk_range_set_update_policy (GTK_RANGE (widget),
             GTK_UPDATE_CONTINUOUS);
      } else {
        gtk_range_set_update_policy (GTK_RANGE (widget),
             GTK_UPDATE_DISCONTINUOUS);    
      }
      // GTK_UPDATE_DELAYED
      
      gtk_scale_set_digits (GTK_SCALE (widget), digits);
      gtk_scale_set_value_pos (GTK_SCALE (widget), numPos);
      gtk_scale_set_draw_value (GTK_SCALE(widget), drawValue);
    }
    else
    {
      ONDEBUG(cerr << "Slider create from glade");
      widget = _widget;
      adj = GTK_OBJECT(gtk_range_get_adjustment(GTK_RANGE(widget)));
    }
    
    gtk_signal_connect (GTK_OBJECT (adj), "value_changed",
			GTK_SIGNAL_FUNC (value_changed), this);
    gtk_signal_connect (GTK_OBJECT (widget), "button_release_event",
			GTK_SIGNAL_FUNC (value_released), this);
    gtk_signal_connect (GTK_OBJECT (widget), "key_release_event",
			GTK_SIGNAL_FUNC (value_released), this);
    
    return true;
  }
  
  //: Update the slider value.
  
  bool SliderBodyC::GUIUpdateValue(const RealT &val) {
    value = val;
    if(widget == 0)
      return true;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");    
#if !RAVL_USE_GTK2
    if(GTK_RANGE (widget)->button == 0) { // Don't set value if user is changing it.
      GTK_ADJUSTMENT (adj)->value = val;
      ONDEBUG(cerr << "Slider setting: Value:" << value << " (L: " << GTK_ADJUSTMENT (adj)->lower << " U:" << GTK_ADJUSTMENT (adj)->upper << ") \n");
    }
#else
    GTK_ADJUSTMENT (adj)->value = val;
    ONDEBUG(cerr << "Slider setting: Value:" << value << " (L: " << GTK_ADJUSTMENT (adj)->lower << " U:" << GTK_ADJUSTMENT (adj)->upper << ") \n");
#endif
    gtk_signal_emit_by_name (GTK_OBJECT (adj), "changed");
    return true;
  }
  
  //: Update the slider value.
  bool SliderBodyC::GUIUpdateRange(const RealT &nlower,const RealT &nupper) {
    lower = nlower;
    upper = nupper;
    if(widget == 0)
      return true;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
    GTK_ADJUSTMENT (adj)->lower = lower;
    GTK_ADJUSTMENT (adj)->upper = (RealT) upper + step_increment;
    // Check range.
    if(GTK_ADJUSTMENT (adj)->lower > GTK_ADJUSTMENT (adj)->value) {
      GTK_ADJUSTMENT (adj)->value = GTK_ADJUSTMENT (adj)->lower;
    }
    if(GTK_ADJUSTMENT (adj)->upper < GTK_ADJUSTMENT (adj)->value) {
      GTK_ADJUSTMENT (adj)->value = GTK_ADJUSTMENT (adj)->upper;
    }
    
    gtk_signal_emit_by_name (GTK_OBJECT (adj), "changed");
    return true;
  }
  
  //: Update the slider value.
  
  bool SliderBodyC::GUIUpdate(const RealT &val,const RealT &nlower,const RealT &nupper,const RealT &inc) {
    lower = nlower;
    upper = nupper;
    step_increment = inc;
    if(widget == 0)
      return true;
    RavlAssertMsg(Manager.IsGUIThread(),"Incorrect thread. This method may only be called on the GUI thread.");
#if !RAVL_USE_GTK2
    if(GTK_RANGE (widget)->button == 0) { // Don't set value if user is changing it.
      GTK_ADJUSTMENT (adj)->value = val;
    }
#else
    GTK_ADJUSTMENT (adj)->value = val;
#endif
    GTK_ADJUSTMENT (adj)->lower = lower;
    GTK_ADJUSTMENT (adj)->upper = (RealT) upper + step_increment;
    GTK_ADJUSTMENT (adj)->step_increment = step_increment;
    gtk_signal_emit_by_name (GTK_OBJECT (adj), "changed");
    return true;
  }
  
  bool SliderBodyC::UpdateRange(RealT nlower,RealT nupper) {
    Manager.Queue(Trigger(SliderC(*this),&SliderC::GUIUpdateRange,nlower,nupper));
    return true;
  }
  
  //: Update the slider value.
  
  bool SliderBodyC::UpdateValue(RealT val) {
#if !RAVL_USE_GTK2
    if(widget != 0) {    
      if(GTK_RANGE (widget)->button != 0) // Don't set value if user is changing it.
	return false;
    }
#endif
    Manager.Queue(Trigger(SliderC(*this),&SliderC::GUIUpdateValue,val));
    return true;
  }

  //: Update the slider value.
  
  bool SliderBodyC::Update(RealT val,RealT nlower,RealT nupper,RealT inc) {
    Manager.Queue(Trigger(SliderC(*this),&SliderC::GUIUpdate,val,nlower,nupper,inc));
    return true;  
  }

}

