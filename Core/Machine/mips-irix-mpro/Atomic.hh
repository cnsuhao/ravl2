// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef __ARCH_SGI_RAVL_ATOMIC__
#define __ARCH_SGI_RAVL_ATOMIC__ 1
//! file="Ravl/Core/Machine/mips-irix-mpro/Atomic.hh"
//! userlevel=Default
//! author="Charles Galambos"
//! date="25/02/99"
//! rcsid="$Id$"
//! docentry="default.Charles Galambos"
//! lib=RavlCore

#ifdef __cplusplus
extern "C" {
#endif

#define USE_MPCODE 1

#if !USE_MPCODE
#include <sys/pmo.h>
#include <fetchop.h>
typedef ravl_atomic_var_t ravl_atomic_t;
#else
typedef int ravl_atomic_t;
#endif

#define ravl_atomic_read(v)		(*v)
#define ravl_atomic_set(v,i)		((*v) = (i))

static inline void ravl_atomic_inc(ravl_atomic_t *v)
{ 
#if USE_MPCODE
  __fetch_and_add(v,1);
#else
  ravl_atomic_fetch_and_increment(v); 
#endif
}

static inline void ravl_atomic_dec(ravl_atomic_t *v)
{ 
#if USE_MPCODE
  __fetch_and_sub(v,1);
#else
  ravl_atomic_fetch_and_decrement(v);  
#endif
}

static inline int ravl_atomic_dec_and_test(ravl_atomic_t *v)
{ 
#if USE_MPCODE
  return __sub_and_fetch(v,1) == 0;
#else
  /* This derements by one, and returns the PREVIOUS value. */
  return  ravl_atomic_fetch_and_decrement(v) == 1; 
#endif
}

#ifdef __cplusplus
};
#endif

#endif /* !(__ARCH_SPARC_RAVL_ATOMIC__) */
