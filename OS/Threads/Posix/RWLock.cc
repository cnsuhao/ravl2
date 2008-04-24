// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlThreads
//! file="Ravl/OS/Threads/Posix/RWLock.cc"

#include "Ravl/Threads/Thread.hh"
#include "Ravl/Threads/RWLock.hh"
#include "Ravl/Stream.hh"

namespace RavlN
{

#if RAVL_HAVE_POSIX_THREADS_RWLOCK
  //: Copy constructor.
  // This just creates another lock.
  
  RWLockC::RWLockC(const RWLockC &)
    : isValid(false)
  {
    int ret = pthread_rwlock_init(&id,0); 
    if(ret != 0)
      Error("RWLockC::RWLockC, Init failed ",ret);
    else isValid = true;    
  }
  
  //: Constructor.
  
  RWLockC::RWLockC() 
    : isValid(false)
  {
    int ret = pthread_rwlock_init(&id,0); 
    if(ret != 0)
      Error("RWLockC::RWLockC, Init failed ",ret);
    else isValid = true;
  }
  
  // Destructor.
  
  RWLockC::~RWLockC() { 
    int x = 100;
    // This could fail if lock is held.
    while(pthread_rwlock_destroy(&id) && x-- > 0)
      OSYield();
    isValid = false;
    if(x == 0) 
      cerr << "WARNING: Failed to destory RWLock. \n";
  }
#else
  
  RWLockC::RWLockC() 
    : AccM(), 
      RdCount(0), 
      WrWait(0), 
      RdWait(0), 
      WriteQueue(0),
      ReadQueue(0) 
  {} 
  
  RWLockC::RWLockC(const RWLockC &) 
    : AccM(), 
      RdCount(0), 
      WrWait(0), 
      RdWait(0), 
      WriteQueue(0),
      ReadQueue(0) 
  {} 
  
#endif  
  
  //: Print an error.
  
  void RWLockC::Error(const char *msg,int ret) {
    cerr << msg << " (errno=" << errno << ") Return=" << ret << " \n";
    RavlAssert(0); // Abort so we can get a stack trace.
  }

  ostream &operator<<(ostream &strm,const RWLockC &vertex) {
    RavlAssertMsg(0,"not implemented");
    return strm;
  }
  //: Text stream output.
  // Not implemented
  
  istream &operator>>(istream &strm,RWLockC &vertex) {
    RavlAssertMsg(0,"not implemented");
    return strm;
  }
  //: Text stream input.
  // Not implemented
  
  BinOStreamC &operator<<(BinOStreamC &strm,const RWLockC &vertex) {
    RavlAssertMsg(0,"not implemented");
    return strm;
  }
  //: Binary stream output.
  // Not implemented
  
  BinIStreamC &operator>>(BinIStreamC &strm,RWLockC &vertex) {
    RavlAssertMsg(0,"not implemented");
    return strm;
  }
  //: Binary stream input.
  // Not implemented
  
}
