// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! file="amma/BasType/sol2/Atomic.hh"
//! userlevel=Default
//! author="Charles Galambos"
//! date="25/02/99"
//! rcsid="$Id$"
//! docentry="default.Charles Galambos"
/* atomic.h: These still suck, but the I-cache hit rate is higher.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 */

#ifndef __ARCH_SPARC_RAVL_ATOMIC__
#define __ARCH_SPARC_RAVL_ATOMIC__

#ifdef __cplusplus
extern "C" {
#endif

#define USE_RAVL_ATOMIC_ASM 1

#if USE_RAVL_ATOMIC_ASM
typedef struct { volatile int counter; } ravl_atomic_t;
extern void yield();

#define RAVL_ATOMIC_INIT(i)	{ (i << 8) }

/* We do the bulk of the actual work out of line in two common
 * routines in assembler, see arch/sparc/lib/atomic.S for the
 * "fun" details.
 *
 * For SMP the trick is you embed the spin lock byte within
 * the word, use the low byte so signedness is easily retained
 * via a quick arithmetic shift.  It looks like this:
 *
 *	----------------------------------------
 *	| signed 24-bit counter value |  lock  |  ravl_atomic_t
 *	----------------------------------------
 *	 31                          8 7      0
 */

static __inline__ int ravl_atomic_read(ravl_atomic_t *v)
{
	int val;

	__asm__ __volatile__("sra	%1, 0x8, %0"
			     : "=r" (val)
			     : "r" (v->counter));
	return val;
}
#define ravl_atomic_set(v, i)	(((v)->counter) = ((i) << 8))

/* Make sure gcc doesn't try to be clever and move things around
 * on us. We need to use _exactly_ the address the user gave us,
 * not some alias that contains the same information.
 */
#define __ravl_atomic_fool_gcc(x) ((struct { int a[100]; } *)x)

static __inline__ void ravl_atomic_add(int i, ravl_atomic_t *v)
{
	register ravl_atomic_t *ptr asm("g1");
	register int increment asm("g2");
	ptr = (ravl_atomic_t *) __ravl_atomic_fool_gcc(v);
	increment = i;
	
	__asm__ __volatile__("
        b       1f
        mov	1,%%g3
2:      call	_yield
        nop
1:	ldstub	[%%g1 + 3], %%g3	! Spin on the byte lock for SMP.
	orcc	%%g3, 0x0, %%g0		! Did we get it?
	bne	2b			! Nope...	
	 ld	[%%g1], %%g3		! Load locked ravl_atomic_t
	sra	%%g3, 8, %%g3		! Get signed 24-bit integer
	add	%%g3, %%g2, %%g2	! Add in argument
	sll	%%g2, 8, %%g3		! Transpose back to ravl_atomic_t
	st	%%g3, [%%g1]		! Clever: This releases the lock as well.
"	: "=&r" (increment)
	: "0" (increment), "r" (ptr)
	:  "g3", "memory", "cc");
}

static __inline__ void ravl_atomic_sub(int i, ravl_atomic_t *v)
{
	register ravl_atomic_t *ptr asm("g1");
	register int increment asm("g2");

	ptr = (ravl_atomic_t *) __ravl_atomic_fool_gcc(v);
	increment = i;

#if 0
#endif
	__asm__ __volatile__("
	b	2f
	mov	1,%%g3
1:      call	yield,0
	nop
2:	ldstub	[%%g1 + 3], %%g3		! Spin on the byte lock for SMP.
	orcc	%%g3, 0x0, %%g0		! Did we get it?
	bne	1b			! Nope...
	
        ld	[%%g1], %%g3	        ! Load locked ravl_atomic_t
	sra	%%g3, 8, %%g3		! Get signed 24-bit integer
	sub	%%g3, %%g2, %%g2		! Subtract argument
	sll	%%g2, 8, %%g3		! Transpose back to ravl_atomic_t
	st	%%g3, [%%g1]		! Clever: This releases the lock as well
"	: "=&r" (increment)
	: "0" (increment), "r" (ptr)
	:  "g4", "g3", "memory", "cc");
	//"g3",
}

static __inline__ int ravl_atomic_add_return(int i, ravl_atomic_t *v)
{
	register ravl_atomic_t *ptr asm("g1");
	register int increment asm("g2");

	ptr = (ravl_atomic_t *) __ravl_atomic_fool_gcc(v);
	increment = i;
	__asm__ __volatile__("
	b	2f
	mov	1,%%g3
1:      call	yield,0
	nop
2:	ldstub	[%%g1 + 3], %%g3	! Spin on the byte lock for SMP.
	orcc	%%g3, 0x0, %%g0		! Did we get it?
	bne	1b			! Nope...	
	 ld	[%%g1], %%g3		! Load locked ravl_atomic_t
	sra	%%g3, 8, %%g3		! Get signed 24-bit integer
	add	%%g3, %%g2, %%g2	! Add in argument
	sll	%%g2, 8, %%g3		! Transpose back to ravl_atomic_t
	st	%%g3, [%%g1]		! Clever: This releases the lock as well.
"	: "=&r" (increment)
	: "0" (increment), "r" (ptr)
	: "g3", "memory", "cc");

	return increment;
}

static __inline__ int ravl_atomic_sub_return(int i, ravl_atomic_t *v)
{
	register ravl_atomic_t *ptr asm("g1");
	register int increment asm("g2");

	ptr = (ravl_atomic_t *) __ravl_atomic_fool_gcc(v);
	increment = i;
	
	__asm__ __volatile__("
	b	2f
	mov	1,%%g3
1:      call	yield,0
	nop
        mov	1,%%g3
2:	ldstub	[%%g1 + 3], %%g3
	orcc	%%g3, 0x0, %%g0	
	bne	1b		
	 ld	[%%g1], %%g3
	sra	%%g3, 8, %%g3
	sub	%%g3, %%g2, %%g2
	sll	%%g2, 8, %%g3	
	st	%%g3, [%%g1]
"	
	: "=&r" (increment)
	: "0" (increment), "r" (ptr)
	: "g3", "memory", "cc");

	return increment;
}

#define ravl_atomic_dec_return(v) ravl_atomic_sub_return(1,(v))
#define ravl_atomic_inc_return(v) ravl_atomic_add_return(1,(v))

#define ravl_atomic_sub_and_test(i, v) (ravl_atomic_sub_return((i), (v)) == 0)

#if 0
#define ravl_atomic_dec_and_test(v) (ravl_atomic_sub_return(1, (v)) == 0)
#else
static __inline__ int ravl_atomic_dec_and_test(ravl_atomic_t *v)
{
  register ravl_atomic_t *ptr asm("g5");
  register int increment asm("g3");
  ptr = (ravl_atomic_t *) __ravl_atomic_fool_gcc(v);
  
	__asm__ __volatile__("
        b       1f 
        mov     255, %%g3
2:      call    yield,0
        nop
1:      mov     %%g5,%%g1
        ldstub	[%%g1 + 3], %%g3	! Spin on the byte lock for SMP.
	orcc	%%g3, 0x0, %%g0		! Did we get it?
	bne	2b			! Nope...
	 ld	[%%g1], %%g3		! Load locked ravl_atomic_t
	sub	%%g3, 511, %%g3
	st	%%g3, [%%g1]		! Clever: This releases the lock as well.
	sll	%%g3, 8, %%g3	
"	: "=&r" (increment)
	:  "r" (ptr)
	:  "g3","g4", "memory", "cc");
  return (increment == 0);
}
#endif

static __inline__ void ravl_atomic_inc(ravl_atomic_t *v)
{
	register ravl_atomic_t *ptr asm("g5");
	ptr = (ravl_atomic_t *) __ravl_atomic_fool_gcc(v);
	__asm__ __volatile__("
        b       1f 
        mov     1, %%g2
2:      call    yield,0
        nop
1:      mov     %%g5,%%g1
        ldstub	[%%g1 + 3], %%g2	! Spin on the byte lock for SMP.
	orcc	%%g2, 0x0, %%g0		! Did we get it?
	bne	2b			! Nope...
	 ld	[%%g1], %%g2		! Load locked ravl_atomic_t
        add	%%g2, 1, %%g3           ! Add in argument
	st	%%g3, [%%g1]		! Clever: This releases the lock as well.
"	: 
	: "r" (ptr)
	:  "g1","g2","g3", "memory", "cc");
	// "g3",
}

static __inline__ void ravl_atomic_dec(ravl_atomic_t *v)
{
	register ravl_atomic_t *ptr asm("g5");
	ptr = (ravl_atomic_t *) __ravl_atomic_fool_gcc(v);
	__asm__ __volatile__("
        b       1f 
        mov     255, %%g2
2:      call    yield,0
        nop
1:      mov     %%g5,%%g1
        ldstub	[%%g1 + 3], %%g2	! Spin on the byte lock for SMP.
	orcc	%%g2, 0x0, %%g0		! Did we get it?
	bne	2b			! Nope...
	 ld	[%%g1], %%g2		! Load locked ravl_atomic_t
	sub	%%g2, 511, %%g3
	st	%%g3, [%%g1]		! Clever: This releases the lock as well.
"	: 
	:  "r" (ptr)
	:  "g2","g3", "memory", "cc");
	// "g3",

}

#else
// Dummy atomic stuff.
typedef int ravl_atomic_t;

#define ravl_atomic_read(v)		(*v)
#define ravl_atomic_set(v,i)		((*v) = (i))

static inline void ravl_atomic_inc(ravl_atomic_t *v)
{ (*v)++; }

static inline void ravl_atomic_dec(ravl_atomic_t *v)
{ (*v)--; }

static inline int ravl_atomic_dec_and_test(ravl_atomic_t *v)
{ return (--(*v)) == 0; }

#endif

#ifdef __cplusplus
};
#endif

#endif /* !(__ARCH_SPARC_RAVL_ATOMIC__) */

