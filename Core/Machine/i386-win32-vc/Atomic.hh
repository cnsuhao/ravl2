// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ATOMIC_I386_WIN32_VC_HEADER
#define RAVL_ATOMIC_I386_WIN32_VC_HEADER 1
//! file="Ravl/Core/Machine/i386-win32-vc/Atomic.hh"
//! userlevel=Default
//! author="Charles Galambos"
//! date="8/04/2004"
//! rcsid="$Id$"
//! docentry="Ravl.API.Core.Misc"
//! lib=RavlCore

#ifdef __cplusplus
extern "C" {
#endif

typedef struct { volatile int counter; } ravl_atomic_t;

#define RAVL_ATOMIC_INIT(i)	{ (i) }

#define ravl_atomic_read(v)		((v)->counter)
#define ravl_atomic_set(v,i)		(((v)->counter) = (i))

static inline void ravl_atomic_inc(volatile ravl_atomic_t *v) {
  //volatile int *counter = &(v->counter);
  //
  __asm {
    mov eax,DWORD PTR [v] ravl_atomic_t.counter
    lock inc DWORD PTR [eax]
  }
}

static inline void ravl_atomic_dec(volatile ravl_atomic_t *v) {
  volatile int &counter = v->counter;
  __asm {
    mov eax,DWORD PTR [v] ravl_atomic_t.counter
    lock dec DWORD PTR [eax]
  }
}

static inline int ravl_atomic_dec_and_test(volatile ravl_atomic_t *v) {
  unsigned char c;
  volatile int &counter = v->counter;
  __asm {
    mov eax,DWORD PTR [v] ravl_atomic_t.counter
    lock dec DWORD PTR [eax]
    sete c
  }
  return c != 0;
}

#ifdef __cplusplus
};
#endif

#endif
