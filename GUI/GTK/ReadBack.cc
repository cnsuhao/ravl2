// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/ReadBack.cc"

#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/ReadBack.hh"

#if 1
#define RAVL_USE_GTKDIRECT RAVL_OS_WIN32
#else
#define RAVL_USE_GTKDIRECT 1
#endif

#if RAVL_USE_GTKDIRECT
#include <gtk/gtk.h>
#endif

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
#if RAVL_USE_GTKDIRECT 
    gdk_threads_enter();
#else
    Manager.Queue(Trigger(lock,&ReadBackC::Issue));
    if(waitForLock)
      Wait();
#endif
  }
  
  //: Release a lock, if held.
  
  ReadBackLockC::~ReadBackLockC() {
    Unlock();
  }
  
  //: Wait for lock to be issued.
  
  bool ReadBackLockC::Wait() {
    if(held || released)
      return held;
#if RAVL_USE_GTKDIRECT
    gdk_threads_enter();
#else 
    lock.WaitForLock();
#endif
    held = true;
    return true;
  }
  
  //: Undo lock.
  
  bool ReadBackLockC::Unlock() {
    if(!released) {
#if RAVL_USE_GTKDIRECT 
      gdk_threads_leave();
#else
      lock.Release();
#endif
      released = true;
      return true;
    }
    return false;
  }

}
