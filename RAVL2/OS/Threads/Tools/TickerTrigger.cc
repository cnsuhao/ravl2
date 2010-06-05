// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////
//! rcsid="$Id: TickerTrigger.cc 5595 2006-06-16 10:32:41Z craftit $"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Tools/TickerTrigger.cc"

#include "Ravl/Threads/TickerTrigger.hh"
#include "Ravl/Stream.hh"
#include "Ravl/OS/SysLog.hh"
#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {

  //: Thread shutdown.
  
  void TickerTriggerBodyC::Terminate() {
    Shutdown();
  }
  
  int TickerTriggerBodyC::Start() { 
    try {
      ONDEBUG(cerr << "Ticker started... " <<  ((void *) this) <<". Delay:" << delay << " \n");
      if(!se.IsValid()) {
	cerr << "ERROR: TickerTriggerBodyC::Startup(), ask to launch an invalid event.\n";
	return 1;
      }
      while(delay > 0 && !terminatePending) {
	next.SetToNow();
	next += delay;
	ONDEBUG(cerr << "Ticker called " << ((void *) this) <<". \n");
	se.Invoke();
	next.Wait();
      }
    } catch(...) {
      // FIXME: Is there any valid exception that can pass through here ???
      SysLog(SYSLOG_WARNING) << "Ticker aborted on exception. " << ((void *) this)  << "\n";
    }
    ONDEBUG(cerr << "Ticker done... " <<  ((void *) this) <<". Delay:" << delay << " \n");
    return 0;
  }
  
}
