// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_PTHREADSRWLOCK_HEADER
#define RAVL_PTHREADSRWLOCK_HEADER 1
//////////////////////////////////////////////////////////////
//! author="Charles Galambos"
//! docentry="Ravl.OS.Threads"
//! rcsid="$Id$"
//! file="Ravl/OS/Threads/Posix/RWLock.hh"
//! lib=RavlThreads
//! userlevel=Normal
//! date="02/07/1999"

#include "Ravl/config.h"
        
#include <pthread.h>

#if RAVL_OS_SOLARIS
#include <sys/signal.h>
#endif

#include <errno.h>

#if !RAVL_HAVE_POSIX_THREADS_RWLOCK
#include <assert.h>
#include "Ravl/Threads/Mutex.hh"
#include "Ravl/Threads/Semaphore.hh"
#endif

#include "Ravl/Types.hh"
#include "Ravl/Assert.hh"

namespace RavlN {
  
  enum RWLockModeT { RWLOCK_READONLY, 
		     RWLOCK_WRITE,
		     RWLOCK_TRY_READONLY, 
		     RWLOCK_TRY_WRITE 
  };
  //: Lock type.
  
#if RAVL_HAVE_POSIX_THREADS_RWLOCK
  //! userlevel=Normal
  //: Read/Write lock.
  
  class RWLockC {
  public:
    RWLockC() 
    { pthread_rwlock_init(&id,0); }
    //: Constructor.
    
    ~RWLockC(); 
    //: Destructor.
    
  protected:
    void Error(const char *msg);
    //: Print an error.
    
  public:
    bool RdLock(void) { 
      do {
	if(pthread_rwlock_rdlock(&id) == 0)
	  return true;
      } while(errno == EINTR) ;
      Error("Failed to get RdLock");
      return false;
    }
    //: Get a read lock.
    
    bool TryRdLock(void) 
    { return (pthread_rwlock_tryrdlock(&id) == 0); }
    //: Try and get a read lock.
    
    bool WrLock(void) { 
      do {
	if(pthread_rwlock_wrlock(&id) == 0)
	  return true;
      } while(errno == EINTR) ;	
      Error("Failed to get WrLock");
      return false;
    }
    //: Get a write lock.
    
    bool TryWrLock(void) 
    { return (pthread_rwlock_trywrlock(&id) == 0); }
    //: Try and get a write lock.
    
    bool UnlockWr(void) 
    { return (pthread_rwlock_unlock(&id) == 0); }
    //: Unlock write lock.
    
    bool UnlockRd(void)
    { return (pthread_rwlock_unlock(&id) == 0); }
    //: Unlock read lock.
    
  private:
    RWLockC(const RWLockC &)
    { RavlAssert(0); }
    //: Dissable copy constructor.
    
    pthread_rwlock_t id;
  };

#else

  //: Read Write Lock.
  // There may be a better way, any suggestions ??
  // Gives priority to write requests.
  
  class RWLockC {
  public:
    inline RWLockC();
    // Constructor.
    
    inline bool RdLock(void);  
    // Get a read lock.
    
    inline bool TryRdLock(void);  
    // Try and get a read lock.
    
    inline bool WrLock(void);  
    // Get a write lock.
    
    inline bool TryWrLock(void);
    // Try and get a write lock.
    
    inline bool UnlockRd(void);
    // Unlock a read lock.
    
    inline bool UnlockWr(void);
    // Unlock a write lock.
    
  protected:
    inline bool Unlock(void);
    // Unlock.
    
    void Error(const char *msg);
    //: Print an error.
    
  private:
    RWLockC(const RWLockC &)
    : WriteQueue(1),
      ReadQueue(1)
      { RavlAssert(0); }
    //: Dissable copy constructor.
    
    MutexC AccM; // Access control.
    int RdCount; // Count of readers with locks. -1=Writing
    int WrWait;  // Count of writers waiting.
    int RdWait;  // Count of readers waiting.
    SemaphoreC WriteQueue; // Writers queue.
    SemaphoreC ReadQueue;  // Readers queue.  
  };

  ///////////////////////
  // Constructor.
  
  inline 
  RWLockC::RWLockC() 
    : AccM(), 
      RdCount(0), 
      WrWait(0), 
      RdWait(0), 
      WriteQueue(0),
      ReadQueue(0) 
  {} 
  
  inline 
  bool RWLockC::RdLock()  {
    AccM.Lock();
    while(WrWait > 0 || RdCount < 0) {
      RdWait++; // Should only go aroung this loop once !
      AccM.Unlock();
      ReadQueue.Wait();
      AccM.Lock();
      RdWait--;
    }
    RavlAssert(RdCount >= 0);
    RdCount++;
    AccM.Unlock();
    return true;
  }

  inline 
  bool RWLockC::TryRdLock()  { 
    AccM.Lock();
    if(WrWait > 0 || RdCount < 0) {
      AccM.Unlock();
      return false;
    }
    RdCount++;
    AccM.Unlock();
    return true;
  }

  inline 
  bool RWLockC::WrLock(void)  { 
    AccM.Lock();
    while(RdCount != 0) {
      WrWait++; // Should only go through here once !
      AccM.Unlock();
      WriteQueue.Wait();
      AccM.Lock();
      WrWait--;
    }
    RdCount = -1; // Flag write lock.
    AccM.Unlock();
    return true;
  }

  inline 
  bool RWLockC::TryWrLock(void)  { 
    AccM.Lock();
    if(RdCount > 0) {
      AccM.Unlock();
      return false; 
    }
    RdCount = -1; // Flag write lock.
    AccM.Unlock();
    return true;
  }

  inline 
  bool RWLockC::Unlock(void)  { 
    AccM.Lock();
    if(RdCount < 0) { 
      // Unlock a write lock.
      RdCount = 0;
      if(WrWait > 0)
	WriteQueue.Post(); // Wake up a waiting writer.
      else {
	for(int i = 0;i < RdWait;i++)
	  ReadQueue.Post(); // Wakeup all waiting readers.
      }
      AccM.Unlock();
      return true;
    }
    // Unlock a read lock.
    RdCount--;  
    if(WrWait < 1) {
      for(int i = 0;i < RdWait;i++)
	ReadQueue.Post(); // Wakeup all waiting readers.
    } else {
      if(RdCount <= 0)
	WriteQueue.Post(); // Wake up a waiting writer.
    }
    AccM.Unlock();
    return true;
  }
  
  inline 
  bool RWLockC::UnlockRd(void) { 
    return Unlock(); 
  }

  inline 
  bool RWLockC::UnlockWr(void)  { 
    return Unlock(); 
  }

#endif

  //! userlevel=Normal
  //: Exception safe RWLockC locking class.
  // SMALL OBJECT <p>
  // The destructor of this object removed the lock if
  // it is held.   This ensures whenever the lock goes
  // out of scope, either by returning from the function
  // or if an exception is held, that the lock will be
  // released properly. <p>  
  // It is the users responsability to ensure that the 
  // RWLockC remains valid for the lifetime of any RWLockHoldC 
  // instance. <p>
  
  class RWLockHoldC {
  public:    
    RWLockHoldC(const RWLockC &m,bool readOnly = true,bool tryOnly = false)
      : rwlock(const_cast<RWLockC &>(m)),
	rLocked(false),
	wLocked(false)
    { 
      if(!tryOnly) {
	if(readOnly) {
	  rwlock.RdLock();
	  rLocked = true;
	} else {
	  rwlock.WrLock();
	  wLocked = true;
	}
      } else {
	if(readOnly) {
	  if(rwlock.TryRdLock())
	    rLocked = true;
	} else {
	  if(rwlock.TryWrLock())
	    wLocked = true;
	}
      }
    }
    //: Create a lock on a rwlock.
    // This method is obsolete and may be remove in future versions,
    // use constructor with RWLockModeT paramiter instead. <br>
    // This may not seem like a good idea,
    // but it allows otherwise constant functions to
    // lock out other accesses to data without undue
    // faffing about.
    
    RWLockHoldC(const RWLockC &m,RWLockModeT lockMode)
      : rwlock(const_cast<RWLockC &>(m)),
	rLocked(false),
	wLocked(false)
    { 
      switch(lockMode) {
      case RWLOCK_READONLY:     rLocked = rwlock.RdLock();    break;
      case RWLOCK_WRITE:        wLocked = rwlock.WrLock();    break;
      case RWLOCK_TRY_READONLY: rLocked = rwlock.TryRdLock(); break;
      case RWLOCK_TRY_WRITE:    wLocked = rwlock.TryWrLock(); break;
      }
    };
    //: Create a lock on a rwlock.
    // This may not seem like a good idea,
    // but it allows otherwise constant functions to
    // lock out other accesses to data without undue
    // faffing.
    
    void Unlock() {
      RavlAssert(!(wLocked && rLocked)); // Not both at once!
      if(wLocked)
	rwlock.UnlockWr();
      if(rLocked)
	rwlock.UnlockRd();
      rLocked = false;
      wLocked = false;
    }
    
    //: Unlock the rwlock.
    ~RWLockHoldC()
    { Unlock(); }
    
    //: Create a lock on a rwlock.
    
    void LockRd() {
      RavlAssertMsg(!(wLocked || rLocked),"RWLockHoldC::LockRd(), ERROR: lock already exists."); // Must be no locks.
      rwlock.RdLock();
      rLocked = true;
    }
    //: relock for read
    
    void LockWr() {
      RavlAssertMsg(!(wLocked || rLocked),"RWLockHoldC::LockWr(), ERROR: lock already exists."); // Must be no locks.
      rwlock.WrLock();
      wLocked = true;
    }
    //: relock for write
    
    bool IsReadLocked() const
    { return rLocked || wLocked; }
    //: Test if safe for reading.
    // This will return true if either a write or read lock is inplace.
    
    bool IsWriteLocked() const
    { return  wLocked; }
    //: Test if safe for writing.
    
  protected:
    RWLockC &rwlock;
    bool rLocked;
    bool wLocked;

  private:
    RWLockHoldC(const RWLockHoldC &o)
      : rwlock(o.rwlock)
    { RavlAssert(0); }
    //: Dissable copy constructor.
  };

}
#endif
