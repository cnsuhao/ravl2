// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUISLIDER_HEADER
#define RAVLGUISLIDER_HEADER 1
/////////////////////////////////////////////////
//! file="Ravl/GUI/GTK/Slider.hh"
//! lib=RavlGUI
//! author="Charles Galambos"
//! date="23/03/99"
//! rcsid="$Id$"
//! example=exSlider.cc
//! docentry="Ravl.GUI.Control"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/Threads/Signal2.hh"

namespace RavlGUIN {

  class SliderC;
  
  //! userlevel=Develop
  //: Slider body
  
  class SliderBodyC
    : public WidgetBodyC
  {
  public:
    SliderBodyC(RealT nvalue, RealT nlower, RealT nupper, 
		RealT nstep_increment = 1,
		RealT npage_increment = 1,
		RealT npage_size = 1);
    //: Constructor.
    
    SliderBodyC(bool nvert,RealT nvalue, RealT nlower, RealT nupper, 
		RealT nstep_increment = 1,
		RealT npage_increment = 1,
		RealT npage_size = 1);
    //: Constructor.
    
    virtual bool Create();
    //: Create the widget.
    
    bool UpdateValue(RealT val);
    //: Update the slider value.
    
    bool UpdateRange(RealT lower,RealT upper);
    //: Update the slider value.
    
    bool Update(RealT val,RealT lower,RealT upper,RealT inc = 1);
    //: Update the slider value.
    
    inline
      RealT Upper() const 
      { return upper; }
    //: Read upper limit
    
    inline
      RealT Lower() const 
      { return lower; }
    //: Read lower limit
    
    void SetValuePosition(GtkPositionType pos)
      { numPos = pos; }
    //: Set number position.
    // Only has effect BEFORE Create() is called.
    // Values for pos are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKPOSITIONTYPE">here</A>.
    
    void SetDrawValue(bool ndrawValue)
      { drawValue = ndrawValue; }  
    //: Draw the value of the slider ?
    // Only has effect BEFORE Create() is called.
    
    Signal1C<RealT> &SigChanged() { return sigChanged; }
    //: Access changed signal.
    
  protected:
    bool GUIUpdateValue(RealT &val);
    //: Update the slider value.
    
    bool GUIUpdateRange(RealT &lower,RealT &upper);
    //: Update the slider value.
    
    bool GUIUpdate(RealT &val,RealT &lower,RealT &upper,RealT &inc);
    //: Update the slider value.
    
    bool setConfig;
    
    RealT value;
    RealT lower;  
    RealT upper;  
    RealT step_increment;
    RealT page_increment;  
    RealT page_size;
    GtkObject *adj;
    IntT digits; // No of digits after decimal point.
    bool updateCont; // Update continously ?
    bool vert;  // Vertical ?
    bool sReq; // Serive request pending.
    GtkPositionType numPos;
    bool drawValue; // Draw the current value ?
    bool setValue;  // Flag if value has been set.
    Signal1C<RealT> sigChanged; // Signal value change.
    
    friend class SliderC;
  };
  
  //! userlevel=Normal
  //: Slider

  class SliderC 
    : public WidgetC
  {
  public:
    SliderC()
      {}
    //: Default constructor.
    
    SliderC(RealT nvalue, RealT nlower, RealT nupper, 
	    RealT nstep_increment = 1,RealT npage_increment = 1,
	    RealT npage_size = 1)
      : WidgetC(*new SliderBodyC(nvalue,nlower,nupper, 
				   nstep_increment,npage_increment,
				   npage_size))
      {}
    //: Constructor
    
    SliderC(bool nvert,RealT nvalue, RealT nlower, RealT nupper, 
	    RealT nstep_increment = 1,RealT npage_increment = 1,
	    RealT npage_size = 1)
      : WidgetC(*new SliderBodyC(nvert,nvalue,nlower,nupper, 
				   nstep_increment,npage_increment,
				    npage_size))
    {}
    //: Constructor
    
    SliderC(SliderBodyC &bod)
      : WidgetC(bod)
      {}
    //: Body Constructor.
    
  protected:
    SliderBodyC &Body() 
      { return static_cast<SliderBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const SliderBodyC &Body() const 
      { return static_cast<const SliderBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    bool GUIUpdateValue(RealT &val)
      { return Body().GUIUpdateValue(val); }
    //: Update the slider value.
    
    bool GUIUpdateRange(RealT &lower,RealT &upper)
      { return Body().GUIUpdateRange(lower,upper); }
    //: Update the slider value.
    
    bool GUIUpdate(RealT &val,RealT &lower,RealT &upper,RealT &inc)
      { return Body().GUIUpdate(val,lower,upper,inc); }
    //: Update the slider value.
    
  public:
    void SetValuePosition(GtkPositionType pos)
      { Body().SetValuePosition(pos); }
    //: Set number position.
    // Only has effect BEFORE Create() is called.
    // Values for pos are listed <A HREF="http://developer.gnome.org/doc/API/gtk/gtk-standard-enumerations.html#GTKPOSITIONTYPE">here</A>.
    
    void SetDrawValue(bool ndrawValue)
      { Body().SetDrawValue(ndrawValue); }
    //: Set draw value.
    
    bool UpdateValue(RealT val)
      { return Body().UpdateValue(val); }
    //: Update the slider value.
    
    bool UpdateRange(RealT lower,RealT upper)
      { return Body().UpdateRange(lower,upper); }
    //: Update the slider value.
    
    bool Update(RealT val,RealT lower,RealT upper,RealT inc = 1)
      { return Body().Update(val,lower,upper,inc); }
    //: Update the slider value.
    
    RealT Upper() const 
      { return Body().Upper(); }
  //: Read upper limit
    
    RealT Lower() const 
      { return Body().Lower(); }
    //: Read lower limit
    
    Signal1C<RealT> &SigChanged() 
      { return Body().SigChanged(); }
    //: Access changed signal.
    
    friend class SliderBodyC;
  };
  
  template<class DataT>
  SliderC SliderV(RealT nvalue, 
		  RealT nlower, 
		  RealT nupper, 
		  RealT nstep_increment,
		  const DataT &obj,bool (DataT::*func)(RealT &value))
  {
    SliderC ret(true,nvalue,nlower,nupper,nstep_increment);
    Connect(ret.SigChanged(),obj,func,nvalue);
    return ret;
  }
  //: Vertical slider with call back to class.

  template<class DataT,class ParmT>
  SliderC SliderV(RealT nvalue, 
		  RealT nlower, 
		  RealT nupper, 
		  RealT nstep_increment,
		  bool (*func)(RealT &value,ParmT &par),const ParmT &pt = ParmT())
  {  
    SliderC ret(true,nvalue,nlower,nupper,nstep_increment);
    Connect(ret.SigChanged(),obj,func,nvalue,pt);
    return ret;
  }
  //: Vertical slider with call back to function.

  template<class DataT>
  SliderC SliderH(RealT nvalue, 
		  RealT nlower, 
		  RealT nupper, 
		  RealT nstep_increment,
		  const DataT &obj,bool (DataT::*func)(RealT &value))
  {
    SliderC ret(false,nvalue,nlower,nupper,nstep_increment);
    Connect(ret.SigChanged(),obj,func,nvalue);
    return ret;
  }
  //: Horizontal slider with call back to class.

  template<class DataT,class ParmT>
  SliderC SliderH(RealT nvalue, 
		  RealT nlower, 
		  RealT nupper, 
		  RealT nstep_increment,
		  bool (*func)(RealT &value,ParmT &par),const ParmT &pt = ParmT())
  {  
    SliderC ret(false,nvalue,nlower,nupper,nstep_increment);
    Connect(ret.SigChanged(),obj,func,nvalue,pt);
    return ret;
  }
  //: Horizontal slider with call back to function.

  template<class DataT>
  SliderC SliderV(RealT nvalue, 
		  RealT nlower, 
		  RealT nupper, 
		  RealT nstep_increment,
		  bool (*func)(RealT &value,DataT &dat),
		  const DataT &data = DataT())
  {  
    SliderC ret(true,nvalue,nlower,nupper,nstep_increment);
    RealT tmp = 0;
    Connect(ret.SigChanged(),func,tmp,data);
    return ret;
  }
  //: Veritical slider with call back to function.
  
  template<class DataT>
  SliderC SliderH(RealT nvalue, 
		  RealT nlower, 
		  RealT nupper, 
		  RealT nstep_increment,
		  bool (*func)(RealT &value,DataT &dat),
		  const DataT &data = DataT())
  {  
    SliderC ret(false,nvalue,nlower,nupper,nstep_increment);
    RealT tmp = 0;
    Connect(ret.SigChanged(),func,tmp,data);
    return ret;
  }
  //: Horizontal slider with call back to function.
  
  template<class DataT>
  SliderC SliderVR(RealT nvalue, 
		   RealT nlower, 
		   RealT nupper, 
		   RealT nstep_increment,
		   DataT &obj,bool (DataT::*func)(RealT &value),RealT defVal = 0)
  {
    SliderC ret(true,nvalue,nlower,nupper,nstep_increment);
    ConnectRef(ret.SigChanged(),obj,func,defVal);
    return ret;
  }
  //: Vertical slider with reference call back to class.

  template<class DataT>
  SliderC SliderHR(RealT nvalue, 
		   RealT nlower, 
		   RealT nupper, 
		   RealT nstep_increment,
		   DataT &obj,bool (DataT::*func)(RealT &value),RealT defVal = 0)
  {
    SliderC ret(false,nvalue,nlower,nupper,nstep_increment);
    ConnectRef(ret.SigChanged(),obj,func,defVal);
    return ret;
  }
  //: Horizontal slider with reference call back to class.
  
}

#endif
