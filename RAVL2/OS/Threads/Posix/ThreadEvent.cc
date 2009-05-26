// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Posix/ThreadEvent.cc"

#include "Ravl/Threads/ThreadEvent.hh"

namespace RavlN
{
  //: Wait for an event.
  // Returns false if timed out.
  
  bool ThreadEventC::Wait(RealT maxTime) {
    if(occurred) // Check before we bother with locking.
      return true;
    bool ret(true);
    cond.Lock();
    while(!occurred && ret) 
      ret = cond.Wait(maxTime);
    cond.Unlock();
    return ret;
  }

  //: Wait for lock to be free.
  // NB. This is only garanteed to work for one thread.
  
  bool ThreadEventC::WaitForFree() {
    if(waiting == 0)
      return true;
    cond.Lock();
    while(waiting != 0) 
      cond.Wait();
    cond.Unlock();
    return true;
  }
  
  
}
