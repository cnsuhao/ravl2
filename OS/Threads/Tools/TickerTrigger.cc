// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Tools/TickerTrigger.cc"

#include "Ravl/Threads/TickerTrigger.hh"
#include "Ravl/Stream.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  int TickerTriggerBodyC::Start() { 
#if 0
    try {
#endif
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
#if 0
    } catch(...) {
      // FIXME: Is there any valid exception that can pass through here ???
      cerr << "WARNING: Ticker aborted on exception. " << ((void *) this)  << "\n";
      throw ;
    }
#endif
    ONDEBUG(cerr << "Ticker done... " <<  ((void *) this) <<". Delay:" << delay << " \n");
    return 0;
  }
  
}
