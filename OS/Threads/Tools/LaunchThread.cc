// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads

#include "Ravl/Threads/LaunchThread.hh"
#include <iostream.h>
#include "Ravl/Threads/MessageQueue.hh"

namespace RavlN {
  MessageQueueC<LaunchThreadC> launchThreads(32);
  
  //: Constructor.

  LaunchThreadBodyC::LaunchThreadBodyC(const TriggerC &nse)
    : se(nse)
  {}

  int LaunchThreadBodyC::Start()
  { 
    do {
      if(se.IsValid()) {
	se.Invoke(); 
	done.Post();
	done.WaitForFree(); // Wait for everything to re-execute.
      } else 
	cerr << "ERROR: LaunchThreadBodyC::Startup(), ask to launch an invalid event.\n";
      
      LaunchThreadC le(*this);
      se.Invalidate();
      if(!launchThreads.TryPut(le)) 
	break ;
      reStart.Wait();
      reStart.Reset();
    } while(1) ;
    
    return true;
  }
  
  //: Reset signal event.
  // Setup new event....
  
  void LaunchThreadBodyC::Reset(const TriggerC &nse) {
    se = nse;
    done.Reset();
    //assert(reStart.Count() == 0);
    reStart.Post();
  }
  
  //: Constructor.
  
  LaunchThreadC::LaunchThreadC(const TriggerC &nse)
    
  {
    LaunchThreadC me;
    if(launchThreads.TryGet(me)) {
      (*this) = me;
      Reset(nse);
      return ;
    }
    LaunchThreadC newun(*new LaunchThreadBodyC(nse));
    (*this) = newun;
    Execute(); 
  }
  
}
