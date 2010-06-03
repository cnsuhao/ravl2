// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_GENERIC_ATOMIC_HEADER 
#define RAVL_GENERIC_ATOMIC_HEADER 1
//////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Machine/Generic/Atomic.hh"
//! userlevel=Default
//! author="Charles Galambos"
//! date="25/02/1999"
//! rcsid="$Id: Atomic.hh 5240 2005-12-06 17:16:50Z plugger $"
//! docentry="Ravl.API.Core.Misc"
//! lib=RavlCore

typedef int ravl_atomic_t;

#define RAVL_ATOMIC_INIT(i)	{ (i) }

#define ravl_atomic_read(v)		(*v)
#define ravl_atomic_set(v,i)		((*v) = (i))

static inline void ravl_atomic_inc(ravl_atomic_t *v)
{ (*v)++; }

static inline void ravl_atomic_dec(ravl_atomic_t *v)
{ (*v)--; }

static inline int ravl_atomic_dec_and_test(ravl_atomic_t *v)
{ return (--(*v)) == 0; }

static inline int ravl_atomic_inc_return(ravl_atomic_t *v)
{ return ++(*v); }

#endif
