// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLTHREADS_EVENT_HEADER
#define RAVLTHREADS_EVENT_HEADER 1
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="amma/StdType/System/PThreads/Posix/Event.hh"
//! lib=RavlThreads
//! userlevel=Normal
//! docentry="Ravl.OS.Threads"
//! author="Charles Galambos"
//! date="25/05/2000"

#include <iostream.h>
#include "Ravl/Threads/ConditionalMutex.hh"

namespace RavlN
{
  //! userlevel=Normal
  //: Broadcast Event.
  
  class ThreadEventC {
  public:
    ThreadEventC()
      : occured(false),
	waiting(0)
      {}
    
    bool Post() {
      cond.Lock();
      if(occured) {
	cond.Unlock();
	return false;
      }
      occured = true;
      cond.Unlock();
      cond.Broadcast();
      return true;
    }
    //: Post an event.
    // Returns true, if event has been posted by this thread.
    
    ~ThreadEventC()  { 
      if(!occured)
	Post(); 
      if(waiting != 0) 
	cerr << "PThread::~ThreadEvent(), WARNING: Called while threads waiting. \n";
    }
    //: Destructor.
    
    void Wait() {
      if(occured) // Check before we bother with locking.
	return ; 
      cond.Lock();
      waiting++;
      while(!occured)
	cond.Wait();
      waiting--;
      if(waiting == 0) {
	cond.Unlock();
	cond.Broadcast(); // If something is waiting for it to be free...
	return ;
      } 
      cond.Unlock();
    }
    //: Wait indefinitly for an event.
    
    bool WaitForFree();
    //: Wait for lock to be free of all waiters.
    
    IntT ThreadsWaiting() const 
      { return waiting; }
    //: Get approximation of number of threads waiting.
    
    bool Wait(RealT maxTime);
    //: Wait for an event.
    // Returns false if timed out.
    
    operator bool() const 
      { return occured; }
    //: Test if the event has occured.
    
    bool Occured() const
      { return occured; }
    //: Test if event has occrued.
    
    void Reset()
      { occured = false; }
    //: Reset an event.
    
  protected:
    ConditionalMutexC cond;
    bool occured;
    IntT waiting; // Count of number of threads waiting on this...
  };
};

#endif
