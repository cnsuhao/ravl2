// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! file="Ravl/Core/Machine/sparc-solaris-gnu-v9/Atomic.hh"
//! userlevel=Default
//! author="Lee Gregory"
//! date="06/12/02"
//! docentry="Ravl.Core.Misc"
//! lib=RavlCore
#ifndef RAVL_ATOMIC_SPARC_HEADER_V9
#define RAVL_ATOMIC_SPARC_HEADER_V9 1

//typedef struct  {
//  volatile int v;
//  
//} ravl_atomic_t;

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


#endif 

