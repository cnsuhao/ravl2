// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLTHREADS_CONDITIONAL_HEADER
#define RAVLTHREADS_CONDITIONAL_HEADER 1
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/OS/Threads/Posix/ConditionalMutex.hh"
//! lib=RavlThreads
//! userlevel=Normal
//! docentry="Ravl.OS.Threads"
//! author="Charles Galambos"
//! date="02/07/1999"

#include "Ravl/config.h"

#if !defined(_POSIX_SOURCE) && !defined(__sgi__)
#define _POSIX_SOURCE 1
#endif

//#if defined(__sol2__)
#if RAVL_HAVE_SIGNAL_H
#include <sys/signal.h>
#endif

#include <pthread.h>
#include "Ravl/Types.hh"
#include "Ravl/Threads/Mutex.hh"

namespace RavlN
{
  
  //! userlevel=Normal
  //: Conditional variable.  
  //This wraps the pthreads conditional variable and its associated mutex
  //into a single object.  See man pages on e.g. pthread_cond_init for
  //a full description.  See also SemaphoreC for an example of its
  //use.
  
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
    //: Boardcast a signal to all waiting threads.
    // Always succeeds.
    
    void Signal() 
#if RAVL_HAVE_PTHREAD_COND 
    { pthread_cond_signal(&cond); }
#else
    ;
#endif
    //: Signal one waiting thread.
    // Always succeeds.
    
    void Wait()
#if RAVL_HAVE_PTHREAD_COND 
    { pthread_cond_wait(&cond,&mutex); }
#else
    ;
#endif
      
    //: Wait for conditional.
    // This unlocks the mutex and then waits for a signal.
    // from either Signal or Broadcast, when it get it
    // the mutex is re-locked and control returned to the
    // program. <p>
    // Always succeeds.
    
    bool Wait(RealT maxTime);
    //: Wait for conditional.
    // This unlocks the mutex and then waits for a signal.
    // from either Signal, Broadcast or timeout, when it get it
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
  };
}

#endif
