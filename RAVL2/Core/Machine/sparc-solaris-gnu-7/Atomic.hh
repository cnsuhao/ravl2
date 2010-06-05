// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! file="Ravl/Core/Machine/sparc-solaris-gnu-7/Atomic.hh"
//! userlevel=Default
//! author="Charles Galambos"
//! date="25/02/1999"
//! rcsid="$Id: Atomic.hh 5240 2005-12-06 17:16:50Z plugger $"
//! docentry="Ravl.API.Core.Misc"
//! lib=RavlCore
#ifndef RAVL_ATOMIC_SPARC_HEADER
#define RAVL_ATOMIC_SPARC_HEADER 1

#include "Ravl/config.h"


#if RAVL_CPU_SPARC_V9

// -------------------------------------------------------------------------------- //
// -------------------------- V9 Instruction Set ---------------------------------- //
// -------------------------------------------------------------------------------- //

typedef int ravl_atomic_t ;

#define RAVL_ATOMIC_INIT(i)	{ (i) }

#define ravl_atomic_read(a)		(*a)
#define ravl_atomic_set(a,i)		((*a) = (i))


static inline void ravl_atomic_inc(ravl_atomic_t *v)
{
  int tmp1, tmp2 ;
  
  __asm__ __volatile__("1:	lduw	[%2], %0\n\t"
		       //"        lduw    [%2], %1\n\t"
		       "        mov     %0, %1 \n\t"
		       "        inc     %1\n\t"
		       "	cas     [%2], %0, %1\n\t"
		       "        sub     %0, %1, %0\n\t"
		       "	brnz,pn	%0, 1b\n\t"
		       "	 nop"
		       : "=&r" (tmp1), "=&r" (tmp2)
		       : "r" (v)
		       : "memory");
  
}

static inline int ravl_atomic_inc_return(ravl_atomic_t *v)
{
   int tmp1, tmp2 ;
  
  __asm__ __volatile__("1:	lduw	[%2], %0\n\t"
		       //"        lduw    [%2], %1\n\t"
		       "        mov     %0, %1 \n\t"
		       "        inc     %1\n\t"
		       "	cas     [%2], %0, %1\n\t"
		       "        sub     %0, %1, %0\n\t"
		       "	brnz,pn	%0, 1b\n\t"
		       "	 nop"
		       : "=&r" (tmp1), "=&r" (tmp2)
		       : "r" (v)
		       : "memory");
  
  return *v ;
}



static inline void ravl_atomic_dec(ravl_atomic_t *v)
{
  int tmp1, tmp2 ;
  
  __asm__ __volatile__("1:	lduw	[%2], %0\n\t"
		       //"        lduw    [%2], %1\n\t"
		       "        mov     %0, %1\n\t"
		       "        dec     %1\n\t"
		       "	cas     [%2], %0, %1\n\t"
		       "        sub     %0, %1, %0\n\t"
		       "	brnz,pn	%0, 1b\n\t"
		       "	 nop"
		       : "=&r" (tmp1), "=&r" (tmp2)
		       : "r" (v)
		       : "memory");
  


}

static inline int ravl_atomic_dec_and_test(ravl_atomic_t *v) { 
   int tmp1, tmp2 ;
  
  __asm__ __volatile__("1:	lduw	[%2], %0\n\t"
		       //"        lduw    [%2], %1\n\t"
		       "        mov     %0, %1\n\t"
		       "        dec     %1\n\t"
		       "	cas     [%2], %0, %1\n\t"
		       "        sub     %0, %1, %0\n\t"
		       "	brnz,pn	%0, 1b\n\t"
		       "	 nop"
		       : "=&r" (tmp1), "=&r" (tmp2)
		       : "r" (v)
		       : "memory");
  

  return ( (*v) == 0);
}


#else
// -------------------------------------------------------------------------------- //
// ---------------------- Non V9 Instruction Set ---------------------------------- //
// -------------------------------------------------------------------------------- //

typedef struct  {
  volatile int v;
  volatile unsigned char lock; 
  
} ravl_atomic_t;

#define RAVL_ATOMIC_INIT(i)	{ (i),0 }

#define ravl_atomic_read(a)		((a)->v)
#define ravl_atomic_set(a,i)		(((a)->v) = (i))

static inline void ravl_atomic_inc(ravl_atomic_t *v)
{
  int tmp;
  
  __asm__ __volatile__("1:	ldstub	[%1], %0\n\t"
		       "	cmp	%0, 0\n\t"
		       "	bne	1b\n\t"
		       "	 nop"
		       : "=&r" (tmp)
		       : "r" (&(v->lock))
		       : "memory");
  (v->v)++;
  __asm__ __volatile__("stb	%%g0, [%0]"
		       : /* no outputs */
		       : "r" (&(v->lock))
		       : "memory");
}

static inline int ravl_atomic_inc_return(ravl_atomic_t *v)
{
  int tmp,ret;
  
  __asm__ __volatile__("1:	ldstub	[%1], %0\n\t"
		       "	cmp	%0, 0\n\t"
		       "	bne	1b\n\t"
		       "	 nop"
		       : "=&r" (tmp)
		       : "r" (&(v->lock))
		       : "memory");
  ret = ++(v->v);
  __asm__ __volatile__("stb	%%g0, [%0]"
		       : /* no outputs */
		       : "r" (&(v->lock))
		       : "memory");
  return ret;
}

static inline void ravl_atomic_dec(ravl_atomic_t *v)
{
  int tmp;

  __asm__ __volatile__("1:	ldstub	[%1], %0\n\t"
		       "	cmp	%0, 0\n\t"
		       "	bne	1b\n\t"
		       "	 nop"
		       : "=&r" (tmp)
		       : "r" (&(v->lock))
		       : "memory");
  (v->v)--;
  __asm__ __volatile__("stb	%%g0, [%0]"
		       : /* no outputs */
		       : "r" (&(v->lock))
		       : "memory");
}

static inline int ravl_atomic_dec_and_test(ravl_atomic_t *v) { 
  int tmp;
  int ret;
  __asm__ __volatile__("1:	ldstub	[%1], %0\n\t"
		       "	cmp	%0, 0\n\t"
		       "	bne	1b\n\t"
		       "	 nop"
		       : "=&r" (tmp)
		       : "r" (&(v->lock))
		       : "memory");
  ret = --(v->v);
  
  __asm__ __volatile__("stb	%%g0, [%0]"
		       : /* no outputs */
		       : "r" (&(v->lock))
		       : "memory");
  return (ret == 0);
}

#endif


#endif 

