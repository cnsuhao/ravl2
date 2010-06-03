// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLTHREADS_CONDITIONAL_HEADER
#define RAVLTHREADS_CONDITIONAL_HEADER 1
/////////////////////////////////////////////////
//! rcsid="$Id: ConditionalMutex.hh 7000 2008-10-20 11:13:34Z robowaz $"
//! file="Ravl/OS/Threads/Posix/ConditionalMutex.hh"
//! lib=RavlThreads
//! userlevel=Normal
//! docentry="Ravl.API.OS.Threads"
//! author="Charles Galambos"
//! date="02/07/1999"

#include "Ravl/config.h"

#if !defined(_POSIX_SOURCE) && !defined(__sgi__) && !RAVL_OS_FREEBSD
#define _POSIX_SOURCE 1
#endif

//#if defined(__sol2__)
#if RAVL_HAVE_SIGNAL_H
#include <sys/signal.h>
#endif

#if RAVL_HAVE_WIN32_THREADS
#include <windows.h>
#endif
#if RAVL_HAVE_POSIX_THREADS
#include <pthread.h>
#endif

#include "Ravl/Types.hh"
#include "Ravl/Threads/Mutex.hh"

namespace RavlN
{
  
  //! userlevel=Normal
  //: Sleeping until signal arrives.
  //
  // <p>This class implements a "condition variable".  
  // It causes a thread to sleep until signalled from another thread.  </p>
  //
  // <p>ConditionalMutexC wraps the pthreads condition variable and
  // its associated mutex
  // into a single object.  See man pages on e.g. pthread_cond_init for
  // a full description.  See also SemaphoreC for an example of its
  // use.</p>
  
  class ConditionalMutexC 
    : public MutexC 
  {
  public:
    ConditionalMutexC() 
#if RAVL_HAVE_PTHREAD_COND 
    { if(pthread_cond_init(&cond,0)) 
      Error("pthread_cond_init failed. \n");
    }
#else
    ;
#endif
    //: Constructor.
    
    ~ConditionalMutexC();
    //: Destructor

    void Broadcast()
#if RAVL_HAVE_PTHREAD_COND 
    { pthread_cond_broadcast(&cond); }
#else
    ;
#endif
    //: Broadcast a signal to all waiting threads.
    // Always succeeds.
    
    void Signal() 
#if RAVL_HAVE_PTHREAD_COND 
    { pthread_cond_signal(&cond); }
#else
    ;
#endif
    //: Signal one waiting thread.
    // Always succeeds.  The particular thread selected is arbitrary.
    
    void Wait()
#if RAVL_HAVE_PTHREAD_COND 
    { pthread_cond_wait(&cond,&mutex); }
#else
    ;
#endif
    //: Wait for conditional.
    // This unlocks the mutex and then waits for a signal
    // from either Signal or Broadcast.  When it gets the signal
    // the mutex is re-locked and control returned to the
    // program. <p>
    // Always succeeds.
    
    bool Wait(RealT maxTime);
    //: Wait for conditional.
    // This unlocks the mutex and then waits for a signal
    // from either Signal, Broadcast or timeout.  When it get the signal
    // the mutex is re-locked and control returned to the
    // program. <p>
    // Returns false, if timeout occures.
    
  private:
    ConditionalMutexC(const ConditionalMutexC &)
    {}
    //: This is just a bad idea.
    
#if RAVL_HAVE_PTHREAD_COND 
    pthread_cond_t cond;
#endif
#if RAVL_HAVE_WIN32_THREADS
    volatile LONG count;
    HANDLE sema; // Flow control semaphore.
#endif
  };
}

#endif
