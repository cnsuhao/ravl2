// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////
//! rcsid="$Id: Semaphore.cc 6756 2008-04-24 13:42:11Z craftit $"
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
    : count(initVal)
  {}
  
  //: Copy Constructor.
  // This just creates a semaphore with the same count.
  
  SemaphoreC::SemaphoreC(const SemaphoreC &oth) 
    : count(oth.Count())
  {}
  
  //: Wait for semaphore.
  
  bool SemaphoreC::Wait() {
    cond.Lock();
    while(count <= 0)
      cond.Wait();
    count--;
    cond.Unlock();
    return true;
  }
  
  bool SemaphoreC::Wait(RealT maxDelay) {
    if(maxDelay == 0)
      return TryWait();
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
  
  istream &operator>>(istream &in,SemaphoreC &sema) {
    int i;
    in >> i;
    return in;
  }
  //: Read in from stream.

  BinOStreamC &operator<<(BinOStreamC &strm,const SemaphoreC &vertex) {
    RavlAssertMsg(0,"not implemented");
    return strm;
  }
  //: Binary stream output.
  // Not implemented
  
  BinIStreamC &operator>>(BinIStreamC &strm,SemaphoreC &vertex) {
    RavlAssertMsg(0,"not implemented");
    return strm;
  }
  //: Binary stream input.
  // Not implemented

}
