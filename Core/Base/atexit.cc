// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/config.h"
#if RAVL_OS_SOLARIS 
#include <stdlib.h>
#include "Ravl/Atomic.hh"
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Base/atexit.cc"

#define TABLESIZE 1024

// This file provides a fix for implementations of libc with
// a limited number of calls to atexit.

extern "C" {
  typedef void (*funcptrT)(void);
  
  static funcptrT ftable[TABLESIZE];
  static ravl_atomic_t reg = RAVL_ATOMIC_INIT(-1);
  
  int atexit(void (*fptr)(void)) {
    int x = ravl_atomic_inc_return(&reg);
    if(x >= TABLESIZE) {
      ravl_atomic_dec(&reg);
      return -1;
    }
    ftable[x] = fptr;
    return 0;
  }
  
  /* I'm assuming by the time this is called we're back to being single threaded. */
  
  void _exithandle(void) {
    int c;
    /* It is just possible that an exit function could inadvernantly call atexit,
       and register another function, so be carefull.... */
    while((c = ravl_atomic_read(&reg)) >= 0) {
      if(ftable[c] != 0)
	ftable[c]();
      ravl_atomic_dec(&reg);
    }
  }
  
};

#else
namespace RavlN {
  int foobar_or_some_such_silly_name;
}

#endif

 
