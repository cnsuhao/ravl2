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
#include <iostream.h>

namespace RavlN
{
  bool SemaphoreC::Wait() {
    cond.Lock();
    while(count <= 0)
      cond.Wait();
    count--;
    cond.Unlock();
    return true;
  }
  //: Wait for semaphore.
  
  bool SemaphoreC::Wait(RealT maxDelay) {
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
  }

  ostream &operator<<(ostream &out,const SemaphoreC &sema) {
    out << sema.Count();
    return out;
  }
  //: Write out to stream.
  // Write the semaphore count to the stream.
  
  istream &operator<<(istream &in,SemaphoreC &sema) {
    return in;
  }
  //: Read in from stream.
  // Does nothing.

}
