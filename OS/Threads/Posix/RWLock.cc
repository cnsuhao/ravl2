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
  RWLockC::~RWLockC() { 
    int x = 100;
    // This could fail if lock is held.
    while(pthread_rwlock_destroy(&id) && x-- > 0)
      OSYield();
    if(x == 0) 
      cerr << "WARNING: Failed to destory RWLock. \n";
  }
#endif  
  
  //: Print an error.
  
  void RWLockC::Error(const char *msg) {
    cerr << msg << " (errno=" << errno << ")\n";
  }
  
}
