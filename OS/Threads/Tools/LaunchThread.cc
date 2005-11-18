// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Tools/LaunchThread.cc"

#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/Threads/MessageQueue.hh"
#include "Ravl/Stream.hh"
#include "Ravl/OS/SysLog.hh"

#define RAVL_REUSE_THREADS 0

namespace RavlN {
#if RAVL_REUSE_THREADS
  MessageQueueC<LaunchThreadC> launchThreads(32);
#endif
  
  //: Constructor.

  LaunchThreadBodyC::LaunchThreadBodyC(const TriggerC &nse)
    : se(nse)
  {}

  LaunchThreadBodyC::LaunchThreadBodyC(SizeT initStackSize,const TriggerC &nse)
    : ThreadBodyC(initStackSize),
      se(nse)
  {}
  
  int LaunchThreadBodyC::Start() {
    
#if RAVL_REUSE_THREADS
    do {
      if(se.IsValid()) {
	se.Invoke(); 
	done.Post();
	done.WaitForFree(); // Wait for everything to re-execute.
	done.Reset();
      } else 
	cerr << "ERROR: LaunchThreadBodyC::Startup(), ask to launch an invalid event.\n";
      
      reStart.Reset();
      
      LaunchThreadC le(*this);
      se.Invalidate();
      if(!launchThreads.TryPut(le)) 
	break ; // Just exit, queue is full.
      
      reStart.Wait();
    } while(1) ;
#else
    se.Invoke();
    done.Post();
#endif    
    return true;
  }
  
  //: Reset signal event.
  // Setup new event....
  
  void LaunchThreadBodyC::Reset(const TriggerC &nse) {
#if RAVL_REUSE_THREADS
    se = nse;
    RavlAssert(!done);
    //done.Reset();
    //assert(reStart.Count() == 0);
    reStart.Post();
#else
    RavlAssertMsg(0,"LaunchThreadBodyC::Reset(), Not supported. "); // Incase someone is using this method.
#endif
  }
  
  //: Constructor.
  
  LaunchThreadC::LaunchThreadC(const TriggerC &nse)
  {
#if RAVL_REUSE_THREADS    
    LaunchThreadC me;
    if(launchThreads.TryGet(me)) {
      SysLog(SYSLOG_DEBUG) << "LaunchThreadC::LaunchThreadC(), Reusing thread.  ";
      (*this) = me;
      Reset(nse);
      return ;
    }
    SysLog(SYSLOG_DEBUG) << "LaunchThreadC::LaunchThreadC(), Creating new thread.  ";
#endif
    LaunchThreadC newun(*new LaunchThreadBodyC(nse));
    (*this) = newun;
    Execute(); 
  }

  //: Constructor.
  
  LaunchThreadC::LaunchThreadC(SizeT initStackSize,const TriggerC &nse) {
    LaunchThreadC newun(*new LaunchThreadBodyC(initStackSize,nse));
    (*this) = newun;
    Execute(); 
  }
  
}
