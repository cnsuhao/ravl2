// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SEMAPHORE_HEADER
#define RAVL_SEMAPHORE_HEADER 1
//////////////////////////////////////////////////////////////
//! userlevel=Normal
//! author="Charles Galambos"
//! date="25/5/1998"
//! docentry="Ravl.OS.Threads"
//! rcsid="$Id$"
//! file="Ravl/OS/Threads/Posix/Semaphore.hh"
//! lib=RavlThreads

#include "Ravl/Threads/ConditionalMutex.hh"

namespace RavlN
{
  //! userlevel=Normal
  //: Semaphore.
  // This is a method for communicating between threads. It includes an
  // atomic counter, which can be incremented by Post(), and decremented
  // by Wait(). Wait() will only when it can decrement the counter from
  // a positive number.   One use of this class is to send a signal to
  // another thread that some processing is ready to be done.
  
  class SemaphoreC {
  public:
    SemaphoreC(int initVal) 
      : count(initVal)
    {}
    //: Constructor.
    // Create a semaphore with an inital count of 'initVal'.
    
    SemaphoreC(const SemaphoreC &oth) 
      : count(oth.Count())
    {}
    //: Copy Constructor.
    // This just creates a semaphore with the same count.
    
    bool Wait();
    //: Wait for semaphore.
    // Test is semaphore has a count greated than 0,
    // if it does decrement it and return.
    // If the count is 0, then wait until it a call
    // to Post() increments it, then decrement it
    // and return. <br>
    // This function always returns true.
    
    bool Wait(RealT maxDelay);
    //: Wait for semaphore.
    // As Wait(), but only wait for semaphore for up to
    // 'maxDelay' seconds. If the time expires return
    // false. If the semaphore is recieved then return true.
    
    bool TryWait() {
      if(count == 0)
	return false; // Quick and dirty test.
      cond.Lock();
      if(count > 0) {
	count--;
	cond.Unlock();
	return true;
      }
      cond.Unlock();
      return false;
    }
    //: Try and wait for semaphore
    // Return true if semaphore has been posted, and decrement as it Wait() had 
    // been called. Otherwise do nothing and return false.
    
    bool Post() {
      cond.Lock();
      count++;
      cond.Unlock();
      cond.Signal();
      return false;
    }
    //: Post a semaphore.
    // Post a semaphore, increase the semaphore count by 1.
    
    int Count(void) const { 
#if 0
      int ret; 
      cond.Lock();
      ret = count;
      cond.Unlock();
      return ret; 
#else
      return count; // Is there any point in locking ???
#endif
    }
    //: Read semaphore count.
    
  private:
    
    ConditionalMutexC cond;
    int count;
  };
  
  ostream &operator<<(ostream &out,const SemaphoreC &sema);
  //: Write out to stream.
  // Write the semaphore count to the stream.
  
  istream &operator>>(istream &in,SemaphoreC &sema);
  //: Read in from stream.
  // Does nothing.
  
}

#endif
