// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLTRIGGER_HEADER
#define RAVLTRIGGER_HEADER 1
//////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Base/Trigger.hh"
//! lib=RavlCore
//! userlevel=Default
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Core.Misc"

#include "Ravl/RefCounter.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Signal Event handle
  
  class TriggerBodyC
    : public RCBodyVC
  {
  public:
    TriggerBodyC()
      {}
    //: Default constructor.
    
    virtual void Invoke();
    //: Trigger event.
  };
  
  //! userlevel=Normal
  //: Signal Event handle
  
  class TriggerC
    : public RCHandleC<TriggerBodyC>
  {
  public:
    TriggerC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    TriggerC(TriggerBodyC &bod) 
      : RCHandleC<TriggerBodyC>(bod)
      {}
    //: Body constructor.x
    
    TriggerBodyC &Body()
      { return  RCHandleC<TriggerBodyC>::Body(); }
    //: Access body.
    
    const TriggerBodyC &Body() const
      { return  RCHandleC<TriggerBodyC>::Body(); }
    //: Access body.
    
  public:
    void Invoke()
      { Body().Invoke(); }
    //: Invoke signal.
  };


}

#endif
