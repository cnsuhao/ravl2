// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ALPHA_ATOMIC_HEADER
#define RAVL_ALPHA_ATOMIC_HEADER 1
//////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Machine/Generic/Atomic.hh"
//! userlevel=Default
//! author="Charles Galambos"
//! date="25/02/1999"
//! rcsid="$Id$"
//! docentry="Ravl.Core.Misc"
//! lib=RavlCore

typedef int ravl_atomic_t;

#define ravl_atomic_read(v)		(*v)
#define ravl_atomic_set(v,i)		((*v) = (i))

static inline void ravl_atomic_inc(ravl_atomic_t *v)
{
  int val = 1;
  register int result;
  __asm__ __volatile__ (
	"/* Inline exchange & add */\n"
	"1:\t"
	"ldl_l	%0,%2\n\t"
	"addl	%0,%3,%0\n\t"
	"stl_c	%0,%1\n\t"
	"beq	%0,2f\n\t"
	".subsection 1\n"
	"2:\t"
	"br	1b\n"
	".previous\n\t"
	"mb\n\t"
	"/* End exchange & add */"
	: "=&r"(result), "=m"(*mem)
	: "m" (*mem), "r"(val));
}

static inline void ravl_atomic_dec(ravl_atomic_t *v)
{
  int val = -1;
  register int result;
  __asm__ __volatile__ (
	"/* Inline exchange & add */\n"
	"1:\t"
	"ldl_l	%0,%2\n\t"
	"addl	%0,%3,%0\n\t"
	"stl_c	%0,%1\n\t"
	"beq	%0,2f\n\t"
	".subsection 1\n"
	"2:\t"
	"br	1b\n"
	".previous\n\t"
	"mb\n\t"
	"/* End exchange & add */"
	: "=&r"(result), "=m"(*mem)
	: "m" (*mem), "r"(val));
}

static inline int ravl_atomic_inc_return(ravl_atomic_t *v) {
    int val = 1;
  register int result;
  __asm__ __volatile__ (
	"/* Inline exchange & add */\n"
	"1:\t"
	"ldl_l	%0,%2\n\t"
	"addl	%0,%3,%0\n\t"
	"stl_c	%0,%1\n\t"
	"beq	%0,2f\n\t"
	".subsection 1\n"
	"2:\t"
	"br	1b\n"
	".previous\n\t"
	"mb\n\t"
	"/* End exchange & add */"
	: "=&r"(result), "=m"(*mem)
	: "m" (*mem), "r"(val));
  return result;
}

static inline int ravl_atomic_dec_and_test(ravl_atomic_t *v) {  
  int val = -1;
  register int result;
  __asm__ __volatile__ (
	"/* Inline exchange & add */\n"
	"1:\t"
	"ldl_l	%0,%2\n\t"
	"addl	%0,%3,%0\n\t"
	"stl_c	%0,%1\n\t"
	"beq	%0,2f\n\t"
	".subsection 1\n"
	"2:\t"
	"br	1b\n"
	".previous\n\t"
	"mb\n\t"
	"/* End exchange & add */"
	: "=&r"(result), "=m"(*mem)
	: "m" (*mem), "r"(val));
  return result == 0;
}

#endif 
