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
#include "Ravl/Stream.hh"

#include <string.h>

#include <unistd.h>

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN
{
  
  MutexC::MutexC(void) 
  { 
#if defined(NDEBUG)
    ONDEBUG(cerr << "MutexC::MutexC(), Constructing normal mutex. (@:" << ((void*) this) << ") \n");
    // Build a fast mutex.
    int rc;
    if((rc = pthread_mutex_init(&mutex,0)) != 0)
      Error("Failed to create mutex.",errno,rc); 
#else
#if defined(PTHREAD_MUTEX_ERRORCHECK) || defined(PTHREAD_MUTEX_ERRORCHECK_NP) || RAVL_OS_LINUX
    ONDEBUG(cerr << "MutexC::MutexC(), Constructing debuging mutex. (@:" << ((void*) this) << ") \n");
#else
    ONDEBUG(cerr << "MutexC::MutexC(), Attempting to construct debuging mutex but don't know how. \n");
#endif
    // Build an error checking mutex.
    pthread_mutexattr_t mutAttr;
    pthread_mutexattr_init(&mutAttr);
#if defined(PTHREAD_MUTEX_ERRORCHECK) || RAVL_OS_LINUX
    pthread_mutexattr_settype(&mutAttr,PTHREAD_MUTEX_ERRORCHECK);
#else
#if defined(PTHREAD_MUTEX_ERRORCHECK_NP)
    pthread_mutexattr_settype(&mutAttr,PTHREAD_MUTEX_ERRORCHECK_NP);
#endif
#endif
    int rc;
    if((rc = pthread_mutex_init(&mutex,&mutAttr)) != 0)
      Error("Failed to create mutex.",errno,rc); 
    pthread_mutexattr_destroy(&mutAttr);
#endif
    //ONDEBUG(cerr << "MutexC::MutexC(), Construction complete. \n");
  }
  //: Constructor.
  
  void MutexC::Error(const char *msg)  {
    cerr << "MutexC::Error() :" << msg << " \n";
    RavlAssert(0);
  }
  
  //: Report an error, with an error number.
  
  void MutexC::Error(const char *msg,int anerrno,int rc) {
    cerr << "MutexC::Error() err=" << anerrno << " (" << strerror(anerrno) << ") : " << msg << " \n";
    cerr << "MutexC::Error()  rc=" << rc << " (" << strerror(rc) << ") \n";
    cerr << "MutexC::Error() @:" << ((void*) this) << "\n";
    RavlAssert(0);
  }
  
  //: Destructor.
  MutexC::~MutexC() { 
    ONDEBUG(cerr << "MutexC::~MutexC(), Destroying mutex. (@:" << ((void*) this) << ")\n");
    int maxRetry = 100;
    while(--maxRetry > 0) {
      if(TryLock()) { // Try get an exclusive lock.
	Unlock(); // Unlock... and destroy.
	if(pthread_mutex_destroy(&mutex) == 0)
	  break; // It worked ok..
      }
      OSYield();
    }
    if(maxRetry <= 0)
      cerr << "WARNING: MutexC::~MutexC(), destroy failed. \n";
  }
  
#if !RAVL_USE_INLINEMUTEXCALLS  
  //: Lock mutex.
  
  bool MutexC::Lock(void) {
    int rc;
    //ONDEBUG(cerr << "MutexC::Lock() Start @:" << ((void*) this) << " \n");
    if((rc = pthread_mutex_lock(&mutex)) == 0) {
      //ONDEBUG(cerr << "MutexC::Lock() Obtained @:" << ((void*) this) << " \n");
      return true;
    }
    Error("Lock failed",errno,rc);
    return false;
  }
    
  //: Try and lock mutex.
  
  bool MutexC::TryLock(void) {
    int rc;
    //ONDEBUG(cerr << "MutexC:TryLock() @:" << ((void*) this) << " \n");
    if((rc = pthread_mutex_trylock(&mutex)) == 0) {
      //ONDEBUG(cerr << "MutexC:TryLock() Succeeded. @:" << ((void*) this) << "  \n");
      return true;
    }
    //ONDEBUG(cerr << "MutexC:TryLock() Failed. @:" << ((void*) this) << "  rc=" << rc << "\n");
    if(rc != EBUSY && rc != EDEADLK)
      Error("Trylock failed for unexpected reason.",errno,rc);
    return false;
  }
    
  //: Unlock mutex.
  
  bool MutexC::Unlock(void) {
    //RavlAssertMsg(!TryLock(),"MutexC::Unlock() called on an unlocked mutex.");
    
    int rc;
    //ONDEBUG(cerr << "MutexC:Unlock() @:" << ((void*) this) << "\n");
    if((rc = pthread_mutex_unlock(&mutex)) == 0) {
      //ONDEBUG(cerr << "MutexC::Unlock() Released @:" << ((void*) this) << " \n");
      return true;
    }
    Error("Unlock failed.",errno,rc);
    return false;
  }
#endif
  
}
