// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/MTLocks.hh"

#ifdef VISUAL_CPP 
#include <process.h>
int _getpid( void );
#else
#include <unistd.h>
#endif

namespace RavlN {
  
  MTLockFuncT MTReadLock = 0;
  MTLockFuncT MTWriteLock = 0;
  MTLockFuncT MTUnlockWr = 0;
  MTLockFuncT MTUnlockRd = 0;
  MTThreadIDFuncT MTGetThreadID = 0;
  
  //: Get thread id.
  int SysGetThreadID() {
    if(MTGetThreadID == 0)
#ifdef VISUAL_CPP 
      return _getpid();
#else
    return getpid();
#endif
    return MTGetThreadID();
  }
}
