// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLTHREADS_EVENT_HEADER
#define RAVLTHREADS_EVENT_HEADER 1
/////////////////////////////////////////////////
//! rcsid="$Id: ThreadEvent.hh 7746 2010-06-02 09:50:15Z alexkostin $"
//! file="Ravl/OS/Threads/Posix/ThreadEvent.hh"
//! lib=RavlThreads
//! userlevel=Normal
//! docentry="Ravl.API.OS.Threads"
//! author="Charles Galambos"
//! date="25/05/2000"

#include "Ravl/config.h"
#include "Ravl/Threads/ConditionalMutex.hh"
#include "Ravl/Stream.hh"

namespace RavlN
{
  //! userlevel=Normal
  //: Broadcast Event.
  
  class ThreadEventC {
  public:
    ThreadEventC()
      : occurred(false),
	waiting(0)
    {}
    
    bool Post() {
      cond.Lock();
      if(occurred) {
	cond.Unlock();
	return false;
      }
      occurred = true;
      cond.Unlock();
      cond.Broadcast();
      return true;
    }
    //: Post an event.
    // Returns true, if event has been posted by this thread.
    
    ~ThreadEventC()  { 
      if(!occurred)
	Post(); 
      if(waiting != 0) 
	cerr << "PThread::~ThreadEvent(), WARNING: Called while threads waiting. \n";
    }
    //: Destructor.
    
    void Wait() {
      if(occurred) // Check before we bother with locking.
        return ;
      cond.Lock();
      waiting++;
      while(!occurred)
        cond.Wait();
      waiting--;
      if(waiting == 0) {
        cond.Unlock();
        cond.Broadcast(); // If something is waiting for it to be free...
        return ;
      } 
      cond.Unlock();
    }
    //: Wait indefinitely for an event.
    
    bool WaitForFree();
    //: Wait for lock to be free of all waiters.
    
    IntT ThreadsWaiting() const 
    { return waiting; }
    //: Get approximation of number of threads waiting.
    
    bool Wait(RealT maxTime);
    //: Wait for an event.
    // Returns false if timed out.
    
    operator bool() const 
    { return occurred; }
    //: Test if the event has occurred.
    
    bool Occurred() const
    { return occurred; }
    //: Test if event has occrued.
    
    void Reset()
    { occurred = false; }
    //: Reset an event.
    
  protected:
    ConditionalMutexC cond;
    volatile bool occurred;
    volatile IntT waiting; // Count of number of threads waiting on this...
  };
};

#endif
