// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPTHREADSMUTEX_HEADER
#define RAVLPTHREADSMUTEX_HEADER 1
//////////////////////////////////////////////////////////////
//! author="Charles Galambos"
//! docentry="Ravl.OS.Threads"
//! file="Ravl/OS/Threads/Posix/Mutex.hh"
//! lib=RavlThreads
//! rcsid="$Id$"
//! userlevel=Normal
//! date="02/07/99"

#if !defined(_POSIX_SOURCE) && !defined(__sgi__)
#define _POSIX_SOURCE 1
#endif

#if defined(__sol2__)
#include <sys/signal.h>
#endif

#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include "Ravl/Types.hh"
#include "Ravl/Assert.hh"

namespace RavlN
{
  //! userlevel=Normal
  //: Mutual Exclusion lock.
  // SMALL OBJECT
  
  class MutexC {
  public:
    MutexC(void);
    //: Constructor.
    
    ~MutexC(void);
    //: Destructor.
    
    inline bool Lock(void) {
      if(pthread_mutex_lock(&mutex) == 0)
	return true;
      Error("Lock failed",errno);
      return false;
    }
    //: Lock mutex.
    
    inline bool TryLock(void) {
      if(pthread_mutex_trylock(&mutex) == 0)
	return true;
      if(errno != EPERM && errno != EBUSY && errno != EINTR)
	Error("Trylock failed for unexpected reason.",errno);
      return false;
    }
    //: Try and lock mutex.
    
    inline bool Unlock(void) {
      if(pthread_mutex_unlock(&mutex) == 0) 
	return true;
      Error("Unlock failed.",errno);
      return false;
    }
    //: Unlock mutex.
    
  protected:
    pthread_mutex_t mutex;
    
    void Error(const char *msg);  
    //: Report an error.
    
    void Error(const char *msg,int anerrno);  
    //: Report an error, with an error number.
  };
  
  //! userlevel=Normal
  //: Exception safe MutexC locking class.
  // SMALL OBJECT <p>
  // The destructor of this object removed the lock if
  // it is held.   This ensures whenever the lock goes
  // out of scope, either by returning from the function
  // or if an exception is held, that the lock will be
  // released properly. <p>  
  // It is the users responsability
  // to ensure that the MutexC remains valid for the 
  // lifetime of any MutexLockC instance. 
  
  class MutexLockC {
  public:
    MutexLockC(MutexC &m)
    : mutex(m),
      locked(true)
      { mutex.Lock(); }
    //: Create a lock on a mutex.
    
    MutexLockC(const MutexC &m)
      : mutex(const_cast<MutexC &>(m)),
	locked(true)
      { mutex.Lock(); }
    //: Create a lock on a mutex.
    // This may not seem like a good idea,
    // but it allows otherwise constant functions to
    // lock out other accesses to data without undue
    // faffing.

    MutexLockC(const MutexC &m,bool tryLock)
      : mutex(const_cast<MutexC &>(m)),
	locked(false)
      { 
	if(tryLock)
	  locked = mutex.TryLock(); 
	else {
	  mutex.Lock();
	  locked = true;
	}
      }
    //: Try and create a lock on a mutex.
    // This may not seem like a good idea,
    // but it allows otherwise constant functions to
    // lock out other accesses to data without undue
    // faffing.
    
    ~MutexLockC()
      { 
	if(locked)
	  mutex.Unlock(); 
      }
    //: Create a lock on a mutex.
    
    void Unlock() {
      RavlAssert(locked);
      mutex.Unlock(); 
      locked = false;
    }
    //: Unlock the mutex.
    
    void Lock() {
      RavlAssert(!locked);
      mutex.Lock(); 
      locked = true;
    }
    //: re Lock the mutex.
    
    bool IsLocked() const
      { return locked; }
    //: Is it locked ?
    
  protected:
    MutexC &mutex;
    bool locked;
  };
  
}


#endif
