// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////////
// $Id$
//! rcsid="$Id$"
//! lib=RavlCore

#include <iostream.h>
#include "Ravl/Random.hh"
#include "Ravl/MTLocks.hh"

#define DODEBUG 1

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

extern "C" {
  extern unsigned short *seed48(unsigned short *);
};


namespace RavlN {

  RandomSeedT randomIdum;
  // The default variable of generators.

  static unsigned short *st = seed48(randomIdum);
  
  // Returns an integer between 0 and RandomIntMax.
  
  long int RandomInt() {
    MTWriteLockC lock(1);
    return RandomInt(randomIdum);
  }
  
  // Returns a uniform random number between 0 and 1.
  
  double Random1() {
    MTWriteLockC lock(1);
    return Random1(randomIdum);
  }

}


// IAPS - Image analysis program system.
// End of file Random.cc



