// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Posix/Mutex.cc"

#include "Ravl/Threads/Mutex.hh"
#include "Ravl/Threads/Thread.hh"
#include <iostream.h>
#include <string.h>

namespace RavlN
{
  
  MutexC::MutexC(void) { 
#if defined(NDEBUG)
    // Build a fast mutex.
    if(pthread_mutex_init(&mutex,0) != 0)
      Error("Failed to create mutex.",errno); 
#else
    // Build an error checking mutex.
    pthread_mutexattr_t mutAttr;
    pthread_mutexattr_init(&mutAttr);
#if defined(PTHREAD_MUTEX_ERRORCHECK)
    pthread_mutexattr_settype(&mutAttr,PTHREAD_MUTEX_ERRORCHECK);
#else
#if defined(PTHREAD_MUTEX_ERRORCHECK_NP)
    pthread_mutexattr_settype(&mutAttr,PTHREAD_MUTEX_ERRORCHECK_NP);
#else
    mutAttr.__mutexkind = PTHREAD_MUTEX_ERRORCHECK_NP;
#endif
#endif
    if(pthread_mutex_init(&mutex,&mutAttr) != 0)
      Error("Failed to create mutex.",errno); 
    pthread_mutexattr_destroy(&mutAttr);
#endif
  }
  //: Constructor.

  void MutexC::Error(const char *msg) 
  {
    cerr << "MutexC::Error() :" << msg << " \n";
  }
  
  //: Report an error, with an error number.
  
  void MutexC::Error(const char *msg,int anerrno)
  {
    cerr << "MutexC::Error() " << anerrno << " (" << strerror(anerrno) << ") :" << msg << " \n";
  }
  
  //: Destructor.
  MutexC::~MutexC() { 
    int maxRetry = 100;
    while(--maxRetry > 0) {
      if(TryLock()) { // Try get an exclusive lock.
	Unlock(); // Unlock... and destroy.
	if(pthread_mutex_destroy(&mutex) == 0)
	  break; // It worked ok..
      }
      Yield();
    }
    if(maxRetry <= 0)
      cerr << "WARNING: MutexC::~MutexC(), destroy failed. \n";
  }
  

}
