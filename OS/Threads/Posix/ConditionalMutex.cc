// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Posix/ConditionalMutex.cc"

#ifdef __sol2__
#define __EXTENSIONS__ 1
#endif

#include "Ravl/Threads/ConditionalMutex.hh"
#include "Ravl/Threads/Thread.hh"
#include "Ravl/Math.hh"

#include <sys/time.h>
#if RAVL_HAVE_UNISTD_H
#include <unistd.h>
#endif

#define NANOSEC 1000000000

namespace RavlN
{

#if RAVL_HAVE_PTHREAD_COND 
  //: Destructor
  
  ConditionalMutexC::~ConditionalMutexC() { 
    int maxRetry = 100;
    while(pthread_cond_destroy(&cond) && --maxRetry > 0) 
      Yield();
    if(maxRetry <= 0)
      Error("WARNING: ConditionalMutexC::~ConditionalMutexC(), destroy failed. \n");
  }
  
  bool ConditionalMutexC::Wait(RealT maxTime) { 
    if(maxTime <= 0)
      return false;
    
    struct timespec ts;
    struct timeval tv;

    // Work out delay.
    long secs = Floor(maxTime);
    long nsecs = (long) ((RealT) ((RealT) maxTime - ((RealT) secs)) * NANOSEC);
    
    // Get current time.
    gettimeofday(&tv,0);
    int errcode;
    ts.tv_sec = tv.tv_sec;
    ts.tv_nsec = tv.tv_usec * 1000;
    
    // Add them.
    
    ts.tv_sec += secs;
    ts.tv_nsec += nsecs;
    if(ts.tv_nsec > NANOSEC) {
      ts.tv_sec += 1;
      ts.tv_nsec -= NANOSEC;
    }
    
    
    do {
      errcode = pthread_cond_timedwait(&cond,&mutex,&ts); 
      if(errcode == ETIMEDOUT)
	break;
      // May be interupted by EINTR... ignore and restart the wait.
    } while(errcode != 0);
    
    return (errcode != ETIMEDOUT);
  }

#else  
  // ----------------------------------------------------------------
  // Some stubs we may fill in later.
  
  ConditionalMutexC::~ConditionalMutexC() { 
  }
  
  bool ConditionalMutexC::Wait(RealT maxTime) {
    RavlAssert(0);// Not implemented.
    return false;
  }
  
  ConditionalMutexC::ConditionalMutexC() {
    RavlAssert(0);// Not implemented.
  }
  
  //: Boardcast a signal to all waiting threads.
  // Always succeeds.
  
  void ConditionalMutexC::Broadcast() { 
    RavlAssert(0); // Not implemented.
  }
  
  //: Signal one waiting thread.
  // Always succeeds.
    
  void ConditionalMutexC::Signal() { 
    RavlAssert(0); // Not implemented.
  }
  
  void ConditionalMutexC::Wait() { 
    RavlAssert(0); // Not implemented.
  }
    
#endif  
}
