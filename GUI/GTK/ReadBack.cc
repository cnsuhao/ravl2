// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI

#include "Ravl/GUI/ReadBack.hh"
#include "Ravl/GUI/Manager.hh"

namespace RavlGUIN {
  using namespace RavlN;
  
  //: Create a lock. (May take some time.)
  
  ReadBackLockC::ReadBackLockC(bool waitForLock) 
    : lock(true),
      held(false),
      released(false)
  {
    if(Manager.IsGUIThread()) {
      held = true;
      released = true;
      return ;
    }
    Manager.Queue(Trigger(lock,&ReadBackC::Issue));
    if(waitForLock)
      Wait();
  }
  
  //: Release a lock, if held.
  
  ReadBackLockC::~ReadBackLockC() {
    Unlock();
  }
  
  //: Wait for lock to be issued.
  
  bool ReadBackLockC::Wait() {
    if(held || released)
      return held;
    lock.WaitForLock();
    held = true;
    return true;
  }
  
  //: Undo lock.
  
  bool ReadBackLockC::Unlock() {
    if(!released) {
      lock.Release();
      released = true;
      return true;
    }
    return false;
  }

}
