// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Posix/Semaphore.cc"

#include "Ravl/Threads/Semaphore.hh"
#include "Ravl/Math.hh"
#include "Ravl/Stream.hh"

namespace RavlN
{
  
  //: Constructor.
  // Create a semaphore with an inital count of 'initVal'.
  
  SemaphoreC::SemaphoreC(int initVal) 
#if !RAVL_HAVE_WIN32_THREADS
    : count(initVal)
  {}
#else
  {
    sema = CreateSemaphore(0,initVal,65535,0);
    if(sema == 0) 
      cerr << "SemaphoreC::SemaphoreC(), ERROR: Failed to create semaphore!. \n";
  }
#endif
  
  //: Copy Constructor.
  // This just creates a semaphore with the same count.
  
  SemaphoreC::SemaphoreC(const SemaphoreC &oth) 
#if !RAVL_HAVE_WIN32_THREADS
    : count(oth.Count())
  {}
#else
  {
    sema = CreateSemaphore(0,oth.Count(),65535,0);
    if(sema == 0) 
      cerr << "SemaphoreC::SemaphoreC(), ERROR: Failed to create semaphore!. \n";    
  }
#endif
  
  //: Wait for semaphore.
  
  bool SemaphoreC::Wait() {
#if !RAVL_HAVE_WIN32_THREADS
    cond.Lock();
    while(count <= 0)
      cond.Wait();
    count--;
    cond.Unlock();
    return true;
#else
    DWORD rc = WaitForSingleObject(sema,INFINITE);
    return (rc == WAIT_OBJECT_0);
#endif
  }
  
  bool SemaphoreC::Wait(RealT maxDelay) {
#if !RAVL_HAVE_WIN32_THREADS
    cond.Lock();
    while(count <= 0) {
      if(!cond.Wait(maxDelay)) {
	cond.Unlock();
	return false;
      }
    }
    count--;
    cond.Unlock();
    return true;
#else
    DWORD rc = WaitForSingleObject(sema,Round(maxDelay * 1000));
    return (rc == WAIT_OBJECT_0);
#endif
  }
  
  
#if RAVL_HAVE_WIN32_THREADS
  
  //: Try and wait for semaphore
  // Return true if semaphore has been posted, and decrement as it Wait() had 
  // been called. Otherwise do nothing and return false.
  bool SemaphoreC::TryWait() {
    DWORD rc = WaitForSingleObject(sema,0L);
    return (rc == WAIT_OBJECT_0);
  }
  
  //: Post a semaphore.
  // Post a semaphore, increase the semaphore count by 1.
  
  bool SemaphoreC::Post() 
  { return ReleaseSemaphore(sema,1,0) != 0; }
  
  int SemaphoreC::Count(void) const {
    long tmp;
    DWORD rc = ReleaseSemaphore(sema,0,&tmp);
    cerr << "SemaphoreC::Count(), RC=" << rc << " Tmp=" << tmp << "\n";
    return tmp;
  }
  
#endif
  
  ostream &operator<<(ostream &out,const SemaphoreC &sema) {
    out << sema.Count();
    return out;
  }
  //: Write out to stream.
  // Write the semaphore count to the stream.
  
  istream &operator>>(istream &in,SemaphoreC &sema) {
    int i;
    in >> i;
    return in;
  }
  //: Read in from stream.

}
