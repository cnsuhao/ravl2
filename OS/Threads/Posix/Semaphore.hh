// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLTHREADSEMAPHORE_HEADER
#define RAVLTHREADSEMAPHORE_HEADER 1
//////////////////////////////////////////////////////////////
//! userlevel=Normal
//! author="Charles Galambos"
//! date="25/5/1998"
//! docentry="Ravl.OS.Threads"
//! rcsid="$Id$"
//! file="amma/StdType/System/PThreads/Posix/Semaphore.hh"
//! lib=RavlThreads

#include "Ravl/Threads/ConditionalMutex.hh"

namespace RavlN
{
  //: Semaphore.
  
  class SemaphoreC {
  public:
    SemaphoreC(int initVal = 1) 
      : count(initVal)
      {}
    //: Constructor.

    SemaphoreC(const SemaphoreC &oth) 
      : count(oth.count)
      {}
    //: Copy Constructor.
    
    bool Wait();
    //: Wait for semaphore.
    // Returns true if semaphore retrieved ok.
    
    bool Wait(RealT maxDelay);
    //: Wait for semaphore.
    // Returns true if semaphore retrieved ok.
    // False is returned on a time out.
    
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
    
    bool Post() {
      cond.Lock();
      count++;
      cond.Unlock();
      cond.Signal();
      return false;
    }
    //: Post a semaphore.
    
    int Count(void) const 
      { 
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
  
  istream &operator<<(istream &in,SemaphoreC &sema);
  //: Read in from stream.
  // Does nothing.
  
}

#endif
