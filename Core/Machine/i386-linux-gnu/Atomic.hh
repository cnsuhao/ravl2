// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef __ARCH_I386_RAVL_ATOMIC_
#define __ARCH_I386_RAVL_ATOMIC_
//! file="Ravl/Core/Machine/i386-linux-gnu/Atomic.hh"
//! userlevel=Default
//! author="Charles Galambos"
//! date="25/02/99"
//! rcsid="$Id$"
//! docentry="default.Charles Galambos"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Atomic operations that C can't guarantee us.  Useful for
 * resource counting etc..
 */

#define LOCK "lock ; "

/*
 * Make sure gcc doesn't try to be clever and move things around
 * on us. We need to use _exactly_ the address the user gave us,
 * not some alias that contains the same information.
 */
#define __ravl_atomic_fool_gcc(x) (*(volatile struct { int a[100]; } *)x)

typedef struct { volatile int counter; } ravl_atomic_t;

#define RAVL_ATOMIC_INIT(i)	{ (i) }

#define ravl_atomic_read(v)		((v)->counter)
#define ravl_atomic_set(v,i)		(((v)->counter) = (i))

static __inline__ void ravl_atomic_add(int i, volatile ravl_atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "addl %1,%0"
		:"=m" (__ravl_atomic_fool_gcc(v))
		:"ir" (i), "m" (__ravl_atomic_fool_gcc(v)));
}

static __inline__ void ravl_atomic_sub(int i, volatile ravl_atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "subl %1,%0"
		:"=m" (__ravl_atomic_fool_gcc(v))
		:"ir" (i), "m" (__ravl_atomic_fool_gcc(v)));
}

static __inline__ void ravl_atomic_inc(volatile ravl_atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "incl %0"
		:"=m" (__ravl_atomic_fool_gcc(v))
		:"m" (__ravl_atomic_fool_gcc(v)));
}

static __inline__ void ravl_atomic_dec(volatile ravl_atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "decl %0"
		:"=m" (__ravl_atomic_fool_gcc(v))
		:"m" (__ravl_atomic_fool_gcc(v)));
}

static __inline__ int ravl_atomic_dec_and_test(volatile ravl_atomic_t *v)
{
	unsigned char c;

	__asm__ __volatile__(
		LOCK "decl %0; sete %1"
		:"=m" (__ravl_atomic_fool_gcc(v)), "=qm" (c)
		:"m" (__ravl_atomic_fool_gcc(v)));
	return c != 0;
}

/* These are x86-specific, used by some header files */
#define ravl_atomic_clear_mask(mask, addr) \
__asm__ __volatile__(LOCK "andl %0,%1" \
: : "r" (~(mask)),"m" (__ravl_atomic_fool_gcc(addr)) : "memory")

#define ravl_atomic_set_mask(mask, addr) \
__asm__ __volatile__(LOCK "orl %0,%1" \
: : "r" (mask),"m" (__ravl_atomic_fool_gcc(addr)) : "memory")

#undef LOCK

#ifdef __cplusplus
};
#endif

#endif
