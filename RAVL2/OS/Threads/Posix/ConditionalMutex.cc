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

#include "Ravl/config.h"
#if RAVL_OS_SOLARIS
#define __EXTENSIONS__ 1
#endif

#include "Ravl/Threads/ConditionalMutex.hh"
#include "Ravl/Threads/Thread.hh"
#include "Ravl/Math.hh"

#if defined(VISUAL_CPP)
#include <time.h>
#else
#include <sys/time.h>
#endif

#if RAVL_HAVE_UNISTD_H
#include <unistd.h>
#include <errno.h>
#endif

#include <iostream>

#define NANOSEC 1000000000

namespace RavlN
{

#if RAVL_HAVE_PTHREAD_COND 
  //: Destructor
  
  ConditionalMutexC::~ConditionalMutexC() { 
    int maxRetry = 100;
    while(pthread_cond_destroy(&cond) && --maxRetry > 0) 
      OSYield();
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
    if(ts.tv_nsec >= NANOSEC) {
      ts.tv_sec += 1;
      ts.tv_nsec -= NANOSEC;
    }
    
    do {
      errcode = pthread_cond_timedwait(&cond,&mutex,&ts); 
      if(errcode == ETIMEDOUT)
        break;
      // May be interupted by EINTR... ignore and restart the wait.
      if ( errcode == 0 ) break ;
      RavlAssertMsg(errcode == EINTR,"ConditionalMutexC::Wait(), ERROR: Unexpected return code.");
    } while(errcode != 0);
    
    return (errcode != ETIMEDOUT);
  }

#else  
  // ----------------------------------------------------------------
  
  ConditionalMutexC::ConditionalMutexC() 
    : count(0)
  {
#if RAVL_HAVE_WIN32_THREADS
    sema = CreateSemaphore(0,0,0x7fffffff,0);
#endif
  }
  
  
  ConditionalMutexC::~ConditionalMutexC() { 
#if RAVL_HAVE_WIN32_THREADS
    CloseHandle(sema);
    sema = 0;
#endif
  }
  
  static bool DecrementNotBelowZero(volatile LONG &count) {
    LONG tmp,ret;
    do {
      tmp = count;
      if(tmp == 0) 
        return false;
      ret = InterlockedCompareExchange(&count,tmp-1,tmp); // Try and decrement by one.
      // Check if decrement worked, if not try again.
    } while(ret != tmp);
    return true;
  }

  bool ConditionalMutexC::Wait(RealT maxTime) {
#if RAVL_HAVE_WIN32_THREADS
    int rc;
    InterlockedIncrement(&count); // Register our interest in getting signalled
    Unlock();
    rc = WaitForSingleObject(sema,Round(maxTime * 1000.0));
    Lock();
    if(rc != WAIT_OBJECT_0) {
      if(rc != WAIT_TIMEOUT) {
        // Warn if something unexpected happend.
        cerr << "ConditionalMutexC::Wait(delay), Failed to wait for conditional mutex. \n";
      }
      // Decrement without going less than zero.  This may happen if
      // there's been a broadcast just after WaitForSingleObject. In
      // that case we'll just end up with the semaphore count 1 too high and
      // the program and a Wait() will return early. 
      if(!DecrementNotBelowZero(count)) {
        // If we get here an extra signal must have been posted, decrement it
        // to keep accounting straight.
        cerr <<  "ConditionalMutexC::Wait(delay), Removing left over sema. \n";
        int rc2 = 0;
        do {
          rc2 = WaitForSingleObject(sema,2000);
          if(rc2 != WAIT_OBJECT_0) {
            // This shouldn't happen, though its possible if the machine is heavily loaded.
            cerr << "ConditionalMutexC::Wait(delay), WARNING: Unexpected failure to wait for semaphore. \n";
          }
        } while(rc2 != WAIT_OBJECT_0);
      }
    }

#endif
#if RAVL_HAVE_POSIX_THREADS
    RavlAssert(0);// Not implemented.
#endif
    return (rc == WAIT_OBJECT_0);
  }
  
  
  //: Boardcast a signal to all waiting threads.
  // Always succeeds.
  
  void ConditionalMutexC::Broadcast() { 
#if RAVL_HAVE_POSIX_THREADS
    RavlAssert(0); // Not implemented.
#endif
#if RAVL_HAVE_WIN32_THREADS
    LONG tmp = 0; 
    // Exchange count with zero and post that to the semaphore, this will restart all threads
    // current waiting.
    tmp = InterlockedExchange(&count,tmp);
    if(tmp == 0) return ; // Nothing waiting for signal!
    if(ReleaseSemaphore(sema,tmp,0) == 0) {
      cerr << "ERROR: ConditionalMutex failed to broadcast! \n";
    }
    return ;
#endif
  }
  
  //: Signal one waiting thread.
  // Always succeeds.
    
  void ConditionalMutexC::Signal() { 
#if RAVL_HAVE_POSIX_THREADS
    RavlAssert(0); // Not implemented.
#endif
#if RAVL_HAVE_WIN32_THREADS
    // Decrement atomicly if greater than 0 and then post to semaphore.
    // else just return.
    if(!DecrementNotBelowZero(count))
      return ; // Counter is zero, nothing to signal!
    if(ReleaseSemaphore(sema,1,0) == 0) {
      cerr << "ERROR: ConditionalMutexC::Signal, ERROR: failed to signal!";
    }
    return ;
#endif
  }
  
  void ConditionalMutexC::Wait() { 
#if RAVL_HAVE_WIN32_THREADS
    int rc;
    InterlockedIncrement(&count); // Register our interest in getting signalled
    Unlock();
    rc = WaitForSingleObject(sema,INFINITE); // Wait for signal
    Lock();

    if(rc != WAIT_OBJECT_0) {
      cerr << "ConditionalMutexC::Wait, Failed to wait for conditional mutex. \n";
      // Decrement without going less than zero.  This may happen if
      // there's been a broadcast just after WaitForSingleObject. In
      // that case we'll just end up with the semaphore count 1 too high and
      // the program and a Wait() will return early.
      if(!DecrementNotBelowZero(count)) { 
        // If we get here an extra signal must have been posted, decrement it
        // to keep accounting straight.
        cerr << "ConditionalMutexC::Wait(delay), Decrement leftover semaphore. \n";
        int rc2 = 0;
        do {
          rc2 = WaitForSingleObject(sema,2000);
          if(rc2 != WAIT_OBJECT_0) {
            // This shouldn't happen, unless the machine is heavily loaded.
            cerr << "ConditionalMutexC::Wait(delay), WARNING: Unexpected failure to wait for semaphore. \n";
          }
        } while(rc2 != WAIT_OBJECT_0);
      }
    }
#endif
#if RAVL_HAVE_POSIX_THREADS
    RavlAssert(0); // Not implemented.
#endif
  }
    
#endif  
}
