// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef __ARCH_GENERIC_ATOMIC__
#define __ARCH_GENERIC_ATOMIC__
//////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Machine/Generic/Atomic.hh"
//! userlevel=Default
//! author="Charles Galambos"
//! date="25/02/99"
//! rcsid="$Id$"
//! docentry="Ravl.Core.Misc"
/********************************************************************
//! lib=RavlCore
 * Dummy atomic operation file.
 */

typedef int ravl_atomic_t;

#define ravl_atomic_read(v)		(*v)
#define ravl_atomic_set(v,i)		((*v) = (i))

static inline void ravl_atomic_inc(ravl_atomic_t *v)
{ (*v)++; }

static inline void ravl_atomic_dec(ravl_atomic_t *v)
{ (*v)--; }

static inline int ravl_atomic_dec_and_test(ravl_atomic_t *v)
{ return (--(*v)) == 0; }

#endif /* !(__ARCH_SPARC_ATOMIC__) */
