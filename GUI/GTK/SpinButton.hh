// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUISPINBUTTON_HEADER
#define RAVLGUISPINBUTTON_HEADER 1
//////////////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"
//! file="Ravl/GUI/GTK/SpinButton.hh"
//! lib=RavlGUI
//! date="29/08/99"
//! docentry="Ravl.GUI.Control"

#include "Ravl/GUI/Widget.hh"
#include "Ravl/Threads/Signal1.hh"

namespace RavlGUIN {
  class SpinButtonC;
  
  //! userlevel=Develop
  //: Spin button body.
  
  class SpinButtonBodyC
    : public WidgetBodyC
  {
  public:
    SpinButtonBodyC(IntT digits,RealT nclimbRate,RealT nvalue,RealT nlower,RealT nupper,RealT nstep_increment);
    //: Default constructor.
    
    Signal1C<RealT> &SigChanged() { return sigChanged; }
    //: Access changed signal.
    
    void SetValue(RealT val);
    //: Set value 
    // Thread safe.
    
    bool GUISetValue(RealT val);
    //: Set value 
    // GUI thread only.
    
    RealT Value();
    //: Get current value.
    
  protected:
    virtual bool Create();
    //: Create widget.
    
    virtual void Destroy();
    //: Undo all references.
    
    IntT  digits;
    RealT climbRate;
    RealT value;
    RealT lower;  
    RealT upper;  
    RealT step_increment;
    
    GtkObject *adj;
    
    Signal1C<RealT> sigChanged; // Signal value change.
    
    friend class SpinButtonC;
  };
  
  //! userlevel=Normal
  //: Spin button body.
  
  class SpinButtonC
    : public WidgetC
  {
  public:
    SpinButtonC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SpinButtonC(IntT digits,RealT nclimbRate,RealT nvalue,RealT nlower,RealT nupper,RealT nstep_increment)
      : WidgetC(*new SpinButtonBodyC(digits,nclimbRate,nvalue,nlower,nupper,nstep_increment))
      {}
    //: Constructor.
    
  protected:
    SpinButtonC(SpinButtonBodyC &bod)
      : WidgetC(bod)
    {}
    //: Body constructor.
    
    SpinButtonBodyC &Body()
    { return static_cast<SpinButtonBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const SpinButtonBodyC &Body() const
    { return static_cast<const SpinButtonBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
    Signal1C<RealT> &SigChanged() 
    { return Body().SigChanged(); }
    //: Access changed signal.
    
    void SetValue(RealT &val)
    { Body().SetValue(val); }
    //: Set value 
    // Thread safe.
    
    bool GUISetValue(RealT &val)
    { return Body().GUISetValue(val); }
    //: Set value 
    // GUI thread only.

    RealT Value()
    { return Body().Value(); }
    //: Get current value.
    
    friend class SpinButtonBodyC;
  };
  

  template<class DataT>
  SpinButtonC SpinButton(RealT nvalue,
			 RealT nlower, 
			 RealT nupper, 
			 RealT nstep_increment,
			 bool (*func)(RealT &value))
  {
    SpinButtonC ret(2,1,nvalue,nlower,nupper,nstep_increment);
    Connect(ret.SigChanged(),obj,func,defVal,nvalue);
    return ret;
  }
  //: Construct spin button with callback to class method.

  template<class DataT,class ParamT>
  SpinButtonC SpinButton(RealT nvalue,
			 RealT nlower, 
			 RealT nupper, 
			 RealT nstep_increment,
			 bool (*func)(RealT &value,ParamT &parm) = 0,const ParamT &parm)
  {
    SpinButtonC ret(2,1,nvalue,nlower,nupper,nstep_increment);
    Connect(ret.SigChanged(),obj,func,nvalue,parm);
    return ret;
  }
  //: Construct spin button with callback to class method.
  
  template<class DataT>
  SpinButtonC SpinButton(RealT nvalue,
			 RealT nlower, 
			 RealT nupper, 
			 RealT nstep_increment,
			 const DataT &obj,bool (DataT::*func)(RealT &value),RealT defVal = 0)
  {
    SpinButtonC ret(2,1,nvalue,nlower,nupper,nstep_increment);
    Connect(ret.SigChanged(),obj,func,defVal);
    return ret;
  }
  //: Construct spin button with callback to class method.
  
  template<class DataT>
  SpinButtonC SpinButtonR(RealT nvalue,
			  RealT nlower, 
			  RealT nupper, 
			  RealT nstep_increment,
			  DataT &obj,bool (DataT::*func)(RealT &value),RealT defVal = 0)
  {
    SpinButtonC ret(2,1,nvalue,nlower,nupper,nstep_increment);
    ConnectRef(ret.SigChanged(),obj,func,defVal);
    return ret;
  }
  //: Construct spin button with callback to referenced class method.
  
}
#endif
