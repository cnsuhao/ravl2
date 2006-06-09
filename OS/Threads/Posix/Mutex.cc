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
#include "Ravl/Exception.hh"
#include "Ravl/Stream.hh"

#include <string.h>

#if RAVL_HAVE_UNISTD_H
#include <unistd.h>
#endif

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif
#if RAVL_HAVE_WIN32_THREADS
#include <windows.h>
#include <conio.h>
#include "Ravl/OS/Date.hh"
#endif

namespace RavlN
{

  //: Default constructor.
  
  MutexC::MutexC() 
    : isValid(false)
  { Init(false); }
  
  //: Constructor.
  
  MutexC::MutexC(bool recursive) 
    : isValid(false)
  { Init(recursive); }
  
  //: Setup mutex.
  
  void MutexC::Init(bool recursive) {

    // ---------------------------------- POSIX ----------------------------------
#if RAVL_HAVE_POSIX_THREADS
#if defined(NDEBUG)
    ONDEBUG(cerr << "MutexC::Init(), Constructing normal mutex. (@:" << ((void*) this) << ") \n");
    // Build a fast mutex.
    int rc;
    if((rc = pthread_mutex_init(&mutex,0)) != 0)
      Error("Failed to create mutex.",errno,rc); 
#else
#if defined(PTHREAD_MUTEX_ERRORCHECK) || defined(PTHREAD_MUTEX_ERRORCHECK_NP) || RAVL_OS_LINUX
    ONDEBUG(cerr << "MutexC::Init(), Constructing debuging mutex. (@:" << ((void*) this) << ") \n");
#else
    ONDEBUG(cerr << "MutexC::Init(), Attempting to construct debuging mutex but don't know how. \n");
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
    if(recursive) { // Do we need a recursive mutex ?
#if ( RAVL_OS_LINUX || RAVL_OS_LINUX64)
      if(pthread_mutexattr_settype(&mutAttr,PTHREAD_MUTEX_RECURSIVE_NP) != 0) // Linux.
#else
#ifdef PTHREAD_MUTEX_RECURSIVE
	if(pthread_mutexattr_settype(&mutAttr,PTHREAD_MUTEX_RECURSIVE) != 0) // Solaris and maybe other ?
#endif
#endif
	throw ExceptionOperationFailedC("ERROR: Recursive mutex's not available. ");
    }
    int rc;
    if((rc = pthread_mutex_init(&mutex,&mutAttr)) != 0) {
      Error("Failed to create mutex.",errno,rc); 
    } else {
      isValid = true;
    }
    
    pthread_mutexattr_destroy(&mutAttr);
#endif
#endif
    // ---------------------------------- WIN32 ----------------------------------
#if RAVL_HAVE_WIN32_THREADS
    if((mutex = CreateMutex(0,false,0)) == 0) {
      Error("Failed to create mutex.",errno,0); 
    } else
      isValid = true;
#endif
  }
  
  void MutexC::Error(const char *msg)  {
    cerr << "MutexC::Error() :" << msg << " \n";
    RavlAssert(0);
  }
  
  //: Report an error, with an error number.
  
  void MutexC::Error(const char *msg,int anerrno,int rc) {
#if RAVL_COMPILER_VISUALCPPNET_2005
    char buff[1024];
    strerror_s(buff,1024,anerrno);
    cerr << "MutexC::Error() err=" << anerrno << " (" << buff << ") : " << msg << " \n";
    RavlAlwaysAssert(0);
#else
    cerr << "MutexC::Error() err=" << anerrno << " (" << strerror(anerrno) << ") : " << msg << " \n";
    cerr << "MutexC::Error()  rc=" << rc << " (" << strerror(rc) << ") \n";
#endif
    cerr << "MutexC::Error() @:" << ((void*) this) << "\n";
    RavlAssert(0);
  }
  
  //: Destructor.
  MutexC::~MutexC() { 
    ONDEBUG(cerr << "MutexC::~MutexC(), Destroying mutex. (@:" << ((void*) this) << ")\n");
    int maxRetry = 100;
    // We need to make sure there's no threads waiting for the lock. There shouldn't be
    // if we're freeing it, as the resource its waiting for is probably on its way out too.
    while(--maxRetry > 0) {
      if(TryLock()) { // Try get an exclusive lock.
	Unlock(); // Unlock... and destroy.
#if RAVL_HAVE_POSIX_THREADS
	if(pthread_mutex_destroy(&mutex) == 0)
	  break; // It worked ok..
#endif
#if RAVL_HAVE_WIN32_THREADS
        if(CloseHandle(mutex)) 
          break;
        cerr << "WARNING: MutexC::~MutexC(), destroy failed. " << GetLastError() << "\n";   
#endif
      }
#if RAVL_HAVE_WIN32_THREADS
      RavlN::Sleep(0.01);
#else
      OSYield();
#endif
    }
    isValid = false;
    if(maxRetry <= 0)
      cerr << "WARNING: MutexC::~MutexC(), destroy failed. \n";
  }
  
#if !RAVL_USE_INLINEMUTEXCALLS  
  //: Lock mutex.
  
  bool MutexC::Lock(void) {
    int rc;
    RavlAssert(isValid);
    
#if RAVL_HAVE_POSIX_THREADS
    //ONDEBUG(cerr << "MutexC::Lock() Start @:" << ((void*) this) << " \n");
    if((rc = pthread_mutex_lock(&mutex)) == 0) {
      //ONDEBUG(cerr << "MutexC::Lock() Obtained @:" << ((void*) this) << " \n");
      return true;
    }
    Error("Lock failed",errno,rc);
#endif
#if RAVL_HAVE_WIN32_THREADS
    if((rc = WaitForSingleObject(mutex,INFINITE)) == WAIT_OBJECT_0) {
      return true;
    }
    Error("Lock failed",GetLastError(),rc);
#endif    
    RavlAssert(isValid);
    return false;
  }
    
  //: Try and lock mutex.
  
  bool MutexC::TryLock(void) {
    int rc;
    RavlAssert(isValid);
#if RAVL_HAVE_POSIX_THREADS
    //ONDEBUG(cerr << "MutexC:TryLock() @:" << ((void*) this) << " \n");
    if((rc = pthread_mutex_trylock(&mutex)) == 0) {
      //ONDEBUG(cerr << "MutexC:TryLock() Succeeded. @:" << ((void*) this) << "  \n");
      return true;
    }
    //ONDEBUG(cerr << "MutexC:TryLock() Failed. @:" << ((void*) this) << "  rc=" << rc << "\n");
    if(rc != EBUSY && rc != EDEADLK)
      Error("Trylock failed for unexpected reason.",errno,rc);
#endif
#if RAVL_HAVE_WIN32_THREADS
    if((rc = WaitForSingleObject(mutex,INFINITE)) == WAIT_OBJECT_0)
      return true;
#endif
    return false;
  }
  
  //: Unlock mutex.
  
  bool MutexC::Unlock(void) {
    //RavlAssertMsg(!TryLock(),"MutexC::Unlock() called on an unlocked mutex.");
    int rc = 0;
    RavlAssert(isValid);
#if RAVL_HAVE_POSIX_THREADS
    //ONDEBUG(cerr << "MutexC:Unlock() @:" << ((void*) this) << "\n");
    if((rc = pthread_mutex_unlock(&mutex)) == 0) {
      //ONDEBUG(cerr << "MutexC::Unlock() Released @:" << ((void*) this) << " \n");
      return true;
    }
    Error("Unlock failed.",errno,rc);
#endif
#if RAVL_HAVE_WIN32_THREADS
    if(ReleaseMutex(mutex))
      return true;
    Error("Unlock failed.",GetLastError(),rc);
#endif
    return false;
  }
#endif
  
}
